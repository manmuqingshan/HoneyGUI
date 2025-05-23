////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  WjCryptLib_Sha1
//
//  Implementation of SHA1 hash function.
//  Original author:  Steve Reid <sreid@sea-to-sky.net>
//  Contributions by: James H. Brown <jbrown@burgoyne.com>, Saul Kravitz <Saul.Kravitz@celera.com>,
//  and Ralph Giles <giles@ghostscript.com>
//  Modified by WaterJuice retaining Public Domain license.
//
//  This is free and unencumbered software released into the public domain - June 2013 waterjuice.org
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PX_SHA1_H
#define PX_SHA1_H

#include "PX_Typedef.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  TYPES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sha1Context - This must be initialised using Sha1Initialised. Do not modify the contents of this structure directly.
typedef struct
{
    px_uint32        State[5];
    px_uint32        Count[2];
    px_byte         Buffer[64];
} PX_Sha1Context;

#define SHA1_HASH_SIZE           ( 160 / 8 )

typedef struct
{
    px_byte      bytes [SHA1_HASH_SIZE];
} PX_SHA1_HASH;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Sha1Calculate
//
//  Combines Sha1Initialise, Sha1Update, and Sha1Finalise into one function. Calculates the SHA1 hash of the buffer.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
px_void
PX_Sha1Calculate
(
    px_void  const        *Buffer,         // [in]
    px_uint32            BufferSize,     // [in]
    PX_SHA1_HASH          *Digest          // [in]
);
#endif