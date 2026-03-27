<?xml version="1.0" encoding="UTF-8"?>
 <!--
  **************************************************************************
* Copyright (c) 2005, 2019, Oracle and/or its affiliates. All rights reserved.
  * This material is the confidential property of Oracle Corporation or its*
  * licensors and may be used, reproduced, stored or transmitted only in   *
  * accordance with a valid Oracle license or sublicense agreement.        *
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
				<BusParamsInvoicing>
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
				</BusParamsInvoicing>
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

				<xsl:when test="$name = 'ADST_Tax_Handle'">
					<xsl:element name="ADSTTaxHandle">
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
				
				<xsl:when test="$name = &apos;threshold_subords_summary&apos;">
					<xsl:element name="ThresholdSubordsSummary">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;threshold_subords_detail&apos;">
					<xsl:element name="ThresholdSubordsDetail">
						<xsl:value-of select="$value"/>
					</xsl:element>
				</xsl:when>
				
				<xsl:when test="$name = 'sub_ar_items_included'">
					<xsl:element name="SubARItemsIncluded">
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

                                <xsl:when test="$name = &apos;promotion_detail_display&apos;">
                                        <xsl:element name="PromotionDetailDisplay">
						<xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = 'enable_invoicing_integration'">
                                        <xsl:element name="EnableInvoicingIntegration">
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

				 <xsl:when test="$name = &apos;invoice_storage_type&apos;">
                                        <xsl:element name="InvoiceStorageType">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                 </xsl:when>

				 <xsl:when test="$name = &apos;in_operator_size&apos;">
                                        <xsl:element name="InOperatorSize">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

                                 <xsl:when test="$name = 'drop_extra_seq_disc_events'">
                                        <xsl:element name="DropExtraSeqDiscEvents">
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

                                 <xsl:when test="$name = 'include_extended_attr'">
                                        <xsl:element name="IncludeExtendedAttr">
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

				<xsl:when test="$name = &apos;inv_event_fetch_size&apos;">
                                        <xsl:element name="InvEventFetchSize">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

				<xsl:when test="$name = &apos;inv_item_fetch_size&apos;">
                                        <xsl:element name="InvItemFetchSize">
                                                <xsl:value-of select="$value"/>
                                        </xsl:element>
                                </xsl:when>

                                 <xsl:when test="$name = 'event_cache'">
                                        <xsl:element name="EventCache">
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

                                 <xsl:when test="$name = 'dis_fil_item_by_prune_time'">
                                        <xsl:element name="DisableFilterItemByPruneTime">
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

