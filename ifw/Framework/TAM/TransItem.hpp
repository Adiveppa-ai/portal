#ifndef TAM_TRANSITEM_HPP
#define TAM_TRANSITEM_HPP
// "@(#)%Portal Version: TransItem.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:46:27 %";
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: TAM
//
//------------------------------------------------------------------------------
// Module Description:
//   Transaction item class implementation.
//
// Open Points:
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: TAM_TransItem.hpp,v $
// $Revision: 1.3 $
// $Author: mliebmann $
// $Date: 2001/08/10 08:15:20 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: TAM_TransItem.hpp,v $
// Revision 1.3  2001/08/10 08:15:20  mliebmann
// PETS #37618 code reviewed
//
// Revision 1.2  2001/06/27 09:57:51  bt
// Enumeration transaction item type values changed to match PROCESS_STATUS.
//
// Revision 1.1  2001/05/08 09:15:07  bt
// Initial version.
//
//==============================================================================

#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_LOCKEDVALORDEREDVECTOR_HPP
  #include "BAS/LockedValOrderedVector.hpp"
#endif
namespace TAM
{
/** This class represents the transaction item.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: TransItem.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.3 $</font></td>
    <td><font size=-1>$Date: 2001/08/10 08:15:20 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>                     

    <dl>
    <dt><b>Registry entries</b></dt>
    <dd>none</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>none</dd>
    </dl> 
*/
class TransItem D_THREADINFO
{
  public:

    /** Enumeration transaction item type.
      * <ul>
      * <li> NORMAL        = 0
      * <li> RECYCLE       = 1
      * <li> RECYCLE_TEST  = 2
      * </ul> */
    enum ItemTypeT
    {
      NORMAL        = 0,
      RECYCLE       = 1,
      RECYCLE_TEST  = 2
    };

    /**@name Public Constructors */
    //@{

      /// Constructs an empty transaction item object.
      TransItem();

      /// Constructs a transaction item object with the given stream name.
      TransItem(const BAS::String& streamName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Destructor.
      ~TransItem();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Returns the transaction item type.
      TransItem::ItemTypeT itemType() const;

      /// Set the transaction item type.
      void itemType(TransItem::ItemTypeT value);

      /// Returns the stream name.
      const BAS::String& streamName() const;

      /// Set the stream name.
      void streamName(const BAS::String& value);

      /// Returns the stream name extension.
      const BAS::String& streamExtension() const;

      /// Set the stream name extension.
      void streamExtension(const BAS::String& value);

      /** Restore the internal representation of self from memory area.
        * @param ptr Pointer to a previously allocated memory area. */
      void binaryRestore(char*& ptr);

      /** Save the internal representation of self to memory area.
        * @param ptr Pointer to a previously allocated memory area. */
      void binarySave(char*& ptr) const;

      /// Returns the number of bytes necessary to store self.
      u_int64 binaryStoreSize() const;

    //@}

    /**@name Related Global Operators */
    //@{

      /** Output operator.
        * @param os The output stream.
        * @param item The transaction item to be written to the stream. */
      friend std::ostream& operator<<(std::ostream& os, const TransItem& item);

    //@}

  private:

    // The following private attributes and functions are used internally.

      ItemTypeT itemTypeM;

      BAS::String streamNameM;

      BAS::String streamExtensionM;

};

//------------------------------------------------------------------------------
// Returns the transaction item type
//------------------------------------------------------------------------------

inline TransItem::ItemTypeT
TransItem::itemType() const
{
  return itemTypeM;
}

//------------------------------------------------------------------------------
// Set the transaction item type
//------------------------------------------------------------------------------

inline void
TransItem::itemType(TransItem::ItemTypeT value)
{
  D_ENTER("TAM::TransItem::itemType(TransItem::ItemTypeT value)");
  D_ARG(value);

  itemTypeM = value;
}

//------------------------------------------------------------------------------
// Returns the stream name
//------------------------------------------------------------------------------

inline const BAS::String&
TransItem::streamName() const
{
  D_ENTER("TAM::TransItem::streamName()");

  return streamNameM;
}

//------------------------------------------------------------------------------
// Set the stream name
//------------------------------------------------------------------------------

inline void
TransItem::streamName(const BAS::String& value)
{
  D_ENTER("TAM::TransItem::streamName(const BAS::String& value)");
  D_ARG(value);

  streamNameM = value;
}

//------------------------------------------------------------------------------
// Returns the stream name extension
//------------------------------------------------------------------------------

inline const BAS::String&
TransItem::streamExtension() const
{
  D_ENTER("TAM::TransItem::streamExtension()");

  return streamExtensionM;
}

//------------------------------------------------------------------------------
// Set the stream name extension
//------------------------------------------------------------------------------

inline void
TransItem::streamExtension(const BAS::String& value)
{
  D_ENTER("TAM::TransItem::streamExtension(const BAS::String& value)");
  D_ARG(value);

  streamExtensionM = value;
}

//------------------------------------------------------------------------------
// Restore the internal representation of self from memory area
//------------------------------------------------------------------------------

inline void
TransItem::binaryRestore(char*& ptr)
{
  D_ENTER("TAM::TransItem::binaryRestore(char*&)");

  memcpy(&itemTypeM,ptr,sizeof(itemTypeM));
  ptr += sizeof(itemTypeM);

  streamNameM.binaryRestore(ptr);

  streamExtensionM.binaryRestore(ptr);
}

//------------------------------------------------------------------------------
// Save the internal representation of self to memory area
//------------------------------------------------------------------------------

inline void
TransItem::binarySave(char*& ptr) const
{
  D_ENTER("TAM::TransItem::binaryRestore(char*&)");

  memcpy(ptr,&itemTypeM,sizeof(itemTypeM));
  ptr += sizeof(itemTypeM);

  streamNameM.binarySave(ptr);

  streamExtensionM.binarySave(ptr);
}

//------------------------------------------------------------------------------
// Returns the number of bytes necessary to store self
//------------------------------------------------------------------------------

inline u_int64
TransItem::binaryStoreSize() const
{
  D_ENTER("TAM::TransItem::binaryStoreSize()");

  return (sizeof(itemTypeM) +
          streamNameM.binaryStoreSize() +
          streamExtensionM.binaryStoreSize());
}

//------------------------------------------------------------------------------
// Output operator
//------------------------------------------------------------------------------

std::ostream&
operator<<(std::ostream& os, const TransItem& item);


//------------------------------------------------------------------------------
// Definitions for TransItemList and its (locked) iterators
//------------------------------------------------------------------------------
typedef BAS::LockedValOrderedVector<TransItem> TransItemList;

typedef BAS::LockedIterator<
	BAS::ValOrderedVectorItr<TransItem>, TransItemList>
TransItemListLockedItr;

typedef BAS::LockedIterator<
	BAS::ValOrderedVectorConstItr<TransItem>, TransItemList>
TransItemListLockedConstItr;
}
#endif // TRANSITEM_HPP

