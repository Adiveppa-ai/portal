#ifndef BAS_DATACOLLECTION_H
#define BAS_DATACOLLECTION_H
/*
 * DataCollection.h 
 *
 * Copyright (c) 2002, 2009, Oracle and/or its affiliates. 
 * All rights reserved.
 *      This material is the confidential property of Oracle Corporation. 
 *      or its subsidiaries or licensors and may be used, reproduced, stored
 *      or transmitted only in accordance with a valid Oracle license or 
 *      sublicense agreement.
 */

#ifndef BAS_CONCRETETYPE_H
  #include "BAS/ConcreteType.hpp"
#endif

namespace BAS {

    /** \class DataCollection DataCollection.h "BAS/DataCollection.h"
     * DataCollection: This is the base bas type for any Infranet represented
     * data type
     */
	class DataCollection : public ConcreteType {
    public:
    private:
    };
}
#endif
