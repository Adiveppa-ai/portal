#ifndef PLG_TRAILERINFO_HPP
#define PLG_TRAILERINFO_HPP
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Base
//------------------------------------------------------------------------------
// Module Description:
//  <description>
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: jens keckstein
//
// $RCSfile: TrailerInfo.hpp,v $
// $Revision: 1.2 $
// $Author: mliebmann $
// $Date: 2001/10/16 08:48:21 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TrailerInfo.hpp,v $
// Revision 1.2  2001/10/16 08:48:21  mliebmann
// PETS #40529 performance bottlenecks - BAS::string-compare to BAS::DateTime-compare changed
//
// Revision 1.1  2001/09/26 10:28:00  sd
// - PETS #39870 EDR::Statistic should not be part of module EDR
//
// Revision 1.32  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.31  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.30  2001/08/03 15:54:23  bt
// PETS #36696 - Type of total duration changed from int64 to decimal.
//             - Method setEDRContainerIndices() enabled.
//
// Revision 1.29  2001/05/28 10:24:35  sd
// - Adjusted to the new container description
//
// Revision 1.28  2001/05/03 16:09:35  bt
// Format renamed to Pipeline.
//
// Revision 1.27  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.1  2001/01/09 09:52:41  sd
// - Backup version.
//
// Revision 1.25  2000/09/29 10:09:28  aro
// Tried to fix doc++ comments.
//
// Revision 1.24  2000/09/27 11:47:16  bt
// Return type 'Long Long' changed to 'Long' for function totalQuantityValue().
//
// Revision 1.23  2000/09/21 09:53:49  jkeckst
// modify the addEdr to make it faster
//
// Revision 1.22  2000/09/07 13:46:55  jkeckst
// add new copyright info
//
// Revision 1.21  2000/02/24 10:02:28  jkeckst
// remove class name from constructor
//
// Revision 1.20  2000/02/22 12:25:08  jkeckst
// change the getData access.
//
// Revision 1.19  2000/01/26 14:49:25  jkeckst
// this is the version 2 of the edr-container
//
// Revision 1.17  2000/01/25 12:07:48  jkeckst
// first try
//
// Revision 1.16  2000/01/18 07:58:04  jkeckst
// this is the new EDR-Container v4.0 (first version)
//
// Revision 1.15  1999/12/14 12:46:36  sd
// Introduction of BAS::Decimal.
//
// Revision 1.13  1999/09/23 13:38:02  jkeckst
// change Long double to Long Long
//
// Revision 1.12  1999/09/09 16:02:20  bt
// RWCString replaced by BAS::String.
//
// Revision 1.11  1999/08/02 14:37:17  pengelbr
// Add new field for totalAlternativeCharge and modify sum-Function.
//
// Revision 1.10  1999/07/16 08:27:34  jkeckst
// change the fieldname callDuration to quantityValue
//
// Revision 1.5  1999/05/27 14:21:15  jkeckst
// change the names in trailerInfos equal to edr_container
//
// Revision 1.3  1999/03/29 08:04:21  jkeckst
// add new methode addEDR and remove all superfluous attributes
//
//==============================================================================

#if !defined PLG_EXPORT
  #if defined(WINDOWS)
    #if !defined(PLG_INTERNAL)
      #define PLG_EXPORT __declspec(dllimport)
    #else
      #define PLG_EXPORT __declspec(dllexport)
    #endif
  #else
    #define PLG_EXPORT 
  #endif
#endif

#ifndef   TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef   BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_DECIMAL_HPP
  #include "BAS/Decimal.hpp"
#endif
#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
namespace PLG
{
/**  <tt><b>TrailerInfo</b></tt> The statistic class for all trailer 
  informations.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: TrailerInfo.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.2 $</font></td>
    <td><font size=-1>$Date: 2001/10/16 08:48:21 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>                

    This class collects all informations from the EDR container.
*/
class TrailerInfo : public BAS::RegisteredObject
{
  // CodeReview - 08.2001 - mwriedt - C - missing in doc (UML)
  // Checked by CodeReview - 08.2001 - sd - C - is is not necessary to add
  //                                            all helper classes to UML doc

  public:
    /**@name TrailerInfor constructors and destructors */
    //@{ 

    /** Default constructor
     */
    TrailerInfo();

    /** Constructor for a registered object
     *  @param name The name of the registered object
     */
    TrailerInfo( const BAS::String& name );
    
    /** Destructor
     */
    ~TrailerInfo();

    //@}

    /**@name TrailerInfo public methods */
    //@{ 

    /** Assignment operator
     *  @param right The right side object of the assignment
     */
    const TrailerInfo& operator=( const TrailerInfo& right );

    /** Comparison operator for equality
     */
    int operator==( const TrailerInfo& right ) const;    

    /** Set the date of the first call
     *  @param value Date of the first call
     */
    void dateOfFirstCall(const BAS::DateTime & value);

    /** Set the date of the last call
     *  @param value Date of the last call
     */
    void dateOfLastCall( const BAS::DateTime& value );

    /** Set the total number of calls
     *  @param value The total number of calls
     */
    void totalNoOfCalls( const int64 value);

    /** Set the total retail amount
     *  @param value The total retail amount
     */
    void totalRetailAmount( const BAS::Decimal& value );

    /** Set the total wholesale amount
     *  @param value The total wholesale amount
     */
    void totalWholesaleAmount( const BAS::Decimal& value );

    /** Set the total duration
     *  @param value The total duration
     */
    void totalDuration(const BAS::Decimal& value);

    /** Get the date of the first call
     *  @return The date of the first call as string in format YYYYMMDDHHMMSS
     */
    const BAS::DateTime& dateOfFirstCall() const;

    /** Get the date of the last call
     *  @return The date of the first call as string in format YYYYMMDDHHMMSS
     */
    const BAS::DateTime& dateOfLastCall() const;

    /** Get the total number of calls
     *  @return The total number of calls
     */
    const int64 totalNoOfCalls() const;
    
    /** Get the total duration
     *  @return The total duration
     */
    const BAS::Decimal& totalDuration() const;
    
    /** Get the total retail amount
     *  @return The total retail amount
     */
    const BAS::Decimal& totalRetailAmount() const;
   
    /** Get the total wholesale amount
     *  @return The total wholesale amount
     */
    const BAS::Decimal& totalWholesaleAmount() const;

    /** Add other trailer information to this trailer
     *  @param right The trailer information to add
     */
    void addTrailer( const TrailerInfo& right );
   
    /** Update the trailer information for an EDR container
     *  @param newEntry The edr to use for the update
     */
    void addEDR( EDR::Container* newEntry );

    /** Assign other trailer information to this trailer information
     *  @param right The trailer information to assign
     */
    void assignTrailer( const TrailerInfo& right );

    /** Clear the trailer information
     */
    void clear (void);

    /** Output operator
     */
    friend std::ostream& operator<<(std::ostream& os, const TrailerInfo& rVal);

    /** Output operator
     */
    friend std::ostream& operator<<(std::ostream& os, const TrailerInfo* rVal);

    //@}
    
  private:
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    TrailerInfo(TrailerInfo& right);
    const TrailerInfo& operator=(TrailerInfo& right);
  
    bool setEDRContainerIndices();

    // Instance members
    BAS::DateTime dateOfFirstCallM;
    BAS::DateTime dateOfLastCallM;
    int64        totalNoOfCallsM;
    BAS::Decimal totalRetailAmountM;   // CHARGED AMOUNT VALUE 
    BAS::Decimal totalWholesaleAmountM;// Wholesale
    BAS::Decimal totalDurationM;     
    EDR::Index   startTimeStampIdxM;
    EDR::Index   wholesaleAmountIdxM;
    EDR::Index   retailAmountIdxM;
    EDR::Index   durationIdxM;

    // Class members
    PLG_EXPORT static const BAS::String registryPipelinesCM;
};

std::ostream& operator<<(std::ostream& os, const TrailerInfo& rVal);

std::ostream& operator<<(std::ostream& os, const TrailerInfo* rVal);

inline void
TrailerInfo::dateOfFirstCall(const BAS::DateTime & value)
{
  dateOfFirstCallM = value;
}

inline void
TrailerInfo::dateOfLastCall(const BAS::DateTime & value)
{
  dateOfLastCallM = value;
}

inline void
TrailerInfo::totalNoOfCalls(const int64 value)
{
  totalNoOfCallsM = value;
}

inline void
TrailerInfo::totalDuration(const BAS::Decimal& value)
{
  totalDurationM = value;
}

inline void
TrailerInfo::totalRetailAmount(const BAS::Decimal& value)
{
  totalRetailAmountM = value;
}

inline void
TrailerInfo::totalWholesaleAmount(const BAS::Decimal& value)
{
  totalWholesaleAmountM = value;
}


inline const BAS::DateTime &
TrailerInfo::dateOfFirstCall() const
{
  return dateOfFirstCallM;
}

inline const BAS::DateTime &
TrailerInfo::dateOfLastCall() const
{
  return dateOfLastCallM;
}

inline const int64
TrailerInfo::totalNoOfCalls() const
{
  return totalNoOfCallsM;
}

inline const BAS::Decimal&
TrailerInfo::totalDuration() const
{
  return totalDurationM;
}

inline const BAS::Decimal&
TrailerInfo::totalRetailAmount() const
{
  return totalRetailAmountM;
}

inline const BAS::Decimal&
TrailerInfo::totalWholesaleAmount() const
{
  return totalWholesaleAmountM;
}
}
#endif // EDR::TRAILERINFO_HPP

