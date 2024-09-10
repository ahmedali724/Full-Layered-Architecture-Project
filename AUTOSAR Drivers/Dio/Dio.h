/*
 ============================================================================
 Name        : Dio.h
 Module Name : DIO
 Author      : Ahmed Ali
 Date        : 7 Aug. 2024
 Description : Header file for TM4C123GH6PM Microcontroller - Dio Driver
 ============================================================================
 */

#ifndef DIO_H
#define DIO_H

#define DIO_VENDOR_ID    (2002U)

/* Dio Module Id */
#define DIO_MODULE_ID    (120U)

/* Dio Instance Id */
#define DIO_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define DIO_SW_MAJOR_VERSION           (1U)
#define DIO_SW_MINOR_VERSION           (0U)
#define DIO_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_AR_RELEASE_MAJOR_VERSION   (4U)
#define DIO_AR_RELEASE_MINOR_VERSION   (0U)
#define DIO_AR_RELEASE_PATCH_VERSION   (3U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Dio Pre-Compile Configuration Header file */
#include "Dio_Cfg.h"

/* AUTOSAR Version checking between Dio_Cfg.h and Dio.h files */
#if ((DIO_CFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Dio_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((DIO_CFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_CFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_CFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif

/* Dio Types Header file */
#include "Dio_Types.h"

/* AUTOSAR Version checking between Dio_Types.h and Dio.h files */
#if ((DIO_TYPES_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_TYPES_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_TYPES_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Dio_Types.h does not match the expected version"
#endif

/* Software Version checking between Dio_Types.h and Dio.h files */
#if ((DIO_TYPES_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_TYPES_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_TYPES_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
#error "The SW version of Dio_Types.h does not match the expected version"
#endif

/* Port Post Build Configuration Header file */
#include "Dio_PBcfg.h"

/* AUTOSAR Version checking between Dio_PBcfg.h and Dio.h files */
#if ((DIO_PBCFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Dio_PBcfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.h and Dio.h files */
#if ((DIO_PBCFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_PBCFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_PBCFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
#error "The SW version of Dio_PBcfg.h does not match the expected version"
#endif

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for the Dio_ReadChannel API.
 * Used to identify the Dio_ReadChannel service when reporting errors to DET. */
#define DIO_READ_CHANNEL_SID           (uint8)0x00

/* Service ID for the Dio_WriteChannel API.
 * Used to identify the Dio_WriteChannel service when reporting errors to DET. */
#define DIO_WRITE_CHANNEL_SID          (uint8)0x01

/* Service ID for the Dio_ReadPort API.
 * Used to identify the Dio_ReadPort service when reporting errors to DET. */
#define DIO_READ_PORT_SID              (uint8)0x02

/* Service ID for the Dio_WritePort API.
 * Used to identify the Dio_WritePort service when reporting errors to DET. */
#define DIO_WRITE_PORT_SID             (uint8)0x03

/* Service ID for the Dio_ReadChannelGroup API.
 * Used to identify the Dio_ReadChannelGroup service when reporting errors to DET. */
#define DIO_READ_CHANNEL_GROUP_SID     (uint8)0x04

/* Service ID for the Dio_WriteChannelGroup API.
 * Used to identify the Dio_WriteChannelGroup service when reporting errors to DET. */
#define DIO_WRITE_CHANNEL_GROUP_SID    (uint8)0x05

/* Service ID for the Dio_GetVersionInfo API.
 * Used to identify the Dio_GetVersionInfo service when reporting errors to DET. */
#define DIO_GET_VERSION_INFO_SID       (uint8)0x12

/* Service ID for the Dio_Init API.
 * Used to identify the Dio_Init service when reporting errors to DET. */
#define DIO_INIT_SID                   (uint8)0x10

/* Service ID for the Dio_FlipChannel API.
 * Used to identify the Dio_FlipChannel service when reporting errors to DET. */
#define DIO_FLIP_CHANNEL_SID           (uint8)0x11

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report an Invalid Channel ID.
 * This error is reported when an invalid or undefined Channel ID is requested in an API call. */
#define DIO_E_PARAM_INVALID_CHANNEL_ID (uint8)0x0A

/* DET code to report a NULL pointer parameter passed to the Dio_Init API.
 * This error is reported when the configuration pointer passed to the Dio_Init API is null. */
#define DIO_E_PARAM_CONFIG             (uint8)0x10

/* DET code to report an Invalid Port ID.
 * This error is reported when an invalid or undefined Port ID is requested in an API call. */
#define DIO_E_PARAM_INVALID_PORT_ID    (uint8)0x14

/* DET code to report an Invalid Channel Group.
 * This error is reported when an invalid or undefined Channel Group is requested in an API call. */
#define DIO_E_PARAM_INVALID_GROUP      (uint8)0x1F

/* DET code to report a NULL pointer passed to an API service.
 * The API service will return immediately and only report this development error. */
#define DIO_E_PARAM_POINTER            (uint8)0x20

/* DET code to report the use of an API service without initializing the module.
 * This error is reported when a service is called before the Dio module is initialized.
 * Note: This code is not defined in the AUTOSAR 4.0.3 DIO SWS document. */
#define DIO_E_UNINIT                   (uint8)0xF0

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
 * Service Name: Dio_ReadPort
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): PortId - ID of DIO Port.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_PortLevelType
 * Description: Function to return the level of all channels of that port.
 ************************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/************************************************************************************
 * Service Name: Dio_WritePort
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): PortId - ID of DIO Port.
 *                  Level - Value to be written.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_PortLevelType
 * Description: Function to set a value of the port.
 ************************************************************************************/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/************************************************************************************
 * Service Name: Dio_ReadChannel
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_LevelType
 * Description: Function to return the value of the specified DIO channel.
 ************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/************************************************************************************
 * Service Name: Dio_WriteChannel
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 *                  Level - Value to be written.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set a level of a channel.
 ************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/************************************************************************************
 * Service Name: Dio_Init
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr - Pointer to post-build configuration data
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Initialize the Dio module.
 ************************************************************************************/
void Dio_Init(const Dio_ConfigType *ConfigPtr);

/************************************************************************************
 * Service Name: Dio_ReadChannelGroup
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_PortLevelType - Level of a subset of the adjoining bits of a port
 * Description: This Service reads a subset of the adjoining bits of a port.
 ************************************************************************************/
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr);

/************************************************************************************
 * Service Name: Dio_WriteChannelGroup
 * Service ID[hex]: 0x05
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup
 *                  Level - Value to be written
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Service to set a subset of the adjoining bits of a port to a specified level.
 ************************************************************************************/
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level);

#if (DIO_FLIP_CHANNEL_API == STD_ON)
/************************************************************************************
 * Service Name: Dio_FlipChannel
 * Service ID[hex]: 0x11
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_LevelType
 * Description: Function to flip the level of a channel and return the level of the channel after flip.
 ************************************************************************************/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif

#if (DIO_VERSION_INFO_API == STD_ON)
/************************************************************************************
 * Service Name: Dio_GetVersionInfo
 * Service ID[hex]: 0x12
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 ************************************************************************************/
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

#endif /* DIO_H */
