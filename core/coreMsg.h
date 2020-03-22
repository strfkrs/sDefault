#pragma once
#include "types.h"
#define CORE_MSG_LENGTH 50

typedef struct coreMsg coreMsg;

typedef enum coreMsgType
{
   coreMsgType_string,
   coreMsgType_charArray
} coreMsgType;

typedef struct coreMsg {
   index_t       msgLength;
   coreMsgType   msgType;
   unsigned char byteArray[CORE_MSG_LENGTH];
} coreMsg;

static coreMsg CORE_MSG;