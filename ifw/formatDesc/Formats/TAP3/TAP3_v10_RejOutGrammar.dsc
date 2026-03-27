//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FMD/TAP3
//------------------------------------------------------------------------------
// Module Description:
//   Reject grammar file for the TAP3_v10 CDR format 
//
//------------------------------------------------------------------------------
// $Log: TAP3_v10_RejOutGrammar.dsc,v $
//
// Log 2003/04/11 pgeiger
// - Creation
//
//==============================================================================

//==============================================================================
// The initial iScript code
//==============================================================================
iScript
{
  // binary strings for the TAP3 englobing objects (in ASN.1 indefinite length form)
  const String byteStr_Tap3TransfertBatch     ="\x61\x80";
  const String byteStr_Tap3CallEventDetailList="\x63\x80";
  const String byteStr_Tap3EndOfConstructed   ="\0\0";
  
  // to be able to determine if the output can be deleted (if empty)
  Long nbWrittenDetails;
  function Bool streamIsEmpty
  {
    if ( nbWrittenDetails == 0 )
    {
      // Only HEADER and TRAILER
      return true;
    }
    // default
    return false;
  }

}

//==============================================================================
// The definition of the grammar
//==============================================================================
Grammar
{
  receive_stream:
      HEADER
      {
        nbWrittenDetails = 0;
        outputWrite(byteStr_Tap3TransfertBatch);     // the indefinite length tag for the TransfertBatch
        outputWrite(edrTokenString());               // the header data
        outputWrite(byteStr_Tap3CallEventDetailList);// the indefinite length tag for the CallEventDetailList
      }
      details
      TRAILER
      {
        outputWrite(byteStr_Tap3EndOfConstructed);   // the indefinite length EOC for the CallEventDetailList
        outputWrite(edrTokenString());               // the trailer data
        outputWrite(byteStr_Tap3EndOfConstructed);   // the indefinite length EOC for the TransfertBatch
      }
    ;

  details:
      details
      DETAIL
      {
        nbWrittenDetails = nbWrittenDetails + 1;
        outputWrite(edrTokenString());               // the detail data
      }
    | /*EMPTY*/
    ;
}
