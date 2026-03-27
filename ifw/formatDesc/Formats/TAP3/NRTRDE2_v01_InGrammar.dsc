//==============================================================================
//
// Copyright (c) 2009, Oracle and/or its affiliates. All rights reserved. 
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FMD/NRTRDE_0201
//------------------------------------------------------------------------------
// Module Description:
//   Input grammar file for the NRTRDE_0201 format
//
//==============================================================================


//==============================================================================
// The initial iScript code
//==============================================================================

iScript                                       
{                                             
  
  // Array to store countryCode
  Long    numOfCountryCode;
  String  countryCodeArray[];

  // Array to store PLMNO list
  Long    numOfPlmnoCode;
  String  PLMNOCode[];
  
  // Array to store Bearer Service Code
  Long    numOfBearerServiceCode;
  String  bearerServiceCodeArray[];
  
  Long    numTeleServiceCode;
  String  TeleServiceCodeArr[]; 
  
  String  applicationName;
  String  applicationID;
  
  String  lastTeleServiceCode;
  String  lastAPN;
  Bool    bearerServiceCodeIsMissing;  
  Bool    dialledDigitsIsMissing;
  Long    lastCauseForTermination;
                                                

  const Long record_Header  = 11;
  const Long record_Trailer = 12;
  const Long record_MOC     = 1;
  const Long record_MTC     = 2;
  const Long record_GPRS    = 3;
  const Long LOG_WARNING    = 2;
  const Long LOG_MAJOR      = 4;  
  const String type_MOC     = "021";
  const String type_MTC     = "031";
  const String type_GPRS    = "042";
  Long  record_Type    = 0; // use to know which type of detail we are reading  
  Long  records;
  String currBlock;
  
  function BEGIN
  {
    
    String countryCodeStr = "1|7|20|27|30|31|32|33|34|36|39|40|41|43|44|45|46|47|48|49|51|52|53|54|55|56|57|58|60|61|62|63|64|65|66|81|82|84|86|90|91|92|93|94|95|98|210|211|212|213|214|215|216|217|218|219|220|221|222|223|224|225|226|227|228|229|230|231|232|233|234|235|236|237|238|239|240|241|242|243|244|245|246|247|248|249|250|251|252|253|254|255|256|257|258|259|260|261|262|263|264|265|266|267|268|269|280|281|282|283|284|285|286|287|288|289|290|291|292|293|294|295|296|297|298|299|350|351|352|353|354|355|356|357|358|359|370|371|372|373|374|375|376|377|378|379|380|381|382|383|384|385|386|387|388|389|420|421|422|423|424|425|426|427|428|429|500|501|502|503|504|505|506|507|508|509|590|591|592|593|594|595|596|597|598|599|670|671|672|673|674|675|676|677|678|679|680|681|682|683|684|685|86|687|688|689|690|691|692|693|694|695|696|697|698|699|800|801|802|803|804|805|806|807|808|809|830|831|832|833|834|835|836|837|838|839|850|851|852|853|854|855|856|857|858|859|870|871|872|873|874|875|876|877|878|879|880|881|882|883|884|885|886|887|888|889|890|891|892|893|894|895|896|897|898|899|960|961|962|963|964|965|966|967|968|969|970|971|972|973|974|975|976|977|978|979|990|991|992|993|994|995|996|997|998|999";
    numOfCountryCode = strSplit( countryCodeArray, countryCodeStr, "|" );    
    String plmnoListStr = "BRABT|URYTM|AILIN|AILID|BMUID|AILPI|AILTN|AILTA|THATC|FRAFF|THAAS|CHNAR|USAAC|USAAN|AFGAW|AFGAW|GMBAC|USAAN|USAAE|INDRC|INDE2|INDE3|INDE4|INDAC|INDAC|RUSVL|FINAM|USAAW|USAAK|ALBAM|TKMTM|URYAM|USAC1|BRAAC|BRACL|PRYHT|PERTM|USAAN|URYAN|ATG03|USAAS|AFGAR|CYPSC|SYRSP|ARM01|ESTEM|IRQAC|UKRAS|IRQAT|LBRAW|CIV02|GABTL|DZAA1|NORNN|TURIS|TURAC|AZEAC|AZEAF|BTNBM|BRNBR|BHRBT|AZEBC|TKMBC|BELKO|RUSKH|BRACL|BLRBT|BELTB|BLZ67|BENBB|BIHPT|INDAP|INDAS|INDBH|INDCH|INDGJ|INDHR|INDHP|INDJK|INDKT|INDKR|INDCA|INDMY|INDMH|INDNE|INDOR|INDPB|INDRJ|INDTN|INDUE|INDUW|INDWB|INDSC|INDBL|INDJH|INDJB|INDAT|INDMT|INDA1|INDA2|INDA3|INDA4|INDA6|INDA7|INDA8|INDA9|INDA5|IND10|IND11|IND12|IND14|IND13|IND10|IND12|INDH1|IND16|EDSCH|EDSUS|KGZMC|FRAF3|INDB1|BGRAB|BGRVA|USAWC|CYMCW|SYCCW|AIACW|BRBCW|ATGCW|LCACW|VCTCW|DMACW|DMAGS|GRDCW|GRDCW|GBRGT|GBRGT|JAMCW|GBRGT|PANCW|KNACW|MSRCW|TCACW|FLKCW|KHMSH|KHMGM|USACR|VGBCC|LBRCT|MYSCC|LBR07|ZAFCC|ISRCL|ISRCH|BFA03|LBRI1|POLI2|ISLI3|KENI4|BRAV9|MUSCP|RUSIZ|USACP|UGACE|SLECT|BFACT|CODCT|COGCT|GABCT|KENKC|MWICT|MDGCO|NERCT|NGAVM|TZACT|TCDCT|ZMBCE|USACC|USAWC|USACV|RUSCH|CHNCT|CHNCM|HKGPP|CHNCU|USAKD|TWNLD|USATM|USACB|USABS|USAPB|USACG|USA3G|USAAT|BMU01|TJKBM|RUSNO|RUSRP|RUSVG|CHLSM|RUSKM|GBRC9|COLCO|GTMCM|CHECF|CHERB|ZAFC2|NGAG2|SWES2|AFGK0|LIEK0|MCOK0|ISLK0|IRQK9|LIEK9|UZBK9|ISLT2|MNGK9|TJKK9|ESTK9|CYPK9|INDKA|INDKB|INDKC|INDKD|INDKE|INDKF|INDKG|INDKH|INDKI|INDKJ|INDKK|INDKL|INDKM|INDKN|INDKO|INDKP|INDKQ|INDKS|INDKU|INDKV|INDKW|INDKW|INDKX|INDKY|INDKZ|INDK0|INDK1|INDK2|INDK3|INDK4|INDK5|INDK6|INDK7|INDK8|INDK9|BGDK9|ESTK8|CHES2|VENK9|ARMK9|PHLK9|KGZK9|UKRK9|RUSK9|TJKK8|UKRK8|ISRK9|GUYK9|TJKK7|JAMK9|BRBK9|CYMK9|DMAK9|GRDK9|LCAK9|MSRK9|TCAK9|KNAK9|VCTK9|AIAK9|ATGK9|EGYK9|CHEVI|ISRK8|ABWK9|EGYK8|TWNK9|REUK9|AFGK9|DJIK9|DEUK9|JORK9|NGAK9|BRAK8|BRAK9|MCOK9|CHEK9|ANTK9|CHEK8|IDNK9|MDVK9|USAK9|AUSK9|CHEK7|MDVK8|MWIK9|LKAK9|UKRK7|BFAK9|LBRK9|SVKK9|VENK7|VENK8|BRNK9|BRNK9|CZEK9|COLK9|GBRK9|IDNK7|IDNK8|ARMK8|MRTK9|YUGK9|BRAK7|HRVK9|NORK9|CHNK9|PHLK8|ARMK7|LBRK8|PHLK7|BRNK7|BRNK8|BOLK9|NORN2|MNEK9|MYSK9|PLWK9|AGOK9|NAMK9|SGPK9|GMBCM|CIVCM|LBRCM|SLENC|SLECM|USACO|USACD|HTICL|HTICL|HTICL|STPST|DOMCL|USATX|ECUPG|CODCC|PHLTA|USACA|VEND2|USAU1|UZB05|BGRCM|MKDCC|GRCCO|ROMCS|USAQ1|USADT|BRACT|BRAC3|BRAC4|SLVTP|ARGCM|MACCT|ANTCT|CPVCV|CYPCT|GLPDT|MDV01|LKADG|MYSMT|BRBDC|33850|FRAF4|TTODL|SLVDC|THADP|PHLDG|IND01|IND02|IND03|IND04|IND05|IND06|IND08|DJIDJ|FINTA|FIN2G|USADC|DEUE1|DEUV1|USATC|ANTEC|ANTNB|USAEC|EGYAR|LSOET|ZWEET|USAEM|USAEW|FINRL|FINES|ESTRE|AREDU|ARETC|JPNEM|CUB01|CUB02|HNDHM|NICEN|NICSC|MUSEM|CHLPC|BOLME|CHLMV|LAOEM|LAOET|USAET|ERIER|INDIH|INDIR|INDIU|ETH01|SAUET|AFGEA|EGYEM|MDAEM|IDNEX|TWNFE|USAFA|FROFT|INDF1|UZB07|FRAAB|ESPRT|ESPOR|FSMFM|GMB01|GEOGC|USAMI|GNQ01|GHAGT|GIBGT|NGAGM|FINGN|CHEGN|AAQGN|BRAV1|BRAV2|BRAV3|USAGT|FRAGS|CANGS|MEXGS|BRAGS|AUSGS|NICGS|SAUGS|USAGS|ITAGS|FINGS|KORGS|CHNGS|ZAFGS|VENGS|PERGS|CHLGS|URYGS|PRYGS|COLGS|TURGS|RUSGS|QATGS|USAGM|CANGM|AUSGM|PHLGT|UKRGT|SOMGT|BGDGP|KAZKZ|GUMHT|GNBGS|GUYGT|ITAH3|SWEHU|DNKHU|USAHM|USAHP|PRYVX|HKGTC|SOMHI|BIHER|AUSHU|AUTHU|IRLH3|GBRHU|IDN89|INDHM|INDHC|INDHK|INDHA|INDHM|INDE1|INDBS|INDB3|INDBS|INDB2|INDBS|INDB4|INDE5|INDE7|HKGHT|HKGH3|INDCC|LKAHT|MACHT|CRICR|CRICE|CRICE|MARM1|CANIW|IND07|INDID|INDBI|INDMP|INDBO|INDEH|INDEK|INDEU|ISLVW|ISLSY|ISLMT|ISLMS|CHEIP|CHEIN|TJKIT|USAIN|CHEIB|INXIX|PHLIC|GIN03|USAIW|IRNMI|TCAIC|GUMIW|USAJS|INTJS|GBRAJ|GBRJT|GBRMS|AAMNT|BLR02|JORFL|RUSSH|RUS12|TJK01|ARM05|FROKA|USAKT|KAZKT|USAWV|USACW|IRNKI|TWNKG|PRKSN|PRKSN|IRQKK|NLDPT|KORKF|KORKP|UKRKS|USALC|LAOLA|LAOLA|LAOAS|LVALM|GAB01|LBYLM|RUSEC|LBRLC|USASX|BMUNI|PRTPW|LUXMW|NLDPP|NLDTV|ESPES|LUXMA|GBRCJ|DNKRO|DNKWL|IPASS|GEOMA|HUNH2|INDDL|INDMB|MLI01|GBRMT|NORMC|BWAGA|MRTMT|MRTMM|MRTMM|MYSSD|MYSMC|USASK|IRN11|MARMT|SYCSC|RUSNW|IRLME|LBNFL|LBNLC|LBNMT|TZAMB|CANMC|USAMT|GHAMT|LAOTL|SLEMC|TCDML|USAM5|MYSMI|MNGMC|FRANM|BLRMD|KAZ77|KWTMT|IRNIM|RUS01|SGPM1|PAKMK|LIEMK|LIEMK|AUTPT|AUTPT|AUTMK|BGR01|ROMMX|MLTGO|BELMO|TWNTM|SUDMO|LKA71|SVNMT|GEOMT|MOZ01|MDAMC|MCOM2|JAMDC|MEXDC|URYTM|NAM01|BHRMV|ZMB02|ZAFMN|CMR01|CMRMT|COGLB|CIVTL|NGAMN|RWAMN|SDNBT|UGAMN|USACH|MMRPT|GBRAR|KWTNM|SOMNL|USANP|NPLNM|NORNC|USA66|USANM|ABWDC|RUS16|HKGNW|NGA40|RUS03|NFKNT|USACI|MKDNO|ISLNO|JPNDO|PRYNP|BOLNT|HTINT|ISL09|DEUE2|DEUO2|GBRCN|IRLDF|IRLLT|CODSA|BENLI|ISLTL|ISL03|RUSUU|RUSBD|UKRBD|TJKBD|GEOBD|UZBBD|KAZBD|USAOW|OMNGT|OMNNT|LTUOM|CHEOA|BFAON|AUTCA|AUTON|NCLPT|PRTOP|BWAVC|LIEVE|GNB03|CMR02|GLPO1|CIV03|CHEOR|DOM01|FRAF1|MDGAN|MLI02|MLI02|MDAVX|NLDDT|GBROR|REU02|REU02|ROMMR|SVKGT|DZAOT|IRQOR|TUNTA|ECUOT|REUOT|MYTMO|LUXPT|POLP4|PNGPM|PAKUF|PAKPL|PLWPM|PLWPM|PSEJE|HUNH1|ISR01|HKGMC|HKGM3|MEXMS|USAPE|USAPC|USAPW|USAP1|POLKM|POL02|POLWL|POLWL|POL02|NAM03|RUS92|YUGPM|MNEPM|SPMPR|IDNSL|IDNIM|IDNIM|IDNLT|IDNTS|IDNM8|POL03|GUMGW|USAPU|GRCQT|QATQT|MEXTL|IRNRI|INDRK|INDRN|INDRM|INDRB|INDRO|INDRW|INDRA|INDRH|USADW|GBRRP|CANRW|RUST2|BIHMS|KENSA|NERSC|WSMGS|SMOSM|IRQST|SAUAJ|CHESB|GHASC|NLDSC|SENSG|GTMSC|BRASC|ANDMA|HNDME|ABWSE|ANTUT|RUSSK|FRAF2|BGDBL|SVNSM|LVABT|RUSS2|TWNAT|HKGBM|ISLPS|ISLOC|SGPST|SGPST|SGPML|SGPSV|AUSOP|KGZ01|USASO|PHLSR|MACSM|HKGSM|USASB|COMHR|FRARE|JPNJP|SLBSI|SOMSF|SENAZ|DNKDM|GIN02|USASL|USAFC|YEMSP|GNBSB|BENSP|INDSP|INDSK|NPLM2|SPM01|RUSSP|SGPSH|SDNTL|USASC|SWZMN|SWESP|CHEC1|USATS|SYR01|CPVTM|GBRME|AUTMM|HRVCN|CZERM|DEUD1|MKDMM|YUGTM|MNETM|NLDPN|NLDPN|SVKET|SVKET|USA31|USA16|USA27|USAW0|USAW1|USAW5|USAW6|USAW4|USAW2|USAW3|USA58|TJK91|TWNPC|LUXTG|USATT|DNKTD|CHEDX|VENMS|ANTTC|SWEIQ|LIETG|GRLTG|LVABC|HRVT2|ESTRB|CHET2|BEN02|CAF02|BFATL|NERTL|TGOTL|ZWEN3|BDITL|SYCAT|COKTC|AFGTD|ITASI|ITAGT|ARGTP|KIRKI|VUT01|TTO12|BOLTE|PRYTC|HND02|ARGTM|CHLTM|COLTM|SLVTS|ESPTE|ESPTE|ESPT2|GTMTG|PANMS|PERMO|CZEET|SVKO2|KHMSM|MWICP|YUGTS|BRATC|SLVTM|YUGMT|NORTM|PAKTP|SWEEP|SURTG|BGDTT|NORT3|NLDTM|DNKIA|DNKMX|FINTF|FINV1|SWETR|MDGTM|SOMTM|AUSTA|CANTM|USARS|BHSBH|DEUCN|SWECN|ARETH|ARETH|LKACT|FRATK|BRASP|BRARN|BRACS|GRCSH|TLSTL|BGDAK|PRTTM|PRTTM|USA1L|BRATM|TGOTC|TON01|THAWP|USANE|TWNTA|THACO|MYST3|TJKTT|TUNTT|TURTC|SVNVG|USAT1|GUYCS|LTUMT|LTU03|UGATL|UKRUM|UKRRS|AAMRS|RUSUL|JORUM|USAUN|USAUN|UZBDU|MNGMN|AGOUT|USABI|USAVW|TWNTG|VNMVC|VNMVT|VNMMO|VNMVI|HRVVI|MOZVC|CODVC|ZAFVC|LSOVL|TZAVC|ALBVF|CZECM|DEUD2|DEUVF|EGYMS|EGYVF|ESPAT|ESPVV|FJIVF|HUNVR|IRLEC|NLDLT|GBRVF|GBRVG|GBRVH|GBRVX|GBRVA|GBRVB|GBRVC|GBRVD|GBRVE|GBRVI|GBRVJ|GBRVK|GBRVL|GBRVM|GBRVN|GBRVO|GBRVP|GBRVQ|GBRVR|GBRVS|GBRVT|GBRVU|GBRVV|GBRVW|GBRVY|GBRVZ|MLTTL|MLTMA|MLTSN|NZLBS|ITAOM|ITAVF|AUSVF|PRTTL|PRTWL|ROMMF|TURTS|GRCPF|CHE88|RUSVM|LUXVM|LUXVM|AAMVM|AAAVM|PAKWA|BGDWT|DZAWT|MDVWM|GUMWR|MNPWR|GBRWT|USAWK|ITAWI|USAWA|USARB|RRCRB|SHIPS|ESPXF|USAXT|USAUS|JORXT|RUSSC|ZMBCZ|TZAZN|TZAZN|RUS07|RUS15|RUSM2";    
    numOfPlmnoCode = strSplit( PLMNOCode, plmnoListStr, "|" );    

    String teleServiceCodeStr = "00|10|11|12|20|21|22|60|61|62|63|70|80|90|91|92";
    numTeleServiceCode = strSplit( TeleServiceCodeArr, teleServiceCodeStr, "|" );    

    String bearerServiceCodeStr = "00|20|21|22|23|24|25|26|27|30|32|34|35|36|37|40|41|42|43|44|45|46|47|50|54|55|56|57|60|70|80|90|A0|B0|C0|D0";
    numOfBearerServiceCode = strSplit( bearerServiceCodeArray, bearerServiceCodeStr, "|" ); 
    

  }

  function initializeForNewStream
  {
    record_Type = -1;
    records = 0;
    lastCauseForTermination = -1;
  }
  
  /***************************************************************************
   * function createNewHeader
   ***************************************************************************/
  function createNewHeader
  {
    if ( edrNew( HEADER, CONTAINER_HEADER ) == false )
    {
      edrAddError( "ERR_EDR_CREATE", 4 );
      logFormat( "ERROR: Failed to create HEADER\n" );
      //TODO abort processing of the input stream
    }
    record_Type = record_Header;  

  }
  
  /***************************************************************************
   * function createNewDetail
   ***************************************************************************/
  function createNewDetail(Long recordTypedId, String detailType)
  {
    if ( edrNew( DETAIL, CONTAINER_DETAIL ) == false )
    {
      edrAddError( "ERR_EDR_CREATE", 4 );
      logFormat( "ERROR: Failed to create DETAIL\n" );
      //TODO abort processing of the input stream
    }
    record_Type = recordTypedId;
    records = records + 1;
    edrString(DETAIL.RECORD_TYPE) = detailType;

    if( (record_Type == record_MOC) or (record_Type == record_MTC) )
    {
      if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT ) == false )
      {
        String Msg = "failed to add ASS_GSMW_EXT datablock for EDR "+longToStr(records);
        edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++
      }
    }
    if( record_Type == record_MOC )
    {
      if ( edrAddDatablock( DETAIL.ASS_GSMW_EXT.SS_PACKET ) == false )
      {
        String Msg = "failed to add ASS_GSMW_EXT.SS_PACKET datablock";
        edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++
      }
    }
   
    
    if( record_Type == record_GPRS )
    {
      if ( edrAddDatablock( DETAIL.ASS_GPRS_EXT ) == false )
      {
        String Msg = "failed to add ASS_GPRS_EXT datablock for EDR "+longToStr(records);
        edrAddError( "ERR_TAP3_INPUT_ERROR", 4, Msg);
// ++++++++++++++++++++
// logPipeline(Msg, 4);
// ++++++++++++++++++++
      }
    }
    lastTeleServiceCode = "-1";
  }
  
  
  /***************************************************************************
   * function validateIpV4
   ***************************************************************************/
  function Bool validateIpV4(String ipAddress)
  {
    String ListArray[];
    Long nbElem = strSplit( ListArray, ipAddress, "." );
    Long i;
    if(nbElem != 4)
    {
      return false;
    }
    for (i=0 ; i<nbElem ; i=i+1)
    {
      Long found = strSearchRegExpr(ListArray[i], "[^0-9]");
      if(found >= 0)
      {
        return false;
      }
      else
      {
        Long num = strToLong(ListArray[i]);
        if(num < 0 or num >255)
        {
          return false;
        }
      }
    }
    return true;
  }


  /***************************************************************************
  * function validateIpV6
  ***************************************************************************/
  function Bool validateIpV6(String ipAddress)
  {
    String ListArray[];
    Long nbElem = strSplit( ListArray, ipAddress, ":" );
    Long i;
    if(nbElem != 8)
    {
      return false;
    }
    for (i=0 ; i<nbElem ; i=i+1)
    {
      if(strLength(ListArray[i]) > 4)
      {
        return false;
      }
      Long found = strSearchRegExpr(ListArray[i], "[^0-9A-Fa-f]");
      if(found >= 0)
      {
        return false;
      }
    }
    return true;
  }
  
  /***************************************************************************
   * function createNewTrailer
   ***************************************************************************/
  function createNewTrailer
  {
    if ( edrNew( TRAILER, CONTAINER_TRAILER ) == false )
    {
      edrAddError( "ERR_EDR_CREATE", 4 );
      logFormat( "ERROR: Failed to create TRAILER\n" );
      //TODO abort processing of the input stream
    }
    
    record_Type = record_Trailer;  
  }
  
  
  /***************************************************************************
   * function validateHexValue
   ***************************************************************************/
  function Bool validateHexValue(String hexValue)
  {
    if( strSearchRegExpr(hexValue, "[^0-9A-F]") < 0 )
    {
      return true;
    }
    return false;
  }
  
  /***************************************************************************
   * Function To Validate Out Of Range Error
   ***************************************************************************/
  function Bool validateOOR( String edrValueStr, String upperLimitStr, String lowerLimitStr, String oorType)
  {
    switch ( oorType )
    {
   
      case "INTEGER_TYPE" :
      {
        Long edrValue   = strToLong(edrValueStr);
        Long upperLimit = strToLong(upperLimitStr);
        Long lowerLimit = strToLong(lowerLimitStr);
  
        if( edrValue < lowerLimit or edrValue > upperLimit )
        {
          return false;
        }
        else
        {
          return true;
        }
      }
      break;
  
      default:
      {
        logStdout("\n ERROR"); 
        return true;
      }
    }
  }
  
/***************************************************************************
 * Function To Validate Syntax Error
 ***************************************************************************/
function Bool validateSyntax( String edrValueStr, String syntaxErrorType )
{
  switch ( syntaxErrorType )
  {
    case "CHECK_NUM" :
    {
      if ( strSearchRegExpr(edrValueStr, "[^0-9]") >= 0 )
      {
        return false;
      }
      return true;
    }
    break;
    case "CHECK_ALPHA_UPPER" :
    {
      if ( strSearchRegExpr(edrValueStr, "[^A-Z]") >= 0 )
      {
        return false;
      }
      return true;
    }
    break;
    case "CHECK_ALPHA_LOWER" :
    {
      if ( strSearchRegExpr(edrValueStr, "[^a-z]") >= 0 )
      {
        return false;
      }
      return true;
    }
    break;
    case "CHECK_ALPHANUMERIC" :
    {
      if ( strSearchRegExpr(edrValueStr, "[^0-9a-zA-Z]") >= 0 )
      {
        return false;
      }
      return true;
    }
    break;
    case "CHECK_ALPHANUMERIC_UPPER" :
    {
      if ( strSearchRegExpr(edrValueStr, "[^0-9A-Z]") >= 0 )
      {
        return false;
      }
      return true;
    }
    break;
    default:
    {
      logStdout("\n ERROR");
      return true;
    }
  }
}
  
  /***************************************************************************
   * function createErrorContext
   ***************************************************************************/
  function createErrorContext
  {
    if ( record_Type == record_MOC )
    {
      applicationName = "moc";
      applicationID  = "3";
    }
    else if ( record_Type == record_MTC )
    {
      applicationName = "mtc";
      applicationID  = "4";
    }
    else
    {
      applicationName = "gprs";
      applicationID  = "5";
    }
  }
    
                                            
}                                             
                                                
Grammar                                       
{                                             
  __inputStream:                              
      {                                       
        initializeForNewStream();           
      }                                       
      inputStream                             
    ;                                         


/////////////////////////////////////////////////////////////////////////
  inputStream:
      {
        //logStdout("Info: parsed inputStream\n");
      }
      Nrtrde
      fileFiller
    ;

  fileFiller:
      fileFiller
      fileFillerElement
    |
    ;

  fileFillerElement:
      NRTRDE_0201.BlockEnd
    | NRTRDE_0201.FileFiller
    | NRTRDE_0201.FileEndFiller
    ;
/////////////////////////////////////////////////////////////////////////

                                                
                                                                                 
  AccessPointNameNI_opt:                                                         
      AccessPointNameNI                                                          
    |/* EMPTY */
      {
        createErrorContext();
        edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "306", "Mandatory item Access Point Name NI missing within group.");
        edrAddError("ERR_TAP3_RET", 3, "severe", "306", applicationID, "0", "-1", "-1", "Mandatory item Access Point Name NI missing within group.");
      }                                                                          
    ;                                                                            
                                                                                 
  AccessPointNameNI:                                                             
      NRTRDE_0201.AccessPointNameNI                                        
      {                                                                          
        //logStdout("NRTRDE_0201.AccessPointNameNI.AccessPointNameNI");    
        //logStdout("Parsed Leaf AccessPointNameNI\n");

        lastAPN = tokenString("NRTRDE_0201.AccessPointNameNI.AccessPointNameNI");

        if ( strLength( lastAPN ) > 63 )    
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "AccessPointNameNI", "16", "100", "Syntax Error");
          edrAddError("ERR_TAP3_RET", 3, "severe", "100", "16", "0", "-1", "-1", "Syntax Error");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  AccessPointNameOI_opt:                                                         
      AccessPointNameOI                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  AccessPointNameOI:                                                             
      NRTRDE_0201.AccessPointNameOI                                        
      {                                                                          
        //logStdout("NRTRDE_0201.AccessPointNameOI.AccessPointNameOI");    
        //logStdout("Parsed Leaf AccessPointNameOI\n");

        lastAPN = lastAPN +","+ tokenString("NRTRDE_0201.AccessPointNameOI.AccessPointNameOI");

        if ( strLength( tokenString("NRTRDE_0201.AccessPointNameOI.AccessPointNameOI") ) > 37 )    
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "AccessPointNameOI", "17", "101", "Syntax Error");
          edrAddError("ERR_TAP3_RET", 3, "severe", "101", "17", "0", "-1", "-1", "Syntax Error");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  AsciiString_opt:                                                         
      AsciiString                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  AsciiString:                                                             
      NRTRDE_0201.AsciiString                                        
      {                                                                          
        //logStdout("NRTRDE_0201.AsciiString.AsciiString");    
        //logStdout("Parsed Leaf AsciiString\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  BCDString_opt:                                                         
      BCDString                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  BCDString:                                                             
      NRTRDE_0201.BCDString                                        
      {                                                                          
        //logStdout("NRTRDE_0201.BCDString.BCDString");    
        //logStdout("Parsed Leaf BCDString\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  BearerServiceCode_opt:                                                         
      BearerServiceCode                                                          
    |
    {
      bearerServiceCodeIsMissing = true;
    }
    ;                                                                            
                                                                                 
  BearerServiceCode:                                                             
      NRTRDE_0201.BearerServiceCode                                        
      {                                                                          
        //logStdout("NRTRDE_0201.BearerServiceCode.BearerServiceCode");    
        //logStdout("Parsed Leaf BearerServiceCode\n");
        edrConnectToken(DETAIL.BASIC_SERVICE, "NRTRDE_0201.BearerServiceCode.BearerServiceCode");
        bearerServiceCodeIsMissing = false; // this Bool variable is used for MOC/MTC validation.
        Bool   bearerServiceCodePresent = false;
        String lastBearerServiceCode = edrString(DETAIL.BASIC_SERVICE);
        edrString(DETAIL.BASIC_SERVICE) = "1" + edrString(DETAIL.BASIC_SERVICE);
        Long   i;  
        
        
        if( validateHexValue(lastBearerServiceCode) == false )
        {
              edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "Bearer Service Code", "18", "102", "Syntax Error");
              edrAddError("ERR_TAP3_RET", 3, "severe", "102", "18", "0", "-1", "-1", "Syntax Error");
        }
        else
        {
          for( i = 0 ; i < numOfBearerServiceCode and bearerServiceCodePresent == false ; i = i + 1 )
          {
            if( lastBearerServiceCode == bearerServiceCodeArray[i])
            {
              bearerServiceCodePresent = true;
            }
          }
          if(bearerServiceCodePresent == false)
          {
            edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "Bearer Service Code", "18", "200", "Value Out Of Range");
            edrAddError("ERR_TAP3_RET", 3, "severe", "200", "18", "0", "-1", "-1", "Value Out Of Range");
          } 
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                      
  CallEvent_opt:              
      CallEvent               
    |                                 
    ;                                 
                                      
  CallEvent:                  
      {                               
        //logStdout("");  
      }                               
      CallEvent_elems         
      {                               
        //logStdout("");           
      }                               
    ;                                 
                                      
  CallEvent_elems:            
      moc_CallEvent     
    | mtc_CallEvent     
    | gprs_CallEvent     
    ;                                 
                                      
  moc_CallEvent:                                                       
      {                                                                                 
        currBlock = "moc";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Moc                                                           
    ;                                                                                   
                                                                                        
  mtc_CallEvent:                                                       
      {                                                                                 
        currBlock = "mtc";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Mtc                                                           
    ;                                                                                   
                                                                                        
  gprs_CallEvent:                                                       
      {                                                                                 
        currBlock = "gprs";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Gprs                                                           
    ;                                                                                   
                                                                                        
                                                                                 
  CallEventDuration_opt:                                                         
      CallEventDuration                                                          
    |/* EMPTY */
      {
        if( record_Type == record_MOC )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "314",
                                                    "Mandatory item Call Event Duration missing within group.");
          edrAddError("ERR_TAP3_RET", 3, "severe", "314", applicationID, "0", "-1", "-1",
                                                    "Mandatory item Call Event Duration missing within group.");
        }
        else if( record_Type == record_MTC )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "321",
                                                    "Mandatory item Call Event Duration missing within group.");
          edrAddError("ERR_TAP3_RET", 3, "severe", "321", applicationID, "0", "-1", "-1",
                                                    "Mandatory item Call Event Duration missing within group.");
        }
        else if( record_Type == record_GPRS )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "304",
                                                    "Mandatory item Call Event Duration missing within group.");
          edrAddError("ERR_TAP3_RET", 3, "severe", "304", applicationID, "0", "-1", "-1",
                                                    "Mandatory item Call Event Duration missing within group.");
        }
      }
    ;                                                                            
                                                                                 
  CallEventDuration:                                                             
      NRTRDE_0201.CallEventDuration                                        
      {                                                                          
        //logStdout("NRTRDE_0201.CallEventDuration.CallEventDuration");    
        //logStdout("Parsed Leaf CallEventDuration\n");
        edrLong(DETAIL.TOTAL_CALL_EVENT_DURATION) = strToLong(tokenString("NRTRDE_0201.CallEventDuration.CallEventDuration"));
        if( edrLong(DETAIL.TOTAL_CALL_EVENT_DURATION) < 0 )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "CallEventDuration", "19", "201", "Value out of range");
          edrAddError("ERR_TAP3_RET", 3, "severe", "201", "19", "0", "-1", "-1", "Value Out Of Range"); 
        } 
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                        
  CallEventList_opt:                                                                
      NRTRDE_0201.CallEventList                                               
      {       
        //logStdout("NRTRDE_0201.CallEventList");                  
        //logStdout("Parsed List CallEventList\n");                                
      }                                                                                 
      CallEventList                                                                 
      BlockEnd                                                                        
      {                                                                                 
        //logStdout("NRTRDE_0201.CallEventList");                          
        //logStdout("CallEventList List END.\n");                                  
      }                                                                                 
    |                                                                                   
    ;                                                                                   
                                                                                        
  CallEventList:                                                                    
      CallEventList                                                                 
      CallEvent_CallEventList                                                    
    |                                                                                   
    ;                                                                                   
                                                                                        
  CallEvent_CallEventList:                                                       
      {                                                                                 
        currBlock = "CallEvent";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEvent                                                           
    ;                                                                                   
                                                                                 
  CallEventStartTimeStamp_opt:                                                         
      CallEventStartTimeStamp                                                          
    |/* EMPTY */
      {
        if( record_Type == record_MOC )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "313",
                                                    "Mandatory item Call Event Start Timestamp missing within group.");
          edrAddError("ERR_TAP3_RET", 3, "severe", "313", applicationID, "0", "-1", "-1",
                                                    "Mandatory item Call Event Start Timestamp missing within group.");
        }
        else if( record_Type == record_MTC )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "320",
                                                    "Mandatory item Call Event Start Timestamp missing within group.");
          edrAddError("ERR_TAP3_RET", 3, "severe", "320", applicationID, "0", "-1", "-1",
                                                    "Mandatory item Call Event Start Timestamp missing within group.");
        }
        else if( record_Type == record_GPRS )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "303",
                                                    "Mandatory item Call Event Start Timestamp missing within group.");
          edrAddError("ERR_TAP3_RET", 3, "severe", "303", applicationID, "0", "-1", "-1",
                                                    "Mandatory item Call Event Start Timestamp missing within group.");
        }
      }
    ;                                                                            
                                                                                 
  CallEventStartTimeStamp:                                                             
      NRTRDE_0201.CallEventStartTimeStamp                                        
      {                                                                          
        //logStdout("NRTRDE_0201.CallEventStartTimeStamp.CallEventStartTimeStamp");    
        //logStdout("Parsed Leaf CallEventStartTimeStamp\n");
        String callEventStartTimeStampStr = tokenString("NRTRDE_0201.CallEventStartTimeStamp.CallEventStartTimeStamp");
        edrDate(DETAIL.CHARGING_START_TIMESTAMP) = strToDate(callEventStartTimeStampStr);
        if ( dateIsValid( strToDate(callEventStartTimeStampStr)) == false )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "CallEventStartTimeStamp", "21", "104", "Syntax Error");
          edrAddError("ERR_TAP3_RET", 3, "severe", "104", "21", "0", "-1", "-1", "Syntax Error");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CallEventsCount_opt:                                                         
      CallEventsCount                                                          
    |/* EMPTY */
      {
        edrAddError("ERR_TAP3_WARNING", LOG_WARNING, "Nrtrde", "1", "331", "Mandatory item Call Events Count missing within group");
      }                                                                           
    ;                                                                            
                                                                                 
  CallEventsCount:                                                             
      NRTRDE_0201.CallEventsCount                                        
      {                                                                          
        //logStdout("NRTRDE_0201.CallEventsCount.CallEventsCount");    
        //logStdout("Parsed Leaf CallEventsCount\n");
        edrConnectToken(TRAILER.TAP_TOTAL_NUMBER_OF_RECORDS, "NRTRDE_0201.CallEventsCount.CallEventsCount");
        if( edrLong(TRAILER.TAP_TOTAL_NUMBER_OF_RECORDS) < 0 )
        {
          edrAddError("ERR_TAP3_WARNING", LOG_WARNING, "CallEventsCount", "20", "203", "Value out of range");
        }
        else if ( edrLong(TRAILER.TAP_TOTAL_NUMBER_OF_RECORDS) != records )
        {
          edrAddError("ERR_TAP3_WARNING", LOG_WARNING, "CallEventsCount", "20", "400", 
                                                       "Value does not match the count of Call Events");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CallReference_opt:                                                         
      CallReference                                                          
    |/* EMPTY */
    ;                                                                            
                                                                                 
  CallReference:                                                             
      NRTRDE_0201.CallReference                                        
      {                                                                          
        //logStdout("NRTRDE_0201.CallReference.CallReference");    
        //logStdout("Parsed Leaf CallReference\n");
        edrConnectToken(DETAIL.ASS_GSMW_EXT.CALL_REFERENCE, 0,
                          "NRTRDE_0201.CallReference.CallReference");
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CallingNumber_opt:                                                         
      CallingNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  CallingNumber:                                                             
      NRTRDE_0201.CallingNumber                                        
      {                                                                          
        //logStdout("NRTRDE_0201.CallingNumber.CallingNumber");    
        //logStdout("Parsed Leaf CallingNumber\n");
        edrString(DETAIL.B_NUMBER) = tokenString("NRTRDE_0201.CallingNumber.CallingNumber");
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  CauseForTermination_opt:                                                         
      CauseForTermination                                                          
    |/* EMPTY */
      {
        if( record_Type == record_MOC )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "315",
                                                    "Mandatory item Cause For Termination missing within group.");
          edrAddError("ERR_TAP3_RET", 3, "severe", "315", applicationID, "0", "-1", "-1",
                                                    "Mandatory item Cause For Termination missing within group.");
        }
        else if( record_Type == record_MTC )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "322",
                                                    "Mandatory item Cause For Termination missing within group.");
          edrAddError("ERR_TAP3_RET", 3, "severe", "322", applicationID, "0", "-1", "-1",
                                                    "Mandatory item Cause For Termination missing within group.");
        }
        else if( record_Type == record_GPRS )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "305",
                                                    "Mandatory item Cause For Termination missing within group.");
          edrAddError("ERR_TAP3_RET", 3, "severe", "305", applicationID, "0", "-1", "-1",
                                                    "Mandatory item Cause For Termination missing within group.");
        }
      }
    ;                                                                            
                                                                                 
  CauseForTermination:                                                             
      NRTRDE_0201.CauseForTermination                                        
      {                                                                          
        //logStdout("NRTRDE_0201.CauseForTermination.CauseForTermination");    
        //logStdout("Parsed Leaf CauseForTermination\n");
        edrConnectToken(DETAIL.CALL_COMPLETION_INDICATOR, "NRTRDE_0201.CauseForTermination.CauseForTermination");
        lastCauseForTermination = strToLong(edrString(DETAIL.CALL_COMPLETION_INDICATOR));
        if ( ( ( record_Type == record_MOC or record_Type == record_MTC ) and ( lastCauseForTermination < 0 or lastCauseForTermination > 5 ) ) 
             or ( ( record_Type == record_GPRS ) and ( lastCauseForTermination < 0 or ( lastCauseForTermination > 0 and lastCauseForTermination < 4 ) or 
                                                    ( lastCauseForTermination < 16 and lastCauseForTermination > 5 )  or lastCauseForTermination > 21 ) ) )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "CauseForTermination", "24", "204", "Value Out of range");
          edrAddError("ERR_TAP3_RET", 3, "severe", "204", "24", "0", "-1", "-1", "Value Out of range");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ChargeAmount_opt:                                                          
      ChargeAmount                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ChargeAmount:                                                             
      NRTRDE_0201.ChargeAmount                                        
      {                                                                          
        //logStdout("NRTRDE_0201.ChargeAmount.ChargeAmount");    
        //logStdout("Parsed Leaf ChargeAmount\n");
        edrConnectToken(DETAIL.WHOLESALE_CHARGED_AMOUNT_VALUE, "NRTRDE_0201.ChargeAmount.ChargeAmount");
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ChargingId_opt:                                                         
      ChargingId                                                          
    |/* EMPTY */
      {
        createErrorContext();
        edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "311", "Mandatory item Charging Id missing within group");
        edrAddError("ERR_TAP3_RET", 3, "severe", "311", applicationID, "0", "-1", "-1", "Mandatory item Charging Id missing within group");
      }                                                                            
    ;                                                                            
                                                                                 
  ChargingId:                                                             
      NRTRDE_0201.ChargingId                                        
      {                                                                          
        //logStdout("NRTRDE_0201.ChargingId.ChargingId");    
        //logStdout("Parsed Leaf ChargingId\n");
        edrConnectToken(DETAIL.ASS_GPRS_EXT.CHARGING_ID, 0, "NRTRDE_0201.ChargingId.ChargingId");
        if( validateOOR(tokenString("NRTRDE_0201.ChargingId.ChargingId") ,"4294967295" , "0", "INTEGER_TYPE") == false )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "Charging Id", "26", "205", "Value Out Of Range");
          edrAddError("ERR_TAP3_RET", 3, "severe", "205", "26", "0", "-1", "-1", "Value Out Of Range");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ConnectedNumber_opt:                                                         
      ConnectedNumber                                                          
    | /* EMPTY */
      {
        if ( dialledDigitsIsMissing == true and lastTeleServiceCode != "12" )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "Moc", "3", "333", "Both items Dialled Digits and Connected Number missing within group, and call is not an emergency call.");
          edrAddError("ERR_TAP3_RET", 3, "severe", "333", "3", "0", "-1", "-1", "Both items Dialled Digits and Connected Number missing within group, and call is not an emergency call.");
        }
        if ( lastCauseForTermination != 3 and lastTeleServiceCode != "12" )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "Moc", "3", "334", "Item Connected Number missing and call is neither an unsuccessful call attempt, nor an emergency call.");
          edrAddError("ERR_TAP3_RET", 3, "severe", "334", "3", "0", "-1", "-1", "Item Connected Number missing and call is neither an unsuccessful call attempt, nor an emergency call.");
        }
      }
    ;                                                                             
                                                                                 
  ConnectedNumber:                                                             
      NRTRDE_0201.ConnectedNumber                                        
      {                                                                          
        //logStdout("NRTRDE_0201.ConnectedNumber.ConnectedNumber");    
        //logStdout("Parsed Leaf ConnectedNumber\n");
        edrString(DETAIL.B_NUMBER) = tokenString("NRTRDE_0201.ConnectedNumber.ConnectedNumber");
        String lastConnectedNumber = edrString(DETAIL.B_NUMBER);
        Long i;
        Bool countryCodeFound = false;
        if( (validateSyntax(lastConnectedNumber, "CHECK_NUM") == false) and lastTeleServiceCode != "12" )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "ConnectedNumber", "27", "109", "Syntax error and call does not represent an emergency call");
          edrAddError("ERR_TAP3_RET", 3, "severe", "109", "27", "0", "-1", "-1", "Syntax error and call does not represent an emergency call");
        }
        else
        {
          for( i = 0 ; i < numOfCountryCode and countryCodeFound == false ; i = i + 1 )
          {
            if (strStartsWith(lastConnectedNumber, countryCodeArray[i]))
            {
              countryCodeFound = true;
            }
          }
          if( countryCodeFound == false and validateSyntax(lastConnectedNumber, "CHECK_NUM") == true ) 
          {
            // FieldName, AppId, ErrorCode,ErrorDescription
            edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "ConnectedNumber", "27", "206",
                                                         "Value out of range or number does not start with a valid country code");
            edrAddError("ERR_TAP3_RET", 3, "severe", "206", "27", "0", "-1", "-1", 
                                                         "Value out of range or number does not start with a valid country code");
          }
        }
      }
    ;                                                                            
                                                                                 
                                                                                 
  DataVolumeIncoming_opt:                                                         
      DataVolumeIncoming                                                          
    |/* EMPTY */
      {
        createErrorContext();
        edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "307", "Mandatory item Data Volume Incoming missing within group");
        edrAddError("ERR_TAP3_RET", 3, "severe", "307", applicationID, "0", "-1", "-1", "Mandatory item Data Volume Incoming missing within group");
      }                                                                          
    ;                                                                            
                                                                                 
  DataVolumeIncoming:                                                             
      NRTRDE_0201.DataVolumeIncoming                                        
      {                                                                          
        //logStdout("NRTRDE_0201.DataVolumeIncoming.DataVolumeIncoming");    
        //logStdout("Parsed Leaf DataVolumeIncoming\n");
        edrConnectToken(DETAIL.VOLUME_RECEIVED, "NRTRDE_0201.DataVolumeIncoming.DataVolumeIncoming");
        if( edrDecimal(DETAIL.VOLUME_RECEIVED) < 0.0 )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "Data Volume Incoming", "28", "207", "Value Out Of Range");
          edrAddError("ERR_TAP3_RET", 3, "severe", "207", "28", "0", "-1", "-1", "Value Out Of Range");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  DataVolumeOutgoing_opt:                                                         
      DataVolumeOutgoing                                                          
    |/* EMPTY */
      {
        createErrorContext();
        edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "308", "Mandatory item Data Volume Outgoing missing within group");
        edrAddError("ERR_TAP3_RET", 3, "severe", "308", applicationID, "0", "-1", "-1", "Mandatory item Data Volume Outgoing missing within group");
      }                                                                          
    ;                                                                            
                                                                                 
  DataVolumeOutgoing:                                                             
      NRTRDE_0201.DataVolumeOutgoing                                        
      {                                                                          
        //logStdout("NRTRDE_0201.DataVolumeOutgoing.DataVolumeOutgoing");    
        //logStdout("Parsed Leaf DataVolumeOutgoing\n");
        edrConnectToken(DETAIL.VOLUME_SENT, "NRTRDE_0201.DataVolumeOutgoing.DataVolumeOutgoing");
        if( edrDecimal(DETAIL.VOLUME_SENT) < 0.0 )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "DataVolumeOutgoing", "29", "208", "Value Out Of Range");
          edrAddError("ERR_TAP3_RET", 3, "severe", "208", "29", "0", "-1", "-1", "Value Out Of Range");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  DialledDigits_opt:                                                         
      DialledDigits                                                          
    | /* EMPTY */
      {
        dialledDigitsIsMissing = true;                                                                           
      }
    ;                                                                            
                                                                                 
  DialledDigits:                                                             
      NRTRDE_0201.DialledDigits                                        
      {                                                                          
        //logStdout("NRTRDE_0201.DialledDigits.DialledDigits");    
        //logStdout("Parsed Leaf DialledDigits\n");
        dialledDigitsIsMissing = false;
        edrConnectToken(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0, "NRTRDE_0201.DialledDigits.DialledDigits");
        if( strSearchRegExpr(edrString(DETAIL.ASS_GSMW_EXT.DIALED_DIGITS, 0), "[^0-9#\*\+]") >= 0 )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "Dialled Digits", "30", "112", "Syntax Error");
          edrAddError("ERR_TAP3_RET", 3, "severe", "112", "30", "0", "-1", "-1", "Syntax Error");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  FileAvailableTimeStamp_opt:                                                         
      FileAvailableTimeStamp                                                          
    |/* EMPTY */
      {
        edrAddError("ERR_TAP3_WARNING", LOG_WARNING, "Nrtrde", "1", "330", "Mandatory item File Available Timestamp missing within group");
      }                                                                        
    ;                                                                            
                                                                                 
  FileAvailableTimeStamp:                                                             
      NRTRDE_0201.FileAvailableTimeStamp                                        
      {                                                                          
        //logStdout("NRTRDE_0201.FileAvailableTimeStamp.FileAvailableTimeStamp");    
        //logStdout("Parsed Leaf FileAvailableTimeStamp\n");
        String theFileAvailableTimeStamp = tokenString("NRTRDE_0201.FileAvailableTimeStamp.FileAvailableTimeStamp");
        edrDate(HEADER.TRANSMISSION_DATE) = strToDate(theFileAvailableTimeStamp);
        if ( dateIsValid( edrDate(HEADER.TRANSMISSION_DATE)) == false )
        {
          edrAddError("ERR_TAP3_WARNING", LOG_WARNING, "FileAvailableTimeStamp", "31", "113", "Syntax Error");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  GgsnAddress_opt:                                                         
      GgsnAddress                                                          
    |/* EMPTY */
      {
        createErrorContext();
        edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "310", "Mandatory item GGSN Address missing within group");
        edrAddError("ERR_TAP3_RET", 3, "severe", "310", applicationID, "0", "-1", "-1", "Mandatory item GGSN Address missing within group");
      }                                                                           
    ;                                                                            
                                                                                 
  GgsnAddress:                                                             
      NRTRDE_0201.GgsnAddress                                        
      {                                                                          
        //logStdout("NRTRDE_0201.GgsnAddress.GgsnAddress");    
        //logStdout("Parsed Leaf GgsnAddress\n");
        Bool ggsnAddressIsCorrect;
        edrConnectToken(DETAIL.ASS_GPRS_EXT.GGSN_ADDRESS, 0, "NRTRDE_0201.GgsnAddress.GgsnAddress");
       
        if( strSearch( edrString(DETAIL.ASS_GPRS_EXT.GGSN_ADDRESS, 0), "." ) >= 0 )  // isIpV4
        {
          ggsnAddressIsCorrect = validateIpV4(edrString(DETAIL.ASS_GPRS_EXT.GGSN_ADDRESS, 0));
        }
        else  // isIpV6
        {
          ggsnAddressIsCorrect = validateIpV6(edrString(DETAIL.ASS_GPRS_EXT.GGSN_ADDRESS, 0));
        }
        if( ggsnAddressIsCorrect == false )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "GgsnAddress", "32", "115", "Syntax does not conform to section 5.4");
          edrAddError("ERR_TAP3_RET", 3, "severe", "115", "32", "0", "-1", "-1", "Syntax does not conform to section 5.4");
          edrDemandRollback();
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  Gprs_opt:                                           
      Gprs                                            
    |                                                              
    ;                                                              
                                                                   
  Gprs:                                               
      NRTRDE_0201.Gprs                                 
      {                                                                   
        //logStdout("NRTRDE_0201.Gprs");   
        //logStdout("Parsed Sequence Gprs\n");
        createNewDetail(record_GPRS, type_GPRS);
      }                                                                   
      imsi_Gprs     
      imei_Gprs     
      callEventStartTimeStamp_Gprs     
      utcTimeOffset_Gprs     
      callEventDuration_Gprs     
      causeForTermination_Gprs     
      accessPointNameNI_Gprs     
      accessPointNameOI_Gprs     
      {
        edrString(DETAIL.ASS_GPRS_EXT.APN_ADDRESS, 0)       = lastAPN;
      }
      dataVolumeIncoming_Gprs     
      dataVolumeOutgoing_Gprs     
      sgsnAddress_Gprs     
      ggsnAddress_Gprs     
      chargingId_Gprs     
      chargeAmount_Gprs     
      BlockEnd                                                   
      {                                                            
        //logStdout("NRTRDE_0201.Gprs");     
        //logStdout("Gprs Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  imsi_Gprs:                                                       
      {                                                                                 
        currBlock = "imsi";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Imsi_opt                                                       
    ;                                                                                   
                                                                                        
  imei_Gprs:                                                       
      {                                                                                 
        currBlock = "imei";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Imei_opt                                                       
    ;                                                                                   
                                                                                        
  callEventStartTimeStamp_Gprs:                                                       
      {                                                                                 
        currBlock = "callEventStartTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEventStartTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_Gprs:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
  callEventDuration_Gprs:                                                       
      {                                                                                 
        currBlock = "callEventDuration";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEventDuration_opt                                                       
    ;                                                                                   
                                                                                        
  causeForTermination_Gprs:                                                       
      {                                                                                 
        currBlock = "causeForTermination";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CauseForTermination_opt                                                       
    ;                                                                                   
                                                                                        
  accessPointNameNI_Gprs:                                                       
      {                                                                                 
        currBlock = "accessPointNameNI";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AccessPointNameNI_opt                                                       
    ;                                                                                   
                                                                                        
  accessPointNameOI_Gprs:                                                       
      {                                                                                 
        currBlock = "accessPointNameOI";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      AccessPointNameOI_opt                                                       
    ;                                                                                   
                                                                                        
  dataVolumeIncoming_Gprs:                                                       
      {                                                                                 
        currBlock = "dataVolumeIncoming";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DataVolumeIncoming_opt                                                       
    ;                                                                                   
                                                                                        
  dataVolumeOutgoing_Gprs:                                                       
      {                                                                                 
        currBlock = "dataVolumeOutgoing";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DataVolumeOutgoing_opt                                                       
    ;                                                                                   
                                                                                        
  sgsnAddress_Gprs:                                                       
      {                                                                                 
        currBlock = "sgsnAddress";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SgsnAddress_opt                                                       
    ;                                                                                   
                                                                                        
  ggsnAddress_Gprs:                                                       
      {                                                                                 
        currBlock = "ggsnAddress";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      GgsnAddress_opt                                                       
    ;                                                                                   
                                                                                        
  chargingId_Gprs:                                                       
      {                                                                                 
        currBlock = "chargingId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargingId_opt                                                       
    ;                                                                                   
                                                                                        
  chargeAmount_Gprs:                                                       
      {                                                                                 
        currBlock = "chargeAmount";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeAmount_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  HexString_opt:                                                         
      HexString                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  HexString:                                                             
      NRTRDE_0201.HexString                                        
      {                                                                          
        //logStdout("NRTRDE_0201.HexString.HexString");    
        //logStdout("Parsed Leaf HexString\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Imei_opt:                                                         
      Imei                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  Imei:                                                             
      NRTRDE_0201.Imei                                        
      {                                                                          
        //logStdout("NRTRDE_0201.Imei.Imei");    
        //logStdout("Parsed Leaf Imei\n"); 
        if (record_Type == record_GPRS)
        {
          edrConnectToken(DETAIL.ASS_GPRS_EXT.DEVICE_NUMBER, 0, "NRTRDE_0201.Imei.Imei");
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.DEVICE_NUMBER, 0, "NRTRDE_0201.Imei.Imei");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Imsi_opt:                                                         
      Imsi                                                          
    |/* EMPTY */
      {
        if( record_Type == record_MOC )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID,"312", 
                                                   "Mandatory item IMSI missing within group");
          edrAddError("ERR_TAP3_RET", 3, "severe", "312", applicationID, "0", "-1", "-1", 
                                                   "Mandatory item IMSI missing within group");
        }
        else if( record_Type == record_MTC )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID,"319",
                                                   "Mandatory item IMSI missing within group");
          edrAddError("ERR_TAP3_RET", 3, "severe", "319", applicationID, "0", "-1", "-1",
                                                   "Mandatory item IMSI missing within group");
        }
        else if( record_Type == record_GPRS )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "302", 
                                                         "Mandatory item IMSI missing within group");
          edrAddError("ERR_TAP3_RET", 3, "severe", "302", applicationID, "0", "-1", "-1", 
                                                         "Mandatory item IMSI missing within group");
        }                                                                           
      }
    ;                                                                            
                                                                                 
  Imsi:                                                             
      NRTRDE_0201.Imsi                                        
      {                                                                          
        //logStdout("NRTRDE_0201.Imsi.Imsi");    
        //logStdout("Parsed Leaf Imsi\n");
        if (record_Type == record_GPRS)
        {
          edrConnectToken(DETAIL.ASS_GPRS_EXT.PORT_NUMBER, 0, "NRTRDE_0201.Imsi.Imsi");
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.PORT_NUMBER, 0, "NRTRDE_0201.Imsi.Imsi");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                   
  Moc_opt:                                           
      Moc                                            
    |                                                              
    ;                                                              
                                                                   
  Moc:                                               
      NRTRDE_0201.Moc                                 
      {                                                                   
        //logStdout("NRTRDE_0201.Moc");   
        //logStdout("Parsed Sequence Moc\n");
        createNewDetail(record_MOC, type_MOC);
      }                                                                   
      imsi_Moc     
      imei_Moc     
      callEventStartTimeStamp_Moc     
      utcTimeOffset_Moc     
      callEventDuration_Moc     
      causeForTermination_Moc     
      serviceCode_Moc     
      supplementaryServiceCode_Moc     
      dialledDigits_Moc     
      connectedNumber_Moc     
      thirdPartyNumber_Moc     
      recEntityId_Moc     
      callReference_Moc     
      chargeAmount_Moc     
      BlockEnd                                                   
      {                                                            
        //logStdout("NRTRDE_0201.Moc");     
        //logStdout("Moc Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  imsi_Moc:                                                       
      {                                                                                 
        currBlock = "imsi";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Imsi_opt                                                       
    ;                                                                                   
                                                                                        
  imei_Moc:                                                       
      {                                                                                 
        currBlock = "imei";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Imei_opt                                                       
    ;                                                                                   
                                                                                        
  callEventStartTimeStamp_Moc:                                                       
      {                                                                                 
        currBlock = "callEventStartTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEventStartTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_Moc:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
  callEventDuration_Moc:                                                       
      {                                                                                 
        currBlock = "callEventDuration";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEventDuration_opt                                                       
    ;                                                                                   
                                                                                        
  causeForTermination_Moc:                                                       
      {                                                                                 
        currBlock = "causeForTermination";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CauseForTermination_opt                                                       
    ;                                                                                   
                                                                                        
  serviceCode_Moc:                                                       
      {                                                                                 
        currBlock = "serviceCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ServiceCode_opt                                                       
    ;                                                                                   
                                                                                        
  supplementaryServiceCode_Moc:                                                       
      {                                                                                 
        currBlock = "supplementaryServiceCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SupplementaryServiceCode_opt                                                       
    ;                                                                                   
                                                                                        
  dialledDigits_Moc:                                                       
      {                                                                                 
        currBlock = "dialledDigits";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      DialledDigits_opt                                                       
    ;                                                                                   
                                                                                        
  connectedNumber_Moc:                                                       
      {                                                                                 
        currBlock = "connectedNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ConnectedNumber_opt                                                       
    ;                                                                                   
                                                                                        
  thirdPartyNumber_Moc:                                                       
      {                                                                                 
        currBlock = "thirdPartyNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ThirdPartyNumber_opt                                                       
    ;                                                                                   
                                                                                        
  recEntityId_Moc:                                                       
      {                                                                                 
        currBlock = "recEntityId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityId_opt                                                       
    ;                                                                                   
                                                                                        
  callReference_Moc:                                                       
      {                                                                                 
        currBlock = "callReference";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallReference_opt                                                       
    ;                                                                                   
                                                                                        
  chargeAmount_Moc:                                                       
      {                                                                                 
        currBlock = "chargeAmount";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeAmount_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  Mtc_opt:                                           
      Mtc                                            
    |                                                              
    ;                                                              
                                                                   
  Mtc:                                               
      NRTRDE_0201.Mtc                                 
      {                                                                   
        //logStdout("NRTRDE_0201.Mtc");   
        //logStdout("Parsed Sequence Mtc\n");
        createNewDetail(record_MTC, type_MTC);
      }                                                                   
      imsi_Mtc     
      imei_Mtc     
      callEventStartTimeStamp_Mtc     
      utcTimeOffset_Mtc     
      callEventDuration_Mtc     
      causeForTermination_Mtc     
      serviceCode_Mtc     
      callingNumber_Mtc     
      recEntityId_Mtc     
      callReference_Mtc     
      chargeAmount_Mtc     
      BlockEnd                                                   
      {                                                            
        //logStdout("NRTRDE_0201.Mtc");     
        //logStdout("Mtc Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  imsi_Mtc:                                                       
      {                                                                                 
        currBlock = "imsi";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Imsi_opt                                                       
    ;                                                                                   
                                                                                        
  imei_Mtc:                                                       
      {                                                                                 
        currBlock = "imei";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Imei_opt                                                       
    ;                                                                                   
                                                                                        
  callEventStartTimeStamp_Mtc:                                                       
      {                                                                                 
        currBlock = "callEventStartTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEventStartTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_Mtc:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
  callEventDuration_Mtc:                                                       
      {                                                                                 
        currBlock = "callEventDuration";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallEventDuration_opt                                                       
    ;                                                                                   
                                                                                        
  causeForTermination_Mtc:                                                       
      {                                                                                 
        currBlock = "causeForTermination";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CauseForTermination_opt                                                       
    ;                                                                                   
                                                                                        
  serviceCode_Mtc:                                                       
      {                                                                                 
        currBlock = "serviceCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ServiceCode_opt                                                       
    ;                                                                                   
                                                                                        
  callingNumber_Mtc:                                                       
      {                                                                                 
        currBlock = "callingNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallingNumber_opt                                                       
    ;                                                                                   
                                                                                        
  recEntityId_Mtc:                                                       
      {                                                                                 
        currBlock = "recEntityId";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      RecEntityId_opt                                                       
    ;                                                                                   
                                                                                        
  callReference_Mtc:                                                       
      {                                                                                 
        currBlock = "callReference";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      CallReference_opt                                                       
    ;                                                                                   
                                                                                        
  chargeAmount_Mtc:                                                       
      {                                                                                 
        currBlock = "chargeAmount";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ChargeAmount_opt                                                       
    ;                                                                                   
                                                                                        
                                                                   
  Nrtrde_opt:                                           
      Nrtrde                                            
    |                                                              
    ;                                                              
                                                                   
  Nrtrde:                                               
      NRTRDE_0201.Nrtrde                                 
      {                                                                   
        //logStdout("NRTRDE_0201.Nrtrde");   
        //logStdout("Parsed Sequence Nrtrde\n");              
      }                                                                   
      specificationVersionNumber_Nrtrde     
      releaseVersionNumber_Nrtrde     
      sender_Nrtrde     
      recipient_Nrtrde     
      sequenceNumber_Nrtrde     
      fileAvailableTimeStamp_Nrtrde     
      utcTimeOffset_Nrtrde     
      callEvents_Nrtrde     
      callEventsCount_Nrtrde     
      BlockEnd                                                   
      {                                                            
        //logStdout("NRTRDE_0201.Nrtrde");     
        //logStdout("Nrtrde Sequence END.\n");         
      }                                                            
    ;                                                              
                                                                   
  specificationVersionNumber_Nrtrde:                                                        
      {                                                                                 
        currBlock = "specificationVersionNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");
        createNewHeader();
      }                                                                                 
      SpecificationVersionNumber_opt                                                       
    ;                                                                                   
                                                                                        
  releaseVersionNumber_Nrtrde:                                                       
      {                                                                                 
        currBlock = "releaseVersionNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      ReleaseVersionNumber_opt                                                       
    ;                                                                                   
                                                                                        
  sender_Nrtrde:                                                       
      {                                                                                 
        currBlock = "sender";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Sender_opt                                                       
    ;                                                                                   
                                                                                        
  recipient_Nrtrde:                                                       
      {                                                                                 
        currBlock = "recipient";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      Recipient_opt                                                       
    ;                                                                                   
                                                                                        
  sequenceNumber_Nrtrde:                                                       
      {                                                                                 
        currBlock = "sequenceNumber";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      SequenceNumber_opt                                                       
    ;                                                                                   
                                                                                        
  fileAvailableTimeStamp_Nrtrde:                                                       
      {                                                                                 
        currBlock = "fileAvailableTimeStamp";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      FileAvailableTimeStamp_opt                                                       
    ;                                                                                   
                                                                                        
  utcTimeOffset_Nrtrde:                                                       
      {                                                                                 
        currBlock = "utcTimeOffset";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      UtcTimeOffset_opt                                                       
    ;                                                                                   
                                                                                        
  callEvents_Nrtrde:                                                       
      {                                                                                 
        currBlock = "callEvents";                                                   
        //logStdout("currContext= " + currContext + "\n");
      }                                                                                 
      CallEventList_opt                                                       
    ;                                                                                   
                                                                                        
  callEventsCount_Nrtrde:                                                       
      {                                                                                 
        currBlock = "callEventsCount";                                                   
        //logStdout("currContext= " + currContext + "\n");
        createNewTrailer();
      }                                                                                 
      CallEventsCount_opt                                                       
    ;                                                                                   
                                                                                        
                                                                                 
  NumberString_opt:                                                         
      NumberString                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  NumberString:                                                             
      NRTRDE_0201.NumberString                                        
      {                                                                          
        //logStdout("NRTRDE_0201.NumberString.NumberString");    
        //logStdout("Parsed Leaf NumberString\n");                         
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  RecEntityId_opt:                                                         
      RecEntityId                                                          
    |/* EMPTY */
      {
        if( record_Type == record_MOC )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "317", 
                                                    "Mandatory item Recording Entity Identification missing within group");
          edrAddError("ERR_TAP3_RET", 3, "severe", "317", applicationID, "0", "-1", "-1", 
                                                    "Mandatory item Recording Entity Identification missing within group");
        }                                                                           
        else if( record_Type == record_MTC )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "324",
                                                    "Mandatory item Recording Entity Identification missing within group");
          edrAddError("ERR_TAP3_RET", 3, "severe", "324", applicationID, "0", "-1", "-1",
                                                    "Mandatory item Recording Entity Identification missing within group");
        }
      }
    ;                                                                            
                                                                                 
  RecEntityId:                                                             
      NRTRDE_0201.RecEntityId                                        
      {                                                                          
        //logStdout("NRTRDE_0201.RecEntityId.RecEntityId");    
        //logStdout("Parsed Leaf RecEntityId\n");
        if( record_Type == record_MOC )
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.ORIGINATING_SWITCH_IDENTIFICATION, 0, "NRTRDE_0201.RecEntityId.RecEntityId");
        }
        else
        {
          edrConnectToken(DETAIL.ASS_GSMW_EXT.TERMINATING_SWITCH_IDENTIFICATION, 0, "NRTRDE_0201.RecEntityId.RecEntityId");
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Recipient_opt:                                                         
      Recipient                                                          
    |/* EMPTY */
      {
        edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "Nrtrde", "1", "328", "Mandatory item Recipient missing within group");
        edrAddError("ERR_TAP3_RET", 4, "fatal", "328", "1", "0", "-1", "-1", "Mandatory item Recipient missing within group");
        edrDemandRollback();
      }                                                                       
    ;                                                                            
                                                                                 
  Recipient:                                                             
      NRTRDE_0201.Recipient                                        
      {                                                                          
        //logStdout("NRTRDE_0201.Recipient.Recipient");    
        //logStdout("Parsed Leaf Recipient\n");
        String theRecipient = tokenString("NRTRDE_0201.Recipient.Recipient");
        edrString(HEADER.RECIPIENT)= theRecipient;
        Long i;  
        Bool recipientPresent = false;
        
        if ( (strLength(theRecipient) != 5) or 
               (validateSyntax(theRecipient, "CHECK_ALPHANUMERIC_UPPER") == false) )
        {
          edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "Recipient", "36", "117", "Syntax error");
          edrAddError("ERR_TAP3_RET", 4, "fatal", "117", "36", "0", "-1", "-1", "Syntax error");
          edrDemandRollback();
        }
        else
        {
          for( i = 0; i < numOfPlmnoCode and recipientPresent == false; i = i + 1 )
          {
            if( PLMNOCode[i] == theRecipient )
            {
              recipientPresent = true;
            }
          }

          if ( recipientPresent == false )
          {
            edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "Recipient", "36", "212", "Value out of range");
            edrAddError("ERR_TAP3_RET", 4, "fatal", "212", "36", "0", "-1", "-1", "Value out of range");
            edrDemandRollback();
          } 
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ReleaseVersionNumber_opt:                                                         
      ReleaseVersionNumber                                                          
    |/* EMPTY */
      {
        edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "Nrtrde", "1", "332", "Mandatory item Release Version Number missing");
        edrAddError("ERR_TAP3_RET", 3, "fatal", "332", "1", "0", "-1", "-1", "Mandatory item Release Version Number missing");
        edrDemandRollback();
      }
    ;                                                                            
                                                                                 
  ReleaseVersionNumber:                                                             
      NRTRDE_0201.ReleaseVersionNumber                                        
      {                                                                          
        //logStdout("NRTRDE_0201.ReleaseVersionNumber.ReleaseVersionNumber");    
        //logStdout("Parsed Leaf ReleaseVersionNumber\n");
        edrConnectToken(HEADER.RELEASE_VERSION, "NRTRDE_0201.ReleaseVersionNumber.ReleaseVersionNumber");
        if ( edrLong(HEADER.RELEASE_VERSION) != 1 ) 
        {
          edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "ReleaseVersionNumber", "37", "213", "Value out of range");
          edrAddError("ERR_TAP3_RET", 3, "fatal", "213", "37", "0", "-1", "-1", "Value Out Of Range"); 
          edrDemandRollback();
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  Sender_opt:                                                         
      Sender                                                          
    |/* EMPTY */
      {
        edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "Nrtrde", "1", "327", "Mandatory item Sender missing within group");
        edrAddError("ERR_TAP3_RET", 4, "fatal", "327", "1", "0", "-1", "-1", "Mandatory item Sender missing within group");
        edrDemandRollback();
      }                                                                       
    ;                                                                            
                                                                                 
  Sender:                                                             
      NRTRDE_0201.Sender                                        
      {                                                                          
        //logStdout("NRTRDE_0201.Sender.Sender"); 
        //logStdout("Parsed Leaf Sender\n");
        String theSender = tokenString("NRTRDE_0201.Sender.Sender");
        edrString(HEADER.SENDER)= theSender;
        Long i;  
        Bool senderPresent = false;

        if ( (strLength(theSender) != 5) or 
               (validateSyntax(theSender, "CHECK_ALPHANUMERIC_UPPER") == false) )
        {
          edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "Sender", "38", "121", "Syntax error");
          edrAddError("ERR_TAP3_RET", 4, "fatal", "121", "38", "0", "-1", "-1", "Syntax error");
          edrDemandRollback();
        }
        else
        {
          for( i = 0; i < numOfPlmnoCode and senderPresent == false; i = i + 1 )
          {
            if( PLMNOCode[i] == theSender )
            {
              senderPresent = true;
            }
          }

          if ( senderPresent == false )
          {
            edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "Sender", "38", "215", "Value out of range");
            edrAddError("ERR_TAP3_RET", 4, "fatal", "215", "38", "0", "-1", "-1", "Value out of range");
            edrDemandRollback();
          }
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  SequenceNumber_opt:                                                         
      SequenceNumber                                                          
    |/* EMPTY */
      {
        edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "Nrtrde", "1", "329", "Mandatory item Sequence Number missing within group");
        edrAddError("ERR_TAP3_RET", 4, "fatal", "329", "1", "0", "-1", "-1", "Mandatory item Sequence Number missing within group");
        edrDemandRollback();
      }                                                                          
    ;                                                                            
                                                                                 
  SequenceNumber:                                                             
      NRTRDE_0201.SequenceNumber                                        
      {                                                                          
        //logStdout("NRTRDE_0201.SequenceNumber.SequenceNumber");    
        //logStdout("Parsed Leaf SequenceNumber\n");
        Long theFileSeqNum     = strToLong(tokenString("NRTRDE_0201.SequenceNumber.SequenceNumber"));
        String lastSequenceNumber = tokenString("NRTRDE_0201.SequenceNumber.SequenceNumber");
        edrLong(HEADER.SEQUENCE_NUMBER)       = theFileSeqNum;

        if( validateSyntax(lastSequenceNumber, "CHECK_NUM") == false )
        {
          edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "File Sequence Number", "39", "120", "Syntax Error");
          edrAddError("ERR_TAP3_RET", 4, "fatal", "120", "39", "0", "-1", "-1", "Syntax error");
          edrDemandRollback();
        }
        else if( validateOOR(lastSequenceNumber, "9999999", "1", "INTEGER_TYPE") == false)
        {
          edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "File Sequence Number", "39", "214", "Value Out Of Range");
          edrAddError("ERR_TAP3_RET", 4, "fatal", "214", "39", "0", "-1", "-1", "Value Out Of Range");
          edrDemandRollback();
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                
  ServiceCode_opt:                                        
      ServiceCode                                         
    |
      {
        if( record_Type == record_MOC )
        { 
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "316", 
                                         "Neither of items TeleService Code or Bearer Service Code present within group");
          edrAddError("ERR_TAP3_RET", 3, "severe", "316", applicationID, "0", "-1", "-1", 
                                         "Neither of items TeleService Code or Bearer Service Code present within group");
        }
        else if( record_Type == record_MTC )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "323",
                                         "Neither of items TeleService Code or Bearer Service Code present within group");
          edrAddError("ERR_TAP3_RET", 3, "severe", "323", applicationID, "0", "-1", "-1",
                                         "Neither of items TeleService Code or Bearer Service Code present within group");
        }
      }	  
    ;                                                           
                                                                
  ServiceCode:                                                       
      NRTRDE_0201.ServiceCode                                  
      {                                                                    
        //logStdout("NRTRDE_0201.ServiceCode");    
        //logStdout("Parsed Choice ServiceCode\n");                 
      }                                                         
      ServiceCode_elems                                   
      BlockEnd                                                
      {                                                         
        //logStdout("NRTRDE_0201.ServiceCode");  
        //logStdout("ServiceCode Choice END.\n");        
      }                                                         
    ;                                                           
                                                                
  ServiceCode_elems:                                      
      teleServiceCode_ServiceCode     
    | bearerServiceCode_ServiceCode     
    ;                                                           
                                                                
  teleServiceCode_ServiceCode:                                                       
      {                                                                                 
        currBlock = "teleServiceCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      TeleServiceCode                                                           
    ;                                                                                   
                                                                                        
  bearerServiceCode_ServiceCode:                                                       
      {                                                                                 
        currBlock = "bearerServiceCode";                                                   
        //logStdout("currContext= " + currContext + "\n");                           
      }                                                                                 
      BearerServiceCode                                                           
    ;                                                                                   
                                                                                        
                                                                                 
  SgsnAddress_opt:                                                         
      SgsnAddress                                                          
    |/* EMPTY */
      {
        createErrorContext();
        edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "309", "Mandatory item SGSN Address missing within group");
        edrAddError("ERR_TAP3_RET", 3, "severe", "309", applicationID, "0", "-1", "-1", "Mandatory item SGSN Address missing within group");
      }                                                                            
    ;                                                                            
                                                                                 
  SgsnAddress:                                                             
      NRTRDE_0201.SgsnAddress                                        
      {                                                                          
        //logStdout("NRTRDE_0201.SgsnAddress.SgsnAddress");    
        //logStdout("Parsed Leaf SgsnAddress\n");
        Bool sgsnAddressIsCorrect; 
        edrConnectToken(DETAIL.ASS_GPRS_EXT.SGSN_ADDRESS, 0, "NRTRDE_0201.SgsnAddress.SgsnAddress");
  
        if( strSearch( edrString(DETAIL.ASS_GPRS_EXT.SGSN_ADDRESS, 0), "." ) >= 0 )  // isIpV4
        {
          sgsnAddressIsCorrect = validateIpV4(edrString(DETAIL.ASS_GPRS_EXT.SGSN_ADDRESS, 0));
        }
        else  // isIpV6
        {
          sgsnAddressIsCorrect = validateIpV6(edrString(DETAIL.ASS_GPRS_EXT.SGSN_ADDRESS, 0));
        }
        if( sgsnAddressIsCorrect == false )
        {

          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "SgsnAddress", "40", "123", "Syntax does not conform to section 5.4");
          edrAddError("ERR_TAP3_RET", 3, "severe", "123", "40", "0", "-1", "-1", "Syntax does not conform to section 5.4");
          edrDemandRollback();
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  SpecificationVersionNumber_opt:                                                         
      SpecificationVersionNumber                                                           
    |/* EMPTY */
      {
        edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "Nrtrde", "1", "326", "Mandatory item Specification Version Number missing within group");
        edrAddError("ERR_TAP3_RET", 4, "fatal", "326", "1", "0", "-1", "-1", "Mandatory item Specification Version Number missing within group");
        edrDemandRollback();
      }                                                                          
    ;                                                                            
                                                                                 
  SpecificationVersionNumber:                                                             
      NRTRDE_0201.SpecificationVersionNumber                                        
      {                                                                          
        //logStdout("NRTRDE_0201.SpecificationVersionNumber.SpecificationVersionNumber");
        edrConnectToken(HEADER.SPECIFICATION_VERSION_NUMBER, "NRTRDE_0201.SpecificationVersionNumber.SpecificationVersionNumber");
        //logStdout("Parsed Leaf SpecificationVersionNumber\n"); 
        if ( edrLong(HEADER.SPECIFICATION_VERSION_NUMBER) != 2 ) 
        {
          edrAddError("ERR_TAP3_FATAL", LOG_MAJOR, "SpecificationVersionNumber", "41", "216", "Value out of range");
          edrAddError("ERR_TAP3_RET", 3, "fatal", "216", "41", "0", "-1", "-1", "Value Out Of Range"); 
          edrDemandRollback();
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  SupplementaryServiceCode_opt:                                                         
      SupplementaryServiceCode                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  SupplementaryServiceCode:                                                             
      NRTRDE_0201.SupplementaryServiceCode                                        
      {                                                                          
        //logStdout("NRTRDE_0201.SupplementaryServiceCode.SupplementaryServiceCode");    
        //logStdout("Parsed Leaf SupplementaryServiceCode\n");
        edrConnectToken(DETAIL.ASS_GSMW_EXT.SS_PACKET.SS_EVENT, 0, 0, "NRTRDE_0201.SupplementaryServiceCode.SupplementaryServiceCode");
        String lastSSCode = tokenString("NRTRDE_0201.SupplementaryServiceCode.SupplementaryServiceCode");
        if( validateHexValue(lastSSCode) == false )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "SupplementaryServiceCode", "42", "125", "Syntax error");
          edrAddError("ERR_TAP3_RET", 3, "severe", "125", "42", "0", "-1", "-1", "Syntax error"); 
        }
        else if ( lastSSCode != "29" and lastSSCode != "2A" and lastSSCode != "2B"  ) 
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "SupplementaryServiceCode", "42", "217", "Value out of range");
          edrAddError("ERR_TAP3_RET", 3, "severe", "217", "42", "0", "-1", "-1", "Value Out Of Range"); 
        }
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  TeleServiceCode_opt:                                                         
      TeleServiceCode                                                          
    |/* EMPTY */
      {
        if ( bearerServiceCodeIsMissing == true )
        {
          createErrorContext();
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, applicationName, applicationID, "34", "Neither of items TeleService Code or Bearer Service Code present within group");
          edrAddError("ERR_TAP3_RET", 3, "severe", "34", applicationID, "0", "-1", "-1", "Neither of items TeleService Code or Bearer Service Code present within group");
        } 
      } 
    ;                                                                            
                                                                                 
  TeleServiceCode:                                                             
      NRTRDE_0201.TeleServiceCode                                        
      {                                                                          
        //logStdout("NRTRDE_0201.TeleServiceCode.TeleServiceCode");    
        //logStdout("Parsed Leaf TeleServiceCode\n");
        edrConnectToken(DETAIL.BASIC_SERVICE, "NRTRDE_0201.TeleServiceCode.TeleServiceCode");
        lastTeleServiceCode = edrString(DETAIL.BASIC_SERVICE);
        edrString(DETAIL.BASIC_SERVICE) = "0" + edrString(DETAIL.BASIC_SERVICE);
        Bool codePresent = false;
        Long i;
        for( i = 0 ; i < numTeleServiceCode and codePresent == false ; i = i + 1 )
        {
          if( lastTeleServiceCode == TeleServiceCodeArr[i])
          {
            codePresent = true;
          }
        }  
        
        if( validateHexValue(lastTeleServiceCode) == false )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "TeleServiceCode", "43", "126", "Syntax error");
          edrAddError("ERR_TAP3_RET", 3, "severe", "126", "43", "0", "-1", "-1", "Syntax error"); 
        }
        else if ( codePresent == false ) 
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "TeleServiceCode", "43", "218", "Value out of range");
          edrAddError("ERR_TAP3_RET", 3, "severe", "218", "43", "0", "-1", "-1", "Value Out Of Range"); 
        } 

        if( (lastTeleServiceCode == "20" or lastTeleServiceCode == "21" or lastTeleServiceCode == "22") and
            (edrLong(DETAIL.TOTAL_CALL_EVENT_DURATION) > 0) )
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "CallEventDuration", "19", "201", "Value out of range");
          edrAddError("ERR_TAP3_RET", 3, "severe", "201", "19", "0", "-1", "-1", "Value Out Of Range");
        } 
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  ThirdPartyNumber_opt:                                                         
      ThirdPartyNumber                                                          
    |                                                                            
    ;                                                                            
                                                                                 
  ThirdPartyNumber:                                                             
      NRTRDE_0201.ThirdPartyNumber                                        
      {                                                                          
        //logStdout("NRTRDE_0201.ThirdPartyNumber.ThirdPartyNumber");    
        //logStdout("Parsed Leaf ThirdPartyNumber\n");
        edrConnectToken(DETAIL.C_NUMBER, "NRTRDE_0201.ThirdPartyNumber.ThirdPartyNumber");
      }                                                                          
    ;                                                                            
                                                                                 
                                                                                 
  UtcTimeOffset_opt:                                                         
      UtcTimeOffset                                                          
    |/* EMPTY */
      {
        if ( record_Type == record_Header )
        {
          edrAddError("ERR_TAP3_WARNING", LOG_WARNING, "FileAvailableTimeStamp", "31", "301", "Missing UTC Time Offset Code");
        }
        else
        {
          edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "CallEventStartTimeStamp", "21", "300", "Missing UTC Time Offset Code");
          edrAddError("ERR_TAP3_RET", 3, "severe", "300", "21", "0", "-1", "-1", "Missing UTC Time Offset Code");
        }
      }                                                                            
    ;                                                                            
                                                                                 
  UtcTimeOffset:                                                             
      NRTRDE_0201.UtcTimeOffset                                        
      {                                                                          
        //logStdout("NRTRDE_0201.UtcTimeOffset.UtcTimeOffset");    
        //logStdout("Parsed Leaf UtcTimeOffset\n");
        String utcTimeOffsetStr = tokenString("NRTRDE_0201.UtcTimeOffset.UtcTimeOffset");
        if ( record_Type == record_Header )
        {
          edrString(HEADER.UTC_TIME_OFFSET)= utcTimeOffsetStr;
        }
        else
        {
          edrString(DETAIL.UTC_TIME_OFFSET)= utcTimeOffsetStr;
        }
        Long utcTimeOffsetVal   = strToLong(utcTimeOffsetStr);
        String mmUtcTimeOffset        = strSubstr(utcTimeOffsetStr,3,2);
        String First_char = strSubstr(utcTimeOffsetStr,0,1);
        String Rest_chars = strSubstr(utcTimeOffsetStr,1,4);
        
        if ( ( strLength(utcTimeOffsetStr) != 5 ) 
          or ( ( First_char != "+" ) and ( First_char != "-" ) ) 
          or ( strSearchRegExpr(Rest_chars, "[^0-9]") >= 0 ) )
        {
          if ( record_Type == record_Header )
          {
            edrAddError("ERR_TAP3_WARNING", LOG_WARNING, "UtcTimeOffset", "45", "128", "Syntax error");
          }
          else
          {
            edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "UtcTimeOffset", "45", "127", "Syntax error");
            edrAddError("ERR_TAP3_RET", 4, "severe", "127", "45", "0", "-1", "-1", "Syntax error");
          }
        }
        else if( ( utcTimeOffsetVal  > 1300 ) 
              or ( utcTimeOffsetVal  < -1300 )
              or (strToLong(mmUtcTimeOffset) % 15 != 0 ) )
        {
          if ( record_Type == record_Header )
          {
            edrAddError("ERR_TAP3_WARNING", LOG_WARNING, "UtcTimeOffset", "45", "220", "Value Out of Range");
          }
          else
          {
            edrAddError("ERR_TAP3_SEVERE", LOG_MAJOR, "UtcTimeOffset", "45", "219", "Value Out of Range");
            edrAddError("ERR_TAP3_RET", 4, "severe", "219", "45", "0", "-1", "-1", "Value Out of Range");
          }

        } 
      }                                                                          
    ;                                                                            
                                                                                 
}                                             
