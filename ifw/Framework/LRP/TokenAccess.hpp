#ifndef LRP_TOKENACCESS_HPP
#define LRP_TOKENACCESS_HPP
//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class TokenAccess.
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
// $RCSfile: EXT_OutFileManager.cpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/04/03 14:28:08 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EXT_OutFileManager.cpp,v $
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace EDR
{
class FieldDescr;
}
namespace FRM
{
class RecordDescr;
}
namespace LRP
{
class IScriptInExt;

/** <b><tt>TokenAccess</tt></b> is the base class for all iScript function
 *  nodes used to access fields inside of token values read from file.
 */
class TokenAccess D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name TokenAccess constructors and destructor */
    //@{

    /** Constructor
     *  @param extension Pointer to the iScript input extension
     *  @param recordDescr Pointer to the recorddescription 
     */
    TokenAccess( IScriptInExt* extension );

    /** Destructor
     */
    virtual ~TokenAccess();

    //@}

    /**@name TokenAccess public methods */
    //@{

    /** Initialize the token access object 
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool initTokenAccess( const BAS::String& fieldName );

    //@}

  protected:
    IScriptInExt* inputExtensionM;
    FRM::RecordDescr*  recordDescrM;
    EDR::FieldDescr*   fieldDescrM;
    size_t            fieldIdxM;
    size_t            symbolIdM;
};
}
#endif // TOKENACCESS_HPP
