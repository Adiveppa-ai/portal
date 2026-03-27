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
                        <BusParamConfiguration>
                        <BusParamConfigurationList>
                                <ParamClass desc="Business logic parameters for Collections" name="collections">
                                        <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsCollections/bc:*"/>
                                </ParamClass>
                        </BusParamConfigurationList>
                        </BusParamConfiguration>
                </BusinessConfiguration>
        </xsl:template>

        <xsl:template match="bc:DeliveryPreference">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>delivery_preference</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Specifies the delivery preference. Can have 2 values: 0(by email)/ 1(hardcopy)
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:choose>
                                         <xsl:when test="normalize-space(text()) = 'email'">
                                                <xsl:text>0</xsl:text>
                                        </xsl:when>
                                        <xsl:when test="normalize-space(text()) = 'hard_copy'">
                                                <xsl:text>1</xsl:text>
                                        </xsl:when>
                                </xsl:choose>
                        </xsl:element>
                </xsl:element>
        </xsl:template>
		
</xsl:stylesheet>
