#ifndef EDR_BYTEBUFFER_HPP
#define EDR_BYTEBUFFER_HPP
//==============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Base
//------------------------------------------------------------------------------
// Module Description:
//   Declaratioin of a byte buffer class the automaticaly growth, when the 
//   number of inserted bytes exceeds the buffer size.
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: ByteBuffer.hpp,v $
// $Revision: 1.4 $
// $Author: cdiab $
// $Date: 2001/09/28 12:01:47 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ByteBuffer.hpp,v $
// Log 200/09/02 cdiab
// PRSF00019502: added the capacity() methode to access the nb of bytes
// allocated by the object
//
// Revision 1.4  2001/09/28 12:01:47  cdiab
// PETS #39832: optimize read/write of Hex Strings in Tap3
// now using an instance member ByteBuffer to optimize the conversion.
//
// Revision 1.3  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.2  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.1  2001/03/20 15:01:32  sd
// - ByteBuffer introduced
//
//==============================================================================

#if !defined EDR_EXPORT
  #if defined(WINDOWS)
    #if !defined(EDR_INTERNAL)
      #define EDR_EXPORT __declspec(dllimport)
    #else
      #define EDR_EXPORT __declspec(dllexport)
    #endif
  #else
    #define EDR_EXPORT 
  #endif
#endif

#include <string.h>
namespace EDR
{
/** <b><tt>ByteBuffer</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ByteBuffer.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/28 12:01:47 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class ByteBuffer D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name ByteBuffer constructors and destructor */
    //@{

    /** Constructor
     *  @param initialSize The initial size of the buffer
     *                     Changed from 1024 to 0 to reduce startup memory
     */
    ByteBuffer( size_t initialSize = 0 );

    /** Destructor
     */
    ~ByteBuffer();

    /** Copy Constructor
     *  @param source ByteBuffer
     */
    ByteBuffer( const ByteBuffer& sourceByteBuffer);

    /** Copy Constructor
     *  @param source ByteBuffer
     */
	ByteBuffer& operator=(const ByteBuffer& sourceByteBuffer);

    //@}


    /**@name ByteBuffer public methods */
    //@{

    /** Clear the byte buffer
     */
    void clear();

    /** Get the number of used bytes inside the buffer
     *  @return The number of used bytes
     */
    size_t used() const;

    /** Get the number of allocated bytes inside the buffer
     *  @return The number of allocated bytes
     */
    size_t capacity() const;

    /** Get the pointer to the start of the internal byte buffer
     *  @return Pointer to start of the internal byte buffer
     */
    const char* data() const;

    /** Append a single byte to the buffer
     *  @param byte The byte to append
     */
    void append( char byte );

    /** Append a number of single bytes to the buffer
     *  @param byte The byte to append
     */
    void append( char byte, size_t numBytes );

    /** Append a number of bytes to the buffer
     *  @param bytes Pointer to the byte buffer
     *  @param numBytes Number of bytes to append
     */
    void append( const void* bytes, size_t numBytes );

    /** Get the pointer to the next n bytes. The user of this function has to
     *  initialize these bytes. The current pointer of the ByteBuffer is
     *  moved behind this buffer.
     *  @param numBytes Number of bytes needed
     *  @return Pointer to buffer with numBytes
     */
// CodeReview - 08.2001 - mwriedt - C - logical const method?
    char* next( size_t numBytes );

    /** Remove the last n characters
     *  @param n The number of bytes to remove
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool removeLast( size_t n );

    /** Change the value used to increment the size of the buffer
     *  @param The number of supplementary bytes when making the buffer grow
     */
    void setIncrement( size_t numBytes );

    //@}

  protected:
    void grow( size_t newSize );

  private:
    // Instance members
    char*  dataM;
    size_t usedM;
    size_t capacityM;
    size_t incrementM;

    // Class members
    EDR_EXPORT static size_t defaultIncrementCM;
};

//==============================================================================
// Clear the byte buffer
//==============================================================================
inline void
ByteBuffer::clear()
{
  usedM = 0;
}


//==============================================================================
// Get number of bytes used
//==============================================================================
inline size_t 
ByteBuffer::used() const
{
  return usedM;
}

//==============================================================================
// Get number of bytes allocated (usefull for memory usage checks)
//==============================================================================
inline size_t 
ByteBuffer::capacity() const
{
  return capacityM;
}
//==============================================================================
// Get the pointer to the internal byte buffer
//==============================================================================
inline const char*
ByteBuffer::data() const
{
  return dataM;
}

//==============================================================================
// Append a single character to the buffer
//==============================================================================
inline void
ByteBuffer::append( char byte )
{
  if ( usedM == capacityM )
  {
    grow( capacityM + incrementM + 1 );
  }

  RWASSERT( capacityM >= usedM+1 );
  dataM[usedM++] = byte;
}

//==============================================================================
// Append a number of characters to the buffer
//==============================================================================
inline void
ByteBuffer::append( const void* bytes, size_t numBytes )
{
  if ( usedM + numBytes > capacityM )
  {
    grow( usedM + incrementM + numBytes );
  }

  RWASSERT( capacityM >= usedM+numBytes );
  memcpy( dataM+usedM, bytes, numBytes );
  usedM += numBytes;
}

//==============================================================================
// Append a single byte n-times to the buffer
//==============================================================================
inline void
ByteBuffer::append( char byte, size_t numBytes )
{
  if ( usedM + numBytes > capacityM )
  {
    grow( usedM + incrementM + numBytes );
  }

  RWASSERT( capacityM >= usedM+numBytes );
  memset( dataM+usedM, byte, numBytes );
  usedM += numBytes;
}

//==============================================================================
// Get pointer to the next n bytes
//==============================================================================
inline char*
ByteBuffer::next( size_t numBytes )
{
  if ( usedM + numBytes > capacityM )
  {
    grow( usedM + incrementM + numBytes );
  }

  RWASSERT( capacityM >= usedM+numBytes );
  char* ret = dataM + usedM;
  usedM += numBytes;

  return ret;
}

//==============================================================================
// Remove the last n bytes
//==============================================================================
inline bool
ByteBuffer::removeLast( size_t n )
{
  if ( n > usedM )
  {
    return false;
  }

  usedM -= n;
  return true;
}

//==============================================================================
// Change the value used to increment the size of the buffer
//==============================================================================
inline void
ByteBuffer::setIncrement( size_t numBytes )
{
  incrementM = numBytes;
}
}
#endif // BYTEBUFFER_HPP
