/*
 ============================================================================
 Name        : Port.c
 Module Name : Port
 Author      : Ahmed Ali
 Date        : 12 Aug. 2024
 Description : Source file for TM4C123GH6PM Microcontroller - Port Driver
 ============================================================================
 */

#include "Port_Private.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"

#endif
#endif

STATIC const Port_ConfigPinType *Port_Pins = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
 * Service Name: Port_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): ConfigPtr - Pointer to configuration set.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Initialize the Port Driver module.
 ************************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr)
{
    /* Point to the required Port Registers base address */
    volatile uint32 *PortGpio_Ptr = NULL_PTR;
    Port_PinType index;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the input configuration pointer is not a NULL_PTR, if not report an error and do not proceed further */
    if (NULL_PTR == ConfigPtr)
    {
        /* DET Report */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
    }
    else
#endif
    {
        /*
         * Set the module state to initialized and point to the PB configuration structure using a global pointer.
         * This global pointer is global to be used by other functions to read the PB configuration structures
         */
        Port_Status = PORT_INITIALIZED;
        Port_Pins = ConfigPtr->Pins;
        for (index = 0; index < PORT_NUMBER_OF_PORT_PINS; index++)
        {
            /* Set the base address of the corresponding GPIO port based on the pin's port number.
             * This is necessary for accessing the correct port registers later in the function.
             */
            switch (Port_Pins[index].Port_Num)
            {
            case PORTA_ID :
                /* PORTA Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS;
                break;
            case PORTB_ID :
                /* PORTB Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS;
                break;
            case PORTC_ID :
                /* PORTC Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS;
                break;
            case PORTD_ID :
                /* PORTD Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS;
                break;
            case PORTE_ID :
                /* PORTE Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS;
                break;
            case PORTF_ID :
                /* PORTF Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS;
                break;
            }

            /* Unlock PD7 and PF0 as they are locked by default due to special functionalities associated with these pins.
             * For these pins to be used as general-purpose I/O, the commit register must be unlocked and updated.
             */
            if (((Port_Pins[index].Port_Num == PORTD_ID ) && (Port_Pins[index].Pin_Num == PIN7_ID )) || ((Port_Pins[index].Port_Num == PORTF_ID ) && (Port_Pins[index].Pin_Num == PIN0_ID ))) /* PD7 or PF0 */
            {
                /* Unlock the GPIOCR register */
                *(volatile uint32*) ((volatile uint8*) PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;

                /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), Port_Pins[index].Pin_Num);
            }
            else if ((Port_Pins[index].Port_Num == PORTC_ID ) && (Port_Pins[index].Pin_Num <= PIN3_ID )) /* PC0 to PC3 */
            {
                /* Special case for JTAG pins (Port C pins 0-3), skipping direction setting as these pins are reserved for JTAG functionality */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            /* Setting pin direction based on the provided configuration:
             * If output: set the pin direction and initialize to the provided level (high/low).
             * If input: configure the pin direction and set internal pull-up/pull-down resistors as needed.
             */
            if (Port_Pins[index].Pin_Direction == PORT_PIN_OUT) /* Pin direction => output */
            {
                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[index].Pin_Num);

                if (Port_Pins[index].Pin_InitialValue == PORT_PIN_LEVEL_HIGH) /* Initial value => logic high */
                {
                    /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Pins[index].Pin_Num);
                }
                else if (Port_Pins[index].Pin_InitialValue == PORT_PIN_LEVEL_LOW) /* Initial value => logic low */
                {
                    /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Pins[index].Pin_Num);
                }
                else
                {
                    /* Do Nothing */
                }
            }
            else if (Port_Pins[index].Pin_Direction == PORT_PIN_IN) /* Pin direction => input */
            {
                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[index].Pin_Num);

                /* Configure internal resistor for input pin:
                 * - Pull-up resistor ensures the pin reads as high when not driven.
                 * - Pull-down resistor ensures the pin reads as low when not driven.
                 * - If no resistor is needed, both pull-up and pull-down are disabled.
                 */
                if (Port_Pins[index].Pin_InternalResistor == PORT_INTERNAL_RESISTOR_PULL_UP) /* Internal resistor => pull-up */
                {
                    /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Pins[index].Pin_Num);
                }
                else if (Port_Pins[index].Pin_InternalResistor == PORT_INTERNAL_RESISTOR_PULL_DOWN) /* Internal resistor => pull-down */
                {
                    /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Pins[index].Pin_Num);
                }
                else if (Port_Pins[index].Pin_InternalResistor == PORT_INTERNAL_RESISTOR_OFF) /* Internal resistor => off */
                {
                    /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Pins[index].Pin_Num);

                    /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Pins[index].Pin_Num);
                }
                else
                {
                    /* Do Nothing */
                }
            }
            else
            {
                /* Final else block in case the direction is neither input nor output (e.g., invalid direction) */
            }

            /* Digital Input/Output Mode:
             * - Disable analog functionality to ensure the pin is used as a digital pin.
             * - Clear alternative functions to ensure the pin operates in regular I/O mode.
             * - Set the pin as a digital pin by enabling the GPIODEN register.
             */
            if (Port_Pins[index].Pin_Mode == PORT_PIN_MODE_DIO) /* Mode => DIO */
            {

                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Pins[index].Pin_Num);

                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Pins[index].Pin_Num);

                /* Clear the PMCx bits for this pin */
                *(volatile uint32*) ((volatile uint8*) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins[index].Pin_Num * 4));

                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Pins[index].Pin_Num);
            }
            /* Analog Input Mode:
             * - Enable analog functionality for ADC operations.
             * - Clear the digital enable register to prevent digital interference with analog signals.
             * - Set the alternative function for ADC to work correctly with the pin.
             */
            else if (Port_Pins[index].Pin_Mode == PORT_PIN_MODE_AIN) /* Mode => ADC */
            {

                /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Pins[index].Pin_Num);

                /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Pins[index].Pin_Num);

                /* Clear the PMCx bits for this pin */
                *(volatile uint32*) ((volatile uint8*) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins[index].Pin_Num * 4));

                /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Pins[index].Pin_Num);

            }
            /* Alternative Function Mode:
             * - Disable analog functionality and set the alternative function to allow the pin to operate
             * in a non-standard mode (e.g., UART, PWM, etc.).
             * - Set the correct bits in the port control register (PMCx) to assign the appropriate alternative function.
             */
            else /* Mode => Another */
            {
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Pins[index].Pin_Num);

                /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Pins[index].Pin_Num);

                /* Clear the PMCx bits first before insert the mode */
                *(volatile uint32*) ((volatile uint8*) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins[index].Pin_Num * 4));
                /* Insert the mode in the PMCx bits for this pin */
                *(volatile uint32*) ((volatile uint8*) PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((Port_Pins[index].Pin_Mode & 0x0000000F) << (Port_Pins[index].Pin_Num * 4));

                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Pins[index].Pin_Num);
            }
        } /* Loop end */
    }
} /* Function end: All pins have been initialized with their respective configurations. */

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin - Port Pin ID number.
 *                  Direction - Port Pin Direction.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Set the port pin direction.
 ************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    /* Point to the required Port Registers base address */
    volatile uint32 *PortGpio_Ptr = NULL_PTR;
    boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the driver has been initialized, if not report an error and do not proceed further */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        /* DET Report */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_API, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
    /* Check if the used pin is within the valid range, if not report an error and do not proceed further */
    if (PORT_NUMBER_OF_PORT_PINS <= Pin)
    {
        /* DET Report */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_API, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
    /* Check if this pin support the direction changeable option, if not report an error and do not proceed further */
    if (PORT_PIN_DIRECTION_CHANGEABLE_OFF == Port_Pins[Pin].Pin_DirectionChange)
    {
        /* DET Report */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_API, PORT_E_DIRECTION_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
#endif

    /* In-case there are no errors */
    if (FALSE == error)
    {
        if ((Port_Pins[Pin].Port_Num == PORTC_ID ) && (Port_Pins[Pin].Pin_Num < 4))
        {
            /* Special case for JTAG pins (Port C pins 0-3), skipping direction setting as these pins are reserved for JTAG functionality */
        }
        else
        {
            /* Set the base address of the corresponding GPIO port based on the pin's port number.
             * This is necessary for accessing the correct port registers later in the function.
             */
            switch (Port_Pins[Pin].Port_Num)
            {
            case PORTA_ID :
                /* PORTA Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS;
                break;
            case PORTB_ID :
                /* PORTB Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS;
                break;
            case PORTC_ID :
                /* PORTC Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS;
                break;
            case PORTD_ID :
                /* PORTD Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS;
                break;
            case PORTE_ID :
                /* PORTE Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS;
                break;
            case PORTF_ID :
                /* PORTF Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS;
                break;
            }

            /* Setting pin direction based on the provided configuration:
             * If output: set the pin direction and initialize to the provided level (high/low).
             * If input: configure the pin direction and set internal pull-up/pull-down resistors as needed.
             */
            if (Direction == PORT_PIN_OUT) /* Pin direction => output */
            {
                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[Pin].Pin_Num);

                if (Port_Pins[Pin].Pin_InitialValue == PORT_PIN_LEVEL_HIGH) /* Initial value => logic high */
                {
                    /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Pins[Pin].Pin_Num);
                }
                else if (Port_Pins[Pin].Pin_InitialValue == PORT_PIN_LEVEL_LOW) /* Initial value => logic low */
                {
                    /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Pins[Pin].Pin_Num);
                }
                else
                {
                    /* Do Nothing */
                }
            }
            else if (Direction == PORT_PIN_IN) /* Pin direction => input */
            {
                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[Pin].Pin_Num);

                /* Configure internal resistor for input pin:
                 * - Pull-up resistor ensures the pin reads as high when not driven.
                 * - Pull-down resistor ensures the pin reads as low when not driven.
                 * - If no resistor is needed, both pull-up and pull-down are disabled.
                 */
                if (Port_Pins[Pin].Pin_InternalResistor == PORT_INTERNAL_RESISTOR_PULL_UP) /* Internal resistor => pull-up */
                {
                    /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Pins[Pin].Pin_Num);
                }
                else if (Port_Pins[Pin].Pin_InternalResistor == PORT_INTERNAL_RESISTOR_PULL_DOWN) /* Internal resistor => pull-down */
                {
                    /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Pins[Pin].Pin_Num);
                }
                else if (Port_Pins[Pin].Pin_InternalResistor == PORT_INTERNAL_RESISTOR_OFF) /* Internal resistor => off */
                {
                    /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Pins[Pin].Pin_Num);

                    /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Pins[Pin].Pin_Num);
                }
                else
                {
                    /* Do Nothing */
                }
            }
            else
            {
                /* Final else block in case the direction is neither input nor output (e.g., invalid direction) */
            }
        }
    }
    else
    {
        /* Do Nothing */
    }
} /* Function end: successfully set pin direction or reported errors as necessary */
#endif

/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Refresh port direction.
 ************************************************************************************/
void Port_RefreshPortDirection(void)
{
    /* point to the required Port Registers base address */
    volatile uint32 *PortGpio_Ptr = NULL_PTR;
    boolean error = FALSE;
    Port_PinType index;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
#endif

    /* In-case there are no errors */
    if (FALSE == error)
    {
        for (index = 0; index < PORT_NUMBER_OF_PORT_PINS; index++)
        {
            if ((Port_Pins[index].Port_Num == PORTC_ID ) && (Port_Pins[index].Pin_Num < 4))
            {
                /* Special case for JTAG pins (Port C pins 0-3), skipping direction setting as these pins are reserved for JTAG functionality */
            }
            else
            {
                /* Set the base address of the corresponding GPIO port based on the pin's port number.
                 * This is necessary for accessing the correct port registers later in the function.
                 */
                switch (Port_Pins[index].Port_Num)
                {
                case PORTA_ID :
                    /* PORTA Base Address */
                    PortGpio_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS;
                    break;
                case PORTB_ID :
                    /* PORTB Base Address */
                    PortGpio_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS;
                    break;
                case PORTC_ID :
                    /* PORTC Base Address */
                    PortGpio_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS;
                    break;
                case PORTD_ID :
                    /* PORTD Base Address */
                    PortGpio_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS;
                    break;
                case PORTE_ID :
                    /* PORTE Base Address */
                    PortGpio_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS;
                    break;
                case PORTF_ID :
                    /* PORTF Base Address */
                    PortGpio_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS;
                    break;
                }

                /* Refresh the pin direction based on the initial configuration.
                 * Pins with the direction changeable option set to OFF are refreshed to their default direction.
                 * - Output pins are set by enabling the corresponding bit in the GPIODIR register.
                 * - Input pins are set by disabling the corresponding bit in the GPIODIR register.
                 * Pins with direction changeable set to ON are skipped as their direction can be altered at runtime.
                 */

                if ((Port_Pins[index].Pin_Direction == PORT_PIN_OUT) && (Port_Pins[index].Pin_DirectionChange == PORT_PIN_DIRECTION_CHANGEABLE_OFF)) /* Pin direction => output */
                {
                    /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[index].Pin_Num);
                }
                else if ((Port_Pins[index].Pin_Direction == PORT_PIN_IN) && (Port_Pins[index].Pin_DirectionChange == PORT_PIN_DIRECTION_CHANGEABLE_OFF)) /* Pin direction => input */
                {
                    /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[index].Pin_Num);
                }
                else
                {
                    /* Do Nothing */
                }
            }
        } /* Loop end */
    }
    else
    {
        /* Do Nothing */
    }
} /* Function end: The port directions for all pins with non-changeable direction settings have been refreshed. */

#if (PORT_VERSION_INFO_API == STD_ON)
/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): versioninfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to Return the version information of this module.
 ************************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer, if not report an error and do not proceed further */
    if (NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_VERSION_INFO_API, PORT_E_PARAM_POINTER);
    }
    else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16) PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16) PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8) PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8) PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8) PORT_SW_PATCH_VERSION;
    }
} /* Function end: Successfully copied the version information (if the pointer was valid) and returned it to the caller */

#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin - Port Pin ID number.
 *                  Mode - New Port Pin mode to be set on port pin.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Set the port pin mode.
 ************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    /* point to the required Port Registers base address */
    volatile uint32 *PortGpio_Ptr = NULL_PTR;
    boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the driver has been initialized, if not report an error and do not proceed further */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        /* DET Report */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_API, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
    /* Check if the used pin is within the valid range, if not report an error and do not proceed further */
    if (PORT_NUMBER_OF_PORT_PINS <= Pin)
    {
        /* DET Report */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_API, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
    /* Check if this pin support the mode changeable option, if not report an error and do not proceed further */
    if (PORT_PIN_MODE_CHANGEABLE_OFF == Port_Pins[Pin].Pin_ModeChange)
    {
        /* DET Report */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_API, PORT_E_MODE_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
#endif

    /* In-case there are no errors */
    if (FALSE == error)
    {
        if ((Port_Pins[Pin].Port_Num == PORTC_ID ) && (Port_Pins[Pin].Pin_Num < 4))
        {
            /* Special case for JTAG pins (Port C pins 0-3), skipping direction setting as these pins are reserved for JTAG functionality */
        }
        else
        {
            /* Set the base address of the corresponding GPIO port based on the pin's port number.
             * This is necessary for accessing the correct port registers later in the function.
             */
            switch (Port_Pins[Pin].Port_Num)
            {
            case PORTA_ID :
                /* PORTA Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS;
                break;
            case PORTB_ID :
                /* PORTB Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS;
                break;
            case PORTC_ID :
                /* PORTC Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS;
                break;
            case PORTD_ID :
                /* PORTD Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS;
                break;
            case PORTE_ID :
                /* PORTE Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS;
                break;
            case PORTF_ID :
                /* PORTF Base Address */
                PortGpio_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS;
                break;
            }

            /* Digital Input/Output Mode:
             * - Disable analog functionality to ensure the pin is used as a digital pin.
             * - Clear alternative functions to ensure the pin operates in regular I/O mode.
             * - Set the pin as a digital pin by enabling the GPIODEN register.
             */
            if (Port_Pins[Pin].Pin_Mode == PORT_PIN_MODE_DIO) /* Mode => DIO */
            {

                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Pins[Pin].Pin_Num);

                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Pins[Pin].Pin_Num);

                /* Clear the PMCx bits for this pin */
                *(volatile uint32*) ((volatile uint8*) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins[Pin].Pin_Num * 4));

                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Pins[Pin].Pin_Num);
            }
            /* Analog Input Mode:
             * - Enable analog functionality for ADC operations.
             * - Clear the digital enable register to prevent digital interference with analog signals.
             * - Set the alternative function for ADC to work correctly with the pin.
             */
            else if (Port_Pins[Pin].Pin_Mode == PORT_PIN_MODE_AIN) /* Mode => ADC */
            {

                /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Pins[Pin].Pin_Num);

                /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Pins[Pin].Pin_Num);

                /* Clear the PMCx bits for this pin */
                *(volatile uint32*) ((volatile uint8*) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins[Pin].Pin_Num * 4));

                /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Pins[Pin].Pin_Num);

            }
            /* Alternative Function Mode:
             * - Disable analog functionality and set the alternative function to allow the pin to operate
             * in a non-standard mode (e.g., UART, PWM, etc.).
             * - Set the correct bits in the port control register (PMCx) to assign the appropriate alternative function.
             */
            else /* Mode => Another */
            {
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Pins[Pin].Pin_Num);

                /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Pins[Pin].Pin_Num);

                /* Clear the PMCx bits first before insert the mode */
                *(volatile uint32*) ((volatile uint8*) PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins[Pin].Pin_Num * 4));
                /* Insert the mode in the PMCx bits for this pin */
                *(volatile uint32*) ((volatile uint8*) PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((Port_Pins[Pin].Pin_Mode & 0x0000000F) << (Port_Pins[Pin].Pin_Num * 4));

                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Pins[Pin].Pin_Num);
            }
        }
    }
    else
    {
        /* Do Nothing */
    }
} /* Function end: Successfully set the pin mode or reported errors as necessary */
#endif

