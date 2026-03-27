<?xml version="1.0" encoding="UTF-8"?>

  <!--
  **************************************************************************
* Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
  *
  * This material is the confidential property of Oracle Corporation
  * or its licensors and may be used, reproduced, stored or transmitted
  * only in accordance with a valid Oracle license or sublicense agreement.
  **************************************************************************
  -->

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
				<BusParamsAR>
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
				</BusParamsAR>
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

				<xsl:when test="$name = 'search_bill_amount_enable'">
					<xsl:element name="SearchBillAmount">
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
				
				<xsl:when test="$name = 'auto_writeoff_reversal_enable'">
					<xsl:element name="AutoWriteOffReversal">
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

				<xsl:when test="$name = 'writeoff_level'">
					<xsl:element name="WriteOffLevel">
						<xsl:choose>
							<xsl:when test="$value = 'account'">
								<xsl:text>account</xsl:text>
							</xsl:when>
							<xsl:when test="$value = 'billinfo'">
								<xsl:text>billinfo</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = 'payment_incentive_enable'">
					<xsl:element name="PaymentIncentive">
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

				<xsl:when test="$name = 'payment_suspense_enable'">
					<xsl:element name="PaymentSuspense">
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

				<xsl:when test="$name = 'nonrefundable_credit_items'">
					<xsl:element name="NonrefundableCreditItems">
						<xsl:value-of select="$value" />
					</xsl:element>
				</xsl:when>

				<xsl:when test ="$name = 'event_over_adjust_enable'">
                                        <xsl:element name="EventOverAdjust">
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

				<xsl:when test="$name = 'item_overallocation'">
					<xsl:element name="ItemOverAllocation">
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

                                <xsl:when test="$name = 'minimum_payment'">
                                        <xsl:element name="MinimumPayment">
                                                <xsl:value-of select="$value" />
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = 'minimum_refund'">
                                        <xsl:element name="MinimumRefund">
                                                <xsl:value-of select="$value" />
                                        </xsl:element>
                                </xsl:when>
				
				<xsl:when test="$name = 'cid_required'">
					<xsl:element name="CidRequired">
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

                               <xsl:when test="$name = 'cvv2_required'">
                                        <xsl:element name="Cvv2Required">
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

                               <xsl:when test="$name = 'dd_collect'">
                                        <xsl:element name="DDcollect">
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

				<xsl:when test="$name = &apos;dd_revalidation_interval&apos;">
                                        <xsl:element name="DDRevalidationInterval">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>                    

                                <xsl:when test="$name = &apos;cc_revalidation_interval&apos;">
                                        <xsl:element name="CCRevalidationInterval">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = 'cc_collect'">
                                        <xsl:element name="CCcollect">
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

			       	<xsl:when test="$name = 'event_adjustment_unallocation'">
					<xsl:element name="EventAdjustmentUnallocation">
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
										
	</xsl:template>
</xsl:stylesheet>

