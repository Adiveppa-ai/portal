#ifndef BAS_MAP_H
#define BAS_MAP_H

/*
 * Map.h 
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
     * \class Map Map.h "BAS/Map.h"
     * Map: This is the base bas type for unordered collections of data
     */
    class Map : public DataCollection {
    };
}
#endif
