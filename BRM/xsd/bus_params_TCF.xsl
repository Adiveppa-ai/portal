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
                                <BusParamConfiguration>
                       <BusParamConfigurationList>
                                <ParamClass desc="Business logic parameter for TCF" name="tcf">
                                        <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsTCF/bc:*"/>
                                </ParamClass>
                        </BusParamConfigurationList>

                                </BusParamConfiguration>
                        </BusinessConfiguration>
                </xsl:template>

                <xsl:template match="bc:RestrictDeviceToServiceStatePropagation">
                        <xsl:element name="Param">
                                <xsl:element name="Name">
                                        <xsl:text>restrict_device_to_service_state_propagation</xsl:text>
                                </xsl:element>
                                <xsl:element name="Desc">
                                        This parameter is used to enable/disable Service inactivation when a Device associated with it is dissociated or swapped.
                                        The default is disabled(0), i.e. Service will be inactivated when the device is dissociated.
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


