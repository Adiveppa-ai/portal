<?xml version="1.0" encoding="UTF-8"?>
  <!--
  **************************************************************************
* Copyright (c) 2016, 2024, Oracle and/or its affiliates.
  *
  * This material is the confidential property of Oracle Corporation
  * or its licensors and may be used, reproduced, stored or transmitted
  * only in accordance with a valid Oracle license or sublicense agreement.
  **************************************************************************
  -->


<xsl:stylesheet version="1.0" xmlns="http://www.portal.com/schemas/BusinessConfig" xmlns:bc="http://www.portal.com/schemas/BusinessConfig" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" exclude-result-prefixes="bc">
	
	<xsl:output method="xml" indent="yes"/>
	
	<xsl:template match="/">
		<BusinessConfiguration xmlns="http://www.portal.com/schemas/BusinessConfig" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.portal.com/schemas/BusinessConfig business_configuration.xsd">
			<BusParamConfigurationClass>
				<BusParamsBilling>
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
				</BusParamsBilling>
			</BusParamConfigurationClass>
		</BusinessConfiguration>
	</xsl:template>

	<xsl:template match="//bc:Param">
			<xsl:variable name="name">
				<xsl:value-of select="bc:Name/text()"/>
			</xsl:variable>
		
			<xsl:variable name="value">
				<xsl:value-of select="bc:Value/text()"/>
			</xsl:variable>

			<xsl:choose>

				<xsl:when test="$name = &apos;billing_cycle_offset&apos;">
					<xsl:element name="BillingCycleOffset">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>
				
				<xsl:when test="$name = &apos;move_day_forward&apos;">
					<xsl:element name="MoveDayForward">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>firstDay</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>lastDay</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;remove_sponsoree&apos;">
					<xsl:element name="RemoveSponsoree">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;prod_end_offset_plan_transition&apos;">
					<xsl:element name="ProdEndOffsetPlanTransition">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;generate_journal_epsilon&apos;">
					<xsl:element name="GenerateJournalEpsilon">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;apply_cycle_fees_for_bill_now&apos;">
					<xsl:element name="ApplyCycleFeeForBillNow">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;generate_corrective_bill_no&apos;">
					<xsl:element name="GenerateCorrectiveBillNo">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;enable_corrective_invoices&apos;">
					<xsl:element name="EnableCorrectiveInvoices">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;enable_ssp_rev_recognition&apos;">
					<xsl:element name="SSPRevenueRecognition">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;allow_corrective_paid_bills&apos;">
					<xsl:element name="AllowCorrectivePaidBills">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;reject_payments_for_previous_bill&apos;">
					<xsl:element name="RejectPaymentsForPreviousBill">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;corrective_bill_threshold&apos;">
					<xsl:element name="CorrectiveBillThreshold">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;rerate_during_billing&apos;">
					<xsl:element name="RerateDuringBilling">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;auto_triggering_limit&apos;">
					<xsl:element name="AutoTriggeringLimit">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;skip_check_for_subordinates_billed&apos;">
                                        <xsl:element name="SkipCheckForSubordinatesBilled">
						 <xsl:choose>
							<xsl:when test="$value = &apos;0&apos;">
                                                	<xsl:text>disabled</xsl:text>
                                        		</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
                                                		<xsl:text>enabled</xsl:text>
                                        		</xsl:when>
                                         	 </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = &apos;validate_discount_dependency&apos;">
					<xsl:element name="ValidateDiscountDependency">
						<xsl:choose>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>discToDiscExcl</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;2&apos;">
								<xsl:text>discToPlanExcl</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;3&apos;">
								<xsl:text>enableBothExcl</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;4&apos;">
								<xsl:text>disableDiscToPlanExclAndNoPurTimeValidation</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;7&apos;">
								<xsl:text>enableBothExclAndNoPurTimeValidation</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;8&apos;">
								<xsl:text>returnOnFirstExcl</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;rollover_correction_during_billing&apos;">
					<xsl:element name="RolloverCorrectionDuringBilling">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = 'enable_ara'">
                                        <xsl:element name="EnableARA">
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
				
				<xsl:when test="$name = 'create_two_bill_now_bills_in_delay'">
                                        <xsl:element name="CreateTwoBillNowBillsInDelay">
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

				<xsl:when test="$name = &apos;sub_bal_validity&apos;">
                                        <xsl:element name="SubBalValidity">
                                                <xsl:choose>
                                                        <xsl:when test="$value = &apos;0&apos;">
                                                                <xsl:text>Cut</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = &apos;1&apos;">
                                                                <xsl:text>Maintain</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = &apos;2&apos;">
                                                                <xsl:text>Align</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

				
                                <xsl:when test="$name = &apos;sequential_cycle_discounting&apos;">
                                        <xsl:element name="SequentialCycleDiscounting">
                                                <xsl:choose>
                                                        <xsl:when test="$value = &apos;1&apos;">
                                                                <xsl:text>enabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = &apos;0&apos;">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>
				
				<xsl:when test="$name = 'cache_residency_distinction'">
					<xsl:element name="CacheResidencyDistinction">
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

				<xsl:when test="$name = &apos;default_business_profile&apos;">
                                        <xsl:element name="DefaultBusinessProfile">
                                                <xsl:choose>
                                                        <xsl:when test="$value = 'Convergent'">
                                                                <xsl:text>Convergent</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = 'Prepaid'">
                                                                <xsl:text>Prepaid</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = 'Postpaid'">
                                                                <xsl:text>Postpaid</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = 'Nonusage'">
                                                                <xsl:text>Nonusage</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = 'SLM'">
                                                                <xsl:text>SLM</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = &apos;custom_journal_update&apos;">
					<xsl:element name="CustomJournalUpdate">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

                                <xsl:when test="$name = &apos;generate_bill_for_child_billnow&apos;">
                                        <xsl:element name="GenerateBillForChildBillNow">
                                                <xsl:choose>
                                                        <xsl:when test="$value = &apos;1&apos;">
                                                                <xsl:text>enabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = &apos;0&apos;">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = 'apply_ar_parent_cycle_fee_first'">
                                        <xsl:element name="ApplyARParentCycleFeeFirst">
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

                                <xsl:when test="$name = &apos;wholesale_billing_system&apos;">
                                        <xsl:element name="WholesaleBillingSystem">
                                                 <xsl:choose>
                                                        <xsl:when test="$value = &apos;0&apos;">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = &apos;1&apos;">
                                                                <xsl:text>enabled</xsl:text>
                                                        </xsl:when>
						 </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = &apos;cycle_tax_interval&apos;">
                                        <xsl:element name="CycleTaxInterval">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = &apos;deal_purchase_for_closed_account&apos;">
                                        <xsl:element name="DealPurchaseForClosedAccount">
                                                 <xsl:choose>
                                                        <xsl:when test="$value = &apos;0&apos;">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = &apos;1&apos;">
                                                                <xsl:text>enabled</xsl:text>
                                                        </xsl:when>
                                                 </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = &apos;cycle_delay_align&apos;">
                                        <xsl:element name="CycleDelayAlign">
                                                 <xsl:choose>
                                                        <xsl:when test="$value = &apos;0&apos;">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = &apos;1&apos;">
                                                                <xsl:text>enabled</xsl:text>
                                                        </xsl:when>
                                                 </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = &apos;31day_billing&apos;">
                                        <xsl:element name="Billing31Day">
                                                 <xsl:choose>
                                                        <xsl:when test="$value = &apos;0&apos;">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = &apos;1&apos;">
                                                                <xsl:text>enabled</xsl:text>
                                                        </xsl:when>
                                                 </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = &apos;split_sponsor_item_by_member&apos;">
                                        <xsl:element name="SplitSponsorItemByMember">
						 <xsl:choose>
                                                        <xsl:when test="$value = '0'">
                                                		<xsl:text>disabled</xsl:text>
                                        	 	</xsl:when>
                                                        <xsl:when test="$value = '3'">
                                                		<xsl:text>enabled</xsl:text>
                                        		</xsl:when>
                                                        <xsl:when test="$value = '1'">
                                                		<xsl:text>onlyRealTime</xsl:text>
                                        		</xsl:when>
                                                        <xsl:when test="$value = '2'">
                                                		<xsl:text>onlyBatch</xsl:text>
                                        		</xsl:when>
                                         	 </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = &apos;staged_billing_fee_processing&apos;">
					<xsl:element name="StagedBillingFeeProcessing">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>
                                
				<xsl:when test ="$name = 'noncurrency_resource_journaling'">
					<xsl:element name="NonCurrencyResourceJournaling">
						<xsl:value-of select="$value" />
					</xsl:element>
				</xsl:when>

				<xsl:when test ="$name = &apos;location_mode_for_taxation&apos;">
					<xsl:element name="LocationModeForTaxation">
						<xsl:value-of select="$value" />
					</xsl:element>
				</xsl:when>


				<xsl:when test="$name = &apos;item_event_charge_discount_mode&apos;">
					<xsl:element name="ItemEventChargeDiscountMode">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>
				<xsl:when test="$name = &apos;zero_event_balances&apos;">
                                        <xsl:element name="ZeroEventBalances">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

                                <xsl:when test="$name = 'stop_bill_closed_accounts'">
                                        <xsl:element name="StopBillClosedAccounts">
                                                <xsl:choose>
                                                        <xsl:when test="$value = '0'">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = '1'">
                                                                <xsl:text>enabled</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>
                                <xsl:when test="$name = 'short_cycle'">
                                        <xsl:element name="ShortCycle">
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

                                <xsl:when test="$name = 'actg_type'">
                                        <xsl:element name="ActgType">
                                                <xsl:choose>
                                                        <xsl:when test="$value = '1'">
                                                                <xsl:text>open_item</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = '2'">
                                                                <xsl:text>balance_forward</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = &apos;segregate_journals_by_gl_period&apos;">
					<xsl:element name="SegregateJournalsByGLPeriod">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>
				<xsl:when test="$name = &apos;general_ledger_reporting&apos;">
					<xsl:element name="GeneralLedgerReporting">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;"> 
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>
				<xsl:when test="$name = &apos;backdating_past_gl_posted_date&apos;">
					<xsl:element name="BackdatingPastGlPostedDate">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>
				<xsl:when test="$name = &apos;acct_cycle_delay_period&apos;">
					<xsl:element name="AcctCycleDelayPeriod">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>
				<xsl:when test="$name = &apos;perf_advanced_tuning_settings&apos;">
					<xsl:element name="PerfAdvancedTuningSettings">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>
				<xsl:when test="$name = &apos;refresh_exchange_rate&apos;">
					<xsl:element name="ExchangeRateRefreshInterval">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>
				<xsl:when test="$name = &apos;deferred_tax_journaling&apos;">
					<xsl:element name="DeferredTaxJournaling">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;config_billing_delay&apos;">
					<xsl:element name="ConfigBillingDelay">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>
				<xsl:when test="$name = &apos;config_billing_cycle&apos;">
					<xsl:element name="ConfigBillingCycle">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;bill_dom_charges_on_current_bill&apos;">
					<xsl:element name="BillDomChargesOnCurrentBill">
						<xsl:choose>
							<xsl:when test="$value = &apos;1&apos;">
								<xsl:text>enabled</xsl:text>
							</xsl:when>
							<xsl:when test="$value = &apos;0&apos;">
								<xsl:text>disabled</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

                               <xsl:when test="$name = &apos;itemized_tax_calculation&apos;">
                                        <xsl:element name="ItemizedTaxCalculation">
                                                <xsl:choose>
                                                        <xsl:when test="$value = &apos;1&apos;">
                                                                <xsl:text>enabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = &apos;0&apos;">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = &apos;apply_folds&apos;">
                                        <xsl:element name="ApplyFolds">
                                                <xsl:choose>
                                                        <xsl:when test="$value = &apos;1&apos;">
                                                                <xsl:text>enabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = &apos;0&apos;">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = &apos;apply_rollover&apos;">
                                        <xsl:element name="ApplyRollover">
                                                <xsl:choose>
                                                        <xsl:when test="$value = &apos;1&apos;">
                                                                <xsl:text>enabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = &apos;0&apos;">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = &apos;cancel_tolerance&apos;">
                                        <xsl:element name="CancelTolerance">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = &apos;add_child_due_in_intermediate_parent_bill&apos;">
                                        <xsl:element name="AddChildDueInIntermediateParentBill">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

			</xsl:choose>

	</xsl:template>
</xsl:stylesheet>
