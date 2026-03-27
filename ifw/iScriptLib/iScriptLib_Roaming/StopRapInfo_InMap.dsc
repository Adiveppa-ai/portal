//==============================================================================
//
// Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FMD
//------------------------------------------------------------------------------
// Module Description:
//   Input Mapping of Stop Rap flat file 
//

STOPRAPSTREAM
{
  DETAIL
  {
    HDR_MAPPING
    {
		SENDER	                     -> HEADER.SENDER;
		RECIPIENT	             -> HEADER.RECIPIENT;
		SEQ_GEN_KEY	             -> HEADER.SEQ_GEN_KEY;
		SPECIFICATION_VERSION_NUMBER -> HEADER.SPECIFICATION_VERSION_NUMBER;
		RELEASE_VERSION              -> HEADER.RELEASE_VERSION;
    }
    ASS_ROAMING
    {
		LAST_SEQ_NUMBER              -> HEADER.ASS_ROAMING_EXT.LAST_SEQ_NUM;
    }
    TRL_MAPPING
    {

    }

  } 
}
