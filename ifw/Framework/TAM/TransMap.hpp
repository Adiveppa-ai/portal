#ifndef TAM_TRANSMAP_HPP
#define TAM_TRANSMAP_HPP

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
//   Transaction map class implementation.
//
// Open Points:
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: TransMap.hpp,v $
// $Revision: 1.6 $
// $Author: mliebmann $
// $Date: 2001/08/10 08:51:54 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// Revision 1.7  2005/09/19 08:51:54  psagar
// PRSF00180923 Abort requested due to unavailability to write binary log file
//
// Revision 1.6  2001/08/10 08:51:54  mliebmann
// PETS #37618 code reviewed
//
// Revision 1.5  2001/05/11 16:25:01  bt
// Error handling for methods binaryRestore() and binarySave() changed.
//
// Revision 1.4  2001/04/19 17:20:23  bt
// Mutex lock removed.
//
// Revision 1.3  2001/04/18 13:54:48  bt
// Default constructor added.
//
// Revision 1.2  2001/04/06 09:13:35  bt
// Methods binaryRestore() and binarySave() changed.
//
// Revision 1.1  2001/04/05 13:49:06  bt
// Initial version.
//
//==============================================================================

#if !defined TAM_EXPORT
  #if defined(WINDOWS)
    #if !defined(TAM_INTERNAL)
      #define TAM_EXPORT __declspec(dllimport)
    #else
      #define TAM_EXPORT __declspec(dllexport)
    #endif
  #else
    #define TAM_EXPORT 
  #endif
#endif

#ifndef   RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif

#ifndef   TAM_TRANSACTION_HPP
  #include "TAM/Transaction.hpp"
#endif

namespace TAM
{
/** This class represents a collection of transaction objects.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: TransMap.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.6 $</font></td>
    <td><font size=-1>$Date: 2001/08/10 08:51:54 $</font></td>
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
class TransMap D_THREADINFO
{
  public:

    typedef RWTPtrMap< TransId,
                       Transaction,
                       less<TransId> > transMapImpl;
    typedef transMapImpl::const_iterator   ConstIterator;
    typedef transMapImpl::iterator         Iterator;

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      TransMap();

      /** Constructs an empty transaction map.
        * @param fileName The file name used for save and restore. */
      TransMap(const BAS::String& fileName);

    //@}

    /**@name Public Destructor */
    //@{

      /// Destructor.
      ~TransMap();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Returns an iterator positioned at the first entry in self.
      Iterator begin();

      /// Returns an iterator positioned at the first entry in self.
      ConstIterator begin() const;

      /// Returns an iterator positioned "just past" the last entry in self.
      Iterator end();

      /// Returns an iterator positioned "just past" the last entry in self.
      ConstIterator end() const;

      /// Returns the number of entries in self.
      size_t entries() const;

      /** Removes all entries from the map.<br>
        * Uses operator delete to destroy the associated objects. */
      void clearAndDestroy();

      /// Returns the file name used for save and restore.
      const BAS::String& storeFileName() const;

      /// Set the file name used for save and restore.
      void storeFileName(const BAS::String& fileName);

      /** Adds transaction id with associated transaction to the map.
        * @param id The transaction id.
        * @param ta The transaction object.
        * @return <tt>true</tt> transaction was successfully added,<br>
        *         <tt>false</tt> otherwise. */
      bool insert(TransId* id, Transaction* ta);

      /** Access by transaction id.
        * @param id The transaction id of the desired entry.
        * @return Pointer to the transaction or 0 if not found. */
      Transaction* findValue(const TransId* id);

      /** Access by transaction id.
        * @param id The transaction id of the desired entry.
        * @return Pointer to the transaction or 0 if not found. */
      const Transaction* findValue(const TransId* id) const;

      /** Removes the entry with the given transaction id.<br>
        * Uses operator delete to destroy the associated objects.
        * @param id The transaction id of the entry.
        * @return <tt>true</tt> transaction was successfully removed,<br>
        *         <tt>false</tt> otherwise. */
      bool remove(const TransId* id);

      /** Restore the internal representation of self from a file.
        * @param errorMessage The error message in case of error.
        * @return <tt>true</tt> self was successfully restored,<br>
        *         <tt>false</tt> otherwise. */
      bool binaryRestore(BAS::String& errorMessage);

      /** Save the internal representation of self to a file.
        * @param errorMessage The error message in case of error.
        * @return <tt>true</tt> self was successfully saved,<br>
        *         <tt>false</tt> otherwise. */
      bool binarySave(BAS::String& errorMessage, BAS::StringList& errorList);

	  /**  Returns the number of bytes necessary to store self.
	   */
      u_int64 binaryStoreSize();


	/** Delete the transaction file
	 * Used during uninstall to cleanup any outstanding transactions
	 */
	bool removePersistedState();
    //@}

    /**@name Related Global Operators */
    //@{

      /** Output operator.
        * @param os The output stream.
        * @param tm The transaction map to be written to the stream. */
      friend std::ostream& operator<<(std::ostream& os, const TransMap& tm);

    //@}

  private:

    // The following private attributes and functions are used internally.

      transMapImpl transMapM;

      BAS::String storeFileNameM;
      BAS::String tempFileNameM;   //used when writing out the binary log file

      u_int64 storeBufferSizeM;

      char* storeBufferPtrM;

    // Class members.

      TAM_EXPORT static const u_int64 beginMarkerCM;

      TAM_EXPORT static const u_int64 endMarkerCM;

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      TransMap(TransMap& right);

      const TransMap& operator=(TransMap& right);

    // Allocates the store buffer with the given size.

      void allocateStoreBuffer(u_int64 storeSize);

    // Deallocates the store buffer.

      void deallocateStoreBuffer();

};

//------------------------------------------------------------------------------
// Returns an iterator positioned at the first entry in self.
//------------------------------------------------------------------------------

inline TransMap::Iterator
TransMap::begin()
{
  return transMapM.begin();
}

//------------------------------------------------------------------------------
// Returns an iterator positioned at the first entry in self.
//------------------------------------------------------------------------------

inline TransMap::ConstIterator
TransMap::begin() const
{
  return transMapM.begin();
}

//------------------------------------------------------------------------------
// Returns an iterator positioned "just past" the last entry in self.
//------------------------------------------------------------------------------

inline TransMap::Iterator
TransMap::end()
{
  return transMapM.end();
}

//------------------------------------------------------------------------------
// Returns an iterator positioned "just past" the last entry in self.
//------------------------------------------------------------------------------

inline TransMap::ConstIterator
TransMap::end() const
{
  return transMapM.end();
}

//------------------------------------------------------------------------------
// Returns the number of entries in self
//------------------------------------------------------------------------------

inline size_t
TransMap::entries() const
{
  return transMapM.entries();
}

//------------------------------------------------------------------------------
// Removes all entries from the map
//------------------------------------------------------------------------------

inline void
TransMap::clearAndDestroy()
{
  transMapM.clearAndDestroy();
}

//------------------------------------------------------------------------------
// Returns the file name used for save and restore
//------------------------------------------------------------------------------

inline const BAS::String&
TransMap::storeFileName() const
{
  return storeFileNameM;
}

//------------------------------------------------------------------------------
// Set the file name used for save and restore
//------------------------------------------------------------------------------

inline void
TransMap::storeFileName(const BAS::String& fileName)
{
  storeFileNameM = fileName;
  tempFileNameM = fileName + ".temp";
}

//------------------------------------------------------------------------------
// Adds transaction id with associated transaction to the map
//------------------------------------------------------------------------------

inline bool
TransMap::insert(TransId* id, Transaction* ta)
{
  return transMapM.insert(id,ta);
}

//------------------------------------------------------------------------------
// Access by transaction id
//------------------------------------------------------------------------------

inline Transaction*
TransMap::findValue(const TransId* id)
{
  return transMapM.findValue(id);
}

//------------------------------------------------------------------------------
// Access by transaction id
//------------------------------------------------------------------------------

inline const Transaction*
TransMap::findValue(const TransId* id) const
{
  return transMapM.findValue(id);
}

//------------------------------------------------------------------------------
// Output operator
//------------------------------------------------------------------------------

std::ostream&
operator<<(std::ostream& os, const TransMap& tm);
}
#endif // TRANSMAP_HPP

