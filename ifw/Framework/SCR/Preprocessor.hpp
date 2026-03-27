#ifndef SCR_PREPROCESSOR_HPP
#define SCR_PREPROCESSOR_HPP

//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates.
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the iScript preprocessor.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: Preprocessor.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:03:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Preprocessor.hpp,v $
// Revision 1.2  2001/08/21 15:10:38  sd
// - PETS #38449 - ISCRIPT_INCLUDE environment variable introduced
//
// Revision 1.1  2001/04/18 11:59:27  sd
// - Preprocessor for include statements added.
//
//==============================================================================

#if !defined SCR_EXPORT
    #define SCR_EXPORT 
#endif

#ifndef RW_TOOLS_REGEXP_H
  #include <rw/regexp.h>
#endif
#ifndef RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace SCR
{
class Log;

/** <b><tt>PreProFileData</tt></b> is the class used to handle cascading
 *  includes in the iScript preprocessor.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Preprocessor.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:38 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class PreProFileData D_THREADINFO
{
  public:
    /**@name PreProFileData constructors and destructor */
    //@{

    /** Constructor
     */
    PreProFileData( const BAS::String& fileName,
                        const BAS::String& inputData );

    /** Destructor
     */
    ~PreProFileData();

    //@}

    /**@name PreProFileData public methods */
    //@{

    /** Get the filename
     *  @return Reference to the filename string
     */
    const BAS::String& fileName() const;

    /** Get the linenumber
     *  @return The current lineNumber
     */
    size_t lineNumber() const;

    /** Get the next line
     *  @param buffer A buffer for returning the result
     *  @return <b>true</b> if there is another line, <b>false</b> otherwise
     */
    bool nextLine( BAS::String& buffer );

    //@}

  private:
    // Instance members
    BAS::String     fileNameM;
    BAS::StringList inputLinesM;
    size_t         lineNumberM;
};

//==============================================================================
// Get the filename
//==============================================================================
inline const BAS::String& 
PreProFileData::fileName() const
{
  return fileNameM;
}

//==============================================================================
// Get the current linenumber
//==============================================================================
inline size_t
PreProFileData::lineNumber() const
{
  return lineNumberM;
}

/** <b><tt>Preprocessor</tt></b> is the iScript preprocessor used to include
 *  source files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Preprocessor.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:38 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Preprocessor D_THREADINFO
{
  public:
    /**@name Preprocessor constructors and destructor */
    //@{

    /** Constructor
     *  @param log Pointer to the log object to use for error messages
     */
    Preprocessor( Log* log );

    /** Destructor
     */
    ~Preprocessor();

    //@}

    /**@name Preprocessor public methods */
    //@{

    /** Preprocess the source code
     *  @param input Buffer for the input source code
     *  @param output Buffer for the preprocessed output
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool preprocess( const BAS::String& input, 
                     BAS::String&       output );

    /** Check for an include statement
     *  @param line The line to check
     *  @param fileName Return buffer for the include file name
     *  @return <b>true</b> if include statement, <b>false</b> otherwise
     */
    bool isIncludeLine( const BAS::String& line,
                        BAS::String&       fileName ) const;

    /** Include a file
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool include( const BAS::String& fileName );

    //@}

  private:
    // Instance members
    Log*                                logM;
    BAS::StringList                          includePathM;
    BAS::StringList                          processedFilesM;
    RWTValOrderedVector<PreProFileData> fileStackM;

    // Class members
    SCR_EXPORT static RWCRegexp regExprIncludeLineCM;
};
}
#endif // PREPROCESSOR_HPP
