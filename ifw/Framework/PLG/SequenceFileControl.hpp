#ifndef PLG_SEQUENCE_FILE_CONTROL_HPP
#define PLG_SEQUENCE_FILE_CONTROL_HPP
//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PLG
//------------------------------------------------------------------------------
// Module Description:
//   Sequence controller with file interface
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// CodeReview - 07.2000 - jkeckstein - I - This is not true.
// Responsible: Alexander Rockel
//
// $RCSfile: SequenceFileControl.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: kkisalay $
// $Date: 2012/01/27 03:19:15 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: SequenceFileControl.hpp,v $
// Revision 1.8  2002/03/13 10:53:59  mliebmann
// PETS #39719 sequencer mod for Rap/Tap: backup for ClearCase migration
//
// Revision 1.7  2000/09/29 12:29:44  aro
// Tried to fix doc++ comments.
//
// Revision 1.6  2000/07/21 13:37:32  jkeckst
// code review CR-07-2000
//
// Revision 1.5  2000/06/16 08:43:29  bt
// Changes for AIX xlC V366.
//
// Revision 1.4  2000/02/25 07:55:54  clohmann
// Class description added.
//
// Revision 1.3  2000/02/23 15:48:03  clohmann
// Sequence sharing added.
//
// Revision 1.2  2000/02/17 09:14:44  clohmann
// Sequence handler redesign.
//
// Revision 1.1  2000/02/16 10:11:02  clohmann
// Initial checkin.
//
//==============================================================================

#ifndef   PLG_SEQUENCE_CONTROL_HPP
  #include "PLG/SequenceControl.hpp"
#endif
#ifndef   STR_FILEIO_HPP
  #include "STR/FileIo.hpp"
#endif
#ifndef   LOG_STREAMDATE_HPP
  #include "LOG/StreamDate.hpp"
#endif
namespace PLG
{
/** This class implements a sequence controller wich holds his
    control and log information in files. 
    This controller can be used if integrate is running without a database.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: SequenceFileControl.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2012/01/27 03:19:15 $</font></td>
    <td><font size=-1>$Author: kkisalay $</font></td>
    </tr>
    </table>                                                                          

<p><dl>
   <dt><b>Registry entries</b></dt>
         <dd>none</dd>
    <dt><b>Messages send</b></dt>
         <dd>none</dd>
    <dt><b>Messages received</b></dt>
         <dd>none</dd>
    <dt><b>Requests send</b></dt>
         <dd>REQ_REJECT_STREAM</dd>
    <dt><b>Requests received</b></dt>
         <dd>none</dd>
    <dt><b>Errors</b></dt>
         <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
         <dd>ERR_REG_ENTRY_NOT_FOUND</dd>
         <dd>ERR_SEQ_FILE_INVALID</dd>
         <dd>ERR_SEQ_INIT</dd>
         <dd>ERR_SEQ_ENTRY_NOT_FOUND</dd>
         <dd>ERR_NO_SEQ_VALUE</dd>
         <dd>ERR_SEQ_SAVE</dd>
         <dd>ERR_SEQ_ALREADY_PROCESSED</dd>
</dl>
*/
class SequenceFileControl : public SequenceControl
{
  public:

    /**@name SequenceFileControl Constructors and Destructors */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    SequenceFileControl();
                                             
    /** Standard constructor.<br>
        Creates an registered sequence controller.
        @param name The name for the created object.
        @param check True if sequence check is active.
        @param generate True if sequence generation is active.
    */
    SequenceFileControl(const BAS::String& name);

    /** Destructor. */
    virtual ~SequenceFileControl();
    //@}                                   

    /**@name Main methods. */
    //@{

    /** Initialise the sequence controller.
    */
    virtual bool init();

    //@}

  protected:
    /** Initialise an instance from the registry.
        @return <tt>False</tt> if the object could not initialise itself successfully,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool readRegistry();         

    /** Initilialise from environment.
        @return <tt>False</tt> if the object could not read the environment information,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool evalEnvironment();

    /** Check the original sequence number.
    */
    virtual bool checkForDouble(const BAS::String & seqCkeckKey);

    /** write the sequence data into the sequence file
    */
    virtual bool writeSequenceInformation(const BAS::String & key, const TAM::TransId & transId);

    /** log the actual sequence information.
    */
    virtual bool logSequenceInformation( SequencerInformation& seqInfo);

    /** log the actual sequence information for input-check.
    */
    virtual bool logSequenceInformation_In( SequencerInformation_In& seqInfo_in);
												 
	/** Commit the file operations */
    virtual bool commitToStorage();

    /** Rollback the file operations */
    virtual bool rollbackFromStorage();

  private: 

    // not implemented
    SequenceFileControl(SequenceFileControl&);
    void operator=(const SequenceFileControl&);

    // key words for sequencer file
    PLG_EXPORT static const BAS::String sequenceNumberCM;
    PLG_EXPORT static const BAS::String originalSequenceNumberCM;
    PLG_EXPORT static const BAS::String offsetCM;
    PLG_EXPORT static const BAS::String maxSequenceNumberCM;
    PLG_EXPORT static const BAS::String maxOffsetCM;
    PLG_EXPORT static const BAS::String minSequenceNumberCM;
    PLG_EXPORT static const BAS::String minOffsetCM;
    PLG_EXPORT static const BAS::String keyCM;
    PLG_EXPORT static const BAS::String gapSequenceNumbersCM;
    
    // registry strings
    PLG_EXPORT static const BAS::String registrySequenceFilePathCM;
    PLG_EXPORT static const BAS::String registrySequenceFileNameCM;
    PLG_EXPORT static const BAS::String registrySequenceLogCM;

    // sequence log object
    BAS::OnlyPointer<LOG::StreamDate> sequenceLogM;
   
    // root name in sequence file
    BAS::String sequenceDataRootM;

    // stream for sequence file
    BAS::OnlyPointer<STR::FileIo> streamM;

    // file path and name
    BAS::String filePathM;
    BAS::String fileNameM;
};
}
#endif 
