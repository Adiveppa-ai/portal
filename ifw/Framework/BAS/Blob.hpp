#ifndef BAS_BLOB_H
#define BAS_BLOB_H
/*
 * Blob.h 
 *
 * Copyright (c) 2002, 2009, Oracle and/or its affiliates. 
 * All rights reserved.
 *      This material is the confidential property of Oracle Corporation. 
 *      or its subsidiaries or licensors and may be used, reproduced, stored
 *      or transmitted only in accordance with a valid Oracle license or 
 *      sublicense agreement.
 */

#ifndef BAS_DATAVALUE_H
  #include "BAS/DataValue.hpp"
#endif

namespace BAS {
	/**
     * \class Blob Blob.h "BAS/Blob.h"
     * Blob: This is the base BAS type for the infranet 'Blob' data type
     */
    class Blob : public DataValue {
   public:
        /**
         * toCharArray: Converts to a character array
         * @return const char * representing data that is contained
         */
	    const char *toCharArray() const;
    };
}
#endif
