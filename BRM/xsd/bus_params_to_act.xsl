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
				<BusParamsActivity>
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
				</BusParamsActivity>
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

				<xsl:when test="$name = 'billing_time_discount_based_on_period'">
					<xsl:element name="BillingTimeDiscountBasedOnPeriod">
						<xsl:choose>
							<xsl:when test="$value = '1'">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '0'">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>				

				<xsl:when test="$name = 'prepaid_traffic_light_enable'">
					<xsl:element name="LightWeightAuthorization">
						<xsl:choose>
							<xsl:when test="$value = '1'">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '0'">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>				

				<xsl:when test="$name = 'max_login_attempts'">
                                        <xsl:element name="MaxLoginAttempts">
                                        <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = 'use_exact_time_for_deferred_action'">
					<xsl:element name="UseExactTimeForDeferredAction">
						<xsl:choose>
							<xsl:when test="$value = '1'">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '0'">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>				

				<xsl:when test="$name = 'set_first_usage_in_session'">
					<xsl:element name="SetFirstUsageInSession">
						<xsl:choose>
							<xsl:when test="$value = '1'">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '0'">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>				

				<xsl:when test="$name = 'last_increment_rounding'">
                                        <xsl:element name=""LastIncrementRounding"">
						<xsl:choose>
							<xsl:when test="$value = '0'">
								<xsl:text>noRounding</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '1'">
								<xsl:text>roundUp</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '2'">
								<xsl:text>roundDown</xsl:text>
							</xsl:when>
						</xsl:choose>
                                        </xsl:element>
                                </xsl:when>
			</xsl:choose>
										
	</xsl:template>
</xsl:stylesheet>

