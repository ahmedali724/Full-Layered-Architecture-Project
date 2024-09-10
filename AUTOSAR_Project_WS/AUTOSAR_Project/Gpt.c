/*
 ============================================================================
 Name        : Gpt.c
 Module Name : Gpt
 Author      : Ahmed Ali
 Date        : 15 Aug. 2024
 Description : Source file for TM4C123GH6PM Microcontroller - Gpt Driver
 ============================================================================
 */

#include "Gpt_Private.h"

#if (GPT_DEV_ERROR_DETECT ==  STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Gpt Modules */
#if ((DET_AR_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Gpt.h does not match the expected version"

#endif
#endif

/* Pointer to hold the first address of the array of structure */
STATIC const Gpt_ConfigChannelType *Gpt_Channels = NULL_PTR;

/* Variable to hold the state of module for Det error checking */
STATIC uint8 Gpt_Status = GPT_NOT_INITIALIZED;

/* Array of structure to hold the state of each Gpt channel */
STATIC Gpt_TimerChannelStates Gpt_ChannelsState[GPT_CONFIGURED_CHANNELS];

/* Global array to hold the address of each gpt call back function in the application */
volatile void (*Gpt_NotificationArr[GPT_CONFIGURED_CHANNELS])(void) =
{   NULL_PTR };

/* global variables to hold the target time in milliseconds and another to count the time */
volatile uint16 SysTick_TargetTime = 0;
volatile uint16 SysTick_CountedTime = 0;

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
void Gpt_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr)
{
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer, if not report an error and do not proceed further */
    if (NULL_PTR == VersionInfoPtr)
    {
        /* Report to DET  */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_VERSION_INFO_API, GPT_E_PARAM_POINTER);
    }
    else
#endif /* (GPT_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        VersionInfoPtr->vendorID = (uint16) GPT_VENDOR_ID;
        /* Copy the module Id */
        VersionInfoPtr->moduleID = (uint16) GPT_MODULE_ID;
        /* Copy Software Major Version */
        VersionInfoPtr->sw_major_version = (uint8) GPT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        VersionInfoPtr->sw_minor_version = (uint8) GPT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        VersionInfoPtr->sw_patch_version = (uint8) GPT_SW_PATCH_VERSION;
    }
}/* Function end: Successfully copied the version information (if the pointer was valid) and returned it to the caller */
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
void Gpt_Init(const Gpt_ConfigType *ConfigPtr)
{
    boolean error = FALSE;
    Gpt_ChannelType index;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Validate the input configuration pointer. If NULL, report a development error and exit the function. */
    if (NULL_PTR == ConfigPtr)
    {
        /* DET Report: Report the error for NULL configuration pointer */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_PARAM_POINTER);
        error = TRUE;
    }
    else
    {
        /* Configuration pointer is valid */
    }

    /* Check if the GPT driver is already initialized. If so, report an error and exit the function. */
    if (GPT_INITIALIZED == Gpt_Status)
    {
        /* DET Report: Report the error for attempting to initialize an already initialized module */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_ALREADY_INITIALIZED);
        error = TRUE;
    }
    else
    {
        /* GPT driver is not yet initialized */
    }
#endif

    if (FALSE == error)
    {
        /*
         * Update the module state to initialized and set the global pointer to the configuration structure.
         * This pointer will be used by other functions to access the configuration data.
         */
        Gpt_Status = GPT_INITIALIZED;
        Gpt_Channels = ConfigPtr->Channels; /* Set the pointer to the array of GPT channels */

        /* Initialize each configured GPT channel */
        for (index = 0; index < GPT_CONFIGURED_CHANNELS; ++index)
        {
            /* Store the call back function address in the array */
            Gpt_NotificationArr[index] = Gpt_Channels[index].Gpt_Notification;
            switch (Gpt_Channels[index].Channel_ID)
            {
            case GPT_SYSTICK_ID :
                /* Configure the SysTick timer for the specified channel */

                /* Disable SysTick timer to prepare for configuration */
                SYSTICK_CTRL_REG = 0;

                /* Set the reload value for the timer */
                SYSTICK_RELOAD_REG = Gpt_Channels[index].Channel_Value;

                /* Clear the current value register */
                SYSTICK_CURRENT_REG = 0;

                /* Configure the clock source for the SysTick timer */
                if (Gpt_Channels[index].Gpt_ClkRef == GPT_SYSTEM_CLOCK)
                {
                    /* Set the clock source to the system clock */
                    SYSTICK_CTRL_REG |= SYSTICK_STCTRL_ENABLE_MASK;
                }
                else
                {
                    /* Additional clock sources can be configured here if needed */
                }

                /* Disable SysTick interrupt */
                SYSTICK_CTRL_REG &= ~SYSTICK_STCTRL_INTEN_MASK;

                /* Finally, disable the SysTick timer */
                SYSTICK_CTRL_REG &= ~SYSTICK_STCTRL_ENABLE_MASK;
                break;

                /* Additional GPT modules can be configured here in the future */
            }
            /* Change the state of the current channel to initialized */
            Gpt_ChannelsState[index].Channel_State = GPT_CHANNEL_INITIALIZED;
        } /* End of channel initialization loop */
    }
    else
    {
        /* Error detected during initialization, no further action */
    }
} /* End of Gpt_Init function */

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
void Gpt_DeInit(void)
{
    boolean error = FALSE;
    Gpt_ChannelType index;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Validate that the GPT driver is currently initialized. If not, report an error and exit the function. */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* DET Report: Report the error for attempting to deinitialize an already uninitialized module */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DE_INIT_SID, GPT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* GPT driver is initialized and can be deinitialized */
    }
    for (index = 0; index < GPT_CONFIGURED_CHANNELS; ++index)
    {
        /* Check for each channel if the current state is running, then report an error */
        if (GPT_CHANNEL_RUNNING == Gpt_ChannelsState[index].Channel_State)
        {
            /* DET Report: Report the error for attempting to deinitialize an already running module */
            Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DE_INIT_SID, GPT_E_BUSY);
            error = TRUE;
        }
        else
        {
            /* Gpt driver is not in running mode */
        }
    }
#endif

    if (FALSE == error)
    {
        /* Update the module state to uninitialized */
        Gpt_Status = GPT_NOT_INITIALIZED;

        /* De-initialize each configured GPT channel */
        for (index = 0; index < GPT_CONFIGURED_CHANNELS; ++index)
        {
            /* Clear the callback function pointer for the current channel */
            Gpt_NotificationArr[index] = NULL_PTR;

            switch (Gpt_Channels[index].Channel_ID)
            {
            case GPT_SYSTICK_ID :
                /* Disable SysTick timer and clear configuration */

                /* Disable the SysTick timer to prepare for deinitialization */
                SYSTICK_CTRL_REG = 0;

                /* Clear the reload value for the timer */
                SYSTICK_RELOAD_REG = 0;

                /* Clear the current value register */
                SYSTICK_CURRENT_REG = 0;

                /* Disable SysTick interrupt */
                SYSTICK_CTRL_REG &= ~SYSTICK_STCTRL_INTEN_MASK;

                /* Clear the clock source selection (if applicable) */
                if (Gpt_Channels[index].Gpt_ClkRef == GPT_SYSTEM_CLOCK)
                {
                    /* Ensure clock source is cleared */
                    SYSTICK_CTRL_REG &= ~SYSTICK_STCTRL_ENABLE_MASK;
                }
                else
                {
                    /* Additional clock sources can be deconfigured here if needed */
                }

                /* Ensure the SysTick timer is fully disabled */
                SYSTICK_CTRL_REG &= ~SYSTICK_STCTRL_ENABLE_MASK;
                break;

                /* Additional GPT modules can be deinitialized here in the future */
            }
            /* Change the state of the channel to uninitialized */
            Gpt_ChannelsState[index].Channel_State = GPT_CHANNEL_UNINITIALIZED;
        } /* End of channel deinitialization loop */
    }
    else
    {
        /* No action required as an error has occurred during validation */
    }
} /* End of Gpt_DeInit function */

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
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)
{
    Gpt_ValueType TimeElapsed = 0;
    boolean error = FALSE;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the GPT driver is initialized. If not, report an error and exit the function. */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* DET Report: GPT driver is not initialized */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_TIME_ELAPSED_SID, GPT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* GPT driver is initialized */
    }

    /* Validate that the provided channel is within the valid range */
    if (Channel >= GPT_CONFIGURED_CHANNELS)
    {
        /* DET Report: Invalid channel ID provided */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_TIME_ELAPSED_SID, GPT_E_PARAM_CHANNEL);
        error = TRUE;
    }
    else
    {
        /* Channel ID is valid */
    }
#endif

    if (FALSE == error)
    {
        /* If the function Gpt_GetTimeElapsed is called on a channel configured
         for "ONE_SHOT mode" in state "EXPIRED" (timer has reached the target time),
         the function shall return the target time. */
        if (Gpt_Channels[Channel].Channel_Mode == GPT_CH_MODE_ONESHOT && Gpt_ChannelsState[Channel].Channel_State == GPT_CHANNEL_EXPIRED)
        {
            /* Set time elapsed to the target time */
            TimeElapsed = SYSTICK_RELOAD_REG;
        }
        else
        {
            /* Check which channel is being requested and retrieve the elapsed time accordingly */
            switch (Gpt_Channels[Channel].Channel_ID)
            {
            case GPT_SYSTICK_ID :
                /* Retrieve the elapsed time from the SysTick current value register */
                TimeElapsed = SYSTICK_CURRENT_REG;
                break;

                /* Additional GPT channels can be handled here in the future */
            }
        }
    }
    else
    {
        /* Error handling has already been managed; no further action required */
    }
    /* Return the elapsed time */
    return TimeElapsed;
} /* End of Gpt_GetTimeElapsed function */

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
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel)
{
    Gpt_ValueType TimeRemaining = 0;
    boolean error = FALSE;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the GPT driver is initialized. If not, report an error and exit the function. */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* DET Report: GPT driver is not initialized */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_TIME_REMAINING_SID, GPT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* GPT driver is initialized */
    }

    /* Validate that the provided channel is within the valid range */
    if (Channel >= GPT_CONFIGURED_CHANNELS)
    {
        /* DET Report: Invalid channel ID provided */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_TIME_REMAINING_SID, GPT_E_PARAM_CHANNEL);
        error = TRUE;
    }
    else
    {
        /* Channel ID is valid */
    }
#endif

    if (FALSE == error)
    {
        /* If the function Gpt_GetTimeRemaining is called on a channel
         configured for "ONE_SHOT" mode in state "EXPIRED" (timer has reached the target time),
         the function shall return the value "0" */
        if (Gpt_Channels[Channel].Channel_Mode == GPT_CH_MODE_ONESHOT && Gpt_ChannelsState[Channel].Channel_State == GPT_CHANNEL_EXPIRED)
        {
            /* Set time elapsed to the target time */
            TimeRemaining = 0;
        }
        else
        {
            /* Check which channel is being requested and retrieve the remaining time accordingly */
            switch (Gpt_Channels[Channel].Channel_ID)
            {
            case GPT_SYSTICK_ID :
                /* Calculate the remaining time by subtracting the current value from the reload value */
                TimeRemaining = SYSTICK_RELOAD_REG - SYSTICK_CURRENT_REG;
                break;

                /* Additional GPT channels can be handled here in the future */
            }
        }
    }
    else
    {
        /* Error handling has already been managed; no further action required */
    }

    /* Return the remaining time */
    return TimeRemaining;
} /* End of Gpt_GetTimeRemaining function */

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
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)
{
    boolean error = FALSE;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the GPT driver is initialized. If not, report an error and exit the function. */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* DET Report: GPT driver is not initialized */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* GPT driver is initialized */
    }

    /* Validate that the provided channel is within the valid range */
    if (Channel >= GPT_CONFIGURED_CHANNELS)
    {
        /* DET Report: Invalid channel ID provided */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_PARAM_CHANNEL);
        error = TRUE;
    }
    else
    {
        /* Channel ID is valid */
    }

    /* Validate that the provided timer value is greater than zero */
    if (Value <= 0)
    {
        /* DET Report: Invalid timer value provided */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_PARAM_VALUE);
        error = TRUE;
    }
    else
    {
        /* Timer value is valid */
    }
    /* Check for each channel if the current state is running, then report an error */
    if (GPT_CHANNEL_RUNNING == Gpt_ChannelsState[Channel].Channel_State)
    {
        /* DET Report: Report the error for attempting to start an already running module */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_BUSY);
        error = TRUE;
    }
    else
    {
        /* Gpt driver is not in running mode */
    }
#endif

    if (FALSE == error)
    {
        switch (Gpt_Channels[Channel].Channel_ID)
        {
        case GPT_SYSTICK_ID :
            /* Start the SysTick timer for the specified channel */

            /* Clear the current value register */
            SYSTICK_CURRENT_REG = 0;

            /* Set the target time */
            SysTick_TargetTime = Value;

            /* Clear the counted time */
            SysTick_CountedTime = 0;

            /* Enable SysTick interrupt */
            SYSTICK_CTRL_REG |= SYSTICK_STCTRL_INTEN_MASK;

            /* Finally, Enable the SysTick timer */
            SYSTICK_CTRL_REG |= SYSTICK_STCTRL_ENABLE_MASK;
            break;

            /* Additional GPT modules can be configured here in the future */
        }
        /* Change the current state of the channel to running state */
        Gpt_ChannelsState[Channel].Channel_State = GPT_CHANNEL_RUNNING;
    }
    else
    {
        /* Error handling has already been managed; no further action required */
    }
} /* Function End */

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
void Gpt_StopTimer(Gpt_ChannelType Channel)
{
    boolean error = FALSE;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the GPT driver is initialized. If not, report an error and exit the function. */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* DET Report: GPT driver is not initialized */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_STOP_TIMER_SID, GPT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* GPT driver is initialized */
    }

    /* Validate that the provided channel is within the valid range */
    if (Channel >= GPT_CONFIGURED_CHANNELS)
    {
        /* DET Report: Invalid channel ID provided */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_STOP_TIMER_SID, GPT_E_PARAM_CHANNEL);
        error = TRUE;
    }
    else
    {
        /* Channel ID is valid */
    }
#endif

    if (FALSE == error)
    {
        /* If the function Gpt_StopTimer is called on a channel in state
         "INITIALIZED", "STOPPED" or "EXPIRED", the function shall leave without any action (no
         change of the channel state). */
        if (Gpt_ChannelsState[Channel].Channel_State == GPT_CHANNEL_INITIALIZED || Gpt_ChannelsState[Channel].Channel_State == GPT_CHANNEL_STOPPED || Gpt_ChannelsState[Channel].Channel_State == GPT_CHANNEL_EXPIRED)
        {
            return;
        }
        else
        {
            switch (Gpt_Channels[Channel].Channel_ID)
            {
            case GPT_SYSTICK_ID :
                /* Stop the SysTick timer for the specified channel */

                /* Disable the SysTick timer by clearing the enable bit */
                SYSTICK_CTRL_REG &= ~SYSTICK_STCTRL_ENABLE_MASK;
                break;

                /* Additional GPT modules can be configured here in the future */
            }
        }
    }
    else
    {
        /* Error handling has already been managed; no further action required */
    }
} /* Function End */

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
void Gpt_EnableNotification(Gpt_ChannelType Channel)
{
    boolean error = FALSE;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the GPT driver is initialized. If not, report an error and exit the function. */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* DET Report: GPT driver is not initialized */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_SID, GPT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* GPT driver is initialized */
    }

    /* Validate that the provided channel is within the valid range */
    if (Channel >= GPT_CONFIGURED_CHANNELS)
    {
        /* DET Report: Invalid channel ID provided */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_SID, GPT_E_PARAM_CHANNEL);
        error = TRUE;
    }
    else
    {
        /* Channel ID is valid */
    }
    /* If no valid notification function is configured (Gpt_callBackPtrArr) */
    if (Gpt_NotificationArr[Channel] == NULL_PTR)
    {
        /* DET Report: Invalid notification function provided */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_SID, GPT_E_PARAM_CHANNEL);
        error = TRUE;
    }
    else
    {
        /* The notification function is configured */
    }
#endif

    if (FALSE == error)
    {
        switch (Gpt_Channels[Channel].Channel_ID)
        {
        case GPT_SYSTICK_ID :
            /* Enable the SysTick timer interrupt for the specified channel */

            /* Set the SysTick control register to enable the interrupt */
            SYSTICK_CTRL_REG |= SYSTICK_STCTRL_INTEN_MASK;
            break;

            /* Additional GPT modules can be configured here in the future */
        }
    }
    else
    {
        /* Error handling has already been managed; no further action required */
    }
} /* Function End */

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
void Gpt_DisableNotification(Gpt_ChannelType Channel)
{
    boolean error = FALSE;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the GPT driver is initialized. If not, report an error and exit the function. */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* DET Report: GPT driver is not initialized */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DISABLE_NOTIFICATION_SID, GPT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* GPT driver is initialized */
    }

    /* Validate that the provided channel is within the valid range */
    if (Channel >= GPT_CONFIGURED_CHANNELS)
    {
        /* DET Report: Invalid channel ID provided */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DISABLE_NOTIFICATION_SID, GPT_E_PARAM_CHANNEL);
        error = TRUE;
    }
    else
    {
        /* Channel ID is valid */
    }
    /* If no valid notification function is configured (Gpt_callBackPtrArr) */
    if (Gpt_NotificationArr[Channel] == NULL_PTR)
    {
        /* DET Report: Invalid notification function provided */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DISABLE_NOTIFICATION_SID, GPT_E_PARAM_CHANNEL);
        error = TRUE;
    }
    else
    {
        /* The notification function is configured */
    }
#endif

    if (FALSE == error)
    {
        switch (Gpt_Channels[Channel].Channel_ID)
        {
        case GPT_SYSTICK_ID :
            /* Disable the SysTick timer interrupt for the specified channel */

            /* Clear the SysTick control register to disable the interrupt */
            SYSTICK_CTRL_REG &= ~SYSTICK_STCTRL_INTEN_MASK;
            break;

            /* Additional GPT modules can be configured here in the future */
        }
    }
    else
    {
        /* Error handling has already been managed; no further action required */
    }
} /* Function End */
#endif
