#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# 
# $Header: install_vob/install_odc/Server/ISMP/Portal_Base/scripts/pin_cmp_billing.pl /cgbubrm_mainbrm.portalbase/2 2017/08/02 09:20:58 mkothari Exp $
#
# pin_cmp_billing.pl
# 
# Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
#
#============================================================= 

use Cwd;

# If running stand alone, without pin_setup
if ( ! ( $RUNNING_IN_PIN_SETUP eq TRUE ) )
{
   require "pin_res.pl";
   require "pin_functions.pl";
   require "../pin_setup.values";

   &ConfigureComponentCalledSeparately ( $0 );
}


#####
#
# Configure pin_billd files
#
#####
sub configure_billing_config_files {
  local( %CM ) = %MAIN_CM;
  local( %DM ) = %MAIN_DM;
  local ( $TEMP ) = $CurrentComponent;

  &ReadIn_PinCnf( "pin_cnf_mta.pl" );
  $PIN_TB_PINCONF_HEADER = $MTA_PINCONF_HEADER;

  $MAIN_CM{'login_name'} = "bill_inv_pymt_sub";
  $MAIN_CM{'user_id'} = "412";
  &ReadIn_PinCnf( "pin_cnf_ar_taxes.pl" );
  &ReadIn_PinCnf( "pin_cnf_pin_bill.pl" );
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_pin_remit.pl" );
  &ReadIn_PinCnf( "pin_cnf_pin_bulk.pl" );
  &ReadIn_PinCnf( "pin_cnf_rate_change.pl" );
  &ReadIn_PinCnf( "pin_cnf_monitor_balance.pl" );

  # Create pin.conf entry in the pin_remit directory
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%PIN_REMIT_PINCONF_ENTRIES );
  &Configure_PinCnf( $BILLING{'remit_location'}."/".$PINCONF,
                     $PIN_REMIT_PINCONF_HEADER,
                     %PIN_REMIT_PINCONF_ENTRIES );

  $MAIN_CM{'login_name'} = "rerating";
  $MAIN_CM{'user_id'} = "407";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  # Add CM entries and pin_rate_change entries
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%PIN_RATE_CHANGE_PINCONF_ENTRIES );

  # Create pin.conf entry in the pin_rate_change directory
  &Configure_PinCnf( $BILLING{'rate_change_location'}."/".$PINCONF,
                     $PIN_RATE_CHANGE_PINCONF_HEADER,
                     %PIN_RATE_CHANGE_PINCONF_ENTRIES );

  $MAIN_CM{'login_name'} = "bill_inv_pymt_sub";
  $MAIN_CM{'user_id'} = "412";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  # Add CM entries and pin_billd entries
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%PIN_BILLD_PINCONF_ENTRIES );

  # Create pin.conf entry in the pin_billd directory
  &Configure_PinCnf( $BILLING{'location'}."/".$PINCONF,
                     $PIN_BILLD_PINCONF_HEADER,
                     %PIN_BILLD_PINCONF_ENTRIES );

  &ReadIn_PinCnf( "pin_cnf_araframework.pl" );
  &AddPinConfEntries( $BILLING{'location'}."/".$PINCONF, %RA_ENABLE_ERA_PINCONF_ENTRIES );

  $MAIN_CM{'login_name'} = "billing";
  $MAIN_CM{'user_id'} = "402";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  # Add MTA entries and trial billing entries
  &AddArrays( \%MTA_PINCONF_ENTRIES, \%PIN_TB_PINCONF_ENTRIES );

  # Add CM entries and trial billing entries
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%PIN_TB_PINCONF_ENTRIES );

  # Create pin.conf entry in the pin_bill_trial directory
  &Configure_PinCnf( $TB{'location'}."/".$PINCONF,
                     $PIN_TB_PINCONF_HEADER,
                     %PIN_TB_PINCONF_ENTRIES );

  &AddPinConfEntries( $TB{'location'}."/".$PINCONF, %RA_ENABLE_ERA_PINCONF_ENTRIES );

  $CurrentComponent = "pin_bulk_adjust";
  $MAIN_CM{'login_name'} = "acct_recv";
  $MAIN_CM{'user_id'} = "408";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_mta.pl" );
  $CurrentComponent = $TEMP;

  # Add MTA entries and bulk adjustment entries
  &AddArrays( \%MTA_PINCONF_ENTRIES, \%PIN_BULK_PINCONF_ENTRIES );

  # Add pin_billd entries to bulk adjustment entries
  &AddArrays(\%CONNECT_PINCONF_ENTRIES, \%PIN_BULK_PINCONF_ENTRIES );

  # Create pin.conf entry in the pin_bulk directory
  &Configure_PinCnf( $BILLING{'bulk_location'}."/".$PINCONF,
                     $PIN_BULK_PINCONF_HEADER,
                     %PIN_BULK_PINCONF_ENTRIES );

  # Create pin.conf entries for pin_monitor application
  $CurrentComponent = "pin_monitor";
  $MAIN_CM{'login_name'} = "cust_mgnt";
  $MAIN_CM{'user_id'} = "406";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_mta.pl" );
  $CurrentComponent = $TEMP;

  # Add MTA entries and pin monitor balance entries
  &AddArrays( \%MTA_PINCONF_ENTRIES, \%PIN_MONITOR_BALANCE_PINCONF_ENTRIES );

  # Add CM entries and pin_monitor_balance entries
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%PIN_MONITOR_BALANCE_PINCONF_ENTRIES );

  # Create pin.conf entry in the pin_monitor directory
  &Configure_PinCnf( $BILLING{'monitor_location'}."/".$PINCONF,
                     $PIN_MONITOR_BALANCE_PINCONF_HEADER,
                     %PIN_MONITOR_BALANCE_PINCONF_ENTRIES );

# Create entries for the pin_bill_handler
  $CurrentComponent = "pin_bill_handler";
  $MAIN_CM{'login_name'} = "java_client";
  $MAIN_CM{'user_id'} = "409";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_mta.pl" );
  $CurrentComponent = $TEMP;

  # Add MTA entries and CM entries
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%MTA_PINCONF_ENTRIES );

  # Create pin.conf entry in the pin_bill_handler directory
  &Configure_PinCnf( $BILLING{'bill_handler_location'}."/".$PINCONF,
                     $MTA_PINCONF_HEADER,
                     %MTA_PINCONF_ENTRIES );

  # Create entries for the pin_balance_transfer
  $CurrentComponent = "pin_balance_transfer";
  $MAIN_CM{'login_name'} = "payments";
  $MAIN_CM{'user_id'} = "404";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_mta.pl" );
  $CurrentComponent = $TEMP;

  # Add MTA entries and CM entries
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%MTA_PINCONF_ENTRIES );

  # Create pin.conf entry in the pin_balance_transfer directory
  &Configure_PinCnf( $BILLING{'balance_transfer_location'}."/".$PINCONF,
                     $MTA_PINCONF_HEADER,
                     %MTA_PINCONF_ENTRIES );

  $MAIN_CM{'login_name'} = "load_utils";
  $MAIN_CM{'user_id'} = "413";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  # Add CM entries and pin_ar_taxes entries
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%PIN_AR_TAXES_PINCONF_ENTRIES );

  if ( ! -e "$PIN_HOME/apps" ){
   mkdir ("$PIN_HOME/apps", 0755) || die "Unable to create $PIN_HOME/apps directory";
  }
  if ( ! -e "$PIN_HOME/apps/pin_ar_taxes" ){
   mkdir ("$PIN_HOME/apps/pin_ar_taxes", 0755) || die "Unable to create $PIN_HOME/apps/pin_ar_taxes directory";
  }

  # Create pin.conf entry in the pin_ar_taxes directory
  &Configure_PinCnf( $BILLING{'ar_taxes_location'}."/".$PINCONF,
                     $PIN_AR_TAXES_PINCONF_HEADER,
                     %PIN_AR_TAXES_PINCONF_ENTRIES );
  $MAIN_CM{'login_name'} = $CM{'login_name'};
  $MAIN_CM{'user_id'} = $CM{'user_id'};
}
1;
