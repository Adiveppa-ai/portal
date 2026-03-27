#=============================================================
#  @(#) % %
# 
# Copyright (c) 2005, 2017, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
#==============================================================


$LDAP_PINCONF_HEADER  =  <<END
#************************************************************************
# Configuration File for LDAP
#
#
# This configuration file is automatically installed and configured with
# default values during Portal installation. You can edit this file to:
#   -- change the default values of the entries.
#   -- disable an entry by inserting a crosshatch (#) at the start of
#        the line.
#   -- enable a commented entry by removing the crosshatch (#).
# 
# Before you make any changes to this file, save a backup copy.
#
# When editing this file, follow the instructions in each section.
# For more information on the general syntax of configuration entries,
# see "Reference Guide to Portal Configuration Files" in the Portal
# online documentation.
#************************************************************************
END
;


%LDAP_PINCONF_ENTRIES = (
  "directory_description", <<END
#***********************************************************************
# LDAP Directory Server and Mapping Configuration
#***********************************************************************
END
  , "mapping_file_description", <<END
#========================================================================
# mapping_file
#
# Specifies the interface definition language (idl) mapping file that
# the LDAP Data Manager uses to pass mapping information to
# Portal.
#
# Replace XXX.idl with the name of your mapping file.
# For the LDAP Manager, the standard name is ldap.idl.
#========================================================================
END
	, "mapping_file", "- ldap_ds	mapping_file	ldap.idl"
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
	, "hostname_description", <<END
#========================================================================
# hostname
#
# Specifies the name of the computer on which the LDAP directory server
# runs.
#
# Replace "localhost" with the name of the computer that contains the
# LDAP directory.
#========================================================================
END
	, "hostname", "- ldap_ds	hostname	localhost"
	, "port_description", <<END
#========================================================================
# port
#
# Specifies the port number on which the LDAP directory server listens.
#
# The standard LDAP directory server port number is 389.
#========================================================================
END
	, "port", "- ldap_ds	port		389"
        , "ssl_description", <<END
#========================================================================
# ssl
#
# Specifies if the port number on which the LDAP directory server listens
# is configured to accept TLS connections from dm_ldap .
#
# 0 - TLS is disabled in LDAP directory server
# 1 - TLS is enabled in LDAP directory server
#
#========================================================================
END
        , "ssl", "- ldap_ds ssl     0"
        , "ssl_auth_mode_description", <<END
#========================================================================
# ssl_auth_mode
#
# Specifies the TLS authentication mode in the LDAP directory server. 
#
# 0 - TLS authentication is disabled in LDAP directory server.
# 1 - TLS one way authentication is enabled in LDAP directory server.
# 2 - TLS two way authentication is enabled in LDAP directory server.
#
#========================================================================
END
        , "ssl_auth_mode", "- ldap_ds ssl_auth_mode       1"
        , "wallet_description", <<END
#========================================================================
# wallet
#
# Specifies the location of Oracle Wallet used by dm_ldap to
# communicate with TLS enabled LDAP directory server.
#
# NOTE: This wallet stores the certificate of the LDAP directory server.
#========================================================================
END
        , "wallet", "- ldap_ds wallet      ldap_wallet"
	, "bind_description", <<END
#========================================================================
# bind
#
# Specifies the Distinguished Name (DN) of the entry used to authenticate
# Portal to the LDAP directory server.
#
# Replace XXX_BIND_DN with the appropriate set of values.
#
# The LDAP Data Manager uses the credentials of this entry to connect to
# the directory server. The specified user ID (uid) must have permission
# to create and modify entries.
#
# For example, you might use:
#
#    uid=admin, ou=Administrators, ou=TopologyManagement, o=NetscapeRoot
#
# to bind to a Netscape LDAP directory server where the
#
#    login uid is admin,
#    organizational unit (ou) is Administrators,
#    next-level ou is TopologyManagement, and
#    organization (o) = NetscapeRoot.
#
#========================================================================
END
	, "bind", "- ldap_ds	bind		XXX_BIND_DN"
	, "password_description", <<END
#========================================================================
# password
#
# Specifies the password for logging on to the LDAP directory server.
#
# The bind password, in clear text, authenticates Portal to the
# directory server during login. Replace XXX_PASSWORD with the password
# for your directory server.
#========================================================================
END
	, "password", "#- ldap_ds	password	XXX_PASSWORD"
	, "debug_description", <<END
#========================================================================
# debug
#
# Specifies whether the LDAP Data Manager prints debugging information
# to the dm_ldap.pinlog file.
#
# The value for this entry can be:
#
#    0 = (Default) Disable debugging
#    1 = Enable debugging
#========================================================================
END
	, "debug", "- ldap_ds	debug		0"
	, "deleteOldRDN_description", <<END
#========================================================================
# deleteOldRDN
#
# Specifies whether to keep the old relative distinguished name of an
# entry when you rename that entry.
#
# The value for this entry can be:
#
#    0 = Retain the existing relative distinguished name
#    1 = (Default) Delete the old relative distinguished name
#========================================================================
END
	, "deleteOldRDN", "- ldap_ds       deleteOldRDN    1"
	, "appendZToTimestamp_description", <<END
#========================================================================
# appendZToTimestamp
#
# Specifies whether to append the letter Z to the timestamp.
# Default value is 0 and is valid only if the encoding is UTCTIMESTRING
#
# The value for this entry can be:
#
#    0 = (Default) Infranet does not append Z.
#    1 = Infranet appends Z
#========================================================================
END
	, "appendZToTimestamp", "- ldap_ds       appendZToTimestamp      0"
	, "encodeTimestamp_description", <<END
#========================================================================
# encodeTimestamp
#
# Specifies the generalized time stamp encoding method.
#
# The value for this entry can be:
#
#    0 = (Default) UTCTIMESTRING
#    1 = UTCTIMEVALUE
#========================================================================
END
	, "encodeTimestamp", "- ldap_ds       encodeTimestamp         UTCTIMESTRING"
 );


%LDAP_CONNECT_PINCONF_ENTRIES = (
  "pin_channel_export_description", <<END
#========================================================================
# pin_channel_export
#
# Specifies how often, in seconds, the /channel_event entries in the
# Portal database are synchronized with the directory server.
#
# By default, the pin_channel_export application sets this value to
# 60 seconds.
#========================================================================
END
	, "pin_channel_export", "- pin_channel_export  sleep_interval  60"
,"retry_interval_description", <<END
#========================================================================
# retry_interval
#
# Interval time in seconds between each retry
#
# The default value is 30 seconds.
#========================================================================
END
	,"retry_interval", "- pin_channel_export    retry_interval  30"
	, "application_loglevel_description", <<END
#========================================================================
# application_loglevel
#
# Specifies how much information the Pin Channel Export Application logs.
# 
# The value for this entry can be:
#
#    0 = no logging
#    1 = (Default) log error messages only
#    2 = log error messages and warnings
#    3 = log error, warning, and debugging messages
#========================================================================
END
	, "application_loglevel", "- pin_channel_export    loglevel        1"
	,"application_logfile_description", <<END
#========================================================================
# application_logfile
#
# Specifies the full path to the log file used by Pin Channel Export Application.
#
# You can enter any valid path.
#========================================================================
END
	,"application_logfile", "- pin_channel_export logfile $LDAP{'log_location'}/pin_channel_export.pinlog"
 );

%LDAP_CHANNEL_PINCONF_ENTRIES = (
"application_loglevel_description", <<END
#========================================================================
# application_loglevel
#
# Specifies how much information the Pin Channel Export Application logs.
# 
# The value for this entry can be:
#
#    0 = no logging
#    1 = (Default) log error messages only
#    2 = log error messages and warnings
#    3 = log error, warning, and debugging messages
#========================================================================
END
	, "application_loglevel", "- load_channel_config loglevel 3"
	
 );

%LDAP_CM_ENTRIES = (
  "ldap_dm_pointer_description", <<END
#========================================================================
# ldap_dm_pointer
#
# Specifies your LDAP Data Manager.
#
# The default database number is 0.0.5.X, where X is the number of the
# of the Oracle database.
#========================================================================
END
  , "ldap_dm_pointer", "- cm dm_pointer $LDAP{'db_num'} ip $LDAP{'hostname'} $LDAP{'port'}"
  , "enable_push_description", <<END
#========================================================================
# enable_push
#
# Specifies whether to track changes to objects and to update channel
# objects.
#
# The value for this entry can be:
#
#    0 = (Default) Don't update channel objects.
#    1 = Update channel objects.
#========================================================================
END
  , "enable_push", "- fm_channel enable_push $LDAP{'enable_push'}"
  , "ldap_db_description", <<END
#========================================================================
# ldap_db
#
# Specifies the database number of the LDAP database.
#
# Verify that the database number matches the number specified in  
# the dm_pointer entry in the LDAP�s Data Manager configuration file.
#========================================================================
END
  , "ldap_db", "- fm_repl_pol ldap_db $LDAP{'db_num'} /_ldap_db 0"
  , "user_scheme_description", <<END
#========================================================================
# user_scheme
#
# Specifies a scheme for mapping events to a single object for pushing 
# to the LDAP directory server.
#
# The value for this entry can be:
#
#    0 = Use the "one-to-one mapping scheme," which maps Portal
#          /account and /service objects to separate entries in the
#          directory server.
#    1 = (Default) Use the "user mapping scheme," which maps Portal
#          /account and /service objects to one entry in the directory
#          server.
#========================================================================
END
  , "user_scheme", "- fm_repl_pol user_scheme $LDAP{'user_scheme'}"
  , "ldap_env_description", <<END
#========================================================================
# ldap_env
#
# Specifies the LDAP environment that Portal uses for data replication. 
#
# The value for this entry can be:
#
#    ldap = LDAP environment
#========================================================================
END
  , "ldap_env", "- fm_repl_pol ldap_env $LDAP{'env'}"
  , "ldap_fm_required_description", <<END
#========================================================================
# ldap_fm_required
#
# Required Facilities Modules (FM) configuration entries
#
# The entries below specify the required FMs that are linked to the CM when
# the CM starts. The FMs required by the CM are included in this file when
# you install Portal. 
#
# Caution: DO NOT modify these entries unless you need to change the
#          location of the shared library file. DO NOT change the order of
#          these entries, because certain modules depend on others being
#          loaded before them.
#========================================================================
END
  , "ldap_fm_required", <<END
- cm fm_module \$\{PIN_HOME\}/lib/fm_channel\$\{LIBRARYEXTENSION\} fm_channel_config$FM_FUNCTION_SUFFIX - pin
- cm fm_module \$\{PIN_HOME\}/lib/fm_repl_pol\$\{LIBRARYEXTENSION\} fm_repl_pol_config$FM_FUNCTION_SUFFIX - pin
END
);

%TRANSPOL_FM_PINCONF_ENTRIES = (

  "fm_trans_pol_fm_required_description", <<END
#========================================================================
# fm_trans_pol_fm_required
#
# Required Facilities Modules (FM) configuration entries
#
# The entries below specify the required FMs that are linked to the CM when
# the CM starts. The FMs required by the CM are included in this file when
# you install Portal.  
#
# Caution: DO NOT modify these entries unless you need to change the
#          location of the shared library file. DO NOT change the order of
#          these entries, because certain modules depend on others being
#          loaded before them.
#========================================================================
END
  , "fm_trans_pol_fm_required", <<END
- cm fm_module \$\{PIN_HOME\}/lib/fm_trans_pol\$\{LIBRARYEXTENSION\} fm_trans_pol_config$FM_FUNCTION_SUFFIX - pin
END
);
