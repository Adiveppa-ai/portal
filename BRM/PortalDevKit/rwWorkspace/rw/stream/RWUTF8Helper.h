#ifndef rw_stream_RWUTF8Helper_h_
#define rw_stream_RWUTF8Helper_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWUTF8Helper.h#1 $
 *
 * Copyright (c) 1996-2016 Rogue Wave Software, Inc.  All Rights Reserved.
 * 
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software, Inc.
 * pursuant to a written license agreement and may be used, copied, transmitted,
 * and stored only in accordance with the terms of such license agreement and
 * with the inclusion of the above copyright notice.  This computer software or
 * any other copies thereof may not be provided or otherwise made available to
 * any other person.
 * 
 * U.S. Government Restricted Rights.  This computer software: (a) was
 * developed at private expense and is in all respects the proprietary
 * information of Rogue Wave Software, Inc.; (b) was not developed with
 * government funds; (c) is a trade secret of Rogue Wave Software, Inc. for all
 * purposes of the Freedom of Information Act; and (d) is a commercial item and
 * thus, pursuant to Section 12.212 of the Federal Acquisition Regulations (FAR)
 * and DFAR Supplement Section 227.7202, Government's use, duplication or
 * disclosure of the computer software is subject to the restrictions set forth
 * by Rogue Wave Software, Inc.
 *
 ********************************************************************/

#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 * \class RWUTF8Helper
 *
 * \brief
 * Provides common functionality used to encode and decode UTF-8 sequences.
 *
 * The class RWUTF8Helper provides common functionality used to encode and
 * decode UTF-8 sequences.
 */
class RW_STREAM_GLOBAL RWUTF8Helper
{

public:

    /**
     * &nbsp;
     */
    enum EncodingCategory {

        /**
         * One byte encoding form of UTF-8
         */
        oneByte = 1,

        /**
         * Two bytes encoding form of UTF-8
         */
        twoBytes,

        /**
         * Three bytes encoding form of UTF-8
         */
        threeBytes,

        /**
         * Four bytes encoding from of UTF-8
         */
        fourBytes,

        /**
         * The character to be encoded is a high surrogate
         */
        highSurrogate,

        /**
         * No low surrogate after a high surrogate
         */
        missingLowSurrogate,

        /**
         * A low surrogate was not preceded by a high surrogate
         */
        lowSurrogateWithoutHighSurrogate,

        /**
         * The encoding is not recognized as UTF-8
         */
        invalidUTF8Encoding
    };

    /**
     * Encodes the UTF-16 character \a uc according to UTF-8. The function
     * returns the UTF-8 encoding category that was used to convert the
     * UTF-16 character, or an error if the UTF-16 character could not be
     * transformed. Throws no exceptions.
     *
     * \param uc
     * The UTF-16 character to be transformed.
     *
     * \param res
     * A pointer to a byte array containing at least four bytes. The byte
     * array is used to store the transformation result.
     *
     * \param highSurrogateValue
     * This parameter is only used when a high surrogate was previously
     * encountered.
     */
    static EncodingCategory encodeOneUChar(RWUChar uc, RWByte* res, RWUChar highSurrogateValue = 0);

    /**
     * Takes the first byte of a UTF-8 byte sequence encoding a single
     * UTF-16 character, and returns the encoding category to which it
     * belongs. Throws no exceptions.
     *
     * \param b
     * The first byte of a UTF-8 byte sequence encoding a single UTF-16
     * character
     */
    static EncodingCategory decodeFirstByte(RWByte b);

    /**
     * Decodes a two-byte encoding UTF-8 sequence. The function returns
     * #invalidUTF8Encoding in case the two-byte sequence doesn't represent
     * a valid UTF-8 encoding sequence. Throws no exceptions.
     *
     * \param firstByte
     * The first byte of a UTF-8 two-byte sequence encoding a single UTF-16
     * character.
     *
     * \param secondByte
     * The second byte of a UTF-8 two-byte sequence encoding a single UTF-16
     * character.
     *
     * \param res
     * The UTF-16 character resulting from the decoding of the two-byte
     * UTF-8 sequence
     */
    static EncodingCategory decodeTwoBytesEncoding(RWByte firstByte, RWByte secondByte, RWUChar& res);

    /**
     * Decodes a three-byte encoding UTF-8 sequence. The function returns
     * #invalidUTF8Encoding if the three-byte sequence doesn't represent a
     * valid UTF-8 encoding sequence. Throws no exceptions.
     *
     * \param firstByte
     * The first byte of a UTF-8 three-byte sequence encoding a single
     * UTF-16 character.
     *
     * \param secondByte
     * The second byte of a UTF-8 three-byte sequence encoding a single
     * UTF-16 character.
     *
     * \param thirdByte
     * The third byte of a UTF-8 three-byte sequence encoding a single
     * UTF-16 character.
     *
     * \param res
     * The UTF-16 character resulting from the decoding of the three-byte
     * UTF-8 sequence
     */
    static EncodingCategory decodeThreeBytesEncoding(RWByte firstByte, RWByte secondByte,
            RWByte thirdByte, RWUChar& res);

    /**
     * Decodes a four-byte UTF-8 sequence. The function returns
     * #invalidUTF8Encoding in case the four-byte sequence doesn't represent
     * a valid UTF-8 encoding sequence. Throws no exceptions.
     *
     * \param firstByte
     * The first byte of a UTF-8 four-byte sequence encoding a single UTF-16
     * character.
     *
     * \param secondByte
     * The second byte of a UTF-8 four-byte sequence encoding a single
     * UTF-16 character.
     *
     * \param thirdByte
     * The third byte of a UTF-8 four-byte sequence encoding a single UTF-16
     * character.
     *
     * \param fourthByte
     * The fourth byte of a UTF-8 four-byte sequence encoding a single
     * UTF-16 character.
     *
     * \param highSurrogateValue
     * The UTF-16 high surrogate resulting from the decoding of the
     * four-byte UTF-8 sequence.
     *
     * \param lowSurrogateValue
     * The UTF-16 low surrogate resulting from the decoding of the four-byte
     * UTF-8 sequence.
     */
    static EncodingCategory decodeFourBytesEncoding(RWByte firstByte, RWByte secondByte,
            RWByte thirdByte, RWByte fourthByte,
            RWUChar& highSurrogateValue,
            RWUChar& lowSurrogateValue);


    // Encoding masks

    // Surrogate encoding masks
    static const RWUChar surrogateIdentificationMask;
    static const RWUChar highSurrogateLowerBound;
    static const RWUChar highSurrogateUpperBound;
    static const RWUChar highSurrogateThirdByteMask;
    static const RWUChar highSurrogateThirdByteMaskBis;
    static const RWUChar highSurrogateFirstByteMask;
    static const RWUChar highSurrogatefourthByteMask;
    static const RWUChar lowSurrogateLowerBound;
    static const RWUChar lowSurrogateUpperBound;
    static const RWUChar lowSurrogateThirdByteMask;

    // 7 bits US-ASCII mask
    static const RWUChar oneByteConversionIdentificationMask;

    // two bytes conversion masks
    static const RWUChar twoBytesConversionIdentificationMask;
    static const RWUChar twoBytesConversionLowerByteMask;
    static const RWUChar twoBytesConversionLowerByteCodeMask;
    static const RWUChar twoBytesConversionHigherByteMask;
    static const RWUChar twoBytesConversionHigherByteCodeMask;

    // three bytes conversion mask
    static const RWUChar threeBytesConversionHigherByteCodeMask;

    // Decoding masks
    static const RWByte firstByteOneByteEncodingIdentificationMask;
    static const RWByte firstByteTwoBytesEncodingIdentificationMask;
    static const RWByte firstByteThreeBytesEncodingIdentificationMask;
    static const RWByte firstByteFourBytesEncodingIdentificationMask;

    static const RWByte firstByteTwoBytesEncodingMask;
    static const RWByte firstByteThreeBytesEncodingMask;
    static const RWByte firstByteFourBytesEncodingMask;

    static const RWByte firstByteTwoBytesEncodingValueMask;
    static const RWByte secondByteTwoBytesEncodingValueMask;

    static const RWByte firstByteThreeBytesEncodingValueMask;

    static const RWByte firstByteFourBytesEncodingValueMask;
    static const RWByte secondByteFourBytesEncodingValueMask;

};

#endif // rw_stream_RWUTF8Helper_h_
