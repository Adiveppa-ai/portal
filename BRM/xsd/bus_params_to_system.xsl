<?xml version="1.0" encoding="UTF-8"?>
<!--
  **************************************************************************
* Copyright (c) 2015, 2022, Oracle and/or its affiliates. All rights reserved.
  *
  * This material is the confidential property of Oracle Corporation
  * or its licensors and may be used, reproduced, stored or transmitted
  * only in accordance with a valid Oracle license or sublicense agreement.
  **************************************************************************
-->
<xsl:stylesheet version="1.0" xmlns="http://www.portal.com/schemas/BusinessConfig" xmlns:bc="http://www.portal.com/schemas/BusinessConfig" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" exclude-result-prefixes="bc">

        <xsl:output method="xml" indent="yes"/>

        <xsl:template match="/">
                <BusinessConfiguration xmlns="http://www.portal.com/schemas/BusinessConfig" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.portal.com/schemas/BusinessConfig business_configuration.xsd">
                        <BusParamConfigurationClass>
                                <BusParamsSystem>
                                        <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
                                </BusParamsSystem>
                        </BusParamConfigurationClass>
                </BusinessConfiguration>
        </xsl:template>

        <xsl:template match="//bc:Param">
                        <xsl:variable name="name">
                                <xsl:value-of select="bc:Name/text()"/>
                        </xsl:variable>

                        <xsl:variable name="value">
                                <xsl:value-of select="bc:Value/text()"/>
                        </xsl:variable>

                        <xsl:choose>

                                <xsl:when test="$name = &apos;config_cache_refresh_interval&apos;">
                                        <xsl:element name="ConfigCacheRefreshInterval">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = &apos;prepaid_partition_set&apos;">
                                        <xsl:element name="PrepaidPartitionSet">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = &apos;notification_subscriber_preferences&apos;">
                                        <xsl:element name="NotificationSubscriberPreferences">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = &apos;notification_silent_period&apos;">
                                        <xsl:element name="NotificationSilentPeriod">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = &apos;acceptable_delay_time&apos;">
                                        <xsl:element name="AcceptableDelayTime">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>
                                
                                <xsl:when test="$name = &apos;silent_days_calendar_name&apos;">
                                        <xsl:element name="SilentDaysCalendarName">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = &apos;enabled_external_ids&apos;">
                                        <xsl:element name="EnableExternalIds">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = &apos;cross_schema_sharing_group&apos;">
                                        <xsl:element name="CrossSchemaSharingGroup">
                                                <xsl:choose>
            					   <xsl:when test="$value = &apos;1&apos;">
              					     <xsl:text>enabled</xsl:text>
            					   </xsl:when>
            					   <xsl:when test="$value = &apos;0&apos;">
              					     <xsl:text>disabled</xsl:text>
            					   </xsl:when>
          					</xsl:choose>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = &apos;cm_authorization&apos;">
                                        <xsl:element name="CMAuthorization">
                                                <xsl:choose>
            					   <xsl:when test="$value = &apos;1&apos;">
              					     <xsl:text>enabled</xsl:text>
            					   </xsl:when>
            					   <xsl:when test="$value = &apos;0&apos;">
              					     <xsl:text>disabled</xsl:text>
            					   </xsl:when>
          					</xsl:choose>
                                        </xsl:element>
                                </xsl:when>

                        </xsl:choose>

        </xsl:template>
</xsl:stylesheet>
