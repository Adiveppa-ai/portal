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
				<BusParamsRating>
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
				</BusParamsRating>
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

				<xsl:when test="$name = 'override_credit_limit'">
					<xsl:element name="OverrideCreditLimit">
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
				<xsl:when test="$name = 'enable_eras'">
					<xsl:element name="EnableEras">
						<xsl:choose>
							<xsl:when test="$value = '3'">
								<xsl:text>serviceAndAccount</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '2'">
								<xsl:text>account</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '1'">
								<xsl:text>service</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '0'">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>
				<xsl:when test="$name = 'enable_tailormade_cache'">
					<xsl:element name="EnableTailormadeCache">
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
				<xsl:when test="$name = 'enable_global_charge_sharing'">
					<xsl:element name="EnableGlobalChargeSharing">
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
				<xsl:when test="$name = 'allocate_rerating_adjustments'">
                                        <xsl:element name="AllocateReratingAdjustments">
                                                <xsl:choose>
                                                        <xsl:when test="$value = '1'">
                                                                <xsl:text>enabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = '0'">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
							<xsl:when test="$name = 'timestamp_rounding_for_purchase_grant'">
								<xsl:element name="TimeStampRoundingForPurchaseGrant">
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
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>
				<xsl:when test="$name = 'products_discounts_threshold'">
					<xsl:element name="ProductsDiscountsThreshold">
					</xsl:element>
					<xsl:variable name="value" select="normalize-space(text())"/>
					<xsl:element name="Value">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>
				<xsl:when test="$name = 'override_in_product_currency'">
					<xsl:element name="OverrideInProductCurrency">
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
				<xsl:when test="$name = 'apply_discount_on_zero_charge'">
					<xsl:element name="ApplyDiscountOnZeroCharge">
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
				<xsl:when test="$name = 'reset_member_credit_limit'">
					<xsl:element name="ResetMemberCreditLimit">
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
                                <xsl:when test="$name = 'sharing_groups_enabled'">
                                        <xsl:element name="SharingGroupsEnabled">
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
				<xsl:when test="$name = 'extra_rate_flags'">
					<xsl:element name="ExtraRateFlags">
					</xsl:element>
					<xsl:variable name="value" select="normalize-space(text())"/>
					<xsl:element name="Value">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>
				 <xsl:when test="$name = 'tax_return_juris'">
                                        <xsl:element name="TaxReturnJuris">
                                              <xsl:choose>
                                                        <xsl:when test="$value = 'summarize'">
                                                                <xsl:text>summarize</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = 'itemize'">
                                                                <xsl:text>itemize</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>
			</xsl:choose>
	</xsl:template>
</xsl:stylesheet>
