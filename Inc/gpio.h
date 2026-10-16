
/**
 * @file gpio.h
 * @brief GPIO driver interface
 *
 * This header file provides the public interface for configuring
 * and initializing GPIO peripherals.
 *
 * @author Abhishek JP
 * @date 06-10-2026
 *
 */

#ifndef GPIO_H
#define GPIO_H

#include "stm32f401re.h"


/**
 * @brief Initializes a GPIO configuration structure with default values.
 *
 * This function initializes the configuration structure with default
 * GPIO settings. Individual configuration parameters can be modified
 * by the caller after calling this function.
 *
 * @param config Pointer to the GPIO configuration structure.
 *
 * @return void
 */
void gpio_config_default(GPIO_Config_t *config);


/**
 * @brief Initializes a GPIO peripheral according to the specified configuration.
 *
 * This function enables the GPIO peripheral clock and configures the
 * selected GPIO pin according to the parameters provided in the
 * GPIO configuration structure.
 *
 * @param gpio Pointer to the GPIO peripheral to be configured.
 * @param config Pointer to the GPIO configuration structure.
 *
 * @return void
 */
void gpio_init(GPIO_RegDef_t *gpio, GPIO_Config_t *config);


/**
 * @brief Sets or resets the specified GPIO pin.
 *
 * This function writes a HIGH or LOW state to the specified GPIO pin
 * using the GPIO Bit Set/Reset Register (BSRR).
 *
 * @param gpio Pointer to the GPIO peripheral to be controlled.
 * @param pin  Pin number (0 to MAX_PIN).
 * @param state Desired GPIO state (HIGH or LOW).
 *
 * @return void
 */
void gpio_write(GPIO_RegDef_t *gpio, uint8_t pin, GPIO_State_t state);

/**
 * @brief Reads the logic level of the specified GPIO pin.
 *
 * This function reads the Input Data Register (IDR) of the selected
 * GPIO peripheral and returns the current logic level present on
 * the specified pin.
 *
 * @param gpio Pointer to the GPIO peripheral to be read.
 * @param pin  Pin number (0 to MAX_PIN).
 *
 * @return GPIO_PIN_HIGH if the pin is at logic high,
 *         GPIO_PIN_LOW if the pin is at logic low or if the
 *         arguments are invalid (NULL gpio or pin out of range).
 */
GPIO_State_t gpio_read(GPIO_RegDef_t *gpio, uint8_t pin);

/**
 * @brief Toggles the output level of the specified GPIO pin.
 *
 * This function inverts the current output state of the selected pin
 * by modifying the Output Data Register (ODR).
 *
 * @param gpio Pointer to the GPIO peripheral to be controlled.
 * @param pin  Pin number (0 to MAX_PIN).
 *
 * @return void
 */
void gpio_toggle(GPIO_RegDef_t *gpio, uint8_t pin);

#endif /* GPIO_H */

