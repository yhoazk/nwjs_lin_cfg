/****************************************************************************************************/
/**
\file       cnf_lin.h
\brief      Configuration of LIN driver
\author     Abraham Tezmol
\version    1.0
\date       28/02/2016
*/
/****************************************************************************************************/

#ifndef __CNF_LIN_H        /*prevent duplicated includes*/
#define    __CNF_LIN_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core Modules */
/** Configuration Options */
#include    "configuration.h"
/** S12X derivative information */
#include    __MCU_DERIVATIVE
/** Variable types and common definitions */
#include    "typedefs.h"

/** SCI configuration definitions */
#include    "cnf_serial.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

typedef enum
{
    LIN_slaveResponse,            /* Data produced by slave  */
    LIN_masterResponse,            /* Data produced by master */
}tLIN_frameType;

typedef enum
{
    LIN_classic,                /* Classic LIN 1.x checksum  */
    LIN_enhanced,                /* Enhanced LIN 2.x checksum  */
}tLIN_checksumType;

typedef enum
{
    LIN_master,                    /* Node is a Master in the network  */
    LIN_slave,                    /* Node is a Slave in the network */
}tLIN_channelType;

typedef enum
{
    LIN_0,                        /* LIN node 0 */
}tLIN_channel;

typedef struct
{
    UINT8*                        LIN_data;                /* Pointer to LIN signal data */
    UINT8                        LIN_signalLength;        /* Size of the signal in bits */
    UINT8                        LIN_signalOffset;        /* Offset of signal within LIN frame in bits */
}tLIN_signal_config;

typedef struct
{
    const tLIN_signal_config*    LIN_signal;                /* Pointer to LIN signal configuration */
    enum tLIN_frameType            LIN_frameType;            /* Master or Slave response frame */
    enum tLIN_checksumType        LIN_checksumType;        /* Classic or enhanced checksum supported */
    UINT16                        LIN_startTime;            /* LIN frame start time in ms */
    UINT8                        LIN_supportedSignals;    /* Size of the signal configuration table */
    UINT8                        LIN_length;                /* Number of data bytes supported by frame */
    UINT8                       LIN_Pid;                /* Protected Identifier */
}tLIN_frame_config;

typedef struct
{
    const tLIN_frame_config*    LIN_framePublisher;        /* Pointer to supported pusblisher frame table */
    const tLIN_frame_config*    LIN_frameSuscriber;        /* Pointer to supported suscriber frame table */
    UINT16                        LIN_tableTotalTime;        /* Table total time in ms */
    UINT8                        LIN_noFramesPublisher;    /* Size of the publisher frame configuration table */
    UINT8                        LIN_noFramesSuscriber;    /* Size of the suscriber frame configuration table */
      UINT8                        LIN_masterResolution;    /* Master table resolution in ms */
}tLIN_table_config;

typedef struct
{
    const tLIN_table_config*    LIN_table;                /* Pointer to LIN configuration table */
    tCallbackFunction*            LIN_wakeUpFctn;            /* Pointer to function to be callled upon Wake Up */
    UINT32                        LIN_baudrate;            /* LIN Baudrate*/
      enum tLIN_channel            LIN_channel;            /* LIN Channel ID */
    enum tSCI_Channel            SCI_Channel;            /* Low leverl drier SCI channel assigned */
      enum tLIN_channelType        LIN_channelType;        /* Master or Slave */
}tLIN_channel_config;

typedef struct
{
    const tLIN_channel_config * LIN_channel_config;    /* Pointer to LIN channels configuration */
}tLIN_driver_config;

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS
*****************************************************************************************************/


/*****************************************************************************************************
* Declaration of public VARIABLEs / Constants
*****************************************************************************************************/


extern UINT8  RearFogLampInd;
extern UINT8  PositionLampInd;
extern UINT8  RearFogLampInd;
extern UINT8  IgnitionKeyPos;
extern UINT8  SLVFuncIllum;
extern UINT8  SLVSymbolIllum;

extern UINT8  SLVSWPartNo;
extern UINT16 SLVHWPartNoB0;
extern UINT16 SLVHWPartNoB1;

extern UINT16 FanIdealSpeed;
extern UINT16 FanMeasSpeed;
extern UINT16 WaterTemp;

#ifdef LIN_NODE_MASTER
    extern const tLIN_driver_config LIN_driverMaster;
#endif
#ifdef LIN_NODE_SLAVE
    extern const tLIN_driver_config LIN_driverSlave;
#endif

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/


#endif /* __CNF_LIN_H */
