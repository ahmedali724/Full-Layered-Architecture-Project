/*
 ============================================================================
 Name        : Dio_PBcfg.h
 Module Name : Dio
 Author      : Ahmed Ali
 Date        : 7 Aug. 2024
 Description : Post Build Configuration Header file for TM4C123GH6PM Microcontroller - Dio Driver
 ============================================================================
 */

#ifndef DIO_PBCFG_H_
#define DIO_PBCFG_H_

/*
 * Module Version 1.0.0
 */
#define DIO_PBCFG_SW_MAJOR_VERSION              (1U)
#define DIO_PBCFG_SW_MINOR_VERSION              (0U)
#define DIO_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for a structure that holds the initialization parameters
 * for a DIO channel, including its Port and Channel ID. */
typedef struct
{
    /* ID of the Port that this channel belongs to.
     * This corresponds to a specific port in the microcontroller. */
    Dio_PortType Port_Num;

    /* ID of the Channel within the specified Port.
     * This identifies the specific pin within the Port. */
    Dio_ChannelType Ch_Num;
} Dio_ConfigChannel;

/* Data Structure required for initializing the Dio Driver.
 * This structure holds the configuration for all the DIO channels
 * specified in the system. */
typedef struct Dio_ConfigType
{
    /* Array of DIO channels to be initialized.
     * The size of the array corresponds to the number of configured channels. */
    Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNLES];
} Dio_ConfigType;

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* External configuration structure to be used by the Dio module
 * and other modules that require access to the DIO configuration.
 * This structure is defined and initialized in Dio_PBcfg.c. */
extern const Dio_ConfigType Dio_Configuration;

#endif /* DIO_PBCFG_H_ */
