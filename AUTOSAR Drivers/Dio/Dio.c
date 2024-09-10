/*
 ============================================================================
 Name        : Dio.c
 Module Name : Dio
 Author      : Ahmed Ali
 Date        : 7 Aug. 2024
 Description : Source file for TM4C123GH6PM Microcontroller - Dio Driver
 ============================================================================
 */

#include "Dio_Private.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Dio_ConfigChannel *Dio_PortChannels = NULL_PTR;
STATIC uint8 Dio_Status = DIO_NOT_INITIALIZED;

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
void Dio_Init(const Dio_ConfigType *ConfigPtr)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if the input configuration pointer is a NULL_PTR.
     * If it is, report an error and do not proceed further.
     */
    if (NULL_PTR == ConfigPtr)
    {
        /* Report the error: Null pointer passed as configuration */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_INIT_SID, DIO_E_PARAM_CONFIG);
    }
    else
#endif
    {
        /*
         * Set the DIO module state to initialized.
         * Store the provided configuration pointer in a global pointer to access it throughout the DIO module.
         * The global pointer Dio_PortChannels points to the first channel configuration structure (Channels[0]).
         */
        Dio_Status = DIO_INITIALIZED;
        Dio_PortChannels = ConfigPtr->Channels; /* Point to the first channel configuration structure */
    }
}/* Function End */

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
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    volatile uint32 *Port_Ptr = NULL_PTR; /* Pointer to the data register of the corresponding port */
    boolean error = FALSE; /* Error flag */

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if the DIO driver is initialized before performing operations */
    if (DIO_NOT_INITIALIZED == Dio_Status)
    {
        /* Report an error if the DIO driver is not initialized */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_SID, DIO_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* DIO driver is initialized */
    }

    /* Validate that the channel ID is within the valid range of configured channels */
    if (DIO_CONFIGURED_CHANNLES <= ChannelId)
    {
        /* Report an error for invalid channel ID */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
        error = TRUE;
    }
    else
    {
        /* Channel ID is valid */
    }
#endif

    /* Proceed with writing to the channel only if there are no errors */
    if (FALSE == error)
    {
        /* Determine the correct PORT register based on the Port_Num associated with the channel */
        switch (Dio_PortChannels[ChannelId].Port_Num)
        {
        case 0:
            Port_Ptr = &GPIO_PORTA_DATA_REG;
            break;
        case 1:
            Port_Ptr = &GPIO_PORTB_DATA_REG;
            break;
        case 2:
            Port_Ptr = &GPIO_PORTC_DATA_REG;
            break;
        case 3:
            Port_Ptr = &GPIO_PORTD_DATA_REG;
            break;
        case 4:
            Port_Ptr = &GPIO_PORTE_DATA_REG;
            break;
        case 5:
            Port_Ptr = &GPIO_PORTF_DATA_REG;
            break;
        default:
            /* Invalid port number, handle accordingly if needed */
            break;
        }

        /* Write the specified logic level (high or low) to the appropriate channel */
        if (Level == STD_HIGH)
        {
            /* Set the specified pin to logic high */
            SET_BIT(*Port_Ptr, Dio_PortChannels[ChannelId].Ch_Num);
        }
        else if (Level == STD_LOW)
        {
            /* Set the specified pin to logic low */
            CLEAR_BIT(*Port_Ptr, Dio_PortChannels[ChannelId].Ch_Num);
        }
    }
    else
    {
        /* Errors have been handled, no further action needed */
    }
} /* Function End */

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
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    volatile uint32 *Port_Ptr = NULL_PTR; /* Pointer to the data register of the corresponding port */
    Dio_LevelType Return_Value = STD_LOW; /* Default return value is set to STD_LOW */
    boolean error = FALSE; /* Error flag */

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if the DIO driver is initialized before performing operations */
    if (DIO_NOT_INITIALIZED == Dio_Status)
    {
        /* Report an error if the DIO driver is not initialized */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_SID, DIO_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* DIO driver is initialized */
    }

    /* Validate that the channel ID is within the valid range of configured channels */
    if (DIO_CONFIGURED_CHANNLES <= ChannelId)
    {
        /* Report an error for invalid channel ID */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
        error = TRUE;
    }
    else
    {
        /* Channel ID is valid */
    }
#endif

    /* Proceed with reading from the channel only if there are no errors */
    if (FALSE == error)
    {
        /* Determine the correct PORT register based on the Port_Num associated with the channel */
        switch (Dio_PortChannels[ChannelId].Port_Num)
        {
        case 0:
            Port_Ptr = &GPIO_PORTA_DATA_REG;
            break;
        case 1:
            Port_Ptr = &GPIO_PORTB_DATA_REG;
            break;
        case 2:
            Port_Ptr = &GPIO_PORTC_DATA_REG;
            break;
        case 3:
            Port_Ptr = &GPIO_PORTD_DATA_REG;
            break;
        case 4:
            Port_Ptr = &GPIO_PORTE_DATA_REG;
            break;
        case 5:
            Port_Ptr = &GPIO_PORTF_DATA_REG;
            break;
        default:
            /* Invalid port number, handle accordingly if needed */
            break;
        }

        /* Read the pin level (high or low) from the appropriate port and channel */
        Return_Value = GET_BIT(*Port_Ptr, Dio_PortChannels[ChannelId].Ch_Num);
    }
    else
    {
        /* Error handling has been managed; no further action required */
    }

    /* Return the level read from the specified channel */
    return Return_Value;
} /* Function End */

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
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr)
{
    volatile uint32 *Port_Ptr = NULL_PTR; /* Pointer to the data register of the corresponding port */
    Dio_PortLevelType Return_Value = 0; /* Default return value */
    boolean error = FALSE; /* Error flag */

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if the DIO driver is initialized before performing operations */
    if (DIO_NOT_INITIALIZED == Dio_Status)
    {
        /* Report an error if the DIO driver is not initialized */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_SID, DIO_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* DIO driver is initialized */
    }

    /* Check if the input pointer to the channel group is not NULL */
    if (NULL_PTR == ChannelGroupIdPtr)
    {
        /* Report an error for null pointer */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_POINTER);
        error = TRUE;
    }
    else
    {
        /* Valid channel group pointer */
    }

    /* Validate the group port index to ensure it's within the configured range */
    if (DIO_CONFIGURED_GROUPS <= (ChannelGroupIdPtr->PortIndex))
    {
        /* Report an error for an invalid group port index */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
        error = TRUE;
    }
    else
    {
        /* Group port index is valid */
    }
#endif

    /* Proceed with reading the group channel only if there are no errors */
    if (FALSE == error)
    {
        /* Determine the correct PORT register based on the group PortIndex */
        switch (Dio_PortChannels[ChannelGroupIdPtr->PortIndex].Port_Num)
        {
        case 0:
            Port_Ptr = &GPIO_PORTA_DATA_REG;
            break;
        case 1:
            Port_Ptr = &GPIO_PORTB_DATA_REG;
            break;
        case 2:
            Port_Ptr = &GPIO_PORTC_DATA_REG;
            break;
        case 3:
            Port_Ptr = &GPIO_PORTD_DATA_REG;
            break;
        case 4:
            Port_Ptr = &GPIO_PORTE_DATA_REG;
            break;
        case 5:
            Port_Ptr = &GPIO_PORTF_DATA_REG;
            break;
        default:
            /* Invalid port number, handle accordingly if needed */
            break;
        }

        /* Extract the specific group level based on the mask and offset provided */
        Return_Value = ((*Port_Ptr) & (ChannelGroupIdPtr->mask)) >> (ChannelGroupIdPtr->offset);
    }
    else
    {
        /* Error handling has been managed; no further action required */
    }

    /* Return the value read from the group of channels */
    return Return_Value;
} /* Function End */

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
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level)
{
    volatile uint32 *Port_Ptr = NULL_PTR; /* Pointer to the data register of the corresponding port */
    boolean error = FALSE; /* Error flag */

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if the DIO driver is initialized before performing operations */
    if (DIO_NOT_INITIALIZED == Dio_Status)
    {
        /* Report an error if the DIO driver is not initialized */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_UNINIT);
        error = TRUE;
    }

    /* Check if the input pointer to the channel group is not NULL */
    if (NULL_PTR == ChannelGroupIdPtr)
    {
        /* Report an error for null pointer */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_POINTER);
        error = TRUE;
    }

    /* Validate the group port index to ensure it's within the configured range */
    if (DIO_CONFIGURED_GROUPS <= (ChannelGroupIdPtr->PortIndex))
    {
        /* Report an error for an invalid group port index */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
        error = TRUE;
    }
#endif

    /* Proceed with writing to the group channel only if there are no errors */
    if (FALSE == error)
    {
        /* Determine the correct PORT register based on the group PortIndex */
        switch (Dio_PortChannels[ChannelGroupIdPtr->PortIndex].Port_Num)
        {
        case 0:
            Port_Ptr = &GPIO_PORTA_DATA_REG;
            break;
        case 1:
            Port_Ptr = &GPIO_PORTB_DATA_REG;
            break;
        case 2:
            Port_Ptr = &GPIO_PORTC_DATA_REG;
            break;
        case 3:
            Port_Ptr = &GPIO_PORTD_DATA_REG;
            break;
        case 4:
            Port_Ptr = &GPIO_PORTE_DATA_REG;
            break;
        case 5:
            Port_Ptr = &GPIO_PORTF_DATA_REG;
            break;
        default:
            /* Invalid port number, handle accordingly if needed */
            break;
        }

        /* Update the group level in the data register for the specific port */
        /* Clear the bits in the mask region, then insert the new level by shifting it to the correct offset */
        *Port_Ptr = ((*Port_Ptr) & (~(ChannelGroupIdPtr->mask))) | ((Level << ChannelGroupIdPtr->offset) & ChannelGroupIdPtr->mask);
    }
    else
    {
        /* Error handling has been managed; no further action required */
    }
} /* Function End */

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
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if the input pointer is not a NULL pointer */
    if (NULL_PTR == versioninfo)
    {
        /* Report an error to DET if the pointer is NULL */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
    }
    else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Populate the Std_VersionInfoType structure with version information */

        /* Copy the Vendor ID */
        versioninfo->vendorID = (uint16)DIO_VENDOR_ID;

        /* Copy the Module ID */
        versioninfo->moduleID = (uint16)DIO_MODULE_ID;

        /* Copy the Software Major Version */
        versioninfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;

        /* Copy the Software Minor Version */
        versioninfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;

        /* Copy the Software Patch Version */
        versioninfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
    }
} /* Function End */
#endif

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
#if (DIO_FLIP_CHANNEL_API == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    volatile uint32 *Port_Ptr = NULL_PTR; /* Pointer to the data register of the corresponding port */
    Dio_LevelType Return_Value = STD_LOW; /* Default return value */
    boolean error = FALSE; /* Error flag */

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (DIO_NOT_INITIALIZED == Dio_Status)
    {
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_FLIP_CHANNEL_SID, DIO_E_UNINIT);
        error = TRUE;
    }

    /* Check if the channel ID is within the valid range */
    if (DIO_CONFIGURED_CHANNLES <= ChannelId)
    {
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_FLIP_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
        error = TRUE;
    }
#endif

    /* If no errors occurred */
    if (FALSE == error)
    {
        /* Point to the correct PORT register according to the Port_Num member */
        switch (Dio_PortChannels[ChannelId].Port_Num)
        {
        case 0:
            Port_Ptr = &GPIO_PORTA_DATA_REG;
            break;
        case 1:
            Port_Ptr = &GPIO_PORTB_DATA_REG;
            break;
        case 2:
            Port_Ptr = &GPIO_PORTC_DATA_REG;
            break;
        case 3:
            Port_Ptr = &GPIO_PORTD_DATA_REG;
            break;
        case 4:
            Port_Ptr = &GPIO_PORTE_DATA_REG;
            break;
        case 5:
            Port_Ptr = &GPIO_PORTF_DATA_REG;
            break;
        }

        /* Toggle the logic level of the selected channel */
        TOGGLE_BIT(*Port_Ptr, Dio_PortChannels[ChannelId].Ch_Num);

        /* Return the new level of the channel after toggling */
        Return_Value = GET_BIT(*Port_Ptr, Dio_PortChannels[ChannelId].Ch_Num);
    }
    else
    {
        /* Error handling has been managed; no further action required */
    }
    return Return_Value;
}
#endif
