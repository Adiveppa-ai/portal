#ifndef __RWDB_TRACER_H__
#define __RWDB_TRACER_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/tracer.h#1 $
 *
 * Copyright (c) 1994-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 **************************************************************************
 *
 * Declaration  of class RWDBTracer
 *
 **************************************************************************/

#include <rw/db/dbmutex.h>
#include <rw/db/defs.h>
#include <rw/rstream.h>
#include <rw/zone.h>

class RWDBMultiRowImp;

/**
 * \ingroup db_utility_and_diagnostics_group
 * \class RWDBTracer
 *
 * \brief
 * Provides a runtime trace facility for DB Interface Module applications.
 *
 * Class RWDBTracer provides a runtime trace facility for DB Interface
 * Module applications. RWDBTracer objects can be turned \c ON or \c OFF,
 * and they can be told what to trace. The default output for an RWDBTracer
 * is the \b std::ostream \c std::clog. The output from an RWDBTracer can be
 * redirected to an \b std::ostream.
 *
 * A database object of the DB Interface Module contains an RWDBTracer.
 * Consequently, enabling tracing on an RWDBDatabase, for example, produces
 * trace output for all objects produced by that RWDBDatabase.
 *
 * It is the application's responsibility to ensure that the associated
 * \b std::ostream referenced by the RWDBTracer remains in scope while the
 * RWDBTracer is set \c ON.
 *
 * \synopsis
 * #include <rw/db/tracer.h>
 * #include <fstream>
 *
 * std::ofstream strm("trace.trc");
 * RWDBTracer& tracer = myDbase.tracer();
 * tracer.setOn(RWDBTracer::SQL);
 * tracer.stream(strm);
 * \endsynopsis
 *
 * \sa
 * RWDBDatabase instances provide access to its RWDBTracer.
 *
 * \example
 * \code
 * RWDBTracer& tracer = myDbase.tracer();
 * tracer.setOn(RWDBTracer::SQL);
 * std::ofstream strm("trace.out");
 * tracer.stream(strm);
 * \endcode
 * \endexample
 */
class RWDB_SYMBOLIC RWDBTracer
{
public:
    /**
     * Defines the values that tell an RWDBTracer what to trace.
     */
    enum TraceFlag {
        ZERO = 0,

        /**
         * Traces all SQL sent to the database through the traced object
         */
        SQL = 1,

        /**
         * Traces all the data sent to the database in input-bound buffers
         */
        BoundBuffers = 2,

        /**
         * Traces all SQL sent to the database through the traced object,
         * and replaces any placeholders in the SQL with their contents.
         * When placeholders are bound as arrays, the SQL is repeated for
         * each value in the arrays
         */
        NoPlaceHolderSQL = 4,

        /**
         * If turned \c ON in multithreaded builds, prints the thread id of
         * the execution thread in the tracer stream. The thread id is
         * printed for all three types of tracer output. For single-threaded
         * builds, this setting does nothing. By default, #ThreadID is
         * \c OFF
         */
        ThreadID = 8
    };

    /**
     * Default constructor that produces an RWDBTracer not associated with
     * any object. To obtain useful trace information, get an RWDBTracer
     * reference from an RWDBDatabase.
     */
    RWDBTracer();

    /**
     * Copy constructor. RWDBTracer objects are copied by value.
     */
    RWDBTracer(const RWDBTracer& aTrace);

    ~RWDBTracer();

    /**
     * Assignment operator. RWDBTracer objects are copied by value.
     */
    RWDBTracer&  operator=(const RWDBTracer& aTrace);

    /**
     * Directs all subsequent trace output to the supplied \a strm. The DB
     * Interface Module does not check \a strm for validity. Returns a
     * reference to self.
     */
    RWDBTracer&  stream(std::ostream& strm);

    /**
     * Returns a reference to the stream currently attached to self.
     */
    std::ostream&   stream();

    /**
     * Adds the categories represented by \a flags to those categories
     * currently being traced by self. Returns the new bit-mask of traced
     * categories.
     */
    unsigned     setOn(TraceFlag flags);

    /**
     * Returns \c true if the trace category represented by \a flag is
     * currently enabled, otherwise returns \c false.
     */
    bool         isOn(TraceFlag flag) const;

    /**
     * Returns a bit-mask representing the categories of tracing currently
     * enabled.
     */
    unsigned     flag() const;

    /**
     * Removes the categories represented by \a flags from those categories
     * currently being traced by self. Returns the new bit-mask of traced
     * categories.
     */
    unsigned     setOff(TraceFlag flags);

    void         traceSql(const RWCString& sql);
    void         traceSqlWithNoPlaceholder(const RWCString& sql);
    void         traceSqlWithNoPlaceholder(const RWCString& sql,
                                           const RWDBPhraseBook& phrase,
                                           const RWDBMultiRow& params,
                                           const size_t bulksize,
                                           const RWZone& timeZone);
    void         traceBoundBuffers(const RWDBMultiRowImp& multirow,
                                   size_t bulkSize,
                                   const RWZone& timeZone);

    /**
     * Attempts to acquire the internal mutex lock. If the mutex is already
     * locked by another thread, the function blocks until the mutex is
     * released. This function can be called from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void         acquire() const;

    /**
     * Releases a previously acquired mutex. This function can be called
     * from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void         release() const;

    /**
     * Values may be streamed out through an RWDBTracer, much as through a
     * \b std::ostream, allowing applications to annotate the trace output.
     * Structured objects may be streamed out by defining a function of the
     * form:
     *
     * \code
     * RWDBTracer& operator<<(RWDBTracer& tracer, someStruct& s);
     * \endcode
     */
    RWDBTracer&  operator<< (char arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (signed char arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (unsigned char arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (short arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (unsigned short arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (int arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (unsigned int arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (long arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (unsigned long arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (long long arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (unsigned long long arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (float arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (double arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (long double arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (const char* str);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (const signed char* arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (const unsigned char* arg);


    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (void* arg);

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (std::ostream & (*f)(std::ostream&));

    /**
     * \copydoc operator<<(char)
     */
    RWDBTracer&  operator<< (std::ios & (*f)(std::ios&));

    /**
     * Returns \c false if the attached \b std::ostream encounters an EOF or
     * if the bad bit has been set, otherwise \c true.
     */
    bool    isValid();

private:
    RWDBLocalRecursiveMutex     mutex_;
    std::ostream*      impl_;
    unsigned                    traceFlag_;

    void         writeThreadID();
};

#endif
