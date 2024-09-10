/*
 ============================================================================
 Name        : Dio_cfg.h
 Module Name : Dio
 Author      : Ahmed Ali
 Date        : 7 Aug. 2024
 Description : Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Dio Driver
 ============================================================================
 */

#ifndef DIO_CFG_H
#define DIO_CFG_H

/*
 * Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION              (1U)
#define DIO_CFG_SW_MINOR_VERSION              (0U)
#define DIO_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for enabling Development Error Detection.
 * STD_ON enables development error detection for the DIO module.
 * STD_OFF disables it. */
#define DIO_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for enabling the Version Info API.
 * STD_ON includes the API function in the compilation.
 * STD_OFF excludes it from the compilation. */
#define DIO_VERSION_INFO_API                (STD_OFF)

/* Pre-compile option for enabling the Dio_FlipChannel API.
 * STD_ON includes the API function in the compilation.
 * STD_OFF excludes it from the compilation. */
#define DIO_FLIP_CHANNEL_API                (STD_ON)

/* Number of Configured DIO Channels.
 * This defines the total number of Digital Input/Output (DIO) channels that are configured in the system.
 * This value indicates how many DIO channels are available for use in the application.
 */
#define DIO_CONFIGURED_CHANNLES             (2U)

/* Number of Configured DIO Groups.
 * This defines the total number of DIO groups configured in the system.
 * This value indicates how many groups of DIO channels are defined, which can be used to manage multiple channels as a single unit.
 */
#define DIO_CONFIGURED_GROUPS               (0U)

/* Channel index definitions for the configured DIO channels in the Dio_PBcfg.c file.
 * These indices are used to access the channel configurations in the array. */
#define DioConf_LED1_CHANNEL_ID_INDEX       (uint8)0x00
#define DioConf_SW1_CHANNEL_ID_INDEX        (uint8)0x01

/* DIO Configured Port IDs.
 * These macros define the port numbers for the configured DIO channels. */
#define DioConf_LED1_PORT_NUM               (Dio_PortType)5 /* LED1 is located on Port F */
#define DioConf_SW1_PORT_NUM                (Dio_PortType)5 /* SW1 is located on Port F */

/* DIO Configured Channel IDs.
 * These macros define the specific pin numbers within the configured ports. */
#define DioConf_LED1_CHANNEL_NUM            (Dio_ChannelType)1 /* LED1 is connected to Pin 1 in Port F */
#define DioConf_SW1_CHANNEL_NUM             (Dio_ChannelType)4 /* SW1 is connected to Pin 4 in Port F */

#endif /* DIO_CFG_H */
