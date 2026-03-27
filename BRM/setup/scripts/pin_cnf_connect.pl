#=======================================================================
#  @(#)%Portal Version: pin_cnf_connect.pl:PortalBase7.2PatchInt:1:2005-Oct-24 10:30:32 %
# 
# Copyright (c) 2005, 2017, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
#========================================================================

$CONNECT_PERL_PCMDD = <<END
# Entries for perl pcmdd_connect
END
;

%CONNECT_PERL_ENTRIES = (
        "cm entries for pcmdd", <<END
#
END
        ,"cm_ptr_entries",
        "- cm enable_ssl $ENABLE_SSL
- cm wallet \$BRM_CONF_WALLET
- cm dm_pointer $DM{'db_num'} ip $DM{'hostname'} $DM{'port'}"

);
$CONNECT_PINCONF_HEADER  = <<END
#************************************************************************
# Configuration file for the testnap utility
#
#
# You use testnap to manually interact with the database and to test your
# custom applications.
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


%CONNECT_PINCONF_ENTRIES = (

	"cm_ptr_0_description", <<END
#========================================================================
# cm_ptr
# 
# Specifies a pointer to the CM or CMMP. 
#
# Use a separate entry for each CM or CMMP. If testnap can't find the
# first CM or CMMP, it looks for the next in the list.
#
# Each entry includes three values:
# 
#     <protocol> = "ip", for this release
#     <host>     = the name or IP address of the computer running the
#                    CM or CMMP
#     <port>     = the TCP port number of the CM or CMMP on this computer
#
# The port number should match a corresponding cm_ports entry with
# the same port number in the CM or CMMP configuration file. The 
# default, 11960, is a commonly specified port for the CM or CMMP.
#========================================================================
END
	,"cm_ptr_0", "- nap cm_ptr ip $CM{'hostname'} $CM{'port'}"

	,"cm_ptr_userid_description", <<END
#========================================================================
# userid
#
# Specifies the database number and service type for the Portal
# database. 
#
# The CM uses the database number to identify the Portal database 
# and to connect to the correct Data Manager. For connections that don't
# require a login name and password, the CM also passes the service
# type to the database.
#
# The database number, in the form 0.0.0.N, is the number assigned to 
# your Portal database when you installed the system. The default
# is 0.0.0.1.
#
# The service type is /service/pcm_client and the ID is set based on login_name.
# DO NOT change these values.
#========================================================================
END
	,"cm_ptr_userid", "- - userid $DM{'db_num'} /service/pcm_client $MAIN_CM{'user_id'}"

	,"cm_ptr_login_description", <<END
#========================================================================
# login_type
#
# Specifies whether the login name and password are required.
#
# The value for this entry can be:
#
#    0 = Only a user ID is required.
#    1 = (Default) Both a name and a password are required.
#
# By default, CMs require a user login and password when requesting an open
# context using PCM_CONTEXT_OPEN. However, you can remove this authentication
# requirement by configuring the CM with a cm_login_module of
# cm_login_null.so
#========================================================================
END
	,"cm_ptr_login", "- nap login_type 1"
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
        ,"enable_ssl", "- nap enable_ssl $ENABLE_SSL"
	,"cm_ptr_login_name_description", <<END
#========================================================================
# login_name
#
# Specifies the login name to use when testnap connects to the CM. 
#========================================================================
END
	,"cm_ptr_login_name", "- nap login_name $MAIN_CM{'login_name'}.$DM{'db_num'}"

        ,"cm_ptr_logfile_description", <<END
#========================================================================
# logfile
#
# Specifies the path to the log file for the sample application
#========================================================================
END
        ,"cm_ptr_logfile",
"- sample_act    logfile sample_act.pinlog
- sample_del    logfile sample_del.pinlog
- sample_app    logfile sample_app.pinlog 
- sample_search logfile sample_search.pinlog 
- sample_who    logfile sample_who.pinlog" 
	,"cm_ptr_login_pw_description", <<END
#========================================================================
# login_pw
#
# Specifies the password to use when testnap connects to the CM.
#========================================================================
END
	,"cm_ptr_login_pw", "#- nap login_pw   $MAIN_CM{'pcm_admin_passwd'}"

 );
