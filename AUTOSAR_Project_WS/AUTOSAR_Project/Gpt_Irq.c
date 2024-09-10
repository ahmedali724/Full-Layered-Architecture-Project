/*
 ============================================================================
 Name        : Gpt_Irq.c
 Module Name : Gpt
 Author      : Ahmed Ali
 Date        : 15 Aug. 2024
 Description : Source file for TM4C123GH6PM Microcontroller Handler - Gpt Driver
 ============================================================================
 */

#include "Gpt_Private.h"

/* Extern declarations for global variables defined in Gpt.c */
extern volatile void (*Gpt_NotificationArr[GPT_CONFIGURED_CHANNELS])(void);
extern volatile uint16 SysTick_TargetTime;
extern volatile uint16 SysTick_CountedTime;

/*********************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Asynchronous
 * Reentrancy: non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Handler for SysTick interrupt, used to call the callback function.
 **********************************************************************/
void SysTick_Handler(void)
{
    if (Gpt_NotificationArr[GPT_SYSTICK_ID ] != NULL_PTR)
    {
        /* Increment counter each 1 Millisecond */
        SysTick_CountedTime++;

        /* Check if the counter has reached the target time */
        if (SysTick_CountedTime >= SysTick_TargetTime)
        {
            /* Call the callback function in the application */
            Gpt_NotificationArr[GPT_SYSTICK_ID ]();

            /* Reset the counter */
            SysTick_CountedTime = 0;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }
}
