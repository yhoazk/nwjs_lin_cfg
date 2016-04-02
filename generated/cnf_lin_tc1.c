
/****************************************************************************************************/
/**
\file       cnf_lin.c
\brief      Configuration of LIN driver
\author     Abraham Tezmol
\version    1.0
\date       Fri Apr 01 2016 22:28:52 GMT-0600 (CST)
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
  UINT16 SlaveMaster_Ack = 0x12;
  UINT16 SlaveMaster1_Ack = 0x13;
  UINT16 SlaveMaster2_Ack = 0x14;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs
*****************************************************************************************************/


/* Frame1 */
const tLIN_signal_config LIN_signalsFrame1[] =
{
  {
    (UINT8 *)&RearFogLampInd, /* Pointer to LIN signal data Signal Name UINT8 */
    1, /* Signal size in bytes  */
    0 /* Signal offset in frame */
  },
  {
    (UINT8 *)&PositionLampInd, /* Pointer to LIN signal data Signal Name UINT8 */
    1, /* Signal size in bytes  */
    1 /* Signal offset in frame */
  },
  {
    (UINT8 *)&FrontFogLampInd, /* Pointer to LIN signal data Signal Name UINT8 */
    1, /* Signal size in bytes  */
    2 /* Signal offset in frame */
  },
  {
    (UINT8 *)&IgnitionKeyPos, /* Pointer to LIN signal data Signal Name UINT8 */
    3, /* Signal size in bytes  */
    3 /* Signal offset in frame */
  },
  {
    (UINT8 *)&SLVFuncIllum, /* Pointer to LIN signal data Signal Name UINT8 */
    4, /* Signal size in bytes  */
    8 /* Signal offset in frame */
  },
  {
    (UINT8 *)&SLVSymbolIllum, /* Pointer to LIN signal data Signal Name UINT8 */
    4, /* Signal size in bytes  */
    12 /* Signal offset in frame */
  },
};
/* end: LIN_signalsFrame1 */


/* Frame2 */
const tLIN_signal_config LIN_signalsFrame2[] =
{
  {
    (UINT8 *)&SLVSWPartNo, /* Pointer to LIN signal data Signal Name UINT8 */
    8, /* Signal size in bytes  */
    0 /* Signal offset in frame */
  },
  {
    (UINT8 *)&SLVHWPartNoB0, /* Pointer to LIN signal data Signal Name UINT16 */
    12, /* Signal size in bytes  */
    8 /* Signal offset in frame */
  },
  {
    (UINT8 *)&SLVHWPartNoB1, /* Pointer to LIN signal data Signal Name UINT16 */
    12, /* Signal size in bytes  */
    24 /* Signal offset in frame */
  },
};
/* end: LIN_signalsFrame2 */


/* Frame3 */
const tLIN_signal_config LIN_signalsFrame3[] =
{
  {
    (UINT8 *)&FanIdealSpeed, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    0 /* Signal offset in frame */
  },
  {
    (UINT8 *)&FanMeasSpeed, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    16 /* Signal offset in frame */
  },
  {
    (UINT8 *)&WaterTemp, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    32 /* Signal offset in frame */
  },
};
/* end: LIN_signalsFrame3 */


/* Frame4 */
const tLIN_signal_config LIN_signalsFrame4[] =
{
  {
    (UINT8 *)&SlaveMaster_Ack, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    0 /* Signal offset in frame */
  },
  {
    (UINT8 *)&SlaveMaster1_Ack, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    16 /* Signal offset in frame */
  },
  {
    (UINT8 *)&SlaveMaster2_Ack, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    32 /* Signal offset in frame */
  },
};
/* end: LIN_signalsFrame4 */



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
    40 /* LIN_startTimeMs */
    sizeof(LIN_signalsFrame3)/sizeof(tLIN_signal_config),
    8, /* 6 actually used  Number of data bytes supported by frame */
    0xfb /* Protected Identifier */
  },
  {
    & LIN_signalsFrame4[0], /* Pointer to LIN signal configuration */
    LIN_slaveResponse,
    LIN_enhanced,               /* Classic or enhanced checksum supported */
    50 /* LIN_startTimeMs */
    sizeof(LIN_signalsFrame4)/sizeof(tLIN_signal_config),
    8, /* 6 actually used  Number of data bytes supported by frame */
    0x78 /* Protected Identifier */
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

const tLIN_channel_config LIN_channelSlave =
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

#endif /* LIN_MODE_SLV */

/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/


