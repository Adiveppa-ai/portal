//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//  This material is the confidential property of Oracle Corporation or its
//  licensors and may be used,reproduced, stored or transmitted only in
//  accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Implementation of the class IXT::ERA::Extension. This class is the iScript
//   extension class for getting ERAs.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------

#ifndef IXTERAEXTENSION_HPP
#ifndef lint
static char Sccs_id[] = "@(#)$Id: EraExtension.hpp /cgbubrm_7.5.0.pipeline/1 2012/03/12 00:35:58 smalviya Exp $";
#endif 
#define IXTERAEXTENSION_HPP

#include "SCR/Variable.hpp"
#include "SCR/Extension.hpp"
#include "BAS/SimpleString.hpp"

//Forward declaration
namespace DAT
{
  namespace Account
  {
    class BatchPlugIn;
  }
}

namespace IXT
{
   static const int AccountProfileFlag(1);
   static const int ServiceProfileFlag(0);
   static const int32 AccountDomFlag(2);

  /** <b><tt>IXT::EraExt</tt></b> is an iScript extension class for Era iScript.
   *
   */
  class EraExt : public SCR::Extension D_THREADINFO_M
  {
    D_NONTHREADSAFE
    public:

      /**@name EraExt constructors and destructor */
      //@{

      /** Constructor
       */
      EraExt();

      /** Destructor
       */
      virtual ~EraExt();

      //@}

      /**@name EraExt public methods */
      //@{

      /** Get the name of the extension
       */
      virtual const BAS::String& extensionName() const;

      /** Get a variable from the Era extension
       *  @param name The name of the variable
       *  @return Pointer to the variable on success, 0 otherwise
       */
      virtual SCR::Variable* variable( const BAS::String& name );

      /** Set the DAT_Account Module name
       *  @param name The registry name of DAT_Account Module
       *  @return True if successful in find the module, Fale otherwise
       */
      bool setDAT_AccountModule( const BAS::String& name);


      /** Get the Service Level ERAs
       *  @param key The Key(IMSI or MSISDN) for the account 
       *  @param svcCode Service Code 
       *  @param era ERA name 
       *  @param date Date of usage 
       *  @return String with name value pair array for the ERA
       */
      BAS::String& getServExtRating( const BAS::String& key,
                                     const BAS::String& svcCode,
                                     const BAS::String& era,
                                     const BAS::DateTime& date);

      /** Get the Account Level ERAs
       *  @param key The Key(IMSI or MSISDN) for the account 
       *  @param svcCode Service Code 
       *  @param era ERA name 
       *  @param date Date of usage 
       *  @return String with name value pair array for the ERA
       */
      BAS::String& getAcctExtRating( const BAS::String& key,
                                     const BAS::String& svcCode,
                                     const BAS::String& era,
                                     const BAS::DateTime& date);
      /** Get the Account Dom
       *  @param key The Key(IMSI or MSISDN) for the account 
       *  @param svcCode Service Code 
       *  @param date Date of usage 
       *  @return String with Dom
       */
      BAS::String& getAcctDom( const BAS::String& key,
                                     const BAS::String& svcCode,
                                     const BAS::DateTime& date);
      //@}

    private:

      //Constants
      static const int keyLenCM;

      // instance members
      DAT::Account::BatchPlugIn* accountModuleM;
      BAS::Status         failureMsgM;
      BAS::String         resultM;

      // class members
      static SCR::VariableMap   constantsCM;


      /** Get the ERAs
       *  @param key The Key(IMSI or MSISDN) for the account 
       *  @param svcCode Service Code 
       *  @param era ERA name 
       *  @param date Date of usage 
       *  @param profileDataKey Key for Service Level or Account Level ERA
       *  @return String with name value pair array for the ERA
       */
      BAS::String& getExtRating( const BAS::String& key,
                                 const BAS::String& svcCode,
                                 const BAS::String& era,
                                 const BAS::DateTime& date,
                                 const BAS::SimpleString& eraKey, 
                                 const BAS::SimpleString& profileDataKey);
  };
}//namespace IXT

#endif // IXTERAEXTENSION_HPP
