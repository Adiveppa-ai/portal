<?xml version="1.0" encoding="UTF-8"?>

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
                                <BusParamsAAA>
                                       <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
                                </BusParamsAAA>
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

                                <xsl:when test="$name = &apos;piggyback_enable&apos;">
                                        <xsl:element name="Piggyback">
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

