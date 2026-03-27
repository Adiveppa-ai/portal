#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_eai_js.pl /cgbubrm_mainbrm.portalbase/1 2018/03/30 02:42:04 mkothari Exp $ 
# 
# Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the EAI Framework JS Component
#
#=============================================================


use Cwd;

# If running stand alone, without pin_setup
if ( ! ( $RUNNING_IN_PIN_SETUP eq TRUE ) )
{
   require "./pin_res.pl";
   require "./pin_functions.pl";
   require "./pin_modular_functions.pl";
   require "../pin_setup.values";

   &ConfigureComponentCalledSeparately ( $0 );
}


#####
#
# Configure EAI pin.conf files
#
#####
sub configure_eai_js_config_files {
  #
  # Configure EAI_JS/infranet.properties and payloadconfig file.
  # Return value from Cofigure_EAI_Payload is ignored.
  #
  require "./pin_modular_functions.pl";
  &Configure_EAI_Payload ("payloadconfig.xml",
			  "payloadconfig_MergedWithEAI.xml",
			  $EAI{'db_num'},
			  "XML");
}
