#=======================================================================
# 
# Copyright (c) 2005, 2023, Oracle and/or its affiliates.
#
# This material is the confidential property of Oracle Corporation or its
# licensors and may be used, reproduced, stored or transmitted only in 
# accordance with a valid Oracle license or sublicense agreement.
#
#========================================================================
$DM_VERTEX_PINCONF_HEADER  =  <<END
#************************************************************************
# Configuration File for BRM with Vertex STQ and CTQ
#
# This configuration file is automatically installed and configured with
# default values during the BRM installation. You can edit this file to:
#   -- change the default values of the entries.
#   -- disable an entry by inserting a crosshatch (#) at the start of
#        the line.
#   -- enable a commented entry by removing the crosshatch (#).
# 
# Before you make any changes to this file, save a backup copy.
#
# When editing this file, follow the instructions in each section.
# For more information on the general syntax of configuration entries,
# see "Reference Guide to BRM Configuration Files" in the BRM online
# documentation.
#************************************************************************
END
;


%DM_VERTEX_PINCONF_ENTRIES = (

  "vertex_quantumdb_description", <<END
#========================================================================
# STQ Database Connection Parameters
#
# Specify the connection parameters for Sales & Use (STQ) system.
#
#   quantumdb_source: The name of the Oracle user in whose schema the STQ
#                     tables reside. This parameter is required if the default
#                     tablespace for the user Id and password parameters is
#                     not the same tablespace that contains the STQ tables.
#                     For ISAM database this parameter is simply the directory
#                     where the database file reside.
#   quantumdb_server: The network identifier for the Oracle database on
#                     the server system.
#                     This parameter should be commented for ISAM database.
#   quantumdb_user:   Identifies the user as a valid Oracle login.
#                     This parameter should be commented for ISAM database.
#   quantumdb_passwd: The identifier that uniquely identifies the user.
#                     This parameter should be commented for ISAM database.
#========================================================================
END
  , "vertex_quantumdb",
"- dm_vertex  quantumdb_source  $DM_VERTEX{'db_source'}
- dm_vertex  quantumdb_server  $DM_VERTEX{'db_server'}
- dm_vertex  quantumdb_user    $DM_VERTEX{'db_user'}
#- dm_vertex  quantumdb_passwd  $DM_VERTEX{'db_passwd'}"
        ,"enable_ssl_description", <<END
#========================================================================
# enable_ssl
#
# Specifies whether TLS will be enabled for PCM connections
#
#    0 - TLS is disabled.
#    1 - TLS is enabled.
#
#========================================================================
END
        ,"enable_ssl", "- dm enable_ssl $ENABLE_SSL"
  , "vertex_quantumdb_register_description", <<END
#========================================================================
# STQ Register Database
#
# Logs an audit trail of invoices in the Register database.
#
# The Register database contains tax rules, rates, results, and other
# information returned from Quantum, and can be used to create audit-trail
# reports. If you need to use the Register DB, remove the crosshatch (#)
# from the start of this entry's line.
#========================================================================
END
  , "vertex_quantumdb_register"
  , "#- dm_vertex quantumdb_register -"

  , "vertex_quantum_logfile_description", <<END
#======================================================================
# STQ Debug Logging
#
# If specified, uses the STQ API to log debug information (into the
# specified filename) about the current transaction to be processed
# for tax calculation. 
#
# To use enable STQ debug logging, remove the crosshatch (#) from the
# start of this entry's line.
#======================================================================
END
  , "vertex_quantum_logfile"
  , "#- dm_vertex quantum_logfile $DM_VERTEX{'logfile'}"

  , "vertex_quantum_sm_obj_description", <<END
#======================================================================
# STQ Storage Manager
#
# Specifies the Storage Manager shared library that the Data Manager
# uses to interact with a particular version of the Vertex STQ system.
# For example, use dm_vertex_stq100 to interact with STQ v10.0.
# Current values can be:
#   dm_vertex_stq100
#======================================================================
END
  , "vertex_quantum_sm_obj"
  , "- dm_vertex quantum_sm_obj ./dm_vertex_stq100\$\{LIBRARYEXTENSION\}"

);


%DM_VERTEX_CM_PINCONF_ENTRIES = (

  "vertex_dm_pointer_description", <<END
#========================================================================
# vertex_dm_pointer
#
#========================================================================
END
  , "vertex_dm_pointer"
  , "- cm dm_pointer $DM_VERTEX{'db_num'} ip $DM_VERTEX{'hostname'} $DM_VERTEX{'port'}  # dm_vertex"

  , "fm_rate_vertex_db_description", <<END
#========================================================================
# fm_rate_vertex_db
#
# Specifies the database number of the Vertex database.
#
# If you use Vertex, enable this configuration entry by removing the
# crosshatch (#) from the beginning of the line and verifying that the
# database number matches the number specified in the dm_pointer entry
# in the Vertex DM configuration file.
#========================================================================
END
  , "fm_rate_vertex_db"
  , "- fm_rate vertex_db $DM_VERTEX{'db_num'} /_tax_db 0"
);

%DM_VERTEX_NEW_PINCONF_ENTRIES = (

  "commtax_config_path_description", <<END
#========================================================================
# CTQ Configuration Path
#
# Specifies the location of the CTQ configuration file (ctqcfg.xml).
# Applicable to CommTax (CTQ) only.
#========================================================================
END
  , "commtax_config_path"
  , "- dm_vertex commtax_config_path \$\{CTQ_HOME\}/cfg"

  ,"commtax_config_name_description", <<END
#========================================================================
# CTQ Configuration Name 
#
# Specifies the configuration name from the ctqcfg.xml configuration file.
# Applicable to CommTax (CTQ) only.
#========================================================================
END
  , "commtax_config_name"
  , "- dm_vertex commtax_config_name CTQ Test"

  , "vertex_commtax_logfile_description", <<END
#======================================================================
# CTQ Debug Logging
#
# If specified, uses the CTQ API to log debug information (into the
# specified filename) about the current transaction to be processed
# for tax calculation. 
#
# To use enable CTQ debug logging, remove the crosshatch (#) from the
# start of this entry's line.
#======================================================================
END
  , "vertex_commtax_logfile"
  , "# - dm_vertex commtax_logfile ./ctq_dbg.log"

  , "vertex_commtaxdb_register_description", <<END
#========================================================================
# CTQ Register Database
#
# Logs the transaction into the Register database.
#
# The Register database contains all transactions that are returned from
# CTQ, and can be used to create audit-trail reports. If you need
# to use the Register DB, remove the crosshatch (#) from the start of
# this entry's line.
#========================================================================
END
  , "vertex_commtaxdb_register"
  , "#- dm_vertex commtaxdb_register -"

  , "vertex_use_charge_to_category_codes_description", <<END
#======================================================================
# use_charge_to_category_codes
#
# If specified, use the value as the Primary Place of Use (PPU) location
# and override the 2/3 rule as per the MTSA. If entry is not set, the
# value is defaulted to 10 (Wireless).  The format is:
#   - dm_vertex use_charge_to_category_codes <ChargeTo>
#
# To specify the ChargeTo, uncomment this entry.
#======================================================================
END
  , "vertex_use_charge_to_category_codes"
  , "#- dm_vertex use_charge_to_category_codes 10"

  , "vertex_commtax_sm_obj_description", <<END
#======================================================================
# CTQ Storage Manager
#
# Specifies the Storage Manager shared library that the Data Manager
# uses to interact with a particular version of the Vertex CTQ system.
# For example, use dm_vertex_ctq30206 to interact with CTQ v3.2.06.
# Current values can be:
#   dm_vertex_ctq30206
#======================================================================
END
  , "vertex_commtax_sm_obj"
  , "- dm_vertex commtax_sm_obj ./dm_vertex_ctq30206\$\{LIBRARYEXTENSION\}"

 , "vertex_tax_rate_precision_description", <<END
#======================================================================
# tax_rate_precision
#
# If specified, precision for tax rate will have given decimal places.
# By default, the value will be 5. Currently, this entry applies to
# CTQ tax rate decimal precision only.
#
# Enable the below entry to change the tax rate decimal precision.
#======================================================================
END
  , "vertex_tax_rate_precision"
  , "#- dm_vertex tax_rate_precision 5"

);
