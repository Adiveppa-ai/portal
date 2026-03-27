<?xml version="1.0" encoding="UTF-8"?>
<!--
  **************************************************************************
* Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
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
                        <BusParamConfigurationClass>
                                <BusParamsCollections>
                                        <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
                                </BusParamsCollections>
                        </BusParamConfigurationClass>
                </BusinessConfiguration>
        </xsl:template>

        <xsl:template match="//bc:Param">
                        <xsl:variable name="name">
                                <xsl:value-of select="bc:Name/text()"></xsl:value-of>
                        </xsl:variable>

                        <xsl:variable name="value">
                                <xsl:value-of select="bc:Value/text()"></xsl:value-of>
                        </xsl:variable>

                        <xsl:choose>
                                <xsl:when test="$name = 'delivery_preference'">
                                        <xsl:element name="DeliveryPreference">
                                                <xsl:choose>
                                                        <xsl:when test="$value = '0'">
                                                                <xsl:text>email</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = '1'">
                                                                <xsl:text>hard_copy</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>
                        </xsl:choose>

        </xsl:template>
</xsl:stylesheet>
