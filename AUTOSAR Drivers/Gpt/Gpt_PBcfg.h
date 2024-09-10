/*
 ============================================================================
 Name        : Gpt_PBcfg.h
 Module Name : Gpt
 Author      : Ahmed Ali
 Date        : 15 Aug. 2024
 Description : Post Build Configuration Header file for TM4C123GH6PM Microcontroller - Gpt Driver
 ============================================================================
 */

#ifndef GPT_PBCFG_H_
#define GPT_PBCFG_H_

/*
 * Module Version 1.0.0
 */
#define GPT_PBCFG_SW_MAJOR_VERSION                 (1U)
#define GPT_PBCFG_SW_MINOR_VERSION                 (0U)
#define GPT_PBCFG_SW_PATCH_VERSION                 (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_PBCFG_AR_RELEASE_MAJOR_VERSION         (4U)
#define GPT_PBCFG_AR_RELEASE_MINOR_VERSION         (0U)
#define GPT_PBCFG_AR_RELEASE_PATCH_VERSION         (3U)

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Enumeration specifying the behavior of the timer channel after the target time is reached. */
typedef enum
{
    /* The timer continues running in continuous mode, resetting to zero after reaching the target time. */
    GPT_CH_MODE_CONTINUOUS,

    /* The timer stops automatically after reaching the target time, indicating the timer has expired. */
    GPT_CH_MODE_ONESHOT
} Gpt_ChannelMode;

/* Enumeration for clock source references used by the timer channels. */
typedef enum
{
    /* The system clock is used as the reference clock source for the timer channels. */
    GPT_SYSTEM_CLOCK
} Gpt_ChannelClkSrcRef;

/* Enumeration specifying the state of the timer channel. */
typedef enum
{
    GPT_CHANNEL_UNINITIALIZED, /* The channel is uninitialized */
    GPT_CHANNEL_INITIALIZED, /* The channel is initialized */
    GPT_CHANNEL_RUNNING, /* The channel is running */
    GPT_CHANNEL_STOPPED, /* The channel is stopped */
    GPT_CHANNEL_EXPIRED /* The channel is expired */
} Gpt_ChannelState;

/* Structure holding the initialization parameters for the GPT module. */
typedef struct
{
    /* Numeric ID of the GPT channel. */
    Gpt_ChannelType Channel_ID;

    /* Number of ticks or value to be loaded into the timer channel. */
    Gpt_ValueType Channel_Value;

    /* Behavior of the timer channel after reaching the target time (continuous or oneshot). */
    Gpt_ChannelMode Channel_Mode;

    /* Mode selection for the GPT module. */
    Gpt_ModeType Gpt_Mode;

    /* Clock reference selection for the GPT module. */
    Gpt_ChannelClkSrcRef Gpt_ClkRef;

    /* Pointer to a callback function that will be invoked on timer expiration. */
    volatile void (*Gpt_Notification)(void);
} Gpt_ConfigChannelType;

/* Data structure containing the initialization data for the GPT module. */
typedef struct
{
    /* Array of GPT channel configurations. */
    Gpt_ConfigChannelType Channels[GPT_CONFIGURED_CHANNELS];
} Gpt_ConfigType;

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* External configuration structure used by the GPT module.
 * This structure is defined and initialized in Gpt_PBcfg.c and contains
 * the configuration settings for all GPT channels. */
extern const Gpt_ConfigType Gpt_Configuration;

#endif /* GPT_PBCFG_H_ */
