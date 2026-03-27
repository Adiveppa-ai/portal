#ifndef __rw_trace_RWTraceEvent_h__
#define __rw_trace_RWTraceEvent_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceEvent.h#1 $
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

#include <rw/trace/RWTraceEventSeverity.h>
#include <rw/trace/pkgdefs.h>
#include <rw/tools/string.h>
#include <stdio.h>
#include <string.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

class RW_TRACE_SYMBOLIC RWTraceEvent
{

public:

    // No ref guide.
    RWTraceEvent(RWTraceEventSeverity level,
                 const char* resource,
                 const char* message,
                 const char* file,
                 size_t line,
                 const void* ptr = 0);

    //--Assignment operator.
    RWTraceEvent&
    operator=(const RWTraceEvent& rhs);

    //--Copy constructor.
    RWTraceEvent(const RWTraceEvent& rhs);

    // Destructor.
    ~RWTraceEvent(void);

    //--Equality operator.  Two trace events are equal if they are
    // from the same file and line.
    bool
    operator==(const RWTraceEvent& rhs) const;

    // Less Than operator. Compares the file name and line number.
    bool
    operator<(const RWTraceEvent& rhs) const;

    //--Returns the trace event's severity level.
    RWTraceEventSeverity
    getSeverity(void) const;

    //--Returns the trace event's resource identifier.
    const char*
    getResourceId(void) const;

    //--Returns the trace event's message.
    const char*
    getMessage(void) const;

    //--Returns the file name where the trace event was generated.
    const char*
    getFileName(void) const;

    //--Returns the line number where the trace event was generated.
    size_t
    getLineNumber(void) const;

    //--Returns the value of the 'this' pointer if an object generated
    //--the trace event.  Otherwise, returns 0.
    const void*
    getThisPtr(void) const;

private:

    // helper class for exception safety
    // replaces RWCString here for efficiency!
    struct String {
        String(const char* str)
        {
            init(str, str ? strlen(str) + 1 : 0);
        }

        String(const String& other)
        {
            init(other.str_, other.len_);
        }

        ~String(void)
        {
            if (buf_ != str_) {
                delete [] str_;
            }
        }

        String& operator=(const String& other)
        {
            if (&other != this) {
                // cache str_ so we can delete it later
                char* save = str_;

                // if we don't have enough room, reallocate
                if (other.len_ < sizeof(buf_)) {
                    str_ = buf_;
                    capacity_ = sizeof(buf_);
                }
                else if (capacity_ < other.len_) {
                    str_ = new char[other.len_];
                    capacity_ = other.len_;
                }

                // copy the string over, cache the length
                rw_memcpy_s(str_, capacity_, other.str_, len_ = other.len_);

                // if allocate and copy was successful, it is now safe to delete the
                // previous string
                if (buf_ != save && str_ != save) {
                    delete [] save;
                }
            }
            return *this;
        }

        void init(const char* str, size_t len)
        {
            // allocate only if necessary, using buffer for efficiency
            if (len < sizeof(buf_)) {
                str_ = buf_;
                capacity_ = sizeof(buf_);
            }
            else {
                str_ = new char[len];
                capacity_ = len;
            }

            // copy the string over, and cache length
            rw_memcpy_s(str_, capacity_, str, len_ = len);
            if (len == 0) {
                str_[len] = '\0';
            }
        }

        char* str_;    // pointer to string, either buf_ or on heap
        char buf_[64]; // cache buffer for short strings
        size_t len_;   // length of the string including null
        size_t capacity_; // capacity of the string buffer
    };

    RWTraceEventSeverity level_;
    const void* ptr_;
    const char* file_;
    size_t line_;

    // expected to have static storage duration
    const char* resource_;

    // allowed to be dynamic
    String message_;
};

inline RWTraceEventSeverity
RWTraceEvent::getSeverity(void) const
{
    return level_;
}

inline const char*
RWTraceEvent::getResourceId(void) const
{
    return resource_;
}

inline const char*
RWTraceEvent::getMessage(void) const
{
    return message_.str_;
}

inline const char*
RWTraceEvent::getFileName(void) const
{
    return file_;
}

inline size_t
RWTraceEvent::getLineNumber(void) const
{
    return line_;
}

inline const void*
RWTraceEvent::getThisPtr(void) const
{
    return ptr_;
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif


#endif // __rw_trace_RWTraceEvent_h__
