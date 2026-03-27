#ifndef BAS_DBTBUFFER_HPP
#define BAS_DBTBUFFER_HPP
//==============================================================================
//
// Copyright (c) 2005, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS
//------------------------------------------------------------------------------
// Module Description:
//   DBTBuffer  Template class implementation.
//------------------------------------------------------------------------------
// Responsible: Rikun Tang
//------------------------------------------------------------------------------
// $Log: DBTBuffer.hpp,v $

#ifndef RWDBTBUFFER_H
  #include <rw/db/tbuffer.h>
#endif
#ifndef _PIN_TYPE_H_
  #include "pin_type.h"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_DBINTEGER_HPP
  #include "BAS/DBInteger.hpp"
#endif

namespace BAS
{
template<class T>
class DBTBuffer :  public RWDBBuffer
{
  public:
    DBTBuffer(){};
    ~DBTBuffer(){};
};
/** <tt><b>DBTBuffer&ltint64&gt</b></tt> encapsulates a fixed-sized array of int64.

    This class is a specialized implementation of RogueWave's 
    <tt><A HREF="http://timos.portal.com/RogueWaveDocumentation/html/dbcoreref/rwdbtbuffer.html">RWDBTBuffer</A></tt>. 

    <p><b>RWDBTBuffer</b> provides mechanisms for converting buffer items to and from RWDBValues. RWDBTBuffer does not support int64 on 
    Windows Itanium 64-bit and Unix 32-bit platforms, as it can not convert __int64 and 'long long' to RWDBValues.

    <p><b>DBTBuffer&ltint64&gt</b> is implemented to work like <b>RWDBTBuffer&ltint64&gt</b> on Windows 64-bit and Unix 32-bit platforms, 
    its functionality is gained at the expense of speed. 

    <p><b>Sample usage of DBTBuffer: </b><br>
    #if !defined(HAS_LONGLONG) <br>
    #include "BAS/DBTBuffer.hpp" <br>
    typedef BAS::DBTBuffer&ltint64&gt BulkLongVector; <br>
    #else <br>
    typedef RWDBTBuffer&ltint64&gt BulkLongVector; <br>
    #endif <br>
 */

template<> class DBTBuffer<int64> :  public RWDBBuffer
{
  public:

    DBTBuffer(RWSize_T entries = 1, RWSize_T width = 0) 
    : RWDBBuffer(RWDBCTypeOf<DBInteger>(),
      RWDBCTypeStockMemoryManager<DBInteger>::allocator,
      RWDBCTypeStockMemoryManager<DBInteger>::deallocator,
      entries.value())
    { 
      D_ENTER("BAS::DBTBuffer::DBTBuffer(RWSize_T, RWSizeT)" );
    }

    DBTBuffer(int64 *data, RWSize_T entries = 1, RWSize_T width = 0)
    : RWDBBuffer(new DBInteger(BAS::toDBInteger(*data)), 
      RWDBCTypeOf<DBInteger>(), 
      entries.value())
    { 
      D_ENTER("BAS::DBTBuffer::DBTBuffer(int64*, RWSize_T, RWSizeT)" );
    }

    DBTBuffer(int64 *data, RWDBNullIndicator* indicator,
              RWSize_T entries = 1, RWSize_T width = 0) 
    : RWDBBuffer(new DBInteger(BAS::toDBInteger(*data)), 
      indicator, RWDBCTypeOf<DBInteger>(), 
      entries.value())
    { 
       D_ENTER("BAS::DBTBuffer::DBTBuffer(int64*, RWDBNullIndicator*, RWSize_T, RWSizeT)" );
    }

    virtual ~DBTBuffer()
    {  
    }
    
    // [] operator to get the value.
    const int64& operator[](size_t index) const 
    {
      RWASSERT(index < this->entries_);

      // Get the value from RWDecimalPortable 
      DBInteger tmp = (reinterpret_cast<DBInteger*>(this->data_))[index];
      valueM = BAS::toInt64(tmp);
      return valueM;
    }

    // [] operator to get the value.
    int64& operator[](size_t index) 
    {
      RWASSERT(index < this->entries_);

      DBInteger tmp = (reinterpret_cast<DBInteger*>(this->data_))[index];
      valueM = BAS::toInt64(tmp);
      return valueM;
    }

    // Function to set the data into the DBTBuffer.
    void setData(int64& newData)
    { 
      unsetNull();

      DBInteger tmpData = BAS::toDBInteger(newData);

      for (size_t i = 0; i < this->entries_; i++)
      {
        (reinterpret_cast<DBInteger*>(this->data_))[i] = tmpData;
      }
    }

    // Function to set the data into the DBTBuffer at a particular index.
    void setData(size_t index, int64& newData)
    {
      RWASSERT(index < this->entries_);
      unsetNull(index);

      DBInteger tmpData = BAS::toDBInteger(newData);
      (reinterpret_cast<DBInteger*>(this->data_))[index] = tmpData;
    }
  private:
    //Private copy constructor/assignment operator -- forbidden!
    DBTBuffer(const DBTBuffer<int64>&);
    DBTBuffer<int64>& operator=(const DBTBuffer<int64>&);
    mutable int64 valueM;
};
}
#endif // BAS_DBTBUFFER_HPP
