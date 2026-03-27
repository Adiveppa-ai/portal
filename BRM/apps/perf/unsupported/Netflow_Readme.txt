continuus file information --- %full_filespec: Netflow_Readme.txt~2:ascii:1 %

    Instruction for running NetFlow Manager

    Netflow manager consists from 2 major pieces: collecting data and billing.
    There is no difference in billing procedure assosiated with Neflow Manager,
    billing will automaticaly pick-up netflow events and bill them. So main 
    efforts should be directed to collect data and populate them into Netflow 
    events. The following steps should be performed to test Netflow collecting.

    1. Install Infranet, make sure optional Netflow package installed.
    2. Run regular Infranet setup. Go in ~/setup directory and run pin_setup.
    3. Go in directory ~/setup/scripts and run script "setup_netflow".
       It will change rates, impact categories and price list accordingly 
       Netflow recommendations.
    4. Create new netflow accounts using pin_loader:

       pin_loader -Q "Netflow Plan" -n 10 -U netaccount%d

       Number of created accounts could be different from 10 , but pattern 
       "netaccount" we use in the next step script. 
    5. Attach known ip addresses to created accounts using Perl script 
    attach_netflow_ipaddrs. Usually this step executed from DM computer. 
    The first 4 lines in the script are configuration parameters which 
    should be adjusted to properly connect to DB:
  
    $CONF_OWNER="pin";
    $CONF_PASSWD="pin";
    $CONF_DBNAME="defiant";
    $ORACLE_VERSION="Oracle8";

    6. Go in directory ~/apps/pin_nfcd. Run testnap to check proper 
    connection with CM. Thereafter run script "gen_collect.pl" to generate
    data flow files. 2 configuration parameters script could affect performance:

      $NUM_THREADS = 8;
      $NUM_LINES = 10000;
      
    Paraameter NUM_THREADS actually set number of data files to generate,
    and parameter NUM_LINES set number of records in each file. The script 
    will generate proper environment and data flow files accordingly SYSCO 
    standards by using script "callrecord" and "template t1.crt".
    
    7. Start Netflow collector. We can time this operation:

       time start_collector


