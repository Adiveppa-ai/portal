# @(#) % %
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

%CONTENT_MANAGER_CM_PINCONF_ENTRIES = (

  "content_profile_cache_ttl_description", <<END
#=======================================================================
# content_profile_cache_ttl
#
# The duration (in seconds) for which content service profiles
# will remain in the CM cache.
#=======================================================================
END
  , "content_profile_cache_ttl",
    "- cm content_profile_cache_ttl 3600"
  ,"content_use_profile_description", <<END
#=======================================================================
# content_use_profile
#
# Enabling Service Profiles
# The entry below specifies if the content products are using 
# Service Profiles
# Valid Values for this are
# 0 - The Content Products do not use Service Profiles
# 1 - The Content Products use Service Profiles
# By default the value is set to 1.
#=======================================================================
END
  , "content_use_profile",
    "- cm content_use_profiles 1"
  ,"content_prerated_mode_description", <<END
#========================================================================
# content_prerated_mode
#
# To enable treating the amount based requests as pre-rated events (Skip rating calls) set,
#  content_prerated_mode 0(default)
#
# - To enable the rating mode , set
#  content_prerated_mode 1
#
# By default the value is set to 0.
#========================================================================
END
  , "content_prerated_mode",
    "- cm content_prerated_mode 0"
  ,"content_fm_required_description", <<END
#========================================================================
# content_fm_required
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
  , "content_fm_required", <<END
- cm fm_module \$\{PIN_HOME\}/lib/fm_content\$\{LIBRARYEXTENSION\} fm_content_config$FM_FUNCTION_SUFFIX fm_content_init pin
- cm fm_module \$\{PIN_HOME\}/lib/fm_content_pol\$\{LIBRARYEXTENSION\} fm_content_pol_config$FM_FUNCTION_SUFFIX - pin
END
);
