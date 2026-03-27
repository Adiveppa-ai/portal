<?xml version="1.0" encoding="UTF-8"?>
<!--
   **************************************************************************
* Copyright (c) 2005, 2022, Oracle and/or its affiliates. All rights reserved.
  *
  * This material is the confidential property of Oracle Corporation
  * or its licensors and may be used, reproduced, stored or transmitted
  * only in accordance with a valid Oracle license or sublicense agreement.
   **************************************************************************
 -->

<xsl:stylesheet version="1.0"
  xmlns="http://www.portal.com/schemas/BusinessConfig"
  xmlns:bc="http://www.portal.com/schemas/BusinessConfig"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform" exclude-result-prefixes="bc">

  <xsl:output method="xml" indent="yes"/>

  <xsl:template match="/">
    <BusinessConfiguration xmlns="http://www.portal.com/schemas/BusinessConfig"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.portal.com/schemas/BusinessConfig business_configuration.xsd">
      <BusParamConfigurationClass>
        <BusParamsSubscription>
          <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
        </BusParamsSubscription>
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

      <xsl:when test="$name = &apos;discount_based_on_contract_days_feature&apos;">
        <xsl:element name="DiscountBasedOnContractDaysFeature">
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

      <xsl:when test="$name = &apos;best_pricing&apos;">
        <xsl:element name="BestPricing">
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

      <xsl:when test="$name = &apos;rollover_transfer&apos;">
        <xsl:element name="RolloverTransfer">
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

      <xsl:when test="$name = &apos;automated_monitor_setup&apos;">
        <xsl:element name="AutomatedMonitorSetup">
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

      <xsl:when test="$name = &apos;enable_product_validation&apos;">
        <xsl:element name="EnableProductValidation">
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

      <xsl:when test="$name = &apos;max_services_to_search&apos;">
        <xsl:element name="MaxServicesToSearch">
          <xsl:value-of select="$value"/>
        </xsl:element>
      </xsl:when>

      <xsl:when test="$name = &apos;cancel_full_discount_immediate&apos;">
        <xsl:element name="CancelFullDiscountImmediate">
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

      <xsl:when test="$name = &apos;tailormade_products_search&apos;">
        <xsl:element name="TailormadeProductsSearch">
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

      <xsl:when test="$name = &apos;cancelled_offerings_search&apos;">
        <xsl:element name="CancelledOfferingsSearch">
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

      <xsl:when test="$name = &apos;allow_backdate_with_no_rerate&apos;">
        <xsl:element name="AllowBackdateNoRerate">
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

      <xsl:when test="$name = &apos;subs_disable_74_backdated_validations&apos;">
        <xsl:element name="SubsDis74BackDateValidations">
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

      <xsl:when test="$name = &apos;transfer_scheduled_actions&apos;">
        <xsl:element name="TransferScheduledActions">
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

      <xsl:when test="$name = &apos;transfer_rerate_requests&apos;">
        <xsl:element name="TransferRerateRequests">
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

      <xsl:when test="$name = &apos;event_adjustments_during_cancellation&apos;">
        <xsl:element name="EventAdjustmentsDuringCancellation">
          <xsl:value-of select="$value"/>
        </xsl:element>
      </xsl:when>

      <xsl:when test="$name = &apos;return_multiple_plan_instances_purchased&apos;">
        <xsl:element name="MultiplePlan">
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

      <xsl:when test="$name = &apos;use_priority_for_subscription_fees&apos;">
        <xsl:element name="UsePrioritySubscriptionFees">
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

      <xsl:when test="$name = &apos;recreate_during_subscription_transfer&apos;">
        <xsl:element name="RecreateDuringSubscriptionTransfer">
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

      <xsl:when test="$name = &apos;create_two_events_in_first_cycle&apos;">
        <xsl:element name="CreateTwoEventsInFirstCycle">
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

      <xsl:when test="$name = &apos;apply_proration_rules&apos;">
        <xsl:element name="ApplyProrationRules">
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

      <xsl:when test="$name = &apos;timestamp_rounding&apos;">
        <xsl:element name="TimestampRounding">
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

      <xsl:when test="$name = &apos;get_rate_plan_from_cache&apos;">
        <xsl:element name="GetRatePlanFromCache">
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

      <xsl:when test="$name = &apos;apply_validity_discount_rules&apos;">
        <xsl:element name="ApplyValidityDiscountRules">
          <xsl:value-of select="$value"/>
        </xsl:element>
      </xsl:when>

      <xsl:when test="$name = &apos;max_retry_count&apos;">
        <xsl:element name="MaxRetryCount">
          <xsl:value-of select="$value"/>
        </xsl:element>
      </xsl:when>

      <xsl:when test="$name = &apos;loan_repayment_percent&apos;">
        <xsl:element name="LoanRepaymentPercent">
          <xsl:value-of select="$value"/>
        </xsl:element>
      </xsl:when>

      <xsl:when test="$name = &apos;apply_charge_on_inactive_or_cancel_product&apos;">
        <xsl:element name="ApplyChargeOnInactiveOrCancelProduct">
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

      <xsl:when test="$name = &apos;apply_rollover_before_cycle_fees&apos;">
        <xsl:element name="ApplyRolloverBeforeCycleFees">
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

      <xsl:when test="$name = &apos;service_transfer_enabled&apos;">
        <xsl:element name="ServiceTransferEnabled">
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

      <xsl:when test="$name = &apos;auto_group_sharing_setup&apos;">
        <xsl:element name="AutomatedGroupSharingSetup">
          <xsl:value-of select="$value"/>
        </xsl:element>
      </xsl:when>

      <xsl:when test="$name = &apos;backdate_trigger_auto_rerate&apos;">
        <xsl:element name="BackdateTriggerAutoRerate">
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

      <xsl:when test="$name = &apos;reduce_loan_bal_during_recovery&apos;">
        <xsl:element name="ReduceLoanBalDuringRecovery">
          <xsl:value-of select="$value"/>
        </xsl:element>
      </xsl:when>

      <xsl:when test="$name = &apos;num_billing_cycles&apos;">
        <xsl:element name="NumBillingCycles">
          <xsl:value-of select="$value"/>
        </xsl:element>
      </xsl:when>

      <xsl:when test="$name = &apos;event_fetch_size&apos;">
        <xsl:element name="EventFetchSize">
          <xsl:value-of select="$value"/>
        </xsl:element>
      </xsl:when>

      <xsl:when test="$name = &apos;propagate_discount&apos;">
        <xsl:element name="PropagateDiscount">
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

      <xsl:when test="$name = &apos;rate_change&apos;">
        <xsl:element name="RateChange">
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

      <xsl:when test="$name = &apos;keep_cancelled_products_or_discounts&apos;">
        <xsl:element name="KeepCancelledProductsOrDiscounts">
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

      <xsl:when test="$name = &apos;cdc_line_cancel_day_include&apos;">
        <xsl:element name="CdcLineCancelDayInclude">
          <xsl:value-of select="$value"/>
        </xsl:element>
      </xsl:when>

      <xsl:when test="$name = &apos;cdc_line_create_day_include&apos;">
        <xsl:element name="CdcLineCreateDayInclude">
          <xsl:value-of select="$value"/>
        </xsl:element>
      </xsl:when>

      <xsl:when test="$name = &apos;timestamp_rounding_during_apply_loan&apos;">
        <xsl:element name="TimestampRoundingDuringApplyLoan">
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

      <xsl:when test="$name = &apos;del_sharing_grp_during_term&apos;">
        <xsl:element name="DeleteSharingGroupDuringTermination">
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

    </xsl:choose>

  </xsl:template>

</xsl:stylesheet>
