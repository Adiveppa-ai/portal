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
                                <BusParamsCustomer>
                                       <xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
                                </BusParamsCustomer>
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

                                <xsl:when test="$name = &apos;subscriber_life_cycle&apos;">
                                        <xsl:element name="SubscriberLifeCycle">
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

                                <xsl:when test="$name = &apos;enable_password_restriction&apos;">
                                        <xsl:element name="EnablePasswordRestriction">
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
                                <xsl:when test="$name = &apos;closed_accts_retention_months&apos;">
					<xsl:element name="ClosedAcctsRetentionMonths">
					<xsl:value-of select="$value" />
					</xsl:element>
				</xsl:when>
                                <xsl:when test="$name = &apos;actg_dom&apos;">
					<xsl:element name="ActgDom">
					<xsl:value-of select="$value" />
					</xsl:element>
				</xsl:when>
                                <xsl:when test="$name = &apos;bill_when&apos;">
					<xsl:element name="BillWhen">
					<xsl:value-of select="$value" />
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = &apos;cc_checksum&apos;">
					<xsl:element name="CCchecksum">
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

