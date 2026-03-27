#ifndef EDR_SAXHANDLER_HPP
#define EDR_SAXHANDLER_HPP
/* @(#)%Portal Version: SaxHandler.hpp:Pipeline7.3.1Int:1:2007-Sep-16 23:17:12 % */

//==============================================================================
//
// Copyright (c) 1996, 2015, Oracle and/or its affiliates. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   SAX Handler for parseing XML serialized EDRs
//------------------------------------------------------------------------------
//
// Revision       1.2  2005/02/07 rtang
// PRSF00151358   Decode field value with base64 when its encoding attribute is set.
//
// Revision       1.1  2004/09/24 ammon
// PRSF00132512   Correct problem with string.
//
// Revision       1.0  2004/03/01 ammon
// PRSF00098531   Created.
//
//==============================================================================

#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#include <xercesc/sax/HandlerBase.hpp>
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   EDR_DATABLOCK_HPP
  #include "EDR/Datablock.hpp"
#endif
#ifndef   EDR_DATABLOCKVALUE_HPP
  #include "EDR/DatablockValue.hpp"
#endif
#ifndef   EDR_FACTORY_HPP
  #include "EDR/Factory.hpp"
#endif
#ifndef   EDR_TOKEN_HPP
  #include "EDR/Token.hpp"
#endif
#ifndef   EDR_VALUE_HPP
  #include "EDR/Value.hpp"
#endif


namespace EDR
{

typedef RWTValOrderedVector< Datablock* > DatablockVector;

/** <b><tt>Utils</tt></b> is a class for utilities used in EDR classes.
 */
class SaxHandler : public xercesc::HandlerBase D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /** Construtor
     * @param factory EDR Factory for creating EDRs.
     */
    SaxHandler( Factory* factory );

    /** Construtor
     * @param factory EDR Factory for creating EDRs.
     */
    ~SaxHandler();

    /** Get the parsed EDR container
     * @return Parsed EDR container or 0 if parse errors
     */
    EDR::Container* getEdr();

    // Handlers for the SAX DocumentHandler interface
    /** Reset the document on it's reuse
     */
    void resetDocument();

    /** Recieve notification of the beginning of an element
     * @param name Tag name.
     * @param attrs Attributes.
     */
    void startElement(const XMLCh* const name,
                      xercesc::AttributeList &attrs);

    /** Recieve notification of the end of an element
     * @param name Tag name.
     */
    void endElement(const XMLCh* const name);

    /** Recieve notification of character data
     * @param name Tag name.
     * @param attrs Attributes.
     */
    void characters(const XMLCh* const chars,
                    const XMLSize_t   length);

  private:
    /** Recieve notification of the beginning of an field
     */
    void startField();

    /** Recieve notification of the beginning of an field
     */
    void startBlock();

    /** Recieve notification of the beginning of an field
     */
    void startToken();

    /** Recieve notification of the beginning of an field
     */
    void startEdr();

    /** Recieve notification of the beginning of an field
     */
    void startFieldMap();

    /** Recieve notification of the beginning of an field
     */
    void startFieldList();

    /** get the last index from an XML id
     * @param xmlId xmlId ot process
     * @return last index from xmlID or -1 on error
     */
    static int64 getLastXmlIndex(const XMLCh* xmlId);

    /** Set a parse error
     * @param name Tag name.
     */
    void setError( BAS::String err );

    // class members
    Factory*                 factoryM;
    Datablock*               currentBlockM;
    Value*                   currentFieldM;
    Token*                   currentTokenM;
    Container*               edrM;
    DatablockVector          blocksM;
    BAS::String              xmlValueM;
    const XMLCh*             xmlAttrM;
    int                      xmlIndexM;
    DatablockValue*          blkValueM;
    bool                     useBase64M;
    bool                     fieldSetM;

    // Error
    bool hasErrorM;

  public:
    // XML tag constants
    static const XMLCh edrTagCM[];
    static const XMLCh fieldMapTagCM[];
    static const XMLCh fieldListTagCM[];
    static const XMLCh tokenListTagCM[];
    static const XMLCh tokenTagCM[];
    static const XMLCh blockTagCM[];
    static const XMLCh fieldTagCM[];
    static const XMLCh typeAttrTagCM[];
    static const XMLCh encodingAttrTagCM[];
    static const XMLCh nameAttrTagCM[];
    static const XMLCh idAttrTagCM[];

    // Supported Container types
    static const XMLCh headerCM[];
    static const XMLCh detailCM[];
    static const XMLCh trailerCM[];
};

//==============================================================================
// Get the parsed EDR container
//==============================================================================
inline EDR::Container*
SaxHandler::getEdr()
{
  return edrM;
}
}

#endif // EDR_SAXHANDLER_HPP
