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
				<ParamClass desc="Business logic parameters for Activity" name="activity">
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsActivity/bc:*"/>
				</ParamClass>
			</BusParamConfigurationList>
			</BusParamConfiguration>
		</BusinessConfiguration>
	</xsl:template>
		
	<xsl:template match="bc:BillingTimeDiscountBasedOnPeriod">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>billing_time_discount_based_on_period</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				This parameter decides if the
				balances to be used for billing time discounts
				will be calculated based on a period.
				When enabled by setting to 1, balances
				will be calculated based on a period.
				Default value is 0 which disables this feature
				where balances will be calculated within the period.
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

	<xsl:template match="bc:LightWeightAuthorization">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>prepaid_traffic_light_enable</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				This parameter turns on(1)/off(0) Light Weight Authorization feature	
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

	<xsl:template match="bc:MaxLoginAttempts">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>max_login_attempts</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				This parameter indicates the maximum number of invalid login attempts allowed
                                for /service/pcm_client and /service/admin_client before the service is locked.
                                The default value is 5.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                            <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                            </xsl:element>
                </xsl:element>
        </xsl:template>

	<xsl:template match="bc:UseExactTimeForDeferredAction">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>use_exact_time_for_deferred_action</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				This parameter determines use of the exact scheduled time for a deferred action. Valid values are 0 (Default) - Disabled: When creating a deferred action, round off scheduled time to midnight and 1 - Enabled: Use exact time specified in input without rounding to midnight.
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

	<xsl:template match="bc:SetFirstUsageInSession">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>set_first_usage_in_session</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
					This parameter decides if the First Usage of
					a balance validity will be triggered at the start 
					or in the middle of a user session.
					When enabled by setting to 1, balance First Usage
					can be set at the authorization/reauthorization
					time, as well as at the end of a session.
					Default value is 0 which disables this feature
					and balance First Usage can only be set at the
					end of a session.
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

	<xsl:template match="bc:LastIncrementRounding">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>last_increment_rounding</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                 This parameter determines how th
e last increment quantity should be rounded in prepaid authorization. Valid valu
es are 0 (Default) - No rounding, 1 - round up and 2 - round down.
                                 The default value is no rounding.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
			<xsl:element name="Value">
				<xsl:choose>
					<xsl:when test="normalize-space(text()) = 'noRounding'">
						<xsl:text>0</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'roundUp'">
						<xsl:text>1</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'roundDown'">
						<xsl:text>2</xsl:text>
					</xsl:when>
				</xsl:choose>
			</xsl:element>
                </xsl:element>
        </xsl:template>

</xsl:stylesheet>
