#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP
/*
* Copyright (c) 1998, 2023, Oracle and/or its affiliates.  
 *
 *	This material is the confidential property of Oracle Corporation.
 *	or its subsidiaries or licensors and may be used, reproduced, stored
 *	or transmitted only in accordance with a valid Oracle license or
 *	sublicense agreement.
 */
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   Directory class implementation.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: aro
//
// $RCSfile: Directory.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:43:46 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Directory.hpp,v $
// Revision 1.24  2001/06/18 14:20:10  kb
// optional sorting by file name implemented
//
// Revision 1.23  2000/06/29 15:39:09  bt
// Changes for AIX xlC V500.
//
// Revision 1.22  1999/05/20 15:10:31  aro
// Directory::read() changed for optional negative filter.
//
// Revision 1.21  1999/05/12 08:05:15  aro
// Assigemnt operators fixed.
//
// Revision 1.20  1999/05/11 10:41:02  aro
// Canonical methods for Directory implemented.
//
// Revision 1.19  1999/04/27 07:51:14  arockel
// ErrorStatus renamed to Status.
//
// Revision 1.18  1999/04/14 12:37:15  arockel
// Directory now always matches whole lines.
//
// Revision 1.17  1999/03/31 08:51:37  arockel
// Minor improvement for th error log.
//
// Revision 1.16  1999/03/31 07:12:28  arockel
// Makefile fixed; Directory::reset() renamed to read()
//
// Revision 1.15  1999/03/30 14:52:01  arockel
// STR_InputFile and Directory improved.
//
// Revision 1.13  1999/03/30 12:26:12  arockel
// STR_InputFile and Directory improved.
//
// Revision 1.12  1999/03/29 14:12:22  arockel
// Updates in STR.
//
// Revision 1.11  1999/03/29 10:51:52  arockel
// Remaining STR classes added, Directory improved.
//
// Revision 1.4  1999/03/19 11:55:58  arockel
// Directory finished.
//
// Revision 1.1  1999/03/18 09:00:31  arockel
// Directory handling class added.
//
//==============================================================================

#ifndef RW_TOOLS_TVSRTVEC_H
  #include <rw/tvsrtvec.h> 
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef BAS_STATUS_HPP
  #include "BAS/Status.hpp"
#endif

#include <dirent.h>

namespace BAS 
{
/** <tt><b>Directory</b></tt> is a utility class for access to file system 
    directories.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Directory.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:43:46 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>
                                                       
    <dl>
      <dt><b>Registry entries</b></dt>
        <dd>none
        <dt><b>Messages send</b></dt>
        <dd>none
      <dt><b>Messages received</b></dt>
        <dd>none
      <dt><b>Errors</b></dt>
        <dd>ERR_NO_PATH_NAME
        <dd>ERR_NO_DIR
        <dd>ERR_INVALID_PATTERN
    </dl>                       
*/
class Directory D_THREADINFO
{
  public:
    /** Default constructor.
    */
    Directory();

    /** Copy constructor.
    */
    Directory(const Directory& orig);

    /** Constructor.
        @param path The path of the directory to be scanned.
    */
    Directory(const String& path);

    /** Constructor.
        @param path The path of the directory to be scanned.
        @param filter A filter.
        @param negFilter A second filter (refer to <tt>read()</tt>)
        @param defSort Sorting criterion (default by timestamp otherwise file name)
    */
    Directory(const String& path, 
                  const String& filter, 
                  const String& negFilter = "",
                  const bool        defSort = true);
    /** Destructor.
    */
    ~Directory();

    /** Number of read directory entries.
        @return Number of entries contained in the internal entry list. 
    */
    size_t entries() const;

    /** Are there entries? 
        @return <tt>True</tt>: directory is empty / no matches,<br>
                <tt>false</tt>: directory not empty.
    */
    bool isEmpty() const;

    /** System-internal error number.
        @return The error number given by the operating system.
    */
    int errorNumber() const;

    /** Error status.
        @return The instance error status.
    */
    const Status& status() const;

    /** Current path.
        @return The path that was used to set up the entry list.
    */
    const String& path() const;

    /** Check if there is a directory present with a given name.
        If there is no such directory, errorNumberM is set accordingly
        and the directory becomes invalid.
        Validates the filtering conditions (if provided).
        @pathName The given name
    */
    void validate(const BAS::String& pathName,
                             const String& filter    = "",
                             const String& negFilter = "");

    /** Rereads the directory entry list. 
        The filters supplied to these method are applied to
        the whole filename, i.e. they are secretely extended by
        "^" at the beginning and "$" at the end of the filter string.
        @param path The file system path.
        @param filter An optional filter.
        @param negFilter An optional <em>negative</em> filter. The result will be files, that match the
                         first filter but <em>not</em> the second one.
        @param defSort An optional sorting flag. If true files will be sorted by time stamp, otherwise
                       by file name.
        @return <tt>True</tt>: reread successful,<br>
                <tt>false</tt>: error occured.
    */
    bool read(const String& path,
              const String& filter    = "",
              const String& negFilter = "",
              const bool        defSort   = true);

    /** Removes the first entry from the list.
        @return The file name of the first list entry.
    */
    String removeFirst();

    /** Checks if a file name is contained in the internal list.
        @return <tt>True</tt>: file name found,<br>
                <tt>false</tt> otherwise.
    */
    bool contains(const String& fileName) const;

    /** Checks if there was no error.
        @return <tt>True</tt>: no error,<br>
                <tt>false</tt>: error occured.
    */
    bool isValid() const;

    /** Checks if the underlying diretory is writeable for the process.
        @return <tt>True</tt> directory is writeable,<br>
                <tt>false</tt> otherwise.
    */
    bool isWriteable() const;

    /** Clears the list of entries and the error status.
    */
    void clear();

    /** Access to entries.
        @param index The position of the entry.
        @return The entry.
    */
    const String& operator[](size_t index) const;

    /** First entry.
       @return The first entry.
    */
    const String& first() const;

    /** Last entry.
       @return The last entry.
    */
    const String& last() const;

    /** Assignment operator.
        @param rVal r-value.
    */
    Directory& operator=(const Directory& rVal);

    /** Self test method.
        @return <tt>True</tt>: self test passed,<br>
                <tt>false</tt> otherwise.
    */
    static bool selfTest();

  private:

    struct DirEntry 
    {
      String fileNameM;
      time_t     fileTimeM;
      bool       defSortM;  
  
      bool operator==(const DirEntry& rVal) const;
      bool operator<(const DirEntry& rVal)  const;
    };


    String                                    pathM;
    String                                    positivePatternM;
    String                                    negativePatternM;
    int                                           errorNumberM;
    Status                                    statusM;
    RWTValOrderedVector<DirEntry> entryListM;

    /** Open the directory whose name is given as input.
        If open successful returns the file list. 
        @dirPtr The pointer to the list of files present inside the directory
        @return <tt>True</tt>: Open successful,<br>
	<tt>false</tt>: error occured.
    */
    bool scanDir(DIR** dirPtr);

    /**  Verify the filtering patterns used file manipulation.
         @filter positive filter
         @negFilter negative filter
         @return <tt>True</tt>: if valid patterns,<br>
                <tt>false</tt>: invalid patterns
    */
    bool validateFilteringConditions(const String& filter ,
                                     const String& negFilter ,
                                     RWCRegexp & positiveExpr ,
                                     RWCRegexp & negativeExpr);

 
};

/** Output operator.
*/
std::ostream& operator<<(std::ostream& os, const Directory& rVal);

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------
inline const String&
Directory::path() const
{
  return pathM;
}

//-------------------------------------------------------------------------

inline size_t
Directory::entries() const
{
  return entryListM.length();
}

//-------------------------------------------------------------------------

inline bool
Directory::isEmpty() const
{
  return entryListM.isEmpty();
}

//-------------------------------------------------------------------------

inline int
Directory::errorNumber() const
{
  return errorNumberM;
}                                

//-------------------------------------------------------------------------

inline const Status&
Directory::status() const
{
  return statusM;
}                                

//-------------------------------------------------------------------------

inline void
Directory::clear()
{
  errorNumberM     = 0;
  positivePatternM = "";
  negativePatternM = "";
  statusM.clear();
  entryListM.clear();
}                                

//-------------------------------------------------------------------------
inline const String& 
Directory::operator[](size_t index) const
{
  return entryListM[index].fileNameM;
}

//-------------------------------------------------------------------------

inline const String& 
Directory::first() const
{
  return entryListM.first().fileNameM;
}

//-------------------------------------------------------------------------

inline const String& 
Directory::last() const
{
  return entryListM.last().fileNameM;
}

//-------------------------------------------------------------------------

inline bool 
Directory::DirEntry::operator==(const Directory::DirEntry& rVal) const
{
  if (true == defSortM)
  {
    return fileTimeM == rVal.fileTimeM;
  }
  else
  {
    return fileNameM == rVal.fileNameM;
  }
}     

//-------------------------------------------------------------------------

inline bool 
Directory::DirEntry::operator<(const Directory::DirEntry& rVal) const
{
  if (true == defSortM)
  {
    return fileTimeM < rVal.fileTimeM;
  }
  else
  {
    return fileNameM < rVal.fileNameM;
  }
}

//-------------------------------------------------------------------------
}
#endif // DIRECTORY_HPP
