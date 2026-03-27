#ifndef BAS_BINSTR_H
#define BAS_BINSTR_H
/*
 * BinStr.h 
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

/**
 * The Basic data types and functionality that all Infranet Objects and 
 * business logic utilizes.
 */
namespace BAS {
    /**
     * \class BinStr BinStr.h "BAS/BinStr.h"
     * BinStr: This is the base bas type for the infranet 'BinStr' data
     * type
     */
    class BinStr : public DataValue {
    public:
        /**
         * toCharArray: Converts to a character array. Does not
         * copy the data, instead returns a pointer to it which cannot
         * be modified
         * @return const char * representing data that is contained.
         */
	    const char *toCharArray() const;
    };
}
#endif
