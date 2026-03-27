set serveroutput on size 1000000
-- 2003 - 2023 Oracle. This material is the confidential property of Oracle Corporation
-- or its licensors and may be used, reproduced, stored or transmitted only in accordance with a valid Oracle
-- license or sublicense  agreement.
--
CREATE OR REPLACE PACKAGE acct_sync AUTHID CURRENT_USER AS 
  --
   TYPE deq_event_rec IS RECORD
    (event_name		 VARCHAR2(32),
     flist_buf		 VARCHAR2(4000),
     large_flist_buf	 CLOB,
     mesg_id		 VARCHAR2(32),
     enq_time		 DATE);
   -- 

   TYPE deq_event_cursor IS REF CURSOR RETURN deq_event_rec;

   -- procedure: deq_event_rc
   --   Dequeue account sync event from Oracle AQ queue. 
   --   Dequeue timeout after 5 seconds.
   -- parameters:
   --   OUT event_cursor	  - event table
   --   IN queue_name		  - queue name
   --   IN event_name_cond        - event name for dequeuing
   --   IN batch_size             - No of Messages to be dequeued
   --   IN ack_queue_name         - ack queue name
   -- exceptions: no_messages

   PROCEDURE deq_event_rc (queue_name            IN VARCHAR2,
                           event_name_cond       IN VARCHAR2,
                           batch_size            IN NUMBER,
                           ack_queue_name        IN VARCHAR2,
                           event_cursor          IN OUT deq_event_cursor);
   --
   -- procedure: deq_event
   --   Dequeue account sync event from Oracle AQ queue. 
   --   Dequeue timeout after 5 seconds.
   -- parameters:
   --   OUT event_name            - event name
   --   OUT flist_buf             - FLIST as a string
   --   OUT large_flist_buf       - large FLIST as a CLOB
   --   OUT mesg_id               - unique AQ message id
   --   OUT enq_time              - message enqueue time (for backlog processing)
   --   IN queue_name             - queue name
   --   IN event_name_cond        - event selection criteria
   -- exceptions: no_messages
   --
   PROCEDURE deq_event(event_name      OUT NOCOPY VARCHAR2,
                       flist_buf       OUT NOCOPY VARCHAR2,
                       large_flist_buf OUT NOCOPY CLOB,
                       mesg_id         OUT NOCOPY VARCHAR2,
                       enq_time        OUT NOCOPY DATE,
                       queue_name      IN VARCHAR2,
                       event_name_cond IN VARCHAR2);
   -- 
   -- procedure: enq_event
   --   Enqueue account sync event in Oracle AQ queue. 
   -- parameters: 
   --   IN event_name		  - event name
   --   IN flist_buf              - FLIST as a string
   --   IN flist_buf_len	  - FLIST string length in characters
   --   IN queue_name		  - queue name
   --   OUT mesg_id		  - unique AQ message id
   -- exceptions: 
   --

   PROCEDURE enq_event(event_name    IN VARCHAR2,
		       flist_buf     IN VARCHAR2,
                       flist_buf_len IN NUMBER,
		       queue_name    IN VARCHAR2,
		       mesg_id	     OUT NOCOPY VARCHAR2);
   --
   -- procedure: enq_event_append
   --   Appends to LOB representation of pre-existing account sync event in Oracle AQ.
   --   Can only be called AFTER acct_sync.enq_event(). Number of calls to
   --   acct_sync.enq_event_append() is unlimited to support FLIST payloads larger the 32k.
   -- parameters:
   --   IN flist_buf               - next FLIST fragment
   --   IN flist_buf_len           - FLIST string length in characters
   --   IN queue_name              - queue name
   --   IN mesg_id                 - unique AQ message id
   -- exceptions:
   --
   PROCEDURE enq_event_append(flist_buf     IN VARCHAR2,
                              flist_buf_len IN NUMBER,
                              queue_name    IN VARCHAR2,
                              mesg_id       IN VARCHAR2);
   --
   -- procedure: purge_event
   --   Purge redundant messages from queue before Pipeline startup.
   -- parameters:
   --   IN queue_name		  - queue name
   --
   PROCEDURE purge_event(queue_name	IN VARCHAR2,
		         purge_mesg_cnt OUT NOCOPY NUMBER);
END;
/
show errors;

