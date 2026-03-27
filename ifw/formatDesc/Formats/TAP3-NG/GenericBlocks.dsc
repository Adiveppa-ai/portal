//==============================================================================
//
//      Copyright (c) 1996 - 2008 Oracle. All rights reserved.
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================

ASN1
{
  BlockEnd(FIX)
  {
    Info
    {
      Pattern = "\0\0";
    }
    dummy AscString(2);
  }

  FileEndFiller(FIX)
  {
    Info
    {
      Pattern = "\n";
    }
    dummy AscString(1);
  }

  FileFiller(FIX)
  {
    Info
    {
      Pattern = "\0";
    }
    dummy AscString(1);
  }
}
