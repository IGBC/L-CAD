#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include "stdint.h"
#include <stdbool.h>
#include <stdlib.h>

/** @file */

/** @brief IO types for internal use with the IO module */
typedef enum { IOM_OUT, /**< @brief Output */
               IOM_IN, /**< @brief FLoating Input */
                IOM_IN_UP, /**< @brief Input with pull up resistor */
                IOM_IN_DOWN /**< @brief Input with pull down resistor */
             } IO_Mode;


/** @brief Container for an IO pin.
  *
  * This container wraps all information needed to associate a GPIO pin with a
  * node in the logic graph. All IO functions use these IO wrappers */
struct {
	uint8_t address; /**< @brief The physical hardware address.
	    * In this implementation this is a number of the BCM port provided by
	    * wiringPi */
    size_t ID; /**< @brief The ID of the graph node this port is assosiated with */
	IO_Mode mode; /**< @brief The mode of the port */
} typedef IO_Item;

/**
 * @brief Set up GPIO Pin
 *
 * Configures the desied GPIO Pin to be in a usable state, and returns a struct
 * describing the IO port, for later use.
 *
 * @param uint8_t pin    The physical address of the GPIO Pin.
 * @param IO_Mode mode   The operation mode for the Pin.
 *
 * @returns IO_Item*     Struct describing the IO port created.
 */
IO_Item *setupPin(uint8_t pin, IO_Mode mode);

/**
 * @brief Frees a specified IO port.
 *
 * Frees the IO port and clears any resources used by it. The provided port 
 * can not be used after calling this function.
 *
 * Cleared Ports are left in the input state with all pull resistors disabled.
 *
 * @param IO_Item* pin   The port to be freed.
 *
 */
void cleanPin(IO_Item *pin);

/**
 * @brief Reads value from given IO port.
 *
 * Returns a boolean value of the state of the port given. This function works
 * on both input and output ports.
 *
 * @param IO_Item* input   The port to read from.
 * @returns bool           The current value of the port.
 */
bool readInput(IO_Item *input);

/**
 * @brief Write a value to the specified port
 *
 * Writes the given value into the IO port specified. This function only works 
 * for ports configured as IOM_OUTPUT.
 *
 * @param IO_Item* output   The output to write to.
 * @param bool state        The value to write.
 *
 */
void writeOutput(IO_Item *output, bool state);

#endif
