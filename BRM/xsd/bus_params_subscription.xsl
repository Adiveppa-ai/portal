<?xml version="1.0" encoding="UTF-8"?>
 <!--
  **************************************************************************
* Copyright (c) 2005, 2022, Oracle and/or its affiliates. All rights reserved.
  * This material is the confidential property of Oracle Corporation or its*
  * licensors and may be used, reproduced, stored or transmitted only in   *
  * accordance with a valid Oracle license or sublicense agreement.        *
  **************************************************************************
 -->
<xsl:stylesheet
    version="1.0"
    xmlns="http://www.portal.com/schemas/BusinessConfig"
    xmlns:bc="http://www.portal.com/schemas/BusinessConfig"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" exclude-result-prefixes="bc">

  <xsl:output method="xml" indent="yes"/>

  <xsl:template match="/">
    <BusinessConfiguration
        xmlns="http://www.portal.com/schemas/BusinessConfig"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xsi:schemaLocation="http://www.portal.com/schemas/BusinessConfig business_configuration.xsd">
      <BusParamConfiguration>
        <BusParamConfigurationList>
          <ParamClass desc="Business logic parameters for Subscription" name="subscription">
            <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsSubscription/bc:*"/>
          </ParamClass>
        </BusParamConfigurationList>
      </BusParamConfiguration>
    </BusinessConfiguration>
  </xsl:template>

  <xsl:template match="bc:DiscountBasedOnContractDaysFeature">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>discount_based_on_contract_days_feature</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to enable contract days counter feature. This needs to be set to 1 if the accounts contain the resource contract days counter.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:BestPricing">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>best_pricing</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to enable or disable best pricing feature. 1 means enabled.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:RolloverTransfer">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>rollover_transfer</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to enable or disable rollover transfer feature. 1 means enabled.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

   <xsl:template match="bc:AutomatedMonitorSetup">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>automated_monitor_setup</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to enable or disable automated monitor setup. Affects processing logic.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:BillTimeDiscountWhen">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>bill_time_discount_when</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to indicate time to apply discount during billing. This discount could be applied either at each accounting cycle time or at the billing cycle time (i.e in the last accounting cycle in the case of multi-month billing cycle). The posible values are 0 (apply discount at each accounting cycle) and 1 (apply discount at billing cycle time). Default is 0.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

 <xsl:template match="bc:ProductLevelValidation">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>enable_product_validation</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to enable or disable product level validation during Deal Dependency checks. 1 means enabled, 0 means disabled.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

 <xsl:template match="bc:MaxServicesToSearch">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>max_services_to_search</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
         Parameter to configure the number of services to search in at a time during the retrieval of purchased offerings for a billinfo by the opcode PCM_OP_SUBSCRIPTION_GET_PURCHASED_OFFERINGS. Default is 5. Increasing the value might cause the select statement to fail, depending on the length of the poids involved in the search. 
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
        <xsl:variable name="value" select="normalize-space(text())"/>
        <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>

 <xsl:template match="bc:CancelFullDiscountImmediate">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>cancel_full_discount_immediate</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to enable or disable immediate cancellation of discount with proration setting of FULL. The posible values are 0(set end date to cycle end) and 1 (set end date and cancel the discount immediately). Default is 0.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

 <xsl:template match="bc:TailormadeProductsSearch">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>tailormade_products_search</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to enable or disable the search for tailormade products during the application of cycle fees. 1 means enabled, 0 means disabled. This parameter should be disabled only if advanced customization of products has not been used.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

 <xsl:template match="bc:CancelledOfferingsSearch">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>cancelled_offerings_search</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to enable or disable the search for cancelled offerings during billing. 1 means enabled, 0 means disabled.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:AllowBackdateNoRerate">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>allow_backdate_with_no_rerate</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to allow backdating beyond the number of billing cycles specified in the cm pin.conf entry 'fm_subs num_billing_cycles', but without creating  the auto-rerate job. The possible values are 0 (Do not allow backdating beyond 'num_billing_cycles') and 1 (Allow backdating beyond 'num_billing_cycles' without creating auto-rerate job). Default is 0. 
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:SubsDis74BackDateValidations">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>subs_disable_74_backdated_validations</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Parameter to disable the backdated validations in 7.4. The possible values are 0 and 1. Default is 0. 
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:TransferScheduledActions">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>transfer_scheduled_actions</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to trigger policy opcode PCM_OP_SUBSCRIPTION_POL_POST_TRANSFER_SUBSCRIPTION which will transfer /schedule objects to new account. The possible values are 0 (Do not trigger policy opcode) and 1 (Trigger policy opcode). Default is 0.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:TransferRerateRequests">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>transfer_rerate_requests</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to disable creating rerate requests as part of subscription transfer. Default is 1(enabled). If disabled rerate requests will not be created as part of OOB subscription transfer
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;disabled&apos;">
            <xsl:text>0</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>1</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

 <xsl:template match="bc:EventAdjustmentsDuringCancellation">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>event_adjustments_during_cancellation</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Parameter to allow accounting for event adjustments on cycle fees while calculating the refund during product inactivation or cancellation. The possible values are 0 (Do not consider event adjustments on the cycle fees while calculating refund) and 1 (Consider event adjustments on the cycle fees and refund based on original charge minus adjustments). Default is 0."
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
        <xsl:variable name="value" select="normalize-space(text())"/>
        <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:MultiplePlan">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>return_multiple_plan_instances_purchased</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	           Parameter to return multiple instances of the plan purchased. The posible values are 0(Return a single instance of the plan purchased) and 1(Return all the instances of the plan purchased). Default is set to 0.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;disabled&apos;">
            <xsl:text>0</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>1</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:UsePrioritySubscriptionFees">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>use_priority_for_subscription_fees</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to make subscription charging use product priority while applying cycle fees (/event/billing/product/fee/cycle) during billing/deal purchase/cancel. This does not take care of discount priority or refunds due to any other operations like inactivations for now. MTA utilities like pin_cycle_fees does not support product prioritization when used with -defer_cancel or -cancel. This may impact performance if large number of offers are present, hence use judiciously. Possible values are 0 (do not use the priority) and 1 (use priority).
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:RecreateDuringSubscriptionTransfer">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>recreate_during_subscription_transfer</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	If this parameter is true then objects will be recreated in a cease+reprovide model. Tranfer across the schemas is possible only if this parameter is true.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:CreateTwoEventsInFirstCycle">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>create_two_events_in_first_cycle</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Parameter to create two events if the product end date is set in the first cycle. If this parameter is enabled, then there will be a charge for full cycle and then there will be a refund from product end to end of the cycle.By default this parameter will be disabled.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:ApplyProrationRules">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>apply_proration_rules</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Parameter to indicate whether proration rules need to be applied when purchase or cancellation occur exactly on cycle boundaries. By default this parameter is disabled and proration rules will not be applied in such cases. If enabled the rules will be applied.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:TimestampRounding">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>timestamp_rounding</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Rounds timestamps of purchased products and discounts. can have 2 values: 1(round timestamp) and (0 do not round timestamp)
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:GetRatePlanFromCache">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>get_rate_plan_from_cache</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	During purchase product BRM will try to fetch all the rate plans available for the product from cache. If the RATE_PLANS are huge then it will cause performance issue during purchase product. If this parameter is disabled then BRM will not fetch RATE_PLANS thus increasing performance during purchase product which might impact billing performance. Default value is enabled
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:ApplyValidityDiscountRules">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>apply_validity_discount_rules</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Parameter to indicate whether discount validity rules need to be applied. Parameter values can be 0 (default) indicates discount validity rules will not be applied if the discount purchase/cancel happens exactly on cycle boundaries, value 0x01(decimal value 1) indicates rules will be applied in all cases, value 0x02(decimal value 2) indicates force reversal of charges if the cancel happens on the same date of discount purchase irrespactive of rules configured. Values can be clubbed(added) together to achieve multiple functionality.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:variable name="value" select="normalize-space(text())"/>
      <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>

       <xsl:template match="bc:CreateRerateJobDuringCancel">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>create_rerate_job_during_cancel</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Indicates whether to rerate the job during cancellation or not. (1 - means, rerate job will be 
				created. 0 - means, no rerate job will be created).
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


  <xsl:template match="bc:DefaultZoneMapName">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>default_zonemap_name</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Default zonemap name used for location based operations.
      </xsl:element>
      <xsl:element name="Type">STR</xsl:element>
      <xsl:variable name="value" select="normalize-space(text())"/>
      <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>

 <xsl:template match="bc:MaxRetryCount">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>max_retry_count</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to configure the maximum retry count to be considered before sending an error in case of the rental failure. Default value is 0.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
        <xsl:variable name="value" select="normalize-space(text())"/>
        <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>
 
  <xsl:template match="bc:ApplyChargeOnInactiveOrCancelProduct">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>apply_charge_on_inactive_or_cancel_product</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
                   Parameter to apply charge on a product even if the product is in inactive or cancelled state based on the configuration set on product charging behavior from PDC. Default is set to 0.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;disabled&apos;">
            <xsl:text>0</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>1</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

   <xsl:template match="bc:LoanRepaymentPercent">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>loan_repayment_percent</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to configure the percentage going towards loan repayment in case of underpayment, It ranges from 0 to 100, 0 being No amount goes towards loan and 100 being entire amount. Default value is 100
      </xsl:element>
      <xsl:element name="Type">DECIMAL</xsl:element>
        <xsl:variable name="value" select="normalize-space(text())"/>
        <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:ApplyRolloverBeforeCycleFees">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>apply_rollover_before_cycle_fees</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Parameter to control whether to call PCM_OP_SUBSCRIPTION_CYCLE_ROLLOVER during PCM_OP_SUBSCRIPTION_CYCLE_FORWARD opcode. The Default value is disabled (0) by default. If enabled (1) , cycle_rollover will be called.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;disabled&apos;">
            <xsl:text>0</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>1</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

<xsl:template match="bc:ServiceTransferEnabled">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>service_transfer_enabled</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to control whether the service transfer feature is enabled. The default value is enabled (1). If disabled (0), the service transfer feature will not be allowed.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:AutomatedGroupSharingSetup">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>auto_group_sharing_setup</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to control whether to Automatic Sharing for DSG or PSG is enabled. The Default value is disabled (0) by default. For DSG value (1) , PSG value (2), For both DSG and PSG value 3.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
        <xsl:variable name="value" select="normalize-space(text())"/>
        <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:BackdateTriggerAutoRerate">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>backdate_trigger_auto_rerate</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
               Parameters to control auto-rerate job objects used by pin_rerate. The default value is disabled (0) indicates rerate object is not automatically created for backdated actions that could cause the need for rerating. If enabled (1), the auto-rerate feature is automatically created.The application pin_rerate can look for these objects and use them to determine which events need rerating and how far back to go.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;disabled&apos;">
            <xsl:text>0</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>1</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:ReduceLoanBalDuringRecovery">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>reduce_loan_bal_during_recovery</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Parameter to configure if loan balance should be reduced during recovery. Default value is 0 (disabled)
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:variable name="value" select="normalize-space(text())"/>
      <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>

   <xsl:template match="bc:NumBillingCycles">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>num_billing_cycles</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Specifies the maximum number of billing cycles allowed between the current time and the backdated event time of a backdated operation.The default is 1 billing cycle
      </xsl:element>
      <xsl:element name="Type">DECIMAL</xsl:element>
        <xsl:variable name="value" select="normalize-space(text())"/>
        <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>

   <xsl:template match="bc:EventFetchSize">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>event_fetch_size</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Size used for step search while searching events in rerating/rebilling This value can be changed as per the required number of events to be searched. Default Value is 10000
      </xsl:element>
      <xsl:element name="Type">DECIMAL</xsl:element>
        <xsl:variable name="value" select="normalize-space(text())"/>
        <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:PropagateDiscount">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>propagate_discount</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
		Enable immediate propagation of shared discount when a new discount is added/deleted to the group or a member subscribes/unsubscribes to the group. By default, it is disabled. Set the value to enabled(1) to enable.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;disabled&apos;">
            <xsl:text>0</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>1</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:RateChange">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>rate_change</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
		Enables or disables the enhanced rate change management feature. If this feature is enabled then rate changes for cycle events in the middle of the cycle will be handled according to old and new rates prorated. If disabled only the old rate will be applied.Default value is  Disable which can be set by disable(0) for enhanced rate change management feature. To Enable enhanced rate change management feature enabled(1) need to be set.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;disabled&apos;">
            <xsl:text>0</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>1</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <xsl:template match="bc:KeepCancelledProductsOrDiscounts">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>keep_cancelled_products_or_discounts</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
        Specifies whether to keep canceled products and discounts. Default Value is Enabled (1), keeps the canceled products and discounts. If disabled (0), Deletes the canceled products and discounts. If the canceled products and discounts are deleted, then rerating will not work.
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
            <xsl:text>1</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>0</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

   <xsl:template match="bc:CdcLineCancelDayInclude">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>cdc_line_cancel_day_include</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
          Parameter that decides whether the day on which the Line was created be counted to decrement contract day Default value of line_cancel_day_include is configured as 1
      </xsl:element>
      <xsl:element name="Type">DECIMAL</xsl:element>
        <xsl:variable name="value" select="normalize-space(text())"/>
        <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>

   <xsl:template match="bc:CdcLineCreateDayInclude">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>cdc_line_create_day_include</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
         Parameter that decides whether the day on which the Line was created be counted to increment contract days Default value of cdc_line_create_day_include is configured as 1
      </xsl:element>
      <xsl:element name="Type">DECIMAL</xsl:element>
        <xsl:variable name="value" select="normalize-space(text())"/>
        <xsl:element name="Value">
        <xsl:value-of select="$value"/>
      </xsl:element>
    </xsl:element>
  </xsl:template>

    <xsl:template match="bc:TimestampRoundingDuringApplyLoan">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>timestamp_rounding_during_apply_loan</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Rounds timestamps of loan sub-balance bucket during apply loan. can have 2 values: 1(round timestamp) and (0 do not round timestamp). By default it is 0(disabled).
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;disabled&apos;">
            <xsl:text>0</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>1</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>

    <xsl:template match="bc:DeleteSharingGroupDuringTermination">
    <xsl:element name="Param">
      <xsl:element name="Name">
        <xsl:text>del_sharing_grp_during_term</xsl:text>
      </xsl:element>
      <xsl:element name="Desc">
	Parameter to control if sharing group member or sharing group should be deleted during account/service termination. can have 2 values: 1(enabled means delete) and 0 (disabled do not delete). By default it is 0(disabled).
      </xsl:element>
      <xsl:element name="Type">INT</xsl:element>
      <xsl:element name="Value">
        <xsl:choose>
          <xsl:when test="normalize-space(text()) = &apos;enabled&apos;">
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
