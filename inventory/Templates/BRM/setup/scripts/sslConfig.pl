#!/usr/local/bin/perl
# 
# $Header: install_vob/nginstall/components/BRMServer/sslConfig.pl /cgbubrm_mainbrm.portalbase/1 2017/08/02 09:20:59 mkothari Exp $
#
# sslConfig.pl
# 
# Copyright (c) 2023, Oracle and/or its affiliates. All rights reserved.
#
#    NAME
#      sslConfig.pl - <one-line expansion of the name>
#
#    DESCRIPTION
#      <short description of component this file declares/defines>
#
#    NOTES
#      <other useful comments, qualifications, etc.>
#
#    MODIFIED   (MM/DD/YY)
#    mkothari    08/02/17 - Creation
# 
use Env;

if(!($ARGV[0] eq '0' || $ARGV[0] eq '1' || $ARGV[0] eq '2' || $ARGV[0] eq 'help')) {
        print "Invalid Option !!! \n";
        exit;
}

# disable SSL
if($ARGV[0] eq '0') {
	`perl -i -pe 's/enable_ssl\ *2/enable_ssl 0/g' $PIN_HOME/sys/cm/pin.conf`;
        system(" find $PIN_HOME -type f -name pin.conf | xargs perl -i -pe 's/enable_ssl\ *1/enable_ssl 0/g' ");
        system(" find $PIN_HOME -type f -name Infranet.properties | xargs perl -i -pe 's/infranet.pcp.ssl.enabled\ *=\ *true/infranet.pcp.ssl.enabled = false/g' ");
        if(-e "$IFW_HOME/pin.conf") {
            system(" find $IFW_HOME -type f -name pin.conf | xargs perl -i -pe 's/enable_ssl\ *1/enable_ssl 0/g' ");
        }
}

# enable SSL
if($ARGV[0] eq '1') {
	`perl -i -pe 's/enable_ssl\ *2/enable_ssl 1/g' $PIN_HOME/sys/cm/pin.conf`;
        system(" find $PIN_HOME -type f -name pin.conf | xargs perl -i -pe 's/enable_ssl\ *0/enable_ssl 1/g' ");
        system(" find $PIN_HOME -type f -name Infranet.properties | xargs perl -i -pe 's/infranet.pcp.ssl.enabled\ *=\ *false/infranet.pcp.ssl.enabled = true/g' ");
        if(-e "$IFW_HOME/pin.conf") {
            system(" find $IFW_HOME -type f -name pin.conf | xargs perl -i -pe 's/enable_ssl\ *0/enable_ssl 1/g' ");
        } 
}

if($ARGV[0] eq '2') {
        my @comp=('dm_oracle','dm_aq','dm_ifw_sync','dm_eai','dm_invoice','dm_ldap','dm_prov_telco','dm_fusa','dm_email','dm_vertex','eai_js','formatter');
                        `perl -i -pe 's/enable_ssl\ *1/enable_ssl 2/g' $PIN_HOME/sys/cm/pin.conf`;
                        `perl -i -pe 's/enable_ssl\ *0/enable_ssl 2/g' $PIN_HOME/sys/cm/pin.conf`;
        foreach $comp (@comp) {
                if(-e "$PIN_HOME/sys/$comp/pin.conf") {
                        `perl -i -pe 's/enable_ssl\ *1/enable_ssl 0/g' $PIN_HOME/sys/$comp/pin.conf`;
                } elsif (-e "$PIN_HOME/sys/$comp/Infranet.properties") {
                         `perl -i -pe 's/infranet.pcp.ssl.enabled\ *=\ *true/infranet.pcp.ssl.enabled = false/g' $PIN_HOME/sys/$comp/Infranet.properties`;
                }
        }
        if(-e "$IFW_HOME/pin.conf") {
            system(" find $IFW_HOME -type f -name pin.conf | xargs perl -i -pe 's/enable_ssl\ *1/enable_ssl 0/g' ");
        }
}

if($ARGV[0] eq 'help') {
        print "perl $0 0 -> Disables SSL \n";
        print "perl $0 1 -> Enables SSL \n";
        print "perl $0 2 -> Enables SSL between clients to CM and Disables SSL between CM to DM/EM\n";
}
