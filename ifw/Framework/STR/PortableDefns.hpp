#ifndef __PORTABLE_DEFNS_H__
#define __PORTABLE_DEFNS_H__

//==============================================================================
//
// Copyright (c) 1996, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: STR
//------------------------------------------------------------------------------
// Module Description:
//   Basic stream class implementation.
//
//------------------------------------------------------------------------------
//
// Revision: 10001  7.4_patch  11-Sep-2009 cprabhak 
// Added Copyright information 
//==============================================================================

#if defined(__sparc)
extern "C"
{
  int CASIO_internal(int*, int, int);
  void* CASPO_internal(void*, void*, void*);
};
/* 32 bit */
#define CAS32(_a,_o,_n) (CASIO_internal((int*)(_a),(int)(_o),(int)(_n)))
/* 64 bit */
#define CAS64(_a,_o,_n) (CASPO_internal((void*)(_a),(void*)(_o),(void*)(_n)))

#elif (defined __hpux && defined __ia64)
#define FENCE (_Asm_fence) (_UP_CALL_FENCE | _UP_SYS_FENCE | \
     _DOWN_CALL_FENCE | _DOWN_SYS_FENCE )

/* 32 bit Compare and Swap */
#define CAS32(_a,_o,_n)  (_Asm_mov_to_ar((_Asm_app_reg)_AREG_CCV, \
    (u_int32)_o, FENCE), _Asm_mf(),\
    (_Asm_cmpxchg((_Asm_sz)_SZ_W, (_Asm_sem)_SEM_ACQ,\
    (u_int32*)_a, (u_int32)_n, (_Asm_ldhint)_LDHINT_NONE)) )

/* 32 bit Acquire */
#define CAS_ACQ32(_a,_o,_n) ((_Asm_mov_to_ar((_Asm_app_reg)_AREG_CCV, \
    (u_int32)_o, FENCE), \
    (_Asm_cmpxchg((_Asm_sz)_SZ_D, (_Asm_sem)_SEM_ACQ,\
    (u_int32*)_a, (u_int32)_n, (_Asm_ldhint)_LDHINT_NONE) )))

/* 32 bit Release */
#define CAS_REL32(_a,_o,_n) ((_Asm_mov_to_ar((_Asm_app_reg)_AREG_CCV, \
    (u_int32)_o, FENCE), \
    (_Asm_cmpxchg((_Asm_sz)_SZ_D, (_Asm_sem)_SEM_REL,\
    (u_int32*)_a, (u_int32)_n, (_Asm_ldhint)_LDHINT_NONE) )))

/* 64 bit Compare and Swap */
#define CAS64(_a,_o,_n) ((_Asm_mov_to_ar((_Asm_app_reg)_AREG_CCV, \
    (u_int64)_o, FENCE), _Asm_mf(),\
    (_Asm_cmpxchg((_Asm_sz)_SZ_D, (_Asm_sem)_SEM_ACQ,\
    (u_int64*)_a, (u_int64)_n, (_Asm_ldhint)_LDHINT_NONE) )))

/* 64 bit Acquire */
#define CAS_ACQ64(_a,_o,_n) ((_Asm_mov_to_ar((_Asm_app_reg)_AREG_CCV, \
    (u_int64)_o, FENCE), \
    (_Asm_cmpxchg((_Asm_sz)_SZ_D, (_Asm_sem)_SEM_ACQ,\
    (u_int64*)_a, (u_int64)_n, (_Asm_ldhint)_LDHINT_NONE) )))

/* 64 bit Release */
#define CAS_REL64(_a,_o,_n) ((_Asm_mov_to_ar((_Asm_app_reg)_AREG_CCV, \
    (u_int64)_o, FENCE), \
    (_Asm_cmpxchg((_Asm_sz)_SZ_D, (_Asm_sem)_SEM_REL,\
    (u_int64*)_a, (u_int64)_n, (_Asm_ldhint)_LDHINT_NONE) )))

#else // Non sparc, non itanium

/* 32 bit */
#define CAS32(_a,_o,_n) (_o)
/* 64 bit */
#define CAS64(_a,_o,_n) (_o)

#endif

#endif

