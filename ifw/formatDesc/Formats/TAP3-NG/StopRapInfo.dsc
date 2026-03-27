//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FMD
//------------------------------------------------------------------------------
// Sample CDR Format:
// ------------------
// plain ASCII, semikolon seperated format, one record per line
// Note: Last record must also contain a NL (new line).
//
// <sender>;<receipient>;<seq-gen-key>;<last-seq-number>;<specification-version-number>;<release-version>
//
//Example:
//
//AIRTL;LOOPT;AIRTL;432;3;11
//


STOPRAPSTREAM
{
  DETAIL(SEPARATED)
  {
    Info
    {
      Pattern = ".*\n"; 
      FieldSeparator = ';';
      RecordSeparator = '\n';
    }

    SENDER                                  AscString();
    RECIPIENT                               AscString();
    SEQ_GEN_KEY                             AscString();
    LAST_SEQ_NUMBER	                    AscInteger();
    SPECIFICATION_VERSION_NUMBER            AscInteger();
    RELEASE_VERSION                         AscInteger();
  } 
}
