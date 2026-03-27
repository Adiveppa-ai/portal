<?xml version="1.0" encoding="UTF-8"?>
<!--
  **************************************************************************
* Copyright (c) 2023, Oracle and/or its affiliates.
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
                                <ParamClass desc="Business logic parameters for Notification" name="notification">
                                        <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsNotification/bc:*"/>
                                </ParamClass>
                        </BusParamConfigurationList>
                        </BusParamConfiguration>
                </BusinessConfiguration>
        </xsl:template>


	<xsl:template match="bc:KafkaDBNumber">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>kafka_db_number</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
							KafkaDBNumber for which  DynamicKey is populated
                        </xsl:element>
                        <xsl:element name="Type">STR</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>


</xsl:stylesheet>

