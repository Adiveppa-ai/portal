#=======================================================================
#  @(#)%Oracle Version: pin_cnf_pin_deposits.pl:12PS6:8:2022-Jan-21 01:44:14 %
# 
# Copyright (c) 2022, Oracle and/or its affiliates. All rights reserved. 
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
#========================================================================
%PIN_DEPOSITS_PINCONF_ENTRIES = (

	"pin_deposit_calc_interest_logfile_description", <<END
#======================================================================
# pin_deposit_calc_interest_logfile
#
# Name and location of the log file used by this Oracle process.
#
#======================================================================
END
	,"pin_deposit_calc_interest_logfile"
	,"- pin_deposit_calc_interest logfile \$\{PIN_LOG_DIR\}/pin_deposits/pin_deposit_calc_interest.pinlog"

	,"pin_deposit_transfer_deposit_logfile_description", <<END
#======================================================================
# pin_deposit_transfer_deposit_logfile
#
# Name and location of the log file used by this Oracle process.
#
#======================================================================
END
	,"pin_deposit_transfer_deposit_logfile"
	,"- pin_deposit_transfer_deposit logfile \$\{PIN_LOG_DIR\}/pin_deposits/pin_deposit_transfer_deposit.pinlog"

	,"pin_deposit_release_purchased_deposit_logfile_description", <<END
#======================================================================
# pin_deposit_release_purchased_deposit_logfile
#
# Name and location of the log file used by this Oracle process.
#
#======================================================================
END
	,"pin_deposit_release_purchased_deposit_logfile"
	,"- pin_deposit_release_purchased_deposit logfile \$\{PIN_LOG_DIR\}/pin_deposits/pin_deposit_release_purchased_deposit.pinlog"


	,"pin_deposit_calc_interest_loglevel_description", <<END
#======================================================================
# pin_deposit_calc_interest_loglevel
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
	,"pin_deposit_calc_interest_loglevel"
	, "- pin_deposit_calc_interest loglevel 1"


	,"pin_deposit_transfer_deposit_loglevel_description", <<END
#======================================================================
# pin_deposit_transfer_deposit_loglevel
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
	,"pin_deposit_transfer_deposit_loglevel"
	, "- pin_deposit_transfer_deposit loglevel 1"


	,"pin_deposit_release_purchased_deposit_loglevel_description", <<END
#======================================================================
# pin_deposit_release_purchased_deposit_loglevel
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
	,"pin_deposit_release_purchased_deposit_loglevel"
	, "- pin_deposit_release_purchased_deposit loglevel 1"


	,"pin_deposit_calc_interest_database_type_description", <<END
#======================================================================
# Database Type for pin_deposit_calc_interest
#
# - pin_deposit_calc_interest database_type oracle -----------> this means oracle
# If no entry is there in pin.conf then assuming database type as oracle.
#
#======================================================================
END
	,"pin_deposit_calc_interest_database_type"
	,"- pin_deposit_calc_interest database_type oracle"

	,"pin_deposit_calc_interest_database_description", <<END
#======================================================================
# Default DB number for the search.
#======================================================================
END
	,"pin_deposit_calc_interest_database"
	,"- pin_deposit_calc_interest database $DM_ORACLE{'db_num'} /search 0"
	
	,"pin_deposit_release_purchased_deposit_database_type_description", <<END
#======================================================================
# Database Type for pin_deposit_release_purchased_deposit
#
# - pin_deposit_release_purchased_deposit database_type oracle -----------> this means oracle
# If no entry is there in pin.conf then assuming database type as oracle.
#
#======================================================================
END
	,"pin_deposit_release_purchased_deposit_database_type"
	,"- pin_deposit_release_purchased_deposit database_type oracle"

	,"pin_deposit_release_purchased_deposit_database_description", <<END
#======================================================================
# Default DB number for the search.
#======================================================================
END
	,"pin_deposit_release_purchased_deposit_database"
	,"- pin_deposit_release_purchased_deposit database $DM_ORACLE{'db_num'} /search 0"

	,"pin_deposit_transfer_deposit_database_type_description", <<END
#======================================================================
# Database Type for pin_deposit_transfer_deposit
#
# - pin_deposit_transfer_deposit database_type oracle -----------> this means oracle
# If no entry is there in pin.conf then assuming database type as oracle.
#
#======================================================================
END
	,"pin_deposit_transfer_deposit_database_type"
	,"- pin_deposit_transfer_deposit database_type oracle"

	,"pin_deposit_transfer_deposit_database_description", <<END
#======================================================================
# Default DB number for the search.
#======================================================================
END
	,"pin_deposit_transfer_deposit_database"
	,"- pin_deposit_transfer_deposit database $DM_ORACLE{'db_num'} /search 0"

	,"pin_deposit_calc_interest_description", <<END
#======================================================================
# Entries for pin_deposit_calc_interest
#
# These entries are used in the pin_deposit_calc_interest -steps only for 
# performance improvement.
#
#======================================================================
END
        ,"pin_deposit_calc_interest",
"#- pin_deposit_calc_interest        children        5
#- pin_deposit_calc_interest        per_step       1000
#- pin_deposit_calc_interest        fetch_size        5000"

	,"pin_deposit_transfer_deposit_description", <<END
#======================================================================
# Entries for pin_deposit_transfer_deposit
#
# These entries are used in the pin_deposit_transfer_deposit -steps only for 
# performance improvement.
#
#======================================================================
END
        ,"pin_deposit_transfer_deposit",
"#- pin_deposit_transfer_deposit        children        5
#- pin_deposit_transfer_deposit        per_step       1000
#- pin_deposit_transfer_deposit        fetch_size        5000"

	,"pin_deposit_release_purchased_deposit_description", <<END
#======================================================================
# Entries for pin_deposit_release_purchased_deposit
#
# These entries are used in the pin_deposit_release_purchased_deposit -steps only for 
# performance improvement.
#
#======================================================================
END
        ,"pin_deposit_release_purchased_deposit",
"#- pin_deposit_release_purchased_deposit        children        5
#- pin_deposit_release_purchased_deposit        per_step       1000
#- pin_deposit_release_purchased_deposit        fetch_size        5000"

);
