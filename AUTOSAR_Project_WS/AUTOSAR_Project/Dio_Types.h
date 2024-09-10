/*
 ============================================================================
 Name        : Dio_Types.h
 Module Name : Dio
 Author      : Ahmed Ali
 Date        : 7 Aug. 2024
 Description : Types Header file for TM4C123GH6PM Microcontroller - Dio Driver
 ============================================================================
 */

#ifndef DIO_TYPES_H_
#define DIO_TYPES_H_

/*
 * Module Version 1.0.0
 */
#define DIO_TYPES_SW_MAJOR_VERSION           (1U)
#define DIO_TYPES_SW_MINOR_VERSION           (0U)
#define DIO_TYPES_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_TYPES_AR_RELEASE_MAJOR_VERSION   (4U)
#define DIO_TYPES_AR_RELEASE_MINOR_VERSION   (0U)
#define DIO_TYPES_AR_RELEASE_PATCH_VERSION   (3U)

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Dio_ChannelType used by the DIO APIs.
 * This represents the specific channel (or pin) within a port. */
typedef uint8 Dio_ChannelType;

/* Type definition for Dio_PortType used by the DIO APIs.
 * This represents a specific port in the microcontroller. */
typedef uint8 Dio_PortType;

/* Type definition for Dio_LevelType used by the DIO APIs.
 * This represents the level (HIGH or LOW) of a DIO channel. */
typedef uint8 Dio_LevelType;

/* Type definition for Dio_PortLevelType used by the DIO APIs.
 * This represents the level (HIGH or LOW) of an entire port. */
typedef uint8 Dio_PortLevelType;

/* Structure definition for Dio_ChannelGroupType used by the DIO APIs.
 * This defines a group of channels within a port that can be accessed together. */
typedef struct
{
    /* Mask defining the bit positions of the channels within the group.
     * The mask determines which bits are part of the channel group. */
    uint8 mask;

    /* Offset indicating the position of the channel group from the least significant bit (LSB).
     * This helps in aligning the group to the correct position within the port. */
    uint8 offset;

    /* Port ID where the channel group is located.
     * This indicates the port in which the channel group is defined. */
    Dio_PortType PortIndex;
} Dio_ChannelGroupType;

#endif /* DIO_TYPES_H_ */
