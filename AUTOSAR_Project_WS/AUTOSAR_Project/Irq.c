/*
 ============================================================================
 Name        : Irq.c
 Module Name : Irq
 Author      : Ahmed Ali
 Date        : 27 Jul 2024
 Description : Source file for the ARM Cortex M4 NVIC driver
 ============================================================================
 */

#include "Irq.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NVIC_PRI_BASE_REG                   ((volatile uint32 *) 0xE000E400)
#define NVIC_EN_BASE_REG                    ((volatile uint32 *) 0xE000E100)
#define NVIC_DIS_BASE_REG                   ((volatile uint32 *) 0xE000E180)

/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for this specific IRQ.
 **********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    /* calculate the register number and bit position */
    uint8 REG_NUM = IRQ_Num / 32;
    uint8 BIT_POS = IRQ_Num % 32;

    /* access the correct register and set the bit to enable the interrupt for specific IRQ */
    NVIC_EN_BASE_REG[REG_NUM] |= (1 << BIT_POS);
}

/*********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for this specific IRQ.
 **********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    /* calculate the register number and bit position */
    uint8 REG_NUM = IRQ_Num / 32;
    uint8 BIT_POS = IRQ_Num % 32;

    /* access the correct register and set the bit to disable the interrupt for specific IRQ */
    NVIC_DIS_BASE_REG[REG_NUM] |= (1 << BIT_POS);
}

/*********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in):
 *     IRQ_Num - Number of the IRQ from the target vector table
 *     IRQ_Priority - Priority value to be set for the specified IRQ
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority value for a specific IRQ.
 **********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority)
{
    /* ensure priority is only 3-bits */
    IRQ_Priority &= 0x07;

    /* calculate the register number */
    uint8 REG_NUM = IRQ_Num / 4;

    /* only upper 3-bits used, so offset is 5-bits */
    uint8 BIT_POS = 5 + (8 * (IRQ_Num % 4));

    /* access the correct register and set the priority for specific IRQ */
    NVIC_PRI_BASE_REG[REG_NUM] = (NVIC_PRI_BASE_REG[REG_NUM] & (~(0x07 << BIT_POS))) | (IRQ_Priority << BIT_POS);
}

/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the exception to enable
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable specific ARM system or fault exceptions.
 **********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    /* check if the exception is a memory management fault */
    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        /* enable memory management fault by setting the corresponding bit in the SYSHNDCTRL Register */
        NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
    }
    /* check if the exception is a bus fault */
    else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        /* enable bus fault by setting the corresponding bit in the SYSHNDCTRL Register */
        NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
    }
    /* check if the exception is a usage fault */
    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        /* enable usage fault by setting the corresponding bit in the SYSHNDCTRL Register */
        NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
    }
}

/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the exception to disable
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable specific ARM system or fault exceptions.
 **********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    /* check if the exception is a memory management fault */
    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        /* disable memory management fault by clearing the corresponding bit in the SYSHNDCTRL Register */
        NVIC_SYSTEM_SYSHNDCTRL &= ~MEM_FAULT_ENABLE_MASK;
    }
    /* check if the exception is a bus fault */
    else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        /* disable bus fault by clearing the corresponding bit in the SYSHNDCTRL Register */
        NVIC_SYSTEM_SYSHNDCTRL &= ~BUS_FAULT_ENABLE_MASK;
    }
    /* check if the exception is a usage fault */
    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        /* disable usage fault by clearing the corresponding bit in the SYSHNDCTRL Register */
        NVIC_SYSTEM_SYSHNDCTRL &= ~USAGE_FAULT_ENABLE_MASK;
    }
}

/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in):
 *     Exception_Num - Number of the exception to set priority
 *     Exception_Priority - Priority value to be set for the specified exception
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority value for specific ARM system or fault
 *              exceptions.
 **********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{
    /* check if the exception is a memory management fault */
    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        /* clear the current priority bits and set the new priority for memory management fault */
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~MEM_FAULT_PRIORITY_MASK) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
    }
    /* check if the exception is a bus fault */
    else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        /* clear the current priority bits and set the new priority for bus fault */
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~BUS_FAULT_PRIORITY_MASK) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
    }
    /* check if the exception is a usage fault */
    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        /* clear the current priority bits and set the new priority for usage fault */
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
    }
    /* check if the exception is a SVC */
    else if (Exception_Num == EXCEPTION_SVC_TYPE)
    {
        /* clear the current priority bits and set the new priority for SVC */
        NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & ~SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
    }
    /* check if the exception is a debug monitor */
    else if (Exception_Num == EXCEPTION_DEBUG_MONITOR_TYPE)
    {
        /* clear the current priority bits and set the new priority for debug monitor */
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
    }
    /* check if the exception is a PendSV */
    else if (Exception_Num == EXCEPTION_PEND_SV_TYPE)
    {
        /* clear the current priority bits and set the new priority for PendSV */
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~PENDSV_PRIORITY_MASK) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
    }
    /* check if the exception is a SysTick exception */
    else if (Exception_Num == EXCEPTION_SYSTICK_TYPE)
    {
        /* clear the current priority bits and set the new priority for SysTick */
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
    }
}
