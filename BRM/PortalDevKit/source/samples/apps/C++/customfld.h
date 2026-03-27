/* Continuus file information --- %full_filespec: customfld.h~1:incl:1 % */
/*
 * @(#) %full_filespec: customfld.h~1:incl:1 %
 *
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *      This material is the confidential property of Oracle Corporation. 
 *      or its subsidiaries or licensors and may be used, reproduced, stored
 *      or transmitted only in accordance with a valid Oracle license or 
 *      sublicense agreement.
 */

#ifndef CUSTOMFLD_H
#define CUSTOMFLD_H

#define EMAIL_EVENT_INFO  10001
#define EMAIL_FROM        10002
#define EMAIL_TO          10003


#define PIN_FLD_EMAIL_EVENT_INFO PIN_MAKE_FLD(PIN_FLDT_SUBSTRUCT, EMAIL_EVENT_INFO)
#define PIN_FLD_EMAIL_FROM		 PIN_MAKE_FLD(PIN_FLDT_STR, EMAIL_FROM)
#define PIN_FLD_EMAIL_TO		 PIN_MAKE_FLD(PIN_FLDT_STR, EMAIL_TO)



const PinSubTypeField tsf_PIN_FLD_EMAIL_EVENT_INFO(PIN_FLD_EMAIL_EVENT_INFO);
const PinStrTypeField tsf_PIN_FLD_EMAIL_FROM(PIN_FLD_EMAIL_FROM);
const PinStrTypeField tsf_PIN_FLD_EMAIL_TO(PIN_FLD_EMAIL_TO);

#endif // CUSTOMFLD_H ///

