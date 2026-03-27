#=============================================================
#  @(#) % %
# 
# Copyright (c) 2000, 2009, Oracle and/or its affiliates. All rights reserved. 
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
#==============================================================

%NUMBER_MANAGER_CM_PINCONF_ENTRIES = (

"num_fm_required_description", <<END
#========================================================================
# num_fm_required
#
# Required Facilities Modules (FM) configuration entries
# The entries below specify the required FMs that are linked to the CM when
# the CM starts. The FMs required by the CM are included in this file when
# you install Portal. 
#
# Caution: DO NOT modify these entries unless you need to change the
#          location of the shared library file. DO NOT change the order of
#          these entries, because certain modules depend on others being
#          loaded before them.
#========================================================================
END
, "num_fm_required", <<END
- cm fm_module \$\{PIN_HOME\}/lib/fm_num\$\{LIBRARYEXTENSION\} fm_num_config$FM_FUNCTION_SUFFIX - pin
- cm fm_module \$\{PIN_HOME\}/lib/fm_num_pol\$\{LIBRARYEXTENSION\} fm_num_pol_config$FM_FUNCTION_SUFFIX - pin
END
);
