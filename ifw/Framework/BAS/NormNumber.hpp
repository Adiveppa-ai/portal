#ifndef NORM_NUMBER_HPP
#define NORM_NUMBER_HPP 
//==============================================================================
//
// 1998,1999 (c) Copyright by solution42 - IT systems & consulting GmbH & Co. KG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//  Normalising Cli-Number
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Carsten Lohmann
//
// $RCSfile: NormNumber.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 04:47:21 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: NormNumber.hpp,v $
// Revision 1.5  2000/09/29 10:53:04  aro
// Tried to fix doc++ comments.
//
//
// Revision 1.3  1999/06/08 10:57:05  aro
// NormNumber.cpp
//==============================================================================

#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace BAS {
/** Default normalising function.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: NormNumber.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2015/11/27 04:47:21 $</font></td>
    <td><font size=-1>$Author: nishahan $</font></td>
    </tr>
    </table>

    <p>This class formats and normalises CLI's (Call Line Identifiers).
    This class can be used as a default (format independent) normalising function. 
    
<dl>
   <dt><b>Registry entries</b></dt>
        <dd>none</dd>
   <dt><b>Messages send</b></dt>
        <dd>none</dd>
   <dt><b>Request send</b></dt>
        <dd>none</dd>
   <dt><b>Request receive</b></dt>
        <dd>none</dd>
   <dt><b>Messages receive</b></dt>
        <dd>none</dd>
   <dt><b>Errors</b></dt>
        <dd>none</dd>
</dl>
*/
class NormNumber D_THREADINFO
{
  public    :

     /** Format type.
        This enumeration is used by the <tt>formatCli()</tt> method.
        The following values are supported:
        <ul><tt>
        <li>TRIM_SPACE_LEAD
        <li>TRIM_SPACE_TRAI
        <li>TRIM_SPACE_BOTH
        <li>TRIM_ZERO_LEAD
        <li>TRIM_ZERO_TRAI
        <li>TRIM_ZERO_BOTH
        <li>EVAL_NORM_NUMBER
        <li>CHECK_FOR_NUMBER
        </tt></ul>
    */
    enum formatType
    {
      TRIM_SPACE_LEAD        =   2,
      TRIM_SPACE_TRAI        =   4,
      TRIM_SPACE_BOTH        =   8,
      TRIM_ZERO_LEAD         =  16,
      TRIM_ZERO_TRAI         =  32,
      TRIM_ZERO_BOTH         =  64,
      EVAL_NORM_NUMBER       = 128,
      CHECK_FOR_NUMBER       = 256
    };


    /**@name Constructors and Destructors */
    //@{
    /** Default constructor.<br>
    */
    NormNumber();

    /** Standard constructor.<br>
        Creates an NormNumber object with valid cli prefix values. 
        @param NAC  National access code.
        @param IAC  International access code.
        @param CC   Country code.
        @param MCC  Mobile country code.
        @param IACS International access code sign.
    */
    NormNumber(const String& NAC
                  ,const String& IAC
                  ,const String& CC
                  ,const String& MCC
                  ,const String& IACS);
    
    /** Copy constructor.
    */
    NormNumber(const NormNumber& val);

    /** Destructor. */
    virtual ~NormNumber();
    //@}

    /**@name Cli format functions */
    //@{
    /** Format and normalize cli number.
        @parm cli   cli number
        @parm type  control flags for cli normalizing  
    */
    bool formatCli(String& cli, const int type);

    /** Normalize cli number. 
        @parm number cli number
        @parm prefix additional prfix for the number
    */
    void evalNormNumber(String& number, const String& prefix);
    //@}

    /**@name get/set */
    //@{

    /**
    */
    const String& natAccessCode() const;
    /**
    */
    const String& intAccessCode() const;
    /**
    */
    const String& countryCode() const;
    /**
    */
    const String& mobCountryCode() const;
    /**
    */
    const String& intAccessCodeSign() const;
    /**
    */
    void natAccessCode(const String& NAC);
    /**
    */
    void intAccessCode(const String& IAC);
    /**
    */
    void countryCode(const String& CC);
    /**
    */
    void mobCountryCode(const String& MCC);
    /**
    */
    void intAccessCodeSign(const String& IACS);
    //@}

  protected :

  private   :
    
    // Default, copy constructor and assign operator are not implemented. They are
    // private to prevent unintentionally use.
    const NormNumber& operator=(NormNumber& right);

    //  Cli prefix
    String natAccessCodeM;
    String intAccessCodeM;
    String countryCodeM;
    String mobCountryCodeM;
    String intAccessCodeSignM;
};

//======================================================================
// inline functions
//======================================================================
inline const String& NormNumber::natAccessCode() const
{
  return natAccessCodeM;
}

inline const String& NormNumber::intAccessCode() const
{
  return intAccessCodeM;
}

inline const String& NormNumber::countryCode() const
{
  return countryCodeM;
}

inline const String& NormNumber::mobCountryCode() const
{
  return mobCountryCodeM;
}

inline const String& NormNumber::intAccessCodeSign() const
{
  return intAccessCodeSignM;
}

inline void NormNumber::natAccessCode(const String& NAC)
{
  natAccessCodeM = NAC;
}

inline void NormNumber::intAccessCode(const String& IAC)
{
  intAccessCodeM = IAC;
}

inline void NormNumber::countryCode(const String& CC)
{
  countryCodeM = CC;
}

inline void NormNumber::mobCountryCode(const String& MCC)
{
  mobCountryCodeM = MCC;
}

inline void NormNumber::intAccessCodeSign(const String& IACS)
{
  intAccessCodeSignM = IACS;
}

}
#endif // PLG_INPUT_STREAM_PLUG_IN_HPP
