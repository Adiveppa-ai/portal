#=============================================================
# Copyright (c) 2021 Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
#=============================================================

%DM_KAFKA_CM_PINCONF_ENTRIES = (

   "dm_kafka_dm_pointer_description", <<END
#========================================================================
# dm_kafka dm_pointer
# Specifies where to find the external manager that provides the integration
# to Kafka server.
#========================================================================
END
  , "dm_kafka_dm_pointer"
  , "- cm dm_pointer $DM_KAFKA{'db_num'} ip $DM_KAFKA{'hostname'} $DM_KAFKA{'port'}  # dm_kafka"

);
