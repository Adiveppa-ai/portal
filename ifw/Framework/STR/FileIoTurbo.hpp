#ifndef STR_FILEIO_TURBO_HPP
#define STR_FILEIO_TURBO_HPP 1
//==============================================================================
//
// Copyright (c) 1996, 2011, Oracle and/or its affiliates. 
// All rights reserved. 
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
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
// $RCSfile: FileIoTurbo.hpp $
// $Revision: /cgbubrm_main.pipeline/1 $
// $Author: sknanda $
// $Date: 2011/06/29 17:40:03 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.11  1999/03/30 14:52:03  arockel
// InputFile and BAS::Directory improved.
//
// Revision 1.1  1999/03/16 14:32:43  jkeckst
// first try
//
//==============================================================================

#if !defined STR_BASE_EXPORT
  #if defined(WINDOWS)
    #if !defined(STR_BASE_INTERNAL)
      #define STR_BASE_EXPORT __declspec(dllimport)
    #else
      #define STR_BASE_EXPORT __declspec(dllexport)
    #endif
  #else
    #define STR_BASE_EXPORT 
  #endif
#endif

#ifndef   BAS_DEFS_HPP
  #include "BAS/Defs.hpp"
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace STR
{
/** <tt><b>FileIoTurbo</b></tt> is the internal file handling class.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: FileIoTurbo.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_main.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2011/06/29 17:40:03 $</font></td>
    <td><font size=-1>$Author: sknanda $</font></td>
    </tr>
    </table>
*/
class FileIoTurbo D_THREADINFO 
{
  public:
    /**@name FileIoTurbo constructors and destructor */
    //@{ 
    ///
    FileIoTurbo();
    ///
    FileIoTurbo(const BAS::String& newFileName, const int64 openFlags = 0);
    ///
    ~FileIoTurbo();
    //@}
    
    /**@name FileIoTurbo special functions */
    //@{ 
    /** Open a file for reading and/or writing.
    If no flags were given, the file open [in | out]
    @param newFileName  the complete name for the file to work on
    @param openFlags    [ ios::app (append) |
                          ios::in (reading) |
                          ios::out (writing) ]
    @return true file is ready for working. <br>
    false an error occurs, file is not ready for working.
    */
    bool openFile(const BAS::String& newFileName, const int64 openFlags = 0);
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
    /** Read data from the file into the buffer specified as parameter
        @param buffer Pointer to the data buffer
        @param bufferSize The size of the data buffer
        @return The number of bytes read
     */
    size_t read(void* buffer, size_t bufferSize);

    // *********************************************************************
    /** Write buffer to file
        @param buffer Pointer to the data buffer
        @param bufferSize The size of the data buffer
        @return The number of bytes written
     */
    size_t write(const void* buffer, size_t bufferSize);

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
	bool seekPosition(const int64 position, const int relFlag = std::ios::beg);

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
    
    // *********************************************************************
    /** Read one byte from file. <br>
    */
    int getByte();
    
    //@}

    /**@name get functions */
    //@{
    ///
    bool fail();
    ///
    bool good();
    /// 
    bool eof();
    ///
    const int64 getPosition(void) const;
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
    FileIoTurbo(FileIoTurbo& right);
    const FileIoTurbo& operator=(FileIoTurbo& right);

    enum Size { MAX_BLOCK_SIZE = 8192 };
    
    STR_BASE_EXPORT static const BAS::String newLine;

    size_t      blockSizeM;
    size_t      bufferSizeM;
    char        *blockBufferM;
    BAS::String  fileNameM;
    BAS::String  systemMessageM;
    bool        isOpenM;
    bool        lastRWOperationM;
    FILE        *fileStreamM;
};

// **************************************************************************** 
// **************************************************************************** 

inline bool FileIoTurbo::good() 
{
  return (isOpenM && lastRWOperationM);
}

inline bool FileIoTurbo::fail() 
{
  return !isOpenM;
}

inline bool FileIoTurbo::eof()
{
  return (feof(fileStreamM) != 0);
}

inline const int64 FileIoTurbo::getPosition( void ) const
{
  return ftell(fileStreamM);
}

inline const BAS::String& FileIoTurbo::fileName(void) const 
{
  return fileNameM;
}

inline const bool FileIoTurbo::isOpen(void)
{
  return isOpenM;
}

inline void FileIoTurbo::blockSize(const size_t value) 
{
  blockSizeM = value;
}

inline const size_t FileIoTurbo::blockSize()
{
  return blockSizeM;
}

inline const size_t FileIoTurbo::bufferSize()
{
  return bufferSizeM;
}

inline const BAS::String& FileIoTurbo::systemMessage()
{
  return systemMessageM;
}

inline int FileIoTurbo::getByte()
{
//   unsigned char byte = 44;
//   
//   fread(&byte, 1, 1, fileStreamM);
  
  return fgetc(fileStreamM);
}
}
#endif // FILEIO_HPP
