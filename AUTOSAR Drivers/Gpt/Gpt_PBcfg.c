/*
 ============================================================================
 Name        : Gpt_PBcfg.c
 Module Name : Gpt
 Author      : Ahmed Ali
 Date        : 15 Aug. 2024
 Description : Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Gpt Driver
 ============================================================================
 */

#include "Gpt.h"

/* AUTOSAR Version checking between Gpt_PBcfg.c and Gpt.h files */
#if ((GPT_PBCFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Gpt_PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Gpt_PBcfg.c and Gpt.h files */
#if ((GPT_PBCFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_PBCFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_PBCFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
#error "The SW version of Gpt_PBcfg.c does not match the expected version"
#endif

extern void Os_NewTimerTick(void);

/* PB structure used with Gpt_Init API */
const Gpt_ConfigType Gpt_Configuration =
{
 /* SysTick Timer Channel Configuration */
 { GPT_SYSTICK_ID, GPT_SYSTICK_VALUE, GPT_CH_MODE_CONTINUOUS, GPT_MODE_NORMAL, GPT_SYSTEM_CLOCK, Os_NewTimerTick }
};
