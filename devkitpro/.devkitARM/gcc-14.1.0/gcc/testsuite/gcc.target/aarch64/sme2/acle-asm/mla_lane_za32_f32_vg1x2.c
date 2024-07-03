/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sme2_acle.h"

/*
** mla_lane_0_z0_z4_0:
**	mov	(w8|w9|w10|w11), #?0
**	fmla	za\.s\[\1, 0, vgx2\], {z0\.s - z1\.s}, z4\.s\[0\]
**	ret
*/
TEST_ZA_LANE (mla_lane_0_z0_z4_0, svfloat32x2_t, svfloat32_t,
	      svmla_lane_za32_f32_vg1x2 (0, z0, z4, 0),
	      svmla_lane_za32_vg1x2 (0, z0, z4, 0))

/*
** mla_lane_w0_z0_z7_1:
**	mov	(w8|w9|w10|w11), w0
**	fmla	za\.s\[\1, 0, vgx2\], {z0\.s - z1\.s}, z7\.s\[1\]
**	ret
*/
TEST_ZA_LANE (mla_lane_w0_z0_z7_1, svfloat32x2_t, svfloat32_t,
	      svmla_lane_za32_f32_vg1x2 (w0, z0, z7, 1),
	      svmla_lane_za32_vg1x2 (w0, z0, z7, 1))

/*
** mla_lane_w8_z28_z4_2:
**	fmla	za\.s\[w8, 0, vgx2\], {z28\.s - z29\.s}, z4\.s\[2\]
**	ret
*/
TEST_ZA_LANE (mla_lane_w8_z28_z4_2, svfloat32x2_t, svfloat32_t,
	      svmla_lane_za32_f32_vg1x2 (w8, z28, z4, 2),
	      svmla_lane_za32_vg1x2 (w8, z28, z4, 2))

/*
** mla_lane_w8p7_z0_z4_3:
**	fmla	za\.s\[w8, 7, vgx2\], {z0\.s - z1\.s}, z4\.s\[3\]
**	ret
*/
TEST_ZA_LANE (mla_lane_w8p7_z0_z4_3, svfloat32x2_t, svfloat32_t,
	      svmla_lane_za32_f32_vg1x2 (w8 + 7, z0, z4, 3),
	      svmla_lane_za32_vg1x2 (w8 + 7, z0, z4, 3))

/*
** mla_lane_w8p8_z0_z4_0:
**	add	(w8|w9|w10|w11), w8, #?8
**	fmla	za\.s\[\1, 0, vgx2\], {z0\.s - z1\.s}, z4\.s\[0\]
**	ret
*/
TEST_ZA_LANE (mla_lane_w8p8_z0_z4_0, svfloat32x2_t, svfloat32_t,
	      svmla_lane_za32_f32_vg1x2 (w8 + 8, z0, z4, 0),
	      svmla_lane_za32_vg1x2 (w8 + 8, z0, z4, 0))

/*
** mla_lane_w0m1_z0_z4_1:
**	sub	(w8|w9|w10|w11), w0, #?1
**	fmla	za\.s\[\1, 0, vgx2\], {z0\.s - z1\.s}, z4\.s\[1\]
**	ret
*/
TEST_ZA_LANE (mla_lane_w0m1_z0_z4_1, svfloat32x2_t, svfloat32_t,
	      svmla_lane_za32_f32_vg1x2 (w0 - 1, z0, z4, 1),
	      svmla_lane_za32_vg1x2 (w0 - 1, z0, z4, 1))

/*
** mla_lane_w8_z4_z15_2:
**	str	d15, \[sp, #?-16\]!
**	fmla	za\.s\[w8, 0, vgx2\], {z4\.s - z5\.s}, z15\.s\[2\]
**	ldr	d15, \[sp\], #?16
**	ret
*/
TEST_ZA_LANE_Z15 (mla_lane_w8_z4_z15_2, svfloat32x2_t, svfloat32_t,
		  svmla_lane_za32_f32_vg1x2 (w8, z4, z15, 2),
		  svmla_lane_za32_vg1x2 (w8, z4, z15, 2))

/*
** mla_lane_w8_z28_z16_3:
**	mov	(z[0-7]).d, z16.d
**	fmla	za\.s\[w8, 0, vgx2\], {z28\.s - z29\.s}, \1\.s\[3\]
**	ret
*/
TEST_ZA_LANE (mla_lane_w8_z28_z16_3, svfloat32x2_t, svfloat32_t,
	      svmla_lane_za32_f32_vg1x2 (w8, z28, z16, 3),
	      svmla_lane_za32_vg1x2 (w8, z28, z16, 3))

/*
** mla_lane_w8_z17_z7_0:
**	mov	[^\n]+
**	mov	[^\n]+
**	fmla	za\.s\[w8, 0, vgx2\], [^\n]+, z7\.s\[0\]
**	ret
*/
TEST_ZA_LANE (mla_lane_w8_z17_z7_0, svfloat32x2_t, svfloat32_t,
	      svmla_lane_za32_f32_vg1x2 (w8, z17, z7, 0),
	      svmla_lane_za32_vg1x2 (w8, z17, z7, 0))

/*
** mla_lane_w8_z22_z4_1:
**	fmla	za\.s\[w8, 0, vgx2\], {z22\.s - z23\.s}, z4\.s\[1\]
**	ret
*/
TEST_ZA_LANE (mla_lane_w8_z22_z4_1, svfloat32x2_t, svfloat32_t,
	      svmla_lane_za32_f32_vg1x2 (w8, z22, z4, 1),
	      svmla_lane_za32_vg1x2 (w8, z22, z4, 1))