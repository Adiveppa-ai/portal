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
				<BusParamsMultiBal>
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfiguration/bc:BusParamConfigurationList/bc:ParamClass/bc:Param"/>
				</BusParamsMultiBal>
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

				<xsl:when test="$name = 'sort_validity_by'">
					<xsl:element name="SortValidityBy">
						<xsl:choose>
							<xsl:when test="$value = '1'">
								<xsl:text>EST</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '2'">
								<xsl:text>LST</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '3'">
								<xsl:text>EET</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '4'">
								<xsl:text>LET</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '5'">
								<xsl:text>ESTLET</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '6'">
								<xsl:text>ESTEET</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '7'">
								<xsl:text>LSTEET</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '8'">
								<xsl:text>LSTLET</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '9'">
								<xsl:text>EETEST</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '10'">
								<xsl:text>EETLST</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '11'">
								<xsl:text>LETEST</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '12'">
								<xsl:text>LETLST</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = 'RestrictResourceValidityToOffer'">
					<xsl:element name="RestrictResourceValidityToOffer">
						<xsl:choose>
							<xsl:when test="$value = '0'">
								<xsl:text>FALSE</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '1'">
								<xsl:text>TRUE</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>

				<xsl:when test="$name = 'LockConcurrency'">
					<xsl:element name="LockConcurrency">
						<xsl:choose>
							<xsl:when test="$value = '0'">
								<xsl:text>normal</xsl:text>
							</xsl:when>
							<xsl:when test="$value = '1'">
								<xsl:text>high</xsl:text>
							</xsl:when>
						</xsl:choose>
					</xsl:element>
				</xsl:when>
				
                                <xsl:when test="$name = 'CreditThresholdChecking'">
                                        <xsl:element name="CreditThresholdChecking">
                                                <xsl:choose>
                                                        <xsl:when test="$value = '0'">
                                                                <xsl:text>disabled</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = '1'">
                                                                <xsl:text>enabledOffline</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>
			
				<xsl:when test="$name = 'consume_subtype'">
                                        <xsl:element name="ConsumeSubType">
                                                <xsl:choose>
                                                        <xsl:when test="$value = '0'">
                                                                <xsl:text>main</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = '1'">
                                                                <xsl:text>loan</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>
				<xsl:when test="$name = 'skip_bal_monitor_impact'">
                                        <xsl:element name="SkipBalMonitorImpact">
                                                <xsl:choose>
                                                        <xsl:when test="$value = '0'">
                                                                <xsl:text>0</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = '1'">
                                                                <xsl:text>1</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = '2'">
                                                                <xsl:text>2</xsl:text>
                                                        </xsl:when>
                                                        <xsl:when test="$value = '3'">
                                                                <xsl:text>3</xsl:text>
                                                        </xsl:when>
                                                </xsl:choose>
                                        </xsl:element>
                                </xsl:when>

			</xsl:choose>
										
	</xsl:template>
</xsl:stylesheet>
