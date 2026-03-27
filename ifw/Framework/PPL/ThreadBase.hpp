#ifndef PPL_THREADBASE_HPP
#define PPL_THREADBASE_HPP
//==============================================================================
//
// Copyright (c) 1996, 2008, Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PPL
//
//------------------------------------------------------------------------------
// Module Description:
//   Standard thread interface class implementation for the pipeline-moduls.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Marco Liebmann
//
// $RCSfile: ThreadBase.hpp $
// $Revision: /cgbubrm_7.3.2.pipeline/1 $
// $Author: knijhawa $
// $Date: 2008/11/05 05:30:07 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: ThreadBase.hpp,v $
// Revision 1.1  2001/11/21 10:36:49  mliebmann
// PETS #41918 new base class for single-thread pipeline and necessary modifiations
//
//==============================================================================

#ifndef   QUEUE_HPP
  #include "STR/Queue.hpp"
#endif
#ifndef   BAS_THREAD_HPP
  #include "BAS/Thread.hpp"
#endif
#ifndef   PLI_STDINTERFACE_HPP
  #include "PLI/StdInterface.hpp"
#endif
#ifndef   BAS_OBJECT_H
  #include "BAS/Object.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif

//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------
namespace EDR
{
class Container;
}
namespace PPL
{
typedef RWTPtrOrderedVector<EDR::Container> EdrContainerList;


/** This class represents the standard thread interface for the pipeline-moduls.
    This class is the base functionality of all pipeline-moduls. You can
    use the pipeline with one or multiple threads. And each pipeline can be
    configured for its own requirement.
    <br>For this the pipeline has to be configured with an registry-value.
    
    <br><br><b>Single-threaded pipeline:</b>
    <br>The pipeline runs with only one thread. This is solved by starting only one 
    thread in the input-controller (input-modul). This modul pushes each 
    container or a list of container into the next (here function-plugin). And 
    this plugin into the necxt plugin and then into the output-modul. Only when 
    this is be done the input-modul becomes the control back to read and push 
    the next container into the next plugin.
    <br>Constructor used: ThreadBase with the pointer-parameter to the next 
    modul.
    
    <br><br><b>Multi-threaded pipeline:</b>
    <br>In case of multithreaded use of the pipeline each modul has it's own thread 
    and they are linked together with queues. 
    The input-modul pushes each edr into the queue by using the pushEdr(..)-
    method. Then each following plugin and output-modul polls with there own 
    thread on the queues to process the EDR-containers.
    <br>Contructor used: ThreadBase with queue-parameter to the queue between
    of the moduls/plugins.<br><br>
 
    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: ThreadBase.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.3.2.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2008/11/05 05:30:07 $</font></td>
    <td><font size=-1>$Author: knijhawa $</font></td>
    </tr>
    </table>  

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>none</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_CONTROLLER_CONFIGURATION</dd>
    <dd>ERR_CONTROLLER_HAS_WRONG_TYPE</dd>
</dl> 
*/
class ThreadBase : public BAS::Object
{
  public:
  
    enum ControllerTypeT
    {
      INPUTCONTROLLER_TYPE,
      OUTPUTCONTROLLER_TYPE,
      FUNCTIONCONTROLLER_TYPE
    };

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      ThreadBase();

      /**@name multi-thread-pipeline Constructors with queues*/
      //@{

        /** Constructs a instance to a control modul.<br> 
          * This constructor is called for multihtreaded execute of the pipeline.
          * The controllertype is only set with one queue in case of 
          * INPUTCONTROLLER_TYPE or OUTPUTCONTROLLER_TYPE.
          * @param objectName The string is used for the object registration.
          * @param queue Input- or output-queue for multipl-threads.
          * @param controllerType Shows the input- or output-controllertype.
          * Also the registry entries are searched with it. */
        ThreadBase(const BAS::String& objectName,
                             STR::Queue<EDR::Container*>* queue,
                             ControllerTypeT controllerType);

        /** Constructs a instance to a control modul.<br> 
          * The plug in function execute() is called in the newly created thread.
          * In case of two queue the controllertype is automatically a
          * FUNCTIONCONTROLLER_TYPE.
          * @param objectName The string is used for the object registration.
          * @param inputQueue Input-queue for multipl-threads.
          * @param outputQueue Output-queue for multipl-threads.
          */
        ThreadBase(const BAS::String& objectName,
                             STR::Queue<EDR::Container*>* inputQueue,
                             STR::Queue<EDR::Container*>* outputQueue);

      //@}
      
      /**@name single-thread-pipeline Constructors without queues*/
      //@{
      
        /** Constructs a instance to a control modul.<br> 
          * The plug in function execute() is called in the newly created thread.
          * Used by the Input- and FunctionControll-Controller
          * @param objectName The string is used for the object registration.
          * @param nextPPLObject Pointer to the next pipeline object for processing
          * @param controllerType Shows the input- or output or functioncollection-
          *                       controllertype.
          * Also the registry entries are searched with it. */
        ThreadBase(const BAS::String& objectName,
                             ThreadBase * nextPPLObject,
                             ControllerTypeT controllerType );

        /** Constructs a instance to a control modul.<br> 
          * The plug in function execute() is called in the newly created thread.
          * The pointer nextPPLObject is set to null in this case! Only used
          * by OutputController!
          * @param objectName The string is used for the object registration.
          * @param controllerType Shows the input- or output or functioncollection-
          *                       controllertype.
          * Also the registry entries are searched with it. */
        ThreadBase(const BAS::String& objectName,
                             ControllerTypeT controllerType );
      //@}
      
    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~ThreadBase();

    //@}

    /**@name Public Member Thread Functions */
    //@{

      /** Thread execute method in which the thread runs!
        * <b>Multithread pipelines:</b>
        * One thread for the input-modul, one thread for the output-modul
        * and several threads for the function-plugins.
        * <b>Singlethread pipelines:</b>
        * In case of use of one thread for each pipeline, only the input-
        * modul has to implement the execute()-method.
        */
      virtual void execute() = 0;

    //@}

    /**@name Public Member Functions */
    //@{
    
      /** Push edr into plugin/modul from Function or outpup-modul.
        * Has to be implemented, but not used in the input-modul!
        * @param EdrContainerList* EDRList of processable EDRs.
        * @return <tt>true </tt> True  on success.
        *         <tt>false</tt> False on failure.
        */
      virtual bool processEdrContainer(EdrContainerList* edrList) = 0;
    
      /** Get an EDR from the queue.<br> 
        * <b>Only be used for plugin developer in the output- and 
        * function-modul for there own threads!</b>
        * @param EDR::Container* Shows the pointer to the EDR-Container.
        * @return <tt>true </tt> True  on success.
        *         <tt>false</tt> False on failure.
        */
      bool readEdr(EDR::Container*& edr);
    
      /** Push of EDRs into the next modul or into the queue.<br> 
        * <b>Only be used for plugin developer in the input-modul!</b>
        * @param EDR::Container* Shows the pointer to the EDR-Container.
        * @return <tt>true </tt> True  on success.
        *         <tt>false</tt> False on failure.
        */
      virtual bool pushEdr(EDR::Container* edr);

      /** Call for usibility
        * @return <tt>true </tt> True,  if usable.
        *         <tt>false</tt> False, if not usable.
        */
      virtual bool isUsable();

      /** Log writing method.
          Creates a log command for the pipeline object
          and sends it.
          @param s The status to be logged.
      */
      void writeToPipelineLog(const BAS::Status& s) const;

      // abort plug in 
      virtual void requestAbort();

    //@}

  protected:
  
    /**@name Protected Member Functions*/
    //@{

      /** Starts the thread with its execute statment
        * @return <tt>true </tt> True  on success.
        *         <tt>false</tt> False on failure.
        */
      bool initThread();

      /** Pushes an EDR-List into the next plugin or pushes each individual 
        * container into the output-queue.<br> 
        * @param EdrContainerList* Shows the pointer to the EDR-Container.
        * @return <tt>true </tt> True  on success.
        *         <tt>false</tt> False on failure.
        */
      virtual bool pushEdr(EdrContainerList* edrList);

    //@}

  private:

    // internal use only
    bool x_or(const bool a, const bool b);

    BAS::RegisteredObject*                       pipelineLogM;

    // Thread-class
    BAS::Thread                  threadM;

    // Classtype
    ControllerTypeT             controllerTypeM;

    // Pointer to itself for one-threadoperation
    ThreadBase *            nextPPLObjectM;

    // Queue-definitions
    STR::Queue<EDR::Container*> * inputQueueM;
    STR::Queue<EDR::Container*> * outputQueueM;
    
    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.
    ThreadBase(ThreadBase& right);
    const ThreadBase& operator=(ThreadBase& right);
};

//------------------------------------------------------------------------------
// inline
//------------------------------------------------------------------------------
inline bool
ThreadBase::x_or(const bool a, const bool b)
{
  return ((a && !b) || (!a && b));
}
}
#endif // THREADBASE_HPP

