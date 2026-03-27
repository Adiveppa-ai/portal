#ifndef __RWDB_COLLDEFS_H__
#define __RWDB_COLLDEFS_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/colldefs.h#1 $
 *
 * Copyright (c) 1994-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 **************************************************************************/

//////////////////////////////////////////////////////////////////////////
// Private Collectable Class IDs
//////////////////////////////////////////////////////////////////////////
// RWDBExprImp::isA():
#define __RWDBEXPRIMP                   0xDB10
#define __RWDBDYADICEXPRIMP             0xDB11
#define __RWDBASSIGNMENTEXPRIMP         0xDB12
#define __RWDBMONADICEXPRIMP            0xDB13
#define __RWDBCOLUMNEXPRIMP             0xDB14
#define __RWDBFORMSUBSTITUTIONEXPRIMP   0xDB15
#define __RWDBFUNCTIONEXPRIMP           0xDB16
#define __RWDBPHRASEKEYEXPRIMP          0xDB17
#define __RWDBVALUEEXPRIMP              0xDB18
#define __RWDBCOLLECTIONEXPRIMP         0xDB19
#define __RWDBSELECTOREXPRIMP           0xDB1A
#define __RWDBSCHEMAEXPRIMP             0xDB1B
#define __RWDBBOUNDEXPRIMP              0xDB1C
#define __RWDBTABLEEXPRIMP              0xDB1D
#define __RWDBJOINEXPRIMP               0xDB1E
#define __RWDBPERSISTEDEXPRIMP          0xDB1F

#endif
