#ifndef STR_BASICSTREAM_HPP
#define STR_BASICSTREAM_HPP
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: STR
//------------------------------------------------------------------------------
// Module Description:
//   Basic stream class implementation.
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
// $RCSfile: STR_BasicStream.hpp,v $
// $Revision: 1.3 $
// $Author: mliebmann $
// $Date: 2001/09/03 12:35:57 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: STR_BasicStream.hpp,v $
// Revision 1.3  2001/09/03 12:35:57  mliebmann
// PETS #37618 code review implemented
//
// Revision 1.2  2001/08/28 07:04:45  jkeckst
// PETS 37618 code review cr-08.2001
//
// Revision 1.1  2000/08/24 11:10:44  rmurawsk
// STR splitted into STR_Base and STR
//
// Revision 1.19  2000/08/09 13:50:06  aro
// Preparation for v4-06-00.
//
// Revision 1.18  2000/08/09 13:24:20  aro
// Diamond-shape inheritance for STR_InputFileIf removed.
//
// Revision 1.17  2000/08/07 14:04:28  kb
// new class STR_InputStreamIf embedded
//
// Revision 1.16  1999/11/09 12:27:11  clohmann
// Checked all CodeReview remarks.
//
// Revision 1.15  1999/11/08 08:19:58  jkeckst
// code review
//
// Revision 1.14  1999/03/31 09:37:02  arockel
// STR_InputFile move functionality added.
//
// Revision 1.12  1999/03/30 12:45:27  arockel
// Online doc improved.
//
// Revision 1.10  1999/03/30 12:26:13  arockel
// STR_InputFile and BAS_Directory improved.
//
// Revision 1.8  1999/03/29 10:51:55  arockel
// Remaining STR classes added, BAS_Directory improved.
//
// Revision 1.4  1999/03/22 11:51:05  arockel
// STR_Collection added.
//
// Revision 1.3  1999/03/22 07:32:24  arockel
// STR_BasicStream derived from BAS_RegisteredObject.
//==============================================================================

#ifndef   RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h> 
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif

/** <tt><b>BasicStream</b></tt> is the base class for all stream templates.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: BasicStream.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.3 $</font></td>
    <td><font size=-1>$Date: 2001/09/03 12:35:57 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>                

    <dl>
    <dt><b>Registry entries</b></dt>
         <dd>none
    <dt><b>Messages send</b></dt>
         <dd>none
    <dt><b>Messages receive</b></dt>
         <dd>none
    <dt><b>Errors</b></dt>
         <dd>none
    </dl>

    This is the basic stream class for the integRate framework. This class
    provides the interface for the input and output stream classes. Every specialized
    stream must be derivered from this class.

*/
namespace STR {
template <class T> class BasicStream : public BAS::RegisteredObject
{
  public:

    /**@name BasicStream constructors and destructor. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    BasicStream();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name Name of the registered object.
    */
    BasicStream(const BAS::String& name);

    /** Destructor. 
    */
    virtual ~BasicStream();
    //@}

    /**@name BasicStream stream functions. */
    //@{
    /// Read from the stream
    virtual bool read(T& val,bool block=true);

    /// Write into the Stream
    virtual bool write(const T& val);

    /// Open Stream
    virtual bool open();

    /// Close Stream
    virtual bool close();

    /** Stream name. Note: This is not the registered instance name.
        @return The current internal name of the stream, 
                 e.g. the system file name.
    */
    const BAS::String& streamName() const;

    /** Check for end of stream.
        @return <tt>True</tt> if the stream is ended,<br>
                <tt>false</tt> otherwise.
    */
    virtual bool eos();  /* const */
    //@}

  protected:
     /** Set the internal name of the stream.
         This method shall only be used by subclasses.
         @param name The new internal name of the stream.
     */
     void streamName(const BAS::String& name);

  private:
    // data member(s)
    BAS::String streamNameM;
};


//======================================================================
// inline
//======================================================================

//======================================================================
// read from stream
//======================================================================
template <class T>
inline bool BasicStream<T>::read(T& val,bool block)
{
  return true;
}

//======================================================================
// write into stream
//======================================================================
template <class T>
inline bool BasicStream<T>::write(const T& val)
{
  return true;
}

//======================================================================
// open stream
//======================================================================
template <class T>
inline bool BasicStream<T>::open()
{
  return true;
}

//======================================================================
// close stream
//======================================================================
template <class T>
inline bool BasicStream<T>::close()
{
  return true;
}

//------------------------------------------------------------------------------

template <class T>
inline bool BasicStream<T>::eos()
{
  // Always return true for the abstract class
  return true;
}

//------------------------------------------------------------------------------

template <class T> inline const BAS::String&
BasicStream<T>::streamName() const
{
  return streamNameM;
}
                  
//------------------------------------------------------------------------------

template <class T> inline void
BasicStream<T>::streamName(const BAS::String& name)
{
  streamNameM = name;
}           

//------------------------------------------------------------------------------
}

#ifdef INC_TEMPL_DEFS
  #include "BasicStream.cpp"
#endif

//------------------------------------------------------------------------------
#endif // BASICSTREAM_HPP
