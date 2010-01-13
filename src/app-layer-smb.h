/*
 * Copyright (c) 2009,2010 Open Information Security Foundation
 * app-layer-smb.h
 *
 * \author Kirby Kuehl <kkuehl@gmail.com>
 */

#ifndef APPLAYERSMB_H_
#define APPLAYERSMB_H_
#include "app-layer-protos.h"
#include "app-layer-parser.h"
#include "flow.h"
#include "stream.h"
#include <stdint.h>
#include "app-layer-nbss.h"

typedef struct smb_hdr_ {
    uint8_t protocol[4];
    uint8_t command;
    uint32_t status;
    uint8_t flags;
    uint16_t flags2;
    uint16_t pidhigh;
    uint64_t securitysignature;
    uint16_t unused;
    uint16_t tid;
    uint16_t pid;
    uint16_t uid;
    uint16_t mid;
}SMBHdr;
#define SMB_HDR_LEN 32
#define MINIMUM_SMB_LEN 35
#define NBSS_SMB_HDRS_LEN 36

typedef struct wordcount_ {
    uint8_t wordcount;
    uint8_t *words;
}SMBWordCount;

typedef struct bytecount_ {
    uint8_t bytecountbytes;
    uint16_t bytecount;
    uint8_t *bytes;
}SMBByteCount;

typedef struct andxcount_ {
    uint8_t isandx;
    uint8_t paddingparsed;
    uint8_t andxcommand;
    uint16_t andxoffset;
    uint16_t andxbytesprocessed;
    uint32_t datalength;
    uint64_t dataoffset;
}SMBAndX;

typedef struct SMBState_ {
    NBSSHdr nbss;
    SMBHdr smb;
    SMBWordCount wordcount;
    SMBByteCount bytecount;
    SMBAndX andx;
    uint16_t bytesprocessed;
}SMBState;

#define SMB_FLAGS_SERVER_TO_REDIR 0x80
#define SMB_NO_SECONDARY_ANDX_COMMAND 0xff

/* http://msdn.microsoft.com/en-us/library/dd327674.aspx */
#define SMB_COM_CREATE_DIRECTORY	0x00
#define SMB_COM_DELETE_DIRECTORY	0x01
#define SMB_COM_OPEN				0x02
#define SMB_COM_CREATE	 			0x03
#define SMB_COM_CLOSE	 			0x04
#define SMB_COM_FLUSH	 			0x05
#define SMB_COM_DELETE	 			0x06
#define SMB_COM_RENAME	 			0x07
#define SMB_COM_QUERY_INFORMATION	0x08
#define SMB_COM_SET_INFORMATION	 	0x09
#define SMB_COM_READ	 			0x0A
#define SMB_COM_WRITE	 			0x0B
#define SMB_COM_LOCK_BYTE_RANGE	 	0x0C
#define SMB_COM_UNLOCK_BYTE_RANGE 	0x0D
#define SMB_COM_CREATE_TEMPORARY	0x0E
#define SMB_COM_CREATE_NEW	 		0x0F
#define SMB_COM_CHECK_DIRECTORY	 	0x10
#define SMB_COM_PROCESS_EXIT	 	0x11
#define SMB_COM_SEEK	 			0x12
#define SMB_COM_LOCK_AND_READ	 	0x13
#define SMB_COM_WRITE_AND_UNLOCK 	0x14
#define SMB_COM_READ_RAW	 		0x1A
#define SMB_COM_READ_MPX	 		0x1B
#define SMB_COM_READ_MPX_SECONDARY 	0x1C
#define SMB_COM_WRITE_RAW	 		0x1D
#define SMB_COM_WRITE_MPX	 		0x1E
#define SMB_COM_WRITE_COMPLETE	 	0x20
#define SMB_COM_SET_INFORMATION2 	0x22
#define SMB_COM_QUERY_INFORMATION2	0x23
#define SMB_COM_LOCKING_ANDX	 	0x24
#define SMB_COM_TRANSACTION	 		0x25
#define SMB_COM_TRANSACTION_SECONDARY	0x26
#define SMB_COM_IOCTL	 			0x27
#define SMB_COM_IOCTL_SECONDARY	 	0x28
#define SMB_COM_COPY	 			0x29
#define SMB_COM_MOVE	 			0x2A
#define SMB_COM_ECHO	 			0x2B
#define SMB_COM_WRITE_AND_CLOSE	 	0x2C
#define SMB_COM_OPEN_ANDX	 		0x2D
#define SMB_COM_READ_ANDX	 		0x2E
#define SMB_COM_WRITE_ANDX	 		0x2F
#define SMB_COM_CLOSE_AND_TREE_DISC	0x31
#define SMB_COM_TRANSACTION2	 	0x32
#define SMB_COM_TRANSACTION2_SECONDARY	0x33
#define SMB_COM_FIND_CLOSE2	 		0x34
#define SMB_COM_FIND_NOTIFY_CLOSE	0x35
#define SMB_COM_TREE_CONNECT	 	0x70
#define SMB_COM_TREE_DISCONNECT	 	0x71
#define SMB_COM_NEGOTIATE	 		0x72
#define SMB_COM_SESSION_SETUP_ANDX	0x73
#define SMB_COM_LOGOFF_ANDX	 		0x74
#define SMB_COM_TREE_CONNECT_ANDX	0x75
#define SMB_COM_QUERY_INFORMATION_DISK	0x80
#define SMB_COM_SEARCH	 			0x81
#define SMB_COM_FIND	 			0x82
#define SMB_COM_FIND_UNIQUE	 		0x83
#define SMB_COM_NT_TRANSACT	 		0xA0
#define SMB_COM_NT_TRANSACT_SECONDARY	0xA1
#define SMB_COM_NT_CREATE_ANDX	 	0xA2
#define SMB_COM_NT_CANCEL	 		0xA4
#define SMB_COM_NT_RENAME	 		0xA5
#define SMB_COM_OPEN_PRINT_FILE	 	0xC0
#define SMB_COM_WRITE_PRINT_FILE	0xC1
#define SMB_COM_CLOSE_PRINT_FILE	0xC2
#define SMB_COM_GET_PRINT_QUEUE	 	0xC3

void RegisterSMBParsers(void);
void SMBParserRegisterTests(void);
int isAndX(SMBState *smb_state);


#endif /* APPLAYERSMB_H_ */
