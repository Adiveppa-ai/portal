#=============================================================
#  @(#) % %
# 
# Copyright (c) 2005, 2009, Oracle and/or its affiliates. All rights reserved. 
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
#==============================================================

%IP_MANAGER_CM_PINCONF_ENTRIES = (
"ip_fm_required_description", <<END
#========================================================================
# ip_fm_required
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
, "ip_fm_required", <<END
- cm fm_module \$\{PIN_HOME\}/lib/fm_ip\$\{LIBRARYEXTENSION\} fm_ip_config$FM_FUNCTION_SUFFIX - pin
- cm fm_module \$\{PIN_HOME\}/lib/fm_ip_pol\$\{LIBRARYEXTENSION\} fm_ip_pol_config$FM_FUNCTION_SUFFIX - pin
- cm fm_module \$\{PIN_HOME\}/lib/fm_apn_pol\$\{LIBRARYEXTENSION\} fm_apn_pol_config$FM_FUNCTION_SUFFIX - pin
END
);
