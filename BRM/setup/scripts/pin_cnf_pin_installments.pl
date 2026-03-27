#=======================================================================
#  @(#)%Oracle Version: pin_cnf_pin_installments.pl:12PS5:8:2021-Dec-16 19:11:14 %
# 
# Copyright (c) 2022, Oracle and/or its affiliates. All rights reserved. 
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
#========================================================================
%PIN_INSTALLMENTS_PINCONF_ENTRIES = (

	"pin_installments_logfile_description", <<END
#======================================================================
# pin_installments_logfile
#
# Name and location of the log file used by this Oracle process.
#
#======================================================================
END
	,"pin_installments_logfile"
	,"- pin_installments logfile \$\{PIN_LOG_DIR\}/pin_installments/pin_installments.pinlog"

	,"pin_installment_status_change_logfile_description", <<END
#======================================================================
# pin_installment_status_change_logfile
#
# Name and location of the log file used by this Oracle process.
#
#======================================================================
END
	,"pin_installment_status_change_logfile"
	,"- pin_installment_status_change logfile \$\{PIN_LOG_DIR\}/pin_installments/pin_installment_status_change.pinlog"

	,"pin_installments_loglevel_description", <<END
#======================================================================
# pin_installments_loglevel
#
# How much information the applications should log.
#
# The value for this entry can be:
#  -- 0: no logging
#  -- 1: log error messages only
#  -- 2: log error messages and warnings
#  -- 3: log error messages, warnings, and debugging messages
#======================================================================
END
	,"pin_installments_loglevel"
	, "- pin_installments loglevel 1"

	,"pin_installment_status_change_loglevel_description", <<END
#======================================================================
# pin_installment_status_change_loglevel
#
# How much information the applications should log.
#
# The value for this entry can be:
#  -- 0: no logging
#  -- 1: log error messages only
#  -- 2: log error messages and warnings
#  -- 3: log error messages, warnings, and debugging messages
#======================================================================
END
	,"pin_installment_status_change_loglevel"
	, "- pin_installment_status_change loglevel 1"

	,"pin_installments_performance_description", <<END
#======================================================================
# Entries for pin_installments
#
# These entries are used in the pin_installments configuration only.
#
#======================================================================
END
	,"pin_installments_performance",
"#- pin_installments        children       5
#- pin_installments        per_batch       500
#- pin_installments        per_step        1000
#- pin_installments        fetch_size      5000
#- pin_installments        max_errs        1"


	,"pin_installments_database_type_description", <<END
#======================================================================
# Database Type for pin_installments
#
# - pin_installments database_type oracle -----------> this means oracle
# If no entry is there in pin.conf then assuming database type as oracle.
#
#======================================================================
END
	,"pin_installments_database_type"
	,"- pin_installments database_type oracle"

	,"pin_installments_database_description", <<END
#======================================================================
# Default DB number for the search.
#======================================================================
END
	,"pin_installments_database"
	,"- pin_installments database $DM_ORACLE{'db_num'} /search 0"

	,"pin_installment_status_change_database_type_description", <<END
#======================================================================
# Database Type for pin_installment_status_change
#
# - pin_installment_status_change database_type oracle -----------> this means oracle
# If no entry is there in pin.conf then assuming database type as oracle.
#
#======================================================================
END
	,"pin_installment_status_change_database_type"
	,"- pin_installment_status_change database_type oracle"

	,"pin_installment_status_change_database_description", <<END
#======================================================================
# Default DB number for the search.
#======================================================================
END
	,"pin_installment_status_change_database"
	,"- pin_installment_status_change database $DM_ORACLE{'db_num'} /search 0"

	,"pin_installments_description", <<END
#======================================================================
# Entries for pin_installments
#
# These entries are used in the pin_installments -steps only for 
# performance improvement.
#
#======================================================================
END
        ,"pin_installments",
"#- pin_installments        children        5
#- pin_installments        per_step       1000
#- pin_installments        fetch_size        5000"

	,"pin_installment_status_change_description", <<END
#======================================================================
# Entries for pin_installment_status_change
#
# These entries are used in the pin_installment_status_change -steps only for 
# performance improvement.
#
#======================================================================
END
        ,"pin_installment_status_change",
"#- pin_installment_status_change        children        5
#- pin_installment_status_change        per_step       1000
#- pin_installment_status_change        fetch_size        5000"

);
 
