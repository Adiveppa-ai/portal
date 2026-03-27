# Copyright (c) 2021 Oracle Corporation and/or its affiliates. All rights reserved.

The following document contains details about all the sample Grafana dashboards included as part of the BRM installation:

1. BRM Services Dashboard:
	a. BRM Service Tracking
	b. BRM Service Status
	c. Memory Usage - BRM Services

2. CM Dashboard:
	
	a. Opcodes
		i. Top 10 Opcode Calls
		ii. Top 5 Opcode Errors
		iii. Top 5 Opcode Execution Time
		iv. Opcode - PCM_OP_READ_OBJ Error Alert
	
	b. CPU and Memory Usage
		i. Opcode level System CPU execution time
		ii. Opcode level User CPU execution time
		iii. Opcode System CPU - CM

3. DM Oracle:

	a. Opcodes
		i. Top 5 Opcode Calls
		ii. Top 5 Opcode Errors
		iii. Top 5 Opcode Execution Time
	
	b. CPU and Memory Usage
		i. Opcode level System CPU execution time
		ii. Opcode level User CPU execution time
		iii. Opcode System CPU - DM Oracle


4. Batch Controller:
	a. Total Loaded Class Count
	b. Open File Descriptor Count
	c. Buffer Pool Memory Used
	d. Heap Memory Used
	e. Memory Pool Used
	f. Process CPU Time
	h. Max Non Heap Memory Used
	i. Max Heap Memory Used
	j. Memory Pool Used Max
	k. Garbage Collector - Last Info Duration

5. EAI JS:
	a. Java Server Opcode Metrics
	b. Successful and Failed Opcode Count
	c. Memory Pool Used
	d. Heap Memory Used
	e. Non Heap Memory Used
	f. Process CPU Time
	g. Buffer Pool Memory Used 
	h. Max Non Heap Memory Usage
	i. Max Heap Memory Usage
	j. Garbage Collector - Last Info Duration

6. DM Oracle Shared Memory:
	a. Shared Memory
			i. Shared Memory - High Water Mark
			ii. Shared Memory - High Water Mark (BigSize)
			iii. Shared Memory Used (Current)
			iv. Shared Memory Used (Current-BigSize)
			v. Shared Memory Used (Max)
			vi. Shared Memory Used (Max-BigSize)
    b.Front and Back End Details
			i. DM Front End and Back End Operations Count
			ii. DM Front End and Back End Transactions Count
			iii. Back End Ops Error Count
			iv. Back End Transaction Error Count

7. REM:
       a. Metrics
                 i.    Total Updater in Milli Seconds
                 ii.   Total Loaded
                 iii.  Total Failure in Updater
                 iv.   Total Failure in PreUpdater
                 v.    Updater Total
                 vi.   PreUpdater Total
                 vii.  Total Load Time in Milli Seconds
                 viii. Total Failure in Loading
                 ix.   Total Pre Updater Time in Milli Seconds
                 x.    Total Number of Loaded Events
                
       b. TableMetrics
                      i.   FailedTotal
                      ii.  FilesTotal
                      iii. RowsLoadedTotal
                      iv.  LoadMillisTotal

          TableMetrics are generated for the following tables.
                      i.   event_bal_impacts_t
                      ii.  event_dlay_sess_tlcs_t
                      iii. event_dlyd_session_tlco_gsm_t
                      iv.  event_essentials_t
                      v.   event_t
                      vi.  event_dlyd_session_tlco_gprs_t
