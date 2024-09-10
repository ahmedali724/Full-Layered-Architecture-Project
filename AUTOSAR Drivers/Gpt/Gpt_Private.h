/*
 ============================================================================
 Name        : Gpt_Private.h
 Module Name : Gpt
 Author      : Ahmed Ali
 Date        : 15 Aug. 2024
 Description : Private file for TM4C123GH6PM Microcontroller - Gpt Driver
 ============================================================================
 */

#ifndef GPT_PRIVATE_H_
#define GPT_PRIVATE_H_

#include "Gpt.h"
#include "Common_Macros.h"

/*
 * Macros for Gpt Status
 */
#define GPT_INITIALIZED                (1U)
#define GPT_NOT_INITIALIZED            (0U)

/* Structure holding the state parameter for each channel. */
typedef struct
{
    Gpt_ChannelState Channel_State;
} Gpt_TimerChannelStates;

/*****************************************************************************
 *                           SysTick Timer Registers                         *
 *****************************************************************************/
#define SYSTICK_CTRL_REG          (*((volatile uint32 *)0xE000E010))
#define SYSTICK_RELOAD_REG        (*((volatile uint32 *)0xE000E014))
#define SYSTICK_CURRENT_REG       (*((volatile uint32 *)0xE000E018))

/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/

#define SYSTICK_STCTRL_COUNT_MASK           0x00010000

#define SYSTICK_STCTRL_CLK_SRC_MASK         0x00000004

#define SYSTICK_STCTRL_INTEN_MASK           0x00000002

#define SYSTICK_STCTRL_ENABLE_MASK          0x00000001

#endif /* GPT_PRIVATE_H_ */
