
/**
 * @file stm32f401re.h
 * @brief This is an MCU Specific header file for stm32f401re
 *
 *
 * @author Abhishek JP
 * @date 06-10-2026
 *
 */
#ifndef STM32F401RE_H
#define STM32F401RE_H

#include <stdint.h>

/* CR1 Bits */
#define I2C_CR1_PE      (1U << 0)
#define I2C_CR1_START   (1U << 8)
#define I2C_CR1_STOP    (1U << 9)
#define I2C_CR1_ACK     (1U << 10)
#define I2C_CR1_SWRST   (1U << 15)

/* SR1 Bits */
#define I2C_SR1_SB      (1U << 0)
#define I2C_SR1_ADDR    (1U << 1)
#define I2C_SR1_BTF     (1U << 2)
#define I2C_SR1_TXE     (1U << 7)
#define I2C_SR1_AF      (1U << 10)

/* SR2 Bits */
#define I2C_SR2_BUSY    (1U << 1)


/* GPIO Alternate Function Select */
typedef enum{
    GPIO_AF0  = 0U,
    GPIO_AF1  = 1U,
    GPIO_AF2  = 2U,
    GPIO_AF3  = 3U,
    GPIO_AF4  = 4U,
    GPIO_AF5  = 5U,
    GPIO_AF6  = 6U,
    GPIO_AF7  = 7U,
    GPIO_AF8  = 8U,
    GPIO_AF9  = 9U,
    GPIO_AF10 = 10U,
    GPIO_AF11 = 11U,
    GPIO_AF12 = 12U,
    GPIO_AF13 = 13U,
    GPIO_AF14 = 14U,
    GPIO_AF15 = 15U
}GPIO_AF_t;

/* GPIO Peripheral Definitions */
#define GPIOA ((GPIO_RegDef_t*)(GPIO_BASE + 0x00U))
#define GPIOB ((GPIO_RegDef_t*)(GPIO_BASE + 0x0400U))
#define GPIOC ((GPIO_RegDef_t*)(GPIO_BASE + 0x0800U))
#define GPIOD ((GPIO_RegDef_t*)(GPIO_BASE + 0x0C00U))
#define GPIOE ((GPIO_RegDef_t*)(GPIO_BASE + 0x1000U))
#define GPIOH ((GPIO_RegDef_t*)(GPIO_BASE + 0x1C00U))

/* I2C Peripheral Definitions */
#define I2C1 ((I2C_RegDef_t*)(I2C_BASE + 0U))
#define I2C2 ((I2C_RegDef_t*)(I2C_BASE + 0x400U))
#define I2C3 ((I2C_RegDef_t*)(I2C_BASE + 0x800U))

/* GPIO Register Definition */
 typedef struct{

    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];

}GPIO_RegDef_t;

 /* I2C Register Definition */
typedef struct{

    volatile uint32_t I2C_CR1;
    volatile uint32_t I2C_CR2;
    volatile uint32_t I2C_OAR1;
    volatile uint32_t I2C_OAR2;
    volatile uint32_t I2C_DR;
    volatile uint32_t I2C_SR1;
    volatile uint32_t I2C_SR2;
    volatile uint32_t I2C_CCR;
    volatile uint32_t I2C_TRISE;
    volatile uint32_t I2C_FLTR;

}I2C_RegDef_t;

/* Base Addresses */
#define RCC_BASE  0x40023800U
#define GPIO_BASE 0x40020000U
#define I2C_BASE  0x40005400U


/* RCC Registers */
#define RCC_AHB1ENR    (*(volatile uint32_t *)(RCC_BASE + 0x30U))
#define RCC_AHB2ENR    (*(volatile uint32_t *)(RCC_BASE + 0x34U))
#define RCC_APB1ENR    (*(volatile uint32_t *)(RCC_BASE + 0x40U))
#define RCC_APB2ENR    (*(volatile uint32_t *)(RCC_BASE + 0x44U))
#define RCC_AHB1LPENR  (*(volatile uint32_t *)(RCC_BASE + 0x50U))
#define RCC_AHB2LPENR  (*(volatile uint32_t *)(RCC_BASE + 0x54U))
#define RCC_APB1LPENR  (*(volatile uint32_t *)(RCC_BASE + 0x60U))
#define RCC_APB2LPENR  (*(volatile uint32_t *)(RCC_BASE + 0x64U))
#define RCC_BDCR       (*(volatile uint32_t *)(RCC_BASE + 0x70U))
#define RCC_CSR        (*(volatile uint32_t *)(RCC_BASE + 0x74U))
#define RCC_SSCGR      (*(volatile uint32_t *)(RCC_BASE + 0x80U))
#define RCC_PLLI2SCFGR (*(volatile uint32_t *)(RCC_BASE + 0x84U))
#define RCC_DCKCFGR    (*(volatile uint32_t *)(RCC_BASE + 0x8CU))
 


/* GPIO Limits */
#define MAX_PIN 15U

/*GPIO States */
typedef enum{
    GPIO_PIN_HIGH = 1U,
    GPIO_PIN_LOW = 0U
}GPIO_State_t;

typedef enum{
    GPIO_NO_PUPD = 0x00U,
    GPIO_PULL_UP = 0x01U,
    GPIO_PULL_DOWN = 0x02U
}GPIO_PuPd_t;

typedef enum{
    
    GPIO_SPEED_LOW       = 0x00U,
    GPIO_SPEED_MEDIUM    = 0x01U,
    GPIO_SPEED_HIGH      = 0x02U,
    GPIO_SPEED_VERY_HIGH = 0x03U
}GPIO_Speed_t;


typedef enum{
    GPIO_OUTPUT_PP = 0,
    GPIO_OUTPUT_OD = 1U
}GPIO_PPOD_t;

typedef enum
{
    GPIO_MODE_INPUT  = 0x00U,
    GPIO_MODE_OUTPUT = 0x01U,
    GPIO_MODE_AF      = 0x02U,
    GPIO_MODE_ANALOG = 0x03U

} GPIO_Mode_t;

typedef enum{
    S_Mode = 1U,
    F_Mode = 0U
}I2C_Clock_Mode_t;


typedef struct{

    uint8_t pin;
    GPIO_PuPd_t pupd;
    GPIO_PPOD_t type;
    GPIO_Speed_t speed;
    GPIO_Mode_t mode;
    GPIO_AF_t    af;

}GPIO_Config_t;

typedef struct {
    uint8_t addr;
    uint8_t len;
    const uint8_t *data;
} I2C_Config_t;

#endif /* STM32F401RE_H */
