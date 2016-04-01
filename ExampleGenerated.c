
/****************************************************************************************************/
/**
\file       cnf_lin.c
\brief      Configuration of LIN driver
\author     Abraham Tezmol
\version    1.0
\date       Thu Mar 31 2016 23:31:34 GMT-0600 (CST)
*/
/****************************************************************************************************/
/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** SCI configuration definitions */
#include    "cnf_lin.h"


/*****************************************************************************************************
* Definition of  VARIABLEs -
*****************************************************************************************************/
  UINT8 RearFogLampInd = 0x0;
  UINT8 PositionLampInd = 0x1;
  UINT8 FrontFogLampInd = 0x2;
  UINT8 IgnitionKeyPos = 0x3;
  UINT8 SLVFuncIllum = 0x4;
  UINT8 SLVSymbolIllum = 0x5;
  UINT8 SLVSWPartNo = 0x6;
  UINT16 SLVHWPartNoB0 = 0x7;
  UINT16 SLVHWPartNoB1 = 0x8;
  UINT16 FanIdealSpeed = 0x9;
  UINT16 FanMeasSpeed = 0x10;
  UINT16 WaterTemp = 0x11;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs
*****************************************************************************************************/


/* Frame1 */
const tLIN_signal_config LIN_signalsFrame1[] =
{
  {
    ( UINT8*)&RearFogLampInd, /* Signal Name */
    1, /* Signal size in bytes TODO */
    0 /* Signal offset in frame */
  },
  {
    ( UINT8*)&PositionLampInd, /* Signal Name */
    1, /* Signal size in bytes TODO */
    1 /* Signal offset in frame */
  },
  {
    ( UINT8*)&FrontFogLampInd, /* Signal Name */
    1, /* Signal size in bytes TODO */
    2 /* Signal offset in frame */
  },
  {
    ( UINT8*)&IgnitionKeyPos, /* Signal Name */
    3, /* Signal size in bytes TODO */
    3 /* Signal offset in frame */
  },
  {
    ( UINT8*)&SLVFuncIllum, /* Signal Name */
    4, /* Signal size in bytes TODO */
    8 /* Signal offset in frame */
  },
  {
    ( UINT8*)&SLVSymbolIllum, /* Signal Name */
    4, /* Signal size in bytes TODO */
    12 /* Signal offset in frame */
  },
};
/* end: Frame1 */


/* Frame2 */
const tLIN_signal_config LIN_signalsFrame2[] =
{
  {
    ( UINT8*)&SLVSWPartNo, /* Signal Name */
    8, /* Signal size in bytes TODO */
    0 /* Signal offset in frame */
  },
  {
    ( UINT16*)&SLVHWPartNoB0, /* Signal Name */
    12, /* Signal size in bytes TODO */
    8 /* Signal offset in frame */
  },
  {
    ( UINT16*)&SLVHWPartNoB1, /* Signal Name */
    12, /* Signal size in bytes TODO */
    24 /* Signal offset in frame */
  },
};
/* end: Frame2 */


/* Frame3 */
const tLIN_signal_config LIN_signalsFrame3[] =
{
  {
    ( UINT16*)&FanIdealSpeed, /* Signal Name */
    16, /* Signal size in bytes TODO */
    0 /* Signal offset in frame */
  },
  {
    ( UINT16*)&FanMeasSpeed, /* Signal Name */
    16, /* Signal size in bytes TODO */
    16 /* Signal offset in frame */
  },
  {
    ( UINT16*)&WaterTemp, /* Signal Name */
    16, /* Signal size in bytes TODO */
    32 /* Signal offset in frame */
  },
};
/* end: Frame3 */



/*****************************************************************************************************
* Definition of  Frames -
*****************************************************************************************************/
const tLIN_frame_config LIN_frameTableMST[] =
{
  /* if is the same publisher */
  {
    & LIN_signalsFrame1[0], /* Pointer to LIN signal configuration */
    LIN_masterResponse,
    LIN_classic,                /* Classic or enhanced checksum supported */
    15 /* LIN_startTimeMs */
    sizeof(LIN_signalsFrame1)/sizeof(tLIN_signal_config),
    8, /* 2 actually used  Number of data bytes supported by frame */
    0xd3 /* Protected Identifier */
  },

};
const tLIN_frame_config LIN_frameTableSLV[] =
{
  /* if is the same publisher */
  {
    & LIN_signalsFrame2[0], /* Pointer to LIN signal configuration */
    LIN_slaveResponse,
    LIN_enhanced,               /* Classic or enhanced checksum supported */
    25 /* LIN_startTimeMs */
    sizeof(LIN_signalsFrame2)/sizeof(tLIN_signal_config),
    8, /* 4 actually used  Number of data bytes supported by frame */
    0xe2 /* Protected Identifier */
  },
  {
    & LIN_signalsFrame3[0], /* Pointer to LIN signal configuration */
    LIN_slaveResponse,
    LIN_enhanced,               /* Classic or enhanced checksum supported */
    25 /* LIN_startTimeMs */
    sizeof(LIN_signalsFrame3)/sizeof(tLIN_signal_config),
    8, /* 6 actually used  Number of data bytes supported by frame */
    0xfb /* Protected Identifier */
  },

};

/*******************************************************************************/

#ifdef LIN_MODE_MST
const tLIN_table_config LIN_tableMST =
{
    &LIN_frameTableMST[0],            /* Pointer to supported pusblisher frame table */
    &LIN_frameTableSLV[0],            /* Pointer to supported suscriber frame table */
    200,                                /* Table total time in ms */
    sizeof(LIN_frameTableMST)/sizeof(tLIN_frame_config),    /* Size of the publisher frame configuration table */
    sizeof(LIN_frameTableSLV)/sizeof(tLIN_frame_config),    /* Size of the suscriber frame configuration table */
      5                                 /* Master table resolution in ms */
};

const tLIN_channel_config LIN_channelMaster =
{
    &LIN_tableMST,                /* Pointer to LIN configuration table */
    (tCallbackFunction*)NULL,        /* Pointer to function to be callled upon Wake Up */
    (UINT32)19200,                    /* LIN Baudrate*/
    LIN_0,                            /* LIN Channel ID */
    SCI_CH0,                        /* Low leverl drier SCI channel assigned */
    LIN_master                         /* Master or Slave */
};

const tLIN_driver_config LIN_driverMaster =
{
    &LIN_channelMaster              /* Pointer to LIN channels configuration */
};

#endif /* LIN_MODE_MST */


#ifdef LIN_MODE_SLV
const tLIN_table_config LIN_tableSLV =
{
    &LIN_frameTableSLV[0],            /* Pointer to supported pusblisher frame table */
    &LIN_frameTableMST[0],            /* Pointer to supported suscriber frame table */
    200,                                /* Table total time in ms */
    sizeof(LIN_frameTableSLV)/sizeof(tLIN_frame_config),    /* Size of the publisher frame configuration table */
    sizeof(LIN_frameTableMST)/sizeof(tLIN_frame_config),    /* Size of the suscriber frame configuration table */
    5                                 /* Master table resolution in ms */
};

const tLIN_channel_config LIN_channelMaster =
{
    &LIN_tableSLV,                /* Pointer to LIN configuration table */
    (tCallbackFunction*)NULL,        /* Pointer to function to be callled upon Wake Up */
    (UINT32)19200,                    /* LIN Baudrate*/
    LIN_0,                            /* LIN Channel ID */
    SCI_CH0,                        /* Low leverl drier SCI channel assigned */
    LIN_slav                         /* Master or Slave */
};

const tLIN_driver_config LIN_driverSlave =
{
    &LIN_channelSlave              /* Pointer to LIN channels configuration */
};

#endif /* LIN_MODE_ */

/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/
