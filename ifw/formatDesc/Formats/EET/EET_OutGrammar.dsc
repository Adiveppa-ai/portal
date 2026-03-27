//==============================================================================
//
//      Copyright (c) 1996 - 2007 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//-------------------------------------------------------------------------------
// Block: EET_OutGrammar.dsc
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

  //----------------------------------------------------------------------------
  // Apply the UTC_TIME_OFFSET to a date to correct output AscDateUnix values
  //----------------------------------------------------------------------------
  function Date dateToUTC( Date origDate, String utcOffset )
  {
    Long offset = strToLong( utcOffset );

    Long hours =  - offset / 100;
    Long minutes =  - offset % 100;

    Date result = dateAdd( origDate, 0, 0, 0, hours, minutes );
    return result;
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

        if ( edrNumDatablocks( DETAIL.ASS_GSMW_EXT ) > 0 )
        {
          edrString( DETAIL.ASS_ROAMING_EXT.PORT_NUMBER, 0 ) =
          edrString( DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0 );
        }
        else if ( edrNumDatablocks( DETAIL.ASS_GPRS_EXT ) > 0 )
        {
          edrString( DETAIL.ASS_ROAMING_EXT.PORT_NUMBER, 0 ) =
          edrString( DETAIL.ASS_GPRS_EXT.PORT_NUMBER, 0 );
        }
        else if ( edrNumDatablocks( DETAIL.ASS_WAP_EXT ) > 0 )
        {
          edrString( DETAIL.ASS_ROAMING_EXT.PORT_NUMBER, 0 ) =
          edrString( DETAIL.ASS_WAP_EXT.PORT_NUMBER, 0 );
        }
        else if ( edrNumDatablocks( DETAIL.ASS_SMS_EXT ) > 0 )
        {
          edrString( DETAIL.ASS_ROAMING_EXT.PORT_NUMBER, 0 ) =
          edrString( DETAIL.ASS_SMS_EXT.PORT_NUMBER, 0 );
        }
        else if ( edrNumDatablocks( DETAIL.ASS_MMS_EXT ) > 0 )
        {
          edrString( DETAIL.ASS_ROAMING_EXT.PORT_NUMBER, 0 ) =
          edrString( DETAIL.ASS_MMS_EXT.PORT_NUMBER, 0 );
        }
	
        // Adjust if UTC_TIME_OFFSET is set
        if ( edrInputState( DETAIL.UTC_TIME_OFFSET ) == EDR_INPUT_OTHER )
        {
          if ( edrInputState( DETAIL.CHARGING_START_TIMESTAMP ) == EDR_INPUT_OTHER )
          {
            edrDate( DETAIL.CHARGING_START_TIMESTAMP ) =
              dateToUTC( edrDate( DETAIL.CHARGING_START_TIMESTAMP ),
                edrString( DETAIL.UTC_TIME_OFFSET ));
          }
        }

        if ( edrString( DETAIL.ASS_ROAMING_EXT.RAP_RECORD_TYPE, 0 ) 
             == "SEVERE" )
          edrOutputMap( "EET.SEVERE_DETAIL.STD_MAPPING", 0 );

        else if ( edrString( DETAIL.ASS_ROAMING_EXT.RAP_RECORD_TYPE, 0 ) 
             == "FATAL" )
          edrOutputMap( "EET.FATAL_DETAIL.STD_MAPPING", 0 );
      }
  | /* EMPTY */
  ;      
}
