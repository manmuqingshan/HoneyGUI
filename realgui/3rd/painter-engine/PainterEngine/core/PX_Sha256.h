////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  WjCryptLib_Sha256
//
//  Implementation of SHA256 hash function.
//  Original author: Tom St Denis, tomstdenis@gmail.com, http://libtom.org
//  Modified by WaterJuice retaining Public Domain license.
//
//  This is free and unencumbered software released into the public domain - June 2013 waterjuice.org
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PX_SHA256
#define PX_SHA256
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  IMPORTS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PX_Typedef.h"

typedef struct
{
    px_uint64    length;
    px_uint32    state[8];
    px_uint32    curlen;
    px_uchar     buf[64];
} PX_Sha256Context;

#define SHA256_HASH_SIZE           ( 256 / 8 )

typedef struct
{
    px_uchar      bytes [SHA256_HASH_SIZE];
} PX_SHA256_HASH;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Sha256Calculate
//
//  Combines Sha256Initialise, Sha256Update, and Sha256Finalise into one function. Calculates the SHA256 hash of the
//  buffer.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void
PX_Sha256Calculate
(
    void        *Buffer,         // [in]
    px_uint32            BufferSize,     // [in]
    PX_SHA256_HASH        *Digest          // [in]
);

void PX_Sha256CalculateHashString(px_void *buffer, px_uint32 bufferSize, px_char stringKey[32]);
#endif
