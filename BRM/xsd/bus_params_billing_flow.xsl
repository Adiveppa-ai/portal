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
				<ParamClass desc="Business logic parameters for Billing Flow" name="billing_flow">
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsBillingFlow/bc:*"/>
				</ParamClass>
			</BusParamConfigurationList>
			</BusParamConfiguration>
		</BusinessConfiguration>
	</xsl:template>
	
	<xsl:template match="bc:BillingFlowDiscount">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>billing_flow_discount</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
			Parameter values can be 0 (flow for discount is undefined), 1 (discount_parents should be billed before members), 2 (members_discount should be billed before parents).
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:element name="Value">
				<xsl:choose>
					<xsl:when test="normalize-space(text()) = 'undefined'">
						<xsl:text>0</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'discountParentsFirst'">
						<xsl:text>1</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'memberDiscountFirst'">
						<xsl:text>2</xsl:text>
					</xsl:when>
				</xsl:choose>			
			</xsl:element>
		</xsl:element>
	</xsl:template>

	<xsl:template match="bc:BillingFlowSponsorship">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>billing_flow_sponsorship</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
			Parameter values can be 0 (flow for sponsorship is undefined), 1 (sponsors should be billed before sponsorees), 2 (sponsorees should be billed before sponsors).
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:element name="Value">
				<xsl:choose>
					<xsl:when test="normalize-space(text()) = 'undefined'">
						<xsl:text>0</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'sponsorsFirst'">
						<xsl:text>1</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'sponsoreesFirst'">
						<xsl:text>2</xsl:text>
					</xsl:when>
				</xsl:choose>			
			</xsl:element>
		</xsl:element>
	</xsl:template>

	<xsl:template match="bc:BillingFlowSkipCheckForCyclicDSG">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>billing_flow_skip_cyc_dsg_check</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
			Parameter values can be 0 (flow for cyclic DSG check is enabled, default behaviour), 1 (cyclic DSG check is disabled).
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:element name="Value">
				<xsl:choose>
					<xsl:when test="normalize-space(text()) = 'disabled'">
						<xsl:text>0</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'enabled'">
						<xsl:text>1</xsl:text>
					</xsl:when>
				</xsl:choose>			
			</xsl:element>
		</xsl:element>
	</xsl:template>

</xsl:stylesheet>

