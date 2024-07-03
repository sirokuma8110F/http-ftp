/* { dg-do compile } */
/* { dg-options "-march=rv64gcv_zvfh_zvl4096b -mabi=lp64d -O3 -mrvv-max-lmul=m8" } */

#include "def.h"

DEF_EXTRACT (int8_t, v2qi, 0)
DEF_EXTRACT (int8_t, v4qi, 0)
DEF_EXTRACT (int8_t, v8qi, 0)
DEF_EXTRACT (int8_t, v16qi, 0)
DEF_EXTRACT (int8_t, v32qi, 0)
DEF_EXTRACT (int8_t, v64qi, 0)
DEF_EXTRACT (int8_t, v128qi, 0)
DEF_EXTRACT (int8_t, v256qi, 0)
DEF_EXTRACT (int8_t, v512qi, 0)
DEF_EXTRACT (int8_t, v1024qi, 0)
DEF_EXTRACT (int8_t, v2048qi, 0)
DEF_EXTRACT (int8_t, v4096qi, 0)
DEF_EXTRACT (int16_t, v2hi, 0)
DEF_EXTRACT (int16_t, v4hi, 0)
DEF_EXTRACT (int16_t, v8hi, 0)
DEF_EXTRACT (int16_t, v16hi, 0)
DEF_EXTRACT (int16_t, v32hi, 0)
DEF_EXTRACT (int16_t, v64hi, 0)
DEF_EXTRACT (int16_t, v128hi, 0)
DEF_EXTRACT (int16_t, v256hi, 0)
DEF_EXTRACT (int16_t, v512hi, 0)
DEF_EXTRACT (int16_t, v1024hi, 0)
DEF_EXTRACT (int16_t, v2048hi, 0)
DEF_EXTRACT (int32_t, v2si, 0)
DEF_EXTRACT (int32_t, v4si, 0)
DEF_EXTRACT (int32_t, v8si, 0)
DEF_EXTRACT (int32_t, v16si, 0)
DEF_EXTRACT (int32_t, v32si, 0);
DEF_EXTRACT (int32_t, v64si, 0);
DEF_EXTRACT (int32_t, v128si, 0)
DEF_EXTRACT (int32_t, v256si, 0)
DEF_EXTRACT (int32_t, v512si, 0)
DEF_EXTRACT (int32_t, v1024si, 0)
DEF_EXTRACT (int64_t, v2di, 0)
DEF_EXTRACT (int64_t, v4di, 0)
DEF_EXTRACT (int64_t, v8di, 0)
DEF_EXTRACT (int64_t, v16di, 0)
DEF_EXTRACT (int64_t, v32di, 0)
DEF_EXTRACT (int64_t, v64di, 0)
DEF_EXTRACT (int64_t, v128di, 0)
DEF_EXTRACT (int64_t, v256di, 0)
DEF_EXTRACT (int64_t, v512di, 0)
DEF_EXTRACT (uint8_t, v2uqi, 0)
DEF_EXTRACT (uint8_t, v4uqi, 0)
DEF_EXTRACT (uint8_t, v8uqi, 0)
DEF_EXTRACT (uint8_t, v16uqi, 0)
DEF_EXTRACT (uint8_t, v32uqi, 0)
DEF_EXTRACT (uint8_t, v64uqi, 0)
DEF_EXTRACT (uint8_t, v128uqi, 0)
DEF_EXTRACT (uint8_t, v256uqi, 0)
DEF_EXTRACT (uint8_t, v512uqi, 0)
DEF_EXTRACT (uint8_t, v1024uqi, 0)
DEF_EXTRACT (uint8_t, v2048uqi, 0)
DEF_EXTRACT (uint8_t, v4096uqi, 0)
DEF_EXTRACT (uint16_t, v2uhi, 0)
DEF_EXTRACT (uint16_t, v4uhi, 0)
DEF_EXTRACT (uint16_t, v8uhi, 0)
DEF_EXTRACT (uint16_t, v16uhi, 0)
DEF_EXTRACT (uint16_t, v32uhi, 0)
DEF_EXTRACT (uint16_t, v64uhi, 0)
DEF_EXTRACT (uint16_t, v128uhi, 0)
DEF_EXTRACT (uint16_t, v256uhi, 0)
DEF_EXTRACT (uint16_t, v512uhi, 0)
DEF_EXTRACT (uint16_t, v1024uhi, 0)
DEF_EXTRACT (uint16_t, v2048uhi, 0)
DEF_EXTRACT (uint32_t, v2usi, 0)
DEF_EXTRACT (uint32_t, v4usi, 0)
DEF_EXTRACT (uint32_t, v8usi, 0)
DEF_EXTRACT (uint32_t, v16usi, 0)
DEF_EXTRACT (uint32_t, v32usi, 0)
DEF_EXTRACT (uint32_t, v64usi, 0)
DEF_EXTRACT (uint32_t, v128usi, 0)
DEF_EXTRACT (uint32_t, v256usi, 0)
DEF_EXTRACT (uint32_t, v512usi, 0)
DEF_EXTRACT (uint32_t, v1024usi, 0)
DEF_EXTRACT (uint64_t, v2udi, 0)
DEF_EXTRACT (uint64_t, v4udi, 0)
DEF_EXTRACT (uint64_t, v8udi, 0)
DEF_EXTRACT (uint64_t, v16udi, 0)
DEF_EXTRACT (uint64_t, v32udi, 0)
DEF_EXTRACT (uint64_t, v64udi, 0)
DEF_EXTRACT (uint64_t, v128udi, 0)
DEF_EXTRACT (uint64_t, v256udi, 0)
DEF_EXTRACT (uint64_t, v512udi, 0)
DEF_EXTRACT (_Float16, v2hf, 0)
DEF_EXTRACT (_Float16, v4hf, 0)
DEF_EXTRACT (_Float16, v8hf, 0)
DEF_EXTRACT (_Float16, v16hf, 0)
DEF_EXTRACT (_Float16, v32hf, 0)
DEF_EXTRACT (_Float16, v64hf, 0)
DEF_EXTRACT (_Float16, v128hf, 0)
DEF_EXTRACT (_Float16, v256hf, 0)
DEF_EXTRACT (_Float16, v512hf, 0)
DEF_EXTRACT (_Float16, v1024hf, 0)
DEF_EXTRACT (_Float16, v2048hf, 0)
DEF_EXTRACT (float, v2sf, 0)
DEF_EXTRACT (float, v4sf, 0)
DEF_EXTRACT (float, v8sf, 0)
DEF_EXTRACT (float, v16sf, 0)
DEF_EXTRACT (float, v32sf, 0)
DEF_EXTRACT (float, v64sf, 0)
DEF_EXTRACT (float, v128sf, 0)
DEF_EXTRACT (float, v256sf, 0)
DEF_EXTRACT (float, v512sf, 0)
DEF_EXTRACT (float, v1024sf, 0)
DEF_EXTRACT (double, v2df, 0)
DEF_EXTRACT (double, v4df, 0)
DEF_EXTRACT (double, v8df, 0)
DEF_EXTRACT (double, v16df, 0)
DEF_EXTRACT (double, v32df, 0)
DEF_EXTRACT (double, v64df, 0)
DEF_EXTRACT (double, v128df, 0)
DEF_EXTRACT (double, v256df, 0)
DEF_EXTRACT (double, v512df, 0)

/* { dg-final { scan-assembler-times {vmv\.x\.s} 84 } } */
/* { dg-final { scan-assembler-times {vfmv\.f\.s} 30 } } */