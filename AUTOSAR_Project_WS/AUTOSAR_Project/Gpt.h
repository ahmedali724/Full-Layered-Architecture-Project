/*
 ============================================================================
 Name        : Gpt.h
 Module Name : Gpt
 Author      : Ahmed Ali
 Date        : 15 Aug. 2024
 Description : Header file for TM4C123GH6PM Microcontroller - Gpt Driver
 ============================================================================
 */

#ifndef GPT_H_
#define GPT_H_

#define GPT_VENDOR_ID    (2002U)

/* Gpt Module Id */
#define GPT_MODULE_ID    (124U)

/* Gpt Instance Id */
#define GPT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define GPT_SW_MAJOR_VERSION                (1U)
#define GPT_SW_MINOR_VERSION                (0U)
#define GPT_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_AR_RELEASE_MAJOR_VERSION        (4U)
#define GPT_AR_RELEASE_MINOR_VERSION        (0U)
#define GPT_AR_RELEASE_PATCH_VERSION        (3U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Gpt Pre-Compile Configuration Header file */
#include "Gpt_Cfg.h"

/* AUTOSAR Version checking between Gpt_Cfg.h and Gpt.h files */
#if ((GPT_CFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Gpt_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Gpt_Cfg.h and Gpt.h files */
#if ((GPT_CFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_CFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_CFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
#error "The SW version of Gpt_Cfg.h does not match the expected version"
#endif

/* Gpt Types Header file */
#include "Gpt_Types.h"

/* AUTOSAR Version checking between Gpt_Types.h and Port.h files */
#if ((GPT_TYPES_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_TYPES_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_TYPES_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Gpt_Types.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((GPT_TYPES_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_TYPES_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_TYPES_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
#error "The SW version of Gpt_Types.h does not match the expected version"
#endif

/* Gpt Post Build Configuration Header file */
#include "Gpt_PBcfg.h"

/* AUTOSAR Version checking between Gpt_PBcfg.h and Gpt.h files */
#if ((GPT_PBCFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_PBcfg.h does not match the expected version"
#endif

/* Software Version checking between Gpt_PBcfg.h and Gpt.h files */
#if ((GPT_PBCFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_PBCFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_PBCFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
#error "The SW version of Gpt_PBcfg.h does not match the expected version"
#endif

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for the Gpt_GetVersionInfo API.
 * Retrieves the version information of the GPT module. */
#define GPT_GET_VERSION_INFO_SID            (uint8)0x00

/* Service ID for the Gpt_Init API.
 * Initializes the GPT module. */
#define GPT_INIT_SID                        (uint8)0x01

/* Service ID for the Gpt_DeInit API.
 * De-initializes the GPT module. */
#define GPT_DE_INIT_SID                     (uint8)0x02

/* Service ID for the Gpt_GetTimeElapsed API.
 * Retrieves the elapsed time since the timer was started. */
#define GPT_GET_TIME_ELAPSED_SID            (uint8)0x03

/* Service ID for the Gpt_GetTimeRemaining API.
 * Retrieves the remaining time until the timer expires. */
#define GPT_GET_TIME_REMAINING_SID          (uint8)0x04

/* Service ID for the Gpt_StartTimer API.
 * Starts the specified timer channel. */
#define GPT_START_TIMER_SID                 (uint8)0x05

/* Service ID for the Gpt_StopTimer API.
 * Stops the specified timer channel. */
#define GPT_STOP_TIMER_SID                  (uint8)0x06

/* Service ID for the Gpt_EnableNotification API.
 * Enables notifications for the specified timer channel. */
#define GPT_ENABLE_NOTIFICATION_SID         (uint8)0x07

/* Service ID for the Gpt_DisableNotification API.
 * Disables notifications for the specified timer channel. */
#define GPT_DISABLE_NOTIFICATION_SID        (uint8)0x08

/* Service ID for the Gpt_SetMode API.
 * Sets the mode of the GPT module. */
#define GPT_SET_MODE_SID                    (uint8)0x09

/* Service ID for the Gpt_DisableWakeup API.
 * Disables wake-up capability for the specified timer channel. */
#define GPT_DISABLE_WAKEUP_SID              (uint8)0x0A

/* Service ID for the Gpt_EnableWakeup API.
 * Enables wake-up capability for the specified timer channel. */
#define GPT_ENABLE_WAKEUP_SID               (uint8)0x0B

/* Service ID for the Gpt_CheckWakeup API.
 * Checks if the specified timer channel has wake-up capability. */
#define GPT_CHECK_WAKEUP_SID                (uint8)0x0C

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report that an API service was called without initializing the module. */
#define GPT_E_UNINIT                    (uint8)0x0A

/* DET code to report that an API service was called while the timer channel is still busy. */
#define GPT_E_BUSY                      (uint8)0x0B

/* DET code to report that the initialization API was called when the module is already initialized. */
#define GPT_E_ALREADY_INITIALIZED       (uint8)0x0D

/* DET code to report invalid channel ID in API parameter checking. */
#define GPT_E_PARAM_CHANNEL             (uint8)0x14

/* DET code to report invalid value in API parameter checking. */
#define GPT_E_PARAM_VALUE               (uint8)0x15

/* DET code to report invalid pointer in API parameter checking. */
#define GPT_E_PARAM_POINTER             (uint8)0x16

/* DET code to report invalid mode in API parameter checking. */
#define GPT_E_PARAM_MODE                (uint8)0x1F

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

#if (GPT_VERSION_INFO_API == STD_ON)
/************************************************************************************
 * Service Name: Gpt_GetVersionInfo
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfoPtr - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to Return the version information of this module.
 ************************************************************************************/
void Gpt_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr);
#endif

/************************************************************************************
 * Service Name: Gpt_Init
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): ConfigPtr - Pointer to a selected configuration structure
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Initialize the hardware timer module.
 ************************************************************************************/
void Gpt_Init(const Gpt_ConfigType *ConfigPtr);

#if (GPT_DEINIT_API == STD_ON)
/************************************************************************************
 * Service Name: Gpt_DeInit
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to De-initialize all hardware timer channels.
 ************************************************************************************/
void Gpt_DeInit(void);
#endif

#if (GPT_TIME_ELAPSED_API == STD_ON)
/************************************************************************************
 * Service Name: Gpt_GetTimeElapsed
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Channel - Numeric identifier of the GPT channel
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Gpt_ValueType - Elapsed timer value (in number of ticks)
 * Description: Function to Return the time already elapsed.
 ************************************************************************************/
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel);
#endif

#if (GPT_TIME_REMAINING_API == STD_ON)
/************************************************************************************
 * Service Name: Gpt_GetTimeRemaining
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Channel - Numeric identifier of the GPT channel
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Gpt_ValueType - Remaining timer value (in number of ticks)
 * Description: Function to Return the time remaining until the target time is reached.
 ************************************************************************************/
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel);
#endif

/************************************************************************************
 * Service Name: Gpt_StartTimer
 * Service ID[hex]: 0x05
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Channel - Numeric identifier of the GPT channel
 *                  Value - Target time in number of ticks.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Start a timer channel.
 ************************************************************************************/
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value);

/************************************************************************************
 * Service Name: Gpt_StopTimer
 * Service ID[hex]: 0x06
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Channel - Numeric identifier of the GPT channel
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Stop a timer channel.
 ************************************************************************************/
void Gpt_StopTimer(Gpt_ChannelType Channel);

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/************************************************************************************
 * Service Name: Gpt_EnableNotification
 * Service ID[hex]: 0x07
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Channel - Numeric identifier of the GPT channel
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Enable the interrupt notification for a channel (relevant in normal mode).
 ************************************************************************************/
void Gpt_EnableNotification(Gpt_ChannelType Channel);

/************************************************************************************
 * Service Name: Gpt_DisableNotification
 * Service ID[hex]: 0x08
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Channel - Numeric identifier of the GPT channel
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Disable the interrupt notification for a channel (relevant in normal mode).
 ************************************************************************************/
void Gpt_DisableNotification(Gpt_ChannelType Channel);
#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/************************************************************************************
 * Service Name: Gpt_SetMode
 * Service ID[hex]: 0x09
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Mode - GPT_MODE_NORMAL: Normal operation mode of the GPT driver.
 *                       - GPT_MODE_SLEEP: Sleep mode of the GPT driver (wakeup capable).
 *                       - See also Gpt_ModeType.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Set the operation mode of the GPT.
 ************************************************************************************/
void Gpt_SetMode(Gpt_ModeType Mode);

/************************************************************************************
 * Service Name: Gpt_DisableWakeup
 * Service ID[hex]: 0x0A
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Channel - Numeric identifier of the GPT channel.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Disable the wakeup interrupt of a channel (relevant in sleep mode).
 ************************************************************************************/
void Gpt_DisableWakeup(Gpt_ChannelType Channel);

/************************************************************************************
 * Service Name: Gpt_EnableWakeup
 * Service ID[hex]: 0x0B
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Channel - Numeric identifier of the GPT channel.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Enable the wakeup interrupt of a channel (relevant in sleep mode).
 ************************************************************************************/
void Gpt_EnableWakeup(Gpt_ChannelType Channel);

/************************************************************************************
 * Service Name: Gpt_CheckWakeup
 * Service ID[hex]: 0x0C
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): WakeupSource - Information on wakeup source to be checked. The associated
 *                                 GPT channel can be determined from configuration data
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Checks if a wakeup capable GPT channel is the source for a wakeup event and
 *              calls the ECU state manager service EcuM_SetWakeupEvent in case of a valid
 *              GPT channel wakeup event.
 ************************************************************************************/
void Gpt_CheckWakeup(EcuM_WakeupSourceType WakeupSource);

#endif

#endif /* GPT_H_ */
