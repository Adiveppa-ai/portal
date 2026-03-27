#=============================================================
# @(#)$Id: pin_cnf_dm_fusa.pl /cgbubrm_mainbrm.portalbase/4 2018/06/22 04:47:05 agangrad Exp $ 
# 
# Copyright (c) 2005, 2018, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
#==============================================================
##
## Also requires QM pin cnf entries
##
#************************************************************************
# Configuration File for Portal with FUSA (Paymentech)
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
%DM_FUSA_PINCONF_ENTRIES = (
	"db_no_description", <<END
#========================================================================
# db_no
#
# Specifies the database number assigned to Paymentech.
#
# The format is 0.0.0.n  / 0, where n is your database number. 
# The default database number for Paymentech is 2.
#
# You must also include the database number in these two entries in the
# Connection Manager’s configuration file:
#    cc_db
#    dm_pointer
#========================================================================
END
	,"db_no", "- dm_fusa db_no $DM_FUSA{'db_num'} / 0"
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
        ,"fusa_tls_enabled_description", <<END
#========================================================================
# fusa_tls_enabled
#
# Specifies whether TLS will be enabled for connection to Paymentech
# from dm_fusa
#
#    0 - TLS is disabled.
#    1 - TLS is enabled.
#
#========================================================================
END
        ,"fusa_tls_enabled", "#- dm_fusa fusa_tls_enabled $ENABLE_SSL"
	,"online_proto_description", <<END
#========================================================================
# online_proto
# 
# Specifies the status of the link to the Paymentech online server.
#
# The value for this entry can be:
#
#    socket   = (Default) The link is up. 
#    linkdown = The link is down.
#
# Use linkdown to speed registration when you know that the Paymentech
# connection will be down for a long time. Linkdown causes the
# Paymentech DM to automatically return a "no answer" error for each
# each connection. If you do not use linkdown, the Paymentech DM must
# wait for a timeout before reporting the "no answer" error.
#
# Note: The modem option is no longer supported.
#========================================================================
END
	,"online_proto", "- dm_fusa online_proto $DM_FUSA{'online_protocol'}"
	,"online_srvr_description", <<END
#========================================================================
# online_srvr
#
# Specifies the IP address or host name for online connections.
#
# Paymentech assigns this address. Change this entry to reflect the
# information you get from Paymentech.
#
# If you use the fusamux program, use the IP address or host name of the
# computer on which fusamux runs.
#========================================================================
END
	,"online_srvr", "- dm_fusa online_srvr $DM_FUSA{'online_srvr'}"
	,"online_port_description", <<END
#========================================================================
# online_port
#
# Specifies the port number for online connections.
#
# Paymentech assigns this port number. Change this entry to reflect the
# information you get from Paymentech.
#
# If you use the fusamux program, set the port number to the one on which
# fusamux listens. (See the guidelines for the fusamux_port entry in the
# fusamux section of this file).
#
# Note: The default port number, 5678, is the port for the Portal
#       credit-card simulator for online transactions, answer_s, 
#       which you can use for testing.
#========================================================================
END
	,"online_port", "- dm_fusa online_port $DM_FUSA{'answer_s_port'}"
	,"batch_proto_description", <<END 
#========================================================================
# batch_proto
# 
# Specifies the status of the link to the Paymentech batch server.
#
# The value for this entry can be:
#
#    socket   = (Default) The link is up.
#    linkdown = The link is down.
#
# Use linkdown when you know that the Paymentech connection will be down
# for a long time. Linkdown causes the Paymentech DM to automatically
# return a "no answer" error for each connection. If you do not use
# linkdown, the Paymentech DM must wait for a timeout before reporting
# the "no answer" error.
#========================================================================
END
	,"batch_proto", "- dm_fusa batch_proto $DM_FUSA{'batch_protocol'}"
	,"batch_srvr_description", <<END
#========================================================================
# batch_srvr
#
# Specifies the IP address or host name for batch connections.
#
# Paymentech assigns this address. Change this entry to reflect the 
# information you get from Paymentech.
#========================================================================
END
	,"batch_srvr", "- dm_fusa batch_srvr $DM_FUSA{'batch_srvr'}"
	,"batch_port_description", <<END
#========================================================================
# batch_port
#
# Specifies the port number for batch connections.
#
# Paymentech assigns this port number. Change this entry to reflect the
# information you get from Paymentech.
#
# Note: The default port number, 5679, is the port for the Portal
#       credit-card simulator for batch transactions, answer_b, 
#       which you can use for testing
#========================================================================
END
	,"batch_port", "- dm_fusa batch_port $DM_FUSA{'answer_b_port'}"
	,"unsupported_description",  <<END
#========================================================================
# Unsupported Modem Options
#
# Note: Portal doesn't support managing Paymentech transactions through
#       a modem, but the Paymentech Data Manager can be configured to work
#       with a modem. Consult Paymentech if you want to experiment with
#       the modem option.
#========================================================================
END
	,"unsupported", 
"- dm_fusa modem_device /dev/cua/b
- dm_fusa modem_dial ATDT 9,1-603-893-0479 # Test Number"
	,"passwords_description", <<END
#========================================================================
# Presenter and submitter IDs and passwords
#
# For the entries below, enter the values supplied to you by Paymentech
# during testing:
#
#    pid     = presenter ID
#    pid_pwd = presenter password
#    sid     = submitter ID
#    sid_pwd = submitter password
#
# See your Paymentech documentation for more information.
#========================================================================
END
	,"passwords",
"- dm_fusa	pid		$DM_FUSA{'presenter_id'}
#- dm_fusa	pid_pwd		$DM_FUSA{'presenter_password'}
- dm_fusa	sid		$DM_FUSA{'submitter_id'}
#- dm_fusa	sid_pwd		$DM_FUSA{'submitter_password'}"
	,"merchant_ids_description", <<END
#========================================================================
# merchant ID and merchant number
#
# Associates a merchant name and currency with a merchant number that
# identifies a Paymentech customer.
#
# Paymentech supplies the merchant numbers when you set up an account.
#
# Each merchant ID has three parts:
#
#    mid_       = The prefix used by Portal; DO NOT change it.
#    <merchant> = Part of the merchant ID; it must match the fm_cust_pol
#                   merchant entry in the CM configuration file.
#    <currency> = The ISO standard number for the currency
#                   associated with this account.
#
# For example, if "merchant" is "psi" and the account uses US dollars,
# the merchant name is "mid_psi_840".
#
# You must define a merchant name and number for each currency you use
# with Paymentech.
#
# Note: Paymentech supplies a merchant number you can use for testing 
#       the service.
#========================================================================
END
	,"merchant_ids", 
"- dm_fusa	mid_".$DM_FUSA{'merchant_name'}."_124	050505			# Canadian dollars 
- dm_fusa	mid_".$DM_FUSA{'merchant_name'}."_250	050506			# French francs
- dm_fusa	mid_".$DM_FUSA{'merchant_name'}."_280	050507			# German marks
- dm_fusa	mid_".$DM_FUSA{'merchant_name'}."_826	050508			# Pounds sterling
- dm_fusa	mid_".$DM_FUSA{'merchant_name'}."_840	050509			# US dollars
- dm_fusa	mid_".$DM_FUSA{'merchant_name'}."_978	050510			# Euros"
	,"code_file_description", <<END
#========================================================================
# code_file
#
# Specifies the name and location of the file that maps Paymentech return
# codes to Portal transaction-results codes.
#
# The default name and location is [Portal_home]/sys/dm_fusa/fusa_codes.
#========================================================================
END
	,"code_file", "- dm_fusa code_file $DM_FUSA{'pin_conf_location'}/fusa_codes"
	,"connect_retrys_description", <<END
#========================================================================
# connect_retrys
#
# Specifies the number of times that the Paymentech DM retries a
# connection to Paymentech.
#
# If this entry is missing or disabled, the default value is 2.
# If you have problems connecting to Paymentech, increase the number
# of retries. You can use any number.
#========================================================================
END
	,"connect_retrys", "- dm_fusa connect_retrys $DM_FUSA{'connect_retrys'}"
	,"fusa_timeout_description", <<END
#========================================================================
# fusa_timeout
#
# Specifies the timeout value, in seconds, for getting a response from
# Paymentech for online authorizations.The default value is 600 seconds.
#========================================================================
END
	,"fusa_timeout", "- dm_fusa fusa_timeout $DM_FUSA{'fusa_timeout'}"
	,"fusa_batch_timeout_description", <<END
#========================================================================
# fusa_batch_timeout
#
# Specifies the timeout value, in seconds, for getting a response from
# Paymentech for batch scripts. The default value is 600 seconds.
#========================================================================
END
	,"fusa_batch_timeout", "- dm_fusa fusa_batch_timeout $DM_FUSA{'fusa_timeout'}"
	,"tempdir_description", <<END
#========================================================================
# temp_dir
#
# Specifies the directory where Portal creates temporary files for 
# processing credit-card transactions.
#========================================================================
END
	,"tempdir", "- dm_fusa temp_dir $DM_FUSA{'pin_conf_location'}/fusa_temp"
	,"fusamux_00", <<END
#************************************************************************
# fusamux configuration entries
#
# Use the entries below when you use the fusamux daemon to run multiple
# online credit-card transactions. To use these entries, remove the
# crosshatch (#) from the start of the line for each entry and set the 
# value for each entry for your system.
#************************************************************************
END
	,"fusamux_0port_description", <<END
#========================================================================
# fusamux_port
#
# Specifies the port on which the fusamux daemon listens.
#
# This is not the port number supplied by Paymentech, which you use for
# the online_port entry.
#========================================================================
END
	,"fusamux_0port", "#- fusamux fusamux_port $DM_FUSA{'fusamux_port'}"
	,"fusamux_online_port_description", <<END
#========================================================================
# fusamux_online_port
#
# Specifies the port number for online connections.
#
# Paymentech assigns this port number. Change this entry to reflect the
# information you get from Paymentech.
#========================================================================
END
	,"fusamux_online_port", "#- fusamux online_port $DM_FUSA{'fusamux_onlineport'}"
	,"fusamux_online_srvr_description", <<END
#========================================================================
# fusamux_online_srvr
#
# Specifies the IP address or host name for online connections.
#
# Paymentech assigns this address. Replace the "XXXX" with the address
# you get from Paymentech.
#
# Note: You must also change the online_srvr entry for dm_fusa to point
#       to the IP address or host name of the fusamux computer. See the 
#       guidelines for that configuration entry elsewhere in this 
#       configuration file.
#========================================================================
END
	,"fusamux_online_srvr", "#- fusamux online_srvr $DM_FUSA{'fusamux_onlinesrvr'}",
        ,"dmfusa05_sd00",  <<END
#************************************************************************
# Soft descriptors 
# 
# Use the four entries below for soft-descriptor information. This
# information appears on your customer's credit-card statement or
# checking-account statement (in the case of direct debit), and includes
# the company name, product line, or phone number.
# 
# You must contact Paymentech to confirm your soft descriptor values.
#************************************************************************
END
  ,"dmfusa05_sd01_01_sd_descriptor_flag_description", <<END
#========================================================================
# Soft-descriptor flag
#
# Indicates the presence of soft descriptors.
# 
# Change this value to 1 after you set up soft descriptors. In the entries
# below, you must use values that you have agreed upon with Paymentech.
#========================================================================
END
  ,"dmfusa05_sd01_01sd_descriptor_flag", "- dm_fusa  sd_descriptor_flag 0"
  ,"dmfusa05_sd02_01_sd_descriptor_entries_description",  <<END
#========================================================================
# Soft-descriptor entries
# 
# Each merchant ID has three parts:
# 
#    sd_        = The prefix used by Portal; DO NOT change it.
#    <merchant> = Part of the merchant ID; it must match the
#                   fm_cust_pol merchant entry in the CM configuration file.
#
#    The third part of the merchant ID is one of these three options:
#
#         dba   = Your DBA (doing business as), or the name the customer
#                  knows you by.
#         pdt   = Your product name.
#         phone = Your customer support line.
# 
# On the customer's statement, an asterisk separates the DBA and the
# product name. If this combined entry is longer than 22 characters
# (including spaces), it is truncated on the statement. In this
# 22-character-maximum line, the asterisk delimiter can appear in
# spaces 4, 8, or 13. For more information, see the Paymentech 
# specifications.
# 
# If you don't provide a phone number, the Paymentech city field is 
# used, showing the city where your headquarters is located. Your phone
# number can use all numbers, or a combination of numbers and letters.
# 
# For example, suppose <merchant> is psi, the DBA is MyFirm, the product
# is InternetSVC, and the customer service number is 800-555-1234. 
# With these values, the entries would be:
#
#    - dm_fusa   sd_psi_dba    MyFirm
#    - dm_fusa   sd_psi_pdt    InternetSVC
#    - dm_fusa   sd_psi_phone  800-555-1234
#
# In the entries below, replace the X strings with the appropriate
# information.
#========================================================================
END
  ,"dmfusa05_sd02_01_sd_descriptor_entries", 
"- dm_fusa 	sd_<merchant>_dba	      XXXXXX
- dm_fusa 	sd_<merchant>_pdt 	XXXXXX
- dm_fusa 	sd_<merchant>_phone	XXX-XXX-XXXX "
  ,"dmfusa_crypt_credit_security_code_description", <<END
#========================================================================
# crypt <encryption scheme tag>
#
# Associates a four byte tag with an encryption algorithm and secret
# key combination.
#
# The encryption algorithm is specified by naming the shared binary
# object that contains the code.
#
# The secret key is a string of characters enclosed in double quotes.
# The double quotes are not considered part of the secret key. Any
# character allowed in a C language string is allowed in the secret
# key string.
#
# The configurations below show an example for Solaris, an example for
# HP and an example for Windows NT. Notice the difference in shared
# binary object names which is necessiated by the underlying operating
# system conventions.
#
# Credit card and security code encryption are mandatory for dm_fusa.
# A crypt pin.conf entry MUST be defined.  
# For security reason, we recommend the customer to modify
# the sample crypt entry and use their own key string. 
#========================================================================
END
  ,"dmfusa_crypt_credit_security_code", "- crypt md5| $PIN_HOME/lib/libpin_crypt4qm.$LIBRARYEXTENSION \"Abracadabra dabracaabraasada!!!!\""
  ,"cc_token_enabled_description", <<END
#========================================================================
# cc_token_enabled
#
# Indicates if CC tokenization is enabled or not.
#
# By default this entry will be enabled. When enabled, the first request 
# to paymentech for a particular card will request for a token and store
# the same. All future transactions will be handled with the token.
#========================================================================
END
  ,"cc_token_enabled", "- dm_fusa cc_token_enabled 1"

);


$FUSA_SERVER_PINCONF_HEADER = <<END 
#************************************************************************
# Configuration File for the Answer Simulators for Transactions
# through the Paymentech Data Manager
#
#
# The entries below specify how the Paymentech Data Manager connects
# with the credit-card service simulator.
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

%FUSA_SERVER_PINCONF_ENTRIES = (
	"answer_0port_description", <<END
#***********************************************************************
# Configuration Entries for the Answer Simulator for Online (Single)
# Transactions (answer_s)
#
#
# The entries below specify how the Paymentech Data Manager connects
# with the credit-card service simulator.
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
#
#========================================================================
# port
#
# Specifies the port for the online answer simulator.
#
# The default port is 5678. This must match the entry for online_port
# in the configuration file for the Paymentech Data Manager.
#========================================================================
END
	,"answer_0port", "- answer_s port $DM_FUSA{'answer_s_port'}"
	,"answer_children_description", <<END
#========================================================================
# children
#
# Specifies the number of child processes.
#
# Use one child process for simulation.
#========================================================================
END
	,"answer_children", "- answer_s children $DM_FUSA{'answer_s_children'}"
	,"answer_s_code_description", <<END
#========================================================================
# s_code
#
# Specifies the security response for Visa CVV2 from the online simulator. 
#
# Enter the value you want the simulator to return for the credit-card
# verification (CVV) request for a Visa card transaction. For a list 
# of Visa CVV2 codes and their meanings, see the table at the end of 
# this file. The default value is "not tested (not processed)".
#
#========================================================================
END
	,"answer_s_code", "- answer_s s_code $DM_FUSA{'s_code'}"
	,"answer_v_code_description", <<END
#========================================================================
# v_code
#
# Specifies the authorization response from the online simulator. 
#
# You can use a general v_code setting, or you can use a specific
# credit-card or direct-debit account number for a specific response 
# to that account. These entries are in the format:
#
#    answer_s v_code_[account_number] [response_code]
#
# The following format can be used to set response specific MOP(VI, MC,
# AX, DI, JC, etc.)
#    answer_s v_code_[mop] [response_code]
#
# Response set for specific debit number will have more precedence than
# that the one set for MOP.
#
# For credit-card testing: you don't need an actual credit-card number,
# but you do need a number that meets certain criteria of a credit-card
# number, such as the prefix and number of digits. See the Paymentech
# specifications for more information.
# 
# For direct-debit testing: use any account number you want to simulate
# a response. Your number doesn't have to match the attributes of a
# checking-account number.
#
# Enter the value you want the simulator to return for an authorization
# request. For a list of response codes and their meanings, see the table
# at the bottom of this file. For a description of how the authorization
# codes map to Portal result codes, see the 
# [Portal_home]/sys/dm_fusa/fusa_codes file.
#
# The American Express CID (card ID) system doesn't return error codes. 
# To simulate a negative CID response, set the v_code to 401.
#========================================================================
END
	,"answer_v_code", 
"- answer_s v_code $DM_FUSA{'answer_s_vcode'}
- answer_s	v_code_4433111122223333	302
- answer_s	v_code_4387751111110	401"
        ,"answer_tls_enabled_description", <<END
#========================================================================
# answer_tls_enabled
#
# Specifies whether TLS will be enabled for Paymentech simulator
#
#    0 - TLS is disabled.
#    1 - TLS is enabled.
#
#========================================================================
END
        ,"answer_tls_enabled", "#- answer answer_tls_enabled $ENABLE_SSL"
	,"answer_avs_description", <<END
#========================================================================
# avs
#
# Specifies the address-verification system’s (AVS’s) response from the
# online simulator.
#
# Enter the value you want the simulator to return for an address-
# verification request. For a list of address-verification codes and
# their meanings, see the table at the bottom of this file.
#========================================================================
END
	,"answer_avs", "- answer_s avs $DM_FUSA{'avs_response'}"
	,"answer_b_0port_description", <<END
#************************************************************************
# Configuration Entries for the Answer Simulator for Batch
#	 Transactions (fdc_answer_b)
#************************************************************************
#
#========================================================================
# port
#
# Specifies the port for the batch answer simulator.
#
# The default port is 5679. This must match the entry for batch_port in
# the configuration file for the Paymentech Data Manager.
#========================================================================
END
	,"answer_b_0port", "- answer_b port $DM_FUSA{'answer_b_port'}"
	,"answer_b_children_description", <<END
#========================================================================
# children
#
# Specifies the number of child processes.
#
# Use one child process for simulation.
#========================================================================
END
	,"answer_b_children", "- answer_b children $DM_FUSA{'answer_b_children'}"
	,"answer_b_v_code_description", <<END
#========================================================================
# v_code
#
# Specifies the authorization response from the batch simulator. 
#
# You can use a general v_code setting, or you can use a specific
# credit-card or direct-debit account number for a specific response 
# to that account. These entries are in the format:
#
#    answer_b v_code_[account_number] [response_code]
#
# The following format can be used to set response specific MOP(VI, MC,
# AX, DI, JC, etc.)
#    answer_b v_code_[mop] [response_code]
#
# Response set for specific debit number will have more precedence than
# that the one set for MOP.
#
# For credit-card testing: you don't need an actual credit-card number, 
# but you do need a number that meets certain criteria of a credit-card 
# number, such as the prefix and number of digits. See the Paymentech 
# specifications for more information.
#
# For direct-debit testing: use any account number you want to simulate
# a response. Your number doesn't have to match the attributes of a
# checking-account number.
#
# Enter the value you want the simulator to return for an authorization
# request. For a list of response codes and their meanings, see the table
# at the end of this file. For a table that maps the authorization codes
# to Portal result codes, see the 
# [Portal_home]/sys/dm_fusa/fusa_codes file.
#========================================================================
END
	,"answer_b_v_code", 
"- answer_b v_code $DM_FUSA{'answer_b_vcode'}
- answer_b	v_code_5442986666666032	302 
- answer_b	v_code_4387751111110	401"
	,"answer_b_rfr_description", <<END
#========================================================================
# rfr
#
# Specifies the RFR response file.
#========================================================================
END
	,"answer_b_rfr", "- answer_b rfr $DM_FUSA{'pin_conf_location'}/rfr.file"
	,"reference_table", <<END
#************************************************************************
# Reference Tables for Paymentech Codes
#************************************************************************
#
#========================================================================
# Meaning of Paymentech Authorization Response Codes (v_code)
#
#    Code  Meaning
#
#    100 = Approved
#    201 = Invalid credit-card number
#    202 = Bad amount (either 0 or unreadable)
#    204 = Unknown error (check with Paymentech)
#    281 = Token Unavailable (Paymentech is unable to provide a token)
#    301 = Authorization network couldn't reach the issuing bank
#    302 = Insufficient funds
#    303 = Declined (reason not provided by issuer)
#    401 = Call (issuer wants to speak with cardholder)
#    402 = Default call (issuer wants telephone approval/declining)
#    501 = Pick up (issuer wants card returned)
#    502 = Lost or stolen card
#    522 = Expired card
#    530 = Do not honor
#    602 = Bad card (check with Paymentech)
#    605 = Invalid expiration date
#    606 = Invalid transaction type (check with Paymentech)
#    607 = Invalid amount
#    806 = Restricted card
#
#========================================================================
# Meaning of Paymentech AVS Codes
#
#    Code  Meaning
#
#    I1 = Valid 5-digit ZIP code, 4-digit ZIP code, and street address
#    I3 = Valid 5-digit ZIP code and street address; non-valid 4-digit ZIP
#    N1 = No address given
#    N2 = Bill-to address not usable  
#    IE = Non-valid AVS data 
#    I2 = Non-valid street address; valid 5-digit and 4-digit ZIP codes
#    I4 = Non-valid 4-digit ZIP code and street address; valid 5-digit ZIP
#    I5 = Non-valid 5-digit ZIP code; valid 4-digit ZIP and street address
#    I6 = Non-valid 5-digit ZIP code and street address; valid 4-digit ZIP
#    I7 = Non-valid 5-digit and 4-digit ZIP code; valid street address
#    I8 = Non-valid 5-digit ZIP code, 4-digit ZIP code, and street address
#    IU = Address information unavailable
#    ID = Issuer does not participate in AVS
#    IS = System unavailable or timeout
#    (two spaces) = AVS not performed
#
#========================================================================
# Mapping of Paymentech AVS Codes to Portal Charge Result Values
#
#    AVS Code         Portal Charge Result
#
#       I1          = PIN_CHARGE_RES_PASS
#       I3          = PIN_CHARGE_RES_PASS
#       N1          = PIN_CHARGE_RES_FAIL_ADDR_AVS
#       N2          = PIN_CHARGE_RES_FAIL_ADDR_AVS
#       IE          = PIN_CHARGE_RES_FAIL_ADDR_AVS
#       I2          = PIN_CHARGE_RES_FAIL_ADDR_LOC
#       I4          = PIN_CHARGE_RES_FAIL_ADDR_LOC
#       I5          = PIN_CHARGE_RES_FAIL_ADDR_ZIP
#       I6          = PIN_CHARGE_RES_FAIL_ADDR_ZIP
#       I7          = PIN_CHARGE_RES_FAIL_ADDR_ZIP
#       I8          = PIN_CHARGE_RES_FAIL_ADDR_ZIP
#       IU          = PIN_CHARGE_RES_SRVC_UNAVAIL
#       ID          = PIN_CHARGE_RES_SRVC_UNAVAIL
#    (two spaces)   = PIN_CHARGE_RES_FAIL_NO_ANS
#       IS          = PIN_CHARGE_RES_FAIL_NO_ANS
#    <unrecognized> = PIN_ERR_BAD_ARG
#========================================================================
END
  ,"simulation_level_description", <<END
#========================================================================
# simulation_level
#
# Choose the testing level:
#
#    0 = Return the assigned authorization response (v_code) and address
#          verification system (AVS) values.
#    1 = Return a specific account v_code (v_code_<account_number>)
#          assigned value and the avs assigned value.
#    2 = Return the v_code_<account_number> assigned value and simulate
#          checking the ZIP-code format.
#
# For default simulation level 0, use v_code 100 and avs I1
#========================================================================
END
  ,"simulation_level", "- answer simulation_level $DM_FUSA{'simulation_level'}"
  ,"simulation_wait_description", <<END
#========================================================================
# sim_wait 
#
# Specifies the simulated waiting time (in seconds) for handling
# no response. 
#
# Set this to a higher number than the fusa_timeout entry in the 
# Paymentech DM configuration file [Portal_home]/sys/dm_fusa/pin.conf.
#========================================================================
END
  ,"simulation_wait", "- answer sim_wait $DM_FUSA{'simulation_wait'}"
  ,"no_response_description", <<END
#========================================================================
# no_response 
#
# Specifies to return no response from the online simulator.
#
# Enter the account number for the simulator to match.
#
# For credit-card testing: you don't need an actual credit-card number, 
# but you do need a number that meets certain criteria of a credit-card 
# number, such as the prefix and number of digits. See the Paymentech 
# specifications for more information.
#
# For direct-debit testing: use any account number to simulate a response.
# Your number doesn't have to match the attributes of a checking-account
# number.
#
# When the account number is matched, the online simulator waits for
# sim_wait seconds. 
#========================================================================
END
  ,"no_response", "#- answer_s no_response $DM_FUSA{'acct_no_response'}"
  ,"drop_line_description", <<END
#========================================================================
# drop_line 
#
# Specifies to disconnect abruptly from the online simulator.
#
# Enter the account number for simulator to match. When the account number
# is matched, the online simulator closes the socket.
#
# For credit-card testing: you don't need an actual credit-card number, but
# you need a number that meets certain criteria of a credit-card number,
# such as the prefix and number of digits. See the Paymentech 
# specifications for more information.
# 
# For direct-debit testing: your number doesn't have to match the
# attributes of a checking-account number.
#========================================================================
END
  ,"drop_line", "#- answer_s drop_line $DM_FUSA{'drop_line'}"
  ,"answer_b_no_response_description", <<END
#========================================================================
# answer_b_no_response
#
# Specifies whether to return a response from the online simulator.
#
# To return no response, change the value to 1.
#========================================================================
END
  ,"answer_b_no_response", "- answer_b no_response $DM_FUSA{'answer_b_no_response'}"
  ,"answer_b_drop_line_description", <<END
#========================================================================
# answer_b_drop_line
#
# Specifies whether to disconnect abruptly from the online simulator.
#
# To disconnect abruptly, change the value to 1.
#========================================================================
END
  ,"answer_b_drop_line", "- answer_b drop_line $DM_FUSA{'answer_b_drop_line'}"
 );

%DM_FUSA_CM_PINCONF_ENTRIES = (
	"dm_fusa_dm_pointer_description", <<END
#========================================================================
# dm_fusa_dm_pointer
#========================================================================
END
	,"dm_fusa_dm_pointer", "- cm dm_pointer $DM_FUSA{'db_num'} ip $HOSTNAME $DM_FUSA{'port'}"
        ,"pol_minimum_refund_description", <<END
#========================================================================
# pol_minimum_refund
#
# Specifies the minimum refund amount.
#    2.00 = (Default)
#========================================================================
END
         ,"pol_minimum_refund", "-  fm_pymt_pol minimum_refund 2.00"
         ,"payment_batch_lock_description", <<END
#========================================================================
# payment_batch_lock
#
# Specifies whether to open a read/write transaction at the account 
# level or at batch level while doing the payments through Payment 
# tool. By default it is batch level. 
# Use 0 to lock at the account level or 1 to lock at the batch level. 
#========================================================================
END
         ,"payment_batch_lock", "- fm_pymt payment_batch_lock 1"
         ,"transaction_type_description", <<END
#========================================================================
# transaction_type 
#
# Electronic Commerce Indicator, defining the transaction type between 
# Paymentech DM and Paymentech. 
# 
# Supported values are: 
# 1 (Single Transaction mail/telephone order) 
# 2 (Recurring Transaction) 
# 7 (Non-SET Channel-encrypted) 
# 
# If the line is commented, Paymentech DM will take the default value 
# as BLANK. 
# 
# Note: Paymentech DM may not behave correctly for other transaction 
# type, other than above listed values. 
#
#========================================================================
END
         ,"transaction_type", "#- dm_fusa transaction_type 2"
	 ,"dm_dd_dm_pointer_description", <<END
#========================================================================
# dm_dd_dm_pointer
#========================================================================
END
	,"dm_dd_dm_pointer", "- cm dm_pointer $DD_DM{'db_num'} ip $HOSTNAME $DM_FUSA{'port'}"

);
