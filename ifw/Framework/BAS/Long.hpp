#ifndef BAS_LONG_H
#define BAS_LONG_H
/*
 * Long.h 
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
     * \class Long Long.h "BAS/Long.h"
     * Long: This is the base BAS type of the infranet 'Long' data type
     */
    class Long : public DataValue {
    public:
        /** 
         * conversion operator
         * @return the value represented as a long
         */
        const long toLong () const;
        
        /**
         * assignment opreator
         * @param l the value being assigned
         * @return Long class representing the assigned value
         */
        Long &operator= (long l);

    private:
        long _l;
    };

}
#endif
