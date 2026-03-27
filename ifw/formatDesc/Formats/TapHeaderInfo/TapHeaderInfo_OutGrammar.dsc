//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-------------------------------------------------------------------------------
// Block: TapHeaderInfo_OutGrammar.dsc
//-------------------------------------------------------------------------------
//

//==============================================================================
// The initial iScript code
//==============================================================================
iScript
{
  Long    recordNumber;
  function Bool streamIsEmpty
  {
    if ( recordNumber <= 0 ) return true;
    else return false;
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
          recordNumber = 0;
        }
      details
      TRAILER
        {
          Long i;
          Long utcTimeOffsetEntries = edrNumDatablocks( TRAILER.ASS_UTCOFFSET );
          for ( i=0 ; i<utcTimeOffsetEntries ; i=i+1 )
            edrOutputMap( "TapHeaderInfo.UTCOFFSET.STD_MAPPING", i );

          Long recEntityEntries = edrNumDatablocks( TRAILER.ASS_RECENTITY );
          for ( i=0 ; i<recEntityEntries ; i=i+1 )
            edrOutputMap( "TapHeaderInfo.RECENTITY.STD_MAPPING", i );

          recordNumber = recordNumber + utcTimeOffsetEntries;
          recordNumber = recordNumber + recEntityEntries;
        }
    ;
  
  details: 
      details
      DETAIL
    | /* EMPTY */
    ;
}
