#ifndef OBJECT_STREAM_HPP
#define OBJECT_STREAM_HPP
//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: STR
//------------------------------------------------------------------------------
// Module Description:
//   Object stream class implementation.
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
// $RCSfile: STR_ObjectStream.hpp,v $
// $Revision: 1.3 $
// $Author: mliebmann $
// $Date: 2001/09/03 12:35:57 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: STR_ObjectStream.hpp,v $
// Revision 1.3  2001/09/03 12:35:57  mliebmann
// PETS #37618 code review implemented
//
// Revision 1.2  2001/08/28 07:04:45  jkeckst
// PETS 37618 code review cr-08.2001
//
// Revision 1.1  2000/08/24 11:10:45  rmurawsk
// STR splitted into STR_Base and STR
//
// Revision 1.11  1999/11/09 12:27:11  clohmann
// Checked all CodeReview remarks.
//
// Revision 1.10  1999/11/08 08:19:58  jkeckst
// code review
//
// Revision 1.9  1999/03/30 12:50:17  arockel
// *** empty log message ***
//
// Revision 1.8  1999/03/30 12:45:33  arockel
// Online doc improved.
//
// Revision 1.7  1999/03/30 12:26:24  arockel
// STR_InputFile and BAS_Directory improved.
//
// Revision 1.6  1999/03/29 10:51:59  arockel
// Remaining STR classes added, BAS_Directory improved.
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   STR_BASICSTREAM_HPP
  #include "STR/BasicStream.hpp"
#endif

/** <tt><b>STR_ObjectStream</b></tt>.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: STR_ObjectStream.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.3 $</font></td>
    <td><font size=-1>$Date: 2001/09/03 12:35:57 $</font></td>
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
    This is the base class for all object streams. An object stream is used to write the
    completete object (not only its content) into a stream.
*/
namespace  STR {
template <class T>
class ObjectStream: public BasicStream<T>
{
  public:
    /**@name Constructors and destructor. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    ObjectStream();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name Name of the registered object.
    */
    ObjectStream(const BAS::String& name);

    /** Destructor. */
    virtual ~ObjectStream();
    //@}


  protected:

  private:

};
}
#ifdef INC_TEMPL_DEFS
  #include "ObjectStream.cpp"
#endif

#endif // OBJECT_STREAM_HPP
