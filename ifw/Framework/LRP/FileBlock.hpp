#ifndef LRP_FILEBLOCK_HPP
#define LRP_FILEBLOCK_HPP

//==============================================================================
//
//             1998, 1999, 2000 (c) Copyright by SOLUTION42 AG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: 
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the class FileBlock. This class is used to store the
//   description of a file datablock.   
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
// $RCSfile: FileBlock.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/11/21 12:50:37 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: FileBlock.hpp,v $
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================
namespace LRP
{
/** <b><tt>FileBlock</tt></b> is used to store the description of a file
 *  datablock.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FileBlock.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2000/11/21 12:50:37 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class FileBlock
{
  public:

    enum FileBlockT
    {
      FIX,
      VAR
    };

    /**@name FileBlock constructors and destructor */
    //@{

    FileBlock( const BAS::String& name );

    //@}


    /**@name FileBlock public methods */
    //@{

    //@}

  private:
    // instance members
    int        recordLengthM;
    char       separatorM;
    FileBlockT blockTypeM;
};
}
#endif // FILEBLOCK_HPP
