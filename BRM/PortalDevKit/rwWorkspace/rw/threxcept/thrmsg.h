#ifndef __rw_threxcept_thrmsg_h__
#define __rw_threxcept_thrmsg_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/threxcept/thrmsg.h#1 $
 *
 * Copyright (c) 1996-2016 Rogue Wave Software, Inc.  All Rights Reserved.
 * 
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software, Inc.
 * pursuant to a written license agreement and may be used, copied, transmitted,
 * and stored only in accordance with the terms of such license agreement and
 * with the inclusion of the above copyright notice.  This computer software or
 * any other copies thereof may not be provided or otherwise made available to
 * any other person.
 * 
 * U.S. Government Restricted Rights.  This computer software: (a) was
 * developed at private expense and is in all respects the proprietary
 * information of Rogue Wave Software, Inc.; (b) was not developed with
 * government funds; (c) is a trade secret of Rogue Wave Software, Inc. for all
 * purposes of the Freedom of Information Act; and (d) is a commercial item and
 * thus, pursuant to Section 12.212 of the Federal Acquisition Regulations (FAR)
 * and DFAR Supplement Section 227.7202, Government's use, duplication or
 * disclosure of the computer software is subject to the restrictions set forth
 * by Rogue Wave Software, Inc.
 *
 *************************************************************************/


/*****************************************************************************

  thrmsg.h - Exception message definition macros.

*****************************************************************************/

#define RW_THR_Unexpected_Error              "Unexpected Error"
#define RW_THR_Unrecognized_Error            "Unrecognized Error"
#define RW_THR_Unexpected_Exception          "Unexpected exception"
#define RW_THR_Unrecognized_Exception        "Unrecognized exception"

#define RW_THR_Unsupported_Value             "Unsupported value"
#define RW_THR_Not_Supported                 "Operation not supported"
#define RW_THR_Not_Available                 "Operation not available"
#define RW_THR_Not_Implemented               "Operation not implemented"
#define RW_THR_Aborted                       "Operation aborted"
#define RW_THR_Terminated                    "Operation terminated"
#define RW_THR_Invalid_Usage                 "Invalid usage"
#define RW_THR_InternalError                 "Internal error"
#define RW_THR_ExternalError                 "External error"
#define RW_THR_Invalid_Pointer               "Invalid pointer"
#define RW_THR_Insufficient_Privileges       "Insufficient privileges"
#define RW_THR_Not_Owner                     "Not owner"
#define RW_THR_Already_Initialized           "Already Initialized"

// Bounds

#define RW_THR_Bounds_Error                  "Bounds error"
#define RW_THR_Range                         "Value out of current allowable range"
#define RW_THR_Invalid                       "Value is invalid or unrecognized"
#define RW_THR_Unrecognized_Priority_Class   "Unrecognized scheduling or priority class"
#define RW_THR_Permission_Error              "Permission error"

// Resource Limits

#define RW_THR_Resource_Limit                "Resource limit"
#define RW_THR_No_Memory                     "Insufficient memory"
#define RW_THR_No_Resources                  "Insufficient system resources"
#define RW_THR_Too_Many_Threads              "Too many threads"
#define RW_THR_Too_Many_Handles              "Too many handles"
#define RW_THR_Too_Many_Requests             "Too many requests"

// Runnable

#define RW_THR_Already_Started               "The runnable is already started"
#define RW_THR_Thread_Active                 "A thread is already active within the runnable"
#define RW_THR_Thread_Not_Active             "No thread is active within the runnable"
#define RW_THR_Not_Interrupted               "The runnable is not currently interrupted"
#define RW_THR_Illegal_Access                "Illegal access"
#define RW_THR_Illegal_Internal_Access       "External thread illegally attempted to call this internal function"
#define RW_THR_Illegal_External_Access       "Internal thread illegally attempted to call this external function"
#define RW_THR_Canceled                      "Runnable canceled"
#define RW_THR_Invalid_Runnable_Functor      "Runnable started with invalid functor"

// Thread Stuff

#define RW_THR_Invalid_Thread_Id             "Invalid thread id"
#define RW_THR_Thread_Not_Suspended          "Thread not suspended"
#define RW_THR_Illegal_Threads_Access        "Illegal call from SourcePro Core - Threads Module thread"

#endif // __rw_threxcept_thrmsg_h__
