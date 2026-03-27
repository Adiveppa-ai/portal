#ifndef PPL_IPCQUEUES_HPP
#define PPL_IPCQUEUES_HPP 1
//=============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: PPL
//-----------------------------------------------------------------------------
// Module Description:
//   This class is the PPL::IPCQueues Implementations.
//   It holds the information about IPCQueues used in AAA GW
//   Pipeline Name.
// Current Issues:
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        rtang   
// Backup-Responsible: 
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------
//-------------------------------------------
// 21-Apr-05	rtang  			PRSF00165066 - Add Web Instrument for IPCQueues

#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   QUEUE_HPP
  #include "STR/Queue.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif

namespace PPL
{

class IPCQueues : public BAS::RegisteredObject
{
  public:

    /** Public constructor
     * @parm objectName, the name of the object
     */
    IPCQueues(const BAS::String&);

    /** Destructor
     */
    virtual ~IPCQueues();
   
     /** Read Registry
      */
     bool readRegistry();

     /** Routine to process incoming messages.
      * @param msg The incoming message. */
     virtual void receiveRequest(BAS::Message& msg);

    /** Generate pretty content for the AAA web server.
     */
    BAS::String generateWebPage(const BAS::Message& msg);

     /** log down the status of IPCQueues
      */
     void  writeQueueStatus();

  private:
     
    // Hiding
    IPCQueues(const IPCQueues&);
    const IPCQueues& operator=(const IPCQueues&);

    RWTPtrVector<STR::Queue<EDR::Container*> > queuesM;
};
}
#endif
