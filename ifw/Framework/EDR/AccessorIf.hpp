#ifndef EDR_ACCESSORIF_H
#define EDR_ACCESSORIF_H

namespace BAS 
{
    class String;
    class Decimal;
    class Identifier;
    class DateTime;
}

namespace EDR
{
	class Index;
	class CompactPoid;
}

namespace EDR
{
    /** Interface class to define accessor methods
     * Defines an abstract interface that accessors (iterator + container)
     * implement
     */
	class AccessorIf  D_THREADINFO
	{
	D_SINGLETHREADED
    public:
        /** Get a string value from the edr
         *  @param index The index for the edr field
         *  @return Reference to string value
         */
        virtual const BAS::String& getString(const EDR::Index& index) const 
            = 0;
        
        /** Get a poid value from the edr
         *  @param index The index for the edr field
         *  @return Reference to poid value
         */
        virtual const EDR::CompactPoid& getCompactPoid(const EDR::Index& index) const 
            = 0;
        
        /** Get a decimal value from the edr
         *  @param index The index for the edr field
         *  @return Reference to decimal value
         */
        virtual const BAS::Decimal& getDecimal(const EDR::Index& index) const 
            = 0;

        /** Get a date value from the edr
         *  @param index The index for the edr field
         *  @return Reference to date/time value
         */
        virtual const BAS::DateTime& getDate(const EDR::Index& index) const 
            = 0;

        /** Get a long value from the edr
         *  @param index The index for the edr field
         *  @return The long value
         */
        virtual int64 getLong( const EDR::Index& index ) const = 0;

        /** Set a string value in the edr
         *  @param index The index for the edr field
         *  @param string The string value to set
         *  @return <b>true</b> on success, <b>false</b> otherwise
         */
        virtual bool setString( const EDR::Index&  index, 
                        const BAS::String& string ) = 0;
        
        /** Set a poid value in the edr
         *  @param index The index for the edr field
         *  @param poid The poid value to set
         *  @return <b>true</b> on success, <b>false</b> otherwise
         */
        virtual bool setCompactPoid( const EDR::Index&  index, 
                      const EDR::CompactPoid& poid ) = 0;

        /** Set a decimal value in the edr
         *  @param index The index for the edr field
         *  @param value The decimal value to set
         *  @return <b>true</b> on success, <b>false</b> otherwise
         */
        virtual bool setDecimal( const EDR::Index&   index, 
                         const BAS::Decimal& value ) = 0;


        /** Set a long value in the edr
         *  @param index The index for the edr field
         *  @param value The long value to set
         *  @return <b>true</b> on success, <b>false</b> otherwise
         */
        virtual bool setLong( const EDR::Index& index, int64 value ) = 0;
        
        /** Set a date value in the edr
         *  @param index The index for the edr field
         *  @param value The date value to set
         *  @return <b>true</b> on success, <b>false</b> otherwise
         */
        virtual bool setDate( const EDR::Index& index, 
                      const BAS::DateTime& value ) = 0;
    };
}

#endif
