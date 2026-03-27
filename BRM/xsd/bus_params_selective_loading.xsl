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
				<ParamClass desc="Business logic parameters for selective loading" name="selective_loading">
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsSelectiveLoading/bc:*"/>
				</ParamClass>
			</BusParamConfigurationList>
			</BusParamConfiguration>
		</BusinessConfiguration>
	</xsl:template>
	
	<xsl:template match="bc:CacheResidenciesForBatchPipeline">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>cache_residencies_for_batch_pipeline</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				Object cache type values pertaining to which, data is loaded by the batch pipeline.
                                The values should be separated by commas.
                        </xsl:element>
                        <xsl:element name="Type">STR</xsl:element>
			<xsl:variable name="value" select="normalize-space(text())"/>
				<xsl:element name="Value">
					<xsl:value-of select="$value"/>	
				</xsl:element>
                </xsl:element>
        </xsl:template>

	<xsl:template match="bc:CacheResidenciesForTimos">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>cache_residencies_for_timos</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				Object cache type values pertaining to which, data is loaded by TIMOS.
                                The values should be separated by commas.
                        </xsl:element>
                        <xsl:element name="Type">STR</xsl:element>
			<xsl:variable name="value" select="normalize-space(text())"/>
				<xsl:element name="Value">
					<xsl:value-of select="$value"/>	
				</xsl:element>
                </xsl:element>
        </xsl:template>

</xsl:stylesheet>
