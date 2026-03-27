//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-------------------------------------------------------------------------------
// Block: SuspenseBatchRecord_OutGrammar.dsc
//-------------------------------------------------------------------------------
//

//==============================================================================
// The initial iScript code
//==============================================================================
iScript
{
  Long    recordNumber;

  //----------------------------------------------------------------------------
  // Check if the file contains only HEADER
  //----------------------------------------------------------------------------
  function Bool streamIsEmpty
  {
    if ( recordNumber <= 1 )
    {
      // Only HEADER
      return true;
    }
    else
    {
      // At least one DETAIL
      return false;
    }
  }
}

//==============================================================================
// The definition of the grammar
//==============================================================================
Grammar
{
  edr_stream:
      HEADER
        {
          recordNumber = 1;
          edrLong( HEADER.RECORD_NUMBER ) = recordNumber;
          edrOutputMap( "SUSPENSE_BATCH_RECORD.HEADER.STD_MAPPING" );
        }
      details
      TRAILER
        {
        }

  ;
  
  details: 
      details 
      DETAIL
      {
        //--------------------------------------------------------------------
        // Write the DETAIL
        //--------------------------------------------------------------------
        recordNumber = recordNumber + 1;
        edrLong( DETAIL.RECORD_NUMBER ) = recordNumber;
        edrOutputMap( "SUSPENSE_BATCH_RECORD.DETAIL.STD_MAPPING", 0 );
      }
  | /* EMPTY */
  ;      
}
