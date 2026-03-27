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
                                <ParamClass desc="Business logic parameters for Pricing" name="pricing">
                                        <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsPricing/bc:*"/>
                                </ParamClass>
                        </BusParamConfigurationList>
                        </BusParamConfiguration>
                </BusinessConfiguration>
        </xsl:template>

        <xsl:template match="bc:PriceDesignCenterInst">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>pdc_enabled</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                This parameter decides if the PDC
                                is enabled. When enabled by setting
                                to 1, it would allow user to edit the  
				names of various pricing objects like 
				planlist, plan, deal, sponsorship.
                                Default value is 0 which disables this feature.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:element name="Value">
                                <xsl:choose>
                                        <xsl:when test="normalize-space(text()) = 'enabled'">
                                                <xsl:text>1</xsl:text>
                                        </xsl:when>
                                        <xsl:otherwise>
                                                <xsl:text>0</xsl:text>
                                        </xsl:otherwise>
                                </xsl:choose>
                        </xsl:element>
                </xsl:element>
        </xsl:template>
        <xsl:template match="bc:CacheReferencesAtStart">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>cache_references_at_start</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				This parameter specifies whether to store objects referenced by price objects in memory in the CM cache when the CM starts. Objects referenced by price objects include BEIDs, GLIDs, tax suppliers, event types, service types, and RUMs. The value for this entry can be 0(The CM caches objects that are referenced by price objectsin the CM cache every time a price list is committed.) or 1((Default) The CM caches objects that are referenced by price objects one time when the CM starts.)
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:element name="Value">
                                <xsl:choose>
                                        <xsl:when test="normalize-space(text()) = 'enabled'">
                                                <xsl:text>1</xsl:text>
                                        </xsl:when>
                                        <xsl:otherwise>
                                                <xsl:text>0</xsl:text>
                                        </xsl:otherwise>
                                </xsl:choose>
                        </xsl:element>
                </xsl:element>
        </xsl:template>
        <xsl:template match="bc:LogPriceChangeEvent">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>log_price_change_event</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				This parameter specifies event creation and logging for price object changes. Price object changes include changes to products, deals, and  plans. Logging such events creates an audit trail that is useful if you need to look up previous versions of a price object. The value for this entry can be: 0 = (Default) Do not create events when price object changes  are made, thus saving storage space. 1 = Create and log an event for each changed price object.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:element name="Value">
                                <xsl:choose>
                                        <xsl:when test="normalize-space(text()) = 'enabled'">
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
