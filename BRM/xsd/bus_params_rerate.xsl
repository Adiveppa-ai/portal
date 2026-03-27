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
				<ParamClass desc="Business logic parameters for Rerate" name="rerate">
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsRerate/bc:*"/>
				</ParamClass>
			</BusParamConfigurationList>
			</BusParamConfiguration>
		</BusinessConfiguration>
	</xsl:template>
		
	<xsl:template match="bc:BatchRatingPipeline">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>batch_rating_pipeline</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Enable/Disable Indicates whether usage rating through the pipeline rating engine is enabled or disabled. The parameter values can be 0 (disabled), 1 (enabled). Default is 0 (disabled).
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

	<xsl:template match="bc:ECERating">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>ece_rating</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Enable/Disable Indicates whether usage rating through the ECE rating engine is enabled or disabled. The parameter values can be 0 (disabled), 1 (enabled). Default is 0 (disabled).
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

	<xsl:template match="bc:LineManagement">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>line_management</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Rerate job creation will consider line transfer cases when enabled.
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
		
	<xsl:template match="bc:AllocateReratingAdjustments">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>allocate_rerating_adjustments</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                This parameter indicates that the item adjustments which are created by the rerating process will be allocated to billable items. The parameter has two values: 0 - do not make allocatioin during rerating (default), or 1 - make allocation during rerating.
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

	<xsl:template match="bc:ApplyDeferredTaxDuringRerating">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>apply_deferred_tax_during_rerating</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				This parameter indicates that deferred taxation should be applied during rerating . The parameter has two values: 0 - do not apply deferred taxes during rerating (default), or 1 -  apply deferred taxes during rerating.
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

	<xsl:template match="bc:OfferEligibilitySelectionMode">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>apply_period_based_during_rerating</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				This parameter indicates that period based rerating should be applied for ECE events. The parameter has two values: 0 - consider endtime based for ECE events during rerating (default), or 1 -  consider period based during rerating.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:element name="Value">
                                <xsl:choose> 
                                        <xsl:when test="normalize-space(text()) = 'timeperiod'">
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
