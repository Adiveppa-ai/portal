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
				<ParamClass desc="Business logic parameters for Rating" name="rating">
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsRating/bc:*"/>
				</ParamClass>
			</BusParamConfigurationList>
			</BusParamConfiguration>
		</BusinessConfiguration>
	</xsl:template>
	
	<xsl:template match="bc:OverrideCreditLimit">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>override_credit_limit</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				This parameter decides if the 
				system-wide credit limit override
				feature is enabled. When enabled by setting 
				to 1, credit limit check is avoided 
				irrespective of the credit limit 
				override value set in the product. 
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
	<xsl:template match="bc:EnableEras">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>enable_eras</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				This configuration can be used to control the selection of ERAs from profile
				objects.
				The values supported for this configuration parameter are:
				0 - disabled (no profiles)
				1 - service (select ERAs from service profiles only)
				2 - account (select ERAs from account profiles only)
				3 - service and account  (select ERAs from service and account profiles)
				The default value for this configuration parameter is 3.
				Also, if this parameter is not specified the implicit behavior is the default behavior.
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:element name="Value">
				<xsl:choose>
					<xsl:when test="normalize-space(text()) = 'serviceAndAccount'">
						<xsl:text>3</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'account'">
						<xsl:text>2</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'service'">
						<xsl:text>1</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'disabled'">
						<xsl:text>0</xsl:text>
					</xsl:when>
				</xsl:choose>
			</xsl:element>
		</xsl:element>
	</xsl:template>
	<xsl:template match="bc:EnableTailormadeCache">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>enable_tailormade_cache</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				This parameter decides if the
				tailormade products need to be stored
				in the cache of C Rating Engine.
				When enabled by setting to 1,
				tailormade products are stored in the cache.
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
        <xsl:template match="bc:EnableGlobalChargeSharing">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>enable_global_charge_sharing</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				This parameter enables or disables
				Global charge sharing.This is enabled by setting to 1.
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
	
	<xsl:template match="bc:ProductsDiscountsThreshold">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>products_discounts_threshold</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				This paramater indicates the maximum number of products or discounts that
				will be cached in C Rating Engine cache. Once the specified value is reached
				for either products/discounts then 10% of the products or discounts that are
				least used will be flushed from the cache. This is applicable only if this
				parameter is non-zero. Default value is 0 which disables this feature.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>
	<xsl:template match="bc:TimeStampRoundingForPurchaseGrant">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>timestamp_rounding_for_purchase_grant</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				This parameter enables or disables rounding of
                                purchase grant valid from validity to midnight.This works along with timestamp_rounding pin.conf
                                configuration.This is enabled by setting to 1.
                                Default value is 1 which enables this feature.
                                If this flag is disabled and timestamp rounding is enabled , then the
                                purchase grant will not be midnight rounded.Higher precedence of flag is
                                given to the new business param.If the new flag is enabled then midnight
                                rounding is enabled , the purchase fee grant will be midnight rounded.
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
	<xsl:template match="bc:OverrideInProductCurrency">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>override_in_product_currency</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				This parameter enables or disables override amount in product currency.
                                Default value is 0 which disables this feature.
                                If this flag is disabled, then the override amount for a product will be
                                in account currency.
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
	<xsl:template match="bc:RatePreCacheProductAndDisc">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>rate_pre_cache_product_and_disc</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				This parameter enables or disables caching of system/user products/discounts during cm startup. Bit fields of the integer value are used to specify the configuration options. Bit 0: precaches system products. Bit 1: precaches user products. Bit 2: precaches system discounts. Bit 3: precaches user discounts. Default value is 0. Any combination of bits can be set based on the precache requirement.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
			<xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
				<xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>
        <xsl:template match="bc:ApplyDiscountOnZeroCharge">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>apply_discount_on_zero_charge</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Default value is enable. If disabled then rating will skip pipeline call so that discounts are not processed if the product scale is 0.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:element name="Value">
                                <xsl:choose>
                                        <xsl:when test="normalize-space(text()) = 'disabled'">
                                                <xsl:text>0</xsl:text>
                                        </xsl:when>
                                        <xsl:otherwise>
                                                <xsl:text>1</xsl:text>
                                        </xsl:otherwise>
	                          </xsl:choose>
			</xsl:element>
		</xsl:element>
	</xsl:template>
	<xsl:template match="bc:ResetMemberCreditLimit">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>reset_member_credit_limit</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				This parameter decides if the 
				credit limit of member account to be
				set zero or not in case of roll up. 
				When enabled, credit limit of member 
				account will be zero.
				Default value is enabled.
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
        <xsl:template match="bc:SharingGroupsEnabled">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>sharing_groups_enabled</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Parameter to control whether the sharing groups feature is enabled. The default value is enabled (1). If disabled (0), the sharing groups feature will not be allowed.
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
	<xsl:template match="bc:ExtraRateFlags">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>extra_rate_flags</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				Parameter to set extra_rate_flags. Default value of extra_rate_flags is configured as 0x00.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
			<xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
				<xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>
	 <xsl:template match="bc:TaxReturnJuris">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>tax_return_juris</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				Parameter to control whether the taxes should be summarized by jurisdiction level. The default value is 'summarize' i.e. Summarize taxes by jurisdiction level. If set to 'itemize' it will not summarize taxes by jurisdiction level.
                        </xsl:element>
                        <xsl:element name="Type">STR</xsl:element>
                        <xsl:element name="Value">
                                <xsl:choose>
                                        <xsl:when test="normalize-space(text()) = 'summarize'">
                                                <xsl:text>summarize</xsl:text>
                                         </xsl:when>
                                        <xsl:when test="normalize-space(text()) = 'itemize'">
                                                <xsl:text>itemize</xsl:text>
                                         </xsl:when>
                                </xsl:choose>
                        </xsl:element>
                </xsl:element>
        </xsl:template>
</xsl:stylesheet>
