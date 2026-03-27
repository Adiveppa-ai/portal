<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xalan="http://xml.apache.org/xalan"
    xmlns:dns="http://www.oracle.com/schemas/BusinessConfig"
    exclude-result-prefixes="xalan dns xsl">

<xsl:output method="xml" encoding="UTF-8" indent="yes"  xalan:indent-amount="5"/>

<xsl:include href="/home/pin/opt/portal/BRM/xsd/PinTransforms.xsl" />

<xsl:template match="@* | node()">
  <xsl:copy>
    <xsl:apply-templates select="@* | node()"/>
  </xsl:copy>
</xsl:template>


<xsl:template match="//dns:ConfigObject/dns:STATES">
   <xsl:copy>

      <xsl:apply-templates select="*[not(dns:MODULE/text()='AAA') and not(name(.)='TRANSITIONS')]   | @*"/>

      <xsl:variable name="AAA_MT" >
         <xsl:choose>
         <xsl:when test="dns:RULES[dns:MODULE/text()='AAA' and dns:NAME/text()='MT_ENABLED']/dns:VALUE='Yes'">
          4
         </xsl:when>
         <xsl:otherwise>0</xsl:otherwise>
         </xsl:choose>
      </xsl:variable>
      <xsl:variable name="AAA_MO" >
         <xsl:choose>
         <xsl:when test="dns:RULES[dns:MODULE/text()='AAA' and dns:NAME/text()='MO_ENABLED']/dns:VALUE='Yes'">
          2
         </xsl:when>
         <xsl:otherwise>0</xsl:otherwise>
         </xsl:choose>
      </xsl:variable>  

      <xsl:variable name="AAA_REQ" >
         <xsl:choose>
         <xsl:when test="dns:RULES[dns:MODULE/text()='AAA' and dns:NAME/text()='REQ_ALLOWED']/dns:VALUE='Yes'">
          1
         </xsl:when>
         <xsl:otherwise>0</xsl:otherwise>
         </xsl:choose>
      </xsl:variable>

      <xsl:variable name="AAA_TFN" >
         <xsl:choose>
         <xsl:when test="dns:RULES[dns:MODULE/text()='AAA' and dns:NAME/text()='TFN_ALLOWED']/dns:VALUE='Yes'">
          8
         </xsl:when>
         <xsl:otherwise>0</xsl:otherwise>
         </xsl:choose>
      </xsl:variable>

      <xsl:variable name="numRules">
        <xsl:choose>
        <xsl:when test="string(number(dns:RULES[not(preceding-sibling::dns:RULES/@elem &gt;= @elem)
                and not(following-sibling::dns:RULES/@elem &gt; @elem)]/@elem))='NaN' " >
        0
        </xsl:when>
        <xsl:otherwise>
           <xsl:value-of  select="dns:RULES[not(preceding-sibling::dns:RULES/@elem &gt;= @elem)
                and not(following-sibling::dns:RULES/@elem &gt; @elem)]/@elem" />
        </xsl:otherwise>
        </xsl:choose>

      </xsl:variable>

      <RULES  xmlns="http://www.oracle.com/schemas/BusinessConfig" elem="{$numRules+1}">
	<MODULE>AAA</MODULE>
	<NAME>CALL_ALLOWED</NAME>
	<VALUE><xsl:value-of select="number($AAA_MT)+number($AAA_MO)+number($AAA_REQ)+number($AAA_TFN)" /></VALUE>
      </RULES>

      <xsl:apply-templates select="dns:TRANSITIONS"/>

  </xsl:copy>

</xsl:template>

<xsl:template match="//dns:ConfigObject/dns:STATES/dns:SERVICE_STATE_EXPIRATION_T" >
   <xsl:copy>
      <xsl:apply-templates select="@*" />

      <xsl:variable name="ExpDays">
         <xsl:choose>  
         <xsl:when test="contains(., ':')" >
            <xsl:value-of select="substring-before(., ':')" />
         </xsl:when>
         <xsl:otherwise>
            <xsl:value-of  select="." />
         </xsl:otherwise>
         </xsl:choose>
      </xsl:variable>
      <xsl:variable name="afterDays" select="substring-after(., ':')" />
      <xsl:variable name="ExpHors">
         <xsl:choose>
         <xsl:when test="string-length($afterDays)=0">
             <xsl:value-of select="0" />
         </xsl:when>
         <xsl:when test="contains($afterDays, ':')">
            <xsl:value-of select="substring-before($afterDays, ':')" />
         </xsl:when>
         <xsl:otherwise>
            <xsl:value-of select="$afterDays" />
         </xsl:otherwise>
         </xsl:choose>
      </xsl:variable>
      <xsl:variable name="ExpMins">
         <xsl:choose>
         <xsl:when test="string-length($afterDays)=0">
            <xsl:value-of select="0" />
         </xsl:when>
         <xsl:when test="string-length(substring-after($afterDays,':'))>0" >
            <xsl:value-of select="substring-after($afterDays,':')" />
         </xsl:when>
         <xsl:otherwise>
            <xsl:value-of select="0" />
        </xsl:otherwise>  
        </xsl:choose>
     </xsl:variable>
     <xsl:value-of select="$ExpMins*60 + ($ExpHors*60*60) + ($ExpDays*24*60*60)" />
   </xsl:copy>
</xsl:template>
</xsl:stylesheet>			


