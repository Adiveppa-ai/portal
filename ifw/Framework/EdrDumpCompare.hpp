//
//  Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//  
//  This material is the confidential property of Oracle Corporation or its
//  licensors and may be used, reproduced, stored or transmitted only in
//  accordance with a valid Oracle license or sublicense agreement.
//

#ifndef TST_EDRCOMPARE_H
#define TST_EDRCOMPARE_H

#include <rw/tvordvec.h>
#include <rw/tpslist.h>
#include <rw/tstack.h>

#include "BAS/Trace.hpp"
#include "BAS/String.hpp"
#include "BAS/DateTime.hpp"
#include "BAS/Decimal.hpp"

#include "EDR/DatablockDescr.hpp"
#include "EDR/DatablockValue.hpp"
#include "EDR/Factory.hpp"
#include "EDR/BlockIndex.hpp"
#include "EDR/ContainerIndex.hpp"
#include "EDR/Index.hpp"
#include "EDR/Iterator.hpp"
#include "EDR/Container.hpp"
#include "EdrDumpParser.hpp"
#include "EDR/FieldDescr.hpp"
#include "EDR/Value.hpp"
#include "PLG/FunctionPlugIn.hpp"


namespace TST {

//------------------------------------------------------------------------------
// forward declaration and typedefs
//------------------------------------------------------------------------------

class Parser;
typedef RWTPtrOrderedVector<EDR::Datablock> EdrDatablockList;
    
class EdrDumpCompare 
{
public:

 /** Constructor
   *
   * Comparing the edr dump.
   */
  EdrDumpCompare();

 /** Destructor
   *
   * Clean the object of the class.
   */
 ~EdrDumpCompare();

 /** compareEDR
   *
   * Compare the EdrDump.
   *
   * @param  edrContainerList The orginal edr dump container
   * @param  edrContainerList The edr dump container which needs to be compare
   * @param  String message after comparison
   *
   * @return Status of the comparison
   */
  bool compareEDR(PLG::EdrContainerList edrContainerListOrig, 
                  PLG::EdrContainerList edrContainerListCompare,BAS::String &msg);

private:

 /** compareEdrBlocks
   *
   * Compare the Edr blocks.
   *
   * @param  String message after comparison
   *
   * @return Status of the comparison
   */
  bool compareEdrBlocks(BAS::String& errMsg);

 /** compareEdrFldValues
   *
   * Compare the value of Edr fields.
   *
   * @param  Value the original value
   * @param  Value the value needs to be compared
   * @param  String message after comparison
   *
   * @return Status of the comparison
   */
  bool compareEdrFldValues(EDR::Value *value1, EDR::Value *value2, BAS::String& errMsg );

 /** compareEdrAttr
   *
   * Compare the type of Edr container.
   *
   * @param  Container the original edr container
   * @param  Container the edr container needs to be compared
   * @param  String message after comparison
   *
   * @return Status of the comparison
   */
  bool compareEdrAttr(EDR::Container *origEdr, EDR::Container *compareEdr, BAS::String& errMsg);

 /** addBlock
   *
   * Add edr block.
   *
   * @param  Datablock the block which needs to be added
   * @param  bool flag for original and compare block
   */
  void addBlock(EDR::Datablock *rdb, bool orig);

 /** printBlockValues
   *
   * Print the value of the block.
   *
   * @param  Datablock the block which value needs to be printed
   * @param  ostringstream the stream for printing the values
   */
  void printBlockValues( EDR::Datablock* rdb, std::ostringstream& logStream );

  EdrDatablockList  origBlockListM;
  EdrDatablockList  compareBlockListM;
};

}

#endif
