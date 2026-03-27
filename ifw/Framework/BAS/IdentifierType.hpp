#ifndef BAS_POIDTYPE_H
#define BAS_POIDTYPE_H
/*
 * IdentifierType.h 
 *
 * Copyright (c) 2002, 2009, Oracle and/or its affiliates. 
 * All rights reserved.
 *      This material is the confidential property of Oracle Corporation. 
 *      or its subsidiaries or licensors and may be used, reproduced, stored
 *      or transmitted only in accordance with a valid Oracle license or 
 *      sublicense agreement.
 */

namespace BAS {
    /**
     * \class IdentifierType IdentifierType.h BAS/IdentifierType.h
     * Class representing the type of a poid in Infranet. Has two 
     * representations, that of an integer, and a string format for 
     * compatibility
     *
     */
	class IdentifierType {
    public:
        /** 
         * Construct a poid type from its integer representation 
         * @param i the id stored in the data dictionary that represents
         * this poid
         */
        IdentifierType(const int i);

        ~IdentifierType();

        /**
         * Construct a poid type from its strings representation
         * @param type the name of the poid (eg /account, /service/email)
         */
        IdentifierType(const char *type);

        /**
         * Conversion operator to a character representation
         * @return string name of the poid (eg /account, /service/email)
         */
        operator const char *();

        /** 
         * Conversion operator to an integer representation
         * @return integer represetation of the poid
         */
        operator const int();
    private:
        const int intTypeM;
        const char *charTypeM;
    };

    IdentifierType::IdentifierType(const int i) : charTypeM(0), intTypeM(i)
    {
    }
    IdentifierType::IdentifierType(const char *type) : 
            charTypeM(type), intTypeM(0)
    {
    }

    IdentifierType::~IdentifierType()
    {
        delete charTypeM;
    }
    IdentifierType::operator const char *()
    {
        return charTypeM;
    }
    IdentifierType::operator const int()
    {
        return intTypeM;
    }
}
        
#endif
