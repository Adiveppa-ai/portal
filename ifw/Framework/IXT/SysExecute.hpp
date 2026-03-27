#ifndef IXT_SYSEXECUTE_HPP
#define IXT_SYSEXECUTE_HPP
//==============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class IXT::SysExecute.
//==============================================================================
#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

#ifndef   RW_TOOLS_CTOKEN_H
  #include <rw/ctoken.h>
#endif
#include <rw/network/except.h>
#include <rw/network/RWSocket.h>
#include <rw/network/RWSockType.h>
#ifndef   __rw_sync_RWMutexLock_h__
  #include <rw/sync/RWMutexLock.h>
#endif
#ifndef   __rw_sync_RWTLockGuard_h__
  #include <rw/sync/RWTLockGuard.h>
#endif

#include <unistd.h>

namespace SCR
{
  class Interpreter;
  class ParserStack;
  class FctDescr;
}

namespace IXT
{
  class Integrate;

  /** <b><tt>SysExecute</tt></b> is the iScript function node to execute
   *  external files and command scripts.
   */
  class SysExecute : public SCR::LongNode
  {
    public:
      /**@name SysExecute constructors and destructor */
      //@{

      /** Destructor */
      virtual ~SysExecute();

      //@}

      /**@name SysExecute public methods */
      //@{

      /** Execute the system command
       *  @return The the exit code
       */
      virtual int64 result();

      /** Create a sysExecute() function node
       *  @param interpreter Interpreter for the function
       *  @param stack Stack with parameters, etc.
       *  @param descr The function description
       *  @return <b>Pointer</b> on success, <b>0</b> otherwise
       */
      static SCR::Node* factory(SCR::Interpreter&	interpreter,
				SCR::ParserStack&	stack,
				const SCR::FctDescr&	descr);

      //@}

    protected:

      /** Constructor
       *  @param commandNode The command to execute
       *  @param outputBufferNode The optional buffer for the output
       */
      SysExecute(Integrate*		extension,
		 SCR::StringNode*	commandNode,
		 SCR::StringDataNode*	outputBufferNode,
		 SCR::LongNode*		timeToWait);

    private:
      // Hide default and copy constructors, and the equalto operator
      SysExecute();
      SysExecute(const SysExecute&);
      const SysExecute& operator=(const SysExecute&);

      // instance members
      SCR::StringNode*     commandNodeM;
      SCR::StringDataNode* outputBufferNodeM;
      SCR::LongNode*  timeToWaitM;
  };
}
#endif // IXT_SYSEXECUTE_HPP
