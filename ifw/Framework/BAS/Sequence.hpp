#ifndef BAS_SEQUENCE_H
#define BAS_SEQUENCE_H

/*
 * Sequence.h 
 *
 * Copyright (c) 2002, 2009, Oracle and/or its affiliates. 
 * All rights reserved.
 *      This material is the confidential property of Oracle Corporation. 
 *      or its subsidiaries or licensors and may be used, reproduced, stored
 *      or transmitted only in accordance with a valid Oracle license or 
 *      sublicense agreement.
 */

#ifndef BAS_DATACOLLECTION_H
  #include "BAS/DataCollection.hpp"
#endif

namespace BAS {
	/**
     * \class Sequence Sequence.h "BAS/Sequence.h"
     * Sequence: This is the base bas type for ordered collections of data
     */
    class Sequence : public DataCollection {
    };
}
#endif
