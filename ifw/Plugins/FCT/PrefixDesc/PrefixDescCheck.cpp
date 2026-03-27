//==============================================================================
//      
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//==============================================================================

#include "BAS/Trace.hpp"
#include "PLI/DataCollection.hpp"
#include "PLI/FunctionCollection.hpp"
#include "EDR/Container.hpp"
#include "FCT/PrefixDescPlugIn.hpp"

int main(int argc, char *argv[])
{

  return 0;   // this program does not work
  
  PLI::DataCollection *dataColl;

  SELECT_DEBUG_LEVEL;

  D_ENTER("main");

  D_ARG(argc);
  D_ARG(argv);
  D_ARG(*argv);

  D_PRINT_T("FCT::PrefixDesc::PrefixDescCheck program started");

  cerr << endl << "FCT::::PrefixDescCheck program started" << endl << endl;

  BAS::RegisteredObject::rootName("integrate");


//  BAS::RegistryEntry root(BAS::RegisteredObject::rootName());
//  root.makeRootNode();
//
//  BAS::RegisteredObject::registry(&root);
//
//  BAS::RegisteredObject* logger = new BAS::RegisteredObject("logger");
//
//  BAS::RegisteredObject::log(logger);
//  //----------------------------------------------------------------------
//  // Test the data collection
//  //----------------------------------------------------------------------
//
//  D_PRINT_T("FCT::PrefixDescCheck data collection test started");
//
//  cerr << endl << "FCT::PrefixDescCheck data collection test started";
//  cerr << endl << endl;
//
//  BAS::RegistryEntryPtr collGroupData =
//    new BAS::RegistryEntry("DataPool");
//
//  BAS::RegistryEntryPtr PrefixDescDataPI =
//    new BAS::RegistryEntry("PrefixDescDataPlugIn");
//
//  PrefixDescDataPI->addEntry("SharedLibraryName","DAT_PrefixDesc");
//  PrefixDescDataPI->addEntry("GeneratorFunctionName","ModuleStart");
//
//  BAS::RegistryEntryPtr PrefixDescDataPlugIn =
//    new BAS::RegistryEntry("Module");
//
//  PrefixDescDataPlugIn->addEntry("Active",
//                                 "true");
//
//  PrefixDescDataPlugIn->addEntry("PrefixDescFile",
//                           "./cc_test.dat");
//
//  PrefixDescDataPI->addEntry(PrefixDescDataPlugIn);
//
//  collGroupData->addEntry(PrefixDescDataPI);
//
//  root.addEntry(collGroupData);
//
//  if (root.isValid() == true)
//  {
//    dataColl = new PLI::DataCollection("integrate.DataPool");
//
//    if (dataColl->isValid() == false)
//    {
//      cerr << endl << "FCT::PrefixDescCheck: ";
//      cerr << "Cannot create the data interfaces !!!" << endl;
//      cerr << dataColl->status() << endl << endl;
//    }
//    else
//    {
//      int numOfData = dataColl->entries();
//
//      for (int i = 0; i < numOfData; i++)
//      {
//        PLG::DataPlugIn* dataPI = dataColl->operator [](i)->plugIn();
//
////         if ( dataPI->init() == false )
////         {
////           cerr << endl << "FCT::PrefixDescCheck: ";
////           cerr << "Cannot init the Data PlugIn !!!" << endl;
////         }
//      }
//    }
//  }
//  else
//  {
//    cerr << endl << "FCT::PrefixDescCheck: ";
//    cerr << "Invalid registry - parse failed !!!" << endl << endl;
//  }
//
//  //----------------------------------------------------------------------
//  // Test the function collection
//  //----------------------------------------------------------------------
//
//  D_PRINT_T("FCT::PrefixDescCheck function collection test started");
//
//  cerr << endl << "FCT::PrefixDescCheck function collection test started";
//  cerr << endl << endl;
//
//  BAS::RegistryEntryPtr collGroupFunc =
//    new BAS::RegistryEntry("FunctionPool");
//
//  BAS::RegistryEntryPtr PrefixDescFuncPI =
//    new BAS::RegistryEntry("PrefixDescFuncPlugIn");
//
//  PrefixDescFuncPI->addEntry("SharedLibraryName","FCT::PrefixDesc");
//  PrefixDescFuncPI->addEntry("GeneratorFunctionName","ModuleStart");
//
//  BAS::RegistryEntryPtr PrefixDescFuncPlugIn =
//    new BAS::RegistryEntry("PlugIn");
//
//  PrefixDescFuncPlugIn->addEntry("DataPlugIn",
//                           "integrate.Datafaces.PrefixDescDataPlugIn" );
//
//  PrefixDescFuncPI->addEntry(PrefixDescFuncPlugIn);
//
//  collGroupFunc->addEntry(PrefixDescFuncPI);
//
//  root.addEntry(collGroupFunc);
//
//  if (root.isValid() == true)
//  {
//    PLI::FunctionCollection funcColl("integrate.FunctionPool");
//
//    if (funcColl.isValid() == false)
//    {
//      cerr << endl << "FCT::PrefixDescCheck: ";
//      cerr << "Cannot create the function interfaces !!!" << endl;
//      cerr << funcColl.status() << endl << endl;
//    }
//    else
//    {
//      EDR::Container* edr = new EDR::Container();
//
//      edr->contentType( EDR::Container::DETAIL );
////      edr->bNumNorm( "004940" );
//
//      int numOfFunc = funcColl.entries();
//
//      for (int i = 0; i < numOfFunc; i++)
//      {
//        FCT::PrefixDescPlugIn* funcPI = (FCT::PrefixDescPlugIn*)funcColl[i]->plugIn();
//
////         if ( funcPI->init( dataColl ) )
////         {
////           funcPI->processEdrContainer( edr );
////         }
////         else
////         {
////           cerr << endl << "FCT::PrefixDescCheck: ";
////           cerr << "Cannot init the Function PlugIn! No Edr processing." << endl;
////         }
//      }
//    }
//  }
//  else
//  {
//    cerr << endl << "FCT::PrefixDescCheck: ";
//    cerr << "Invalid registry - parse failed !!!" << endl << endl;
//  }

  D_PRINT_T("FCT::PrefixDesc::PrefixDescCheck program finished");

  cerr << endl << "FCT::PrefixDesc::PrefixDescCheck program finished" << endl << endl;

  return 0;

}
