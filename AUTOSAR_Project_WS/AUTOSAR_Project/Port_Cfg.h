/*
 ============================================================================
 Name        : Port_Cfg.h
 Module Name : Port
 Author      : Ahmed Ali
 Date        : 12 Aug. 2024
 Description : Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 ============================================================================
 */

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION           (1U)
#define PORT_CFG_SW_MINOR_VERSION           (0U)
#define PORT_CFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION   (3U)

/* Pre-compile option for enabling Development Error Detection.
 * STD_ON enables development error detection for the Port module.
 * STD_OFF disables it. */
#define PORT_DEV_ERROR_DETECT               (STD_ON)

/* Pre-compile option for enabling the Port_SetPinDirection API.
 * STD_ON includes the API function in the compilation.
 * STD_OFF excludes it from the compilation. */
#define PORT_SET_PIN_DIRECTION_API          (STD_ON)

/* Pre-compile option for enabling the Port_SetPinMode API.
 * STD_ON includes the API function in the compilation.
 * STD_OFF excludes it from the compilation. */
#define PORT_SET_PIN_MODE_API               (STD_ON)

/* Pre-compile option for enabling the Version Info API.
 * STD_ON includes the API function in the compilation.
 * STD_OFF excludes it from the compilation. */
#define PORT_VERSION_INFO_API               (STD_ON)

/* The total number of Port Pins available in the microcontroller.
 * This defines the size of the configuration array. */
#define PORT_NUMBER_OF_PORT_PINS            (39U)

/* Defines the initial mode for all pins during initialization.
 * Default is set to Digital I/O (DIO) mode. */
#define PORT_PIN_INITIAL_MODE               PORT_PIN_MODE_DIO

/* Pin index definitions for Port A (used in configuration array) */
#define PortConf_PINA0_ID_INDEX             (0U)
#define PortConf_PINA1_ID_INDEX             (1U)
#define PortConf_PINA2_ID_INDEX             (2U)
#define PortConf_PINA3_ID_INDEX             (3U)
#define PortConf_PINA4_ID_INDEX             (4U)
#define PortConf_PINA5_ID_INDEX             (5U)
#define PortConf_PINA6_ID_INDEX             (6U)
#define PortConf_PINA7_ID_INDEX             (7U)

/* Pin index definitions for Port B (used in configuration array) */
#define PortConf_PINB0_ID_INDEX             (8U)
#define PortConf_PINB1_ID_INDEX             (9U)
#define PortConf_PINB2_ID_INDEX             (10U)
#define PortConf_PINB3_ID_INDEX             (11U)
#define PortConf_PINB4_ID_INDEX             (12U)
#define PortConf_PINB5_ID_INDEX             (13U)
#define PortConf_PINB6_ID_INDEX             (14U)
#define PortConf_PINB7_ID_INDEX             (15U)

/* Pin index definitions for Port C (used in configuration array) */
#define PortConf_PINC4_ID_INDEX             (16U)
#define PortConf_PINC5_ID_INDEX             (17U)
#define PortConf_PINC6_ID_INDEX             (18U)
#define PortConf_PINC7_ID_INDEX             (19U)

/* Pin index definitions for Port D (used in configuration array) */
#define PortConf_PIND0_ID_INDEX             (20U)
#define PortConf_PIND1_ID_INDEX             (21U)
#define PortConf_PIND2_ID_INDEX             (22U)
#define PortConf_PIND3_ID_INDEX             (23U)
#define PortConf_PIND4_ID_INDEX             (24U)
#define PortConf_PIND5_ID_INDEX             (25U)
#define PortConf_PIND6_ID_INDEX             (26U)
#define PortConf_PIND7_ID_INDEX             (27U)

/* Pin index definitions for Port E (used in configuration array) */
#define PortConf_PINE0_ID_INDEX             (28U)
#define PortConf_PINE1_ID_INDEX             (29U)
#define PortConf_PINE2_ID_INDEX             (30U)
#define PortConf_PINE3_ID_INDEX             (31U)
#define PortConf_PINE4_ID_INDEX             (32U)
#define PortConf_PINE5_ID_INDEX             (33U)

/* Pin index definitions for Port F (used in configuration array) */
#define PortConf_PINF0_ID_INDEX             (34U)
#define PortConf_PINF1_ID_INDEX             (35U)
#define PortConf_PINF2_ID_INDEX             (36U)
#define PortConf_PINF3_ID_INDEX             (37U)
#define PortConf_PINF4_ID_INDEX             (38U)

/* Definitions for Port IDs (used to identify the Port in the microcontroller) */
#define PORTA_ID                            (Port_Type)0
#define PORTB_ID                            (Port_Type)1
#define PORTC_ID                            (Port_Type)2
#define PORTD_ID                            (Port_Type)3
#define PORTE_ID                            (Port_Type)4
#define PORTF_ID                            (Port_Type)5

/* Definitions for Pin IDs (used to identify the Pin within a Port) */
#define PIN0_ID                             (Port_PinType)0
#define PIN1_ID                             (Port_PinType)1
#define PIN2_ID                             (Port_PinType)2
#define PIN3_ID                             (Port_PinType)3
#define PIN4_ID                             (Port_PinType)4
#define PIN5_ID                             (Port_PinType)5
#define PIN6_ID                             (Port_PinType)6
#define PIN7_ID                             (Port_PinType)7

#endif /* PORT_CFG_H_ */
