/*
 ============================================================================
 Name        : Port_PBcfg.h
 Module Name : Port
 Author      : Ahmed Ali
 Date        : 12 Aug. 2024
 Description : Post Build Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 ============================================================================
 */

#ifndef PORT_PBCFG_H_
#define PORT_PBCFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION                 (1U)
#define PORT_PBCFG_SW_MINOR_VERSION                 (0U)
#define PORT_PBCFG_SW_PATCH_VERSION                 (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION         (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION         (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION         (3U)

/* Enumeration for the Pin levels (used in the Port APIs) */
typedef enum
{
    PORT_PIN_LEVEL_LOW, /* Pin level is low (logical 0) */
    PORT_PIN_LEVEL_HIGH /* Pin level is high (logical 1) */
} Port_PinLevel_Value;

/* Enumeration for the direction changeability of a Pin (used in the Port APIs) */
typedef enum
{
    PORT_PIN_DIRECTION_CHANGEABLE_OFF, /* Pin direction cannot be changed after initialization */
    PORT_PIN_DIRECTION_CHANGEABLE_ON /* Pin direction can be changed after initialization */
} Port_PinDirectionChangeable;

/* Enumeration for the mode changeability of a Pin (used in the Port APIs) */
typedef enum
{
    PORT_PIN_MODE_CHANGEABLE_OFF, /* Pin mode cannot be changed after initialization */
    PORT_PIN_MODE_CHANGEABLE_ON /* Pin mode can be changed after initialization */
} Port_PinModeChangeable;

/* Enumeration for the internal resistor configuration of a Pin (used in the Port APIs) */
typedef enum
{
    PORT_INTERNAL_RESISTOR_OFF, /* No internal resistor connected */
    PORT_INTERNAL_RESISTOR_PULL_UP, /* Internal pull-up resistor connected */
    PORT_INTERNAL_RESISTOR_PULL_DOWN /* Internal pull-down resistor connected */
} Port_InternalResistor;

/* Enumeration for the mode configuration of a Pin (used in the Port APIs) */
typedef enum
{
    PORT_PIN_MODE_DIO, /* Digital I/O mode */
    PORT_PIN_MODE_ALT1, /* Alternate function 1 */
    PORT_PIN_MODE_ALT2, /* Alternate function 2 */
    PORT_PIN_MODE_ALT3, /* Alternate function 3 */
    PORT_PIN_MODE_ALT4, /* Alternate function 4 */
    PORT_PIN_MODE_ALT5, /* Alternate function 5 */
    PORT_PIN_MODE_ALT6, /* Alternate function 6 */
    PORT_PIN_MODE_ALT7, /* Alternate function 7 */
    PORT_PIN_MODE_ALT8, /* Alternate function 8 */
    PORT_PIN_MODE_ALT9, /* Alternate function 9 */
    PORT_PIN_MODE_ALT14 = 14,/* Alternate function 14 */
    PORT_PIN_MODE_AIN /* Analog input mode */
} Port_PinMode;

/* Structure representing the configuration of a single Pin */
typedef struct
{
    /* ID of the Port to which this Pin belongs */
    Port_Type Port_Num;

    /* ID of the Pin within the Port */
    Port_PinType Pin_Num;

    /* Direction of the Pin (input/output) */
    Port_PinDirectionType Pin_Direction;

    /* Internal resistor configuration (if input pin) */
    Port_InternalResistor Pin_InternalResistor;

    /* Initial level of the Pin (if output pin) */
    Port_PinLevel_Value Pin_InitialValue;

    /* Mode of the Pin (DIO, Alternate function, Analog) */
    Port_PinModeType Pin_Mode;

    /* Option to change the direction of the Pin after initialization */
    Port_PinDirectionChangeable Pin_DirectionChange;

    /* Option to change the mode of the Pin after initialization */
    Port_PinModeChangeable Pin_ModeChange;
} Port_ConfigPinType;

/* Structure representing the configuration for all Pins in the Port module */
typedef struct Port_ConfigType
{
    /* Array of Pin configuration structures */
    Port_ConfigPinType Pins[PORT_NUMBER_OF_PORT_PINS];
} Port_ConfigType;

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* External configuration structure to be used by the Port module 
 * and other modules that require access to the Port configuration.
 * This structure is defined and initialized in Port_PBcfg.c and contains
 * the configuration settings for all Port pins.
 */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_PBCFG_H_ */
