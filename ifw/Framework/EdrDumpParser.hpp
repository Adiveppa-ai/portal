//
// Copyright (c) 2004 - 2024 Oracle and/or its affiliates.
//
// This material is the confidential property of Oracle Corporation or 
// its licensors and may be used, reproduced, stored or transmitted only 
// in accordance with a valid Oracle license or sublicense agreement.
//

#ifndef TST_PARSER_H
#define TST_PARSER_H

#include <rw/tvordvec.h>
#include <rw/tpslist.h>
#include <rw/tstack.h>

#include "BAS/Trace.hpp"
#include "BAS/String.hpp"
#include "BAS/DateTime.hpp"
#include "BAS/Decimal.hpp"

#include "EDR/DatablockDescr.hpp"
#include "EDR/Factory.hpp"
#include "EDR/BlockIndex.hpp"
#include "EDR/ContainerIndex.hpp"
#include "EDR/Index.hpp"
#include "EDR/Iterator.hpp"
#include "EDR/Container.hpp"
#include "EDR/Iterator.hpp"
#include "PLG/InputStreamDevice.hpp"
#include "PLG/FunctionPlugIn.hpp"

namespace TST {

class Lexer;

class Parser 
{
public:

 /** Constructor
   *
   * Parsing the edr dump file/edr container.
   *
   * @param  descFile The file to be parsed
   */
  Parser(BAS::String& descFile);

 /** Constructor
   *
   * Parsing the edr dump file/edr container.
   *
   * @param  factory The edr container to be parsed
   */
  Parser(EDR::Factory *factory);

 /** Destructor
   *
   * Clean the object of the class.
   */
  ~Parser();

 /** parse
   *
   * Parse the EdrDump file.
   *
   * @param  edrDumpFileName  The edr dump file to be parsed
   * @param  EdrContainerList Edr container
   * @param  String errMsg 
   * @param  InputDevice Handle of the device is used to pushed the Edr, default value NULL
   *
   * @return Status of the parsing 
   */
  bool parse(BAS::String& edrDumpFileName,
                          PLG::EdrContainerList&,
                          BAS::String& errMsg,
                          PLG::InputDevice* inputDevice = NULL);

 /** getContainerType
   *
   * Get the type of the container.
   *
   * @param   str String to be checked 
   * @return  type of the container
   */
  EDR::Container::containerTypeT getContainerType(BAS::String& str);

 /** getContentType
   *
   * Get the type of the content of the container.
   *
   * @param   str String to be checked 
   * @return  type of the content of the container
   */
  EDR::Container::contentTypeT getContentType(BAS::String& str);

 /** getBlkName
   *
   * Get the block name of the block type.
   *
   * @param  block type to be checked
   * @param  block name to be returned
   */
  void getBlkName(int level, BAS::String &blkTypeName, BAS::String &blkName);

 /** getParentBlkName
   *
   * Get the block name of the parent block.
   *
   * @return  block name of the parent block
   */
  BAS::String& getParentBlkName();

 /** getParentBlkName
   *
   * Get the block name of the parent block.
   *
   * @param  level of the parent block to be returned
   * @return  block name of the parent block
   */
  BAS::String& getParentBlkName(int level);

 /** setParentBlkName
   *
   * Set the block name of the parent block.
   *
   * @param  parent block name to be set
   */
  void setParentBlkName(BAS::String& parentBlkName);

 /** addBlkTypeName
   *
   * Add block type.
   *
   * @param  block type to be add
   */
  void addBlkTypeName(BAS::String& blkTypeName);

 /** setIndexValue
   *
   * Set the value of the edr index.
   *
   * @param  Index of the edr
   * @param  string to be set
   * @param  state to be set
   */
  void setIndexValue(EDR::Index& edrIndex, BAS::String& value, BAS::String& state);

 /** getFactory
   *
   * Get edr factory
   *
   * @return  edr factory
   */
  EDR::Factory *getFactory();

 /** getCurrEdr
   *
   * Get current edr
   *
   * @return  current edr
   */
  EDR::Container *getCurrEdr();

 /** setCurrEdr
   *
   * Set current edr
   *
   * @param  current edr
   */
  void setCurrEdr(EDR::Container * edr);

 /** addEdr
   *
   * Add edr into edr contaner.
   *
   * @param  edr to be added
   */
  void addEdr(EDR::Container *edr);

 /** dump
   *
   * Dump edr into a file.
   *
   * @param  file name where the edr to be dump
   */
  void dump(BAS::String fileName);

 /** getEdrContainer
   *
   * Get edr container.
   *
   * @return  edr container
   */
  PLG::EdrContainerList getEdrContainerList();

  // Input Device for pushing the parsed edr into EdrContainer
  PLG::InputDevice* inputDeviceM;

private:

 /** parse
   *
   * Parse the string
   *
   * @param   lexical analyzer
   * @return  token
   */
  int parse(void *lexer);

 /** replaceEnvVar
   *
   * Replaces the env variable with the its value in the input EDR Dump
   *
   * @param   configValue - which can have the env variable in %ABC% format
   * @return  resultValue - env variables are substituted with the value
   */
  void replaceEnvVar(const BAS::String& configValue, BAS::String& resultValue);

private:
  EDR::Factory *factoryM;
  bool needToDeleteFactoryM;
  EDR::Container *currEdrM;
  PLG::EdrContainerList edrContainerListM;

  RWTValSlist<BAS::String> blkTypeNameListM;
  BAS::String parentBlkNameM;

  bool validM;
};

}


inline EDR::Factory *
TST::Parser::getFactory()
{
  return factoryM;
}

inline EDR::Container *
TST::Parser::getCurrEdr()
{
  return currEdrM;
}

inline void 
TST::Parser::setCurrEdr(EDR::Container * edr)
{
  currEdrM = edr;
}

inline void
TST::Parser::addBlkTypeName(BAS::String& blkTypeName)
{
  blkTypeNameListM.insert(blkTypeName);
}

inline void
TST::Parser::addEdr(EDR::Container *edr)
{
  edrContainerListM.insert(edr);
}

inline PLG::EdrContainerList 
TST::Parser::getEdrContainerList()
{
  return edrContainerListM;
}

inline void
TST::Parser::dump(BAS::String fileName)
{
  ofstream orig( fileName );
  while (!edrContainerListM.isEmpty())
  {
    orig << *edrContainerListM.removeFirst() << endl;
  }
}

inline BAS::String&
TST::Parser::getParentBlkName()
{
  return parentBlkNameM;
}

inline BAS::String&
TST::Parser::getParentBlkName(int level)
{
  // Sync the parent block name to the current level
  while (blkTypeNameListM.entries() >= (size_t)level)
  {
    blkTypeNameListM.removeLast();
    size_t pos = parentBlkNameM.last(".");
    if (pos != RW_NPOS)
    {
      parentBlkNameM.remove(pos);
    }
  }

  return parentBlkNameM;
}

inline void
TST::Parser::setParentBlkName(BAS::String& parentBlkName)
{
  parentBlkNameM = parentBlkName;
}

#endif
