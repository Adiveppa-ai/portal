#ifndef EDR_UTILS_HPP
#define EDR_UTILS_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Utilities for EDR classes
//------------------------------------------------------------------------------
//
// Revision       1.3  2005/02/07 rtang
// PRSF00151358   Use base64 encoding for invalid string field.
//
// Revision       1.2  2004/03/12 ammon
// PRSF00099349   Correct base64ValuesCM declaration
//
// Revision       1.1  2004/03/10 ammon
// PRSF00098531   Added decodeBase64();
//
// Revision       1.0  2004/02/17 ammon
// PRSF00092698   Created.
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_BYTEBUFFER_HPP
  #include "EDR/ByteBuffer.hpp"
#endif

namespace EDR
{

/** <b><tt>Utils</tt></b> is a class for utilities used in EDR classes.
 */
class Utils D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /** Prepare a string for including in XML.
     * Replaces special characters with their escape sequence.
     * @param str String to encode.
     * @return true when use base64 to encode string with invalid character 
     */
    static bool encodeXml(BAS::String& str);

    /** Encode a binary string in Base64 format.
     * This is NOT a fully compliant Base64 encoder.
     * Encoded string doesn't contain new lines.
     * The Base64 spec requires lines to not exceed 76 characters.
     * @param str String to encode.
     */
    static void encodeBase64(BAS::String& str);

    /** Decode a binary string in Base64 format.
     * This is NOT a fully compliant Base64 decoder.
     * Decoding will fail if the encoded string contains include newlines,
     * whitespace or invalid characters.
     * The Base64 spec requires decoders to skip whitespace and invalid characters.
     * @param str String to encode.
     * @return true on success false on failure
     */
    static bool decodeBase64(BAS::String& str);

  private:
    /** get value of a Base64 character
     * @param ch Character to evaluate
     * @return Value of the Base64 character or -1 on error
     */
    static short convertBase64Char(char ch);

    // Base64 characters
    static char base64CharsCM[64];

    // Base64 pad character "="
    static char base64PadCM;

    // Map of Base64 characters to values
    static short base64ValuesCM[128];

    // Buffer used during encoding
    static ByteBuffer bufferCM;

    // bufferCM mutex
    static RWMutexLock bufferMutexCM;
};
}

#endif // EDR_UTILS_HPP
