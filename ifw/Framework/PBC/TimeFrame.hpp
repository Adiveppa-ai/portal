#ifndef PBC_TIMEFRAME_HPP
#define PBC_TIMEFRAME_HPP
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PBC
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of a class for specifying time intervalls.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: TimeFrame.hpp,v $
// $Revision: 1.5 $
// $Author: aro $
// $Date: 2000/09/29 10:27:47 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.2  1999/07/14 13:31:07  sd
// Default constructor added
//==============================================================================

#ifndef   BAS_DATE_HPP
  #include "BAS/Date.hpp"
#endif
#ifndef   BAS_TIME_HPP
  #include "BAS/Time.hpp"
#endif
#ifndef   BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace PBC
{
/** <b><tt>TimeFrame</tt></b> is used to specify time intervalls.
  
    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: TimeFrame.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.5 $</font></td>
    <td><font size=-1>$Date: 2000/09/29 10:27:47 $</font></td>
    <td><font size=-1>$Author: aro $</font></td>
    </tr>
    </table>
*/
class TimeFrame D_THREADINFO
{
    
  public:
    /**@name TimeFrame constructors and destructor */
    //@{

    /** Default constructor. Object is invalid after construction! 
     */
    TimeFrame();

    /** Constructor. Use the isValid() method to check if the constructor was
        successful.
	@param validFrom Begin of time intervall in format 19990325 or MON20:00
	@param validTo End of time intervall in format 19981231 or TUE21:00
	@param timeFrom Begin of time intervall inside every day of date 
	                intervall
	@param timeTo End of time intervall inside every day of date intervall
     */
    TimeFrame( const BAS::String& validFrom, const BAS::String& validTo,
		   const BAS::String& timeFrom, const BAS::String& timeTo );

    //@}

    /** Outstream operator.
    */
    friend std::ostream& operator<<(std::ostream& os, const TimeFrame& value);

    /**@name TimeFrame public methods */
    //@{

    /** Setup the time frame.
 	@param validFrom Begin of time intervall in format 19990325 or MON20:00
	@param validTo End of time intervall in format 19981231 or TUE21:00
	@param timeFrom Begin of time intervall inside every day of date 
	                intervall
	@param timeTo End of time intervall inside every day of date intervall
	@return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setup( const BAS::String& validFrom, const BAS::String& validTo,
		const BAS::String& timeFrom, const BAS::String& timeTo );

    /** Check if the time frame contains the specified date/time.
	@param timeStamp Timestamp to check
	@return <b>true</b> if timestamp is contained, <b>false</b> otherwise
     */
    bool contains( const BAS::DateTime& timeStamp ) const;

    /** Check if the instance is valid.
	@return <b>true</b> if valid, <b>false</b> otherwise
     */
    bool isValid() const;

    //@}

  private:

    /** Extract the weekday number for a weekday description string. MON=1,
        ... SUN=7.
	@param string Input string
	@param da Return value for the extracted weekday
	@return <b>true</b> on success, <b>false</b> otherwise
     */
    static bool extractWeekday( const BAS::String& string, int& day );

    /** Extract the time from a weekday description string.
	@param string Input string
	@param timeSpecified Return value if a time was specified
	@param time Return value for the specified time
	@return <b>true</b> on success, <b>false</b> otherwise
     */
    static bool extractTime( const BAS::String& string, bool& timeSpecified,
			     BAS::Time& time );
      
    // member variables
    bool     isValidM;
    BAS::Date validFromDateM;
    BAS::Date validToDateM;
    bool     weekdayIntervallM;
    int      weekdayFromM;
    BAS::Time weekdayFromTimeM;
    int      weekdayToM;
    BAS::Time weekdayToTimeM;
    BAS::Time timeFromM;
    BAS::Time timeToM;
    
};

//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const TimeFrame& value);

//------------------------------------------------------------------------------
inline bool
TimeFrame::isValid() const
{
  return isValidM;
}
}
#endif // TIMEFRAME_HPP
