
/****************************************************************************************************/
/**
\file       cnf_lin.c
\brief      Configuration of LIN driver
\author     Abraham Tezmol
\version    1.0
\date       Sat Apr 02 2016 01:45:47 GMT-0600 (CST)
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
  UINT16 sign_16b_01 = 0x12;
  UINT16 sign_16b_02 = 0x13;
  UINT16 sign_16b_03 = 0x14;
  UINT16 sign_16b_04 = 0x15;
  UINT16 sign_16b_05 = 0x16;
  UINT16 sign_16b_06 = 0x17;
  UINT16 sign_16b_07 = 0x18;
  UINT16 sign_16b_08 = 0x19;
  UINT16 sign_16b_09 = 0x20;
  UINT16 sign_16b_10 = 0x21;
  UINT16 sign_16b_11 = 0x22;
  UINT16 sign_16b_12 = 0x23;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs
*****************************************************************************************************/


/* EnvioDatos */
const tLIN_signal_config LIN_signalsEnvioDatos[] =
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
/* end: LIN_signalsEnvioDatos */


/* Ack_slv */
const tLIN_signal_config LIN_signalsAck_slv[] =
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
/* end: LIN_signalsAck_slv */


/* data_respose */
const tLIN_signal_config LIN_signalsdata_respose[] =
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
/* end: LIN_signalsdata_respose */


/* data_req1 */
const tLIN_signal_config LIN_signalsdata_req1[] =
{
  {
    (UINT8 *)&sign_16b_01, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    0 /* Signal offset in frame */
  },
  {
    (UINT8 *)&sign_16b_02, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    16 /* Signal offset in frame */
  },
  {
    (UINT8 *)&sign_16b_03, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    32 /* Signal offset in frame */
  },
};
/* end: LIN_signalsdata_req1 */


/* data_req2 */
const tLIN_signal_config LIN_signalsdata_req2[] =
{
  {
    (UINT8 *)&sign_16b_04, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    0 /* Signal offset in frame */
  },
  {
    (UINT8 *)&sign_16b_05, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    16 /* Signal offset in frame */
  },
  {
    (UINT8 *)&sign_16b_06, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    32 /* Signal offset in frame */
  },
};
/* end: LIN_signalsdata_req2 */


/* acq_timer */
const tLIN_signal_config LIN_signalsacq_timer[] =
{
  {
    (UINT8 *)&sign_16b_07, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    0 /* Signal offset in frame */
  },
  {
    (UINT8 *)&sign_16b_08, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    16 /* Signal offset in frame */
  },
  {
    (UINT8 *)&sign_16b_09, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    32 /* Signal offset in frame */
  },
};
/* end: LIN_signalsacq_timer */


/* acq_time_mst */
const tLIN_signal_config LIN_signalsacq_time_mst[] =
{
  {
    (UINT8 *)&sign_16b_10, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    0 /* Signal offset in frame */
  },
  {
    (UINT8 *)&sign_16b_11, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    16 /* Signal offset in frame */
  },
  {
    (UINT8 *)&sign_16b_12, /* Pointer to LIN signal data Signal Name UINT16 */
    16, /* Signal size in bytes  */
    32 /* Signal offset in frame */
  },
};
/* end: LIN_signalsacq_time_mst */



/*****************************************************************************************************
* Definition of  Frames -
*****************************************************************************************************/
const tLIN_frame_config LIN_frameTableMST[] =
{
  /* if is the same publisher */
  {
    & LIN_signalsEnvioDatos[0], /* Pointer to LIN signal configuration */
    LIN_masterResponse,
    LIN_classic,                /* Classic or enhanced checksum supported */
    10, /* LIN_startTimeMs */
    sizeof(LIN_signalsEnvioDatos)/sizeof(tLIN_signal_config),
    8, /* 2 actually used  Number of data bytes supported by frame */
    0xcf /* Protected Identifier */
  },

};

const tLIN_frame_config LIN_frameTableSLV[] =
{
  /* if is the same publisher */
  {
    & LIN_signalsAck_slv[0], /* Pointer to LIN signal configuration */
    LIN_slaveResponse,
    LIN_enhanced,               /* Classic or enhanced checksum supported */
    25, /* LIN_startTimeMs */
    sizeof(LIN_signalsAck_slv)/sizeof(tLIN_signal_config),
    8, /* 4 actually used  Number of data bytes supported by frame */
    0xe2 /* Protected Identifier */
  },
  {
    & LIN_signalsdata_respose[0], /* Pointer to LIN signal configuration */
    LIN_slaveResponse,
    LIN_enhanced,               /* Classic or enhanced checksum supported */
    40, /* LIN_startTimeMs */
    sizeof(LIN_signalsdata_respose)/sizeof(tLIN_signal_config),
    8, /* 6 actually used  Number of data bytes supported by frame */
    0xb1 /* Protected Identifier */
  },
  {
    & LIN_signalsdata_req1[0], /* Pointer to LIN signal configuration */
    LIN_slaveResponse,
    LIN_enhanced,               /* Classic or enhanced checksum supported */
    55, /* LIN_startTimeMs */
    sizeof(LIN_signalsdata_req1)/sizeof(tLIN_signal_config),
    8, /* 6 actually used  Number of data bytes supported by frame */
    0x32 /* Protected Identifier */
  },
  {
    & LIN_signalsdata_req2[0], /* Pointer to LIN signal configuration */
    LIN_slaveResponse,
    LIN_enhanced,               /* Classic or enhanced checksum supported */
    70, /* LIN_startTimeMs */
    sizeof(LIN_signalsdata_req2)/sizeof(tLIN_signal_config),
    8, /* 6 actually used  Number of data bytes supported by frame */
    0x73 /* Protected Identifier */
  },
  {
    & LIN_signalsacq_timer[0], /* Pointer to LIN signal configuration */
    LIN_slaveResponse,
    LIN_enhanced,               /* Classic or enhanced checksum supported */
    85, /* LIN_startTimeMs */
    sizeof(LIN_signalsacq_timer)/sizeof(tLIN_signal_config),
    8, /* 6 actually used  Number of data bytes supported by frame */
    0xb4 /* Protected Identifier */
  },
  {
    & LIN_signalsacq_time_mst[0], /* Pointer to LIN signal configuration */
    LIN_slaveResponse,
    LIN_enhanced,               /* Classic or enhanced checksum supported */
    100, /* LIN_startTimeMs */
    sizeof(LIN_signalsacq_time_mst)/sizeof(tLIN_signal_config),
    8, /* 6 actually used  Number of data bytes supported by frame */
    0xf5 /* Protected Identifier */
  },

};


/*******************************************************************************/

#ifdef LIN_NODE_MASTER
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

#endif /* LIN_MODE_MASTER */


#ifdef LIN_NODE_SLAVE
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

#endif /* LIN_MODE_SLAVE */

/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/


