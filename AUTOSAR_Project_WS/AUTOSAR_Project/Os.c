/******************************************************************************
 *
 * Module: Os
 *
 * File Name: Os.c
 *
 * Description: Source file for Os Scheduler.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#include "Irq.h"
#include "Gpt.h"
#include "Os.h"
#include "App.h"
#include "Button.h"
#include "Led.h"

/* Global variable store the Os Time */
static uint8 g_Time_Tick_Count = 0;

/* Global variable to indicate the the timer has a new tick */
static uint8 g_New_Time_Tick_Flag = 0;

/*********************************************************************************************/
void Os_start(void)
{
    /* Global Interrupts Enable */
    Enable_Exceptions();

    /* Execute the Init Task */
    Init_Task();

    /* Start SysTickTimer to generate interrupt every 20ms */
    Gpt_StartTimer(GPT_SYSTICK_ID, OS_BASE_TIME);

    /* Setup priority for SysTick Exception */
    NVIC_SetPriorityException(EXCEPTION_SYSTICK_TYPE, GPT_SYSTICK_INTERRUPT_PRIORITY);

    /* Start the Os Scheduler */
    Os_Scheduler();
}

/*********************************************************************************************/
void Os_NewTimerTick(void)
{
    /* Increment the Os time by OS_BASE_TIME */
    g_Time_Tick_Count += OS_BASE_TIME;

    /* Set the flag to 1 to indicate that there is a new timer tick */
    g_New_Time_Tick_Flag = 1;
}

/*********************************************************************************************/
void Os_Scheduler(void)
{
    while (1)
    {
        /* Code is only executed in case there is a new timer tick */
        if (g_New_Time_Tick_Flag == 1)
        {
            switch (g_Time_Tick_Count)
            {
            case 20:
            case 100:
                Button_Task();
                g_New_Time_Tick_Flag = 0;
                break;
            case 40:
            case 80:
                Button_Task();
                Led_Task();
                g_New_Time_Tick_Flag = 0;
                break;
            case 60:
                Button_Task();
                App_Task();
                g_New_Time_Tick_Flag = 0;
                break;
            case 120:
                Button_Task();
                App_Task();
                Led_Task();
                g_New_Time_Tick_Flag = 0;
                g_Time_Tick_Count = 0;
                break;
            }
        }
    }

}
/*********************************************************************************************/
