/*
 ============================================================================
 Name        : Port_Types.h
 Module Name : Port
 Author      : Ahmed Ali
 Date        : 12 Aug. 2024
 Description : Types Header file for TM4C123GH6PM Microcontroller - Port Driver
 ============================================================================
 */

#ifndef PORT_TYPES_H_
#define PORT_TYPES_H_

/*
 * Module Version 1.0.0
 */
#define PORT_TYPES_SW_MAJOR_VERSION           (1U)
#define PORT_TYPES_SW_MINOR_VERSION           (0U)
#define PORT_TYPES_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_TYPES_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_TYPES_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_TYPES_AR_RELEASE_PATCH_VERSION   (3U)

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Port_PinType (used by the Port APIs)
 * Represents the ID of a Pin within a Port.
 * Range and interpretation of the value depend on the microcontroller's specifications. */
typedef uint8 Port_PinType;

/* Type definition for Port_Type (used by the Port APIs)
 * Represents the ID of a Port in the microcontroller.
 * The value corresponds to specific ports as defined by the microcontroller. */
typedef uint8 Port_Type;

/* Enumeration for the direction of a Pin (used by the Port APIs)
 * Defines whether the Pin is configured as an input or an output. */
typedef enum
{
    PORT_PIN_IN, /* Pin is configured as an input */
    PORT_PIN_OUT /* Pin is configured as an output */
} Port_PinDirectionType;

/* Type definition for Port_PinModeType (used by the Port APIs)
 * Represents the mode of a Pin (Digital I/O, Analog input, or any alternate function).
 * This value is used to configure the mode of the Pin as specified by the microcontroller's alternate function configuration. */
typedef uint8 Port_PinModeType;

#endif /* PORT_TYPES_H_ */
