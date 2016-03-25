<script id="template_lincfg" type="text/x-handlebars-template">
/****************************************************************************************************/
/**
\file       cnf_lin.c
\brief      Configuration of LIN driver
\author     Abraham Tezmol
\version    1.0
\date    <b>   {{lincfg.date_gen}}</b>
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

UINT8  RearFogLampInd    = 0x01;
UINT8  PositionLampInd   = 0x01;
UINT8  FrontFogLampInd   = 0x01;
UINT8  IgnitionKeyPos    = 0x05;
UINT8  SLVFuncIllum      = 0x09;
UINT8  SLVSymbolIllum    = 0x0A;

UINT8  SLVSWPartNo       = 0xAB;
UINT16 SLVHWPartNoB0     = 0x345;
UINT16 SLVHWPartNoB1     = 0x654;

UINT16 FanIdealSpeed     = 0x5544;
UINT16 FanMeasSpeed      = 0x5435;
UINT16 WaterTemp         = 0x1234;


/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs
*****************************************************************************************************/

const tLIN_signal_config LIN_signalsFrame1[] =
{
    {
        (UINT8 *)&RearFogLampInd,    /* Pointer to LIN signal data */
        1,                          /* Size of the signal in bits */
        0                            /* Offset of signal within LIN frame in bits */
    },
    {
        (UINT8 *)&PositionLampInd,    /* Pointer to LIN signal data */
        1,                          /* Size of the signal in bits */
        1                            /* Offset of signal within LIN frame in bits */
    },
    {
        (UINT8 *)&FrontFogLampInd,    /* Pointer to LIN signal data */
        1,                          /* Size of the signal in bits */
        2                            /* Offset of signal within LIN frame in bits */
    },
    {
        (UINT8 *)&IgnitionKeyPos,    /* Pointer to LIN signal data */
        3,                          /* Size of the signal in bits */
        3                            /* Offset of signal within LIN frame in bits */
    },
    {
        (UINT8 *)&SLVFuncIllum,        /* Pointer to LIN signal data */
        4,                          /* Size of the signal in bits */
        8                            /* Offset of signal within LIN frame in bits */
    },
    {
        (UINT8 *)&SLVSymbolIllum,   /* Pointer to LIN signal data */
        4,                          /* Size of the signal in bits */
        12                            /* Offset of signal within LIN frame in bits */
    }
};

const tLIN_signal_config LIN_signalsFrame2[] =
{
    {
        (UINT8 *)&SLVSWPartNo,        /* Pointer to LIN signal data */
        8,                          /* Size of the signal in bits */
        0                            /* Offset of signal within LIN frame in bits */
    },
    {
        (UINT8 *)&SLVHWPartNoB0,    /* Pointer to LIN signal data */
        12,                         /* Size of the signal in bits */
        8                            /* Offset of signal within LIN frame in bits */
    },
    {
        (UINT8 *)&SLVHWPartNoB1,    /* Pointer to LIN signal data */
        12,                         /* Size of the signal in bits */
        24                            /* Offset of signal within LIN frame in bits */
    }
};


const tLIN_signal_config LIN_signalsFrame3[] =
{
    {
        (UINT8 *)&FanIdealSpeed,    /* Pointer to LIN signal data */
        16,                         /* Size of the signal in bits */
        0                            /* Offset of signal within LIN frame in bits */
    },
    {
        (UINT8 *)&FanMeasSpeed,        /* Pointer to LIN signal data */
        16,                         /* Size of the signal in bits */
        16                            /* Offset of signal within LIN frame in bits */
    },
    {
        (UINT8 *)&WaterTemp,        /* Pointer to LIN signal data */
        16,                         /* Size of the signal in bits */
        32                            /* Offset of signal within LIN frame in bits */
    }
};


const tLIN_frame_config LIN_frameTable1[] =
{
    {
        &LIN_signalsFrame1[0],        /* Pointer to LIN signal configuration */
        LIN_masterResponse,            /* Master or Slave response frame */
        LIN_classic,                /* Classic or enhanced checksum supported */
        55,                        /* LIN_startTimeMs */
        sizeof(LIN_signalsFrame1)/sizeof(tLIN_signal_config),    /* Size of the signal configuration table */
        8,                            /* Number of data bytes supported by frame */
        0xD3,                       /* Protected Identifier */
    }
};

const tLIN_frame_config LIN_frameTable2[] =
{
    {
        &LIN_signalsFrame2[0],        /* Pointer to LIN signal configuration */
        LIN_slaveResponse,            /* Master or Slave response frame */
        LIN_enhanced,                /* Classic or enhanced checksum supported */
        5,                          /* LIN_startTimeMs */
        sizeof(LIN_signalsFrame2)/sizeof(tLIN_signal_config),    /* Size of the signal configuration table */
        8,                            /* Number of data bytes supported by frame */
        0xE2,                       /* Protected Identifier */
    },
    {
        &LIN_signalsFrame3[0],        /* Pointer to LIN signal configuration */
        LIN_slaveResponse,            /* Master or Slave response frame */
        LIN_enhanced,                /* Classic or enhanced checksum supported */
        105,                        /* LIN_startTimeMs */
        sizeof(LIN_signalsFrame3)/sizeof(tLIN_signal_config),    /* Size of the signal configuration table */
        8,                            /* Number of data bytes supported by frame */
        0xFB,                       /* Protected Identifier */
    }
};

#ifdef LIN_NODE_MASTER
    const tLIN_table_config LIN_tableMaster =
    {
        &LIN_frameTable1[0],            /* Pointer to supported pusblisher frame table */
        &LIN_frameTable2[0],            /* Pointer to supported suscriber frame table */
        200,                                /* Table total time in ms */
        sizeof(LIN_frameTable1)/sizeof(tLIN_frame_config),    /* Size of the publisher frame configuration table */
        sizeof(LIN_frameTable2)/sizeof(tLIN_frame_config),    /* Size of the suscriber frame configuration table */
          5                                 /* Master table resolution in ms */
    };

    const tLIN_channel_config LIN_channelMaster =
    {
        &LIN_tableMaster,                /* Pointer to LIN configuration table */
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
#endif

#ifdef LIN_NODE_SLAVE
    const tLIN_table_config LIN_tableSlave =
    {
        &LIN_frameTable2[0],            /* Pointer to supported pusblisher frame table */
        &LIN_frameTable1[0],            /* Pointer to supported suscriber frame table */
        200                                /* Table total time in ms */
        sizeof(LIN_frameTable2)/sizeof(tLIN_frame_config),    /* Size of the publisher frame configuration table */
        sizeof(LIN_frameTable1)/sizeof(tLIN_frame_config),    /* Size of the suscriber frame configuration table */
          5                                 /* Master table resolution in ms */
    };

    const tLIN_channel_config LIN_channelSlave =
    {
        &LIN_tableSlave,                /* Pointer to LIN configuration table */
        (tCallbackFunction*)NULL,        /* Pointer to function to be callled upon Wake Up */
        (UINT32)19200,                    /* LIN Baudrate*/
          LIN_1,                            /* LIN Channel ID */
        SCI_CH0,                        /* Low leverl drier SCI channel assigned */
          LIN_slave                         /* Master or Slave */
    };

    const tLIN_driver_config LIN_driverSlave =
    {
        &LIN_channelSlave               /* Pointer to LIN channels configuration */
    };
#endif

/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/


/*****************************************************************************************************
* Code of public FUNCTIONS
*****************************************************************************************************/


/***************************************************************************************************/
</script>
