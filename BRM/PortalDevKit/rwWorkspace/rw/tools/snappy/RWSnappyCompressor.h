#ifndef rw_tools_snappy_RWSnappyCompressor_h__
#define rw_tools_snappy_RWSnappyCompressor_h__


/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/tools/snappy/RWSnappyCompressor.h#1 $
 *
 * Copyright (c) 1989-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 *************************************************************************/

/**************************************************************************
 *
 * Description:
 *
 * Compressor that uses the Google Snappy compression library.
 *
 *************************************************************************/

#include <rw/tools/snappy/pkgdefs.h>
#include <rw/typedefs.h> // for rwuint32

/**
 * \ingroup snappy_module
 *
 * \brief
 * Compressor adapter that compresses and decompresses data using the Google
 * Snappy compression library.
 *
 * Compressor adapter for compressing and decompressing data using the
 * Google Snappy compression library.
 */
class RW_SNAPPY_SYMBOLIC RWSnappyCompressor
{
public:

    /**
     * Initialize the compressor.
     */
    RWSnappyCompressor();

    /**
     * Compresses \a uncompressed_length bytes of data from \a uncompressed
     * into \a compressed and stores the number of compressed bytes in
     * \a compressed_length.
     *
     * Returns -1 if \a compressed_length is not of sufficient size to store
     * the compressed data.
     */
    int compress(void* compressed, rwuint32& compressed_length,
                 const void* uncompressed, rwuint32 uncompressed_length);

    /**
     * Decompress \a compressed_length bytes of data from \a compressed and
     * place it into \a uncompressed, and stores the number of uncompressed
     * bytes to \a uncompressed_length on success.
     *
     * Returns -1 if \a uncompressed_length is not of sufficient size to
     * store the decompressed data or if \a compressed refers to data that
     * could not be decompressed.
     */
    int decompress(void* uncompressed, rwuint32& uncompressed_length,
                   const void* compressed, rwuint32 compressed_length);

    /**
     * Calculates the number of bytes needed to store an uncompressed byte
     * array given \a compressed_length bytes of compressed data stored in
     * \a compressed. Stores the result in \a uncompressed_length.
     *
     * Returns -1 to indicate that the compressed data stream was invalid.
     */
    int uncompressed_length(const void* compressed, rwuint32 compressed_length,
                            rwuint32& uncompressed_length);

    /**
     * Calculates the maximum number of bytes needed to store a compressed
     * byte array given \a uncompressed_length bytes of uncompressed data.
     * Stores the result in \a compressed_length.
     *
     * Returns 0 on success.
     */
    int max_compressed_length(rwuint32 uncompressed_length, rwuint32& compressed_length);
};

#endif // rw_tools_snappy_RWSnappyCompressor_h__
