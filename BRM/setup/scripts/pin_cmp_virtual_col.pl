#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl

#=======================================================================
# @(#)$Id: pin_cmp_virtual_col.pl /cgbubrm_mainbrm.portalbase/5 2018/03/30 02:42:03 mkothari Exp $
#
# Copyright (c) 2013, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
#========================================================================

# If running stand alone, without pin_setup
if ( ! ( $RUNNING_IN_PIN_SETUP eq TRUE ) )
{
   require "./pin_res.pl";
   require "./pin_functions.pl";
   require "../pin_setup.values";

   &ReadIn_PinCnf( "pin_cnf_dm.pl" );

   &Configure_VirtCol_Cnf;
}

sub Configure_VirtCol_Cnf{
	local($PinConfFile) = $PIN_HOME."/apps/pin_virtual_columns/Infranet.properties";
       
        &Configure_Infranet("$PinConfFile");
	if (! -e $PinConfFile) {
		#
		# Adding configuration
		#
		if (open(PINCONFFILE, "> $PinConfFile")) {
			print PINCONFFILE "$VIRTCOL_PINCONF_HEADER\n\n";
			print PINCONFFILE "# Logging configuration\n";
			print PINCONFFILE "infranet.log.file = vcol.pinlog\n";
			print PINCONFFILE "infranet.log.level = 1\n";
			print PINCONFFILE "infranet.log.name = VCOL\n\n";

			print PINCONFFILE "# JDBC connection configuration\n";
			print PINCONFFILE "infranet.vcol.userid = $MAIN_DM{'db'}->{'user'}\n";
			print PINCONFFILE "infranet.vcol.dbname = $MAIN_DM{'db'}->{'alias'}\n\n";

			print PINCONFFILE "infranet.vcol.worker_threads = 10\n\n";

			print PINCONFFILE "infranet.pcp.ssl.enabled = false\n";
			print PINCONFFILE "infranet.pcp.ssl.wallet.location = /home/pin/opt/portal/BRM/wallet/client\n";
			print PINCONFFILE "infranet.pcp.ssl.wallet.filename = cwallet.sso\n";
			
			if($DB_SSL_MODE eq '2'){
				print PINCONFFILE "infranet.vcol.ssl.db.ssl.enabled = true\n";
				print PINCONFFILE "infranet.vcol.ssl.db.ssl.client_auth = true\n";
			}
			elsif($DB_SSL_MODE eq '1'){
				print PINCONFFILE "infranet.vcol.ssl.db.ssl.enabled = true\n";
			}
			else{
				print PINCONFFILE "infranet.vcol.ssl.db.ssl.enabled = false\n";
				print PINCONFFILE "infranet.vcol.ssl.db.ssl.client_auth = false\n";
			}
			print PINCONFFILE "infranet.vcol.ssl.db.ssl.truststore.filename = cwallet.sso\n";
			print PINCONFFILE "infranet.vcol.ssl.db.ssl.truststore.location = $DB_SSL_TRUST_STORE_LOCATION\n";
			print PINCONFFILE "infranet.vcol.ssl.db.ssl.keyStore.filename = cwallet.sso\n";
		        print PINCONFFILE "infranet.vcol.ssl.db.ssl.keyStore.location = $DB_SSL_KEY_STORE_LOCATION\n";

			close( PINCONFFILE );
		} else {
			print STDOUT "The file $PinConfFile could not be opened \n";
		}
		chmod(0640,$PinConfFile);
	}
}
1;
