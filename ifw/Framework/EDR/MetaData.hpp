/*
 *      @(#)%Portal Version: MetaData.hpp:Pipeline7.3ModularInt:1:2007-Mar-08 16:24:56 %
 *
 *	Copyright (c) 1996 - 2007 Oracle. All rights reserved.
 *	
 *	This material is the confidential property of Oracle Corporation or its
 *	licensors and may be used, reproduced, stored or transmitted only in
 *	accordance with a valid Oracle license or sublicense agreement.
 */
#ifndef EDR_METADATA_H
#define EDR_METADATA_H

#ifndef WIN32
  #ifndef __aix
  /* Don't include this on AIX because it defines _STD which interferes with RogueWave */
  #include <cstddef>
  #endif
#include <inttypes.h>
#endif

#include <sys/types.h>
#include <netinet/in.h>
#ifdef __hpux
#include <sys/byteorder.h>
#endif

#ifndef   _PIN_TYPE_H_
  #include "pin_type.h"
#endif

namespace EDR
{

	/*
	 * The format is:
	 * int32 containg type+flags in bottom 4 bytes, flags in upper 2
	 * int32 containing field name
	 * int32 containing record id
	 * value:
	 *  string is long for length followed by string (not null terminated!)
	 *     0x80000000 indicates NULL
	 *  decimal is 
	 *     int32 (0)
	 *     int32 (flag)
	 *     int32 (signum)
	 *     int32 (scale)
	 *     decimal data (text string, as string)
	 *  buf is 
	 *     int32 (length = 0 for null)
	 *     int32 (flag)
	 *     int32 (size)
	 *     int32 (offset)
	 *     char *data for BUF
	 *     char *xbuf for XBUF
	 *  binstr is 
	 *     int32 (length = 0 for null)
	 *     int32 (size)
	 *     char *data for binstr
	 */

	struct FldHdr {
		int16 flags;
		int16 type;
		int32 name;
		int32 rec_id;
	};
	struct Str {
		int32 length;
		char data[1];
	};

	struct Dec {
		int32 isNull;
		int32 flag;
		int32 signum;
		int32 scale;
		Str val;
	};

	struct Buf {
		int32       length;       /* 0 for null */
		int32       flag;       /* if XBUF, ... */
		int32       size;       /* size of data */
		int32       offset;     /* offset (for read) */
		Str data; /* data for BUF */
		Str xbuf_file; /* XBUF */
	};

	struct BinStr {
		int32 length; /* 0 for null */
		Str data; /* data for Binstr */
	};

#if defined(sparc) || defined(x86_64)
#pragma pack (4)
#else
#if defined(__hp9000s800)
#pragma pack 4
#endif
#endif

	// This is the serialized flist data format

	struct Poid {
		int32 isNull;
		u_int32 database[2];
		u_int32 id[2];
		Str val;
	};


	// This is the storage form for CompactPoid without Db

	struct StoragePoidNoDb {
		int32 isNull;
		u_int32 id[2];
		u_int16 poidTypeNum;
		u_int16 pad;
		int32 revision;
	};

	// This is the storage form for CompactPoid with Db

	struct StoragePoidWithDb {
		int32 isNull;
		u_int32 id[2];
		u_int16 poidTypeNum;
		u_int16 pad;
		int32 revision;
		u_int32 database[2];
	};
    /*
     * First 11 fields encoded by pcm for Ebuf
     * These are location, pin_errclass, pin_err, field, rec_id, reserved,
     * facility, msg_id, err_time_sec, err_time_usec, version
     * This blob is followed by a list of 0 or more field information
     * which then ends with another int32 field for reserved2
     */

    struct EbufData {
        int32 TopFlds[11];
    };


#if defined(sparc) || defined(x86_64)
#pragma pack()
#else
#if defined(__hp9000s800)
#pragma pack
#endif
#endif
    /**
     * Class to represent the meta data about an object that is needed when
     * serializing something to an flist. Each EDR::Value object will contain
     * one of these
     */
	class MetaData  D_THREADINFO
    {
  	D_SINGLETHREADED

    public:
        typedef char MetaDataBuffer[24];
        MetaData(const size_t length);

        MetaData(const size_t length, const short dataType);

        void setLength(const size_t length);
        void setBuffer(const MetaDataBuffer& m);
        void setFieldLength(const size_t length);

        const size_t getLength() const;
        const size_t getFieldLength() const;
        void setPinType(const short type);
		const short getPinType() const;
	
        const MetaDataBuffer& getBuffer() const;
        void setLongValue(const int32 val, const size_t offset);

    private:
        size_t lengthM;
        size_t fieldLengthM;
        // This is the maximum currently. It might change
        MetaDataBuffer metaDataM;
    };

	inline MetaData::MetaData(const size_t length) : lengthM(length), fieldLengthM(0)
    {
    }

    inline MetaData::MetaData(const size_t length, const short dataType) 
            : lengthM(length), fieldLengthM(0)
    {
        memset(&metaDataM, 0, sizeof(metaDataM));
        setPinType(dataType);
    }

    inline void
    MetaData::setLength(const size_t length)
    {
        lengthM = length;
    }
    
    inline void 
    MetaData::setBuffer(const MetaDataBuffer& m)
    {
        memcpy(metaDataM, &m, lengthM);
    }

    inline const size_t 
    MetaData::getLength()  const
    {
        return lengthM;
    }

    inline const MetaData::MetaDataBuffer&
    MetaData::getBuffer() const
    {
        return metaDataM;
    }

    inline void
    MetaData::setPinType(const short type)
    {
        *(u_int16 *)&(((char *)&metaDataM)[2]) = (u_int16)(htons(type));
    }

    inline const short
    MetaData::getPinType() const
    {
        return ntohs(*(u_int16 *)&(((char *)&metaDataM)[2]));
    }
    
    inline void
    MetaData::setLongValue(const int32 val, const size_t offset)
    {
        *(int32 *)&(((char *)&metaDataM)[offset]) = (int32)(htonl(val));
    }
    
    inline const size_t
    MetaData::getFieldLength() const
    {
        return fieldLengthM;
    }

    inline void
    MetaData::setFieldLength(const size_t fieldLength) 
    {
        fieldLengthM = fieldLength;
    }
}
#endif
