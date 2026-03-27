#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# Copyright (c) 2023, 2024 Oracle and/or its affiliates.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the dm_kafka Component
#
#=============================================================

use Cwd;
use aes;

# If running stand alone, without pin_setup
if (!($RUNNING_IN_PIN_SETUP eq TRUE)) {
    require "./pin_res.pl";
    require "./pin_functions.pl";
    require "../pin_setup.values";

    &ConfigureComponentCalledSeparately($0);
}

require "./pin_modular_functions.pl";

#########################################
# Configure DM Kafka Infranet.properties files
#########################################
sub configure_dm_kafka_config_files {
    local (%DM) = %DM_KAFKA;
    local (%CM) = %MAIN_CM;
    local ($publish_db_num) = $DM_KAFKA{'db_num'};
    local ($publish_format) = "FLIST";
    local ($XMLFile);
    local ($i);
    local ($Current_Dir) = cwd();

    # This feature is currently supported only in Unix. This need not run on Windows.
    if ($^O =~ /win/i) {
        return;
    }

    &ReadIn_PinCnf("pin_cnf_dm_kafka.pl");

    # If the sys/cm/pin.conf is there, add the entries to it.
    # If not, add the entries to the temporary pin.conf file.
    if (-f $CM{'location'} . "/" . $PINCONF) {
        &ReplacePinConfEntries($CM{'location'} . "/" . $PINCONF, %DM_KAFKA_CM_PINCONF_ENTRIES);

        # Display a message current component entries are appended to cm/pin.conf file.
        &Output(STDOUT, $IDS_CM_PIN_CONF_APPEND_SUCCESS,
            $CurrentComponent,
            $CM{'location'} . "/" . $PINCONF);
    }
    else {
        &ReplacePinConfEntries("$TEMP_PIN_CONF_FILE", %DM_KAFKA_CM_PINCONF_ENTRIES);

        # Display a message saying to append this file to cm/pin.conf file.
        &Output(STDOUT, $IDS_APPEND_PIN_CONF_MESSAGE,
            $CM{'location'} . "/" . $PINCONF,
            $CurrentComponent,
            $TEMP_PIN_CONF_FILE);
    }

    #
    #  Configure payloadconfig_kafka_sync.xml with current values ...
    #
    $i = 0;
    open(XML_FILE, "+< $EAI{'eai_js_location'}/payloadconfig_kafka_sync.xml") || die("Can't open $EAI{'eai_js_location'}/payloadconfig$suffix.xml");
    @Array_XML = <XML_FILE>;
    seek(XML_FILE, 0, 0);

    while (<XML_FILE>) {
        $_ =~ s/Publisher DB.*/Publisher DB=\"$publish_db_num\" Format=\"$publish_format\"\>/i;
        $Array_XML[$i++] = $_;
    }
    seek(XML_FILE, 0, 0);
    print XML_FILE @Array_XML;
    print XML_FILE "\n";
    truncate(XML_FILE, tell(XML_FILE));
    close(XML_FILE);

    #
    # Configure dm_kafka/infranet.properties and payloadconfig_kafka_sync file.
    # Return value from Configure_EAI_Payload is ignored.
    #
    &configure_dm_kafka_properties();
    #&configure_aq_kafka_properties();
}

sub configure_dm_kafka_properties {

    &Configure_Infranet("$PIN_HOME/sys/dm_kafka/Infranet.properties");

    open(PROPFILE, "> $PIN_HOME/sys/dm_kafka/Infranet.properties") || die("Can't open Infranet.properties");
    print PROPFILE "# Infranet.properties file for dm_kafka.\n";
    print PROPFILE "# Contains configuration parameters for the DM Kafka Server.\n";
    print PROPFILE "\n";
    print PROPFILE "########################################################\n";
    print PROPFILE "# JS Configuration\n";
    print PROPFILE "########################################################\n";
    print PROPFILE "# java servers port #\n";
    print PROPFILE "infranet.server.portNr = 12010\n";
    print PROPFILE "# the log file that the java server will log msgs to\n";
    print PROPFILE "infranet.log.file=${PIN_LOG_DIR}/dm_kafka/dm_kafka.pinlog\n";
    print PROPFILE "# the name of the application that the java server will use in it's log msgs.\n";
    print PROPFILE "infranet.log.name=DMKafkaServer\n";
    print PROPFILE "# log level.\n";
    print PROPFILE "infranet.log.level=1\n";
    print PROPFILE "# Java Server mode\n";
    print PROPFILE "infranet.server.mode=JS_DM_EAI\n";
    print PROPFILE "# Prints out timing information for opcode calls.\n";
    print PROPFILE "# infranet.server.enabletimeinfo=yes \n";
    print PROPFILE "\n";
    print PROPFILE "########################################################\n";
    print PROPFILE "# DM EAI Configuration\n";
    print PROPFILE "########################################################\n";
    print PROPFILE "infranet.dm.eai.handler=com.portal.dm.eai.plugin.DMKafkaEaiHandler\n";
    print PROPFILE "infranet.dm.dbno=0.0.9.6 / 0\n";
    print PROPFILE "infranet.dm.name=DM-KAFKA-1\n";
    print PROPFILE "infranet.connection.pool.enable=true\n";
    print PROPFILE "infranet.connection.pool.size=64\n";
    print PROPFILE "\n";
    print PROPFILE "########################################################\n";
    print PROPFILE "# DM Kafka Configuration\n";
    print PROPFILE "########################################################\n";
    print PROPFILE "infranet.dm.kafka.configFile=dm_kafka_config.xml\n";
    print PROPFILE "infranet.json.buffer.encoding=base64\n";
    print PROPFILE "infranet.xml.buffer.encoding=base64\n";
    print PROPFILE "\n";
    print PROPFILE "########################################################\n";
    print PROPFILE "# SSL configuration\n";
    print PROPFILE "########################################################\n";
    print PROPFILE "# To  enable SSL, make sure to provide correct values for below config entries. e.g wallet location and filename etc.\n";
    print PROPFILE "infranet.pcp.ssl.enabled = false\n";
    print PROPFILE "# To set the ciphersuites to be used.You can specify multiple ciphers seperated by commas.\n";
    print PROPFILE "#infranet.pcp.ssl.handshake.ciphersuites = TLS_RSA_WITH_AES_128_CBC_SHA\n";
    print PROPFILE "# To enable SSL 2 way authentication\n";
    print PROPFILE "infranet.pcp.ssl.client_auth = false\n";
    print PROPFILE "# Oracle wallet location\n";
    print PROPFILE "infranet.pcp.ssl.wallet.location = $PIN_HOME/wallet/server\n";
    print PROPFILE "infranet.pcp.ssl.wallet.filename = cwallet.sso\n";

    close(PROPFILE);
    chmod(0640, "$PIN_HOME/sys/dm_kafka/Infranet.properties");
}

sub configure_aq_kafka_properties {

    local ( %DM ) = %MAIN_DM;
    
    &Configure_Infranet("$PIN_HOME/apps/aqkafkaconnector/Infranet.properties");

    open(INFILE,"+<$PIN_HOME/apps/aqkafkaconnector/Infranet.properties") || die ("Can't open the $PIN_HOME/apps/aqkafkaconnector/Infranet.properties $!\n");

    $i = 0;
    @Array_INFILE = <INFILE>;
    seek( INFILE, 0, 0 );
    while ( <INFILE> )
    {
        $_ =~ s/^\s*infranet\.aq\.kafka\.db\.hostname.*/infranet\.aq\.kafka\.db\.hostname = $MAIN_DM{'db'}->{'Host'}/i;
        $_ =~ s/^\s*infranet\.aq\.kafka\.db\.userid.*/infranet\.aq\.kafka\.db\.userid = $MAIN_DM{'db'}->{'user'}/i;
        $_ =~ s/^\s*infranet\.aq\.kafka\.db\.port.*/infranet\.aq\.kafka\.db\.port = $MAIN_DM{'db'}->{'port'}/i;
        $_ =~ s/^\s*infranet\.aq\.kafka\.db\.svcname.*/infranet\.aq\.kafka\.db\.svcname = $MAIN_DM{'db'}->{'alias'}/i;
    
        $Array_INFILE[$i++] = $_;

    }
    
    seek( INFILE, 0, 0 );
    print INFILE @Array_INFILE;
    print INFILE "\n";
    truncate( INFILE, tell( INFILE ) );
    close(INFILE);
    chmod(0640, "$PIN_HOME/apps/aqkafkaconnector/Infranet.properties");


}
