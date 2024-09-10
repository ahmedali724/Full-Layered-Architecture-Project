/*
 ============================================================================
 Name        : Gpt_Cfg.h
 Module Name : Gpt
 Author      : Ahmed Ali
 Date        : 15 Aug. 2024
 Description : Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Gpt Driver
 ============================================================================
 */

#ifndef GPT_CFG_H_
#define GPT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define GPT_CFG_SW_MAJOR_VERSION            (1U)
#define GPT_CFG_SW_MINOR_VERSION            (0U)
#define GPT_CFG_SW_PATCH_VERSION            (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_CFG_AR_RELEASE_MAJOR_VERSION    (4U)
#define GPT_CFG_AR_RELEASE_MINOR_VERSION    (0U)
#define GPT_CFG_AR_RELEASE_PATCH_VERSION    (3U)

/******************************************************************************
 *                      Pre-compile Configuration Options                     *
 ******************************************************************************/

/* Pre-compile option for enabling Development Error Detection.
 * If set to STD_ON, development errors are detected and reported. */
#define GPT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for reporting wake-up sources.
 * If set to STD_ON, the wake-up sources are reported to the ECU State Manager (EcuM). */
#define GPT_REPORT_WAKEUP_SOURCE            (STD_OFF)

/* Pre-compile option for enabling the Gpt_DeInit API.
 * If set to STD_ON, the Gpt_DeInit API is available to deinitialize the GPT driver. */
#define GPT_DEINIT_API                      (STD_ON)

/* Pre-compile option for enabling Gpt_EnableNotification and Gpt_DisableNotification APIs.
 * If set to STD_ON, these APIs can be used to enable or disable timer notifications. */
#define GPT_ENABLE_DISABLE_NOTIFICATION_API (STD_ON)

/* Pre-compile option for enabling the Gpt_GetTimeElapsed API.
 * If set to STD_ON, this API is available to retrieve the time elapsed since the timer started. */
#define GPT_TIME_ELAPSED_API                (STD_ON)

/* Pre-compile option for enabling the Gpt_GetTimeRemaining API.
 * If set to STD_ON, this API is available to retrieve the remaining time until the timer expires. */
#define GPT_TIME_REMAINING_API              (STD_ON)

/* Pre-compile option for enabling the Gpt_GetVersionInfo API.
 * If set to STD_ON, this API is available to retrieve version information for the GPT module. */
#define GPT_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for enabling wake-up functionality.
 * If set to STD_ON, APIs related to wake-up (Gpt_SetMode, Gpt_EnableWakeup, Gpt_DisableWakeup, Gpt_CheckWakeup) are available. */
#define GPT_WAKEUP_FUNCTIONALITY_API        (STD_OFF)

/* Pre-compile option for enabling wake-up capability for a specific channel.
 * If set to STD_ON, the channel can be used to wake up the MCU from a low-power mode. */
#define GPT_ENABLE_WAKEUP                   (STD_OFF)

/* Pre-compile option to select the clock reference for the GPT.
 * The clock reference can be either the system clock or an external clock. */
#define GPT_CLOCK_REFERENCE                 GPT_SYSTEM_CLOCK

/* The number of GPT channels that are configured in the system.
 * This value defines the size of the configuration array for the GPT module. */
#define GPT_CONFIGURED_CHANNELS             (1U)

/* Channel Index in the array of structures in the Gpt_PBcfg.c file.
 * This index corresponds to the SysTick channel configuration in the array. */
#define GptConf_SYSTICK_CHANNEL_ID_INDEX    (uint8)0x00

/* SysTick Timer ID.
 * This defines the unique ID assigned to the SysTick timer channel in the GPT driver.
 * It is used to identify the SysTick timer channel when configuring or controlling the timer.
 */
#define GPT_SYSTICK_ID                      (Gpt_ChannelType)0

/* SysTick Interrupt Priority.
 * This defines the priority level of the SysTick timer interrupt.
 * Lower values represent higher priorities. This value determines the handling priority of the SysTick interrupt compared to other interrupts.
 */
#define GPT_SYSTICK_INTERRUPT_PRIORITY      1

/* SysTick Timer Value.
 * This value represents the initial value of the SysTick timer for a 1ms tick with a 16MHz clock. */
#define GPT_SYSTICK_VALUE                   (Gpt_ValueType)15999

#endif /* GPT_CFG_H_ */
