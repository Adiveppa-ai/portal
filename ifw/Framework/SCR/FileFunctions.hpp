#ifndef SCR_FILEFUNCTIONS_HPP
#define SCR_FILEFUNCTIONS_HPP 

/* @(#)%Portal Version: FileFunctions.hpp:PlatformR2Int:2:2006-Jul-16 15:27:34 % */
//==============================================================================
//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//  <description>
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: FileFunctions.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:57 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: FileFunctions.hpp,v $
// Log 2002/07/29 cdiab
// - added FileTell and FileSeek
//
// Revision 1.8  2000/11/23 11:52:20  sd
// - New function Bool fileRename(String,String)
//
// Revision 1.7  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
// Revision 1.6  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
// Revision 1.5  2000/05/25 14:02:56  sd
// - function Bool fileFlush(File) added.
//
// Revision 1.4  2000/04/18 14:38:19  sd
// - Interface for fileWriteLong() changed. Now there is support for
//   formating the output.
//
// Revision 1.3  2000/04/18 13:23:27  sd
// - function Long strSearchRegExpr(String,String[,Long]) added
// - function Bool fileDelete(String) added.
//
// Revision 1.2  2000/03/23 14:51:04  sd
// - Functions fileReadLine(), fileEof() and fileIsOpen() added.
//
// Revision 1.1  2000/03/23 11:25:52  sd
// Initial revision.
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_DATA_HPP
  #include "SCR/Data.hpp"
#endif
namespace SCR
{

class Interpreter;
class ParserStack;
class FctDescr;

/**<b><tt>FileOpen</tt></b> is the function node for opening files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileOpen : public BoolNode
{
  public:
    /**@name FileOpen constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileOpen();

    //@}

    /**@name FileOpen public methods */
    //@{

    /** Execute the file open function.
     *  @return <b>true</b> if operation was successful, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a fileOpen() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:

    /** Private constructor. Use the factory function to create FileOpen
     *  nodes.
     *  @param fileNode The filedata variable to open
     *  @param fileName The filename data node
     *  @param openMode The mode for the open operation
     */
    FileOpen( FileData*   fileNode,
                  StringNode* fileName,
                  StringNode* openMode );

    // instance members
    FileData*   fileNodeM;
    StringNode* fileNameM;
    StringNode* openModeM;
};

/**<b><tt>FileClose</tt></b> is the function node for closing files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileClose : public VoidNode
{
  public:
    /**@name FileClose constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileClose();

    //@}

    /**@name FileClose public methods */
    //@{

    /** Execute the file close function.
     *  @return <b>true</b> if operation was successful, <b>false</b> otherwise
     */
    virtual void result();

    /** Create a fileClose() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:

    /** Private constructor. Use the factory function to create FileClose
     *  nodes.
     *  @param fileNode The filedata variable to close
     */
    FileClose( FileData* fileNode );

    // instance members
    FileData*   fileNodeM;
};

/**<b><tt>FileWriteString</tt></b> is the function for writing data to
 * files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileWriteString : public BoolNode
{
  public:
    /**@name FileWriteString constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileWriteString();

    //@}

    /**@name FileWriteString public methods */
    //@{

    /** Execute the fileWriteString() function
     *  @return <b>true</b> if operation was successful, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a fileWriteString() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:

    /** Private constructor. Use the factory function to create 
     *  FileWriteString nodes.
     *  @param fileNode The file to write to
     *  @param stringNode The string to write
     */
    FileWriteString( FileData*   fileNode,
                         StringNode* stringNode );

    // instance members
    FileData*   fileNodeM;
    StringNode* stringNodeM;
};

/**<b><tt>FileWriteLong</tt></b> is the function for writing data to
 * files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileWriteLong : public BoolNode
{
  public:
    /**@name FileWriteLong constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileWriteLong();

    //@}

    /**@name FileWriteLong public methods */
    //@{

    /** Execute the fileWriteLong() function
     *  @return <b>true</b> if operation was successful, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a fileWriteLong() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:

    /** Private constructor. Use the factory function to create 
     *  FileWriteLong nodes.
     *  @param fileNode The file to write to
     *  @param longNode The long value to write
     *  @param lengthNode The length of the output value
     *  @param padChar The pad character
     */
    FileWriteLong( FileData*   fileNode,
                       LongNode*   longNode,
                       LongNode*   lengthNode,
                       BoolNode*   leadingNode,
                       StringNode* padCharNode );

    // instance members
    FileData*   fileNodeM;
    LongNode*   longNodeM;
    LongNode*   lengthNodeM;
    BoolNode*   leadingNodeM;
    StringNode* padCharNodeM;
    BAS::String      bufferM;
};

/**<b><tt>FileReadLine</tt></b> is the function for writing data to
 * files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileReadLine : public BoolNode
{
  public:
    /**@name FileReadLine constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileReadLine();

    //@}

    /**@name FileReadLine public methods */
    //@{

    /** Execute the fileReadLine() function
     *  @return <b>true</b> if operation was successful, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a fileReadLine() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:

    /** Private constructor. Use the factory function to create 
     *  FileReadLine nodes.
     *  @param fileNode The file to read from
     *  @param stringNode The string to read
     *  @param longNode The maximum line length
     */
    FileReadLine( FileData*       fileNode,
                      StringDataNode* stringNode,
                      LongNode*       longNode );

    // instance members
    FileData*       fileNodeM;
    StringDataNode* stringDataM;
    LongNode*       longNodeM;
};

/**<b><tt>FileEof</tt></b> is the function to check for end-of-file.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileEof : public BoolNode
{
  public:
    /**@name FileEof constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileEof();

    //@}

    /**@name FileEof public methods */
    //@{

    /** Execute the fileEof() function
     *  @return <b>true</b> if end-of-file, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a fileEof() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:

    /** Private constructor. Use the factory function to create 
     *  FileEof nodes.
     *  @param fileNode The file to check
     */
    FileEof( FileData* fileNode );

    // instance members
    FileData* fileNodeM;
};

/**<b><tt>FileIsOpen</tt></b> is the function to check for open file
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileIsOpen : public BoolNode
{
  public:
    /**@name FileIsOpen constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileIsOpen();

    //@}

    /**@name FileIsOpen public methods */
    //@{

    /** Execute the fileIsOpen() function
     *  @return <b>true</b> if file is open, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a fileEof() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:

    /** Private constructor. Use the factory function to create 
     *  FileIsOpen nodes.
     *  @param fileNode The file to check
     */
    FileIsOpen( FileData* fileNode );

    // instance members
    FileData* fileNodeM;
};

/**<b><tt>FileDelete</tt></b> is the function node for deleting files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileDelete : public BoolNode
{
  public:
    /**@name FileDelete constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileDelete();

    //@}

    /**@name FileDelete public methods */
    //@{

    /** Execute the fileDelete() function.
     *  @return <b>true</b> if operation was successful, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a fileDelete() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Private constructor. Use the factory function to create FileDelete
     *  nodes.
     *  @param fileName The filename data node
     */
    FileDelete( StringNode* fileName );

    // disallow use of copy and default constructor
    FileDelete();
    FileDelete( const FileDelete& );
    const FileDelete& operator=( const FileDelete& );


    // instance members
    StringNode* fileNameM;
};

/**<b><tt>FileFlush</tt></b> is used to flush the current filebuffer contents to disk
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileFlush : public BoolNode
{
  public:
    /**@name FileFlush constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileFlush();

    //@}

    /**@name FileFlush public methods */
    //@{

    /** Execute the fileFlush() function
     *  @return <b>true</b> if flush was successful, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a fileFlush() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:

    /** Private constructor. Use the factory function to create 
     *  FileFlush nodes.
     *  @param fileNode The file to check
     */
    FileFlush( FileData* fileNode );

    // instance members
    FileData* fileNodeM;
};

/**<b><tt>FileRename</tt></b> is the function node for renaming files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileRename : public BoolNode
{
  public:
    /**@name FileRename constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileRename();

    //@}

    /**@name FileRename public methods */
    //@{

    /** Execute the fileRename() function.
     *  @return <b>true</b> if operation was successful, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a fileRename() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Private constructor. Use the factory function to create FileRename
     *  nodes.
     *  @param sourceName The old filename
     *  @param destName The new filename
     */
    FileRename( StringNode* sourceName,
                    StringNode* destName );

    // disallow use of copy and default constructor
    FileRename();
    FileRename( const FileRename& );
    const FileRename& operator=( const FileRename& );

    // instance members
    StringNode* sourceNameM;
    StringNode* destNameM;
};

/**<b><tt>FileCopy</tt></b> is the function node for Copying files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileCopy : public BoolNode
{
  public:
    /**@name FileCopy constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileCopy();

    //@}

    /**@name FileCopy public methods */
    //@{

    /** Execute the fileCopy() function.
     *  @return <b>true</b> if operation was successful, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a FileCopy() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Private constructor. Use the factory function to create FileCopy
     *  nodes.
     *  @param sourceName The old filename
     *  @param destName The new filename
     */
    FileCopy( StringNode* sourceName,
                  StringNode* destName );

    // disallow use of copy and default constructor
    FileCopy();
    FileCopy( const FileCopy& );
    const FileCopy& operator=( const FileCopy& );

    // instance members
    StringNode* sourceNameM;
    StringNode* destNameM;
};

/**<b><tt>FileTell</tt></b> is the function node for getting the current
 * read/write pointer position in a file.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileTell : public LongNode
{
  public:
    /**@name FileTell constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileTell();

    //@}

    /**@name FileTell public methods */
    //@{

    /** Execute the fileTell() function.
     *  @return <b>the position in byte</b> if successful, <b>-1</b> otherwise
     */
    virtual int64 result();

    /** Create a fileTell() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Private constructor. Use the factory function to create FileTell
     *  nodes.
     *  @param fileNode The file to check
     */
    FileTell( FileData* fileNode );

    // disallow use of copy and default constructor
    FileTell();
    FileTell( const FileTell& );
    const FileTell& operator=( const FileTell& );

    // instance members
    FileData* fileNodeM;
};

/**<b><tt>FileSeek</tt></b> is the function node for setting the current
 * read/write pointer position in a file.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FileSeek : public BoolNode
{
  public:
    /**@name FileSeek constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FileSeek();

    //@}

    /**@name FileSeek public methods */
    //@{

    /** Execute the fileSeek() function.
     *  @return <b>true</b> if successful, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a fileSeek() function node.
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Private constructor. Use the factory function to create FileSeek
     *  nodes.
     *  @param fileNode The file to check
     *  @param offsetNode The offset in byte from file start
     */
    FileSeek( FileData* fileNode, LongNode* offsetNode );

    // disallow use of copy and default constructor
    FileSeek();
    FileSeek( const FileSeek& );
    const FileSeek& operator=( const FileSeek& );

    // instance members
    FileData* fileNodeM;
    LongNode* offsetNodeM;
};
}
#endif // FILEFUNCTIONS_HPP
