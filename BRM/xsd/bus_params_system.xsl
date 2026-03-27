<?xml version="1.0" encoding="UTF-8"?>
<!--
  **************************************************************************
* Copyright (c) 2016, 2022, Oracle and/or its affiliates. All rights reserved.
  *
  * This material is the confidential property of Oracle Corporation
  * or its licensors and may be used, reproduced, stored or transmitted
  * only in accordance with a valid Oracle license or sublicense agreement.
  **************************************************************************
-->
<xsl:stylesheet
        version="1.0"
        xmlns="http://www.portal.com/schemas/BusinessConfig"
        xmlns:bc="http://www.portal.com/schemas/BusinessConfig"
        xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
        exclude-result-prefixes="bc">

        <xsl:output method="xml" indent="yes"/>

        <xsl:template match="/">
                <BusinessConfiguration xmlns="http://www.portal.com/schemas/BusinessConfig" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.portal.com/schemas/BusinessConfig business_configuration.xsd">
                        <BusParamConfiguration>
                        <BusParamConfigurationList>
                                <ParamClass desc="Business logic parameters for Business Cofiguration Center" name="system">
                                        <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsSystem/bc:*"/>
                                </ParamClass>
                        </BusParamConfigurationList>
                        </BusParamConfiguration>
                </BusinessConfiguration>
        </xsl:template>

        <xsl:template match="bc:ConfigCacheRefreshInterval">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>config_cache_refresh_interval</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
							Specifies the interval in minutes after which config params cached data will be considered stale.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>

        <xsl:template match="bc:PrepaidEngine">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>prepaid_engine</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
							Specifies the rating engine used for prepaid events. Valid values are 0 and 1. When set to 0, c_rating is used and When set to 1, ece_rating is used . Default value is 0.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
	</xsl:template>

        <xsl:template match="bc:PrepaidPartitionSet">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>prepaid_partition_set</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
							Specifies the partition set for prepaid events. Valid values are 0 and 2 - 7. When set to 0, prepaid partitioning is disabled. Default value is 0.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
	</xsl:template>

	<xsl:template match="bc:NotificationSubscriberPreferences">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>notification_subscriber_preferences</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
							Specifies the comma seperated list of subscriber preferences that needs to be part of notification messages
                        </xsl:element>
                        <xsl:element name="Type">STR</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
	</xsl:template>

	<xsl:template match="bc:NotificationSilentPeriod">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>notification_silent_period</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
							Default silent period value is 21:00-07:00. This values would be used when SilentPeriod is enabled in /config/notification_spec for the BusinessEvent being processed.
                        </xsl:element>
                        <xsl:element name="Type">STR</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>

        <xsl:template match="bc:AcceptableDelayTime">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>acceptable_delay_time</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                                        Default value is 02:00.
                        </xsl:element>
                        <xsl:element name="Type">STR</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>
        
        <xsl:template match="bc:SilentDaysCalendarName">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>silent_days_calendar_name</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                                        Default value is NotificationSilentDays
                        </xsl:element>
                        <xsl:element name="Type">STR</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>

        <xsl:template match="bc:EnableExternalIds">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>enable_external_ids</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                              				Generation of unique IDs for Event, Balance Group, Billinfo, payinfo can be Enabled/Disabled. Default value is 0. 
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>

        <xsl:template match="bc:CrossSchemaSharingGroup">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>cross_schema_sharing_group</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
							Specifies whether the parent and member accounts in sharing groups can be present in different schemas. Default value is disabled meaning parent and member account must be present in same schema.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:element name="Value">
        		  <xsl:choose>
          		    <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            		      <xsl:text>1</xsl:text>
                            </xsl:when>
          		    <xsl:otherwise>
            		      <xsl:text>0</xsl:text>
          		    </xsl:otherwise>
        		  </xsl:choose>
                        </xsl:element>
                </xsl:element>
        </xsl:template>

        <xsl:template match="bc:CMAuthorization">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>cm_authorization</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
							Specifies whether the CM authorization will be provided for pcm_client and admin_client applications. Default value is enabled.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:element name="Value">
        		  <xsl:choose>
          		    <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            		      <xsl:text>1</xsl:text>
                            </xsl:when>
          		    <xsl:otherwise>
            		      <xsl:text>0</xsl:text>
          		    </xsl:otherwise>
        		  </xsl:choose>
                        </xsl:element>
                </xsl:element>
        </xsl:template>

</xsl:stylesheet>
