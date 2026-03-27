//==============================================================================
//
// Copyright (c) 1998, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//
//       This material is the confidential property of Oracle Corporation
//       or its licensors and may be used, reproduced, stored or transmitted
//       only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Module Description:
//   Generic I/O input grammar file to be used for Stop Return type RAP
//
//------------------------------------------------------------------------------

Grammar
{
	StopRap:
		STOPRAPSTREAM.DETAIL
		{
			edrNew( HEADER, CONTAINER_HEADER );
			edrInputMap( "STOPRAPSTREAM.DETAIL.HDR_MAPPING" );
			
			edrAddDatablock( HEADER.ASS_ROAMING_EXT );
			edrInputMap( "STOPRAPSTREAM.DETAIL.ASS_ROAMING" );

                        edrNew( TRAILER, CONTAINER_TRAILER );
                        edrInputMap( "STOPRAPSTREAM.DETAIL.TRL_MAPPING" );
		}
                ;
}
