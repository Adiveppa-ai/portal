//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================

//#include <iostream.h>
//#include <fstream.h>
//#include <rw/thr/thrutil.h>

#include "STR/FileIo.hpp"
#include "BAS/Date.hpp"
#include "PLI/DataCollection.hpp"
#include "DBC/DatabasePlugIn.hpp"
#include "DAT/PrefixDescPlugIn.hpp"

int main(int argc, char *argv[])
{
  cout << "Start" << endl;
  
  SELECT_DEBUG_LEVEL;

  D_ENTER("main()");
  
  int errCnt = 0;
  char optChar = 0;

  extern int optind;
  extern int optopt;
  extern int opterr;
  extern char *optarg;

  BAS::String registryFile = "";

  D_PRINT_T("DAT::PrefixDesc::PrefixDescPlugInCheck program started");

  cerr << endl << "DAT::PrefixDesc::PrefixDescPlugInCheck program started" << endl << endl;

  optind = 1;
  optopt = 0;
  opterr = 0;
  optarg = 0;

  while (optind < argc)
  {
    while ((optChar = getopt(argc,argv,":r:")) != EOF)
    {
      switch (optChar)
      {
        case 'r' :
        {     
          if (registryFile.isNull() == TRUE)
          {
            registryFile = optarg;

            if (registryFile.isNull() == FALSE)
            {
              if (registryFile[(size_t)0] == '-')
              {
                cerr << endl << "invalid registry file name: ";
                cerr << registryFile << endl;

                errCnt++;
              }
            }
          }
          else
          {
            cerr << endl << "duplicate registry file name option: -";
            cerr << (char) optopt << endl;

            errCnt++;
          }

          break;
        }

        case ':' :  
       {
          cerr << endl << "option -" << (char) optopt;
          cerr << " requires an operand" << endl;

          errCnt++;

          break;
        }

        case '?' :
        {
          cerr << endl << "unrecognised option: -";
          cerr << (char) optopt << endl;

          errCnt++;

          break;
        }
      }
    }

    if (optind < argc)
    {
      cerr << endl << "unrecognised argument: " << argv[optind] << endl;

      optind++;

      errCnt++;
    }     
  }

  if ((errCnt > 0) || (registryFile.isNull() == true))
  {
    BAS::String argFiller (' ',strlen(argv[0]));

    cerr << endl << "usage: ";
    cerr << argv[0] << "    -r registry file name" << endl;
    cerr << endl;

//    cerr << argFiller << "           -x xxx yyy zzz" << endl;
  }
  else
  {
    BAS::RegisteredObject::rootName("integrate");

    BAS::RegistryEntry root(BAS::RegisteredObject::rootName());

    root.makeRootNode();

    BAS::RegisteredObject::registry(&root);

    STR::FileIo regFile;

    if (regFile.openFile(registryFile,ios::in) == true)
    {
      regFile >> root;

      if ((regFile.good() == 0) && (regFile.eof() == 0))
      {
        cerr << endl << "DAT::PrefixDesc::PrefixDescPlugInCheck: ";
        cerr << "error reading from file '";
        cerr << registryFile << "'" << endl;
      }
      else if (root.isValid() == true)
      {
        regFile.closeFile();

        cout << "Registry " << endl;
        cout << root;

        PLI::DataCollection datDataColl("integrate.DataPool");

        if (datDataColl.isValid() == false)
        {
          cerr << endl << "DAT::PrefixDesc::PrefixDescPlugInCheck: ";
          cerr << "Cannot create the integrate data collection !!!" << endl;
          cerr << datDataColl.status() << endl;
        }
        else
        {
          cerr << "DataPlugIn's created" << endl;

          datDataColl.init(); 

          DAT::PrefixDesc::PrefixDescPlugIn* plugIn = dynamic_cast<DAT::PrefixDesc::PrefixDescPlugIn *>
                                       (datDataColl["PrefixDescData"]->plugIn());

          if(plugIn->isUsable() == false)
          {
            cerr << "Plug in is not usable\n";
          }
          else {
            cout << "Plug In is usable" << endl;
            
            BAS::String number ("004940232323");
            BAS::String prefix;
            BAS::String description;
            
            plugIn->search(number, description);
            
            D_PRINT("search number " << number << " description " << description);
            
            plugIn->search(number, description, prefix);
            
            D_PRINT("search number " << number 
                    << " description " << description
                    << " prefix " << prefix);
          }

        }

        rwSleep(5000);
      }
      else
      {
        cerr << endl << "DAT::PrefixDesc::PrefixDescPlugInCheck: ";
        cerr << "Registry parse failed near '";
        cerr << registryFile << "'" << endl;
      }
    }
    else
    {
      cerr << endl << "???? : ";
      cerr << "cannot open registry file '";
      cerr << registryFile << "'" << endl;
    }
  }

  D_PRINT_T("DAT::PrefixDesc::PrefixDescPlugInCheck program finished");

  cerr << endl << "DAT::PrefixDesc::PrefixDescPlugInCheck program finished" << endl << endl;

  return 0;
}                
