<?xml version="1.0" encoding="UTF-8"?>
 <!--
  ***************************************************************************
  * Copyright (c) 2021, Oracle and/or its affiliates. All rights reserved.
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
				<ParamClass desc="Business logic parameters for Installment" name="Installment">
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsInstallment/bc:*"/>
				</ParamClass>
			</BusParamConfigurationList>
			</BusParamConfiguration>
		</BusinessConfiguration>
	</xsl:template>
	
	<xsl:template match="bc:DueDateReminderNotification">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>due_date_reminder_notification</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				This parameter is used to send installment due date notification 
				before X days of installment due date.
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:variable name="value" select="normalize-space(text())"/>
			<xsl:element name="Value">
				<xsl:value-of select="$value"/>
			</xsl:element>
		</xsl:element>
	</xsl:template>
	<xsl:template match="bc:EndDateReminderNotification">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>end_date_reminder_notification</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				This parameter is used to send installment end date notification 
				before X days of installment due date.
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:variable name="value" select="normalize-space(text())"/>
			<xsl:element name="Value">
				<xsl:value-of select="$value"/>
			</xsl:element>
		</xsl:element>
	</xsl:template>


</xsl:stylesheet>
