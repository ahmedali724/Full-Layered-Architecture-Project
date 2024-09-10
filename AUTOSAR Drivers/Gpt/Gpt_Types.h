/*
 ============================================================================
 Name        : Gpt_Types.h
 Module Name : Gpt
 Author      : Ahmed Ali
 Date        : 15 Aug. 2024
 Description : Types file for TM4C123GH6PM Microcontroller - Gpt Driver
 ============================================================================
 */

#ifndef GPT_TYPES_H_
#define GPT_TYPES_H_

/*
 * Module Version 1.0.0
 */
#define GPT_TYPES_SW_MAJOR_VERSION           (1U)
#define GPT_TYPES_SW_MINOR_VERSION           (0U)
#define GPT_TYPES_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_TYPES_AR_RELEASE_MAJOR_VERSION   (4U)
#define GPT_TYPES_AR_RELEASE_MINOR_VERSION   (0U)
#define GPT_TYPES_AR_RELEASE_PATCH_VERSION   (3U)

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Gpt_ChannelType.
 * Represents the numeric ID of a GPT channel used by the GPT APIs. */
typedef uint8 Gpt_ChannelType;

/* Type definition for Gpt_ValueType.
 * Represents the number of ticks or value used by the GPT APIs. */
typedef uint64 Gpt_ValueType;

/* Type definition for Gpt_ModeType.
 * Represents the selection of different power modes for the GPT module. */
typedef enum
{
    /* Normal operation mode of the GPT.
     * The GPT operates with full functionality and resources. */
    GPT_MODE_NORMAL,

    /* Reduced power operation mode (sleep mode).
     * Only wake-up capable channels are available in this mode. */
    GPT_MODE_SLEEP
} Gpt_ModeType;

#endif /* GPT_TYPES_H_ */
