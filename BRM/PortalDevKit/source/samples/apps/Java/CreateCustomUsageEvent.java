/*********************************************************************
 *
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 *********************************************************************
 *
 *  To run this program you need to do the following steps
 *  1.  create custom fields
 *      Use the DevCenter-Storable class Editor to create storable event 
 *      classes and fields.
 *	Create the storable class of type /event/activity/email
 *	Create the following custom fields with following IDs greater than 10000
 *      Example: 
 *	   EMAIL_EVENT_INFO   PIN_FLDT_SUBSTRUCT [0]   ID# 10001
 *	        EMAIL_FROM    PIN_FLDT_STR [0]             10002
 *	        EMAIL_TO      PIN_FLDT_STR [0]             10003
 *      Load the customfields.sce in DevCenter-Storable class editor to make sure 
 *      that the above defined fields are available in your database.
 *   2. Create Java files for the custom fileds.
 *      In DevCenter: In the file menu, Click "Generate Custom Fields Source"
 *      Select the option to create the Java files.
 *   3. Compile the generated java files. 
 *   4. Create a directory hierarchy to reflect the java package name. 
 *      For Example: create com/portal/customfields.
 *   5. Copy all the .class files from step 3 to com/portal/customfields
 *   6. Package the .class files into a package customflds.jar        
 *   7. Update this source file to include the package where your custom fields 
 *      are. Example: import com.portal.customfields.*;
 *   8. Add customflds.jar to your classpath. 
 *
 *  For detailed information, please see our documentation.
 *
 *  To run this program from commandline
 *  USAGE: java CreateCustomUsageEvent
 ***************************************************************************/

import java.util.*;
import java.io.*;

import com.portal.pcm.*;
import com.portal.pcm.fields.*;

/**
 * The following program generates an email activity event for a given
 * account.
 */
public class CreateCustomUsageEvent
{
    private Date whenEventUsageOccurred = new Date();
    PortalContext pCtx = null;

    public CreateCustomUsageEvent() throws EBufException {
        /** Create a PortalContext object using the connect() method.
	       * This uses the Infranet.properties file for settings.  */
        pCtx = new PortalContext();
        pCtx.connect();
    }

    public void createUsage(String login) throws EBufException  {
       /* find the service given the login and service type */
       FList eService = findService(login,"/service/email");
       /* get the account poid and service poid from the output flist */
       Poid accountPoid = eService.get(FldAccountObj.getInst());
       Poid servicePoid = eService.get(FldPoid.getInst());
       FList resultList = generateEvent(accountPoid,servicePoid);
    }

    /* to find email service for the given login name  */
    protected FList findService(String login, String serviceType)
                                               throws EBufException {
      FList inflist = new FList();
      FList outflist = null;
      Poid tmppoid = new Poid(pCtx.getCurrentDB(),-1,serviceType);
      inflist.set(FldPoid.getInst(),tmppoid);
      inflist.set(FldLogin.getInst(),login);
      outflist = pCtx.opcode(PortalOp.ACT_FIND,inflist);
      return outflist;
    }

    /* generate activity event */
    protected FList generateEvent(Poid accountPoid, Poid servicePoid)
                                                      throws EBufException {
       /*set up the inputflist for PCM_OP_ACT_ACTIVITY, and execute opcode */
        FList inflist = new FList();
        FList outflist = null;
        inflist.set( FldPoid.getInst(), accountPoid );
        inflist.set( FldServiceObj.getInst(), servicePoid );
        inflist.set( FldProgramName.getInst(), "SampleAct" );
        inflist.set( FldStartT.getInst(), whenEventUsageOccurred );
        inflist.set( FldEndT.getInst(), whenEventUsageOccurred );
        inflist.set( FldObjType.getInst(), "/email");
        FList flt = createInheritedInfoSubstruct();
        inflist.set( FldInheritedInfo.getInst(),flt);
       /* Call PCM_OP_ACT_ACTIVITY. */
        outflist = pCtx.opcode( PortalOp.ACT_ACTIVITY, inflist );
        return outflist;
     }

     /* set custom email fields     */
	   protected FList createInheritedInfoSubstruct()
    {
         FList substruct = new FList();
         substruct.set(EmailFrom.getInst(),"mickey@portal.com");
         substruct.set(EmailTo.getInst(),"mouse@portal.com");
         FList inheritedInfo = new FList();
         inheritedInfo.set( EmailEventInfo.getInst(), substruct );
         return inheritedInfo;
    }


    public static void main( String [] args )
    {
      /* Allowing user to enter the login name for which they
            want to generate email activity event     */
       System.out.println("Enter the login name: ");
       String login = null;
       try {
          InputStreamReader isr = new InputStreamReader(System.in);
          BufferedReader br = new BufferedReader(isr);
          login = br.readLine();
          CreateCustomUsageEvent usage = new CreateCustomUsageEvent();
          usage.createUsage(login);
          System.out.println("Email event generated successfully for " + login);
       } catch (IOException ex) {
          ex.printStackTrace();
       } catch (EBufException e) {
            e.printStackTrace();
       }
     }

}
