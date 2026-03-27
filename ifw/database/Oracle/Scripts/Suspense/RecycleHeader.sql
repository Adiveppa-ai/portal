SELECT 'BATCH_ID='||decode(recycle_mode, 1, 'RECYCLE_', 2, 'TEST_RECYCLE_')||obj_id0||chr(9)||'EVENT_TYPE='||recycle_mode from susp_usage_recycle_t where obj_id0 = ${RECYCLE_JOB_ID}
