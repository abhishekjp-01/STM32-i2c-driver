/**
 * @file i2c.h
 * @brief I2C driver interface
 *
 *
 * @author Abhishek JP
 * @date 16-10-2026
 *
 */

#ifndef I2C_H
#define I2C_H


#include "gpio.h"

#define I2C_TIMEOUT 100000

 typedef enum{
    I2C_OK = 0,
    I2C_ERR_TIMEOUT,
    I2C_ERR_NACK
 }I2C_Status_t;

/**
 * @brief Initializes an I2C peripheral in master mode.
 *
 * This function enables the peripheral clock, performs a software reset,
 * programs the clock control registers for the selected bus speed and
 * enables the peripheral.
 *
 * The timing values assume PCLK1 = 16 MHz (HSI, no APB1 prescaler).
 * If the system clock configuration changes, CR2, CCR and TRISE
 * must be recalculated.
 *
 * @note The SCL and SDA pins must be configured as alternate function,
 *       open-drain (AF4 for I2C1) before calling this function, and
 *       external pull-up resistors must be present on the bus.
 *
 * @param i2c  Pointer to the I2C peripheral (I2C1, I2C2 or I2C3).
 * @param mode Bus speed: S_Mode for standard mode (100 kHz) or
 *             F_Mode for fast mode (400 kHz).
 *
 * @return void
 */
void i2c_init(I2C_RegDef_t *i2c, I2C_Clock_Mode_t mode);


/**
 * @brief Writes data to a slave device as an I2C master (blocking).
 *
 * This function waits for the bus to become free, generates a START
 * condition, sends the 7-bit slave address with the write bit, transmits
 * the data bytes and generates a STOP condition. It blocks until the
 * transfer finishes, fails or times out.
 *
 * @note The slave address in the configuration structure is the plain
 *       7-bit address. The function shifts it left by one bit internally
 *       to add the R/W bit.
 *
 * @note The buffer pointed to by config->data must remain valid for the
 *       whole duration of the call.
 *
 * @param i2c    Pointer to the I2C peripheral to use.
 * @param config Pointer to the transfer configuration: 7-bit slave
 *               address, pointer to the data buffer and number of bytes.
 *
 * @return I2C_OK            Transfer completed successfully.
 * @return I2C_ERR_NACK      The slave did not acknowledge the address or
 *                           a data byte.
 * @return I2C_ERR_TIMEOUT   The bus stayed busy or a flag was not set
 *                           within I2C_TIMEOUT iterations.
 */
I2C_Status_t i2c_write(I2C_RegDef_t *i2c, I2C_Config_t *config);


#endif /* I2C_H */
