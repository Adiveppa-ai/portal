/*
 * @(#)%Portal Version: pin_partition_mode.h:CommonIncludeInt:3:2006-Mar-14 00:47:35 %
 *      Copyright (c) 2001-2006 Portal Software, Inc. All rights reserved.
 *      This material is the confidential property of Portal Software, Inc. 
 *      or its subsidiaries or licensors and may be used, reproduced, stored
 *      or transmitted only in accordance with a valid Portal license or 
 *      sublicense agreement.
 */
#ifndef _PIN_PARTITION_MODE_H_
#define _PIN_PARTITION_MODE_H_

typedef enum pin_partition_mode {
	PIN_PARTITION_MODE_HISTORIC = 0, 
	PIN_PARTITION_MODE_FINITE,
	PIN_PARTITION_MODE_UNKNOWN = -1
} pin_partition_mode_t;

#define PIN_PARTITION_MODE_HISTORIC_STR "Historic"
#define PIN_PARTITION_MODE_FINITE_STR	"Finite"

/* These 2 constants are for event classes */
#define PARTITION_CLAUSE_ROOT_CLASS "partition by range (poid_id0) (partition partition_historic values less than (35184372088832), partition partition_last values less than (MAXVALUE))"
#define PARTITION_CLAUSE_DERIVED_CLASS "partition by range (obj_id0) (partition partition_historic values less than (35184372088832), partition partition_last values less than (MAXVALUE))"
	
/* These 2 constants are for non event classes */
#define PARTITION_CLAUSE_NON_EVENT_ROOT_CLASS "partition by range (poid_id0) (partition partition_last values less than (MAXVALUE))"
#define PARTITION_CLAUSE_NON_EVENT_DERIVED_CLASS "partition by range (obj_id0) (partition partition_last values less than (MAXVALUE))"

#endif
