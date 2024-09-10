/*
 ============================================================================
 Name        : Port.h
 Module Name : Port
 Author      : Ahmed Ali
 Date        : 12 Aug. 2024
 Description : Header file for TM4C123GH6PM Microcontroller - Port Driver
 ============================================================================
 */

#ifndef PORT_H_
#define PORT_H_

#define PORT_VENDOR_ID    (2002U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION               (1U)
#define PORT_SW_MINOR_VERSION               (0U)
#define PORT_SW_PATCH_VERSION               (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION       (4U)
#define PORT_AR_RELEASE_MINOR_VERSION       (0U)
#define PORT_AR_RELEASE_PATCH_VERSION       (3U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Port Types Header file */
#include "Port_Types.h"

/* AUTOSAR Version checking between Port_Types.h and Port.h files */
#if ((PORT_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Types.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_TYPES_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_TYPES_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_TYPES_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_Types.h does not match the expected version"
#endif

/* Port Post Build Configuration Header file */
#include "Port_PBcfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_PBcfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_PBcfg.h does not match the expected version"
#endif

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port_Init API
 * Used to identify the Port_Init service when reporting errors to DET */
#define PORT_INIT_SID                       (uint8)0x00

/* Service ID for Port_SetPinDirection API
 * Used to identify the Port_SetPinDirection service when reporting errors to DET */
#define PORT_SET_PIN_DIRECTION_SID          (uint8)0x01

/* Service ID for Port_RefreshPortDirection API
 * Used to identify the Port_RefreshPortDirection service when reporting errors to DET */
#define PORT_REFRESH_PORT_DIRECTION_SID     (uint8)0x02

/* Service ID for Port_GetVersionInfo API
 * Used to identify the Port_GetVersionInfo service when reporting errors to DET */
#define PORT_GET_VERSION_INFO_SID           (uint8)0x03

/* Service ID for Port_SetPinMode API
 * Used to identify the Port_SetPinMode service when reporting errors to DET */
#define PORT_SET_PIN_MODE_SID               (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code for reporting an Invalid Port Pin ID
 * This error is reported when an invalid or undefined Pin ID is requested in an API call */
#define PORT_E_PARAM_PIN                    (uint8)0x0A

/* DET code for reporting an attempt to change the direction of a Pin 
 * that is configured as non-changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE       (uint8)0x0B

/* DET code for reporting that the Port_Init service was called with 
 * an invalid or incorrect configuration parameter */
#define PORT_E_PARAM_CONFIG                 (uint8)0x0C

/* DET code for reporting an Invalid Mode selection for a Pin
 * This error is reported when an unsupported or invalid mode is selected for a Pin */
#define PORT_E_PARAM_INVALID_MODE           (uint8)0x0D

/* DET code for reporting an attempt to change the mode of a Pin 
 * that is configured as non-changeable */
#define PORT_E_MODE_UNCHANGEABLE            (uint8)0x0E

/* DET code for reporting that an API service was called without 
 * the Port module being initialized */
#define PORT_E_UNINIT                       (uint8)0x0F

/* DET code for reporting that a Null Pointer was passed as a parameter to an API */
#define PORT_E_PARAM_POINTER                (uint8)0x10

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
 * Service Name: Port_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): ConfigPtr - Pointer to configuration set.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Initialize the Port Driver module.
 ************************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin - Port Pin ID number.
 *                  Direction - Port Pin Direction.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Set the port pin direction.
 ************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Refresh port direction.
 ************************************************************************************/
void Port_RefreshPortDirection(void);

#if (PORT_VERSION_INFO_API == STD_ON)
/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): versioninfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to Return the version information of this module.
 ************************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin - Port Pin ID number.
 *                  Mode - New Port Pin mode to be set on port pin.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Set the port pin mode.
 ************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif

#endif /* PORT_H_ */
