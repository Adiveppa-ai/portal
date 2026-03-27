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
				<BusParamsSelectiveLoading>
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
				</BusParamsSelectiveLoading>
			</BusParamConfigurationClass>
		</BusinessConfiguration>
	</xsl:template>

	<xsl:template match="//bc:Param">
		<xsl:when test="$name = 'cache_residencies_for_batch_pipeline'">
			<xsl:element name="CacheResidenciesForBatchPipeline">
			<xsl:value-of select="$value"/>
			</xsl:element>
		</xsl:when>
	</xsl:template>

	<xsl:template match="//bc:Param">
		<xsl:when test="$name = 'cache_residencies_for_timos'">
			<xsl:element name="CacheResidenciesForTimos">
			<xsl:value-of select="$value"/>
			</xsl:element>
		</xsl:when>
	</xsl:template>
</xsl:stylesheet>

