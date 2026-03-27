#ifndef TRACE_HPP
#define TRACE_HPP
//==============================================================================
// @(#)$Id: Trace.hpp /cgbubrm_7.5.0.portalbase/1 2015/11/27 04:48:25 nishahan Exp $
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates. 
// 
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//
//  Thread-enabled tracing macros and classes. 
//
//------------------------------------------------------------------------------
// Author: Alexander Rockel
//------------------------------------------------------------------------------
//
// $Log: Trace.hpp,v $
//
// Revision 1.38 2005/12/02 bertm
// PRSF00188168  Performance improvements so Trace can be used in Release builds.
//
// Revision 1.37 2005/06/21 pborah
// PRSF00173135  "Pipeline trace debug intrumentation for Windows"

// Revision 1.36  2001/07/25 13:52:09  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.35  2001/07/04 13:37:22  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.34  2001/04/23 12:58:26  aro
// Small but misleading inline documentation bug fixed.
//
// Revision 1.33  2000/06/15 12:17:52  bt
// Changes for AIX xlC V366.
//
// Revision 1.32  2000/04/17 07:36:20  bt
// Stream table changed to a pointer, because the order of destructor
// calls is unspecified for static objects and if D_ENTER() is called
// in the destructor of a static class, a segmentation fault occurs.
//
// Revision 1.31  1999/09/08 12:28:22  bt
// Implementation changed to support the egcs release 1.1.2 compiler.
// Class STR_InputFile modified to synchronize start() and inactiveLoop().
// If start() is called prior to inactiveLoop(), inactiveLoop() will hang.
//
// Revision 1.30  1999/09/03 14:41:59  bt
// Implementation changed to support the egcs release 1.1.2 compiler.
//
// Revision 1.29  1999/04/28 12:25:25  arockel
// Trace file name: Thread number normalised.
//
// Revision 1.28  1999/04/27 12:08:05  arockel
// BAS_Trace: Negative match implemented.
//
// Revision 1.27  1999/04/13 07:33:32  arockel
// Documentation fixed.
//
// Revision 1.26  1999/03/25 14:59:03  arockel
// Online doc fixed.
//
// Revision 1.19  1999/02/25 10:28:13  arockel
// strtok() replaced by more desireable function.
//
// Revision 1.16  1999/02/17 10:59:07  arockel
// D_PRINT_T makro added to trace class.
//
// Revision 1.12  1999/02/04 15:36:41  arockel
// Default size of trace stream table increased.
//
// Revision 1.11  1999/02/04 14:32:57  arockel
// Signal handling corrected.
//
// Revision 1.9  1999/02/04 12:26:30  arockel
// Command line parameters for trace changed.
//
// Revision 1.6  1999/02/03 14:08:46  arockel
// Multithreaded tracing implemented.
//==============================================================================

#include <stdio.h>      // Basic I/O
#include <signal.h>     // Unix signals
#include <stdlib.h>     // atoi()
#include <string.h>     // strcpy() strrchr() etc. used
#include <malloc.h>     // allocation of new memory

#ifndef    _pin_os_time_h_
  #include "pin_os_time.h"
#endif
#ifndef RW_TOOLS_CSTRING_COMPAT_H
  #include <rw/cstring.h> // RWCString
#endif
#ifndef RW_TOOLS_TIME_H
  #include <rw/rwtime.h>  // RWTime
#endif
#ifndef RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h> // RWTValHashMap
#endif

#ifdef RW_MULTI_THREAD
#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#endif

#ifndef ONLYPOINTER_HPP
  #include "BAS/OnlyPointer.hpp"
#endif
#ifndef BAS_THREADINFO
  #include "BAS/ThreadInfo.hpp"
#endif

//3rd party has been upgraded only for Linux and Sun. 
//Please modify this accordingly once it has been upgraded for other OS. 

// Add specific std's instead of all of them at once. It saves compilation time
// and some compilation issues because of symbol clash with unwanted std being // included

using std::ofstream;
using std::equal_to;
using std::stringstream;
using std::ios;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::iostream;
using std::istream;
using std::ostream;
using std::less;
using std::ifstream;
#include "rw_macros.hpp"


#define TFILE_SIZE           256
#define MAX_NUM_OF_FUNCTIONS 20
#define MAX_ARG              100
#define MAX_FUNCTION_LEN     120

#define MAKE_STR(x) #x
#define MAKE_STR2(x) MAKE_STR(x)

#ifdef TRACE  
// macro-definitions 
// you can find the explanations of the macros 
// together with the comments of the class Trace.
 
// ThreadInfo is optional, 
// but can be used with compile time macro "-DTHREADINFO"

#define D_THREADNAME(arg) \
BAS::Trace::setStreamName(arg);


#ifdef THREADINFO

#define D_THREADINFO \
: virtual public BAS::ThreadInfo

#define D_THREADINFO_M \
, virtual public BAS::ThreadInfo

// deprecated
#define D_MULTITHREADED \
public: virtual bool isThreadSafe() {return true;};

#define D_THREADSAFE \
public: virtual bool isThreadSafe() {return true;};

#define D_NONTHREADSAFE \
public: virtual bool isThreadSafe() {return false;};

// deprecated
#define D_SINGLETHREADED \
public: virtual bool isThreadSafe() {return false;};

#define D_ENTER(arg) \
BAS::Trace theTracer(arg,  __FILE__, __LINE__, this);

#define D_ENTER_F(arg) \
BAS::Trace theTracer(arg, __FILE__, __LINE__, 0);

#else // #ifdef THREADINFO

#define D_THREADINFO
#define D_THREADINFO_M
#define D_MULTITHREADED
#define D_THREADSAFE
#define D_SINGLETHREADED
#define D_NONTHREADSAFE

#define D_ENTER(arg) \
BAS::Trace theTracer(arg,  __FILE__, __LINE__);

#define D_ENTER_F(arg) \
BAS::Trace theTracer(arg, __FILE__, __LINE__);

#endif // #ifdef THREADINFO


// automatic leaving-message in destructor (macro obsolete)
#define D_LEAVE

#define D_ARG(arg) \
if (theTracer.checkLevel(2)) {\
theTracer.traceStream() << "Argument: " << #arg << " = " << arg << endl << BAS_DEFS_STD_GLOBAL(flush);\
}

#define D_BARG(arg) \
if (theTracer.checkLevel(2)) {\
if (arg) theTracer.traceStream()  << "Argument: " << #arg << " = TRUE"  << endl << BAS_DEFS_STD_GLOBAL(flush);\
if (!arg) theTracer.traceStream() << "Argument: " << #arg << " = FALSE" << endl << BAS_DEFS_STD_GLOBAL(flush);\
}

#define D_RETURN(arg) \
if (theTracer.checkLevel(2)) {\
theTracer.traceStream() << "Returning: " << #arg << " = " << arg << endl << BAS_DEFS_STD_GLOBAL(flush);\
}

#define D_PRINT(arg) \
if (theTracer.checkLevel(4)) {\
theTracer.traceStream() << "<> " << arg << endl << BAS_DEFS_STD_GLOBAL(flush);\
}

#define D_PRINT_T(arg) \
if (theTracer.checkLevel(4)) {\
char           timeBuffer[20]; \
pin_now_hrtime_to_str(&timeBuffer[0]); \
theTracer.traceStream() << "<" << timeBuffer << "> " << arg << endl << BAS_DEFS_STD_GLOBAL(flush);\
}

#define D_BPRINT(label, arg) \
if (theTracer.checkLevel(4)) {\
if (arg) theTracer.traceStream() << "<> " << label << " = TRUE" << endl << BAS_DEFS_STD_GLOBAL(flush); \
if (!arg) theTracer.traceStream() << "<> " << label << " = FALSE" << endl << BAS_DEFS_STD_GLOBAL(flush); \
}

#define D_LPRINT(label, arg) \
if (theTracer.checkLevel(4)) {\
theTracer.traceStream() << "<> " << label << " = " << arg << endl << BAS_DEFS_STD_GLOBAL(flush);\
}

#define D_CPRINT(label, arg) \
if (theTracer.checkLevel(4)) {\
theTracer.traceStream() << "<> " << label << " = " << arg << endl << BAS_DEFS_STD_GLOBAL(flush);\
}

#define D_IPRINT(label, arg) \
if (theTracer.checkLevel(4)) {\
theTracer.traceStream() << "<> " << label << " = " << arg << endl << BAS_DEFS_STD_GLOBAL(flush);\
}

#define D_SPRINT(label, arg) \
if (theTracer.checkLevel(4)) {\
theTracer.traceStream() << "<> " << label << " = " << arg << endl << BAS_DEFS_STD_GLOBAL(flush);\
}

#define D_HALT(arg) \
char myc;\
if (theTracer.checkLevel(8)) {\
theTracer.traceStream() << "<> halt: " << arg << endl << BAS_DEFS_STD_GLOBAL(flush);\
cin.get(myc);\
}

#define SELECT_DEBUG_LEVEL \
BAS::Trace::setStreamName("main"); \
BAS::Trace::selectDebugLevel();

#else

// empty macro-definitions in case of no tracing
#define D_THREADINFO 
#define D_THREADINFO_M
#define D_MULTITHREADED 
#define D_THREADSAFE 
#define D_SINGLETHREADED 
#define D_NONTHREADSAFE 
#define D_THREADNAME(arg)
#define D_ENTER(arg)
#define D_ENTER_F(arg)
#define D_LEAVE 
#define D_ARG(arg)
#define D_BARG(arg)
#define D_RETURN(arg)
#define D_PRINT(arg)
#define D_PRINT_T(arg)
#define D_BPRINT(label, arg)
#define D_LPRINT(label, arg)
#define D_CPRINT(label, arg)
#define D_IPRINT(label, arg)
#define D_SPRINT(label, arg)
#define D_HALT(arg) 
#define SELECT_DEBUG_LEVEL

#endif // TRACE

// C-procedure for signal-handler
extern "C" void dSelectDebugLevel(int);
namespace BAS
{
class ThreadInfo;

//------------------------------------------------------------------------------
/** class BAS::TraceStream.
An instance of this class is created for every thread in the program.
The instances are managed by the static BAS::Trace::streamTableCM.
*/
class TraceStream
{
  public:
    TraceStream();
    TraceStream(const TraceStream& orig);
    TraceStream(unsigned traceNum);
    ~TraceStream();

    int              level() const;
    void             increaseLevel();
    void             decreaseLevel();
    const RWCString& streamName() const;
    void             streamName(const RWCString& name);
    
    std::ofstream&  stream();


  private:
    int                       levelM;
    unsigned                  numM;
    RWCString                 streamNameM;
    OnlyPointer<ofstream> streamM;
};

//------------------------------------------------------------------------------
// functor for StreamTable
//------------------------------------------------------------------------------
struct UnsignedHash
{
  unsigned long operator()(const unsigned& num) const 
                {return (unsigned long) num;}
};       

// typedefs
typedef RWTValHashMap<unsigned, 
                      TraceStream, 
                      UnsignedHash, 
                      equal_to<unsigned> > StreamTable;

//------------------------------------------------------------------------------
/** Thread-enabled tracing macros and classes. 
  
     <P>The following macros are defined to simplify the usage of the tracing classes.
     To enable tracing, the macro '<tt>TRACE</tt>' has to be defined, otherwise the macros
     are zero-expanded.
   
     <P>An explanation of the trace-class '<tt>Trace</tt>' is following below.
     <P>NOTE: Direct usage of the class <tt>Trace</tt> is discouraged, always use the
     macro-interface.
  
     <dl>
     <dt><tt><b>SELECT_DEBUG_LEVEL</b></tt></dt>  
                           <dd>Should be the first executable line in the '<tt>main()</tt>',
                           selects a debug/trace level from the environment. Also defines the thread name "main".</dd>
     <dt><tt><b>D_THREADINFO</b></tt></dt>
                           <dd>This macro has to be put after class name.</dd>
     <dt><tt><b>D_THREADINFO_M</b></tt></dt>
                           <dd>This macro has to be put after the last class name in presence of a public
                           inheritance declaration.</dd>
     <dt><tt><b>D_THRREADSAFE</b></tt></dt>
                           <dd>This macro has to be defined in the class declaration for any
                           class identified as multithread-safe.</dd>
     <dt><tt><b>D_NONTHREADSAFE</b></tt></dt>
                           <dd>This macro can be defined in the class declaration for any
                           class identified as not multithread-safe. Since this is the default,
                           this is only a recommendation.</dd>
     <dt><tt><b>D_THREADNAME(arg)</b></tt></dt>
                           <dd>To enable the thread name feature, this macro has to be put at the
                           beginning of the function that is started in the thread, <b>before the
                           D_ENTER macro</b>. The string argument will be used as the thread name 
                           internally and in the log file suffix.</dd>
     <dt><tt><b>D_ENTER("routine")</b></tt></dt>  
                           <dd>Should be one of the first lines in every <b>member function</b>.</dd>
     <dt><tt><b>D_ENTER_F("routine")</b></tt></dt>  
                           <dd>Should be one of the first lines in every <b>ordinary function</b> (functions in which we do not have an instance pointer (<em>this)</em>).</dd>
     <dt><tt><b>D_ARG(variable)</b></tt></dt>   
                           <dd>Use where a printout of an argument is desired
                           (the variable must be printable by <<).</dd>
     <dt><tt><b>D_BARG(variable)</b></tt></dt>
                           <dd>Use where a printout of an argument is desired
                           (the variable must be a boolean).</dd>
     <dt><tt><b>D_RETURN(variable)</b></tt></dt>
                           <dd>Use where printout of a returned value is desired
                           (the variable must be printable by <<).</dd>
     <dt><tt><b>D_PRINT(expression)</b></tt></dt>
                           <dd>Prints the expression which can be of the form:
                           "value found: " << value.</dd>
     <dt><tt><b>D_PRINT_T(expr.)</b></tt></dt>
                           <dd>Prints the expression as described for D_PRINT,
                           associated with the current time.</dd>
     <dt><tt><b>D_BPRINT(label, variable)</b></tt></dt>
                           <dd>Use to print the name of a variable and its value 
                           (the variable must be a boolean).</dd>
     <dt><tt><b>D_LPRINT(label, variable)</b></tt></dt>
                           <dd>Use to print the name of a variable (label) and its value
                           (the variable must be printable by << ).</dd>
     <dt><tt><b>D_HALT(expression)</b></tt></dt>
                           <dd>Prints the expression, halts the program and waits
                           for 'Return' to be pressed.</dd>
     </dl> 

     <p>The debug/tracing is switched on by setting the environment variable <tt>DEBUG</tt>
     according to the following rule:
       <p><pre>-l Level -d [ all | Function Name | :Function Name] [-d ...] ...</pre>
  
     <p>Levels are:
     <dl>
       <dt><tt><b>1</b></tt></dt> Enter/Leave
       <dt><tt><b>2</b></tt></dt> Argument/Return value
       <dt><tt><b>4</b></tt></dt> Print
       <dt><tt><b>8</b></tt></dt> Halt
     </dl>
  
     <p>The options can be or'ed together i.e. '<tt>-l 15 -d all</tt>' means tracing on
     Enter/Leave, Argument/Return value and Print in all functions.
  
     <p><tt>-d Function Name</tt> includes tracing for all functions starting with the
     string specified.
  
     <p><tt>-d :Function Name</tt> excludes tracing for all functions starting with the
     string specified (must be specified before '<tt>-d all</tt>').
  
     <p>Several <tt>-d</tt>'s may be specified.
  
     <p>Trace may be turned on/off by sending signal <tt>SIGUSR2</tt> to process.
     Trace-info is then read from file "<tt>./TRACE</tt>".

     <p>In Windows Trace may be turned on/off by sending signal <tt>CTRL+C (hold down the CTRL key and press “C”) </tt> to process.
     Trace-info is then read from file "<tt>./TRACE</tt>".
  
     <p>The trace output is written to files called trace.log.<thread number> in 
     the current directory. The main thread (even for non-multithreaded 
     programs) is always '<tt>1</tt>'. 
*/
class Trace
{
  public:
    // Constructor
    Trace(const char* routine, const char* file , int line, const ThreadInfo* tracedObj=0);

    // Destructor
    ~Trace();

    // this static method must be called at first
    // (used in macro SELECT_DEBUG_LEVEL) 
    static void selectDebugLevel(void);

    // print messages at debuglevel 1
    void printMsgL1(const RWCString&   val);
    // print messages at debuglevel 2
    void printMsgL2(const RWCString&   val);

    // print messages at debuglevel 4
    void printMsgL4(const RWCString&   val);
      
    // print information about arguments at debuglevel 2 
    void printArgL2(const int          val, const char* label = 0);
    void printArgL2(const double       val, const char* label = 0);
    void printArgL2(const char*  const val, const char* label = 0);
    void printArgL2(const RWCString&   val, const char* label = 0);

    // print information about return-values at debuglevel 2
    void printRetL2(const int         val, const char* label = 0);
    void printRetL2(const double      val, const char* label = 0);
    void printRetL2(const char* const val, const char* label = 0);
    void printRetL2(const RWCString&  val, const char* label = 0);

    // print information about bool-values at debuglevel 2
    void printBoolL2(const int        val, const char* label = 0);

    // print information about arguments at debuglevel 4
    void printArgL4(const int         val, const char* label = 0);
    void printArgL4(const double      val, const char* label = 0);
    void printArgL4(const char* const val, const char* label = 0);
    void printArgL4(const RWCString&  val, const char* label = 0);

    // print information about bool-values at debuglevel 4      
    void printBoolL4(const int        val, const char* label= 0);

    // halts the program and prints information at debuglevel 8
    void haltL8(const int             val, const char* label = 0);
    void haltL8(const double          val, const char* label = 0);
    void haltL8(const char* const     val, const char* label = 0);
    void haltL8(const RWCString&      val, const char* label = 0);

    // public method to check if the actual level was set before
    // in Trace::selectDebugLevel
    bool checkLevel(int level);

    // class function members
    // This function returns the trace stream belonging
    // to the current thread. The stream is created if necessary.
    static std::ofstream&        traceStream();
    static void             setStreamName(const RWCString& name);
    static const RWCString& getStreamName();
    static const RWCString& getStreamName(unsigned threadNum);
    static unsigned         getThreadId();

  private:
    // class data members
    BAS_EXPORT static int  debugLevelCM;
    BAS_EXPORT static int  numOfFunctionsCM;
    BAS_EXPORT static char functionNamesCM[MAX_NUM_OF_FUNCTIONS][MAX_FUNCTION_LEN];
    BAS_EXPORT static int  functionNameLengthsCM[MAX_NUM_OF_FUNCTIONS];
    BAS_EXPORT static bool traceIsOnCM;
    BAS_EXPORT static bool firstTimeCM;

    //-------------------------------------------------------------------
    // Stream table changed to a pointer, because the order of destructor
    // calls is unspecified for static objects and if D_ENTER() is called
    // in the destructor of a static class, a segmentation fault occurs.
    // DO NOT DELETE THE STREAM TABLE OBJECT !!!
    //-------------------------------------------------------------------
    BAS_EXPORT static StreamTable* streamTableCM;

    // class function members
    static TraceStream& stream();
    static TraceStream& stream(unsigned threadNum);
    static int              actualLevel();
    static void             increaseActualLevel();
    static void             decreaseActualLevel();

    // private member functions
    bool        checkLevel(int level, const char* routine);
    const char* fileName(const char* name) const;

    // instance members
    // name of the actual routine and the tracefile-name
    const char* routineNameM;
    const char* fileNameM;
};

// inlines
inline std::ofstream&
Trace::traceStream()
{
  return Trace::stream().stream();
}

inline int
Trace::actualLevel()
{
  return Trace::stream().level();
}

inline void
Trace::increaseActualLevel()
{
  Trace::stream().increaseLevel();
}

inline void
Trace::decreaseActualLevel()
{
  Trace::stream().decreaseLevel();
}

inline
TraceStream::TraceStream()
               :levelM(0), 
                numM(0) 
{
}

inline
TraceStream::TraceStream(const TraceStream& orig)
{
  if (this != &orig)
  {
    levelM  = orig.levelM;
    numM    = orig.numM;
    streamM = orig.streamM;
  }
}

inline
TraceStream::TraceStream(unsigned traceNum)
               :levelM(0), 
                numM(traceNum),
                streamM(0)
{
}

inline
TraceStream::~TraceStream()
{
}

inline int
TraceStream::level() const
{
  return levelM;
}

inline void
TraceStream::increaseLevel()
{
  levelM++;
}

inline void
TraceStream::decreaseLevel()
{
  levelM--;
}

inline ofstream&
TraceStream::stream()
{
  if (streamM == (const std::ofstream*)0)
  { 
    stringstream str;
    str << "trace.log." << streamName();

    RWCString fileName;
    fileName.readLine(str);
    streamM = new std::ofstream(fileName, ios::out | ios::app);
  }

  return *streamM;
}

inline const RWCString& 
TraceStream::streamName() const
{
  if (streamNameM.isNull())
  {
    RWCString* streamNamePtr = const_cast<RWCString*>(&streamNameM);
    stringstream str;
    str << std::setw(3) << std::setfill('0') << numM;
    streamNamePtr->readLine(str);
  }
  return streamNameM;
}

inline void
TraceStream::streamName(const RWCString& name)
{
  streamNameM = name;
}
}
#endif  // TRACE_HPP

