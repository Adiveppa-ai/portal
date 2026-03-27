#ifndef STR_FILEIO_HPP
#define STR_FILEIO_HPP 1
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
// Block: STR
//------------------------------------------------------------------------------
// Module Description:
//  <description>
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work, finished, accepted>
//
//------------------------------------------------------------------------------
// Responsible: jens keckstein
//
// $RCSfile: FileIo.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: ssajjans $
// $Date: 2012/02/08 21:37:48 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: FileIo.hpp,v $
//Revision 1.4
//sknanda_bug-12697606  Changes for 3rd party upgrade in Cronous

// Revision 1.3  2001/08/28 07:04:45  jkeckst
// PETS 37618 code review cr-08.2001
//
// Revision 1.2  2001/07/04 13:37:23  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.1  2000/08/24 11:10:45  rmurawsk
// STR splitted into Base and STR
//
// Revision 1.21  2000/01/06 13:03:43  clohmann
// Error messages from operation system added.
//
//==============================================================================

#ifndef   BAS_DEFS_HPP
  #include "BAS/Defs.hpp"
#endif
#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace STR
{
/** <tt><b>FileIo</b></tt> is the internal file handling class.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: FileIo.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2012/02/08 21:37:48 $</font></td>
    <td><font size=-1>$Author: ssajjans $</font></td>
    </tr>
    </table>                
*/
class FileIo : public std::fstream D_THREADINFO_M
{
  public:
    /**@name FileIo constructors and destructor */
    //@{ 
    ///
    FileIo();
    ///
    FileIo(const BAS::String& newFileName, std::ios_base::openmode openFlags = std::ios_base::in|std::ios_base::out);
    ///
    ~FileIo();
    //@}
    
    /**@name FileIo special functions */
    //@{ 
    /** Open a file for reading and/or writing.
    If no flags were given, the file open [in | out]
    @param newFileName  the complete name for the file to work on
    @param openFlags    [ app (append) |
                          ate (at end) |
                          binary (default text-modus) |
                          in (reading) |
                          out (writing) |
                          trunc (overwrite) |
                          nocreate (must exists) |
                          noreplace (must not exists) ].
    @return true file is ready for working. <br>
    false an error occurs, file is not ready for working.
    */
    bool openFile(const BAS::String& newFileName, std::ios_base::openmode openFlags = std::ios_base::in|std::ios_base::out);
    /// If file is open, it will be closed 
    bool closeFile(void);

    // *********************************************************************
    /** Read one line from file.
        The end of line is will be detected by "\n".
        @param line contains the readed line or is empty.
        @return true reading was successful. <br> 
        false an error occurs or eof detected.
    */
    bool readLine(BAS::String& line);
    
    // *********************************************************************
    /** Write one line to file.
        A "end of line" character ("\n") is added to the output.
        @param line contains the string to be written.
        @return true writing was successful. <br>
        false an error occurs. 
    */
    bool writeLine(const BAS::String& line);

    // *********************************************************************
    /** Read count (blockLen) chars from file.
        If blockLen is not given the member blockSizeM is taken.
        @param line contains the readed line or is empty.
        @param blockLen contains the count of chars to be read
        @return true reading was successful. <br>
        false an error occurs or eof detected.
    */
    bool readBlock(BAS::String& line, size_t blockLen = 0);

    // *********************************************************************
    /** Writes all characters in line to file.
        @param line contains the charcters to be written
        @return true writing was successful. <br>
        false an error occurs. 
    */
    bool writeBlock(const BAS::String& line);

    // *********************************************************************
    /** Read from file in block or line modus.
        This function check if blockSizeM is set to 0. If true
        all read operations call the readLine functions. If false
        all read operations call the readBlock functions.
        @param line contains the readed line or is empty.
        @return true reading was successful. <br>
        false an error occurs or eof detected.
    */
    bool read(BAS::String& line);

    // *********************************************************************
    /** Write to file in block or line modus.
        This function check if blockSizeM is set to 0. If true
        all write operations call the writeLine functions. If false
        all write operations call the writeBlock functions.
        @param line contains the string to be written.
        @return true writing was successful. <br>
        false an error occurs. 
    */
    bool write(const BAS::String& line);
    
    // *********************************************************************
    /** Set the read/write position in file.
        @param position the relative position from relFlag
        @param relFlag [ios::beg || ios::cur || ios::end]
    */
    void seekPosition(const int64 position, const seekdir relFlag = ios::beg);

    // *********************************************************************
    /** Read from file all characters until the delim-char where found.
      @param token contains the founded token or is empty
      @param delim delimeter character that marks the end of a token
      @return true reading was successful. <br>
      false an error occurs or eof detected.
    */
    bool readToDelim(BAS::String& token, char delim = '\n');

    // *********************************************************************
    /** Truncate the file. <br>
    All data from the file were removed and the filepointer is set
    to the beginning.
    */
    void truncate();
    //@}

    /**@name get functions */
    //@{
    /// 
    int64 getPosition(void);
    /// 
    const bool isOpen(void);
    ///
    const BAS::String& fileName(void) const ;
    ///
    const size_t blockSize();
    ///
    const size_t bufferSize();
    ///
    const BAS::String& systemMessage();
    //@}

    /**@name set functions */
    //@{
    ///
    void blockSize(const size_t value);
    ///
    void bufferSize(const size_t value);
    //@}

    
  private:
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    FileIo(FileIo& right);
    const FileIo& operator=(FileIo& right);

    enum Size { MAX_BLOCK_SIZE = 8192 };
    
    size_t      blockSizeM;
    size_t      bufferSizeM;
    char        *blockBufferM;
    BAS::String   fileNameM;
    BAS::String   systemMessageM;
};

// **************************************************************************** 
// **************************************************************************** 
inline int64 FileIo::getPosition( void ) 
{
  // return the read position
  return std::fstream::tellg();
}

inline const BAS::String& FileIo::fileName(void) const 
{
  return fileNameM;
}

inline const bool FileIo::isOpen(void)
{
  //  return std::fstream::is_open();   ** for GNU **
  return std::fstream::rdbuf()->is_open();
}

inline void FileIo::blockSize(const size_t value) 
{
  blockSizeM = value;
}

inline const size_t FileIo::blockSize()
{
  return blockSizeM;
}

inline const size_t FileIo::bufferSize()
{
  return bufferSizeM;
}

inline const BAS::String& FileIo::systemMessage()
{
  return systemMessageM;
}
}

#endif // FILEIO_HPP
