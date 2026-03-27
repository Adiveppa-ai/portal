<?xml version="1.0" encoding="UTF-8"?>

  <!--
  **************************************************************************
* Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
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
			<BusParamConfiguration>
			<BusParamConfigurationList>
				<ParamClass desc="Business logic parameters for AR" name="ar">
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsAR/bc:*"/>
				</ParamClass>
			</BusParamConfigurationList>
			</BusParamConfiguration>
		</BusinessConfiguration>
	</xsl:template>
	
	<xsl:template match="bc:SearchBillAmount">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>search_bill_amount_enable</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Enable/Disable Search of Bill Object by matching Bill Amount. The parameter values can be 0 (disabled), 1 (enabled). Default is 0 (disabled).
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
	
	
	<xsl:template match="bc:AutoWriteOffReversal">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>auto_writeoff_reversal_enable</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Enable/Disable automatic write-off reversal on Payment receipt.The Parameter values can be 0 (disabled), 1 (enabled). Default is 0 (disabled).
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
	
	<xsl:template match="bc:WriteOffLevel">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>writeoff_level</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Level of writeoff to be tracked for the purpose of writeoff reversal. Default is account. Currently only account and billinfo level writeoff reversal is supported.
			</xsl:element>
			<xsl:element name="Type">STR</xsl:element>
			<xsl:element name="Value">
				<xsl:choose>
					<xsl:when test="normalize-space(text()) = 'account'">
						<xsl:text>account</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'billinfo'">
						<xsl:text>billinfo</xsl:text>
					</xsl:when>
				</xsl:choose>
			</xsl:element>
		</xsl:element>
	</xsl:template>

<xsl:template match="bc:PaymentIncentive">
	<xsl:element name="Param">
		<xsl:element name="Name">
			<xsl:text>payment_incentive_enable</xsl:text>
		</xsl:element>
		<xsl:element name="Desc">
			Enable/Disable Payment incentives on early payment in full. The parameter values can be 0 (disabled), 1 (enabled). Default is 0 (disabled).
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
	
	<xsl:template match="bc:PaymentSuspense">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>payment_suspense_enable</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Enable/Disable Payment Suspense Management . The parameter values can be 0 (disabled), 1 (enabled). Default is 0 (disabled).
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

	<xsl:template match="bc:NonrefundableCreditItems">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>nonrefundable_credit_items</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				Types of items which will NOT be refunded in case of outstanding credit balance.
The values should be separated by commas. Default is /item/refund .
                        </xsl:element>
                        <xsl:element name="Type">STR</xsl:element>
			<xsl:element name="Value">
				<xsl:variable name="value">
					<xsl:value-of select="normalize-space(text())"></xsl:value-of>
				</xsl:variable>
				<xsl:choose>
					<xsl:when test="$value">
						<xsl:value-of select="$value" />
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="'/item/refund'" />
					</xsl:otherwise>
				</xsl:choose>
			</xsl:element>
                </xsl:element>
        </xsl:template>

	<xsl:template match="bc:EventOverAdjust">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>event_over_adjust_enable</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Enable/Disable over adjustment of events. The parameter values can be 0 (disabled), 1 (enabled). Default is 0 (disabled).
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

	<xsl:template match="bc:ItemOverAllocation">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>item_overallocation</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Enable/Disable Overallocation to billable items during payment. The parameter values can be 0 (disabled), 1 (enabled). Default is 1 (enabled).
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

        <xsl:template match="bc:MinimumPayment">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>minimum_payment</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				Specifies minimum bill amount for credit card collection. The value is expressed in account currency.
                        </xsl:element>
                        <xsl:element name="Type">DECIMAL</xsl:element>
                        <xsl:element name="Value">
                                <xsl:variable name="value">
                                        <xsl:value-of select="normalize-space(text())"></xsl:value-of>
                                </xsl:variable>
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>

        <xsl:template match="bc:MinimumRefund">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>minimum_refund</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				Specifies minimum value for refund.
                        </xsl:element>
                        <xsl:element name="Type">DECIMAL</xsl:element>
                        <xsl:element name="Value">
                                <xsl:variable name="value">
                                        <xsl:value-of select="normalize-space(text())"></xsl:value-of>
                                </xsl:variable>
				<xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>

	<xsl:template match="bc:BillPaymentDeallocation">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>bill_payment_deallocation</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Enable/Disable payment deallocation during bill adjustment. The parameter values can be 0 (disabled), 1 (enabled). Default is 0 (disabled).
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
 
         <xsl:template match="bc:UseEventRoundingRulesForAdjustment">
                 <xsl:element name="Param">
                         <xsl:element name="Name">
                                 <xsl:text>use_event_rounding_rules_for_adjustment</xsl:text>
                         </xsl:element>
                         <xsl:element name="Desc">
                                 Enable/Disable using rounding rule of event for adjustment. The parameter values can be 0 (disabled), 1 (enabled). Default is 0 (disabled).
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

         <xsl:template match="bc:PINlessDebitProcessing">
                 <xsl:element name="Param">
                         <xsl:element name="Name">
                                 <xsl:text>pinless_debit_processing</xsl:text>
                         </xsl:element>
                         <xsl:element name="Desc">
                                 Enable/Disable PINless debit processing. The parameter values can be 0 (disabled), 1 (enabled). Default is 0 (disabled).
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
		<xsl:template match="bc:CidRequired">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>cid_required</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Require credit-card verification (CID) data for American Express card transactions. The parameter values can be 0 (disabled), 1 (enabled). Default is 0 (disabled).
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
	 
	 <xsl:template match="bc:Cvv2Required">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>cvv2_required</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
For Paymentech credit-card processor users, specifies whether to require credit-card verification (CVV) data for Visa card transactions, as a method of fraud prevention.
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
	 

	<xsl:template match="bc:DDcollect">
                 <xsl:element name="Param">
                         <xsl:element name="Name">
                                 <xsl:text>dd_collect</xsl:text>
                         </xsl:element>
                         <xsl:element name="Desc">
                                Enable/Disable collection of current balance during registration. The parameter values can be disabled (0), enabled (1). Default is enabled (1).
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

	<xsl:template match="bc:DDRevalidationInterval">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>dd_revalidation_interval</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Specifies the time limit, in seconds, before Infranet tries to revalidate a customer's direct-debit account during registration. Infranet won't attempt to validate an account if a previous validation failed and the specified time hasn't elapsed. The default time limit is 3600 seconds (1 hour).
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>

	<xsl:template match="bc:CCRevalidationInterval">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>cc_revalidation_interval</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Specifies the time limit, in seconds, for trying to revalidate a customer's credit card during registration. Portal won't attempt to validate a credit card if a previous validation failed and the specified time hasn't elapsed. The default time limit is 3600 seconds (60 minutes).
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:variable name="value" select="normalize-space(text())"/>
			<xsl:element name="Value">
				<xsl:value-of select="$value"/>
			</xsl:element>
		</xsl:element>
	</xsl:template>

	<xsl:template match="bc:CCcollect">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>cc_collect</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Enable/Disable collection of current balance during registration. The parameter values can be disabled (0), enabled (1). Default is enabled (1).
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

	<xsl:template match="bc:EventAdjustmentUnallocation">
                 <xsl:element name="Param">
                         <xsl:element name="Name">
                                 <xsl:text>event_adjustment_unallocation</xsl:text>
                         </xsl:element>
                         <xsl:element name="Desc">
				Parameter to control the consumable (transfer) amount in event adjustment 
				such that the sign of an item due will not change.
                                Enable/Disable PINless debit processing. The parameter values can be 0 (disabled), 1 (enabled).
				Default is 0 (disabled).
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
