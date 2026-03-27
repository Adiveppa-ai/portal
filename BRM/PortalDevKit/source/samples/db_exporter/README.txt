# Copyright (c) 2021 Oracle Corporation and/or its affiliates. All rights reserved.

Steps to deploy DB_exporter for ORACLE DATABASE :

1. Pre-requisite : Oracle DB Instant Client Version should be 18.5.0.0.0 or greater versions.

2. Copy/use "default-metrics.toml" file which has BRM related queries.

3. Steps :

    a. Install oracledb_exporter ("oracledb_exporter.0.2.9-ora18.5.linux-amd64.tar.gz" )
    b. Replace the "default-metrics.toml" file present inside the "oracledb_exporter.0.2.9-ora18.5.linux-amd64" folder with the above file.
    c. Set the LD_LIBRARY_PATH to use the DB Client.
          setenv LD_LIBRARY_PATH <PATH where the DB Client is installed>:$LD_LIBRARY_PATH
          ex : setenv LD_LIBRARY_PATH /pinhome/pin775/monitoring/DBClient/instantclient_18_5:$LD_LIBRARY_PATH

    d. Set the DB Details , make sure that DB is able to connect 
          setenv DATA_SOURCE_NAME <USERNAME>/<PASSWORD>@<TNS_NAME>
    e. Configure OracleDB_Exporter port in the prometheus.yml.
	
          - job_name: 'oracledbexporter'
          static_configs:
          - targets: ['<HOSTNAME>:9161']

    f. Start the oracledb_exporter
           oracledb_exporter --log.level error --web.listen-address <HOSTNAME>:9161
    g. Check the Oracledb_exporter metrcis here : http://<HOSTNAME>:9161/metrics 
    h. List of parameters gets exposed in the metrics are :
	
           oracledb_brm_stream_value
           oracledb_brm_version_value
           oracledb_size_of_audit_tables_value
           oracledb_sessions_value
           oracledb_brm_event_part_value
           oracledb_brm_bill_count_value
           oracledb_brm_invoices_day_count_value
		   
    i. Create New Dashboards and Panels by adding DB metrics parameters , Then DB related graphs can be displayed in Grafana

