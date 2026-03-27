#ifndef FRM_DATADESCR_HPP
#define FRM_DATADESCR_HPP
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
//   Class containing information about all in- and output formats.
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
// $RCSfile: DataDescr.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:47 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DataDescr.hpp,v $
// Revision 1.5  2012/05/14  Santanu 
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER
//
// Revision 1.4  2001/09/27 12:01:17  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.3  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.2  2001/06/21 10:15:09  sd
// - FileDescr renamed to StreamDescr
//
// Revision 1.1  2001/05/03 16:29:23  bt
// Base moved to FRM (Format renamed to Pipeline).
//
// Revision 1.2  2001/04/27 10:06:16  sd
// - New functions (needed by the ASN iScript extension) added
//
// Revision 1.1  2001/04/12 09:49:48  sd
// - Creation of module Base
//
// Revision 1.9  2001/04/05 09:28:24  sd
// - Backup version
//
// Revision 1.8  2001/04/02 09:13:22  sd
// - BlockDescr renamed to RecordDescr
//
// Revision 1.7  2001/03/21 08:34:57  sd
// - Now multiple file and mapping descriptions are supported.
//
// Revision 1.6  2001/03/19 11:16:55  sd
// - Backup version
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif
#ifndef   FRM_RECORDDESCR_HPP
  #include "FRM/RecordDescr.hpp"
#endif
#ifndef   FRM_STREAMDESCR_HPP
  #include "FRM/StreamDescr.hpp"
#endif

#define YYSTYPE BAS::String
#define YYARG YYSTYPE* lvalp

#ifndef   FRM_STDDESCRPARSER_HPP
  #include "FRM/StdDescrParser.hpp"
#endif
#ifndef   FRM_ASNSPECPARSER_HPP
  #include "FRM/ASNSpecParser.hpp"
#endif
#ifndef   RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif

namespace EDR
{
class Factory;
}
namespace FRM
{
class InputMapping;
class OutputMapping;

/** <b><tt>DataDescr</tt></b> is description of all input files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DataDescr.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:47 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>
 */
class DataDescr : public BAS::RegisteredObject
{
  public:
    /**@name DataDescr constructors and destructor */
    //@{

    /** Constructor for a registered data description
     *  @param name The registry name
     *  @param edrFactory Pointer to the edr factory
     */
    DataDescr( const BAS::String& name,
                   EDR::Factory*      edrFactor );

    /** Constructor for an unregistered data description
     *  @param edrFactory Pointer to the edr factory
     *  @param streamFormatFiles Files with format descriptions
     *  @param inputMappingFiles Files with input mapping descriptions
     *  @param outputMappingFiles File with output mapping description
     */
    DataDescr( EDR::Factory*          edrFactory,
                   const BAS::StringList& streamFormatFiles,
                   const BAS::StringList& inputMappingFiles,
                   const BAS::StringList& ouputMappingFiles );

    /** Destructor
     */
    virtual ~DataDescr();

    //@}


    /**@name DataDescr public methods */
    //@{

    /** Get a data descriptions instance via its registry name
     *  @param name The registry name of the data description
     */
    static DataDescr* registeredDataDescr( const BAS::String& name );

    /** Set the failure string (is only used by the parser)
     * @param failure The new failure string
     */
    void failure( const BAS::String& failure );

    /** Get the failure string in case of error
     *  @return Reference to the failure string
     */
    const BAS::String& failure() const;

    /** Get all record names (terminal symbols) from the data description
     *  @return A string list containing all record names
     */
    BAS::StringList recordNames();

    /** Register generated InGrammar with the specified name
     *  @param name InGrammar name
     *  @param value Generated InGrammar Code
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addInGrammar(const BAS::String& name, const BAS::String& value);

    /** Get InGrammar Code with the specified name
     *  @param name InGrammar name
     *  @param value InGrammar Code
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool getInGrammar(const BAS::String& name, BAS::String& value);

    /** Add a new file description to the lexical analyser
     *  @param fileDescr Add a new file description to the lexical analyser
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addFileDescr( StreamDescr* fileDescr );

    /** Set the symbol id for a record
     *  @param name The name of the symbol
     *  @param id The id of the symbol
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool symbolId( const BAS::String& name, size_t id );

    /** Get the string list with lexer state names used
     *  @return Stringlist with lexer state names
     */
    BAS::StringList lexerStates() const;
    
    /** Get a vector with record descriptions for a lexer state name
     *  @param name The name of the lexer state
     *  @return Vector with record descriptions for this state
     */
    RWTPtrOrderedVector<RecordDescr> 
    recordDescrsForLexerState( const BAS::String& name ) const;

    /** Get a vector with all record descriptions 
     *  @return Vector with all record descriptions 
     */
    RWTPtrOrderedVector<RecordDescr> recordDescrs() const;

    /** Insert a record description prototype
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool insertRecordPrototype( RecordDescr* record );
    
    /** Insert a field description prototype
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool insertFieldPrototype( EDR::FieldDescr* record );
    
    /** Create a new record description by it's typename
     *  @param typeName The typename of the new record description
     *  @param recordName The recordname of the descr. inside the file descr.
     *  @return Pointer to the record description on success, 0 otherwise
     */
    RecordDescr* createRecordDescr( const BAS::String& typeName,
                                        const BAS::String& recordName ) const;

    /** Create a new field description by it's typename
     *  @param typeName The typename of the new field description
     *  @param fieldName The fieldname of the descr. inside the input record
     *  @return Pointer to the field description on success, 0 otherwise
     */
    EDR::FieldDescr* createFieldDescr( const BAS::String& typeName,
                                      const BAS::String& fieldName ) const;

    /** Get the edr factory
     *  @return Pointer to the edr factory
     */
    EDR::Factory* edrFactory() const;

    /** Get a input mapping description by its name
     *  @param name The name of the mapping description
     *  @return Pointer to mapping description on success, 0 otherwise
     */
    InputMapping* inputMapping( const BAS::String& name );
    
    /** Get a output mapping description by its name
     *  @param name The name of the mapping description
     *  @return Pointer to mapping description on success, 0 otherwise
     */
    OutputMapping* outputMapping( const BAS::String& name );

// CodeReview  - 08.2001 - cdiab - B - xx.xx missing a star(**) for doc++ to be activated
    /* Get a file description by its name
     * @param name The name of the file description
     * @return Pointer to the file description on success, 0 otherwise
     */
    StreamDescr* fileDescr( const BAS::String& name ) const;

    /** Get a record description by its name
     *  @param name The name of the field description
     *  @return Pointer to block description on success, 0 otherwise
     */
    RecordDescr* recordDescr( const BAS::String& name ) const;

    /** Get a field description by its name
     *  @param name The name of the field description
     *  @return Pointer to field description on success, 0 otherwise
     */
    EDR::FieldDescr* fieldDescr( const BAS::String& name ) const;

    /** Set the interpreter name
     *  @param name The name of the interpreter being set.
     */
    void interpreterName( const BAS::String & iName );

    /** get the interpreter name
     *  @return name of the interpreter
     */ 
    const BAS::String & interpreterName();

    /** Set the multithreaded flag
     *  @param flag The value of the multithreaded flag being set
     */
    void multiThreaded( const bool flag );

    /** Get the value of the multithreaded flag
     *  @return the value of the multithreaded flag
     */
    const bool multiThreaded();

    /** Parse the description file
     *  @fileName The name of the description file
     *  @return Returns the status (success/failure)
     */
    bool parseDescrFile ( const BAS::String & fileName );

    /** Parse the output mapping file
     *  @fileName The name of the output mapping file
     *  @return Returns the status (success/failure)
     */
    bool parseOutputMappingFile ( const BAS::String & fileName );
    
    //@}

  protected:
    
    /* Evaluate the plugins registry
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool readRegistry();

    /* Read the mapping files and initialize the data description
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool parseDescriptions();

    /* Initialize the arrays with the prototypes
     */
    void initPrototypeArrays();

    /* Get a record prototype by its name
     * @param typeName The name of the record type
     * @return Pointer to the record prototype on success, 0 otherwise
     */
    const RecordDescr* getRecordPrototype( const BAS::String& typeName ) const;

    /* Get a field prototype by its name
     * @param typeName The name of the field type
     * @return Pointer to the record prototype on success, 0 otherwise
     */
    const EDR::FieldDescr* getFieldPrototype( const BAS::String& typeName ) const;
    
  private:

    // instance members
    BAS::String                           failureM;
    EDR::Factory*                         edrFactoryM;
    RWTPtrOrderedVector<EDR::FieldDescr>  fieldPrototypesM;
    RWTPtrOrderedVector<RecordDescr> recordPrototypesM;

    BAS::String                           interpreterNameM;
    bool                                  multiThreadedM;

    RWTPtrOrderedVector<StreamDescr>   fileDescrM;
    BAS::StringList                       streamFormatFilesM;
    BAS::StringList                       inputMappingFilesM;
    BAS::StringList                       outputMappingFilesM;

    FRM::StdDescrParser parserM;
    FRM::ASNSpecParser asnSpecParserM;

    // class members
    FRM_EXPORT static const BAS::String              regStreamFormatsCM;
    FRM_EXPORT static const BAS::String              regInputMappingCM;
    FRM_EXPORT static const BAS::String              regOutputMappingCM;

    RWTValMap<BAS::String, BAS::String, std::less<BAS::String> > grammarMapM;
};

//==============================================================================
// Get the failure string
//==============================================================================
inline const BAS::String&
DataDescr::failure() const
{
  return failureM; 
}

//==============================================================================
// Set the failure string
//==============================================================================
inline void
DataDescr::failure( const BAS::String& failure )
{
  failureM = failure; 
}

//==============================================================================
// Get a pointer to the edr factory
//==============================================================================
inline EDR::Factory*
DataDescr::edrFactory() const
{
  return edrFactoryM;
}

inline bool 
DataDescr::addInGrammar(const BAS::String& name, const BAS::String& value)
{
  return grammarMapM.insert(name + ".InGrammar", value);
}

inline bool 
DataDescr::getInGrammar(const BAS::String& name, BAS::String& value)
{
  return grammarMapM.findValue(name + ".InGrammar", value);
}

//==============================================================================
// Set interpreterName
//==============================================================================
inline void
DataDescr::interpreterName( const BAS::String & iName )
{
  interpreterNameM = iName;
}

//==============================================================================
// Get interpreterName
//==============================================================================
inline const BAS::String &
DataDescr::interpreterName()
{
  return interpreterNameM;
}

//==============================================================================
// Set multiThreadedM flag.
//==============================================================================
inline void
DataDescr::multiThreaded( const bool flag )
{
  multiThreadedM = flag;
}

//==============================================================================
// Get multiThreadedM flag.
//==============================================================================
inline const bool
DataDescr::multiThreaded()
{
  return multiThreadedM;
}

//==============================================================================
// Parse data-description file.
//==============================================================================
inline bool
DataDescr:: parseDescrFile ( const BAS::String & fileName )
{
  return parserM.parseDescrFile ( this, fileName );
}

//==============================================================================
// Parse OutputMapping file.
//==============================================================================
inline bool
DataDescr:: parseOutputMappingFile ( const BAS::String & fileName )
{
  return parserM.parseOutputMappingFile ( this, fileName );
}

}
#endif // DATADESCR::HPP
