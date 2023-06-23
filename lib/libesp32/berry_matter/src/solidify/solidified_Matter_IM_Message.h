/* Solidification of Matter_IM_Message.h */
/********************************************************************\
* Generated code, don't edit                                         *
\********************************************************************/
#include "be_constobj.h"
// compact class 'Matter_IM_Message' ktab size: 28, total: 48 (saved 160 bytes)
static const bvalue be_ktab_class_Matter_IM_Message[28] = {
  /* K0   */  be_nested_str_weak(resp),
  /* K1   */  be_nested_str_weak(build_response),
  /* K2   */  be_nested_str_weak(ready),
  /* K3   */  be_nested_str_weak(expiration),
  /* K4   */  be_nested_str_weak(tasmota),
  /* K5   */  be_nested_str_weak(millis),
  /* K6   */  be_nested_str_weak(MSG_TIMEOUT),
  /* K7   */  be_nested_str_weak(last_counter),
  /* K8   */  be_const_int(0),
  /* K9   */  be_nested_str_weak(finishing),
  /* K10  */  be_nested_str_weak(finished),
  /* K11  */  be_nested_str_weak(data),
  /* K12  */  be_nested_str_weak(reset),
  /* K13  */  be_nested_str_weak(to_TLV),
  /* K14  */  be_nested_str_weak(tlv2raw),
  /* K15  */  be_nested_str_weak(encode_frame),
  /* K16  */  be_nested_str_weak(encrypt),
  /* K17  */  be_nested_str_weak(loglevel),
  /* K18  */  be_nested_str_weak(log),
  /* K19  */  be_nested_str_weak(MTR_X3A_X20_X3Csnd_X20_X20_X20_X20_X20_X20_X20_X28_X256i_X29_X20id_X3D_X25s_X20exch_X3D_X25s_X20rack_X3D_X25s),
  /* K20  */  be_nested_str_weak(session),
  /* K21  */  be_nested_str_weak(local_session_id),
  /* K22  */  be_nested_str_weak(message_counter),
  /* K23  */  be_nested_str_weak(exchange_id),
  /* K24  */  be_nested_str_weak(ack_message_counter),
  /* K25  */  be_nested_str_weak(send_response_frame),
  /* K26  */  be_nested_str_weak(opcode),
  /* K27  */  be_nested_str_weak(x_flag_r),
};

extern const bclass be_class_Matter_IM_Message;

/********************************************************************
** Solidified function: status_error_received
********************************************************************/
be_local_closure(Matter_IM_Message_status_error_received,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    2,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    0,                          /* has constants */
    NULL,                       /* no const */
    be_str_weak(status_error_received),
    &be_const_str_solidified,
    ( &(const binstruction[ 1]) {  /* code */
      0x80000000,  //  0000  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: send_im
********************************************************************/
be_local_closure(Matter_IM_Message_send_im,   /* name */
  be_nested_proto(
    11,                          /* nstack */
    2,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[18]) {     /* constants */
    /* K0   */  be_nested_str_weak(ready),
    /* K1   */  be_nested_str_weak(resp),
    /* K2   */  be_nested_str_weak(encode_frame),
    /* K3   */  be_nested_str_weak(data),
    /* K4   */  be_nested_str_weak(to_TLV),
    /* K5   */  be_nested_str_weak(tlv2raw),
    /* K6   */  be_nested_str_weak(encrypt),
    /* K7   */  be_nested_str_weak(tasmota),
    /* K8   */  be_nested_str_weak(log),
    /* K9   */  be_nested_str_weak(MTR_X3A_X20_X3Csnd_X20_X20_X20_X20_X20_X20_X20_X28_X256i_X29_X20id_X3D_X25i_X20exch_X3D_X25i_X20rack_X3D_X25s),
    /* K10  */  be_nested_str_weak(session),
    /* K11  */  be_nested_str_weak(local_session_id),
    /* K12  */  be_nested_str_weak(message_counter),
    /* K13  */  be_nested_str_weak(exchange_id),
    /* K14  */  be_nested_str_weak(ack_message_counter),
    /* K15  */  be_nested_str_weak(send_response_frame),
    /* K16  */  be_nested_str_weak(last_counter),
    /* K17  */  be_nested_str_weak(finish),
    }),
    be_str_weak(send_im),
    &be_const_str_solidified,
    ( &(const binstruction[34]) {  /* code */
      0x88080100,  //  0000  GETMBR	R2	R0	K0
      0x740A0001,  //  0001  JMPT	R2	#0004
      0x50080000,  //  0002  LDBOOL	R2	0	0
      0x80040400,  //  0003  RET	1	R2
      0x88080101,  //  0004  GETMBR	R2	R0	K1
      0x8C0C0502,  //  0005  GETMET	R3	R2	K2
      0x88140103,  //  0006  GETMBR	R5	R0	K3
      0x8C140B04,  //  0007  GETMET	R5	R5	K4
      0x7C140200,  //  0008  CALL	R5	1
      0x8C140B05,  //  0009  GETMET	R5	R5	K5
      0x7C140200,  //  000A  CALL	R5	1
      0x7C0C0400,  //  000B  CALL	R3	2
      0x8C0C0506,  //  000C  GETMET	R3	R2	K6
      0x7C0C0200,  //  000D  CALL	R3	1
      0xB80E0E00,  //  000E  GETNGBL	R3	K7
      0x8C0C0708,  //  000F  GETMET	R3	R3	K8
      0x60140018,  //  0010  GETGBL	R5	G24
      0x58180009,  //  0011  LDCONST	R6	K9
      0x881C050A,  //  0012  GETMBR	R7	R2	K10
      0x881C0F0B,  //  0013  GETMBR	R7	R7	K11
      0x8820050C,  //  0014  GETMBR	R8	R2	K12
      0x8824050D,  //  0015  GETMBR	R9	R2	K13
      0x8828050E,  //  0016  GETMBR	R10	R2	K14
      0x7C140A00,  //  0017  CALL	R5	5
      0x541A0003,  //  0018  LDINT	R6	4
      0x7C0C0600,  //  0019  CALL	R3	3
      0x8C0C030F,  //  001A  GETMET	R3	R1	K15
      0x5C140400,  //  001B  MOVE	R5	R2
      0x7C0C0400,  //  001C  CALL	R3	2
      0x880C050C,  //  001D  GETMBR	R3	R2	K12
      0x90022003,  //  001E  SETMBR	R0	K16	R3
      0x500C0200,  //  001F  LDBOOL	R3	1	0
      0x90022203,  //  0020  SETMBR	R0	K17	R3
      0x80000000,  //  0021  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: get_exchangeid
********************************************************************/
be_local_closure(Matter_IM_Message_get_exchangeid,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    1,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(resp),
    /* K1   */  be_nested_str_weak(exchange_id),
    }),
    be_str_weak(get_exchangeid),
    &be_const_str_solidified,
    ( &(const binstruction[ 3]) {  /* code */
      0x88040100,  //  0000  GETMBR	R1	R0	K0
      0x88040301,  //  0001  GETMBR	R1	R1	K1
      0x80040200,  //  0002  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(class_Matter_IM_Message_init,   /* name */
  be_nested_proto(
    9,                          /* nstack */
    4,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[10]) {     /* constants */
    /* K0   */  be_nested_str_weak(resp),
    /* K1   */  be_nested_str_weak(build_response),
    /* K2   */  be_nested_str_weak(ready),
    /* K3   */  be_nested_str_weak(expiration),
    /* K4   */  be_nested_str_weak(tasmota),
    /* K5   */  be_nested_str_weak(millis),
    /* K6   */  be_nested_str_weak(MSG_TIMEOUT),
    /* K7   */  be_nested_str_weak(last_counter),
    /* K8   */  be_const_int(0),
    /* K9   */  be_nested_str_weak(finish),
    }),
    be_str_weak(init),
    &be_const_str_solidified,
    ( &(const binstruction[17]) {  /* code */
      0x8C100301,  //  0000  GETMET	R4	R1	K1
      0x5C180400,  //  0001  MOVE	R6	R2
      0x5C1C0600,  //  0002  MOVE	R7	R3
      0x7C100600,  //  0003  CALL	R4	3
      0x90020004,  //  0004  SETMBR	R0	K0	R4
      0x50100200,  //  0005  LDBOOL	R4	1	0
      0x90020404,  //  0006  SETMBR	R0	K2	R4
      0xB8120800,  //  0007  GETNGBL	R4	K4
      0x8C100905,  //  0008  GETMET	R4	R4	K5
      0x7C100200,  //  0009  CALL	R4	1
      0x88140106,  //  000A  GETMBR	R5	R0	K6
      0x00100805,  //  000B  ADD	R4	R4	R5
      0x90020604,  //  000C  SETMBR	R0	K3	R4
      0x90020F08,  //  000D  SETMBR	R0	K7	K8
      0x50100000,  //  000E  LDBOOL	R4	0	0
      0x90021204,  //  000F  SETMBR	R0	K9	R4
      0x80000000,  //  0010  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: ack_received
********************************************************************/
be_local_closure(Matter_IM_Message_ack_received,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 4]) {     /* constants */
    /* K0   */  be_nested_str_weak(expiration),
    /* K1   */  be_nested_str_weak(tasmota),
    /* K2   */  be_nested_str_weak(millis),
    /* K3   */  be_nested_str_weak(MSG_TIMEOUT),
    }),
    be_str_weak(ack_received),
    &be_const_str_solidified,
    ( &(const binstruction[ 8]) {  /* code */
      0xB80A0200,  //  0000  GETNGBL	R2	K1
      0x8C080502,  //  0001  GETMET	R2	R2	K2
      0x7C080200,  //  0002  CALL	R2	1
      0x880C0103,  //  0003  GETMBR	R3	R0	K3
      0x00080403,  //  0004  ADD	R2	R2	R3
      0x90020002,  //  0005  SETMBR	R0	K0	R2
      0x50080000,  //  0006  LDBOOL	R2	0	0
      0x80040400,  //  0007  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: get_exchangeid
********************************************************************/
be_local_closure(class_Matter_IM_Message_get_exchangeid,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_Message,     /* shared constants */
    be_str_weak(get_exchangeid),
    &be_const_str_solidified,
    ( &(const binstruction[ 3]) {  /* code */
      0x88040100,  //  0000  GETMBR	R1	R0	K0
      0x88040317,  //  0001  GETMBR	R1	R1	K23
      0x80040200,  //  0002  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: ack_received
********************************************************************/
be_local_closure(class_Matter_IM_Message_ack_received,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_Message,     /* shared constants */
    be_str_weak(ack_received),
    &be_const_str_solidified,
    ( &(const binstruction[13]) {  /* code */
      0x88080109,  //  0000  GETMBR	R2	R0	K9
      0x780A0002,  //  0001  JMPF	R2	#0005
      0x50080200,  //  0002  LDBOOL	R2	1	0
      0x90021402,  //  0003  SETMBR	R0	K10	R2
      0x70020005,  //  0004  JMP		#000B
      0xB80A0800,  //  0005  GETNGBL	R2	K4
      0x8C080505,  //  0006  GETMET	R2	R2	K5
      0x7C080200,  //  0007  CALL	R2	1
      0x880C0106,  //  0008  GETMBR	R3	R0	K6
      0x00080403,  //  0009  ADD	R2	R2	R3
      0x90020602,  //  000A  SETMBR	R0	K3	R2
      0x50080000,  //  000B  LDBOOL	R2	0	0
      0x80040400,  //  000C  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: reached_timeout
********************************************************************/
be_local_closure(class_Matter_IM_Message_reached_timeout,   /* name */
  be_nested_proto(
    1,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_Message,     /* shared constants */
    be_str_weak(reached_timeout),
    &be_const_str_solidified,
    ( &(const binstruction[ 1]) {  /* code */
      0x80000000,  //  0000  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: status_ok_received
********************************************************************/
be_local_closure(class_Matter_IM_Message_status_ok_received,   /* name */
  be_nested_proto(
    7,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 9]) {     /* constants */
    /* K0   */  be_nested_str_weak(expiration),
    /* K1   */  be_nested_str_weak(tasmota),
    /* K2   */  be_nested_str_weak(millis),
    /* K3   */  be_nested_str_weak(MSG_TIMEOUT),
    /* K4   */  be_nested_str_weak(resp),
    /* K5   */  be_nested_str_weak(build_response),
    /* K6   */  be_nested_str_weak(opcode),
    /* K7   */  be_nested_str_weak(x_flag_r),
    /* K8   */  be_nested_str_weak(ready),
    }),
    be_str_weak(status_ok_received),
    &be_const_str_solidified,
    ( &(const binstruction[19]) {  /* code */
      0xB80A0200,  //  0000  GETNGBL	R2	K1
      0x8C080502,  //  0001  GETMET	R2	R2	K2
      0x7C080200,  //  0002  CALL	R2	1
      0x880C0103,  //  0003  GETMBR	R3	R0	K3
      0x00080403,  //  0004  ADD	R2	R2	R3
      0x90020002,  //  0005  SETMBR	R0	K0	R2
      0x78060007,  //  0006  JMPF	R1	#000F
      0x8C080305,  //  0007  GETMET	R2	R1	K5
      0x88100104,  //  0008  GETMBR	R4	R0	K4
      0x88100906,  //  0009  GETMBR	R4	R4	K6
      0x88140104,  //  000A  GETMBR	R5	R0	K4
      0x88140B07,  //  000B  GETMBR	R5	R5	K7
      0x88180104,  //  000C  GETMBR	R6	R0	K4
      0x7C080800,  //  000D  CALL	R2	4
      0x90020802,  //  000E  SETMBR	R0	K4	R2
      0x50080200,  //  000F  LDBOOL	R2	1	0
      0x90021002,  //  0010  SETMBR	R0	K8	R2
      0x50080200,  //  0011  LDBOOL	R2	1	0
      0x80040400,  //  0012  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Matter_IM_Message
********************************************************************/
be_local_class(Matter_IM_Message,
    6,
    NULL,
    be_nested_map(14,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(MSG_TIMEOUT, -1), be_const_int(5000) },
        { be_const_key_weak(data, -1), be_const_var(4) },
        { be_const_key_weak(send_im, -1), be_const_closure(Matter_IM_Message_send_im_closure) },
        { be_const_key_weak(status_ok_received, -1), be_const_closure(Matter_IM_Message_status_ok_received_closure) },
        { be_const_key_weak(get_exchangeid, 0), be_const_closure(Matter_IM_Message_get_exchangeid_closure) },
        { be_const_key_weak(init, -1), be_const_closure(Matter_IM_Message_init_closure) },
        { be_const_key_weak(expiration, -1), be_const_var(0) },
        { be_const_key_weak(resp, -1), be_const_var(1) },
        { be_const_key_weak(finish, 13), be_const_var(3) },
        { be_const_key_weak(last_counter, 6), be_const_var(5) },
        { be_const_key_weak(ack_received, 9), be_const_closure(Matter_IM_Message_ack_received_closure) },
        { be_const_key_weak(reached_timeout, -1), be_const_closure(Matter_IM_Message_reached_timeout_closure) },
        { be_const_key_weak(status_error_received, 3), be_const_closure(Matter_IM_Message_status_error_received_closure) },
        { be_const_key_weak(ready, -1), be_const_var(2) },
    })),
    be_str_weak(Matter_IM_Message)
);

extern const bclass be_class_Matter_IM_Status;

/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(class_Matter_IM_Status_init,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    3,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 6]) {     /* constants */
    /* K0   */  be_nested_str_weak(init),
    /* K1   */  be_const_int(1),
    /* K2   */  be_nested_str_weak(matter),
    /* K3   */  be_nested_str_weak(StatusResponseMessage),
    /* K4   */  be_nested_str_weak(status),
    /* K5   */  be_nested_str_weak(data),
    }),
    be_str_weak(init),
    &be_const_str_solidified,
    ( &(const binstruction[14]) {  /* code */
      0x600C0003,  //  0000  GETGBL	R3	G3
      0x5C100000,  //  0001  MOVE	R4	R0
      0x7C0C0200,  //  0002  CALL	R3	1
      0x8C0C0700,  //  0003  GETMET	R3	R3	K0
      0x5C140200,  //  0004  MOVE	R5	R1
      0x58180001,  //  0005  LDCONST	R6	K1
      0x501C0200,  //  0006  LDBOOL	R7	1	0
      0x7C0C0800,  //  0007  CALL	R3	4
      0xB80E0400,  //  0008  GETNGBL	R3	K2
      0x8C0C0703,  //  0009  GETMET	R3	R3	K3
      0x7C0C0200,  //  000A  CALL	R3	1
      0x900E0802,  //  000B  SETMBR	R3	K4	R2
      0x90020A03,  //  000C  SETMBR	R0	K5	R3
      0x80000000,  //  000D  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Matter_IM_Status
********************************************************************/
extern const bclass be_class_Matter_IM_Message;
be_local_class(Matter_IM_Status,
    0,
    &be_class_Matter_IM_Message,
    be_nested_map(1,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(init, -1), be_const_closure(class_Matter_IM_Status_init_closure) },
    })),
    be_str_weak(Matter_IM_Status)
);

extern const bclass be_class_Matter_IM_InvokeResponse;

/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(class_Matter_IM_InvokeResponse_init,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    3,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(init),
    /* K1   */  be_nested_str_weak(data),
    }),
    be_str_weak(init),
    &be_const_str_solidified,
    ( &(const binstruction[10]) {  /* code */
      0x600C0003,  //  0000  GETGBL	R3	G3
      0x5C100000,  //  0001  MOVE	R4	R0
      0x7C0C0200,  //  0002  CALL	R3	1
      0x8C0C0700,  //  0003  GETMET	R3	R3	K0
      0x5C140200,  //  0004  MOVE	R5	R1
      0x541A0008,  //  0005  LDINT	R6	9
      0x501C0200,  //  0006  LDBOOL	R7	1	0
      0x7C0C0800,  //  0007  CALL	R3	4
      0x90020202,  //  0008  SETMBR	R0	K1	R2
      0x80000000,  //  0009  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Matter_IM_InvokeResponse
********************************************************************/
extern const bclass be_class_Matter_IM_Message;
be_local_class(Matter_IM_InvokeResponse,
    0,
    &be_class_Matter_IM_Message,
    be_nested_map(1,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(init, -1), be_const_closure(class_Matter_IM_InvokeResponse_init_closure) },
    })),
    be_str_weak(Matter_IM_InvokeResponse)
);

extern const bclass be_class_Matter_IM_WriteResponse;

/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(class_Matter_IM_WriteResponse_init,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    3,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(init),
    /* K1   */  be_nested_str_weak(data),
    }),
    be_str_weak(init),
    &be_const_str_solidified,
    ( &(const binstruction[10]) {  /* code */
      0x600C0003,  //  0000  GETGBL	R3	G3
      0x5C100000,  //  0001  MOVE	R4	R0
      0x7C0C0200,  //  0002  CALL	R3	1
      0x8C0C0700,  //  0003  GETMET	R3	R3	K0
      0x5C140200,  //  0004  MOVE	R5	R1
      0x541A0006,  //  0005  LDINT	R6	7
      0x501C0200,  //  0006  LDBOOL	R7	1	0
      0x7C0C0800,  //  0007  CALL	R3	4
      0x90020202,  //  0008  SETMBR	R0	K1	R2
      0x80000000,  //  0009  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Matter_IM_WriteResponse
********************************************************************/
extern const bclass be_class_Matter_IM_Message;
be_local_class(Matter_IM_WriteResponse,
    0,
    &be_class_Matter_IM_Message,
    be_nested_map(1,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(init, -1), be_const_closure(class_Matter_IM_WriteResponse_init_closure) },
    })),
    be_str_weak(Matter_IM_WriteResponse)
);
// compact class 'Matter_IM_ReportData_Pull' ktab size: 51, total: 57 (saved 48 bytes)
static const bvalue be_ktab_class_Matter_IM_ReportData_Pull[51] = {
  /* K0   */  be_nested_str_weak(resp),
  /* K1   */  be_nested_str_weak(data),
  /* K2   */  be_nested_str_weak(device),
  /* K3   */  be_nested_str_weak(debug),
  /* K4   */  be_nested_str_weak(data_ev),
  /* K5   */  be_nested_str_weak(event_generator_or_arr),
  /* K6   */  be_nested_str_weak(generator_or_arr),
  /* K7   */  be_const_int(0),
  /* K8   */  be_nested_str_weak(next_attribute),
  /* K9   */  be_nested_str_weak(is_direct),
  /* K10  */  be_nested_str_weak(im),
  /* K11  */  be_nested_str_weak(read_single_attribute_to_bytes),
  /* K12  */  be_nested_str_weak(get_pi),
  /* K13  */  be_nested_str_weak(session),
  /* K14  */  be_nested_str_weak(MAX_MESSAGE),
  /* K15  */  be_nested_str_weak(append),
  /* K16  */  be_nested_str_weak(remove),
  /* K17  */  be_nested_str_weak(next_event),
  /* K18  */  be_nested_str_weak(tasmota),
  /* K19  */  be_nested_str_weak(loglevel),
  /* K20  */  be_const_int(3),
  /* K21  */  be_nested_str_weak(),
  /* K22  */  be_nested_str_weak(data0),
  /* K23  */  be_nested_str_weak(_X20_X2D_X20),
  /* K24  */  be_nested_str_weak(data1),
  /* K25  */  be_nested_str_weak(_X2C_X20),
  /* K26  */  be_nested_str_weak(data2),
  /* K27  */  be_nested_str_weak(log),
  /* K28  */  be_nested_str_weak(MTR_X3A_X20_X3ERead_Event_X28_X256i_X7C_X258s_X29_X20_X5B_X2502X_X5D_X2504X_X2F_X2502X_X25s),
  /* K29  */  be_nested_str_weak(local_session_id),
  /* K30  */  be_nested_str_weak(event_no),
  /* K31  */  be_nested_str_weak(endpoint),
  /* K32  */  be_nested_str_weak(cluster),
  /* K33  */  be_nested_str_weak(event_id),
  /* K34  */  be_nested_str_weak(to_raw_bytes),
  /* K35  */  be_nested_str_weak(add),
  /* K36  */  be_const_int(1),
  /* K37  */  be_nested_str_weak(subscription_id),
  /* K38  */  be_const_int(2),
  /* K39  */  be_nested_str_weak(suppress_response),
  /* K40  */  be_nested_str_weak(encode_frame),
  /* K41  */  be_nested_str_weak(encrypt),
  /* K42  */  be_nested_str_weak(send_response_frame),
  /* K43  */  be_nested_str_weak(last_counter),
  /* K44  */  be_nested_str_weak(message_counter),
  /* K45  */  be_nested_str_weak(ready),
  /* K46  */  be_nested_str_weak(finishing),
  /* K47  */  be_nested_str_weak(status_ok_received),
  /* K48  */  be_nested_str_weak(_message_handler),
  /* K49  */  be_nested_str_weak(send_encrypted_ack),
  /* K50  */  be_nested_str_weak(init),
};


extern const bclass be_class_Matter_IM_ReportData_Pull;

/********************************************************************
** Solidified function: send_im
********************************************************************/
be_local_closure(class_Matter_IM_ReportData_Pull_send_im,   /* name */
  be_nested_proto(
    12,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[17]) {     /* constants */
    /* K0   */  be_nested_str_weak(ready),
    /* K1   */  be_nested_str_weak(resp),
    /* K2   */  be_nested_str_weak(data),
    /* K3   */  be_nested_str_weak(more_chunked_messages),
    /* K4   */  be_const_int(1),
    /* K5   */  be_nested_str_weak(attribute_reports),
    /* K6   */  be_const_int(2147483647),
    /* K7   */  be_const_int(0),
    /* K8   */  be_nested_str_weak(to_TLV),
    /* K9   */  be_nested_str_weak(tlv2raw),
    /* K10  */  be_nested_str_weak(MAX_MESSAGE),
    /* K11  */  be_nested_str_weak(encode_frame),
    /* K12  */  be_nested_str_weak(encrypt),
    /* K13  */  be_nested_str_weak(send_response_frame),
    /* K14  */  be_nested_str_weak(last_counter),
    /* K15  */  be_nested_str_weak(message_counter),
    /* K16  */  be_nested_str_weak(finish),
    }),
    be_str_weak(send_im),
    &be_const_str_solidified,
    ( &(const binstruction[67]) {  /* code */
      0x88080100,  //  0000  GETMBR	R2	R0	K0
      0x740A0001,  //  0001  JMPT	R2	#0004
      0x50080000,  //  0002  LDBOOL	R2	0	0
      0x80040400,  //  0003  RET	1	R2
      0x88080101,  //  0004  GETMBR	R2	R0	K1
      0x880C0102,  //  0005  GETMBR	R3	R0	K2
      0x88100703,  //  0006  GETMBR	R4	R3	K3
      0x58140004,  //  0007  LDCONST	R5	K4
      0x4C180000,  //  0008  LDNIL	R6
      0x881C0705,  //  0009  GETMBR	R7	R3	K5
      0x4C200000,  //  000A  LDNIL	R8
      0x201C0E08,  //  000B  NE	R7	R7	R8
      0x781E000D,  //  000C  JMPF	R7	#001B
      0x401C0B06,  //  000D  CONNECT	R7	R5	K6
      0x88200705,  //  000E  GETMBR	R8	R3	K5
      0x94181007,  //  000F  GETIDX	R6	R8	R7
      0x04240B04,  //  0010  SUB	R9	R5	K4
      0x40260E09,  //  0011  CONNECT	R9	K7	R9
      0x88280705,  //  0012  GETMBR	R10	R3	K5
      0x94241409,  //  0013  GETIDX	R9	R10	R9
      0x900E0A09,  //  0014  SETMBR	R3	K5	R9
      0x6024000C,  //  0015  GETGBL	R9	G12
      0x5C280C00,  //  0016  MOVE	R10	R6
      0x7C240200,  //  0017  CALL	R9	1
      0x24241307,  //  0018  GT	R9	R9	K7
      0x900E0609,  //  0019  SETMBR	R3	K3	R9
      0x70020001,  //  001A  JMP		#001D
      0x501C0000,  //  001B  LDBOOL	R7	0	0
      0x900E0607,  //  001C  SETMBR	R3	K3	R7
      0x7811FFFF,  //  001D  JMPF	R4	#001E
      0x881C0703,  //  001E  GETMBR	R7	R3	K3
      0x781E0001,  //  001F  JMPF	R7	#0022
      0x5C1C0800,  //  0020  MOVE	R7	R4
      0x741DFFFF,  //  0021  JMPT	R7	#0022
      0x881C0102,  //  0022  GETMBR	R7	R0	K2
      0x8C1C0F08,  //  0023  GETMET	R7	R7	K8
      0x7C1C0200,  //  0024  CALL	R7	1
      0x8C200F09,  //  0025  GETMET	R8	R7	K9
      0x60280015,  //  0026  GETGBL	R10	G21
      0x882C010A,  //  0027  GETMBR	R11	R0	K10
      0x7C280200,  //  0028  CALL	R10	1
      0x7C200400,  //  0029  CALL	R8	2
      0x8C24050B,  //  002A  GETMET	R9	R2	K11
      0x5C2C1000,  //  002B  MOVE	R11	R8
      0x7C240400,  //  002C  CALL	R9	2
      0x8C24050C,  //  002D  GETMET	R9	R2	K12
      0x7C240200,  //  002E  CALL	R9	1
      0x8C24030D,  //  002F  GETMET	R9	R1	K13
      0x5C2C0400,  //  0030  MOVE	R11	R2
      0x7C240400,  //  0031  CALL	R9	2
      0x8824050F,  //  0032  GETMBR	R9	R2	K15
      0x90021C09,  //  0033  SETMBR	R0	K14	R9
      0x4C240000,  //  0034  LDNIL	R9
      0x20240C09,  //  0035  NE	R9	R6	R9
      0x78260008,  //  0036  JMPF	R9	#0040
      0x6024000C,  //  0037  GETGBL	R9	G12
      0x5C280C00,  //  0038  MOVE	R10	R6
      0x7C240200,  //  0039  CALL	R9	1
      0x24241307,  //  003A  GT	R9	R9	K7
      0x78260003,  //  003B  JMPF	R9	#0040
      0x900E0A06,  //  003C  SETMBR	R3	K5	R6
      0x50240000,  //  003D  LDBOOL	R9	0	0
      0x90020009,  //  003E  SETMBR	R0	K0	R9
      0x70020001,  //  003F  JMP		#0042
      0x50240200,  //  0040  LDBOOL	R9	1	0
      0x90022009,  //  0041  SETMBR	R0	K16	R9
      0x80000000,  //  0042  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(class_Matter_IM_ReportData_Pull_init,   /* name */
  be_nested_proto(
    9,                          /* nstack */
    4,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_ReportData_Pull,     /* shared constants */
    be_str_weak(init),
    &be_const_str_solidified,
    ( &(const binstruction[11]) {  /* code */
      0x60100003,  //  0000  GETGBL	R4	G3
      0x5C140000,  //  0001  MOVE	R5	R0
      0x7C100200,  //  0002  CALL	R4	1
      0x8C100932,  //  0003  GETMET	R4	R4	K50
      0x5C180200,  //  0004  MOVE	R6	R1
      0x541E0004,  //  0005  LDINT	R7	5
      0x50200200,  //  0006  LDBOOL	R8	1	0
      0x7C100800,  //  0007  CALL	R4	4
      0x90020C02,  //  0008  SETMBR	R0	K6	R2
      0x90020A03,  //  0009  SETMBR	R0	K5	R3
      0x80000000,  //  000A  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Matter_IM_ReportData_Pull
********************************************************************/
extern const bclass be_class_Matter_IM_Message;
be_local_class(Matter_IM_ReportData_Pull,
    5,
    &be_class_Matter_IM_Message,
    be_nested_map(11,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(send_im, -1), be_const_closure(class_Matter_IM_ReportData_Pull_send_im_closure) },
        { be_const_key_weak(status_ok_received, -1), be_const_closure(class_Matter_IM_ReportData_Pull_status_ok_received_closure) },
        { be_const_key_weak(data_ev, -1), be_const_var(4) },
        { be_const_key_weak(suppress_response, 8), be_const_var(3) },
        { be_const_key_weak(MAX_MESSAGE, -1), be_const_int(1200) },
        { be_const_key_weak(set_suppress_response, -1), be_const_closure(class_Matter_IM_ReportData_Pull_set_suppress_response_closure) },
        { be_const_key_weak(set_subscription_id, -1), be_const_closure(class_Matter_IM_ReportData_Pull_set_subscription_id_closure) },
        { be_const_key_weak(generator_or_arr, 5), be_const_var(0) },
        { be_const_key_weak(event_generator_or_arr, 4), be_const_var(1) },
        { be_const_key_weak(init, -1), be_const_closure(class_Matter_IM_ReportData_Pull_init_closure) },
        { be_const_key_weak(subscription_id, -1), be_const_var(2) },
    })),
    be_str_weak(Matter_IM_ReportData_Pull)
);
// compact class 'Matter_IM_ReportDataSubscribed_Pull' ktab size: 34, total: 46 (saved 96 bytes)
static const bvalue be_ktab_class_Matter_IM_ReportDataSubscribed_Pull[34] = {
  /* K0   */  be_nested_str_weak(ack_received),
  /* K1   */  be_nested_str_weak(report_data_phase),
  /* K2   */  be_nested_str_weak(sub),
  /* K3   */  be_nested_str_weak(is_keep_alive),
  /* K4   */  be_nested_str_weak(re_arm),
  /* K5   */  be_nested_str_weak(ready),
  /* K6   */  be_nested_str_weak(generator_or_arr),
  /* K7   */  be_nested_str_weak(event_generator_or_arr),
  /* K8   */  be_nested_str_weak(send_im),
  /* K9   */  be_nested_str_weak(finishing),
  /* K10  */  be_nested_str_weak(finished),
  /* K11  */  be_nested_str_weak(resp),
  /* K12  */  be_nested_str_weak(build_standalone_ack),
  /* K13  */  be_nested_str_weak(encode_frame),
  /* K14  */  be_nested_str_weak(encrypt),
  /* K15  */  be_nested_str_weak(tasmota),
  /* K16  */  be_nested_str_weak(loglevel),
  /* K17  */  be_nested_str_weak(log),
  /* K18  */  be_nested_str_weak(MTR_X3A_X20_X3CAck_X20_X20_X20_X20_X20_X20_X20_X28_X256i_X29_X20ack_X3D_X25i_X20id_X3D_X25i),
  /* K19  */  be_nested_str_weak(session),
  /* K20  */  be_nested_str_weak(local_session_id),
  /* K21  */  be_nested_str_weak(ack_message_counter),
  /* K22  */  be_nested_str_weak(message_counter),
  /* K23  */  be_nested_str_weak(send_response_frame),
  /* K24  */  be_nested_str_weak(last_counter),
  /* K25  */  be_nested_str_weak(init),
  /* K26  */  be_nested_str_weak(matter),
  /* K27  */  be_nested_str_weak(Frame),
  /* K28  */  be_nested_str_weak(initiate_response),
  /* K29  */  be_nested_str_weak(set_subscription_id),
  /* K30  */  be_nested_str_weak(subscription_id),
  /* K31  */  be_nested_str_weak(set_suppress_response),
  /* K32  */  be_nested_str_weak(remove_self),
  /* K33  */  be_nested_str_weak(status_ok_received),
};


extern const bclass be_class_Matter_IM_ReportDataSubscribed_Pull;

/********************************************************************
** Solidified function: ack_received
********************************************************************/
be_local_closure(class_Matter_IM_ReportDataSubscribed_Pull_ack_received,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 5]) {     /* constants */
    /* K0   */  be_nested_str_weak(ack_received),
    /* K1   */  be_nested_str_weak(report_data_phase),
    /* K2   */  be_nested_str_weak(sub),
    /* K3   */  be_nested_str_weak(is_keep_alive),
    /* K4   */  be_nested_str_weak(re_arm),
    }),
    be_str_weak(ack_received),
    &be_const_str_solidified,
    ( &(const binstruction[20]) {  /* code */
      0x60080003,  //  0000  GETGBL	R2	G3
      0x5C0C0000,  //  0001  MOVE	R3	R0
      0x7C080200,  //  0002  CALL	R2	1
      0x8C080500,  //  0003  GETMET	R2	R2	K0
      0x5C100200,  //  0004  MOVE	R4	R1
      0x7C080400,  //  0005  CALL	R2	2
      0x88080101,  //  0006  GETMBR	R2	R0	K1
      0x740A0008,  //  0007  JMPT	R2	#0011
      0x88080102,  //  0008  GETMBR	R2	R0	K2
      0x88080503,  //  0009  GETMBR	R2	R2	K3
      0x780A0002,  //  000A  JMPF	R2	#000E
      0x88080102,  //  000B  GETMBR	R2	R0	K2
      0x8C080504,  //  000C  GETMET	R2	R2	K4
      0x7C080200,  //  000D  CALL	R2	1
      0x50080200,  //  000E  LDBOOL	R2	1	0
      0x80040400,  //  000F  RET	1	R2
      0x70020001,  //  0010  JMP		#0013
      0x50080000,  //  0011  LDBOOL	R2	0	0
      0x80040400,  //  0012  RET	1	R2
      0x80000000,  //  0013  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: send_im
********************************************************************/
be_local_closure(class_Matter_IM_ReportDataSubscribed_Pull_send_im,   /* name */
  be_nested_proto(
    10,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[20]) {     /* constants */
    /* K0   */  be_nested_str_weak(ready),
    /* K1   */  be_nested_str_weak(data),
    /* K2   */  be_nested_str_weak(attribute_reports),
    /* K3   */  be_const_int(0),
    /* K4   */  be_nested_str_weak(report_data_phase),
    /* K5   */  be_nested_str_weak(send_im),
    /* K6   */  be_nested_str_weak(finish),
    /* K7   */  be_nested_str_weak(resp),
    /* K8   */  be_nested_str_weak(build_standalone_ack),
    /* K9   */  be_nested_str_weak(encode_frame),
    /* K10  */  be_nested_str_weak(encrypt),
    /* K11  */  be_nested_str_weak(tasmota),
    /* K12  */  be_nested_str_weak(log),
    /* K13  */  be_nested_str_weak(MTR_X3A_X20_X3CAck_X20_X20_X20_X20_X20_X20_X20_X28_X256i_X29_X20ack_X3D_X25i_X20id_X3D_X25i),
    /* K14  */  be_nested_str_weak(session),
    /* K15  */  be_nested_str_weak(local_session_id),
    /* K16  */  be_nested_str_weak(ack_message_counter),
    /* K17  */  be_nested_str_weak(message_counter),
    /* K18  */  be_nested_str_weak(send_response_frame),
    /* K19  */  be_nested_str_weak(last_counter),
    }),
    be_str_weak(send_im),
    &be_const_str_solidified,
    ( &(const binstruction[69]) {  /* code */
      0x88080100,  //  0000  GETMBR	R2	R0	K0
      0x740A0001,  //  0001  JMPT	R2	#0004
      0x50080000,  //  0002  LDBOOL	R2	0	0
      0x80040400,  //  0003  RET	1	R2
      0x6008000C,  //  0004  GETGBL	R2	G12
      0x880C0101,  //  0005  GETMBR	R3	R0	K1
      0x880C0702,  //  0006  GETMBR	R3	R3	K2
      0x7C080200,  //  0007  CALL	R2	1
      0x24080503,  //  0008  GT	R2	R2	K3
      0x780A002C,  //  0009  JMPF	R2	#0037
      0x88080104,  //  000A  GETMBR	R2	R0	K4
      0x780A000F,  //  000B  JMPF	R2	#001C
      0x60080003,  //  000C  GETGBL	R2	G3
      0x5C0C0000,  //  000D  MOVE	R3	R0
      0x7C080200,  //  000E  CALL	R2	1
      0x8C080505,  //  000F  GETMET	R2	R2	K5
      0x5C100200,  //  0010  MOVE	R4	R1
      0x7C080400,  //  0011  CALL	R2	2
      0x88080106,  //  0012  GETMBR	R2	R0	K6
      0x740A0000,  //  0013  JMPT	R2	#0015
      0x80000400,  //  0014  RET	0
      0x50080000,  //  0015  LDBOOL	R2	0	0
      0x90020802,  //  0016  SETMBR	R0	K4	R2
      0x50080000,  //  0017  LDBOOL	R2	0	0
      0x90020002,  //  0018  SETMBR	R0	K0	R2
      0x50080000,  //  0019  LDBOOL	R2	0	0
      0x90020C02,  //  001A  SETMBR	R0	K6	R2
      0x70020019,  //  001B  JMP		#0036
      0x88080107,  //  001C  GETMBR	R2	R0	K7
      0x8C080508,  //  001D  GETMET	R2	R2	K8
      0x50100000,  //  001E  LDBOOL	R4	0	0
      0x7C080400,  //  001F  CALL	R2	2
      0x8C0C0509,  //  0020  GETMET	R3	R2	K9
      0x7C0C0200,  //  0021  CALL	R3	1
      0x8C0C050A,  //  0022  GETMET	R3	R2	K10
      0x7C0C0200,  //  0023  CALL	R3	1
      0xB80E1600,  //  0024  GETNGBL	R3	K11
      0x8C0C070C,  //  0025  GETMET	R3	R3	K12
      0x60140018,  //  0026  GETGBL	R5	G24
      0x5818000D,  //  0027  LDCONST	R6	K13
      0x881C050E,  //  0028  GETMBR	R7	R2	K14
      0x881C0F0F,  //  0029  GETMBR	R7	R7	K15
      0x88200510,  //  002A  GETMBR	R8	R2	K16
      0x88240511,  //  002B  GETMBR	R9	R2	K17
      0x7C140800,  //  002C  CALL	R5	4
      0x541A0003,  //  002D  LDINT	R6	4
      0x7C0C0600,  //  002E  CALL	R3	3
      0x8C0C0312,  //  002F  GETMET	R3	R1	K18
      0x5C140400,  //  0030  MOVE	R5	R2
      0x7C0C0400,  //  0031  CALL	R3	2
      0x880C0511,  //  0032  GETMBR	R3	R2	K17
      0x90022603,  //  0033  SETMBR	R0	K19	R3
      0x500C0200,  //  0034  LDBOOL	R3	1	0
      0x90020C03,  //  0035  SETMBR	R0	K6	R3
      0x7002000C,  //  0036  JMP		#0044
      0x88080104,  //  0037  GETMBR	R2	R0	K4
      0x780A0008,  //  0038  JMPF	R2	#0042
      0x60080003,  //  0039  GETGBL	R2	G3
      0x5C0C0000,  //  003A  MOVE	R3	R0
      0x7C080200,  //  003B  CALL	R2	1
      0x8C080505,  //  003C  GETMET	R2	R2	K5
      0x5C100200,  //  003D  MOVE	R4	R1
      0x7C080400,  //  003E  CALL	R2	2
      0x50080000,  //  003F  LDBOOL	R2	0	0
      0x90020802,  //  0040  SETMBR	R0	K4	R2
      0x70020001,  //  0041  JMP		#0044
      0x50080200,  //  0042  LDBOOL	R2	1	0
      0x90020C02,  //  0043  SETMBR	R0	K6	R2
      0x80000000,  //  0044  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(class_Matter_IM_ReportDataSubscribed_Pull_init,   /* name */
  be_nested_proto(
    12,                          /* nstack */
    6,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_ReportDataSubscribed_Pull,     /* shared constants */
    be_str_weak(init),
    &be_const_str_solidified,
    ( &(const binstruction[27]) {  /* code */
      0x60180003,  //  0000  GETGBL	R6	G3
      0x5C1C0000,  //  0001  MOVE	R7	R0
      0x7C180200,  //  0002  CALL	R6	1
      0x8C180D19,  //  0003  GETMET	R6	R6	K25
      0x4C200000,  //  0004  LDNIL	R8
      0x5C240600,  //  0005  MOVE	R9	R3
      0x5C280800,  //  0006  MOVE	R10	R4
      0x7C180800,  //  0007  CALL	R6	4
      0xB81A3400,  //  0008  GETNGBL	R6	K26
      0x88180D1B,  //  0009  GETMBR	R6	R6	K27
      0x8C180D1C,  //  000A  GETMET	R6	R6	K28
      0x5C200200,  //  000B  MOVE	R8	R1
      0x5C240400,  //  000C  MOVE	R9	R2
      0x542A0004,  //  000D  LDINT	R10	5
      0x502C0200,  //  000E  LDBOOL	R11	1	0
      0x7C180A00,  //  000F  CALL	R6	5
      0x90021606,  //  0010  SETMBR	R0	K11	R6
      0x90020405,  //  0011  SETMBR	R0	K2	R5
      0x50180200,  //  0012  LDBOOL	R6	1	0
      0x90020206,  //  0013  SETMBR	R0	K1	R6
      0x8C18011D,  //  0014  GETMET	R6	R0	K29
      0x88200B1E,  //  0015  GETMBR	R8	R5	K30
      0x7C180400,  //  0016  CALL	R6	2
      0x8C18011F,  //  0017  GETMET	R6	R0	K31
      0x50200000,  //  0018  LDBOOL	R8	0	0
      0x7C180400,  //  0019  CALL	R6	2
      0x80000000,  //  001A  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: status_error_received
********************************************************************/
be_local_closure(class_Matter_IM_ReportDataSubscribed_Pull_status_error_received,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(sub),
    /* K1   */  be_nested_str_weak(remove_self),
    }),
    be_str_weak(status_error_received),
    &be_const_str_solidified,
    ( &(const binstruction[ 4]) {  /* code */
      0x88080100,  //  0000  GETMBR	R2	R0	K0
      0x8C080501,  //  0001  GETMET	R2	R2	K1
      0x7C080200,  //  0002  CALL	R2	1
      0x80000000,  //  0003  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: reached_timeout
********************************************************************/
be_local_closure(class_Matter_IM_ReportDataSubscribed_Pull_reached_timeout,   /* name */
  be_nested_proto(
    3,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_ReportDataSubscribed_Pull,     /* shared constants */
    be_str_weak(reached_timeout),
    &be_const_str_solidified,
    ( &(const binstruction[ 4]) {  /* code */
      0x88040102,  //  0000  GETMBR	R1	R0	K2
      0x8C040320,  //  0001  GETMET	R1	R1	K32
      0x7C040200,  //  0002  CALL	R1	1
      0x80000000,  //  0003  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: status_ok_received
********************************************************************/
be_local_closure(class_Matter_IM_ReportDataSubscribed_Pull_status_ok_received,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_ReportDataSubscribed_Pull,     /* shared constants */
    be_str_weak(status_ok_received),
    &be_const_str_solidified,
    ( &(const binstruction[22]) {  /* code */
      0x88080101,  //  0000  GETMBR	R2	R0	K1
      0x780A0007,  //  0001  JMPF	R2	#000A
      0x60080003,  //  0002  GETGBL	R2	G3
      0x5C0C0000,  //  0003  MOVE	R3	R0
      0x7C080200,  //  0004  CALL	R2	1
      0x8C080521,  //  0005  GETMET	R2	R2	K33
      0x5C100200,  //  0006  MOVE	R4	R1
      0x7C080400,  //  0007  CALL	R2	2
      0x80040400,  //  0008  RET	1	R2
      0x7002000A,  //  0009  JMP		#0015
      0x88080102,  //  000A  GETMBR	R2	R0	K2
      0x8C080504,  //  000B  GETMET	R2	R2	K4
      0x7C080200,  //  000C  CALL	R2	1
      0x60080003,  //  000D  GETGBL	R2	G3
      0x5C0C0000,  //  000E  MOVE	R3	R0
      0x7C080200,  //  000F  CALL	R2	1
      0x8C080521,  //  0010  GETMET	R2	R2	K33
      0x4C100000,  //  0011  LDNIL	R4
      0x7C080400,  //  0012  CALL	R2	2
      0x50080000,  //  0013  LDBOOL	R2	0	0
      0x80040400,  //  0014  RET	1	R2
      0x80000000,  //  0015  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Matter_IM_ReportDataSubscribed_Pull
********************************************************************/
extern const bclass be_class_Matter_IM_ReportData_Pull;
be_local_class(Matter_IM_ReportDataSubscribed_Pull,
    2,
    &be_class_Matter_IM_ReportData_Pull,
    be_nested_map(8,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(ack_received, 1), be_const_closure(class_Matter_IM_ReportDataSubscribed_Pull_ack_received_closure) },
        { be_const_key_weak(status_ok_received, -1), be_const_closure(class_Matter_IM_ReportDataSubscribed_Pull_status_ok_received_closure) },
        { be_const_key_weak(send_im, -1), be_const_closure(class_Matter_IM_ReportDataSubscribed_Pull_send_im_closure) },
        { be_const_key_weak(init, -1), be_const_closure(class_Matter_IM_ReportDataSubscribed_Pull_init_closure) },
        { be_const_key_weak(report_data_phase, 7), be_const_var(1) },
        { be_const_key_weak(sub, 6), be_const_var(0) },
        { be_const_key_weak(reached_timeout, -1), be_const_closure(class_Matter_IM_ReportDataSubscribed_Pull_reached_timeout_closure) },
        { be_const_key_weak(status_error_received, -1), be_const_closure(class_Matter_IM_ReportDataSubscribed_Pull_status_error_received_closure) },
    })),
    be_str_weak(Matter_IM_ReportDataSubscribed_Pull)
);
// compact class 'Matter_IM_SubscribedHeartbeat' ktab size: 13, total: 16 (saved 24 bytes)
static const bvalue be_ktab_class_Matter_IM_SubscribedHeartbeat[13] = {
  /* K0   */  be_nested_str_weak(sub),
  /* K1   */  be_nested_str_weak(remove_self),
  /* K2   */  be_nested_str_weak(send_im),
  /* K3   */  be_nested_str_weak(ready),
  /* K4   */  be_nested_str_weak(ack_received),
  /* K5   */  be_nested_str_weak(init),
  /* K6   */  be_nested_str_weak(resp),
  /* K7   */  be_nested_str_weak(matter),
  /* K8   */  be_nested_str_weak(Frame),
  /* K9   */  be_nested_str_weak(initiate_response),
  /* K10  */  be_nested_str_weak(set_subscription_id),
  /* K11  */  be_nested_str_weak(subscription_id),
  /* K12  */  be_nested_str_weak(set_suppress_response),
};


extern const bclass be_class_Matter_IM_SubscribedHeartbeat;

/********************************************************************
** Solidified function: status_error_received
********************************************************************/
be_local_closure(class_Matter_IM_SubscribedHeartbeat_status_error_received,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_SubscribedHeartbeat,     /* shared constants */
    be_str_weak(status_error_received),
    &be_const_str_solidified,
    ( &(const binstruction[ 5]) {  /* code */
      0x88080100,  //  0000  GETMBR	R2	R0	K0
      0x8C080501,  //  0001  GETMET	R2	R2	K1
      0x7C080200,  //  0002  CALL	R2	1
      0x50080000,  //  0003  LDBOOL	R2	0	0
      0x80040400,  //  0004  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: send_im
********************************************************************/
be_local_closure(class_Matter_IM_SubscribedHeartbeat_send_im,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_SubscribedHeartbeat,     /* shared constants */
    be_str_weak(send_im),
    &be_const_str_solidified,
    ( &(const binstruction[ 9]) {  /* code */
      0x60080003,  //  0000  GETGBL	R2	G3
      0x5C0C0000,  //  0001  MOVE	R3	R0
      0x7C080200,  //  0002  CALL	R2	1
      0x8C080502,  //  0003  GETMET	R2	R2	K2
      0x5C100200,  //  0004  MOVE	R4	R1
      0x7C080400,  //  0005  CALL	R2	2
      0x50080000,  //  0006  LDBOOL	R2	0	0
      0x90020602,  //  0007  SETMBR	R0	K3	R2
      0x80000000,  //  0008  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: ack_received
********************************************************************/
be_local_closure(class_Matter_IM_SubscribedHeartbeat_ack_received,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_SubscribedHeartbeat,     /* shared constants */
    be_str_weak(ack_received),
    &be_const_str_solidified,
    ( &(const binstruction[ 8]) {  /* code */
      0x60080003,  //  0000  GETGBL	R2	G3
      0x5C0C0000,  //  0001  MOVE	R3	R0
      0x7C080200,  //  0002  CALL	R2	1
      0x8C080504,  //  0003  GETMET	R2	R2	K4
      0x5C100200,  //  0004  MOVE	R4	R1
      0x7C080400,  //  0005  CALL	R2	2
      0x50080000,  //  0006  LDBOOL	R2	0	0
      0x80040400,  //  0007  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: reached_timeout
********************************************************************/
be_local_closure(class_Matter_IM_SubscribedHeartbeat_reached_timeout,   /* name */
  be_nested_proto(
    3,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_SubscribedHeartbeat,     /* shared constants */
    be_str_weak(reached_timeout),
    &be_const_str_solidified,
    ( &(const binstruction[ 4]) {  /* code */
      0x88040100,  //  0000  GETMBR	R1	R0	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x7C040200,  //  0002  CALL	R1	1
      0x80000000,  //  0003  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: status_ok_received
********************************************************************/
be_local_closure(class_Matter_IM_SubscribedHeartbeat_status_ok_received,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 4]) {     /* constants */
    /* K0   */  be_nested_str_weak(report_data_phase),
    /* K1   */  be_nested_str_weak(status_ok_received),
    /* K2   */  be_nested_str_weak(sub),
    /* K3   */  be_nested_str_weak(re_arm),
    }),
    be_str_weak(status_ok_received),
    &be_const_str_solidified,
    ( &(const binstruction[22]) {  /* code */
      0x88080100,  //  0000  GETMBR	R2	R0	K0
      0x780A0007,  //  0001  JMPF	R2	#000A
      0x60080003,  //  0002  GETGBL	R2	G3
      0x5C0C0000,  //  0003  MOVE	R3	R0
      0x7C080200,  //  0004  CALL	R2	1
      0x8C080501,  //  0005  GETMET	R2	R2	K1
      0x5C100200,  //  0006  MOVE	R4	R1
      0x7C080400,  //  0007  CALL	R2	2
      0x80040400,  //  0008  RET	1	R2
      0x7002000A,  //  0009  JMP		#0015
      0x88080102,  //  000A  GETMBR	R2	R0	K2
      0x8C080503,  //  000B  GETMET	R2	R2	K3
      0x7C080200,  //  000C  CALL	R2	1
      0x60080003,  //  000D  GETGBL	R2	G3
      0x5C0C0000,  //  000E  MOVE	R3	R0
      0x7C080200,  //  000F  CALL	R2	1
      0x8C080501,  //  0010  GETMET	R2	R2	K1
      0x4C100000,  //  0011  LDNIL	R4
      0x7C080400,  //  0012  CALL	R2	2
      0x50080000,  //  0013  LDBOOL	R2	0	0
      0x80040400,  //  0014  RET	1	R2
      0x80000000,  //  0015  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Matter_IM_ReportDataSubscribed
********************************************************************/
extern const bclass be_class_Matter_IM_ReportData;
be_local_class(Matter_IM_ReportDataSubscribed,
    2,
    &be_class_Matter_IM_ReportData,
    be_nested_map(8,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(ack_received, 1), be_const_closure(Matter_IM_ReportDataSubscribed_ack_received_closure) },
        { be_const_key_weak(status_ok_received, -1), be_const_closure(Matter_IM_ReportDataSubscribed_status_ok_received_closure) },
        { be_const_key_weak(send_im, -1), be_const_closure(Matter_IM_ReportDataSubscribed_send_im_closure) },
        { be_const_key_weak(init, -1), be_const_closure(Matter_IM_ReportDataSubscribed_init_closure) },
        { be_const_key_weak(report_data_phase, 7), be_const_var(1) },
        { be_const_key_weak(sub, 6), be_const_var(0) },
        { be_const_key_weak(reached_timeout, -1), be_const_closure(Matter_IM_ReportDataSubscribed_reached_timeout_closure) },
        { be_const_key_weak(status_error_received, -1), be_const_closure(Matter_IM_ReportDataSubscribed_status_error_received_closure) },
    })),
    be_str_weak(Matter_IM_ReportDataSubscribed)
);
/*******************************************************************/

void be_load_Matter_IM_ReportDataSubscribed_class(bvm *vm) {
    be_pushntvclass(vm, &be_class_Matter_IM_ReportDataSubscribed);
    be_setglobal(vm, "Matter_IM_ReportDataSubscribed");
    be_pop(vm, 1);
}

extern const bclass be_class_Matter_IM_SubscribedHeartbeat;

/********************************************************************
** Solidified function: status_error_received
********************************************************************/
be_local_closure(Matter_IM_SubscribedHeartbeat_status_error_received,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    2,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(sub),
    /* K1   */  be_nested_str_weak(remove_self),
    }),
    be_str_weak(status_error_received),
    &be_const_str_solidified,
    ( &(const binstruction[ 5]) {  /* code */
      0x88080100,  //  0000  GETMBR	R2	R0	K0
      0x8C080501,  //  0001  GETMET	R2	R2	K1
      0x7C080200,  //  0002  CALL	R2	1
      0x50080000,  //  0003  LDBOOL	R2	0	0
      0x80040400,  //  0004  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: send_im
********************************************************************/
be_local_closure(Matter_IM_SubscribedHeartbeat_send_im,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    2,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(ready),
    /* K1   */  be_nested_str_weak(send_im),
    }),
    be_str_weak(send_im),
    &be_const_str_solidified,
    ( &(const binstruction[13]) {  /* code */
      0x88080100,  //  0000  GETMBR	R2	R0	K0
      0x740A0001,  //  0001  JMPT	R2	#0004
      0x50080000,  //  0002  LDBOOL	R2	0	0
      0x80040400,  //  0003  RET	1	R2
      0x60080003,  //  0004  GETGBL	R2	G3
      0x5C0C0000,  //  0005  MOVE	R3	R0
      0x7C080200,  //  0006  CALL	R2	1
      0x8C080501,  //  0007  GETMET	R2	R2	K1
      0x5C100200,  //  0008  MOVE	R4	R1
      0x7C080400,  //  0009  CALL	R2	2
      0x50080000,  //  000A  LDBOOL	R2	0	0
      0x90020002,  //  000B  SETMBR	R0	K0	R2
      0x80000000,  //  000C  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: ack_received
********************************************************************/
be_local_closure(Matter_IM_SubscribedHeartbeat_ack_received,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    2,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(ack_received),
    /* K1   */  be_nested_str_weak(finish),
    }),
    be_str_weak(ack_received),
    &be_const_str_solidified,
    ( &(const binstruction[10]) {  /* code */
      0x60080003,  //  0000  GETGBL	R2	G3
      0x5C0C0000,  //  0001  MOVE	R3	R0
      0x7C080200,  //  0002  CALL	R2	1
      0x8C080500,  //  0003  GETMET	R2	R2	K0
      0x5C100200,  //  0004  MOVE	R4	R1
      0x7C080400,  //  0005  CALL	R2	2
      0x50080200,  //  0006  LDBOOL	R2	1	0
      0x90020202,  //  0007  SETMBR	R0	K1	R2
      0x50080200,  //  0008  LDBOOL	R2	1	0
      0x80040400,  //  0009  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: reached_timeout
********************************************************************/
be_local_closure(Matter_IM_SubscribedHeartbeat_reached_timeout,   /* name */
  be_nested_proto(
    3,                          /* nstack */
    1,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(sub),
    /* K1   */  be_nested_str_weak(remove_self),
    }),
    be_str_weak(reached_timeout),
    &be_const_str_solidified,
    ( &(const binstruction[ 4]) {  /* code */
      0x88040100,  //  0000  GETMBR	R1	R0	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x7C040200,  //  0002  CALL	R1	1
      0x80000000,  //  0003  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: status_ok_received
********************************************************************/
be_local_closure(Matter_IM_SubscribedHeartbeat_status_ok_received,   /* name */
  be_nested_proto(
    3,                          /* nstack */
    2,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    0,                          /* has constants */
    NULL,                       /* no const */
    be_str_weak(status_ok_received),
    &be_const_str_solidified,
    ( &(const binstruction[ 2]) {  /* code */
      0x50080000,  //  0000  LDBOOL	R2	0	0
      0x80040400,  //  0001  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(Matter_IM_SubscribedHeartbeat_init,   /* name */
  be_nested_proto(
    11,                          /* nstack */
    5,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[11]) {     /* constants */
    /* K0   */  be_nested_str_weak(resp),
    /* K1   */  be_nested_str_weak(matter),
    /* K2   */  be_nested_str_weak(Frame),
    /* K3   */  be_nested_str_weak(initiate_response),
    /* K4   */  be_nested_str_weak(data),
    /* K5   */  be_nested_str_weak(ready),
    /* K6   */  be_nested_str_weak(expiration),
    /* K7   */  be_nested_str_weak(tasmota),
    /* K8   */  be_nested_str_weak(millis),
    /* K9   */  be_nested_str_weak(MSG_TIMEOUT),
    /* K10  */  be_nested_str_weak(sub),
    }),
    be_str_weak(init),
    &be_const_str_solidified,
    ( &(const binstruction[20]) {  /* code */
      0xB8160200,  //  0000  GETNGBL	R5	K1
      0x88140B02,  //  0001  GETMBR	R5	R5	K2
      0x8C140B03,  //  0002  GETMET	R5	R5	K3
      0x5C1C0200,  //  0003  MOVE	R7	R1
      0x5C200400,  //  0004  MOVE	R8	R2
      0x54260004,  //  0005  LDINT	R9	5
      0x50280200,  //  0006  LDBOOL	R10	1	0
      0x7C140A00,  //  0007  CALL	R5	5
      0x90020005,  //  0008  SETMBR	R0	K0	R5
      0x90020803,  //  0009  SETMBR	R0	K4	R3
      0x50140200,  //  000A  LDBOOL	R5	1	0
      0x90020A05,  //  000B  SETMBR	R0	K5	R5
      0xB8160E00,  //  000C  GETNGBL	R5	K7
      0x8C140B08,  //  000D  GETMET	R5	R5	K8
      0x7C140200,  //  000E  CALL	R5	1
      0x88180109,  //  000F  GETMBR	R6	R0	K9
      0x00140A06,  //  0010  ADD	R5	R5	R6
      0x90020C05,  //  0011  SETMBR	R0	K6	R5
      0x90021404,  //  0012  SETMBR	R0	K10	R4
      0x80000000,  //  0013  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Matter_IM_SubscribedHeartbeat
********************************************************************/
extern const bclass be_class_Matter_IM_ReportData;
be_local_class(Matter_IM_SubscribedHeartbeat,
    1,
    &be_class_Matter_IM_ReportData,
    be_nested_map(7,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(init, 1), be_const_closure(Matter_IM_SubscribedHeartbeat_init_closure) },
        { be_const_key_weak(status_ok_received, -1), be_const_closure(Matter_IM_SubscribedHeartbeat_status_ok_received_closure) },
        { be_const_key_weak(sub, 6), be_const_var(0) },
        { be_const_key_weak(ack_received, -1), be_const_closure(Matter_IM_SubscribedHeartbeat_ack_received_closure) },
        { be_const_key_weak(reached_timeout, -1), be_const_closure(Matter_IM_SubscribedHeartbeat_reached_timeout_closure) },
        { be_const_key_weak(status_error_received, 0), be_const_closure(Matter_IM_SubscribedHeartbeat_status_error_received_closure) },
        { be_const_key_weak(send_im, -1), be_const_closure(Matter_IM_SubscribedHeartbeat_send_im_closure) },
    })),
    be_str_weak(Matter_IM_SubscribedHeartbeat)
);
/*******************************************************************/

void be_load_Matter_IM_SubscribedHeartbeat_class(bvm *vm) {
    be_pushntvclass(vm, &be_class_Matter_IM_SubscribedHeartbeat);
    be_setglobal(vm, "Matter_IM_SubscribedHeartbeat");
    be_pop(vm, 1);
}

extern const bclass be_class_Matter_IM_SubscribeResponse;

/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(class_Matter_IM_SubscribedHeartbeat_init,   /* name */
  be_nested_proto(
    10,                          /* nstack */
    4,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_SubscribedHeartbeat,     /* shared constants */
    be_str_weak(init),
    &be_const_str_solidified,
    ( &(const binstruction[25]) {  /* code */
      0x60100003,  //  0000  GETGBL	R4	G3
      0x5C140000,  //  0001  MOVE	R5	R0
      0x7C100200,  //  0002  CALL	R4	1
      0x8C100905,  //  0003  GETMET	R4	R4	K5
      0x4C180000,  //  0004  LDNIL	R6
      0x4C1C0000,  //  0005  LDNIL	R7
      0x4C200000,  //  0006  LDNIL	R8
      0x7C100800,  //  0007  CALL	R4	4
      0xB8120E00,  //  0008  GETNGBL	R4	K7
      0x88100908,  //  0009  GETMBR	R4	R4	K8
      0x8C100909,  //  000A  GETMET	R4	R4	K9
      0x5C180200,  //  000B  MOVE	R6	R1
      0x5C1C0400,  //  000C  MOVE	R7	R2
      0x54220004,  //  000D  LDINT	R8	5
      0x50240200,  //  000E  LDBOOL	R9	1	0
      0x7C100A00,  //  000F  CALL	R4	5
      0x90020C04,  //  0010  SETMBR	R0	K6	R4
      0x90020003,  //  0011  SETMBR	R0	K0	R3
      0x8C10010A,  //  0012  GETMET	R4	R0	K10
      0x8818070B,  //  0013  GETMBR	R6	R3	K11
      0x7C100400,  //  0014  CALL	R4	2
      0x8C10010C,  //  0015  GETMET	R4	R0	K12
      0x50180200,  //  0016  LDBOOL	R6	1	0
      0x7C100400,  //  0017  CALL	R4	2
      0x80000000,  //  0018  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Matter_IM_SubscribedHeartbeat
********************************************************************/
extern const bclass be_class_Matter_IM_ReportData_Pull;
be_local_class(Matter_IM_SubscribedHeartbeat,
    1,
    &be_class_Matter_IM_ReportData_Pull,
    be_nested_map(7,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(init, 1), be_const_closure(class_Matter_IM_SubscribedHeartbeat_init_closure) },
        { be_const_key_weak(status_ok_received, -1), be_const_closure(class_Matter_IM_SubscribedHeartbeat_status_ok_received_closure) },
        { be_const_key_weak(sub, 6), be_const_var(0) },
        { be_const_key_weak(ack_received, -1), be_const_closure(class_Matter_IM_SubscribedHeartbeat_ack_received_closure) },
        { be_const_key_weak(reached_timeout, -1), be_const_closure(class_Matter_IM_SubscribedHeartbeat_reached_timeout_closure) },
        { be_const_key_weak(status_error_received, 0), be_const_closure(class_Matter_IM_SubscribedHeartbeat_status_error_received_closure) },
        { be_const_key_weak(send_im, -1), be_const_closure(class_Matter_IM_SubscribedHeartbeat_send_im_closure) },
    })),
    be_str_weak(Matter_IM_SubscribedHeartbeat)
);
// compact class 'Matter_IM_SubscribeResponse_Pull' ktab size: 29, total: 36 (saved 56 bytes)
static const bvalue be_ktab_class_Matter_IM_SubscribeResponse_Pull[29] = {
  /* K0   */  be_nested_str_weak(init),
  /* K1   */  be_nested_str_weak(sub),
  /* K2   */  be_nested_str_weak(report_data_phase),
  /* K3   */  be_nested_str_weak(set_subscription_id),
  /* K4   */  be_nested_str_weak(subscription_id),
  /* K5   */  be_nested_str_weak(tasmota),
  /* K6   */  be_nested_str_weak(loglevel),
  /* K7   */  be_const_int(3),
  /* K8   */  be_nested_str_weak(log),
  /* K9   */  be_nested_str_weak(MTR_X3A_X20_X3ESub_OK_X20_X20_X20_X20_X28_X256i_X29_X20sub_X3D_X25i),
  /* K10  */  be_nested_str_weak(session),
  /* K11  */  be_nested_str_weak(local_session_id),
  /* K12  */  be_nested_str_weak(status_ok_received),
  /* K13  */  be_nested_str_weak(finishing),
  /* K14  */  be_nested_str_weak(send_im),
  /* K15  */  be_nested_str_weak(ready),
  /* K16  */  be_nested_str_weak(resp),
  /* K17  */  be_nested_str_weak(matter),
  /* K18  */  be_nested_str_weak(SubscribeResponseMessage),
  /* K19  */  be_nested_str_weak(max_interval),
  /* K20  */  be_nested_str_weak(opcode),
  /* K21  */  be_nested_str_weak(encode_frame),
  /* K22  */  be_nested_str_weak(to_TLV),
  /* K23  */  be_nested_str_weak(tlv2raw),
  /* K24  */  be_nested_str_weak(encrypt),
  /* K25  */  be_nested_str_weak(send_response_frame),
  /* K26  */  be_nested_str_weak(last_counter),
  /* K27  */  be_nested_str_weak(message_counter),
  /* K28  */  be_nested_str_weak(re_arm),
};


extern const bclass be_class_Matter_IM_SubscribeResponse_Pull;

/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(class_Matter_IM_SubscribeResponse_Pull_init,   /* name */
  be_nested_proto(
    10,                          /* nstack */
    5,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_IM_SubscribeResponse_Pull,     /* shared constants */
    be_str_weak(init),
    &be_const_str_solidified,
    ( &(const binstruction[15]) {  /* code */
      0x60140003,  //  0000  GETGBL	R5	G3
      0x5C180000,  //  0001  MOVE	R6	R0
      0x7C140200,  //  0002  CALL	R5	1
      0x8C140B00,  //  0003  GETMET	R5	R5	K0
      0x5C1C0200,  //  0004  MOVE	R7	R1
      0x5C200400,  //  0005  MOVE	R8	R2
      0x5C240600,  //  0006  MOVE	R9	R3
      0x7C140800,  //  0007  CALL	R5	4
      0x90020204,  //  0008  SETMBR	R0	K1	R4
      0x50140200,  //  0009  LDBOOL	R5	1	0
      0x90020405,  //  000A  SETMBR	R0	K2	R5
      0x8C140103,  //  000B  GETMET	R5	R0	K3
      0x881C0904,  //  000C  GETMBR	R7	R4	K4
      0x7C140400,  //  000D  CALL	R5	2
      0x80000000,  //  000E  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: status_ok_received
********************************************************************/
be_local_closure(class_Matter_IM_SubscribeResponse_Pull_status_ok_received,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 9]) {     /* constants */
    /* K0   */  be_nested_str_weak(tasmota),
    /* K1   */  be_nested_str_weak(log),
    /* K2   */  be_nested_str_weak(MTR_X3A_X20_X3ESub_OK_X20_X20_X20_X20_X28_X256i_X29_X20sub_X3D_X25i),
    /* K3   */  be_nested_str_weak(session),
    /* K4   */  be_nested_str_weak(local_session_id),
    /* K5   */  be_nested_str_weak(sub),
    /* K6   */  be_nested_str_weak(subscription_id),
    /* K7   */  be_const_int(3),
    /* K8   */  be_nested_str_weak(status_ok_received),
    }),
    be_str_weak(status_ok_received),
    &be_const_str_solidified,
    ( &(const binstruction[18]) {  /* code */
      0xB80A0000,  //  0000  GETNGBL	R2	K0
      0x8C080501,  //  0001  GETMET	R2	R2	K1
      0x60100018,  //  0002  GETGBL	R4	G24
      0x58140002,  //  0003  LDCONST	R5	K2
      0x88180303,  //  0004  GETMBR	R6	R1	K3
      0x88180D04,  //  0005  GETMBR	R6	R6	K4
      0x881C0105,  //  0006  GETMBR	R7	R0	K5
      0x881C0F06,  //  0007  GETMBR	R7	R7	K6
      0x7C100600,  //  0008  CALL	R4	3
      0x58140007,  //  0009  LDCONST	R5	K7
      0x7C080600,  //  000A  CALL	R2	3
      0x60080003,  //  000B  GETGBL	R2	G3
      0x5C0C0000,  //  000C  MOVE	R3	R0
      0x7C080200,  //  000D  CALL	R2	1
      0x8C080508,  //  000E  GETMET	R2	R2	K8
      0x5C100200,  //  000F  MOVE	R4	R1
      0x7C080400,  //  0010  CALL	R2	2
      0x80040400,  //  0011  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: send_im
********************************************************************/
be_local_closure(class_Matter_IM_SubscribeResponse_Pull_send_im,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[19]) {     /* constants */
    /* K0   */  be_nested_str_weak(ready),
    /* K1   */  be_nested_str_weak(report_data_phase),
    /* K2   */  be_nested_str_weak(send_im),
    /* K3   */  be_nested_str_weak(finish),
    /* K4   */  be_nested_str_weak(resp),
    /* K5   */  be_nested_str_weak(matter),
    /* K6   */  be_nested_str_weak(SubscribeResponseMessage),
    /* K7   */  be_nested_str_weak(subscription_id),
    /* K8   */  be_nested_str_weak(sub),
    /* K9   */  be_nested_str_weak(max_interval),
    /* K10  */  be_nested_str_weak(opcode),
    /* K11  */  be_nested_str_weak(encode_frame),
    /* K12  */  be_nested_str_weak(to_TLV),
    /* K13  */  be_nested_str_weak(tlv2raw),
    /* K14  */  be_nested_str_weak(encrypt),
    /* K15  */  be_nested_str_weak(send_response_frame),
    /* K16  */  be_nested_str_weak(last_counter),
    /* K17  */  be_nested_str_weak(message_counter),
    /* K18  */  be_nested_str_weak(re_arm),
    }),
    be_str_weak(send_im),
    &be_const_str_solidified,
    ( &(const binstruction[53]) {  /* code */
      0x88080100,  //  0000  GETMBR	R2	R0	K0
      0x740A0001,  //  0001  JMPT	R2	#0004
      0x50080000,  //  0002  LDBOOL	R2	0	0
      0x80040400,  //  0003  RET	1	R2
      0x88080101,  //  0004  GETMBR	R2	R0	K1
      0x780A000E,  //  0005  JMPF	R2	#0015
      0x60080003,  //  0006  GETGBL	R2	G3
      0x5C0C0000,  //  0007  MOVE	R3	R0
      0x7C080200,  //  0008  CALL	R2	1
      0x8C080502,  //  0009  GETMET	R2	R2	K2
      0x5C100200,  //  000A  MOVE	R4	R1
      0x7C080400,  //  000B  CALL	R2	2
      0x88080103,  //  000C  GETMBR	R2	R0	K3
      0x780A0003,  //  000D  JMPF	R2	#0012
      0x50080000,  //  000E  LDBOOL	R2	0	0
      0x90020202,  //  000F  SETMBR	R0	K1	R2
      0x50080000,  //  0010  LDBOOL	R2	0	0
      0x90020602,  //  0011  SETMBR	R0	K3	R2
      0x50080000,  //  0012  LDBOOL	R2	0	0
      0x90020002,  //  0013  SETMBR	R0	K0	R2
      0x7002001E,  //  0014  JMP		#0034
      0x88080104,  //  0015  GETMBR	R2	R0	K4
      0xB80E0A00,  //  0016  GETNGBL	R3	K5
      0x8C0C0706,  //  0017  GETMET	R3	R3	K6
      0x7C0C0200,  //  0018  CALL	R3	1
      0x88100108,  //  0019  GETMBR	R4	R0	K8
      0x88100907,  //  001A  GETMBR	R4	R4	K7
      0x900E0E04,  //  001B  SETMBR	R3	K7	R4
      0x88100108,  //  001C  GETMBR	R4	R0	K8
      0x88100909,  //  001D  GETMBR	R4	R4	K9
      0x900E1204,  //  001E  SETMBR	R3	K9	R4
      0x88100104,  //  001F  GETMBR	R4	R0	K4
      0x54160003,  //  0020  LDINT	R5	4
      0x90121405,  //  0021  SETMBR	R4	K10	R5
      0x8C10050B,  //  0022  GETMET	R4	R2	K11
      0x8C18070C,  //  0023  GETMET	R6	R3	K12
      0x7C180200,  //  0024  CALL	R6	1
      0x8C180D0D,  //  0025  GETMET	R6	R6	K13
      0x7C180200,  //  0026  CALL	R6	1
      0x7C100400,  //  0027  CALL	R4	2
      0x8C10050E,  //  0028  GETMET	R4	R2	K14
      0x7C100200,  //  0029  CALL	R4	1
      0x8C10030F,  //  002A  GETMET	R4	R1	K15
      0x5C180400,  //  002B  MOVE	R6	R2
      0x7C100400,  //  002C  CALL	R4	2
      0x88100511,  //  002D  GETMBR	R4	R2	K17
      0x90022004,  //  002E  SETMBR	R0	K16	R4
      0x88100108,  //  002F  GETMBR	R4	R0	K8
      0x8C100912,  //  0030  GETMET	R4	R4	K18
      0x7C100200,  //  0031  CALL	R4	1
      0x50100200,  //  0032  LDBOOL	R4	1	0
      0x90020604,  //  0033  SETMBR	R0	K3	R4
      0x80000000,  //  0034  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Matter_IM_SubscribeResponse_Pull
********************************************************************/
extern const bclass be_class_Matter_IM_ReportData_Pull;
be_local_class(Matter_IM_SubscribeResponse_Pull,
    2,
    &be_class_Matter_IM_ReportData_Pull,
    be_nested_map(5,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(init, 4), be_const_closure(class_Matter_IM_SubscribeResponse_Pull_init_closure) },
        { be_const_key_weak(sub, -1), be_const_var(0) },
        { be_const_key_weak(status_ok_received, -1), be_const_closure(class_Matter_IM_SubscribeResponse_Pull_status_ok_received_closure) },
        { be_const_key_weak(send_im, -1), be_const_closure(class_Matter_IM_SubscribeResponse_Pull_send_im_closure) },
        { be_const_key_weak(report_data_phase, -1), be_const_var(1) },
    })),
    be_str_weak(Matter_IM_SubscribeResponse_Pull)
);
/********************************************************************/
/* End of solidification */
