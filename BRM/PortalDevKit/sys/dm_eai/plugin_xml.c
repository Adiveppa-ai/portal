/*******************************************************************
 *
 * @(#)plugin_xml.c 1.2 99/11/12
 *
 * Copyright (c) 2000, 2022, Oracle and/or its affiliates.All rights reserved. 
 * or its licensors and may be used, reproduced, stored or transmitted only in accordance with a valid Oracle license or
 * sublicense agreement.
 *******************************************************************/

#include "pcm.h"
#include "dm_eai_plugin.h"
int
Initialize(void **context, int *output_type)
{
	int pid = getpid();
	char msg[256];

	pin_snprintf(msg,sizeof(msg), "Initialize succeeded : pid = %d", pid);
	PIN_ERR_LOG_MSG(PIN_ERR_LEVEL_DEBUG, msg);
	*output_type = TYPE_XML;
	return PIN_RESULT_PASS;
}


int 
OpenTransaction(void *ctx)
{
	int pid = getpid();
	char msg[256];

	pin_snprintf(msg,sizeof(msg), "OpenTransaction called : pid = %d", pid);
	PIN_ERR_LOG_MSG(PIN_ERR_LEVEL_DEBUG, msg);
	return PIN_RESULT_PASS;
}

int
PublishEvent(void *context, void *payload, char *srvc_poidp)
{
	int pid = getpid();
	char msg[256];
	pin_snprintf(msg, sizeof(msg), "Publishevent  : pid = %d, service poid = %s", pid,
		srvc_poidp);
	PIN_ERR_LOG_MSG(PIN_ERR_LEVEL_DEBUG, msg);
	PIN_ERR_LOG_MSG(PIN_ERR_LEVEL_DEBUG, (char *)payload);
	return PIN_RESULT_PASS;
}


int 
PrepareCommit(void *ctx)
{
	int pid = getpid();
	char msg[256];

	pin_snprintf(msg,sizeof(msg), "PrepareCommit called : pid = %d", pid);
	PIN_ERR_LOG_MSG(PIN_ERR_LEVEL_DEBUG, msg);
	return PIN_RESULT_PASS;
}

int
CommitTransaction(void *ctx)
{
	int pid = getpid();
	char msg[256];

	pin_snprintf(msg,sizeof(msg), "CommitTransaction called : pid = %d", pid);
	PIN_ERR_LOG_MSG(PIN_ERR_LEVEL_DEBUG, msg);
	return PIN_RESULT_PASS;
}

int
AbortTransaction(void *ctx)
{
	int pid = getpid();
	char msg[256];

	pin_snprintf(msg,sizeof(msg), "AbortTransaction called : pid = %d", pid);
	PIN_ERR_LOG_MSG(PIN_ERR_LEVEL_DEBUG, msg);
	return PIN_RESULT_PASS;
}

void
Shutdown(void *ctx)
{
	int pid = getpid();
	char msg[256];
	pin_snprintf(msg,sizeof(msg), "Shutdown succeeded : pid = %d", pid);
	PIN_ERR_LOG_MSG(PIN_ERR_LEVEL_DEBUG, msg);
	return;
}

