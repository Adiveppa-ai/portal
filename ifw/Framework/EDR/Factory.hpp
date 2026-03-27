#ifndef EDR_FACTORY_HPP
#define EDR_FACTORY_HPP
/* @(#)$Id: Factory.hpp /cgbubrm_7.5.0.pipeline/1 2012/05/23 01:27:45 sknanda Exp $ */

//==============================================================================
//
// 	Copyright (c) 1996, 2023, Oracle and/or its affiliates. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Factory.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
//------------------------------------------------------------------------------
// Revision 1.27  2012/05/11 Santanu 
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER 
//
// Revision 1.26  2005/04/1 rtang
// PRSF00161772  Platform support for improving pre-suspense performance 
//
// Revision 1.25  2004/03/10 ammon
// PRSF00098531 XML de-serialize performance
//
// Revision 1.24  2004/02/06 ammon
// PRSF00090996 More XML performance
//
// Revision 1.23  2004/02/02 ammon
// PRSF00090216 XML performance
//
// Revision 1.22  2003/11/24 ammon
// PRSF00079838 Rename containerPoid to containerVersionPoid
//
// Revision 1.21  2003/11/20 ammon
// PRSF00068378 Add fuctions for XML deserialization
//
// Revision 1.20  2003/11/12 ammon
// PRSF00068381 Add fuctions for XML field mapping and serialization
//
// Revision 1.19  2003/10/31 ammon
// PRSF00075996 Add fuctions for XML IDs
//
// Revision 1.18  2002/01/15 09:28:23  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.17  2001/11/11 19:08:27  sd
// - Token cache introduced
//
// Revision 1.16  2001/11/09 15:32:33  sd
// - Token cache introduced
//
// Revision 1.15  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.14  2001/08/10 12:35:09  mliebmann
// - PETS #36559 SourcePro AIX port
//
// Revision 1.13  2001/08/07 12:58:46  mwriedt
// - PETS #37618: Code Review.
//
// Revision 1.12  2001/08/03 13:15:02  bt
// - PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.11  2001/06/26 07:52:25  sd
// - Error handling for illegal EDR indices corrected
//
// Revision 1.10  2001/06/21 14:44:37  sd
// - Online doc improved
//
// Revision 1.9  2001/06/19 12:26:28  sd
// - Output for edr usage statistic added.
//
// Revision 1.8  2001/05/31 10:33:30  mwriedt
// - Support for automatic alias mapping added.
//
// Revision 1.7  2001/05/16 11:35:59  sd
// - Functions for getting index names added.
//
// Revision 1.6  2001/05/02 08:12:51  sd
// - Mapping table introduced
//
// Revision 1.5  2001/04/26 16:16:43  sd
// - New parameters library and reference added to index functions
//
// Revision 1.4  2001/04/26 15:23:25  s
// - ContainerIndex introduced
//
// Revision 1.3  2001/04/23 14:53:16  sd
// - Index splitted to IndexBase, Index and BlockIndex
//
// Revision 1.2  2001/03/30 12:49:44  sd
// - Changes to support duplication of EDR containers
//
// Revision 1.1  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.13  2001/03/14 11:42:27  sd
// - Output operator added to Container
//
// Revision 1.12  2001/03/12 10:13:15  sd
// - The EDR factory sets it's status on errors while creating an index.
//
// Revision 1.5  2000/10/19 12:54:56  sd
// - Access functions added to iterator
//
// Revision 1.4  2000/10/19 10:14:14  sd
// - First running iterator version.
//
// Revision 1.3  2000/10/17 14:07:31  sd
// - Clear method() added.
// - Block index removed.
//
// Revision 1.2  2000/10/17 11:49:55  sd
// - Bugfix in cache
//
// Revision 1.1  2000/10/17 08:41:54  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   __RWDB_DB_H__
  #include <rw/db/db.h>
#endif
#ifndef   __RWDB_CONNECT_H__
  #include <rw/db/connect.h>
#endif
#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   EDR_TOKENCACHE_HPP
  #include "EDR/TokenCache.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   EDR_CONTAINERCACHE_HPP
  #include "EDR/ContainerCache.hpp"
#endif
#ifndef   EDR_DATABLOCKCACHE_HPP
  #include "EDR/DatablockCache.hpp"
#endif
#ifndef   EDR_DATABLOCKDESCR_HPP
  #include "EDR/DatablockDescr.hpp"
#endif
#ifndef   EDR_FIELDMAPTABLE_HPP
  #include "EDR/FieldMapTable.hpp"
#endif
#include "xercesc/util/XercesDefs.hpp"

namespace XERCES_CPP_NAMESPACE {
    class DOMElement;
    class DOMDocument;
    class SAXParser;
}

namespace GDD
{
    class GlobalDataDictionaryIf;
}

namespace EDR
{
//class DBC_DatabasePlugIn;
class Lexer;
class DatablockValue;
class Index;
class Iterator;
class SaxHandler;
class BlockIndex;
/**
 * Typedef for a map of Infranet Pin_fld_num and corresponging BlockIndex
 */
typedef std::map<pin_fld_num_t, BlockIndex>  BlockIndexFieldNumTableT;


class Factory : public BAS::RegisteredObject
{
  public:

     void changeTraceMode(bool mode);

     bool traceModeEnabled() const ;

     /** Sets the flag to do memberwise copy
      */
     void variantFactoryCopy(bool);

     /** Gets the value of the flag used to do memberwise copy
      */
     bool variantFactoryCopy() const;

    /**@name Factory constructors and destructor */
    //@{

    /** Default constructor
     */
    Factory();

    /** Constructor for a registered object
     *  @param name Name for object registration
     */
    Factory( const BAS::String& name );

    /** Destructor 
     */
    ~Factory();

    //@}

    /**@name Factory public methods */
    //@{

    /** Get an instance of the edr factory via its registry name
     *  @param name The registry name of the factory
     */
    static Factory* registeredFactory( const BAS::String& name );

    /** Get the failure string
     *  @return Reference to failure string
     */
    const BAS::String& failure() const;

    /** Initialize the factory from a file
     *  @param fileName The file name to initialize from
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init( const BAS::String& fileName );

    /** Initialize the factory from a file
     *  @param fileName The file name to initialize from
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool initFromFile( const BAS::String& fileName );

    /** Initialize the factory from the Object(Poid) Type
     *  @param poidType The Object(Poid) Type (as in "/account")
     *  @param globalDataDictionary The global data dictionary
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool initFromType ( const BAS::String& poidType,
                        GDD::GlobalDataDictionaryIf *globalDataDictionary = 0);

    /** Initialize the factory from the Base type of the Object(Poid) Type
     *  @param poidType The Object(Poid) Type (as in "/account")
     *  @param globalDataDictionary The global data dictionary
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool initFromBaseType ( const BAS::String& poidType,
                        GDD::GlobalDataDictionaryIf *globalDataDictionary = 0);

    bool initDb( RWDBConnection dbConnection );

    /** Produce a new EDR container
     *  @param index The block index for the root block
     *  @return Pointer to the new EDR container on success
     */
    Container* produceEDR( const ContainerIndex& index );

    /** Restore a EDR container from an input stream
     *  @param in The input stream
     *  @return Pointer to the new EDR container on success
     *          0 otherwise
     */
    Container* produceEDR( std::istream& in );

    /** Duplicate an EDR container
     *  @param edr The EDR container to duplicate
     *  @return Pointer to the duplicated EDR container
     */
    Container* duplicateEDR( const Container* edr );

    /** Release a EDR container
     *  @param edr Pointer to the edr to release
     */
    void releaseEDR( Container* edr );

    /** Release a datablock
     *  @param block Pointer to the datablock to release
     */
    void releaseDatablock( Datablock* block );

    /** Release a token
     *  @param token Pointer to the tokne to release
     */
    void releaseToken( Token* token );

    /** Add a new block description to the factory
     *  @param descr The datablock description to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    void addBlockDescr( DatablockDescr* descr );

    /** Get a block description by it's name
     *  @param name The name of the datablock
     *  @return Pointer to the description on success, 0 otherwise
     */
    const DatablockDescr* getBlockDescr( const BAS::String& name ) const;

    /** Get a block description by it's name (to change)
     *  @param name The name of the datablock
     *  @return Pointer to the description on success, 0 otherwise
     */
    DatablockDescr* getBlockDescrForChange( const BAS::String& name ) const;

    /** Get Container Description Text (like in containerDesc.dsc)
     *  @return String containing Container Description
     */
    BAS::String getContainerDescrStr() const;

    /** Get a block description by it's type id
     *  @param id The blocktype id
     *  @return Pointer to the description on success, 0 otherwise
     */
    const DatablockDescr* getBlockDescr( size_t blockTypeId ) const;

    /** Do the final setup for the factory after adding all descriptions
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool finalSetup();

    /** Setup all the prototype values and Datablocks for the factory
     *  Set length, type and Infranet pin_fld)num valus in the prototypes
     *  @param dataInMemory = true indicates in memory data (timos), 
     *                      = false for pipeline
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setupAllPrototypes(bool dataInMemory);

    /** Get an index for container value access 
     *  @param library The name of the library that accesses uses the index
     *  @param defName The default name of the container field
     *  @param index Return buffer for the container index
     *  @param key The locigal name of the field
     *  @param reference The reference for the field mapping
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool getIndex( const BAS::String& library,
                   const BAS::String& defName,
                   Index&        index,
                   const BAS::String& key       = BAS::NULL_STRING,
                   const BAS::String& reference = BAS::NULL_STRING );

    /** Get an index for container value access (throws BAS::Status exception 
     *  on error!)
     *  @param library The name of the library that accesses uses the index
     *  @param defName The default name of the container field
     *  @param key The locigal name of the field
     *  @param reference The reference for the field mapping
     *  @return The index
     */
    Index getIndex( const BAS::String& library,
                        const BAS::String& defName,
                        const BAS::String& key       = BAS::NULL_STRING,
                        const BAS::String& reference = BAS::NULL_STRING );

    /** Get an index for container block access
     *  @param library The name of the library that accesses uses the index
     *  @param defName The default name of the datablock
     *  @param index Return buffer for the container block index
     *  @param key The locigal name of the field
     *  @param reference The reference for the field mapping
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool getBlockIndex( const BAS::String& library,
                        const BAS::String& defName, 
                        BlockIndex&   index,
                        const BAS::String& key       = BAS::NULL_STRING,
                        const BAS::String& reference = BAS::NULL_STRING );

    /** Get a block index for container access (throws BAS::Status exception on 
     *  error!)
     *  @param library The name of the library that accesses uses the index
     *  @param defName The default name of the datablock
     *  @param key The locigal name of the field
     *  @param reference The reference for the field mapping
     *  @return The index
     */
    BlockIndex getBlockIndex( const BAS::String& library,
                                  const BAS::String& defName,
                                  const BAS::String& key       = BAS::NULL_STRING,
                                  const BAS::String& reference = BAS::NULL_STRING );

    /** Get an index for container creation
     *  @param library The name of the library that accesses uses the index
     *  @param defName The default name of the container's rootblock
     *  @param index Return buffer for the container index
     *  @param key The locigal name of the field
     *  @param reference The reference for the field mapping
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool getContainerIndex( const BAS::String&   library,
                            const BAS::String&   defName, 
                            ContainerIndex& index,
                            const BAS::String&   key       = BAS::NULL_STRING,
                            const BAS::String&   reference = BAS::NULL_STRING );

    /** Get a container index for container creation (throws BAS::Status 
     *  exception on error!)
     *  @param library The name of the library that accesses uses the index
     *  @param defName The default name of the container 
     *  @param key The locigal name of the field
     *  @param reference The reference for the field mapping
     *  @return The index
     */
    ContainerIndex getContainerIndex( const BAS::String& library,
                                          const BAS::String& defName,
                                          const BAS::String& key 
                                            = BAS::NULL_STRING,
                                          const BAS::String& reference
                                            = BAS::NULL_STRING );

    /** Get the name of a datablock
     *  @param blockTypeId The type id of the datablock
     *  @return The name of the datablock
     */
    const BAS::String& blockName( size_t blockTypeId ) const;

	/** Get the flag associated with a value
	 * @param blockTypeId the id
	 * @param valueIdx index of the value in the block
	 * @return FlagtypeT flag indicating DD flags for the object
	 */
	const ValueDescr::FlagtypeT getValueFlag(size_t blockTypeId, 
											 size_t valueIdx) const;

	/** Get the flag associated with a value
	 * @param blockTypeId the id
	 * @return FlagtypeT flag indicating DD flags for the object
	 * @todo Not yet implemented
	 */
	const ValueDescr::FlagtypeT getBlockFlag(size_t blockTypeId) const;

    /** Get the name of a data field
     *  @param blockTypeId The type id of the datablock
     *  @param valueIdx The index of the value
     */
    const BAS::String& valueName( size_t blockTypeId,
                                 size_t valueIdx ) const;

    /** Get the pin_fld_num value  of a data field
     *  @param blockTypeId The type id of the datablock
     *  @param valueIdx The index of the value
     */
    pin_fld_num_t  valuePinFldNum( size_t blockTypeId,
                                 size_t valueIdx ) const;

    /** Get the pin_fld_num value  for the datablock
     *  @param blockTypeId The type id of the datablock
     */

    pin_fld_num_t blockPinFldNum( size_t blockTypeId ) const;


    /** Duplicate a datablock (and all its subblocks). This function should
     *  only be used by the assignment operator of the EDR container.
     *  @param datablock The datablock to duplicate
     *  @return Pointer to the duplicated datablock
     */
    Datablock* duplicateDatablock( const Datablock* block );

    /** Produce a new datablock
     *  @param blockTypeId The type id of the block to produce
     *  @return Pointer to the new datablock
     */
    Datablock* produceDatablock( size_t blockTypeId );

    /** Restore a datablock from an input stream
     *  @param in The input stream
     *  @return Pointer to the new datablock
     */
    Datablock* produceDatablock( std::istream& in );

    /** Produce a new token
     *  @return Pointer to the new token
     */
    Token* produceToken();

    /** Get the name for a normal index
     *  @param index 
     *  @param name Return buffer for the name
     *  @return <b>true</b> if index is valid, <b>false</b> otherwise
     */
    bool getIndexName( const Index& index,
                       BAS::String&      name ) const;

    /** Get the name for a block index
     *  @param index 
     *  @param name Return buffer for the name
     *  @return <b>true</b> if index is valid, <b>false</b> otherwise
     */
    bool getBlockIndexName( const BlockIndex& index,
                            BAS::String&           name ) const;

    /** Get the name for a container index
     *  @param index 
     *  @param name Return buffer for the name
     *  @return <b>true</b> if index is valid, <b>false</b> otherwise
     */
    bool getContainerIndexName( const ContainerIndex& index,
                                BAS::String&               name ) const;

    /** Get the value description pointer for a particular value
     * @param blockTypeId the block type
     * @param valueIdx the index of the value
     * @return pointer to a ValueDescr object describing the value
     */
     const ValueDescr* getValueDescr(size_t blockTypeId,
                                     size_t valueIdx) const;  

    /** Set the container description version
     *  @param version Container description version
     */
    void setContainerVersion( const BAS::String& version );

    /** Get the container description version
     *  @return The container description version
     */
    const BAS::String& getContainerVersion() const;

    /** Set the container description version
     *  @param version Container description version
     */
    void setContainerVersionPoid( const BAS::String& version );

    /** Get the container description version
     *  @return The container description version
     */
    const BAS::String& getContainerVersionPoid() const;

    /** Get an index from an XML ID
     *  @param index Return buffer for the edr index
     *  @param xmlId The XML ID to convert
     *  @return <b>true</b> if ID is valid, <b>false</b> otherwise
     */
    bool getIndexFromXmlId( Index&       index,
                            BAS::String& xmlId );

    /** Get an XML ID
     *  @param index The index to look up ID for
     *  @return The XML ID
     */
    BAS::String getXmlId( Index& index );

    /** Get a blockIndex from an XML ID
     *  @param index Return buffer for the block index
     *  @param xmlIndices The XML ID to convert
     *  @return <b>true</b> if indices are valid, <b>false</b> otherwise
     */
    bool getBlockIndexFromXmlIndices( BlockIndex&     index,
                                      BAS::StringList xmlId );

    /** Get a blockIndex from an XML ID
     *  @param index Return buffer for the block index
     *  @param xmlId The XML ID to convert
     *  @return <b>true</b> if ID is valid, <b>false</b> otherwise
     */
    bool getBlockIndexFromXmlId( BlockIndex&  index,
                                 BAS::String& xmlId );

    /** Get an XML ID
     *  @param index The index to look up ID for
     *  @return The XML ID
     */
    BAS::String getXmlId( BlockIndex& index );

    /** Get the field to XML ID mapping
     *  @return XML ID to field mapping if sucessful, BAS::NULL_STRING otherwise.
     */
    BAS::String getXmlFieldMap();

    /** Serialize an EDR Container to XML
     *  @param edr    Container to serialize
     *  @param markedOnly  only dump the marked blocks to xml for recycle.
     *  @return XML XML representation of the EDR if sucessful, BAS::NULL_STRING otherwise.
     */
    BAS::String getEdrXml( EDR::Container* edr, bool markedOnly = false );

    /** Walk through an EDR Container to set a flag in all set/connected/initialized fields and datablocks
     *  @param edr    Container to walk through
     */
    void markSetFields( EDR::Container* edr);

    /** De-serialize an EDR Container from XML.
     *  Only de-serializes if the container description version in the XML matches
     *  the current version in the factory, or if the version is not set.
     *  @return EDR Container if successful, null otherwise.
     */
    Container* getEdrFromXml( const BAS::String xmlDoc );

    /** validate Container version
     *  @param dbConnection database connection
     *  @return true if no errors encountered, false otherwise
     */
    bool validateContainerVersion(RWDBConnection& dbConnection );

    /** Check if version number exists, call update otherwise
     *  @param dbConnection database connection
     *  @return true if no errors encountered, false otherwise
     */
    bool checkAndUpdateXmlVersionInfo(RWDBConnection& dbConnection );

    /** Write version and xml map info in the databsae
     *  @param dbConnection database connection
     *  @return true if no errors encountered, false otherwise
     */
    bool writeXmlVersionInDb(RWDBConnection& dbConnection );

    /** Get the Poid Id Number for the version Info
     *  @param   dbConnection database connection
     *  @param   poidId Number
     *  @return  true if no errors, false otherwise
     */
    bool   getVersionPoidId(RWDBConnection& dbConnection, 
                             pin_poid_id_t& idNumber);

    /** Return the DBC plugin Name for xml/version database
     *  @return DBC plugin name for xml db
     */
    const BAS::String& getVersionDbPlugInName();

    /** Print the edr usage statistic 
     *  @param os The output stream
     */
    bool printUsageStatistic();

#ifdef TRACE
    void printCacheStatistic( std::ostream& os ) const;
#endif

	/** The guts of the parser. Moved out of the yacc file because it is 
	 * more modular and called in two places now
	 * @param lexer the lexer being uesed
	 * @param line the line being parsed
	 * @param fieldName the field name being added
	 * @param typeName the type of the field
	 * @param flagName the flag associated with the field (if any)
	 * @return int representing parse status
	 *
	 * @todo remove hard coded value for parse failed!
	 *
	 * Disabled the compiler optimization on this function as 
	 * the if condition check on passM was always evaluated
	 * as true due to compiler optimization in GCC12. 
	 */
	int processEntry(Lexer* lexer,
					 const BAS::String& line,
					 const BAS::String& fieldName, 
					 const BAS::String& typeName,
					 const BAS::String& flagName) __attribute__((optimize("O0")));

    //@}

    const BAS::String & plugInName();
    BAS::String libName();

    /** Receive incoming messages.
     */
    void receiveRequest(BAS::Message& msg);

    /** Generate pretty content for the timos web server.
     */
    BAS::String generateWebPage(const BAS::Message& msg);

    /** Get fully qualified Block name from pin_fld_num value 
     */
    const BAS::String& getFullBlockName(pin_fld_num_t fldNum) const;

    /** Get the block Index from the Factory's cache of BlockIndex Table
     *  @param fieldNum The pin_fld_num_t value for the block
     *  @return pointer to BlockIndex, null if not found in cache
     */
    BlockIndex *getBlockIndexFromCache(pin_fld_num_t fieldNum);

   /**  Write message to pipeline log
     *  @param BAS::Status message to log into pipeline log
     */
    void writeToPipelineLog(BAS::Status& msg);

    /** Build the block Index Cache indexed by Infranet field number
     *  @param blockDescr Current datablock descriptor
     *  @param blockName Current full datablock name 
     */
	void buildBlockIndexCache(const EDR::DatablockDescr *blockDescr, 
							const BAS::String &blockName);


  protected:

    /* Set the failure message
     * @param msg The failure message
     */
    void failure( const BAS::String& msg );

    /* Set the error status when a index creation failed
     * @param defName The default name of the index
     * @param key The key for the index mapping
     * @param reference The reference for the mapping
     */
    void indexCreationFailed( const BAS::String& defName,
                              const BAS::String& key,
                              const BAS::String& reference );

    /* Evaluate the factories registry
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool readRegistry();

    /* Create an Value by it's typename
     * @param typeName The typename for the value
     * @return Pointer to value on success, 0 otherwise
     */
    Value* createValue(const BAS::String& typeName) const;

    /* Create an Value by it's typename and set the maxLen
     * @param typeName The typename for the value
     * @param dataInMemory true for timos, false otherwise
     * @return Pointer to value on success, 0 otherwise
     */
    Value* createValueAndSetMaxLen(const BAS::String& typeName,
                                   bool dataInMemory) const;

    /* Create an DatablockValue by the blockname
     * @param blockName The blockname for the value
     * @return Pointer to value on success, 0 otherwise
     */
    DatablockValue* createDatablockValue( const BAS::String& blockName ) const;

    /** Add all the fields to XML ID mapping
     *  @param doc Return document for the field map
     *  @return <b>true</b> if successful
     */
    bool addFieldsToFieldMap( XERCES_CPP_NAMESPACE::DOMDocument* doc );

    /** Add a block to the field to XML ID mapping
     *  @param name Name of the block to add
     *  @param path Path to the block
     *  @param doc  Return document for the field map
     *  @param root Root element in thge document
     *  @return <b>true</b> if successful
     */
    bool addBlockToFieldMap( const BAS::String name,
                             const BAS::String path,
                             XERCES_CPP_NAMESPACE::DOMDocument* doc,
                             XERCES_CPP_NAMESPACE::DOMElement* root );

    /** Add an item to the field to XML ID mapping
     *  @param value ValueDescr of the item to add
     *  @param path  Path to the item
     *  @param doc   Return document for the field map
     *  @param root  Root element in the document
     *  @return <b>true</b> if successful
     */
    bool addItemToFieldMap( EDR::ValueDescr* value,
                            const BAS::String path,
                            XERCES_CPP_NAMESPACE::DOMDocument* doc,
                            XERCES_CPP_NAMESPACE::DOMElement* root );

  private:

    typedef std::map<pin_fld_num_t, BAS::String>  BlockFldNumToNameTableT;

    // disallow use of copy constructor/operator
    Factory( const Factory& other );
    const Factory& operator=( const Factory& other );

	/** parse the description file
     * changed to use istream rather than strings and assined to strstream
     * two params used to do 2 passes (first one gets closed automatically!)
	 * @param ifile = istream pointer to the description file
	 * @param ifile2 = second istream pointer to the description file
	 * @return bool true indicates success
	 */
    bool parseDescription(std::istream *ifile, std::istream *ifile2);

    int parse(void* lexer);

	void createXmlParser();

    // instance members
    bool 					edrTraceEnabledM;
     bool                                       fieldTypeCheckM;
    BAS::String                                     failureM;
    ContainerCache                             containerCacheM;
    TokenCache                                 tokenCacheM;
    RWTPtrOrderedVector<DatablockCache>        blockCacheVectorM;
    RWTPtrOrderedVector<DatablockDescr>        blockDescrVectorM;
    BAS::String                                     plugInNameM;
    BAS::String                                     versionDbPlugInNameM;
    
    FieldMapTable                              fieldMapTableM;
    BAS::String                                     usageStatisticFileM;
    BAS::StringList                          typeNamesM;

    int                                     passM;
    BAS::StringList                          blockNamesM;
    RWTPtrOrderedVector<EDR::DatablockDescr> blockDescrM;
    BAS::String                              descrVersionM;
    BAS::String                                     containerVersionM;
    BAS::String                                     containerVersionPoidM;

    // XML Parser objects
    XERCES_CPP_NAMESPACE::SAXParser*           xmlParserM;
    SaxHandler*                                xmlHandlerM;

    // Instrumentation objects
    u_int64                              containerCacheHitM;
    u_int64                              containerCacheMissM;
    u_int64                              blockCacheHitM;
    u_int64                              blockCacheMissM;
    BlockFldNumToNameTableT                    blkFldNumToNameM;
    BlockIndexFieldNumTableT                 blockIndexFieldNumTableM;


  public:
    // class members
    EDR_EXPORT static const size_t illegalBlockTypeCM;
    EDR_EXPORT static const size_t illegalValueIndexCM;

    // XML tags and attributes
    EDR_EXPORT static const BAS::String edrDocCM;
    EDR_EXPORT static const BAS::String fieldMapDocCM;

    EDR_EXPORT static const BAS::String blockElementCM;
    EDR_EXPORT static const BAS::String fieldElementCM;
    EDR_EXPORT static const BAS::String fieldListElementCM;
    EDR_EXPORT static const BAS::String fieldMapElementCM;
    EDR_EXPORT static const BAS::String tokenElementCM;
    EDR_EXPORT static const BAS::String tokenListElementCM;

    EDR_EXPORT static const BAS::String idAttrCM;
    EDR_EXPORT static const BAS::String nameAttrCM;
    EDR_EXPORT static const BAS::String poidAttrCM;
    EDR_EXPORT static const BAS::String typeAttrCM;

private:

	static void InitializeXml();
	static void TerminateXml();

	static int initXmlCountCM;
	static RWMutexLock initXmlMutexCM;
        bool variantFactoryCopyM;
};

//==============================================================================
// Get the failure string
//==============================================================================
inline const BAS::String&
Factory::failure() const
{
  return failureM;
}

//==============================================================================
// Set the failure string
//==============================================================================
inline void
Factory::failure( const BAS::String& msg )
{
  failureM = msg;
}

//==============================================================================
// Get the name of the database plugin
//==============================================================================
inline const BAS::String &
Factory::plugInName()
{
  return plugInNameM;
}

//==============================================================================
// Get the name of the version and xml field map  database plugin
//==============================================================================
inline const BAS::String &
Factory::getVersionDbPlugInName()
{
  return versionDbPlugInNameM;
}

//==============================================================================
// Get the container version
//==============================================================================
inline const BAS::String&
Factory::getContainerVersion() const
{
  return containerVersionM;
}

//==============================================================================
// Set the container version
//==============================================================================
inline void
Factory::setContainerVersion( const BAS::String& ver )
{
  containerVersionM = ver;
}

//==============================================================================
// Get the container poid
//==============================================================================
inline const BAS::String&
Factory::getContainerVersionPoid() const
{
  return containerVersionPoidM;
}

//==============================================================================
// Set the container poid
//==============================================================================
inline void
Factory::setContainerVersionPoid( const BAS::String& ver )
{
  containerVersionPoidM = ver;
}

inline void
EDR::Factory::variantFactoryCopy(bool flag)
{
  variantFactoryCopyM = flag;
}

inline bool
EDR::Factory::variantFactoryCopy() const
{
  return variantFactoryCopyM;
}


}
#endif // FACTORY_HPP
