CREATE OR REPLACE PROCEDURE install_rel_monitor wrapped 
a000000
367
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
7
1e86 5b4
tiT56kDkjY4V6RNnbXPwhAfUZggwgz2TMUiMWo6Q6sHVuf1homAE2itvgR0t9mhayd6nWRny
oC7Td8nzQEHeJiQ/nhg91Le0KYkFNASU6ZDHcjtq7XBVUOgRyf3nNHC3Vx4qSlUqM2rdDBUE
FE7hpohAyXAMRQ/KeirIkfrsnu0m6OynGqMOg5cAZY8ztnEYrMp0u+W6kT2iQGwKTnMDlX5h
Jj7n9jwXkXDSV+kjy6b4SIgq+8l9CLJu1DFiKDDfunDrCVZ9gSMo8X9zVojgtfIvOdJlk15/
wTtt4D/3ce2Ax5NsnaabDxBcA2ecXH4ex3o9juletRr8DoAxoEcinKFa21klstxXvKMjfKbT
FEwb2n1RAFMWy01KOerTHZyA48pbN4sGULAXygpv7O/WB90ITE3O0EavqZj2Vl8cs3cbDPoY
rMnAYRGyPUHqXWt/OaV4OChCUUefFNJ8FDGiVCWBAnrXgqxOIYGY3y8occZAmHmAnFcPsdFW
C7GhNHypSca6mNXOxgyHhXoXtjnE3a9yT3A/k5GeTnCI36t3Usoyn7+zCsexPtFVY1iso/1z
NaO0hUa83cHEUm47cuPgk5eBRMIvxqSwzWvOatOqa6GCxT7VEVLV9eiPhtNu/5GZP0ysHjl7
6aVqva4IsolVG4hvgjFkOsXA2BdDryGTOK7URJ8cf//fegNGmc/NZQkDVO4ZWatTik9irHWh
h56HeZ/JzuDiEnmCQJcoZGC2vHlSPJvQAhOhhD9hgw8oIKK8I1OCjod2wYfZRnJP0XUtQ2Cx
hsDrzOS2frz6uG73Ta00nN1b9X5ctfnoyfBHuIZdhRs7V6hVgVU1TJ/T2tkgh6VfnJbcpYoc
d0gsJbi7j4mQeD8YhJ1InQwqFSMRvp+QyvD8N42Yk9TBGYy7npvVE4EZCkCDlSC/3KBt+qTf
NHcLeBhqY5gxdovi/lAOO3Q7ua2yCPGivOeQjf0DCzWY7F4DDkw5O8Stbcyn09qjrb1eq0ID
UsCroH3rn8d1swQPZcFn9rX4rW68+YrUzhnmd02EIGKERO80wLasI3CUe9jTeYQ1JJ7tlDMr
5kw401GNLDds1eMhpxj/hCtjpTPEURRoq3tqe6Dvxsana2akOgeApaXRHVB36iXS/TEKOoH1
T4WQNSOvl3PEupHW9z3fJrvaCNDvNJ+JVcVT0Z15MvWENQT1WFBM2rNAfaKd3E4vGiKH4gbo
7w8GfBA/9CUadfXUStiUEj3xLF2FrK9hbNoJQjxBVmrkLF7C5arZd66xNvmYEm6W0HzJtvE0
ib4IvyCh3Kqi8J012woK+w0FtrORA/bdwMpRlp5XCM/Eq3G3SL4A5uhjQsR3HBmk2gv4YfUB
CcN5XPngv9q+6cnZ//h43ZOYRZQ8ZMSf2pcAs81t5R4ourzaTawnr2TPyiHnyXf5zijrl9oj


/
EXEC install_rel_monitor;
DROP PROCEDURE install_rel_monitor;
CREATE OR REPLACE TRIGGER monitor_rel_status_change
   AFTER INSERT OR UPDATE
   ON batch_t
   REFERENCING NEW AS NEW OLD AS OLD
   FOR EACH ROW
DECLARE
   v_descr        VARCHAR2(100) := NULL;
   v_prev_status  INTEGER       := NULL;
   v_cleanup      INTEGER       := 0;
   CURSOR rms_cv(poid IN rel_monitor_summary_t.poid_id0%TYPE) IS
      SELECT rms.num_cdrs,
             rms.elapsed,
             rms.descr
        FROM rel_monitor_summary_t rms
       WHERE rms.poid_id0 = poid;
   v_service_type VARCHAR2(255) := NULL;
   v_num_cdrs     INTEGER       := 0;
   v_preproc_t    NUMBER        := 0;
   v_load_t       NUMBER        := 0;
   v_preupdate_t  NUMBER        := 0;
   v_update_t     NUMBER        := 0;
   v_stage        VARCHAR2(100) := NULL;
BEGIN
   IF :new.poid_type = '/batch/rel' THEN
      
      
      
      v_stage := 'INSERT rel_monitor_detail_t';
      INSERT INTO rel_monitor_detail_t
           VALUES (:new.poid_id0, LOCALTIMESTAMP, NVL(:old.status, -1), :new.status);
      
      
      
      v_stage := 'SELECT rel_tracking_change_t';
      BEGIN
         SELECT descr, status_from, cleanup
           INTO v_descr, v_prev_status, v_cleanup
           FROM rel_tracking_change_t
          WHERE status_to = :new.status
            AND status_from = NVL(:old.status, -1)
            AND NVL(:old.status, -1) <> :new.status; 
      EXCEPTION
         WHEN NO_DATA_FOUND THEN
            v_descr := NULL;
            v_prev_status := NULL;
            v_cleanup := 0;
      END;
      
      
      
      
      IF v_descr IS NOT NULL THEN
         v_stage := 'INSERT rel_monitor_summary_t';
         INSERT INTO rel_monitor_summary_t
            SELECT :new.poid_id0,
                   v_descr,
                   LOCALTIMESTAMP,
                   EXTRACT(HOUR from (LOCALTIMESTAMP - rmd.tstamp)) * 3600 +
                   EXTRACT(MINUTE from (LOCALTIMESTAMP - rmd.tstamp)) * 60 +
                   EXTRACT(SECOND from (LOCALTIMESTAMP - rmd.tstamp)),
                   br.num_total_records,
                   DECODE(
                      br.num_total_records, 0, 0,
                      br.num_total_records /
                        ((EXTRACT(HOUR from LOCALTIMESTAMP - rmd.tstamp)*3600) +
                         (EXTRACT(MINUTE from LOCALTIMESTAMP - rmd.tstamp)*60) +
                          EXTRACT(SECOND from LOCALTIMESTAMP - rmd.tstamp))
                   )
              FROM batch_rel_t br,
                   rel_monitor_detail_t rmd
             WHERE br.obj_id0 = :new.poid_id0
               AND br.obj_id0 = rmd.poid_id0
               AND rmd.to_status = v_prev_status
               AND rmd.to_status <> rmd.from_status; 
      END IF;
      
      
      
      
      IF v_cleanup <> 0 THEN
         
         
         
         v_num_cdrs := 0;
         v_preproc_t := 0;
         v_load_t := 0;
         v_preupdate_t := 0;
         v_update_t := 0;
         FOR rms_rec IN rms_cv(:new.poid_id0) LOOP
            IF v_num_cdrs = 0 THEN v_num_cdrs := rms_rec.num_cdrs; END IF;
            IF rms_rec.descr = '1-Preprocess' THEN v_preproc_t := rms_rec.elapsed; END IF;
            IF rms_rec.descr = '2-SQLLoader' THEN v_load_t := rms_rec.elapsed; END IF;
            IF rms_rec.descr = '3-PreUpdater' THEN v_preupdate_t := rms_rec.elapsed; END IF;
            IF rms_rec.descr = '4-Updater' THEN v_update_t := rms_rec.elapsed; END IF;
         END LOOP;
         
         
         
         BEGIN
            v_stage := 'SELECT batch_rel_t';
            SELECT SUBSTR(myfile, 1, INSTR(myfile, '_', 1) - 1)
              INTO v_service_type
              FROM (SELECT SUBSTR(br.input_file_name, INSTR(br.input_file_name, '/BRMCDR_', -1) + 8) AS myfile
                      FROM batch_rel_t br
                     WHERE br.obj_id0 = :new.poid_id0);
         EXCEPTION
            WHEN OTHERS THEN
               v_service_type := '';
         END;
         
         
         
         BEGIN
             v_stage := 'SELECT rel_monitor_cumulative_t';
             INSERT INTO rel_monitor_cumulative_t (service_type, num_files, num_cdrs, preproc_time, load_time, preupdate_time, update_time)
                VALUES (v_service_type, 1, v_num_cdrs, v_preproc_t, v_load_t, v_preupdate_t, v_update_t);
         EXCEPTION
            WHEN DUP_VAL_ON_INDEX THEN
               v_stage := 'UPDATE rel_monitor_cumulative_t';
               UPDATE rel_monitor_cumulative_t
                  SET num_files = num_files + 1,
                      num_cdrs = num_cdrs + v_num_cdrs,
                      preproc_time = preproc_time + v_preproc_t,
                      load_time = load_time + v_load_t,
                      preupdate_time = preupdate_time + v_preupdate_t,
                      update_time = update_time + v_update_t
                WHERE service_type = v_service_type;
         END;
         
         
         
         v_stage := 'DELETE rel_monitor_detail_t';
         DELETE rel_monitor_detail_t
          WHERE poid_id0 = :new.poid_id0;
      END IF;
   END IF;
EXCEPTION
  WHEN OTHERS THEN
     RAISE_APPLICATION_ERROR(-20000,
         'ERROR updating rel-monitor: poid_id0[' || :new.poid_id0 || '] ' ||
         'status[' || :old.status||'] -> [' || :new.status || ']', TRUE);
END monitor_rel_status_change;
/
show errors;
exit;
