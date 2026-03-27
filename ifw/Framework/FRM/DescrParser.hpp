#ifndef FRM_DESCRPARSER_HPP
#define FRM_DESCRPARSER_HPP
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
// Block: FRM
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the helper class used by the Yacc parser that parses the
//   configuration files. This class was only created because the SUN CC 
//   compile had problems with the templates database. To fix this problem
//   I had to move all the actions from the Yacc source code to member 
//   functions of this class.
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: DescrParser.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:48 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DescrParser.hpp,v $
// Revision 1.4  2012/05/14 Santanu
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER
//
// Revision 1.3  2001/09/27 12:01:17  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.2  2001/06/21 10:15:09  sd
// - FileDescr renamed to StreamDescr
//
// Revision 1.1  2001/05/03 16:29:23  bt
// Base moved to FRM (Format renamed to Pipeline).
//
// Revision 1.3  2001/05/03 09:52:42  sd
// - use statement for type extensions introduced
// - bugfix in insertRecordPrototype()
//
// Revision 1.2  2001/04/12 12:44:27  sd
// - Update for the new modules EDR::Base, Base and IXT
//
// Revision 1.1  2001/04/12 09:49:48  sd
// - Creation of module Base
//
// Revision 1.8  2001/04/02 09:13:22  sd
// - BlockDescr renamed to RecordDescr
//
// Revision 1.7  2001/03/21 08:34:57  sd
// - Now multiple file and mapping descriptions are supported.
//
// Revision 1.4  2001/03/16 16:03:13  sd
// - ASN blocks added
//
// Revision 1.3  2001/03/13 13:45:35  sd
// - Backup version
//
// Revision 1.2  2001/03/07 15:02:39  sd
// - Backup
//
// Revision 1.1  2001/03/07 14:01:08  sd
// - New class DescrParser introduced
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_PARAMETER_HPP
  #include "EDR/Parameter.hpp"
#endif
#ifndef   EDR_DATABLOCKDESCR_HPP
  #include "EDR/DatablockDescr.hpp"
#endif

namespace EDR
{
class FieldDescr;
class DatablockDescr;
}
namespace FRM
{
class DataDescr;
class StreamDescr;
class RecordDescr;
class InputMapping;
class OutputMapping;

typedef enum
{
  IN_MAPPING,
  OUT_MAPPING
} MappingModeT;


/** <b><tt>DescrParser</tt></b> is used by the Yacc parser that parses
 *  the input files like grammar description etc. This class was introduced
 *  because of some problems with the Solaris templates database when this
 *  functions were directly inserted in the Yacc source code.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DescrParser.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:48 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>
 */
class DescrParser D_THREADINFO_M
{
  public:
    /**@name DescrParser constructors and destructor */
    //@{

    /** Constructor
     */
    DescrParser();

    /** Destructor
     */
    virtual ~DescrParser();

    //@}


    /**@name DescrParser public methods */
    //@{

    /** Set the failure description
     *  @param msg New failure description
     */
    void failure( const BAS::String& msg );

    /** Get the failure description
     *  @return Reference to failure string
     */
    const BAS::String& failure();

    /** Set the current file description
     *  @param name The name of the file description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setFileDescr( const BAS::String& name );

    /** Set the current record description
     *  @param name The name of the record description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setRecordDescr( const BAS::String& name );

    /** Begin the processing of a new mapping set
     *  @param name The name of the mapping set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool beginMappingSet(const BAS::String& name);

    /** Process a mapping entry
     *  @param arrow The arrow symbol used in description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool processMappingEntry( const BAS::String& arrow );

    /** Finish the processing of a new mapping set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool finishMappingSet();

    /** Push a parameter to the parameter stack
     *  @param parameter The parameter to push on the stack
     */
    void pushParameter( const EDR::Parameter& parameter );

    /** Load and use a type extension
     *  @param name The name of the type extension to load
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool useTypeExtension( const BAS::String& name );

    /** Add a new file description
     *  @param name The name of the file description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addFileDescr( const BAS::String& name );

    /** Add a new datablock description to the EDR Factory
     *  @param datablockDescr pointer to the datablock description
     */
    void addDatablockDescription(EDR::DatablockDescr* datablockDescr);

    /** Add datablock within datablock
     *  @param targetBlock Datablock to which the subblock is to be added
     *  @param blockName Name for the subblock
     *  @param blockType Type of the subblock
     *  @param flags whether optional/mandatory
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addDatablockInDatablock(const BAS::String& targetBlock, const BAS::String& blockName, const BAS::String& blockType, const BAS::String& flags);

    /** Setup the internal structures, must be called at the end of all modifications to EDR
     *  @param flags true or false
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setupAllPrototypes(bool flags);

    /** Creates a new Datablock description
     *  @param name The name of the new Datablock description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool newDatablockDescription(const BAS::String& name);

    /** Add a leaf field to the last created datablock description
     *  @param name The name of the leaf field
     *  @param type Type of the leaf, Integer, Date etc.
     *  @param flags whether optional, required etc.
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addValue(const BAS::String& name, const BAS::String& type, const BAS::String& flags);

    /** Add a subblock field to the last created datablock description
     *  @param name The name of the subblock field
     *  @param type Type of the subblock field
     *  @param flags whether optional, required etc.
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addBlock(const BAS::String& name, const BAS::String& type, const BAS::String& flags);

    /** Processes any new datablock descriptions added
     */
    void processNewDatablockDescriptions();

    /** Create a new record description
     *  @param name The name of the record description
     *  @param type The type of the record (FIX,SEPARATED etc.)
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool createRecordDescr( const BAS::String& name,
                                  const BAS::String& type );
    
    /** Do the final setup for the current record description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setupRecordDescr();

    /** Get the current record description
     *  @return Pointer to the current record description
     */
    RecordDescr* curRecordDescr();

    /** Begin a new field description
     *  @param type The type of the field
     *  @param name The name of the field
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool beginFieldDescr( const BAS::String& name,
                                 const BAS::String& type );

    /** Finish the last field description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool finishFieldDescr();

    /** Add a new info parameter to the record description
     *  @param name The name of the new input parameter
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addRecordDescrParameter( const BAS::String& name );

    /** Append new iScript source code
     *  @param source The source code to append
     */
    void appendIScriptSource( const BAS::String& source );

    /** Get the number of non-terminal symbols
     *  @return number of non-terminal symbols
     */
    size_t numNonTerminals();

    /** Add a new non-terminal symbol
     *  @param name The name of the symbol
     */
    void addNonTerminal( const BAS::String& name );

    /** Get a non-terminal symbol name
     *  @param idx The index of the symbol
     *  @return Reference to symbol name
     */
    const BAS::String& nonTerminal( size_t idx );
    
    
    /** Set the start symbol name
     *  @param name The name of the symbol
     */
    void startSymbol( const BAS::String& name );

    /** Get the name of the description file
     *  @return the name of the file
     */
    const BAS::String& getFileName() const;

    //@}


  protected:
    int64 getLineNumber() const;
    void setLineNumber(int64 lineNumer);
    void incrementLineNumber();

    void setFileName(const BAS::String& fileName);
    
    bool getIScriptMode() const;
    void setIScriptMode(bool flag);
    
    void setBraceLevel(int braceLevel);
    void setiScriptBuffer(const BAS::String& iScriptBuffer);
    void setCurMappingMode(MappingModeT mappingMode);

    DataDescr* getCurDataDescr();
    void setCurDataDescr(DataDescr* dataDescr);
    
    const BAS::String& getFailure() const;
    const BAS::String& iScriptSource();
    int error(const char msg[], const BAS::String& FRM_lval);

  private:
    // class members
    BAS::String                                 failureM;
    BAS::String                                 startSymbolM;
    BAS::StringList                             nonTerminalsM;
    RWTValOrderedVector<EDR::Parameter>         parameterStackM;
    
    DataDescr*                             curDataDescrM;
    StreamDescr*                             curFileDescrM;
    RecordDescr*                           curRecordDescrM;
    EDR::FieldDescr*                            curFieldDescrM;
    BAS::String                                 curFieldDescrTypeNameM;
    InputMapping*                          curInputMappingM;
    OutputMapping*                         curOutputMappingM;
    MappingModeT                           curMappingModeM;

    EDR::DatablockDescr* currDatablockDescrM;
    RWTPtrOrderedVector<EDR::DatablockDescr> newBlockDescriptionsM;

    BAS::String fileNameM;
    BAS::String iScriptBufferM;
    int lineNumberM;
    int braceLevelM;
    bool switchToIScriptModeM;
};

//==============================================================================
// Get the failure description
//==============================================================================
inline const BAS::String&
DescrParser::failure()
{
  return failureM;
}

//==============================================================================
// Get the current record description
//==============================================================================
inline RecordDescr*
DescrParser::curRecordDescr()
{
  return curRecordDescrM;
}

inline const BAS::String&
DescrParser::iScriptSource()
{
	return iScriptBufferM;
}

inline void
DescrParser::setIScriptMode(bool flag)
{
	switchToIScriptModeM = flag;
}

inline bool
DescrParser::getIScriptMode() const
{
     return switchToIScriptModeM;
}

inline const BAS::String&
DescrParser::getFileName() const
{
    return fileNameM;
}

inline void
DescrParser::setBraceLevel(int braceLevel)
{
   braceLevelM = braceLevel;
} 

inline void
DescrParser::setiScriptBuffer(const BAS::String& iScriptBuffer)
{
   iScriptBufferM = iScriptBuffer;
}

inline int64
DescrParser::getLineNumber() const
{
    return lineNumberM;
}

inline void 
DescrParser::setCurDataDescr(DataDescr* dataDescr)
{
     curDataDescrM = dataDescr;
}

inline DataDescr* 
DescrParser::getCurDataDescr()
{
   return curDataDescrM;
}

inline void
DescrParser::setCurMappingMode(MappingModeT mappingMode)
{   
    curMappingModeM = mappingMode;
}

inline int
DescrParser::error(const char msg[], const BAS::String& FRM_lval)
{
  failureM = 
    BAS::String("error line ") + 
    BAS::String().convert(getLineNumber()) +
    BAS::String(": ") + 
    BAS::String(msg) + 
    BAS::String(" before `") + 
    BAS::String(FRM_lval) + 
    BAS::String( "'" );    
  return -1;
}

inline void
DescrParser::incrementLineNumber()
{
   lineNumberM++;
}

inline void
DescrParser::setFileName(const BAS::String& fileName)
{
    fileNameM = fileName;
}

inline void 
DescrParser::setLineNumber(int64 lineNumer)
{
   lineNumberM = lineNumer;
}

}

#endif // DESCRPARSER_HPP
