/* Copyright (c) 2021 Oracle and/or its affiliates. All rights reserved */
/* ---------------------------------------------------------------------- */
/* BATCH_REL_ZIP_FILE_T - Store Zipped file data
/* ---------------------------------------------------------------------- */
/*
DROP TABLE batch_rel_zip_file_t;

CREATE TABLE batch_rel_zip_file_t (
    obj_id0         NUMBER,
    rec_id          NUMBER,
    status          NUMBER,
    filename        VARCHAR2(255),
    num_records     NUMBER,
    buffer_size     NUMBER
);
COMMENT ON TABLE batch_rel_zip_file_t IS 'Contains rated event data transferred from ECE for loading'
COMMENT ON COLUMN batch_rel_zip_file_t.obj_id0 IS 'Unique identifier of record to be joined with batch_t.poid_id0'
COMMENT ON COLUMN batch_rel_zip_file_t.rec_id IS 'Array index'
COMMENT ON COLUMN batch_rel_zip_file_t.status IS 'Status of record - 0 = completed, 1 = ready to process, 2 = data error'
COMMENT ON COLUMN batch_rel_zip_file_t.filename IS 'The filename of the CDR file'
COMMENT ON COLUMN batch_rel_zip_file_t.num_records IS 'The number of records that are in this file'
COMMENT ON COLUMN batch_rel_zip_file_t.buffer_size IS 'The size of the zip file'
*/
CREATE INDEX i_batch_rel_zip_incomplete ON batch_rel_zip_file_t(DECODE(status, 0, NULL, status));
CREATE UNIQUE INDEX i_batch_rel_zip__obj_id0 ON batch_rel_zip_file_t(obj_id0, rec_id);

/* ---------------------------------------------------------------------- */
/* BATCH_REL_ZIP_FILE_BUF_T - Store Zipped file data
/* ---------------------------------------------------------------------- */
/*
DROP TABLE batch_rel_zip_file_buf_t;

CREATE TABLE batch_rel_zip_file_buf_t (
    obj_id0         NUMBER,
    rec_id          NUMBER,
    buffer_buf      BLOB
);
COMMENT ON TABLE batch_rel_zip_file_buf_t IS 'Contains zipped rated event data transferred from ECE for loading'
COMMENT ON COLUMN batch_rel_zip_file_buf_t.obj_id0 IS 'Unique identifier of record to be joined with batch_t.poid_id0'
COMMENT ON COLUMN batch_rel_zip_file_buf_t.rec_id IS 'Array index'
COMMENT ON COLUMN batch_rel_zip_file_buf_t.buffer IS 'The BLOB of ZIP data'
*/
CREATE UNIQUE INDEX i_batch_rel_zip_buf__obj_id0 ON batch_rel_zip_file_buf_t(obj_id0, rec_id);

/* ---------------------------------------------------------------------- */
/* BATCH_REL_RETRY_T - Store retry requests from REL Manager
/* ---------------------------------------------------------------------- */
/*
DROP TABLE batch_rel_retry_t;

CREATE TABLE batch_rel_retry_t (
    obj_id0         NUMBER,
    rec_id          NUMBER,
    created_t       NUMBER,
    process_start_t NUMBER,
    process_end_t   NUMBER,
    status          NUMBER
);
COMMENT ON TABLE batch_rel_retry_t IS 'Contains rated event data transferred from ECE for loading'
COMMENT ON COLUMN batch_rel_retry_t.obj_id0 IS 'Unique identifier of record to be joined with batch_t.poid_id0'
COMMENT ON COLUMN batch_rel_retry_t.created_t IS 'Timestamp for when this retry attempt was created'
COMMENT ON COLUMN batch_rel_retry_t.process_start_t IS 'Timestamp for when this retry attempt was started'
COMMENT ON COLUMN batch_rel_retry_t.process_end_t IS 'Timestamp for when this retry attempt ended'
COMMENT ON COLUMN batch_rel_retry_t.status IS 'Status of record: COMPLETE(0), READY(1), PROCESSING(2)' 
*/
CREATE INDEX i_batch_rel_retry_ready ON batch_rel_retry_t(DECODE(status, 1, status, NULL));
CREATE UNIQUE INDEX i_batch_rel_retry__id ON batch_rel_retry_t(obj_id0, rec_id);

exit;
