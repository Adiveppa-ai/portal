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
				<ParamClass desc="Business logic parameters for Multi-Bal" name="multi-bal">
					<xsl:apply-templates select="/bc:BusinessConfiguration/bc:BusParamConfigurationClass/bc:BusParamsMultiBal/bc:*"/>
				</ParamClass>
			</BusParamConfigurationList>
			</BusParamConfiguration>
		</BusinessConfiguration>
	</xsl:template>
	
	<xsl:template match="bc:SortValidityBy">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>sort_validity_by</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
			When consuming validity-based sub-balances, this parameter decides the default consumption rule. Possible values are EST (1), LST(2), EET (3), LET (4), ESTLET (5), ESTEET(6),  LSTEET (7), LSTLET (8), EETEST (9), EETLST (10), LETEST (11), LETLST (12).
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:element name="Value">
				<xsl:choose>
					<xsl:when test="normalize-space(text()) = 'EST'">
						<xsl:text>1</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'LST'">
						<xsl:text>2</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'EET'">
						<xsl:text>3</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'LET'">
						<xsl:text>4</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'ESTLET'">
						<xsl:text>5</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'ESTEET'">
						<xsl:text>6</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'LSTEET'">
						<xsl:text>7</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'LSTLET'">
						<xsl:text>8</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'EETEST'">
						<xsl:text>9</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'EETLST'">
						<xsl:text>10</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'LETEST'">
						<xsl:text>11</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'LETLST'">
						<xsl:text>12</xsl:text>
					</xsl:when>
				</xsl:choose>			
			</xsl:element>
		</xsl:element>
	</xsl:template>
	<xsl:template match="bc:RestrictResourceValidityToOffer">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>RestrictResourceValidityToOffer</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
			This parameter decides if the validity of resource valid
			from first usage has to be restricted by the validity
			of the product or discount granting the resource.
			FALSE (0) disabled. TRUE (0) enabled.
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:element name="Value">
				<xsl:choose>
					<xsl:when test="normalize-space(text()) = 'FALSE'">
						<xsl:text>0</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'TRUE'">
						<xsl:text>1</xsl:text>
					</xsl:when>
				</xsl:choose>
			</xsl:element>
		</xsl:element>
	</xsl:template>
	<xsl:template match="bc:BalanceMonitoring">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>balance_monitoring</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Enable/Disable Balance Monitoring . The parameter values can be 0 (disabled), 1 (enabled).
Default is 0 (disabled).
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:element name="Value">
                                <xsl:choose>
                                        <xsl:when test="normalize-space(text()) = 'enabled'">
                                                <xsl:text>1</xsl:text>
                                        </xsl:when>
					<xsl:when test="normalize-space(text()) = 'disabled'">
                                                <xsl:text>0</xsl:text>
                                        </xsl:when>
                                </xsl:choose>
                        </xsl:element>
                </xsl:element>
        </xsl:template>
			
	<xsl:template match="bc:LockConcurrency">
		<xsl:element name="Param">
			<xsl:element name="Name">
				<xsl:text>lock_concurrency</xsl:text>
			</xsl:element>
			<xsl:element name="Desc">
				Indicates the concurrency of object locking. 
				Possible values are normal(0) to
				lock the account object and high(1) to have
				more concurrency of locking with 
				greater granularity in terms of which balance 
				group to lock. Default is high(1).
			</xsl:element>
			<xsl:element name="Type">INT</xsl:element>
			<xsl:element name="Value">
				<xsl:choose>
					<xsl:when test="normalize-space(text()) = 'high'">
						<xsl:text>1</xsl:text>
					</xsl:when>
					<xsl:when test="normalize-space(text()) = 'normal'">
						<xsl:text>0</xsl:text>
					</xsl:when>
				</xsl:choose>
			</xsl:element>
		</xsl:element>
	</xsl:template>

	<xsl:template match="bc:CreditThresholdChecking"> 
		<xsl:element name="Param"> 
			<xsl:element name="Name"> 
				<xsl:text>CreditThresholdChecking</xsl:text> 
			</xsl:element> 
			<xsl:element name="Desc"> 
				Enable/Disable credit threshold checking during offline 
				processing.  The parameter values can be: 
				0 (disabled), 
				1 (enabledOffline). 
				Default is 0 (disabled).   
				We may want additional values in 
				the future (i.e. enabledRealtime, enabled, etc.) 
			</xsl:element> 
			<xsl:element name="Type">INT</xsl:element> 
			<xsl:element name="Value"> 
				<xsl:choose> 
					<xsl:when test="normalize-space(text()) = 'enabledOffline'"> 
						<xsl:text>1</xsl:text> 
					</xsl:when> 
					<xsl:when test="normalize-space(text()) = 'disabled'"> 
						<xsl:text>0</xsl:text> 
					</xsl:when> 
				</xsl:choose> 
			</xsl:element> 
		</xsl:element> 
	</xsl:template> 
	    <xsl:template match="bc:ConsumeSubType">
                <xsl:element name="Param">
                        <xsl:element name="Name">
                                <xsl:text>consume_subtype</xsl:text>
                        </xsl:element>
                        <xsl:element name="Desc">
                                Order of Loan or Main Balance Consumption
                                processing.  The parameter values can be:
                                main (0),
                                loan (1).
                                Default is main balance (0).
                                We may want additional values in
                                the future (i.e. etc.)
                        </xsl:element>
                        <xsl:element name="Type">INT</xsl:element>
                        <xsl:element name="Value">
                                <xsl:choose>
                                        <xsl:when test="normalize-space(text()) = 'loan'">
                                                <xsl:text>1</xsl:text>
                                        </xsl:when>
                                        <xsl:when test="normalize-space(text()) = 'main'">
                                                <xsl:text>0</xsl:text>
                                        </xsl:when>
                                </xsl:choose>
                        </xsl:element>
                </xsl:element>
        </xsl:template>
	<xsl:template match="bc:SkipBalMonitorImpact"> 
		<xsl:element name="Param"> 
			<xsl:element name="Name"> 
				<xsl:text>skip_bal_monitor_impact</xsl:text> 
			</xsl:element> 
			<xsl:element name="Desc"> 
				Allows Balance Monitor Impact to skip during OBG 
				monitor create/update/delete events processing.
				The parameter values can be: 
				0 (disabled, default impact monitor bal), 
				1 (Skip Monitor Impact during OBG create/update event), 
				2 (Skip Monitor Impact during OBG delete event), 
				3 (Skip Monitor Impact during OBG create/update/delete event). 
			</xsl:element> 
			<xsl:element name="Type">INT</xsl:element> 
			<xsl:element name="Value"> 
				<xsl:choose> 
					<xsl:when test="normalize-space(text()) = '0'"> 
						<xsl:text>0</xsl:text> 
					</xsl:when> 
					<xsl:when test="normalize-space(text()) = '1'"> 
						<xsl:text>1</xsl:text> 
					</xsl:when> 
					<xsl:when test="normalize-space(text()) = '2'"> 
						<xsl:text>2</xsl:text> 
					</xsl:when> 
					<xsl:when test="normalize-space(text()) = '3'"> 
						<xsl:text>3</xsl:text> 
					</xsl:when> 
				</xsl:choose> 
			</xsl:element> 
		</xsl:element> 
	</xsl:template> 

</xsl:stylesheet>

