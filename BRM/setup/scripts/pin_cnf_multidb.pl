#=============================================================
#  @(#) % %
#    
# Copyright (c) 2006, 2010, Oracle and/or its affiliates. All rights reserved. 
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
#==============================================================

$MULTIDB_PINCONF_HEADER  =  <<END
#======================================================================
# Use this file to specify how the pin_confirm_logins application communicates
# with Infranet.
#
#  -- You can change the default value of an entry.
#  -- You can exclude an optional entry by adding the # symbol
#     at the beginning of the line.
#  -- You can include a commented entry by removing the # symbol.
#
# Before you make any changes to this file, save a backup copy.
#
# To edit this file, follow the instructions in the commented sections.
# For more information on the general syntax of configuration entries,
# see "Reference Guide to Infranet Configuration Files" in the Infranet
# online documentation.
#======================================================================
END
;

%MULTIDB_PINCONF_ENTRIES = (

 "pin_confirm_logfile_description", <<END
#======================================================================
# logfile
#
# Full path to the log file for the pin_confirm_logins application.
#======================================================================
END

  , "pin_confirm_logfile", "- pin_confirm_logins	logfile \$\{PIN_LOG_DIR\}/pin_confirm_logins/pin_confirm_logins.pinlog"

  , "pin_confirm_loglevel_description", <<END
#======================================================================
# loglevel
#
# How much information the pin_confirm_logins application should log.
# 
# The value for this entry can be:
#  -- 0: no logging
#  -- 1: log error messages only
#  -- 2: log error messages and warnings
#  -- 3: log error messages, warnings, and debugging messages
#======================================================================
END
  , "pin_confirm_loglevel", "- pin_confirm_logins	loglevel		2"

  , "pin_confirm_frequency_description", <<END
#======================================================================
# frequency
#
# How frequently, in minutes, the application runs.
#======================================================================
END
  , "pin_confirm_frequency", "- pin_confirm_logins	frequency		10"

  , "pin_confirm_validation_delay_description", <<END
#======================================================================
# validation_delay
#
# How much time since the modification of the uniqueness entry must
# go by before we validate it.  We don't want to validate something that
# is in process of being created.  This allows us to delay validation
# until we are sure enough time has passed to allow commit_customer to
# finish.
#======================================================================
END
  , "pin_confirm_validation_delay", "- pin_confirm_logins	validation_delay	10"

  , "pin_confirm_use_account_no_description", <<END
#======================================================================
# use_account_no
#
# Boolean value indicating if we should add the account_no to each
# /uniqueness object:
# 1 = TRUE
# 0 = FALSE
# It requires an extra read so it may take time for large groups of 
# confirmations
#======================================================================
END
  , "pin_confirm_use_account_no", "- pin_confirm_logins	use_account_no		1"

  , "pin_config_logfile_description", <<END
#======================================================================
# logfile
#
# Full path to the log file for the pin_config_distribution application.
#======================================================================
END
  , "pin_config_logfile", "- pin_config_distribution	logfile	\$\{PIN_LOG_DIR\}/pin_config_distribution/pin_config_distribution.pinlog"

  , "pin_config_loglevel_description", <<END
#======================================================================
# loglevel
#
# How much information the pin_config_distribution application should log.
# 
# The value for this entry can be:
#  -- 0: no logging
#  -- 1: log error messages only
#  -- 2: log error messages and warnings
#  -- 3: log error messages, warnings, and debugging messages
#======================================================================
END
  , "pin_config_loglevel", "- pin_config_distrbution	loglevel		2"

  , "pin_config_frequency_description", <<END
#======================================================================
# frequency
#
# Frequency at which pin_config_distribution updates the 
# /config/distribution object to reflect how many accounts are in each
# database, and the status of the database.
#
# Units here are the number of hours to wait between updates.
#
# 0 means run constantly, although this may impose too much load on
# your system, so use with caution.
#======================================================================
END
  , "pin_config_frequency", "- pin_config_distribution	frequency		1"

);

$MULTIDB_CONFIGDIST_HEADER  =  <<END
#
#       
# Copyright (c) 1996, 2023, Oracle and/or its affiliates. All rights reserved. 
#       
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#

#       A database number must conform to the format int.int.int.int.
#       A priority must be a value greater than 0.
#       A max account size must be a value greater than 0.
#       A status is either OPEN, CLOSED or UNAVAILABLE
#         OPEN means that the database is available for account
#         creation.
#
#         CLOSED means that the database has reached the 'full'
#         status, and will not be used for account creation unless
#         all other databases are CLOSED, or the account you are
#         creating has a billing relationship (sponsor, brand,
#         subordinate) with another account in this database.
#
#         UNAVAILABLE means never use the database unless forced to by the 
#         rule that a subordinate/sponsored/brand account must be in
#         the same database as its parent. 
#
#         The difference between CLOSED and UNAVAILABLE is that if all
#         databases are CLOSED, one of them will be chosen for account
#         creation. One labelled UNAVAILABLE will never be chosen.
#         This logic is controllable via policy; see fm_cust_pol_get_db_no
#--------------------------------------------------------------------------
END
;

$MULTIDB_CONFIGDIST_ENTRIES = <<END
DB_NO = "0.0.0.1" ;             # 1st database config block.
PRIORITY = 1 ;
MAX_ACCOUNT_SIZE = 100000 ;
STATUS = "OPEN" ;
SCHEMA_NAME = "$DM{'db'}->{'user'}" ;

#DB_NO = "0.0.0.2" ;             # 2nd database config block.
#PRIORITY = 1 ;
#MAX_ACCOUNT_SIZE = 100000 ;
#STATUS = "UNAVAILABLE" ;
#SCHEMA_NAME = "pin211x" ;

# 1st database config block, With logical partition
#DB_NO = "0.1.0.1" ;             
#PRIORITY = 1 ;
#MAX_ACCOUNT_SIZE = 100000 ;
#STATUS = "UNAVAILABLE" ;
#SCHEMA_NAME = "pin211x" ;
END
;
