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
                                <ParamClass desc="Business logic parameters for Customer" name="customer">
                                        <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsCustomer/bc:*"/>
                                </ParamClass>
                        </BusParamConfigurationList>

                                </BusParamConfiguration>
                        </BusinessConfiguration>
                </xsl:template>

                <xsl:template match="bc:SubscriberLifeCycle">
                        <xsl:element name="Param">
                                <xsl:element name="Name">
                                        <xsl:text>subscriber_life_cycle</xsl:text>
                                </xsl:element>
                                <xsl:element name="Desc">
                                	This parameter indicates Subscriber Lifecycle Management feature enabled/disabled. The default is disabled(0).
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

                <xsl:template match="bc:EnablePasswordRestriction">
                        <xsl:element name="Param">
                                <xsl:element name="Name">
                                        <xsl:text>enable_password_restriction</xsl:text>
                                </xsl:element>
                                <xsl:element name="Desc">
                                	This parameter indicates if password restriction should apply on service. The default is enabled(1).
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
               <xsl:template match="bc:ClosedAcctsRetentionMonths">
			<xsl:element name="Param">
				<xsl:element name="Name">
					<xsl:text>closed_accts_retention_months</xsl:text>
				</xsl:element>
				<xsl:element name="Desc">
					This parameter indicates the number of months to retain the deleted accounts in system.Default is to keep the accounts forever.
				</xsl:element>
				<xsl:element name="Type">INT</xsl:element>
				<xsl:variable name="value" select="normalize-space(text())"/>
				<xsl:element name="Value">
					<xsl:value-of select="$value"/>
				</xsl:element>

			</xsl:element>
		</xsl:template>
                <xsl:template match="bc:ActgDom">
			<xsl:element name="Param">
				<xsl:element name="Name">
					<xsl:text>actg_dom</xsl:text>
				</xsl:element>
				<xsl:element name="Desc">
					Specifies the day of the month when Portal should bill accounts.
				</xsl:element>
				<xsl:element name="Type">INT</xsl:element>
				<xsl:variable name="value" select="normalize-space(text())"/>
				<xsl:element name="Value">
					<xsl:value-of select="$value"/>
				</xsl:element>
			</xsl:element>
		</xsl:template>
                <xsl:template match="bc:BillWhen">
			<xsl:element name="Param">
				<xsl:element name="Name">
					<xsl:text>bill_when</xsl:text>
				</xsl:element>
				<xsl:element name="Desc">
					Specifies the number of accounting cycles before the customer is billed.
				</xsl:element>
				<xsl:element name="Type">INT</xsl:element>
				<xsl:variable name="value" select="normalize-space(text())"/>
				<xsl:element name="Value">
					<xsl:value-of select="$value"/>
				</xsl:element>
			</xsl:element>
		</xsl:template>

		<xsl:template match="bc:CCchecksum">
			<xsl:element name="Param">
				<xsl:element name="Name">
					<xsl:text>cc_checksum</xsl:text>
				</xsl:element>
				<xsl:element name="Desc">
					This parameter indicates whether to run a checksum validation on the customer's credit card during registration. The default is enabled(1).
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


