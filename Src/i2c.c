/**
 * @file i2c.c
 * @brief I2C driver implementation for STM32
 *
 *
 * @author Abhishek JP
 * @date 16-10-2026
 *
 */
#include"i2c.h"
#include"gpio.h"

/**
 * @brief Waits until a flag in the I2C status register 1 is set.
 *
 * This function polls SR1 until the requested flag is set. If the
 * acknowledge failure flag (AF) is detected, it clears the flag, requests
 * a STOP condition and aborts. If the flag does not appear within
 * I2C_TIMEOUT iterations, it aborts with a timeout error.
 *
 * This is an internal helper function and is only accessible within
 * this source file.
 *
 * @param i2c  Pointer to the I2C peripheral.
 * @param flag Bit mask of the SR1 flag to wait for (e.g. I2C_SR1_SB,
 *             I2C_SR1_ADDR, I2C_SR1_TXE, I2C_SR1_BTF).
 *
 * @return I2C_OK            The flag was set.
 * @return I2C_ERR_NACK      The slave did not acknowledge.
 * @return I2C_ERR_TIMEOUT   The flag was not set in time.
 */
static I2C_Status_t i2c_wait(I2C_RegDef_t *i2c, uint32_t flag);



static I2C_Status_t i2c_wait(I2C_RegDef_t *i2c, uint32_t flag)
{
    uint32_t t = I2C_TIMEOUT;
    while (!(i2c->I2C_SR1 & flag)) {
        if (i2c->I2C_SR1 & I2C_SR1_AF) {
            i2c->I2C_SR1 &= ~I2C_SR1_AF;
            i2c->I2C_CR1 |= I2C_CR1_STOP;
            return I2C_ERR_NACK;
        }
        if (--t == 0U) return I2C_ERR_TIMEOUT;
    }
    return I2C_OK;
}


 void i2c_init(I2C_RegDef_t* i2c, I2C_Clock_Mode_t mode){

    /* Enable clock for i2c */
    if(i2c == I2C1)
        RCC_APB1ENR |= (1 << 21);
    else if(i2c == I2C2)
        RCC_APB1ENR |= (1 << 22);
    else if(i2c == I2C3)
        RCC_APB1ENR |= (1 << 23);
    (void)(RCC_APB1ENR);

/* Reset I2C */
i2c->I2C_CR1 |= (1 << 15);
i2c->I2C_CR1 &= ~(1 << 15);



/* Clock config */
i2c->I2C_CR2 = 16U;
if (mode == S_Mode) {
    i2c->I2C_CCR   = 80U;
    i2c->I2C_TRISE = 17U;
} else {
    i2c->I2C_CCR   = (1U << 15) | 13U;
    i2c->I2C_TRISE = 5U;
}

/* Enable Peripheral */
i2c->I2C_CR1 |= (1U << 0);

 }

I2C_Status_t i2c_write(I2C_RegDef_t *i2c, I2C_Config_t* config){

    I2C_Status_t s;
    volatile uint32_t tmp;

    /* Wait until bus is free */
    uint32_t t = I2C_TIMEOUT;
    while (i2c->I2C_SR2 & I2C_SR2_BUSY) 
        if (--t == 0U) return I2C_ERR_TIMEOUT;


    /* Start */
    i2c->I2C_CR1 |= (I2C_CR1_START);
    if((s = i2c_wait(i2c, I2C_SR1_SB)) != I2C_OK) return s; // Check Start Condition generated

    /* Target Address + Write bit(0)*/
    i2c->I2C_DR = (uint8_t)(config->addr << 1);
    if((s = i2c_wait(i2c, I2C_SR1_ADDR)) != I2C_OK) return s; // Check Address Sent 

    /* Clear ADDR by reading SR1 then SR2 */
    tmp = i2c->I2C_SR1;
    tmp = i2c->I2C_SR2;
    (void)tmp;

    /* Sent Data */
    for (uint16_t i = 0; i < config->len; i++) {
        if ((s = i2c_wait(i2c, I2C_SR1_TXE)) != I2C_OK) return s;
        i2c->I2C_DR = config->data[i];
    }

    /* Wait for last byte to fully shift out */
    if ((s = i2c_wait(i2c, I2C_SR1_BTF)) != I2C_OK) return s;

    /* Stop */
    i2c->I2C_CR1 |= I2C_CR1_STOP;
    return I2C_OK;

 }
