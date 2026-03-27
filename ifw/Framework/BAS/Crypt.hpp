#ifndef BAS_CRYPT_HPP
#define BAS_CRYPT_HPP
//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates.
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//
//------------------------------------------------------------------------------
// Module Description:
//   Crypt encryption and decryption class implementation.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: Crypt.hpp $
// $Revision: /cgbubrm_mainbrm.portalbase/1 $
// $Author: subange $
// $Date: 2017/05/26 07:37:30 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: Crypt.h,v $
//
// Revision 2  2006/01/20 nmanchal 
// PRSF00191010 "ECR_PCI: To deliver 3rd party AES library code and DM changes"
//
// Revision 1.4  2005/03/02  skalita
// PRSF00034502  "Use integrate's password encryption mechanism for database passwords in dm_oracle"
//
// Revision 1.3  2000/06/15 12:17:52  bt
// Changes for AIX xlC V366.
//
// Revision 1.2  1999/11/10 09:04:33  clohmann
// CodeReview - 10.1999 - clohmann
//
// Revision 1.1  1999/07/01 09:58:51  bt
// Initial version.
//
//==============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#ifndef _pin_sys_h_
  #include "pin_sys.h"
#endif

#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace BAS {

extern "C" PIN_EXPORT int decrypt_pass(const char *const, const char *const,char*,const bool toUpperCase = true );


/** This class provides encryption and decryption methods.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Crypt.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_mainbrm.portalbase/1 $</font></td>
    <td><font size=-1>$Date: 2017/05/26 07:37:30 $</font></td>
    <td><font size=-1>$Author: subange $</font></td>
    </tr>
    </table>

    <p> The plain password is encrypted to a cipher password
        with a hexadecimal format and a length of 40 characters.
        <dl>
        <dt>The following applies to user name and plain password.</dt>
        <dd>Only 7-bit ASCII characters are allowed.</dd>
        <dd>Only the first eighteen characters are used.</dd>
        <dd>All lower-case characters are converted to upper-case
            (This default can be changed).</dd>
        </dl>

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

class Crypt D_THREADINFO
{
  public:

    /**@name Public Constructors */
    //@{

      /// Default constructor.
      Crypt();

    //@}

    /**@name Public Destructor */
    //@{

      /// Destructor.
      ~Crypt();

    //@}

    /**@name Static Public Member Functions */
    //@{

      /** Decrypt the given user name, cipher password string
        * and generate the plain password string. Only the first
        * eighteen characters of the user name are used.
        * If toUpperCase is true, all lower-case user name
        * characters are converted to upper-case (default).
        * @param userName The user name string (length <= 18).
        * @param cipherPW The cipher password string (length = 40).
        * @param plainPW The plain password return string (length <= 18).
        * @param toUpperCase If true, convert lower-case to upper-case.
        * @return <tt>true</tt> In case of success,<br>
        *         <tt>false</tt> otherwise. */
      static bool decrypt(const String& userName,
                          const String& cipherPW,
                          String& plainPW,
                          const bool toUpperCase = true,
			  const bool useAes = true);

      /** Encrypt the given user name, plain password string
        * and generate the cipher password string with a length
        * of 40. If the input parameters are empty, an default
        * string is generated. Only the first eighteen characters
        * of the user name and plain password string are used.
        * If toUpperCase is true, all lower-case user name and plain
        * password characters are converted to upper-case (default).
        * @param userName The user name string (length <= 18).
        * @param plainPW The plain password string (length <= 18).
        * @param cipherPW The cipher password return string (length = 40).
        * @param toUpperCase If true, convert lower-case to upper-case.
        * @return <tt>true</tt> In case of success,<br>
        *         <tt>false</tt> otherwise. */
      static bool encrypt(const String& userName,
                          const String& plainPW,
                          String& cipherPW,
                          const bool toUpperCase = true,
			  const bool useAes = true);

	static bool get_conf_entry(String& confkey,
			String& valuep);

      static bool selfTest();

    //@}

  private:

    // The following private attributes and functions are used internally.

    // reads the conf entry from wallet.
    // returns 0 is success, -1 otherwise.
   
	int c_get_conf(char* confkey, char** valuep); 
    // Encryption or decryption of a single character value.
    // Returns the encrypted or decrypted value, -1 otherwise.

      int c_crypt (const int value, const int pos);

    // Use AES mechanism
    // Decryption of the cipher password string.
    // Returns 0 in case of success, -1 otherwise.

      int c_decrypt (const char *uname, const char *cipher, char **plain);

    // Use AES mechanism
    // Encryption of the plain password string.
    // Returns 0 in case of success, -1 otherwise.

      int c_encrypt (const char *uname, const char *plain, char **cipher);

     // Use ZT implementation of AES mechanism
     // Encryption of the plain password string.
     // Returns 0 in case of success, -1 otherwise.

     int c_encrypt_zt (const char *uname, const char *plain, char **cipher);


    // Use Legacy encryption mechanism
    // Decryption of the cipher password string.
    // Returns 0 in case of success, -1 otherwise.

      int c_decrypt_nonaes (const char *uname, const char *cipher, char *plain);

    // Use Legacy encryption mechanism
    // Encryption of the plain password string.
    // Returns 0 in case of success, -1 otherwise.

      int c_encrypt_nonaes (const char *uname, const char *plain, char *cipher);

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      Crypt(Crypt& right);

      const Crypt& operator=(Crypt& right);

};
}
#endif // CRYPT_HPP

