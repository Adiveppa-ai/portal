<?xml version="1.0" encoding="UTF-8"?>
 <!--
  ***************************************************************************
* Copyright (c) 2005, 2019, Oracle and/or its affiliates. All rights reserved.
  * This material is the confidential property of Oracle Corporation or its *
  * licensors and may be used, reproduced, stored or transmitted only in    *
  * accordance with a valid Oracle license or sublicense agreement.         *
  ***************************************************************************
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
				<ParamClass desc="Business logic parameters for Invoicing" name="Invoicing">
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsInvoicing/bc:*"/>
				</ParamClass>
			</BusParamConfigurationList>
			</BusParamConfiguration>
		</BusinessConfiguration>
	</xsl:template>
	
	<xsl:template match="bc:ADSTTaxHandle">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>ADST_Tax_Handle</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Enable/Disable ADST Tax handling Feature for Invoicing. 
				Parameter values can be 0 (disable), 1 (enable). Default is 0 (disabled).
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

	<xsl:template match="bc:ThresholdSubordsSummary">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>threshold_subords_summary</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Threshold for number of subordinates for summary invoices.
				(0=default(no split invoices for hierarchy))
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:variable name="value" select="normalize-space(text())"/>
			<xsl:element name="Value">
				<xsl:value-of select="$value"/>
			</xsl:element>
		</xsl:element>
	</xsl:template>

	<xsl:template match="bc:ThresholdSubordsDetail">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>threshold_subords_detail</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Threshold for number of subordinates for detail invoice.
				(0=default(no split invoices for hierarchy))
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:variable name="value" select="normalize-space(text())"/>
			<xsl:element name="Value">
				<xsl:value-of select="$value"/>
			</xsl:element>
		</xsl:element>
	</xsl:template>
	
	<xsl:template match="bc:SubARItemsIncluded">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>sub_ar_items_included</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Indicates whether Subordinate account invoice includes AR items or not.
				(0- default , AR items not included and 1 - AR items included)
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

        <xsl:template match="bc:PromotionDetailDisplay">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>promotion_detail_display</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Indicates whether promotion details should be shown on the invoice.
                                (1- default , show promotion details for non-wholesale accounts, 
				 0 - Do not show promotion details, 
				 2- show promotions details for wholesale as well as non-wholesale accounts)
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
			<xsl:element name="Value">
				<xsl:value-of select="$value"/>
                        </xsl:element>
                </xsl:element>
        </xsl:template>
	
	<xsl:template match="bc:EnableInvoicingIntegration">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>enable_invoicing_integration</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				Enable/Disable BRM-BIP integration for final invoice document generation.
				Parameter values can be 0 (disable), 1 (enable). Default is 0 (disabled)	
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

	<xsl:template match="bc:InvoiceStorageType">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>invoice_storage_type</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                               	Format of invoice which needs to be stored in BRM database.
				Parameter values can be 0 (flist), 1 (xml). Default is 0 (flist)	 
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>

                </xsl:element>
        </xsl:template>

	<xsl:template match="bc:InOperatorSize">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>in_operator_size</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				IN operator size in sql statement limited by string length.
				Parameter values can be based on database capacity. 
				Default value is 500.The value can be less than 500 but cannot be greater than 500.
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>

                </xsl:element>
        </xsl:template>
        
        <xsl:template match="bc:DropExtraSeqDiscEvents">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>drop_extra_seq_disc_events</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Indicates whether to drop from the invoice the events related to non-relevant discounts when a discount is being purchased or cancelled during sequential discounting.
                                (1- Drop non-relevant sequential discounting events, and 0 - default, Do not drop non-relevant sequential discounting events)
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

        <xsl:template match="bc:IncludeExtendedAttr">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>include_extended_attr</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Indicates whether to include custom event attributes, pricing information, etc. in the invoice.
                                (1- Include extra base and customized fields, and 0 - default, Do not extra base and customized fields)
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

        <xsl:template match="bc:ARItemsInCorrectiveInvoice">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>ar_items_in_corr_invoice</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Indicates whether to include AR items only in its corresponding Corrective Invoice
                                (0- default , AR items are displayed in regular invoice if Corrective invoice is not generated and 1 - AR items included only in its Corrective Invoice)
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

        <xsl:template match="bc:InvEventFetchSize">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>inv_event_fetch_size</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				Size used for step search while searching events. This value can be changed as per the required number of events to be searched
				Default Value is 10000
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>

                </xsl:element>
        </xsl:template>

        <xsl:template match="bc:InvItemFetchSize">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>inv_item_fetch_size</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				Size used for step search while searching items. This value can be changed as per the required number of items to be searched
				Default Value is 10000
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:variable name="value" select="normalize-space(text())"/>
                        <xsl:element name="Value">
                                <xsl:value-of select="$value"/>
                        </xsl:element>

                </xsl:element>
        </xsl:template>

        <xsl:template match="bc:EventCache">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>event_cache</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
			Enables or disables the event cache for the PIN_FLD_BAL_IMPACTS array. You can save the cache space for invoicing by turning off this entry.The value for this entry can be.
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
        <xsl:template match="bc:DisableFilterItemByPruneTime">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>dis_fil_item_by_prune_time</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
				Indicates whether to filter invoice items by pruning time
				(disabled - default , items are filtered by pruning time , enabled - items are not filtered by pruning time)
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
