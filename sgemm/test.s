	.text
	.file	"test.cpp"
	.globl	_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_ // -- Begin function _Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.p2align	2
	.type	_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_,@function
_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_: // @_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.cfi_startproc
// %bb.0:                               // %.lr.ph
	ldp	x8, x10, [x4]
	mov	w9, #12
	ldp	x12, x13, [x3]
	ldp	q21, q20, [x8, #32]
	madd	x9, x10, x9, x8
	add	x11, x8, x10, lsl #3
	add	x10, x8, x10, lsl #2
	add	x12, x12, #32
	lsl	x13, x13, #2
	ldp	q1, q0, [x9, #32]
	ldp	q4, q2, [x9]
	ldp	x15, x9, [x2]
	ldp	q5, q3, [x11, #32]
	mov	x14, x15
	ldp	q7, q6, [x11]
	add	x11, x9, x9, lsl #1
	lsl	x11, x11, #2
	ldp	q17, q16, [x10, #32]
	ldp	q19, q18, [x10]
	lsl	x10, x9, #3
	ldp	q23, q22, [x8]
.LBB0_1:                                // =>This Inner Loop Header: Depth=1
	ld1r	{ v24.4s }, [x14], #4
	ldp	q26, q27, [x12, #-32]
	subs	x1, x1, #1
	fmla	v23.4s, v24.4s, v26.4s
	ldp	q28, q29, [x12]
	fmla	v22.4s, v24.4s, v27.4s
	add	x12, x12, x13
	fmla	v21.4s, v24.4s, v28.4s
	ldr	s25, [x15, x9, lsl #2]
	fmla	v20.4s, v24.4s, v29.4s
	ldr	s30, [x15, x10]
	ldr	s24, [x15, x11]
	mov	x15, x14
	fmla	v19.4s, v26.4s, v25.s[0]
	fmla	v18.4s, v27.4s, v25.s[0]
	fmla	v17.4s, v28.4s, v25.s[0]
	fmla	v16.4s, v29.4s, v25.s[0]
	fmla	v7.4s, v26.4s, v30.s[0]
	fmla	v6.4s, v27.4s, v30.s[0]
	fmla	v5.4s, v28.4s, v30.s[0]
	fmla	v3.4s, v29.4s, v30.s[0]
	fmla	v4.4s, v26.4s, v24.s[0]
	fmla	v2.4s, v27.4s, v24.s[0]
	fmla	v1.4s, v28.4s, v24.s[0]
	fmla	v0.4s, v29.4s, v24.s[0]
	b.ne	.LBB0_1
// %bb.2:                               // %.preheader
	str	q23, [x8]
	mov	w10, #12
	ldr	x8, [x4, #16]
	ldr	x9, [x4]
	str	q22, [x9, x8, lsl #4]
	ldr	x8, [x4, #16]
	ldr	x9, [x4]
	lsl	x8, x8, #5
	str	q21, [x9, x8]
	mov	w9, #48
	ldr	x8, [x4, #16]
	mul	x8, x8, x9
	ldr	x9, [x4]
	str	q20, [x9, x8]
	ldp	x9, x8, [x4]
	lsl	x8, x8, #2
	str	q19, [x9, x8]
	ldp	x8, x9, [x4, #8]
	add	x8, x8, x9, lsl #2
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q18, [x9, x8]
	ldp	x8, x9, [x4, #8]
	add	x8, x8, x9, lsl #3
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q17, [x9, x8]
	ldp	x8, x9, [x4, #8]
	madd	x8, x9, x10, x8
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q16, [x9, x8]
	ldp	x9, x8, [x4]
	lsl	x8, x8, #3
	str	q7, [x9, x8]
	ldp	x9, x8, [x4, #8]
	lsl	x8, x8, #2
	add	x8, x8, x9, lsl #1
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q6, [x9, x8]
	ldp	x9, x8, [x4, #8]
	lsl	x8, x8, #3
	add	x8, x8, x9, lsl #1
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q5, [x9, x8]
	ldp	x9, x8, [x4, #8]
	mul	x8, x8, x10
	add	x8, x8, x9, lsl #1
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q3, [x9, x8]
	ldp	x9, x8, [x4]
	mul	x8, x8, x10
	str	q4, [x9, x8]
	ldp	x8, x9, [x4, #8]
	add	x8, x8, x8, lsl #1
	add	x8, x8, x9, lsl #2
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q2, [x9, x8]
	ldp	x8, x9, [x4, #8]
	add	x8, x8, x8, lsl #1
	add	x8, x8, x9, lsl #3
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q1, [x9, x8]
	ldp	x8, x9, [x4, #8]
	add	x8, x8, x8, lsl #1
	madd	x8, x9, x10, x8
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q0, [x9, x8]
	ret
.Lfunc_end0:
	.size	_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_, .Lfunc_end0-_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.cfi_endproc
                                        // -- End function
	.globl	_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_ // -- Begin function _Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_
	.p2align	2
	.type	_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_,@function
_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_: // @_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #128
	stp	x29, x30, [sp, #32]             // 16-byte Folded Spill
	stp	x28, x27, [sp, #48]             // 16-byte Folded Spill
	stp	x26, x25, [sp, #64]             // 16-byte Folded Spill
	stp	x24, x23, [sp, #80]             // 16-byte Folded Spill
	stp	x22, x21, [sp, #96]             // 16-byte Folded Spill
	stp	x20, x19, [sp, #112]            // 16-byte Folded Spill
	.cfi_def_cfa_offset 128
	.cfi_offset w19, -8
	.cfi_offset w20, -16
	.cfi_offset w21, -24
	.cfi_offset w22, -32
	.cfi_offset w23, -40
	.cfi_offset w24, -48
	.cfi_offset w25, -56
	.cfi_offset w26, -64
	.cfi_offset w27, -72
	.cfi_offset w28, -80
	.cfi_offset w30, -88
	.cfi_offset w29, -96
	mov	x17, x2
	lsr	x8, x1, #4
	cmp	x1, #16
	str	x1, [sp]                        // 8-byte Folded Spill
	str	x8, [sp, #16]                   // 8-byte Folded Spill
	b.lo	.LBB1_7
// %bb.1:                               // %.preheader98.us.preheader
	mov	x9, xzr
	mov	w11, #4
	mov	w12, #8
	mov	w14, #12
	str	xzr, [sp, #24]                  // 8-byte Folded Spill
.LBB1_2:                                // %.preheader98.us
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB1_3 Depth 2
                                        //       Child Loop BB1_4 Depth 3
	mov	x15, xzr
	mov	x16, xzr
	lsl	x8, x9, #2
	str	x9, [sp, #8]                    // 8-byte Folded Spill
.LBB1_3:                                //   Parent Loop BB1_2 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB1_4 Depth 3
	ldp	x13, x10, [x5, #8]
	mov	w9, #12
	ldr	x0, [x5]
	ldp	x1, x2, [x3]
	mul	x18, x13, x8
	mul	x10, x16, x10
	ldr	x28, [sp, #24]                  // 8-byte Folded Reload
	add	x10, x18, x10, lsl #4
	madd	x28, x28, x2, x1
	madd	x29, x11, x2, x1
	add	x18, x0, x10, lsl #2
	madd	x30, x12, x2, x1
	madd	x0, x13, x9, x18
	add	x6, x18, x13, lsl #3
	ldp	x9, x10, [x4, #8]
	add	x24, x18, x13, lsl #2
	mov	x20, x6
	ldr	x13, [x4]
	mov	x22, x6
	mov	x23, x6
	mov	x25, x24
	mov	x7, x0
	mov	x19, x0
	mov	x21, x0
	mov	x26, x24
	mov	x27, x24
	madd	x10, x10, x15, x13
	ldp	q21, q20, [x18, #32]
	madd	x1, x14, x2, x1
	add	x10, x10, #32
	lsl	x13, x9, #2
	mov	x2, x17
	ldp	q23, q22, [x18]
	ldr	q2, [x20, #48]!
	ldr	q4, [x22, #32]!
	ldr	q6, [x23, #16]!
	ldr	q0, [x7, #48]!
	ldr	q1, [x19, #32]!
	ldr	q3, [x21, #16]!
	ldr	q5, [x0]
	ldr	q7, [x6]
	ldr	q16, [x25, #48]!
	ldr	q17, [x26, #32]!
	ldr	q18, [x27, #16]!
	ldr	q19, [x24]
.LBB1_4:                                //   Parent Loop BB1_2 Depth=1
                                        //     Parent Loop BB1_3 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ld1r	{ v24.4s }, [x28], #4
	ld1r	{ v25.4s }, [x29], #4
	ld1r	{ v26.4s }, [x30], #4
	ld1r	{ v27.4s }, [x1], #4
	ldp	q28, q29, [x10, #-32]
	subs	x2, x2, #1
	fmla	v23.4s, v28.4s, v24.4s
	fmla	v19.4s, v28.4s, v25.4s
	fmla	v7.4s, v26.4s, v28.4s
	fmla	v5.4s, v27.4s, v28.4s
	ldp	q30, q31, [x10]
	fmla	v22.4s, v29.4s, v24.4s
	fmla	v18.4s, v29.4s, v25.4s
	fmla	v6.4s, v29.4s, v26.4s
	fmla	v3.4s, v27.4s, v29.4s
	add	x10, x10, x13
	fmla	v21.4s, v30.4s, v24.4s
	fmla	v17.4s, v30.4s, v25.4s
	fmla	v4.4s, v30.4s, v26.4s
	fmla	v1.4s, v30.4s, v27.4s
	fmla	v20.4s, v31.4s, v24.4s
	fmla	v16.4s, v31.4s, v25.4s
	fmla	v2.4s, v31.4s, v26.4s
	fmla	v0.4s, v31.4s, v27.4s
	b.ne	.LBB1_4
// %bb.5:                               // %_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_.exit.us
                                        //   in Loop: Header=BB1_3 Depth=2
	ldr	x9, [sp, #16]                   // 8-byte Folded Reload
	add	x16, x16, #1
	add	x15, x15, #64
	stp	q23, q22, [x18]
	stp	q21, q20, [x18, #32]
	cmp	x16, x9
	str	q19, [x24]
	str	q18, [x27]
	str	q17, [x26]
	str	q16, [x25]
	str	q7, [x6]
	str	q6, [x23]
	str	q4, [x22]
	str	q2, [x20]
	str	q5, [x0]
	str	q3, [x21]
	str	q1, [x19]
	str	q0, [x7]
	b.ne	.LBB1_3
// %bb.6:                               // %._crit_edge.us
                                        //   in Loop: Header=BB1_2 Depth=1
	ldr	x9, [sp, #8]                    // 8-byte Folded Reload
	add	x11, x11, #16
	ldr	x8, [sp, #24]                   // 8-byte Folded Reload
	add	x12, x12, #16
	add	x14, x14, #16
	add	x9, x9, #1
	add	x8, x8, #16
	cmp	x9, #16
	str	x8, [sp, #24]                   // 8-byte Folded Spill
	b.ne	.LBB1_2
.LBB1_7:                                // %.preheader97
	ldr	x12, [sp]                       // 8-byte Folded Reload
	ands	x9, x12, #0xf
	b.eq	.LBB1_26
// %bb.8:                               // %.preheader97.split123
	ldr	x8, [x4, #16]
	mov	x10, xzr
	ldr	x14, [sp, #16]                  // 8-byte Folded Reload
	and	x12, x12, #0x7ffffffffffffff0
	ldp	x16, x13, [x4]
	ldp	x11, x4, [x3]
	mul	x18, x8, x14
	lsl	x8, x8, #2
	ldr	x0, [x3, #16]
	ldp	x15, x2, [x5]
	add	x16, x16, x18, lsl #6
	lsl	x13, x13, #2
	lsl	x18, x0, #2
	ldr	x0, [x5, #16]
	add	x5, x4, x4, lsl #1
	lsl	x14, x4, #4
	lsl	x1, x4, #2
	lsl	x3, x4, #3
	lsl	x4, x5, #2
.LBB1_9:                                // %.preheader96
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB1_10 Depth 2
                                        //       Child Loop BB1_11 Depth 3
                                        //     Child Loop BB1_14 Depth 2
                                        //       Child Loop BB1_15 Depth 3
                                        //     Child Loop BB1_18 Depth 2
                                        //       Child Loop BB1_19 Depth 3
                                        //     Child Loop BB1_22 Depth 2
                                        //       Child Loop BB1_23 Depth 3
	lsl	x5, x10, #2
	mov	x6, xzr
	mov	x19, x16
	mul	x7, x2, x5
.LBB1_10:                               // %.preheader
                                        //   Parent Loop BB1_9 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB1_11 Depth 3
	add	x20, x6, x12
	mov	x21, x17
	mov	x22, x11
	mov	x23, x19
	madd	x20, x0, x20, x7
	ldr	s0, [x15, x20, lsl #2]
.LBB1_11:                               //   Parent Loop BB1_9 Depth=1
                                        //     Parent Loop BB1_10 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x22]
	add	x22, x22, x18
	ldr	s2, [x23]
	add	x23, x23, x13
	subs	x21, x21, #1
	fmadd	s0, s2, s1, s0
	str	s0, [x15, x20, lsl #2]
	b.ne	.LBB1_11
// %bb.12:                              // %._crit_edge
                                        //   in Loop: Header=BB1_10 Depth=2
	add	x6, x6, #1
	add	x19, x19, x8
	cmp	x6, x9
	b.ne	.LBB1_10
// %bb.13:                              // %._crit_edge119
                                        //   in Loop: Header=BB1_9 Depth=1
	orr	x7, x5, #0x1
	mov	x6, xzr
	mov	x19, x16
	mul	x7, x2, x7
.LBB1_14:                               // %.preheader.1
                                        //   Parent Loop BB1_9 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB1_15 Depth 3
	add	x20, x6, x12
	mov	x21, x1
	mov	x22, x19
	mov	x23, x17
	madd	x20, x0, x20, x7
	ldr	s0, [x15, x20, lsl #2]
.LBB1_15:                               //   Parent Loop BB1_9 Depth=1
                                        //     Parent Loop BB1_14 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x11, x21]
	subs	x23, x23, #1
	ldr	s2, [x22]
	add	x22, x22, x13
	add	x21, x21, x18
	fmadd	s0, s2, s1, s0
	str	s0, [x15, x20, lsl #2]
	b.ne	.LBB1_15
// %bb.16:                              // %._crit_edge.1
                                        //   in Loop: Header=BB1_14 Depth=2
	add	x6, x6, #1
	add	x19, x19, x8
	cmp	x6, x9
	b.ne	.LBB1_14
// %bb.17:                              // %._crit_edge119.1
                                        //   in Loop: Header=BB1_9 Depth=1
	orr	x7, x5, #0x2
	mov	x6, xzr
	mov	x19, x16
	mul	x7, x2, x7
.LBB1_18:                               // %.preheader.2
                                        //   Parent Loop BB1_9 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB1_19 Depth 3
	add	x20, x6, x12
	mov	x21, x3
	mov	x22, x19
	mov	x23, x17
	madd	x20, x0, x20, x7
	ldr	s0, [x15, x20, lsl #2]
.LBB1_19:                               //   Parent Loop BB1_9 Depth=1
                                        //     Parent Loop BB1_18 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x11, x21]
	subs	x23, x23, #1
	ldr	s2, [x22]
	add	x22, x22, x13
	add	x21, x21, x18
	fmadd	s0, s2, s1, s0
	str	s0, [x15, x20, lsl #2]
	b.ne	.LBB1_19
// %bb.20:                              // %._crit_edge.2
                                        //   in Loop: Header=BB1_18 Depth=2
	add	x6, x6, #1
	add	x19, x19, x8
	cmp	x6, x9
	b.ne	.LBB1_18
// %bb.21:                              // %._crit_edge119.2
                                        //   in Loop: Header=BB1_9 Depth=1
	orr	x5, x5, #0x3
	mov	x6, xzr
	mov	x7, x16
	mul	x5, x2, x5
.LBB1_22:                               // %.preheader.3
                                        //   Parent Loop BB1_9 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB1_23 Depth 3
	add	x19, x6, x12
	mov	x20, x4
	mov	x21, x7
	mov	x22, x17
	madd	x19, x0, x19, x5
	ldr	s0, [x15, x19, lsl #2]
.LBB1_23:                               //   Parent Loop BB1_9 Depth=1
                                        //     Parent Loop BB1_22 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x11, x20]
	subs	x22, x22, #1
	ldr	s2, [x21]
	add	x21, x21, x13
	add	x20, x20, x18
	fmadd	s0, s2, s1, s0
	str	s0, [x15, x19, lsl #2]
	b.ne	.LBB1_23
// %bb.24:                              // %._crit_edge.3
                                        //   in Loop: Header=BB1_22 Depth=2
	add	x6, x6, #1
	add	x7, x7, x8
	cmp	x6, x9
	b.ne	.LBB1_22
// %bb.25:                              // %._crit_edge119.3
                                        //   in Loop: Header=BB1_9 Depth=1
	add	x10, x10, #1
	add	x11, x11, x14
	cmp	x10, #16
	b.ne	.LBB1_9
.LBB1_26:                               // %.split125.us
	ldp	x20, x19, [sp, #112]            // 16-byte Folded Reload
	ldp	x22, x21, [sp, #96]             // 16-byte Folded Reload
	ldp	x24, x23, [sp, #80]             // 16-byte Folded Reload
	ldp	x26, x25, [sp, #64]             // 16-byte Folded Reload
	ldp	x28, x27, [sp, #48]             // 16-byte Folded Reload
	ldp	x29, x30, [sp, #32]             // 16-byte Folded Reload
	add	sp, sp, #128
	ret
.Lfunc_end1:
	.size	_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_, .Lfunc_end1-_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_
	.cfi_endproc
                                        // -- End function
	.globl	_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_ // -- Begin function _Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_
	.p2align	2
	.type	_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_,@function
_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_: // @_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #176
	stp	x29, x30, [sp, #80]             // 16-byte Folded Spill
	add	x29, sp, #80
	str	x27, [sp, #96]                  // 8-byte Folded Spill
	stp	x26, x25, [sp, #112]            // 16-byte Folded Spill
	stp	x24, x23, [sp, #128]            // 16-byte Folded Spill
	stp	x22, x21, [sp, #144]            // 16-byte Folded Spill
	stp	x20, x19, [sp, #160]            // 16-byte Folded Spill
	.cfi_def_cfa w29, 96
	.cfi_offset w19, -8
	.cfi_offset w20, -16
	.cfi_offset w21, -24
	.cfi_offset w22, -32
	.cfi_offset w23, -40
	.cfi_offset w24, -48
	.cfi_offset w25, -56
	.cfi_offset w26, -64
	.cfi_offset w27, -80
	.cfi_offset w30, -88
	.cfi_offset w29, -96
	mov	x21, x6
	mov	x22, x5
	mov	x23, x1
	mov	x24, x4
	mov	x19, x3
	mov	x20, x2
	lsr	x25, x1, #6
	cmp	x1, #64
	b.hs	.LBB2_9
.LBB2_1:                                // %._crit_edge
	ands	x8, x23, #0x3f
	b.eq	.LBB2_8
// %bb.2:                               // %.preheader43.lr.ph
	ldp	x14, x17, [x24]
	mov	x9, xzr
	and	x11, x23, #0x7fffffffffffffc0
	ldp	x16, x12, [x22, #8]
	ldr	x18, [x24, #16]
	mul	x15, x17, x25
	ldr	x10, [x22]
	lsl	x16, x16, #2
	lsl	x17, x17, #2
	lsl	x12, x12, #2
	lsl	x18, x18, #2
	add	x14, x14, x15, lsl #8
	ldr	x0, [x21, #16]
	ldp	x13, x15, [x21]
.LBB2_3:                                // %.preheader43
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB2_4 Depth 2
                                        //       Child Loop BB2_5 Depth 3
	add	x2, x9, x11
	mov	x1, xzr
	mov	x3, x10
	mul	x2, x15, x2
.LBB2_4:                                // %.preheader
                                        //   Parent Loop BB2_3 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB2_5 Depth 3
	madd	x4, x0, x1, x2
	mov	x5, x19
	mov	x6, x14
	mov	x7, x3
	ldr	s0, [x13, x4, lsl #2]
.LBB2_5:                                //   Parent Loop BB2_3 Depth=1
                                        //     Parent Loop BB2_4 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x6]
	add	x6, x6, x18
	ldr	s2, [x7]
	add	x7, x7, x16
	subs	x5, x5, #1
	fmadd	s0, s2, s1, s0
	str	s0, [x13, x4, lsl #2]
	b.ne	.LBB2_5
// %bb.6:                               // %._crit_edge48
                                        //   in Loop: Header=BB2_4 Depth=2
	add	x1, x1, #1
	add	x3, x3, x12
	cmp	x1, x20
	b.ne	.LBB2_4
// %bb.7:                               // %._crit_edge50
                                        //   in Loop: Header=BB2_3 Depth=1
	add	x9, x9, #1
	add	x14, x14, x17
	cmp	x9, x8
	b.ne	.LBB2_3
.LBB2_8:                                // %.loopexit
	ldp	x20, x19, [sp, #160]            // 16-byte Folded Reload
	ldp	x22, x21, [sp, #144]            // 16-byte Folded Reload
	ldp	x24, x23, [sp, #128]            // 16-byte Folded Reload
	ldp	x26, x25, [sp, #112]            // 16-byte Folded Reload
	ldp	x29, x30, [sp, #80]             // 16-byte Folded Reload
	ldr	x27, [sp, #96]                  // 8-byte Folded Reload
	add	sp, sp, #176
	ret
.LBB2_9:                                // %.lr.ph
	mov	x26, xzr
	sub	x27, x25, #1
	mov	w8, #1
	mov	w9, #1
	mov	w10, #1
.LBB2_10:                               // =>This Inner Loop Header: Depth=1
	ldp	x12, x11, [x24]
	and	x13, x26, #0xffffffc0
	sub	x3, x29, #24
	ldp	x15, x14, [x21]
	add	x4, sp, #32
	add	x5, sp, #8
	mov	x1, x20
	mov	x2, x19
	stp	x11, x10, [x29, #-16]
	mul	x16, x11, x13
	ldp	x10, x17, [x22]
	mul	x13, x14, x13
	stp	x8, x10, [sp, #24]
	add	x10, x15, x13, lsl #2
	stp	x17, x9, [sp, #40]
	add	x9, x12, x16, lsl #2
	stp	x10, x14, [sp, #8]
	stur	x9, [x29, #-24]
	bl	_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_
	cbz	x27, .LBB2_1
// %bb.11:                              // %._crit_edge65
                                        //   in Loop: Header=BB2_10 Depth=1
	ldr	x10, [x24, #16]
	add	x26, x26, #64
	ldr	x9, [x22, #16]
	sub	x27, x27, #1
	ldr	x8, [x21, #16]
	b	.LBB2_10
.Lfunc_end2:
	.size	_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_, .Lfunc_end2-_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_
	.cfi_endproc
                                        // -- End function
	.globl	_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_ // -- Begin function _Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_
	.p2align	2
	.type	_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_,@function
_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_: // @_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_
	.cfi_startproc
// %bb.0:                               // %.preheader82
	ldp	x8, x10, [x3]
	mov	w12, #12
	mov	x9, xzr
	ldp	x14, x15, [x2]
	ldp	q21, q20, [x8]
	add	x11, x8, x10, lsl #2
	add	x13, x8, x10, lsl #3
	add	x14, x14, #32
	lsl	x15, x15, #2
	ldp	q19, q18, [x11]
	ldp	q17, q7, [x11, #32]
	madd	x11, x10, x12, x8
	ldp	q16, q6, [x13]
	ldp	q5, q4, [x13, #32]
	ldp	x10, x13, [x1]
	ldp	q3, q2, [x11]
	madd	x12, x13, x12, x10
	ldp	q1, q0, [x11, #32]
	add	x11, x10, x13, lsl #2
	add	x13, x10, x13, lsl #3
	ldp	q23, q22, [x8, #32]
.LBB3_1:                                // %.preheader79.preheader
                                        // =>This Inner Loop Header: Depth=1
	ldp	q26, q27, [x14, #-32]
	ldp	q28, q29, [x14]
	add	x14, x14, x15
	ldr	s24, [x10, x9]
	ldr	s25, [x11, x9]
	ldr	s30, [x13, x9]
	fmla	v21.4s, v26.4s, v24.s[0]
	fmla	v20.4s, v27.4s, v24.s[0]
	fmla	v23.4s, v28.4s, v24.s[0]
	fmla	v22.4s, v29.4s, v24.s[0]
	ldr	s24, [x12, x9]
	fmla	v19.4s, v26.4s, v25.s[0]
	fmla	v18.4s, v27.4s, v25.s[0]
	fmla	v17.4s, v28.4s, v25.s[0]
	fmla	v7.4s, v29.4s, v25.s[0]
	fmla	v16.4s, v26.4s, v30.s[0]
	fmla	v6.4s, v27.4s, v30.s[0]
	fmla	v5.4s, v28.4s, v30.s[0]
	fmla	v4.4s, v29.4s, v30.s[0]
	fmla	v3.4s, v26.4s, v24.s[0]
	fmla	v2.4s, v27.4s, v24.s[0]
	fmla	v1.4s, v28.4s, v24.s[0]
	fmla	v0.4s, v29.4s, v24.s[0]
	add	x9, x9, #4
	cmp	x9, #256
	b.ne	.LBB3_1
// %bb.2:                               // %.preheader78
	str	q21, [x8]
	mov	w10, #12
	ldr	x8, [x3, #16]
	ldr	x9, [x3]
	str	q20, [x9, x8, lsl #4]
	ldr	x8, [x3, #16]
	ldr	x9, [x3]
	lsl	x8, x8, #5
	str	q23, [x9, x8]
	mov	w9, #48
	ldr	x8, [x3, #16]
	mul	x8, x8, x9
	ldr	x9, [x3]
	str	q22, [x9, x8]
	ldp	x9, x8, [x3]
	lsl	x8, x8, #2
	str	q19, [x9, x8]
	ldp	x8, x9, [x3, #8]
	add	x8, x8, x9, lsl #2
	ldr	x9, [x3]
	lsl	x8, x8, #2
	str	q18, [x9, x8]
	ldp	x8, x9, [x3, #8]
	add	x8, x8, x9, lsl #3
	ldr	x9, [x3]
	lsl	x8, x8, #2
	str	q17, [x9, x8]
	ldp	x8, x9, [x3, #8]
	madd	x8, x9, x10, x8
	ldr	x9, [x3]
	lsl	x8, x8, #2
	str	q7, [x9, x8]
	ldp	x9, x8, [x3]
	lsl	x8, x8, #3
	str	q16, [x9, x8]
	ldp	x9, x8, [x3, #8]
	lsl	x8, x8, #2
	add	x8, x8, x9, lsl #1
	ldr	x9, [x3]
	lsl	x8, x8, #2
	str	q6, [x9, x8]
	ldp	x9, x8, [x3, #8]
	lsl	x8, x8, #3
	add	x8, x8, x9, lsl #1
	ldr	x9, [x3]
	lsl	x8, x8, #2
	str	q5, [x9, x8]
	ldp	x9, x8, [x3, #8]
	mul	x8, x8, x10
	add	x8, x8, x9, lsl #1
	ldr	x9, [x3]
	lsl	x8, x8, #2
	str	q4, [x9, x8]
	ldp	x9, x8, [x3]
	mul	x8, x8, x10
	str	q3, [x9, x8]
	ldp	x8, x9, [x3, #8]
	add	x8, x8, x8, lsl #1
	add	x8, x8, x9, lsl #2
	ldr	x9, [x3]
	lsl	x8, x8, #2
	str	q2, [x9, x8]
	ldp	x8, x9, [x3, #8]
	add	x8, x8, x8, lsl #1
	add	x8, x8, x9, lsl #3
	ldr	x9, [x3]
	lsl	x8, x8, #2
	str	q1, [x9, x8]
	ldp	x8, x9, [x3, #8]
	add	x8, x8, x8, lsl #1
	madd	x8, x9, x10, x8
	ldr	x9, [x3]
	lsl	x8, x8, #2
	str	q0, [x9, x8]
	ret
.Lfunc_end3:
	.size	_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_, .Lfunc_end3-_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_
	.cfi_endproc
                                        // -- End function
	.globl	_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_ // -- Begin function _Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.p2align	2
	.type	_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_,@function
_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_: // @_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #144
	stp	x29, x30, [sp, #48]             // 16-byte Folded Spill
	add	x29, sp, #48
	stp	x28, x27, [sp, #64]             // 16-byte Folded Spill
	stp	x26, x25, [sp, #80]             // 16-byte Folded Spill
	stp	x24, x23, [sp, #96]             // 16-byte Folded Spill
	stp	x22, x21, [sp, #112]            // 16-byte Folded Spill
	stp	x20, x19, [sp, #128]            // 16-byte Folded Spill
	.cfi_def_cfa w29, 96
	.cfi_offset w19, -8
	.cfi_offset w20, -16
	.cfi_offset w21, -24
	.cfi_offset w22, -32
	.cfi_offset w23, -40
	.cfi_offset w24, -48
	.cfi_offset w25, -56
	.cfi_offset w26, -64
	.cfi_offset w27, -72
	.cfi_offset w28, -80
	.cfi_offset w30, -88
	.cfi_offset w29, -96
	mov	x19, x4
	mov	x22, x3
	mov	x20, x2
	lsr	x8, x1, #4
	cmp	x1, #16
	str	x1, [sp, #8]                    // 8-byte Folded Spill
	str	x8, [sp, #24]                   // 8-byte Folded Spill
	b.hs	.LBB4_21
.LBB4_1:                                // %.preheader113
	ldr	x11, [sp, #8]                   // 8-byte Folded Reload
	ands	x8, x11, #0xf
	b.eq	.LBB4_20
// %bb.2:                               // %.preheader113.split
	ldr	x12, [x22, #16]
	mov	x9, xzr
	ldr	x14, [sp, #24]                  // 8-byte Folded Reload
	and	x11, x11, #0x7ffffffffffffff0
	ldp	x16, x13, [x22]
	ldp	x10, x2, [x20]
	mul	x17, x12, x14
	lsl	x12, x12, #2
	ldr	x18, [x20, #16]
	lsl	x13, x13, #2
	ldr	x0, [x19, #16]
	add	x16, x16, x17, lsl #6
	ldp	x15, x17, [x19]
	add	x3, x2, x2, lsl #1
	lsl	x14, x2, #4
	lsl	x18, x18, #2
	lsl	x1, x2, #2
	lsl	x2, x2, #3
	lsl	x3, x3, #2
.LBB4_3:                                // %.preheader112
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB4_4 Depth 2
                                        //       Child Loop BB4_5 Depth 3
                                        //     Child Loop BB4_8 Depth 2
                                        //       Child Loop BB4_9 Depth 3
                                        //     Child Loop BB4_12 Depth 2
                                        //       Child Loop BB4_13 Depth 3
                                        //     Child Loop BB4_16 Depth 2
                                        //       Child Loop BB4_17 Depth 3
	lsl	x4, x9, #2
	mov	x5, xzr
	mov	x7, x16
	mul	x6, x17, x4
.LBB4_4:                                // %.preheader
                                        //   Parent Loop BB4_3 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB4_5 Depth 3
	add	x19, x5, x11
	mov	w20, #64
	mov	x21, x10
	mov	x22, x7
	madd	x19, x0, x19, x6
	ldr	s0, [x15, x19, lsl #2]
.LBB4_5:                                //   Parent Loop BB4_3 Depth=1
                                        //     Parent Loop BB4_4 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x21]
	add	x21, x21, x18
	ldr	s2, [x22]
	add	x22, x22, x13
	subs	x20, x20, #1
	fmadd	s0, s2, s1, s0
	str	s0, [x15, x19, lsl #2]
	b.ne	.LBB4_5
// %bb.6:                               //   in Loop: Header=BB4_4 Depth=2
	add	x5, x5, #1
	add	x7, x7, x12
	cmp	x5, x8
	b.ne	.LBB4_4
// %bb.7:                               // %..loopexit_crit_edge
                                        //   in Loop: Header=BB4_3 Depth=1
	orr	x6, x4, #0x1
	mov	x5, xzr
	mov	x7, x16
	mul	x6, x17, x6
.LBB4_8:                                // %.preheader.1
                                        //   Parent Loop BB4_3 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB4_9 Depth 3
	add	x19, x5, x11
	mov	x20, x1
	mov	x21, x7
	mov	w22, #64
	madd	x19, x0, x19, x6
	ldr	s0, [x15, x19, lsl #2]
.LBB4_9:                                //   Parent Loop BB4_3 Depth=1
                                        //     Parent Loop BB4_8 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x10, x20]
	subs	x22, x22, #1
	ldr	s2, [x21]
	add	x21, x21, x13
	add	x20, x20, x18
	fmadd	s0, s2, s1, s0
	str	s0, [x15, x19, lsl #2]
	b.ne	.LBB4_9
// %bb.10:                              //   in Loop: Header=BB4_8 Depth=2
	add	x5, x5, #1
	add	x7, x7, x12
	cmp	x5, x8
	b.ne	.LBB4_8
// %bb.11:                              // %..loopexit_crit_edge.1
                                        //   in Loop: Header=BB4_3 Depth=1
	orr	x6, x4, #0x2
	mov	x5, xzr
	mov	x7, x16
	mul	x6, x17, x6
.LBB4_12:                               // %.preheader.2
                                        //   Parent Loop BB4_3 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB4_13 Depth 3
	add	x19, x5, x11
	mov	x20, x2
	mov	x21, x7
	mov	w22, #64
	madd	x19, x0, x19, x6
	ldr	s0, [x15, x19, lsl #2]
.LBB4_13:                               //   Parent Loop BB4_3 Depth=1
                                        //     Parent Loop BB4_12 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x10, x20]
	subs	x22, x22, #1
	ldr	s2, [x21]
	add	x21, x21, x13
	add	x20, x20, x18
	fmadd	s0, s2, s1, s0
	str	s0, [x15, x19, lsl #2]
	b.ne	.LBB4_13
// %bb.14:                              //   in Loop: Header=BB4_12 Depth=2
	add	x5, x5, #1
	add	x7, x7, x12
	cmp	x5, x8
	b.ne	.LBB4_12
// %bb.15:                              // %..loopexit_crit_edge.2
                                        //   in Loop: Header=BB4_3 Depth=1
	orr	x4, x4, #0x3
	mov	x5, xzr
	mov	x6, x16
	mul	x4, x17, x4
.LBB4_16:                               // %.preheader.3
                                        //   Parent Loop BB4_3 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB4_17 Depth 3
	add	x7, x5, x11
	mov	x19, x3
	mov	x20, x6
	mov	w21, #64
	madd	x7, x0, x7, x4
	ldr	s0, [x15, x7, lsl #2]
.LBB4_17:                               //   Parent Loop BB4_3 Depth=1
                                        //     Parent Loop BB4_16 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x10, x19]
	subs	x21, x21, #1
	ldr	s2, [x20]
	add	x20, x20, x13
	add	x19, x19, x18
	fmadd	s0, s2, s1, s0
	str	s0, [x15, x7, lsl #2]
	b.ne	.LBB4_17
// %bb.18:                              //   in Loop: Header=BB4_16 Depth=2
	add	x5, x5, #1
	add	x6, x6, x12
	cmp	x5, x8
	b.ne	.LBB4_16
// %bb.19:                              // %..loopexit_crit_edge.3
                                        //   in Loop: Header=BB4_3 Depth=1
	add	x9, x9, #1
	add	x10, x10, x14
	cmp	x9, #16
	b.ne	.LBB4_3
.LBB4_20:                               // %.split141.us
	ldp	x20, x19, [sp, #128]            // 16-byte Folded Reload
	ldp	x22, x21, [sp, #112]            // 16-byte Folded Reload
	ldp	x24, x23, [sp, #96]             // 16-byte Folded Reload
	ldp	x26, x25, [sp, #80]             // 16-byte Folded Reload
	ldp	x28, x27, [sp, #64]             // 16-byte Folded Reload
	ldp	x29, x30, [sp, #48]             // 16-byte Folded Reload
	add	sp, sp, #144
	ret
.LBB4_21:                               // %.lr.ph
	mov	x23, xzr
	mov	x24, xzr
	mov	w21, #1
	mov	w26, #12
	str	x22, [sp, #16]                  // 8-byte Folded Spill
.LBB4_22:                               // =>This Loop Header: Depth=1
                                        //     Child Loop BB4_23 Depth 2
                                        //     Child Loop BB4_25 Depth 2
                                        //       Child Loop BB4_26 Depth 3
	mov	w0, #4096
	bl	malloc
	ldp	x10, x11, [x22]
	mov	x9, xzr
	lsl	x8, x24, #4
	lsl	x12, x21, #2
	stp	x23, x24, [x29, #-16]           // 16-byte Folded Spill
	madd	x10, x21, x23, x10
	lsl	x11, x11, #2
.LBB4_23:                               // %.preheader114
                                        //   Parent Loop BB4_22 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	add	x14, x10, x12
	ldr	s1, [x10, x12]
	add	x15, x14, x12
	ldr	s0, [x10]
	ldr	s2, [x14, x12]
	add	x14, x15, x12
	add	x13, x0, x9
	ldr	s3, [x15, x12]
	add	x15, x14, x12
	ldr	s4, [x14, x12]
	add	x14, x15, x12
	add	x9, x9, #64
	stp	s0, s1, [x13]
	ldr	s0, [x15, x12]
	ldr	s1, [x14, x12]
	add	x14, x14, x12
	stp	s2, s3, [x13, #8]
	add	x10, x10, x11
	cmp	x9, #1, lsl #12                 // =4096
	stp	s4, s0, [x13, #16]
	str	s1, [x13, #24]
	ldr	s0, [x14, x12]
	add	x14, x14, x12
	str	s0, [x13, #28]
	ldr	s0, [x14, x12]
	add	x14, x14, x12
	str	s0, [x13, #32]
	ldr	s0, [x14, x12]
	add	x14, x14, x12
	str	s0, [x13, #36]
	ldr	s0, [x14, x12]
	add	x14, x14, x12
	str	s0, [x13, #40]
	ldr	s0, [x14, x12]
	add	x14, x14, x12
	str	s0, [x13, #44]
	ldr	s0, [x14, x12]
	add	x14, x14, x12
	str	s0, [x13, #48]
	ldr	s0, [x14, x12]
	add	x14, x14, x12
	str	s0, [x13, #52]
	ldr	s0, [x14, x12]
	add	x14, x14, x12
	str	s0, [x13, #56]
	ldr	s0, [x14, x12]
	str	s0, [x13, #60]
	b.ne	.LBB4_23
// %bb.24:                              // %.preheader115.preheader
                                        //   in Loop: Header=BB4_22 Depth=1
	mov	x9, xzr
	mov	x10, xzr
	add	x25, x0, #32
	mov	w12, #8
	mov	w13, #12
	mov	w14, #4
.LBB4_25:                               // %.preheader115
                                        //   Parent Loop BB4_22 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB4_26 Depth 3
	ldp	x11, x16, [x19, #8]
	mov	x15, xzr
	ldr	x18, [x19]
	mul	x17, x10, x11
	mul	x16, x16, x8
	add	x16, x16, x17, lsl #2
	add	x16, x18, x16, lsl #2
	add	x17, x16, x11, lsl #2
	add	x18, x16, x11, lsl #3
	madd	x1, x11, x26, x16
	mov	x30, x17
	ldp	x11, x22, [x20]
	mov	x28, x17
	mov	x27, x17
	mov	x7, x18
	mov	x6, x18
	mov	x5, x18
	mov	x4, x1
	mov	x2, x1
	mov	x3, x1
	ldp	q19, q18, [x16]
	madd	x21, x22, x9, x11
	madd	x23, x22, x14, x11
	madd	x24, x22, x13, x11
	madd	x22, x22, x12, x11
	mov	x11, x25
	ldp	q23, q21, [x16, #32]
	ldr	q16, [x30, #16]!
	ldr	q7, [x28, #32]!
	ldr	q6, [x27, #48]!
	ldr	q5, [x7, #16]!
	ldr	q4, [x6, #32]!
	ldr	q2, [x5, #48]!
	ldr	q3, [x4, #16]!
	ldr	q1, [x2, #32]!
	ldr	q0, [x3, #48]!
	ldr	q22, [x17]
	ldr	q20, [x18]
	ldr	q17, [x1]
.LBB4_26:                               // %.preheader79.preheader.i
                                        //   Parent Loop BB4_22 Depth=1
                                        //     Parent Loop BB4_25 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldp	q26, q27, [x11, #-32]
	ldp	q28, q29, [x11], #64
	ldr	s24, [x21, x15]
	ldr	s25, [x23, x15]
	ldr	s30, [x22, x15]
	fmla	v19.4s, v26.4s, v24.s[0]
	fmla	v18.4s, v27.4s, v24.s[0]
	fmla	v23.4s, v28.4s, v24.s[0]
	fmla	v21.4s, v29.4s, v24.s[0]
	ldr	s24, [x24, x15]
	fmla	v22.4s, v26.4s, v25.s[0]
	fmla	v16.4s, v27.4s, v25.s[0]
	fmla	v7.4s, v28.4s, v25.s[0]
	fmla	v6.4s, v29.4s, v25.s[0]
	fmla	v20.4s, v26.4s, v30.s[0]
	fmla	v5.4s, v27.4s, v30.s[0]
	fmla	v4.4s, v28.4s, v30.s[0]
	fmla	v2.4s, v29.4s, v30.s[0]
	fmla	v17.4s, v26.4s, v24.s[0]
	fmla	v3.4s, v27.4s, v24.s[0]
	fmla	v1.4s, v28.4s, v24.s[0]
	fmla	v0.4s, v29.4s, v24.s[0]
	add	x15, x15, #4
	cmp	x15, #256
	b.ne	.LBB4_26
// %bb.27:                              // %_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_.exit
                                        //   in Loop: Header=BB4_25 Depth=2
	add	x10, x10, #1
	add	x9, x9, #16
	add	x14, x14, #16
	add	x13, x13, #16
	add	x12, x12, #16
	cmp	x10, #16
	stp	q19, q18, [x16]
	stp	q23, q21, [x16, #32]
	str	q22, [x17]
	str	q16, [x30]
	str	q7, [x28]
	str	q6, [x27]
	str	q20, [x18]
	str	q5, [x7]
	str	q4, [x6]
	str	q2, [x5]
	str	q17, [x1]
	str	q3, [x4]
	str	q1, [x2]
	str	q0, [x3]
	b.ne	.LBB4_25
// %bb.28:                              //   in Loop: Header=BB4_22 Depth=1
	bl	free
	ldur	x24, [x29, #-8]                 // 8-byte Folded Reload
	ldp	x22, x8, [sp, #16]              // 16-byte Folded Reload
	add	x24, x24, #1
	cmp	x24, x8
	b.eq	.LBB4_1
// %bb.29:                              // %._crit_edge
                                        //   in Loop: Header=BB4_22 Depth=1
	ldur	x23, [x29, #-16]                // 8-byte Folded Reload
	ldr	x21, [x22, #16]
	add	x23, x23, #64
	b	.LBB4_22
.Lfunc_end4:
	.size	_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_, .Lfunc_end4-_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.cfi_endproc
                                        // -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4                               // -- Begin function _Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_
.LCPI5_0:
	.xword	64                              // 0x40
	.xword	1                               // 0x1
	.text
	.globl	_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_
	.p2align	2
	.type	_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_,@function
_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_: // @_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #272
	stp	x29, x30, [sp, #176]            // 16-byte Folded Spill
	add	x29, sp, #176
	stp	x28, x27, [sp, #192]            // 16-byte Folded Spill
	stp	x26, x25, [sp, #208]            // 16-byte Folded Spill
	stp	x24, x23, [sp, #224]            // 16-byte Folded Spill
	stp	x22, x21, [sp, #240]            // 16-byte Folded Spill
	stp	x20, x19, [sp, #256]            // 16-byte Folded Spill
	.cfi_def_cfa w29, 96
	.cfi_offset w19, -8
	.cfi_offset w20, -16
	.cfi_offset w21, -24
	.cfi_offset w22, -32
	.cfi_offset w23, -40
	.cfi_offset w24, -48
	.cfi_offset w25, -56
	.cfi_offset w26, -64
	.cfi_offset w27, -72
	.cfi_offset w28, -80
	.cfi_offset w30, -88
	.cfi_offset w29, -96
	mov	x19, x2
	lsr	x8, x1, #6
	cmp	x1, #64
	stp	x4, x5, [sp, #48]               // 16-byte Folded Spill
	str	x1, [sp, #8]                    // 8-byte Folded Spill
	str	x8, [sp, #40]                   // 8-byte Folded Spill
	b.hs	.LBB5_9
.LBB5_1:                                // %._crit_edge
	ldr	x11, [sp, #8]                   // 8-byte Folded Reload
	ands	x8, x11, #0x3f
	b.eq	.LBB5_8
// %bb.2:                               // %.preheader53.lr.ph
	ldp	x14, x17, [x3]
	mov	x9, xzr
	and	x11, x11, #0x7fffffffffffffc0
	ldp	x10, x13, [sp, #40]             // 16-byte Folded Reload
	ldr	x0, [sp, #56]                   // 8-byte Folded Reload
	ldr	x18, [x3, #16]
	mul	x15, x17, x10
	lsl	x17, x17, #2
	ldp	x16, x12, [x13, #8]
	lsl	x18, x18, #2
	ldr	x10, [x13]
	add	x14, x14, x15, lsl #8
	ldp	x13, x15, [x0]
	lsl	x16, x16, #2
	lsl	x12, x12, #2
	ldr	x0, [x0, #16]
.LBB5_3:                                // %.preheader53
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB5_4 Depth 2
                                        //       Child Loop BB5_5 Depth 3
	add	x2, x9, x11
	mov	x1, xzr
	mov	x3, x10
	mul	x2, x15, x2
.LBB5_4:                                // %.preheader
                                        //   Parent Loop BB5_3 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB5_5 Depth 3
	madd	x4, x0, x1, x2
	mov	w5, #64
	mov	x6, x14
	mov	x7, x3
	ldr	s0, [x13, x4, lsl #2]
.LBB5_5:                                //   Parent Loop BB5_3 Depth=1
                                        //     Parent Loop BB5_4 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x6]
	add	x6, x6, x18
	ldr	s2, [x7]
	add	x7, x7, x16
	subs	x5, x5, #1
	fmadd	s0, s2, s1, s0
	str	s0, [x13, x4, lsl #2]
	b.ne	.LBB5_5
// %bb.6:                               //   in Loop: Header=BB5_4 Depth=2
	add	x1, x1, #1
	add	x3, x3, x12
	cmp	x1, x19
	b.ne	.LBB5_4
// %bb.7:                               // %._crit_edge62
                                        //   in Loop: Header=BB5_3 Depth=1
	add	x9, x9, #1
	add	x14, x14, x17
	cmp	x9, x8
	b.ne	.LBB5_3
.LBB5_8:                                // %.loopexit
	ldp	x20, x19, [sp, #256]            // 16-byte Folded Reload
	ldp	x22, x21, [sp, #240]            // 16-byte Folded Reload
	ldp	x24, x23, [sp, #224]            // 16-byte Folded Reload
	ldp	x26, x25, [sp, #208]            // 16-byte Folded Reload
	ldp	x28, x27, [sp, #192]            // 16-byte Folded Reload
	ldp	x29, x30, [sp, #176]            // 16-byte Folded Reload
	add	sp, sp, #272
	ret
.LBB5_9:                                // %.preheader56.lr.ph
	adrp	x9, .LCPI5_0
	adrp	x27, _ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	mov	x15, xzr
	mov	x16, xzr
	mov	w8, #1
	add	x27, x27, :lo12:_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	ldr	q0, [x9, :lo12:.LCPI5_0]
	str	x3, [sp, #32]                   // 8-byte Folded Spill
	str	q0, [sp, #16]                   // 16-byte Folded Spill
.LBB5_10:                               // %.preheader56
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB5_13 Depth 2
                                        //       Child Loop BB5_17 Depth 3
	ldp	x11, x12, [x3]
	lsl	x9, x16, #6
	str	x16, [sp, #72]                  // 8-byte Folded Spill
	add	x20, x8, x8, lsl #1
	lsl	x13, x8, #2
	lsl	x14, x8, #3
	add	x7, x13, x8
	add	x5, x14, x8
	mov	x10, xzr
	mul	x17, x16, x12
	lsl	x16, x8, #4
	madd	x23, x12, x15, x11
	lsl	x18, x7, #2
	lsl	x17, x17, #8
	lsl	x0, x20, #3
	str	x16, [sp, #88]                  // 8-byte Folded Spill
	lsl	x16, x20, #2
	lsl	x2, x8, #5
	lsl	x5, x5, #2
	lsl	x7, x7, #3
	lsl	x25, x20, #4
	str	x16, [sp, #80]                  // 8-byte Folded Spill
	mov	w16, #28
	lsl	x22, x12, #2
	mov	x21, x27
	mul	x1, x8, x16
	mov	w16, #44
	str	x15, [sp, #64]                  // 8-byte Folded Spill
	mul	x3, x8, x16
	mov	w16, #52
	mul	x4, x8, x16
	mov	w16, #56
	mul	x6, x8, x16
	mov	w16, #60
	mul	x30, x8, x16
	b	.LBB5_13
.LBB5_11:                               // %vector.body
                                        //   in Loop: Header=BB5_13 Depth=2
	add	x20, x10, x9
	ldr	x16, [sp, #80]                  // 8-byte Folded Reload
	lsl	x24, x24, #2
	mul	x28, x12, x20
	orr	x15, x24, #0x10
	add	x20, x13, x28
	add	x16, x16, x28
	lsl	x20, x20, #2
	add	x26, x14, x28
	lsl	x16, x16, #2
	lsl	x26, x26, #2
	ldr	q0, [x11, x20]
	ldr	x20, [sp, #88]                  // 8-byte Folded Reload
	ldr	q2, [x11, x16]
	add	x16, x18, x28
	ldr	q1, [x11, x26]
	orr	x26, x24, #0x20
	add	x20, x20, x28
	lsl	x16, x16, #2
	lsl	x20, x20, #2
	str	q0, [x27, x15]
	str	q1, [x27, x26]
	orr	x15, x24, #0x30
	ldr	q1, [x11, x16]
	add	x16, x0, x28
	ldr	q0, [x11, x20]
	orr	x20, x24, #0x40
	lsl	x16, x16, #2
	mov	w26, #80
	orr	x26, x24, x26
	str	q2, [x27, x15]
	str	q0, [x27, x20]
	orr	x15, x24, #0x60
	ldr	q0, [x11, x16]
	add	x16, x1, x28
	str	q1, [x27, x26]
	add	x26, x5, x28
	lsl	x16, x16, #2
	add	x20, x2, x28
	str	q0, [x27, x15]
	lsl	x15, x26, #2
	lsl	x20, x20, #2
	lsl	x26, x28, #2
	ldr	q0, [x11, x16]
	orr	x16, x24, #0x70
	ldr	q2, [x11, x15]
	mov	w15, #144
	orr	x15, x24, x15
	ldr	q1, [x11, x20]
	orr	x20, x24, #0x80
	str	q0, [x27, x16]
	add	x16, x3, x28
	str	q2, [x27, x15]
	add	x15, x7, x28
	lsl	x15, x15, #2
	str	q1, [x27, x20]
	lsl	x16, x16, #2
	add	x20, x25, x28
	lsl	x20, x20, #2
	ldr	q0, [x11, x15]
	mov	w15, #160
	orr	x15, x24, x15
	ldr	q1, [x11, x16]
	mov	w16, #176
	ldr	q2, [x11, x20]
	orr	x16, x24, x16
	orr	x20, x24, #0xc0
	str	q0, [x27, x15]
	add	x15, x4, x28
	ldr	q0, [x11, x26]
	lsl	x15, x15, #2
	str	q1, [x27, x16]
	add	x16, x6, x28
	str	q2, [x27, x20]
	add	x20, x30, x28
	lsl	x16, x16, #2
	lsl	x20, x20, #2
	str	q0, [x27, x24]
	ldr	q0, [x11, x15]
	mov	w15, #208
	orr	x15, x24, x15
	ldr	q1, [x11, x16]
	orr	x16, x24, #0xe0
	ldr	q2, [x11, x20]
	orr	x20, x24, #0xf0
	str	q0, [x27, x15]
	str	q1, [x27, x16]
	str	q2, [x27, x20]
.LBB5_12:                               // %middle.block
                                        //   in Loop: Header=BB5_13 Depth=2
	add	x10, x10, #1
	add	x21, x21, #256
	add	x23, x23, x22
	cmp	x10, #64
	b.eq	.LBB5_18
.LBB5_13:                               // %.preheader55
                                        //   Parent Loop BB5_10 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB5_17 Depth 3
	cmp	x8, #1
	b.ne	.LBB5_16
// %bb.14:                              // %vector.memcheck
                                        //   in Loop: Header=BB5_13 Depth=2
	mul	x20, x12, x10
	lsl	x24, x10, #6
	add	x20, x11, x20, lsl #2
	add	x28, x20, x17
	add	x20, x27, x24, lsl #2
	add	x26, x28, #256
	cmp	x26, x20
	b.ls	.LBB5_11
// %bb.15:                              // %vector.memcheck
                                        //   in Loop: Header=BB5_13 Depth=2
	add	x20, x20, #256
	cmp	x28, x20
	b.hs	.LBB5_11
.LBB5_16:                               // %scalar.ph.preheader
                                        //   in Loop: Header=BB5_13 Depth=2
	mov	x24, xzr
	mov	x28, x23
.LBB5_17:                               // %scalar.ph
                                        //   Parent Loop BB5_10 Depth=1
                                        //     Parent Loop BB5_13 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s0, [x28]
	add	x28, x28, x13
	str	s0, [x21, x24]
	add	x24, x24, #4
	cmp	x24, #256
	b.ne	.LBB5_17
	b	.LBB5_12
.LBB5_18:                               //   in Loop: Header=BB5_10 Depth=1
	ldp	x11, x10, [sp, #48]             // 16-byte Folded Reload
	sub	x2, x29, #32
	sub	x3, x29, #56
	ldr	q1, [sp, #16]                   // 16-byte Folded Reload
	sub	x4, x29, #80
	mov	x1, x19
	stur	x27, [x29, #-32]
	ldur	q0, [x10, #8]
	stur	q1, [x29, #-24]
	ldr	x10, [x10]
	fmov	x8, d0
	stur	q0, [x29, #-72]
	ldur	q0, [x11, #8]
	mul	x8, x8, x9
	ldr	x9, [x11]
	stur	q0, [x29, #-48]
	add	x8, x10, x8, lsl #2
	stur	x9, [x29, #-56]
	stur	x8, [x29, #-80]
	bl	_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_
	ldr	x16, [sp, #72]                  // 8-byte Folded Reload
	ldp	x3, x8, [sp, #32]               // 16-byte Folded Reload
	add	x16, x16, #1
	cmp	x16, x8
	b.eq	.LBB5_1
// %bb.19:                              // %..preheader56_crit_edge
                                        //   in Loop: Header=BB5_10 Depth=1
	ldr	x15, [sp, #64]                  // 8-byte Folded Reload
	ldr	x8, [x3, #16]
	add	x15, x15, #256
	b	.LBB5_10
.Lfunc_end5:
	.size	_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_, .Lfunc_end5-_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_
	.cfi_endproc
                                        // -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4                               // -- Begin function _Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
.LCPI6_0:
	.xword	64                              // 0x40
	.xword	1                               // 0x1
	.text
	.globl	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	.p2align	2
	.type	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_,@function
_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_: // @_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #336
	stp	x29, x30, [sp, #240]            // 16-byte Folded Spill
	add	x29, sp, #240
	stp	x28, x27, [sp, #256]            // 16-byte Folded Spill
	stp	x26, x25, [sp, #272]            // 16-byte Folded Spill
	stp	x24, x23, [sp, #288]            // 16-byte Folded Spill
	stp	x22, x21, [sp, #304]            // 16-byte Folded Spill
	stp	x20, x19, [sp, #320]            // 16-byte Folded Spill
	.cfi_def_cfa w29, 96
	.cfi_offset w19, -8
	.cfi_offset w20, -16
	.cfi_offset w21, -24
	.cfi_offset w22, -32
	.cfi_offset w23, -40
	.cfi_offset w24, -48
	.cfi_offset w25, -56
	.cfi_offset w26, -64
	.cfi_offset w27, -72
	.cfi_offset w28, -80
	.cfi_offset w30, -88
	.cfi_offset w29, -96
	mov	x20, x1
	cmp	x3, #64
	stp	x6, x2, [sp, #72]               // 16-byte Folded Spill
	stp	x4, x5, [sp, #8]                // 16-byte Folded Spill
	str	x3, [sp, #24]                   // 8-byte Folded Spill
	b.lo	.LBB6_7
// %bb.1:                               // %.preheader89.lr.ph.lr.ph
	ldp	x22, x10, [sp, #16]             // 16-byte Folded Reload
	lsl	x9, x20, #8
	adrp	x8, .LCPI6_0
	mov	x24, xzr
	ldr	x25, [sp, #8]                   // 8-byte Folded Reload
	str	x20, [sp, #48]                  // 8-byte Folded Spill
	ldr	q0, [x8, :lo12:.LCPI6_0]
	lsr	x11, x10, #6
	lsl	x23, x10, #2
	str	q0, [sp, #32]                   // 16-byte Folded Spill
	stp	x9, x11, [sp, #56]              // 16-byte Folded Spill
	ldr	x9, [sp, #80]                   // 8-byte Folded Reload
	lsl	x21, x9, #8
	lsl	x27, x9, #2
.LBB6_2:                                // %.preheader89.lr.ph
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB6_3 Depth 2
                                        //     Child Loop BB6_5 Depth 2
	ldr	x0, [sp, #56]                   // 8-byte Folded Reload
	bl	malloc
	mov	x28, x0
	mov	x9, x0
	mov	x10, x25
.LBB6_3:                                // %.preheader89
                                        //   Parent Loop BB6_2 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	ldp	q0, q1, [x10, #192]
	subs	x20, x20, #1
	ldp	q2, q3, [x10, #224]
	stp	q0, q1, [x9, #192]
	ldp	q0, q1, [x10, #128]
	stp	q2, q3, [x9, #224]
	ldp	q2, q3, [x10, #160]
	stp	q0, q1, [x9, #128]
	ldp	q0, q1, [x10, #64]
	stp	q2, q3, [x9, #160]
	ldp	q2, q3, [x10, #96]
	stp	q0, q1, [x9, #64]
	ldp	q0, q1, [x10]
	stp	q2, q3, [x9, #96]
	ldp	q2, q3, [x10, #32]
	stp	q0, q1, [x9]
	add	x10, x10, x23
	stp	q2, q3, [x9, #32]
	add	x9, x9, #256
	b.ne	.LBB6_3
// %bb.4:                               // %._crit_edge
                                        //   in Loop: Header=BB6_2 Depth=1
	mov	x0, x21
	mov	x19, x21
	bl	malloc
	mov	x21, x0
	mov	w26, #64
.LBB6_5:                                // %.preheader
                                        //   Parent Loop BB6_2 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	add	x0, x21, x20
	add	x1, x22, x20
	mov	x2, x27
	bl	memcpy
	add	x20, x20, x27
	subs	x26, x26, #1
	b.ne	.LBB6_5
// %bb.6:                               //   in Loop: Header=BB6_2 Depth=1
	ldr	x20, [sp, #48]                  // 8-byte Folded Reload
	mov	w9, #1
	ldp	x8, x2, [sp, #72]               // 16-byte Folded Reload
	sub	x3, x29, #32
	sub	x4, x29, #56
	ldr	q0, [sp, #32]                   // 16-byte Folded Reload
	sub	x5, x29, #80
	mov	x1, x20
	stp	x9, x28, [x29, #-40]
	stur	x9, [x29, #-64]
	stur	q0, [x29, #-24]
	stp	x21, x2, [x29, #-56]
	stp	x8, x2, [x29, #-80]
	bl	_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_
	mov	x0, x28
	bl	free
	mov	x0, x21
	bl	free
	ldr	x8, [sp, #64]                   // 8-byte Folded Reload
	add	x24, x24, #1
	add	x25, x25, #256
	mov	x21, x19
	add	x22, x22, x19
	cmp	x24, x8
	b.ne	.LBB6_2
.LBB6_7:                                // %._crit_edge96
	ldr	x12, [sp, #24]                  // 8-byte Folded Reload
	ands	x3, x12, #0x3f
	b.eq	.LBB6_9
// %bb.8:
	ldp	x11, x2, [sp, #72]              // 16-byte Folded Reload
	and	x8, x12, #0x7fffffffffffffc0
	mov	w9, #1
	sub	x4, x29, #104
	add	x5, sp, #112
	add	x6, sp, #88
	mov	x1, x20
	stp	x12, x9, [x29, #-96]
	stp	x11, x2, [sp, #88]
	ldr	x11, [sp, #8]                   // 8-byte Folded Reload
	mul	x10, x8, x2
	stp	x2, x9, [sp, #120]
	add	x8, x11, x8, lsl #2
	ldr	x11, [sp, #16]                  // 8-byte Folded Reload
	add	x10, x11, x10, lsl #2
	stur	x8, [x29, #-104]
	stp	x9, x10, [sp, #104]
	bl	_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_
.LBB6_9:
	ldp	x20, x19, [sp, #320]            // 16-byte Folded Reload
	ldp	x22, x21, [sp, #304]            // 16-byte Folded Reload
	ldp	x24, x23, [sp, #288]            // 16-byte Folded Reload
	ldp	x26, x25, [sp, #272]            // 16-byte Folded Reload
	ldp	x28, x27, [sp, #256]            // 16-byte Folded Reload
	ldp	x29, x30, [sp, #240]            // 16-byte Folded Reload
	add	sp, sp, #336
	ret
.Lfunc_end6:
	.size	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_, .Lfunc_end6-_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	.cfi_endproc
                                        // -- End function
	.globl	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_ // -- Begin function _Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.p2align	2
	.type	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_,@function
_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_: // @_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.cfi_startproc
// %bb.0:                               // %.lr.ph
	ldp	x8, x10, [x4]
	mov	w9, #12
	ldp	x12, x13, [x3]
	ldp	q21, q20, [x8, #32]
	madd	x9, x10, x9, x8
	add	x11, x8, x10, lsl #3
	add	x10, x8, x10, lsl #2
	add	x12, x12, #32
	lsl	x13, x13, #2
	ldp	q1, q0, [x9, #32]
	ldp	q4, q2, [x9]
	ldp	x15, x9, [x2]
	ldp	q5, q3, [x11, #32]
	mov	x14, x15
	ldp	q7, q6, [x11]
	add	x11, x9, x9, lsl #1
	lsl	x11, x11, #2
	ldp	q17, q16, [x10, #32]
	ldp	q19, q18, [x10]
	lsl	x10, x9, #3
	ldp	q23, q22, [x8]
.LBB7_1:                                // %.preheader82.preheader
                                        // =>This Inner Loop Header: Depth=1
	ld1r	{ v24.4s }, [x14], #4
	ldp	q26, q27, [x12, #-32]
	subs	x1, x1, #1
	fmla	v23.4s, v26.4s, v24.4s
	ldp	q28, q29, [x12]
	fmla	v22.4s, v27.4s, v24.4s
	add	x12, x12, x13
	fmla	v21.4s, v28.4s, v24.4s
	ldr	s25, [x15, x9, lsl #2]
	fmla	v20.4s, v29.4s, v24.4s
	ldr	s30, [x15, x10]
	ldr	s24, [x15, x11]
	mov	x15, x14
	fmla	v19.4s, v26.4s, v25.s[0]
	fmla	v18.4s, v27.4s, v25.s[0]
	fmla	v17.4s, v28.4s, v25.s[0]
	fmla	v16.4s, v29.4s, v25.s[0]
	fmla	v7.4s, v26.4s, v30.s[0]
	fmla	v6.4s, v27.4s, v30.s[0]
	fmla	v5.4s, v28.4s, v30.s[0]
	fmla	v3.4s, v29.4s, v30.s[0]
	fmla	v4.4s, v26.4s, v24.s[0]
	fmla	v2.4s, v27.4s, v24.s[0]
	fmla	v1.4s, v28.4s, v24.s[0]
	fmla	v0.4s, v29.4s, v24.s[0]
	b.ne	.LBB7_1
// %bb.2:                               // %.preheader81
	str	q23, [x8]
	mov	w10, #12
	ldr	x8, [x4, #16]
	ldr	x9, [x4]
	str	q22, [x9, x8, lsl #4]
	ldr	x8, [x4, #16]
	ldr	x9, [x4]
	lsl	x8, x8, #5
	str	q21, [x9, x8]
	mov	w9, #48
	ldr	x8, [x4, #16]
	mul	x8, x8, x9
	ldr	x9, [x4]
	str	q20, [x9, x8]
	ldp	x9, x8, [x4]
	lsl	x8, x8, #2
	str	q19, [x9, x8]
	ldp	x8, x9, [x4, #8]
	add	x8, x8, x9, lsl #2
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q18, [x9, x8]
	ldp	x8, x9, [x4, #8]
	add	x8, x8, x9, lsl #3
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q17, [x9, x8]
	ldp	x8, x9, [x4, #8]
	madd	x8, x9, x10, x8
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q16, [x9, x8]
	ldp	x9, x8, [x4]
	lsl	x8, x8, #3
	str	q7, [x9, x8]
	ldp	x9, x8, [x4, #8]
	lsl	x8, x8, #2
	add	x8, x8, x9, lsl #1
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q6, [x9, x8]
	ldp	x9, x8, [x4, #8]
	lsl	x8, x8, #3
	add	x8, x8, x9, lsl #1
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q5, [x9, x8]
	ldp	x9, x8, [x4, #8]
	mul	x8, x8, x10
	add	x8, x8, x9, lsl #1
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q3, [x9, x8]
	ldp	x9, x8, [x4]
	mul	x8, x8, x10
	str	q4, [x9, x8]
	ldp	x8, x9, [x4, #8]
	add	x8, x8, x8, lsl #1
	add	x8, x8, x9, lsl #2
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q2, [x9, x8]
	ldp	x8, x9, [x4, #8]
	add	x8, x8, x8, lsl #1
	add	x8, x8, x9, lsl #3
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q1, [x9, x8]
	ldp	x8, x9, [x4, #8]
	add	x8, x8, x8, lsl #1
	madd	x8, x9, x10, x8
	ldr	x9, [x4]
	lsl	x8, x8, #2
	str	q0, [x9, x8]
	ret
.Lfunc_end7:
	.size	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_, .Lfunc_end7-_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.cfi_endproc
                                        // -- End function
	.globl	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_ // -- Begin function _Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	.p2align	2
	.type	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_,@function
_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_: // @_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #480
	stp	x29, x30, [sp, #384]            // 16-byte Folded Spill
	add	x29, sp, #384
	stp	x28, x27, [sp, #400]            // 16-byte Folded Spill
	stp	x26, x25, [sp, #416]            // 16-byte Folded Spill
	stp	x24, x23, [sp, #432]            // 16-byte Folded Spill
	stp	x22, x21, [sp, #448]            // 16-byte Folded Spill
	stp	x20, x19, [sp, #464]            // 16-byte Folded Spill
	.cfi_def_cfa w29, 96
	.cfi_offset w19, -8
	.cfi_offset w20, -16
	.cfi_offset w21, -24
	.cfi_offset w22, -32
	.cfi_offset w23, -40
	.cfi_offset w24, -48
	.cfi_offset w25, -56
	.cfi_offset w26, -64
	.cfi_offset w27, -72
	.cfi_offset w28, -80
	.cfi_offset w30, -88
	.cfi_offset w29, -96
	mov	w0, #16384
	mov	x19, x6
	str	x5, [sp, #24]                   // 8-byte Folded Spill
	mov	x20, x3
	str	x4, [sp, #112]                  // 8-byte Folded Spill
	mov	x21, x2
	mov	x23, x1
	bl	malloc
	mov	x22, x0
	mov	w0, #16384
	bl	malloc
	mov	x24, x0
	lsr	x10, x20, #6
	lsl	x11, x21, #2
	lsr	x8, x23, #2
	cmp	x20, #64
	str	x20, [sp, #104]                 // 8-byte Folded Spill
	str	x8, [sp, #16]                   // 8-byte Folded Spill
	stur	x21, [x29, #-56]                // 8-byte Folded Spill
	stur	x11, [x29, #-96]                // 8-byte Folded Spill
	str	x23, [sp, #136]                 // 8-byte Folded Spill
	b.lo	.LBB8_47
// %bb.1:                               // %.preheader502.lr.ph
	lsl	x8, x21, #1
	mov	x14, x21
	add	x9, x8, x21
	lsr	x13, x23, #6
	add	x15, x9, #12
	add	x12, x9, #8
	mov	x17, x9
	add	x18, x9, #4
	add	x9, x8, #12
	mov	x16, x8
	add	x0, x21, #12
	add	x1, x21, #8
	add	x2, x21, #4
	cmp	x23, #64
	stp	x9, x18, [x29, #-40]            // 16-byte Folded Spill
	add	x9, x8, #8
	add	x18, x8, #4
	lsl	x8, x20, #8
	stp	x12, x15, [x29, #-24]           // 16-byte Folded Spill
	stur	x9, [x29, #-48]                 // 8-byte Folded Spill
	stur	x8, [x29, #-184]                // 8-byte Folded Spill
	str	x10, [sp, #8]                   // 8-byte Folded Spill
	stur	x22, [x29, #-112]               // 8-byte Folded Spill
	stur	x24, [x29, #-72]                // 8-byte Folded Spill
	b.lo	.LBB8_26
// %bb.2:                               // %.preheader502.lr.ph.split.us
	lsl	x4, x20, #2
	cmp	x14, #64
	str	x13, [sp, #184]                 // 8-byte Folded Spill
	b.hs	.LBB8_9
// %bb.3:                               // %.preheader502.us.preheader
	cmp	x13, #1
	mov	x8, xzr
	csinc	x9, x13, xzr, hi
	cmp	x10, #1
	csinc	x10, x10, xzr, hi
	ldr	x11, [sp, #112]                 // 8-byte Folded Reload
.LBB8_4:                                // %.preheader502.us
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB8_5 Depth 2
                                        //       Child Loop BB8_6 Depth 3
	mov	x12, xzr
	mov	x13, x11
.LBB8_5:                                // %.preheader501.us570
                                        //   Parent Loop BB8_4 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB8_6 Depth 3
	mov	x14, xzr
	mov	x3, x13
.LBB8_6:                                // %.preheader499.us567
                                        //   Parent Loop BB8_4 Depth=1
                                        //     Parent Loop BB8_5 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldp	q0, q1, [x3, #192]
	add	x15, x22, x14
	add	x14, x14, #256
	cmp	x14, #4, lsl #12                // =16384
	ldp	q2, q3, [x3, #224]
	stp	q0, q1, [x15, #192]
	ldp	q0, q1, [x3, #128]
	stp	q2, q3, [x15, #224]
	ldp	q2, q3, [x3, #160]
	stp	q0, q1, [x15, #128]
	ldp	q0, q1, [x3, #64]
	stp	q2, q3, [x15, #160]
	ldp	q2, q3, [x3, #96]
	stp	q0, q1, [x15, #64]
	ldp	q0, q1, [x3]
	stp	q2, q3, [x15, #96]
	stp	q0, q1, [x15]
	ldp	q2, q0, [x3, #32]
	add	x3, x3, x4
	stp	q2, q0, [x15, #32]
	b.ne	.LBB8_6
// %bb.7:                               // %.preheader500.us569
                                        //   in Loop: Header=BB8_5 Depth=2
	ldur	x14, [x29, #-184]               // 8-byte Folded Reload
	add	x12, x12, #1
	cmp	x12, x9
	add	x13, x13, x14
	b.ne	.LBB8_5
// %bb.8:                               // %._crit_edge563.split.us572
                                        //   in Loop: Header=BB8_4 Depth=1
	add	x8, x8, #1
	add	x11, x11, #256
	ldur	x14, [x29, #-56]                // 8-byte Folded Reload
	cmp	x8, x10
	b.ne	.LBB8_4
	b	.LBB8_25
.LBB8_9:                                // %.preheader502.us.us.preheader
	lsr	x8, x14, #6
	mov	x9, xzr
	cmp	x8, #1
	csinc	x8, x8, xzr, hi
	cmp	x13, #1
	stur	x8, [x29, #-104]                // 8-byte Folded Spill
	csinc	x8, x13, xzr, hi
	cmp	x10, #1
	stur	x8, [x29, #-152]                // 8-byte Folded Spill
	lsl	x8, x14, #8
	stur	x8, [x29, #-176]                // 8-byte Folded Spill
	csinc	x8, x10, xzr, hi
	str	x8, [sp, #192]                  // 8-byte Folded Spill
	ldr	x8, [sp, #24]                   // 8-byte Folded Reload
	stur	x8, [x29, #-136]                // 8-byte Folded Spill
	ldr	x12, [sp, #112]                 // 8-byte Folded Reload
	stur	x4, [x29, #-144]                // 8-byte Folded Spill
.LBB8_10:                               // %.preheader502.us.us
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB8_11 Depth 2
                                        //       Child Loop BB8_12 Depth 3
                                        //       Child Loop BB8_14 Depth 3
                                        //         Child Loop BB8_15 Depth 4
                                        //         Child Loop BB8_17 Depth 4
                                        //           Child Loop BB8_18 Depth 5
                                        //             Child Loop BB8_19 Depth 6
	stp	x12, x9, [x29, #-168]           // 16-byte Folded Spill
	mov	x13, xzr
	mov	x9, x12
.LBB8_11:                               // %.preheader501.us.us.us
                                        //   Parent Loop BB8_10 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB8_12 Depth 3
                                        //       Child Loop BB8_14 Depth 3
                                        //         Child Loop BB8_15 Depth 4
                                        //         Child Loop BB8_17 Depth 4
                                        //           Child Loop BB8_18 Depth 5
                                        //             Child Loop BB8_19 Depth 6
	mov	x8, xzr
	stur	x9, [x29, #-128]                // 8-byte Folded Spill
.LBB8_12:                               // %.preheader499.us.us.us
                                        //   Parent Loop BB8_10 Depth=1
                                        //     Parent Loop BB8_11 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldp	q0, q1, [x9, #192]
	add	x10, x22, x8
	add	x8, x8, #256
	cmp	x8, #4, lsl #12                 // =16384
	ldp	q2, q3, [x9, #224]
	stp	q0, q1, [x10, #192]
	ldp	q0, q1, [x9, #128]
	stp	q2, q3, [x10, #224]
	ldp	q2, q3, [x9, #160]
	stp	q0, q1, [x10, #128]
	ldp	q0, q1, [x9, #64]
	stp	q2, q3, [x10, #160]
	ldp	q2, q3, [x9, #96]
	stp	q0, q1, [x10, #64]
	ldp	q0, q1, [x9]
	stp	q2, q3, [x10, #96]
	stp	q0, q1, [x10]
	ldp	q2, q0, [x9, #32]
	add	x9, x9, x4
	stp	q2, q0, [x10, #32]
	b.ne	.LBB8_12
// %bb.13:                              // %.preheader500.us.us.us
                                        //   in Loop: Header=BB8_11 Depth=2
	mov	x9, xzr
	lsl	x8, x13, #6
	ldur	x10, [x29, #-136]               // 8-byte Folded Reload
	stur	x13, [x29, #-120]               // 8-byte Folded Spill
	stur	x8, [x29, #-64]                 // 8-byte Folded Spill
.LBB8_14:                               // %.preheader498.us.us.us
                                        //   Parent Loop BB8_10 Depth=1
                                        //     Parent Loop BB8_11 Depth=2
                                        // =>    This Loop Header: Depth=3
                                        //         Child Loop BB8_15 Depth 4
                                        //         Child Loop BB8_17 Depth 4
                                        //           Child Loop BB8_18 Depth 5
                                        //             Child Loop BB8_19 Depth 6
	mov	x8, xzr
	stp	x10, x9, [x29, #-88]            // 16-byte Folded Spill
	lsl	x6, x9, #6
	mov	x9, x10
.LBB8_15:                               // %.preheader496.us.us.us
                                        //   Parent Loop BB8_10 Depth=1
                                        //     Parent Loop BB8_11 Depth=2
                                        //       Parent Loop BB8_14 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldp	q0, q1, [x9, #192]
	add	x10, x24, x8
	add	x8, x8, #256
	cmp	x8, #4, lsl #12                 // =16384
	ldp	q2, q3, [x9, #224]
	stp	q0, q1, [x10, #192]
	ldp	q0, q1, [x9, #128]
	stp	q2, q3, [x10, #224]
	ldp	q2, q3, [x9, #160]
	stp	q0, q1, [x10, #128]
	ldp	q0, q1, [x9, #64]
	stp	q2, q3, [x10, #160]
	ldp	q2, q3, [x9, #96]
	stp	q0, q1, [x10, #64]
	ldp	q0, q1, [x9]
	stp	q2, q3, [x10, #96]
	stp	q0, q1, [x10]
	ldp	q2, q0, [x9, #32]
	add	x9, x9, x11
	stp	q2, q0, [x10, #32]
	b.ne	.LBB8_15
// %bb.16:                              // %.preheader495.us.us.us.preheader
                                        //   in Loop: Header=BB8_14 Depth=3
	mov	x7, xzr
	mov	x3, x22
.LBB8_17:                               // %.preheader495.us.us.us
                                        //   Parent Loop BB8_10 Depth=1
                                        //     Parent Loop BB8_11 Depth=2
                                        //       Parent Loop BB8_14 Depth=3
                                        // =>      This Loop Header: Depth=4
                                        //           Child Loop BB8_18 Depth 5
                                        //             Child Loop BB8_19 Depth 6
	ldur	x8, [x29, #-64]                 // 8-byte Folded Reload
	mov	x10, xzr
	add	x8, x8, x7, lsl #2
	mul	x23, x8, x14
.LBB8_18:                               //   Parent Loop BB8_10 Depth=1
                                        //     Parent Loop BB8_11 Depth=2
                                        //       Parent Loop BB8_14 Depth=3
                                        //         Parent Loop BB8_17 Depth=4
                                        // =>        This Loop Header: Depth=5
                                        //             Child Loop BB8_19 Depth 6
	add	x8, x6, x10, lsl #4
	mov	x25, xzr
	add	x8, x23, x8
	mov	x13, x3
	add	x4, x19, x8, lsl #2
	ldur	x8, [x29, #-16]                 // 8-byte Folded Reload
	add	x21, x4, x17, lsl #2
	add	x27, x4, x18, lsl #2
	add	x28, x4, x16, lsl #2
	add	x22, x4, x0, lsl #2
	add	x5, x4, x8, lsl #2
	ldur	x8, [x29, #-24]                 // 8-byte Folded Reload
	add	x11, x4, x2, lsl #2
	add	x12, x4, x14, lsl #2
	ldp	q21, q20, [x4, #32]
	add	x20, x4, x8, lsl #2
	mov	x14, x3
	ldur	x8, [x29, #-32]                 // 8-byte Folded Reload
	ldp	q23, q22, [x4]
	add	x26, x4, x8, lsl #2
	ldur	x8, [x29, #-40]                 // 8-byte Folded Reload
	ldr	q0, [x5]
	ldr	q1, [x20]
	add	x9, x4, x8, lsl #2
	ldur	x8, [x29, #-48]                 // 8-byte Folded Reload
	ldr	q2, [x26]
	ldr	q3, [x21]
	add	x30, x4, x8, lsl #2
	add	x8, x4, x1, lsl #2
	ldr	q4, [x9]
	ldr	q6, [x27]
	ldr	q5, [x30]
	ldr	q7, [x28]
	ldr	q16, [x22]
	ldr	q17, [x8]
	ldr	q18, [x11]
	ldr	q19, [x12]
.LBB8_19:                               // %.preheader82.preheader.i.us.us.us
                                        //   Parent Loop BB8_10 Depth=1
                                        //     Parent Loop BB8_11 Depth=2
                                        //       Parent Loop BB8_14 Depth=3
                                        //         Parent Loop BB8_17 Depth=4
                                        //           Parent Loop BB8_18 Depth=5
                                        // =>          This Inner Loop Header: Depth=6
	add	x15, x24, x25
	add	x25, x25, #256
	ld1r	{ v24.4s }, [x14], #4
	ldr	s29, [x13, #256]
	cmp	x25, #4, lsl #12                // =16384
	ldp	q25, q26, [x15]
	fmla	v23.4s, v25.4s, v24.4s
	fmla	v19.4s, v25.4s, v29.s[0]
	ldp	q27, q28, [x15, #32]
	fmla	v22.4s, v26.4s, v24.4s
	fmla	v18.4s, v26.4s, v29.s[0]
	fmla	v21.4s, v27.4s, v24.4s
	fmla	v17.4s, v27.4s, v29.s[0]
	ldr	s30, [x13, #512]
	fmla	v20.4s, v28.4s, v24.4s
	ldr	s24, [x13, #768]
	fmla	v16.4s, v28.4s, v29.s[0]
	mov	x13, x14
	fmla	v7.4s, v25.4s, v30.s[0]
	fmla	v6.4s, v26.4s, v30.s[0]
	fmla	v5.4s, v27.4s, v30.s[0]
	fmla	v4.4s, v28.4s, v30.s[0]
	fmla	v3.4s, v25.4s, v24.s[0]
	fmla	v2.4s, v26.4s, v24.s[0]
	fmla	v1.4s, v27.4s, v24.s[0]
	fmla	v0.4s, v28.4s, v24.s[0]
	b.ne	.LBB8_19
// %bb.20:                              // %_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.exit.us.us.us
                                        //   in Loop: Header=BB8_18 Depth=5
	add	x10, x10, #1
	add	x24, x24, #64
	ldur	x14, [x29, #-56]                // 8-byte Folded Reload
	cmp	x10, #4
	stp	q23, q22, [x4]
	stp	q21, q20, [x4, #32]
	str	q19, [x12]
	str	q18, [x11]
	str	q17, [x8]
	str	q16, [x22]
	str	q7, [x28]
	str	q6, [x27]
	str	q5, [x30]
	str	q4, [x9]
	str	q3, [x21]
	str	q2, [x26]
	str	q1, [x20]
	str	q0, [x5]
	b.ne	.LBB8_18
// %bb.21:                              //   in Loop: Header=BB8_17 Depth=4
	add	x7, x7, #1
	add	x3, x3, #1024
	ldur	x24, [x29, #-72]                // 8-byte Folded Reload
	cmp	x7, #16
	b.ne	.LBB8_17
// %bb.22:                              //   in Loop: Header=BB8_14 Depth=3
	ldp	x10, x9, [x29, #-88]            // 16-byte Folded Reload
	ldp	x22, x8, [x29, #-112]           // 16-byte Folded Reload
	add	x10, x10, #256
	ldur	x11, [x29, #-96]                // 8-byte Folded Reload
	add	x9, x9, #1
	cmp	x9, x8
	b.ne	.LBB8_14
// %bb.23:                              // %._crit_edge.us.us.us
                                        //   in Loop: Header=BB8_11 Depth=2
	ldp	x9, x13, [x29, #-128]           // 16-byte Folded Reload
	ldur	x8, [x29, #-184]                // 8-byte Folded Reload
	add	x9, x9, x8
	add	x13, x13, #1
	ldp	x8, x4, [x29, #-152]            // 16-byte Folded Reload
	cmp	x13, x8
	b.ne	.LBB8_11
// %bb.24:                              // %._crit_edge563.split.us.us.us
                                        //   in Loop: Header=BB8_10 Depth=1
	ldur	x8, [x29, #-176]                // 8-byte Folded Reload
	ldur	x10, [x29, #-136]               // 8-byte Folded Reload
	ldp	x12, x9, [x29, #-168]           // 16-byte Folded Reload
	add	x10, x10, x8
	add	x12, x12, #256
	stur	x10, [x29, #-136]               // 8-byte Folded Spill
	add	x9, x9, #1
	ldr	x8, [sp, #192]                  // 8-byte Folded Reload
	ldr	x20, [sp, #104]                 // 8-byte Folded Reload
	cmp	x9, x8
	b.ne	.LBB8_10
.LBB8_25:                               // %.preheader494
	ldr	x23, [sp, #136]                 // 8-byte Folded Reload
	cmp	x20, #63
	ldr	x10, [sp, #8]                   // 8-byte Folded Reload
	ldr	x13, [sp, #184]                 // 8-byte Folded Reload
	b.ls	.LBB8_47
.LBB8_26:                               // %.preheader493.lr.ph
	ubfx	x11, x23, #2, #4
	lsr	x8, x14, #4
	ubfx	x9, x14, #4, #2
	cmp	x13, #1
	mov	x5, x13
	mov	x4, xzr
	stp	x11, x9, [x29, #-160]           // 16-byte Folded Spill
	lsl	x11, x13, #4
	and	x9, x14, #0x7fffffffffffffc0
	mul	x12, x20, x5
	lsl	x15, x20, #4
	stur	x11, [x29, #-168]               // 8-byte Folded Spill
	csinc	x11, x13, xzr, hi
	cmp	x8, #1
	ldr	x3, [sp, #112]                  // 8-byte Folded Reload
	csinc	x8, x8, xzr, hi
	cmp	x10, #1
	ldr	x13, [sp, #24]                  // 8-byte Folded Reload
	stp	x8, x11, [sp, #168]             // 16-byte Folded Spill
	csinc	x8, x10, xzr, hi
	add	x11, x3, x20, lsl #2
	add	x10, x3, x20, lsl #3
	str	x8, [sp, #128]                  // 8-byte Folded Spill
	mov	w8, #12
	stp	x10, x11, [sp, #88]             // 16-byte Folded Spill
	mov	w11, #8
	madd	x10, x20, x8, x3
	stur	x9, [x29, #-176]                // 8-byte Folded Spill
	add	x9, x13, x9, lsl #2
	bfi	x11, x5, #8, #56
	add	x9, x9, #32
	bfi	x8, x5, #8, #56
	str	x10, [sp, #80]                  // 8-byte Folded Spill
	mov	w10, #4
	bfi	x10, x5, #8, #56
	madd	x8, x20, x8, x3
	madd	x10, x20, x10, x3
	stp	x9, x10, [sp, #64]              // 16-byte Folded Spill
	madd	x10, x20, x11, x3
	lsl	x9, x14, #6
	str	x9, [sp, #120]                  // 8-byte Folded Spill
	add	x9, x3, x12, lsl #8
	stp	x8, x10, [sp, #48]              // 16-byte Folded Spill
	add	x8, x13, #32
	stp	x8, x9, [sp, #32]               // 16-byte Folded Spill
	ldur	x13, [x29, #-96]                // 8-byte Folded Reload
	b	.LBB8_28
.LBB8_27:                               // %._crit_edge584
                                        //   in Loop: Header=BB8_28 Depth=1
	ldr	x4, [sp, #160]                  // 8-byte Folded Reload
	ldr	x8, [sp, #128]                  // 8-byte Folded Reload
	add	x4, x4, #1
	cmp	x4, x8
	b.eq	.LBB8_46
.LBB8_28:                               // %.preheader493
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB8_31 Depth 2
                                        //       Child Loop BB8_32 Depth 3
                                        //         Child Loop BB8_33 Depth 4
                                        //           Child Loop BB8_34 Depth 5
                                        //     Child Loop BB8_41 Depth 2
                                        //       Child Loop BB8_42 Depth 3
                                        //         Child Loop BB8_43 Depth 4
	ldr	x9, [sp, #120]                  // 8-byte Folded Reload
	and	x8, x4, #0x3ffffff
	mul	x9, x9, x8
	lsl	x8, x8, #8
	stp	x8, x4, [sp, #152]              // 16-byte Folded Spill
	ldr	x8, [sp, #136]                  // 8-byte Folded Reload
	str	x9, [sp, #144]                  // 8-byte Folded Spill
	cmp	x8, #64
	b.lo	.LBB8_38
// %bb.29:                              // %.preheader491.lr.ph
                                        //   in Loop: Header=BB8_28 Depth=1
	ldur	x8, [x29, #-152]                // 8-byte Folded Reload
	cbz	x8, .LBB8_38
// %bb.30:                              // %.preheader491.us.preheader
                                        //   in Loop: Header=BB8_28 Depth=1
	ldr	x8, [sp, #112]                  // 8-byte Folded Reload
	mov	x11, xzr
	ldr	x9, [sp, #152]                  // 8-byte Folded Reload
	add	x8, x8, x9
	stur	x8, [x29, #-120]                // 8-byte Folded Spill
	ldr	x8, [sp, #96]                   // 8-byte Folded Reload
	add	x8, x8, x9
	stur	x8, [x29, #-128]                // 8-byte Folded Spill
	ldr	x8, [sp, #88]                   // 8-byte Folded Reload
	add	x8, x8, x9
	stur	x8, [x29, #-136]                // 8-byte Folded Spill
	ldr	x8, [sp, #64]                   // 8-byte Folded Reload
	ldr	x10, [sp, #144]                 // 8-byte Folded Reload
	add	x8, x8, x10, lsl #2
	str	x8, [sp, #184]                  // 8-byte Folded Spill
	ldr	x8, [sp, #80]                   // 8-byte Folded Reload
	add	x8, x8, x9
	stur	x8, [x29, #-144]                // 8-byte Folded Spill
.LBB8_31:                               // %.preheader491.us
                                        //   Parent Loop BB8_28 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB8_32 Depth 3
                                        //         Child Loop BB8_33 Depth 4
                                        //           Child Loop BB8_34 Depth 5
	lsl	x8, x11, #6
	str	x11, [sp, #192]                 // 8-byte Folded Spill
	mov	x9, xzr
	stur	x8, [x29, #-88]                 // 8-byte Folded Spill
	ldr	x8, [sp, #184]                  // 8-byte Folded Reload
	stur	x8, [x29, #-64]                 // 8-byte Folded Spill
.LBB8_32:                               // %.preheader489.us
                                        //   Parent Loop BB8_28 Depth=1
                                        //     Parent Loop BB8_31 Depth=2
                                        // =>    This Loop Header: Depth=3
                                        //         Child Loop BB8_33 Depth 4
                                        //           Child Loop BB8_34 Depth 5
	ldur	x8, [x29, #-176]                // 8-byte Folded Reload
	stur	x9, [x29, #-104]                // 8-byte Folded Spill
	ldp	x4, x23, [x29, #-144]           // 16-byte Folded Reload
	mov	x3, xzr
	add	x8, x8, x9, lsl #4
	ldp	x25, x9, [x29, #-128]           // 16-byte Folded Reload
	stur	x8, [x29, #-80]                 // 8-byte Folded Spill
.LBB8_33:                               //   Parent Loop BB8_28 Depth=1
                                        //     Parent Loop BB8_31 Depth=2
                                        //       Parent Loop BB8_32 Depth=3
                                        // =>      This Loop Header: Depth=4
                                        //           Child Loop BB8_34 Depth 5
	ldp	x8, x10, [x29, #-88]            // 16-byte Folded Reload
	mov	x5, xzr
	add	x8, x8, x3, lsl #2
	madd	x8, x8, x14, x10
	ldur	x10, [x29, #-64]                // 8-byte Folded Reload
	add	x28, x19, x8, lsl #2
	ldur	x8, [x29, #-16]                 // 8-byte Folded Reload
	add	x6, x28, x17, lsl #2
	add	x26, x28, x18, lsl #2
	add	x20, x28, x16, lsl #2
	add	x22, x28, x0, lsl #2
	add	x24, x28, x8, lsl #2
	ldur	x8, [x29, #-24]                 // 8-byte Folded Reload
	add	x11, x28, x2, lsl #2
	add	x12, x28, x14, lsl #2
	ldp	q21, q20, [x28, #32]
	add	x27, x28, x8, lsl #2
	ldur	x8, [x29, #-32]                 // 8-byte Folded Reload
	ldp	q23, q22, [x28]
	add	x7, x28, x8, lsl #2
	ldur	x8, [x29, #-40]                 // 8-byte Folded Reload
	ldr	q0, [x24]
	ldr	q1, [x27]
	add	x21, x28, x8, lsl #2
	ldur	x8, [x29, #-48]                 // 8-byte Folded Reload
	ldr	q2, [x7]
	ldr	q3, [x6]
	add	x30, x28, x8, lsl #2
	add	x8, x28, x1, lsl #2
	ldr	q4, [x21]
	ldr	q6, [x26]
	ldr	q5, [x30]
	ldr	q7, [x20]
	ldr	q16, [x22]
	ldr	q17, [x8]
	ldr	q18, [x11]
	ldr	q19, [x12]
.LBB8_34:                               // %.preheader82.preheader.i314.us
                                        //   Parent Loop BB8_28 Depth=1
                                        //     Parent Loop BB8_31 Depth=2
                                        //       Parent Loop BB8_32 Depth=3
                                        //         Parent Loop BB8_33 Depth=4
                                        // =>        This Inner Loop Header: Depth=5
	ldp	q26, q27, [x10, #-32]
	ldp	q28, q29, [x10]
	add	x10, x10, x13
	ldr	s24, [x9, x5]
	ldr	s25, [x25, x5]
	ldr	s30, [x23, x5]
	fmla	v23.4s, v26.4s, v24.s[0]
	fmla	v22.4s, v27.4s, v24.s[0]
	fmla	v21.4s, v28.4s, v24.s[0]
	fmla	v20.4s, v29.4s, v24.s[0]
	ldr	s24, [x4, x5]
	fmla	v19.4s, v26.4s, v25.s[0]
	fmla	v18.4s, v27.4s, v25.s[0]
	fmla	v17.4s, v28.4s, v25.s[0]
	fmla	v16.4s, v29.4s, v25.s[0]
	fmla	v7.4s, v26.4s, v30.s[0]
	fmla	v6.4s, v27.4s, v30.s[0]
	fmla	v5.4s, v28.4s, v30.s[0]
	fmla	v4.4s, v29.4s, v30.s[0]
	fmla	v3.4s, v26.4s, v24.s[0]
	fmla	v2.4s, v27.4s, v24.s[0]
	fmla	v1.4s, v28.4s, v24.s[0]
	fmla	v0.4s, v29.4s, v24.s[0]
	add	x5, x5, #4
	cmp	x5, #256
	b.ne	.LBB8_34
// %bb.35:                              // %_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.exit315.us
                                        //   in Loop: Header=BB8_33 Depth=4
	add	x3, x3, #1
	add	x9, x9, x15
	add	x25, x25, x15
	add	x23, x23, x15
	add	x4, x4, x15
	cmp	x3, #16
	stp	q23, q22, [x28]
	stp	q21, q20, [x28, #32]
	str	q19, [x12]
	str	q18, [x11]
	str	q17, [x8]
	mov	x8, x15
	str	q16, [x22]
	str	q7, [x20]
	str	q6, [x26]
	str	q5, [x30]
	str	q4, [x21]
	str	q3, [x6]
	str	q2, [x7]
	str	q1, [x27]
	str	q0, [x24]
	b.ne	.LBB8_33
// %bb.36:                              //   in Loop: Header=BB8_32 Depth=3
	ldur	x8, [x29, #-64]                 // 8-byte Folded Reload
	ldur	x9, [x29, #-104]                // 8-byte Folded Reload
	add	x8, x8, #64
	add	x9, x9, #1
	stur	x8, [x29, #-64]                 // 8-byte Folded Spill
	ldur	x8, [x29, #-152]                // 8-byte Folded Reload
	cmp	x9, x8
	b.ne	.LBB8_32
// %bb.37:                              // %._crit_edge.us
                                        //   in Loop: Header=BB8_31 Depth=2
	ldur	x8, [x29, #-184]                // 8-byte Folded Reload
	ldur	x9, [x29, #-120]                // 8-byte Folded Reload
	ldr	x11, [sp, #192]                 // 8-byte Folded Reload
	add	x9, x9, x8
	add	x11, x11, #1
	stur	x9, [x29, #-120]                // 8-byte Folded Spill
	ldur	x9, [x29, #-128]                // 8-byte Folded Reload
	add	x9, x9, x8
	stur	x9, [x29, #-128]                // 8-byte Folded Spill
	ldur	x9, [x29, #-136]                // 8-byte Folded Reload
	add	x9, x9, x8
	stur	x9, [x29, #-136]                // 8-byte Folded Spill
	ldur	x9, [x29, #-144]                // 8-byte Folded Reload
	add	x9, x9, x8
	stur	x9, [x29, #-144]                // 8-byte Folded Spill
	ldr	x8, [sp, #176]                  // 8-byte Folded Reload
	cmp	x11, x8
	b.ne	.LBB8_31
.LBB8_38:                               // %.preheader492
                                        //   in Loop: Header=BB8_28 Depth=1
	cmp	x14, #16
	b.lo	.LBB8_27
// %bb.39:                              // %.preheader490.lr.ph
                                        //   in Loop: Header=BB8_28 Depth=1
	ldur	x8, [x29, #-160]                // 8-byte Folded Reload
	cbz	x8, .LBB8_27
// %bb.40:                              // %.preheader490.us.preheader
                                        //   in Loop: Header=BB8_28 Depth=1
	ldr	x8, [sp, #40]                   // 8-byte Folded Reload
	mov	x11, xzr
	ldr	x9, [sp, #152]                  // 8-byte Folded Reload
	add	x8, x8, x9
	stur	x8, [x29, #-104]                // 8-byte Folded Spill
	ldr	x8, [sp, #72]                   // 8-byte Folded Reload
	add	x8, x8, x9
	stur	x8, [x29, #-120]                // 8-byte Folded Spill
	ldr	x8, [sp, #56]                   // 8-byte Folded Reload
	add	x8, x8, x9
	stur	x8, [x29, #-128]                // 8-byte Folded Spill
	ldr	x8, [sp, #32]                   // 8-byte Folded Reload
	ldr	x10, [sp, #144]                 // 8-byte Folded Reload
	add	x8, x8, x10, lsl #2
	stur	x8, [x29, #-64]                 // 8-byte Folded Spill
	ldr	x8, [sp, #48]                   // 8-byte Folded Reload
	add	x8, x8, x9
	stur	x8, [x29, #-136]                // 8-byte Folded Spill
.LBB8_41:                               // %.preheader490.us
                                        //   Parent Loop BB8_28 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB8_42 Depth 3
                                        //         Child Loop BB8_43 Depth 4
	ldp	x5, x6, [x29, #-136]            // 16-byte Folded Reload
	mov	x28, xzr
	lsl	x8, x11, #4
	ldur	x7, [x29, #-120]                // 8-byte Folded Reload
	ldur	x27, [x29, #-104]               // 8-byte Folded Reload
	stp	x11, x8, [x29, #-88]            // 16-byte Folded Spill
.LBB8_42:                               //   Parent Loop BB8_28 Depth=1
                                        //     Parent Loop BB8_41 Depth=2
                                        // =>    This Loop Header: Depth=3
                                        //         Child Loop BB8_43 Depth 4
	ldur	x8, [x29, #-168]                // 8-byte Folded Reload
	mov	x20, xzr
	ldur	x9, [x29, #-80]                 // 8-byte Folded Reload
	ldur	x10, [x29, #-64]                // 8-byte Folded Reload
	add	x8, x28, x8
	mul	x8, x8, x14
	add	x8, x9, x8, lsl #2
	add	x26, x19, x8, lsl #2
	ldur	x8, [x29, #-16]                 // 8-byte Folded Reload
	add	x23, x26, x17, lsl #2
	add	x3, x26, x18, lsl #2
	add	x25, x26, x16, lsl #2
	add	x22, x26, x0, lsl #2
	add	x24, x26, x8, lsl #2
	ldur	x8, [x29, #-24]                 // 8-byte Folded Reload
	add	x11, x26, x2, lsl #2
	add	x12, x26, x14, lsl #2
	ldp	q21, q20, [x26, #32]
	add	x30, x26, x8, lsl #2
	ldur	x8, [x29, #-32]                 // 8-byte Folded Reload
	ldp	q23, q22, [x26]
	add	x4, x26, x8, lsl #2
	ldur	x8, [x29, #-40]                 // 8-byte Folded Reload
	ldr	q0, [x24]
	ldr	q1, [x30]
	add	x21, x26, x8, lsl #2
	ldur	x8, [x29, #-48]                 // 8-byte Folded Reload
	ldr	q2, [x4]
	ldr	q3, [x23]
	add	x9, x26, x8, lsl #2
	add	x8, x26, x1, lsl #2
	ldr	q4, [x21]
	ldr	q6, [x3]
	ldr	q5, [x9]
	ldr	q7, [x25]
	ldr	q16, [x22]
	ldr	q17, [x8]
	ldr	q18, [x11]
	ldr	q19, [x12]
.LBB8_43:                               // %.preheader82.preheader.i335.us
                                        //   Parent Loop BB8_28 Depth=1
                                        //     Parent Loop BB8_41 Depth=2
                                        //       Parent Loop BB8_42 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldp	q26, q27, [x10, #-32]
	ldp	q28, q29, [x10]
	add	x10, x10, x13
	ldr	s24, [x27, x20]
	ldr	s25, [x7, x20]
	ldr	s30, [x6, x20]
	fmla	v23.4s, v26.4s, v24.s[0]
	fmla	v22.4s, v27.4s, v24.s[0]
	fmla	v21.4s, v28.4s, v24.s[0]
	fmla	v20.4s, v29.4s, v24.s[0]
	ldr	s24, [x5, x20]
	fmla	v19.4s, v26.4s, v25.s[0]
	fmla	v18.4s, v27.4s, v25.s[0]
	fmla	v17.4s, v28.4s, v25.s[0]
	fmla	v16.4s, v29.4s, v25.s[0]
	fmla	v7.4s, v26.4s, v30.s[0]
	fmla	v6.4s, v27.4s, v30.s[0]
	fmla	v5.4s, v28.4s, v30.s[0]
	fmla	v4.4s, v29.4s, v30.s[0]
	fmla	v3.4s, v26.4s, v24.s[0]
	fmla	v2.4s, v27.4s, v24.s[0]
	fmla	v1.4s, v28.4s, v24.s[0]
	fmla	v0.4s, v29.4s, v24.s[0]
	add	x20, x20, #4
	cmp	x20, #256
	b.ne	.LBB8_43
// %bb.44:                              // %_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.exit336.us
                                        //   in Loop: Header=BB8_42 Depth=3
	stp	q23, q22, [x26]
	add	x28, x28, #1
	stp	q21, q20, [x26, #32]
	add	x27, x27, x15
	str	q17, [x8]
	mov	x8, x15
	ldur	x8, [x29, #-160]                // 8-byte Folded Reload
	add	x7, x7, x15
	add	x6, x6, x15
	add	x5, x5, x15
	str	q19, [x12]
	cmp	x28, x8
	str	q18, [x11]
	str	q16, [x22]
	str	q7, [x25]
	str	q6, [x3]
	str	q5, [x9]
	str	q4, [x21]
	str	q3, [x23]
	str	q2, [x4]
	str	q1, [x30]
	str	q0, [x24]
	b.ne	.LBB8_42
// %bb.45:                              // %._crit_edge.us585
                                        //   in Loop: Header=BB8_41 Depth=2
	ldur	x8, [x29, #-64]                 // 8-byte Folded Reload
	ldur	x11, [x29, #-88]                // 8-byte Folded Reload
	add	x8, x8, #64
	add	x11, x11, #1
	stur	x8, [x29, #-64]                 // 8-byte Folded Spill
	ldr	x8, [sp, #168]                  // 8-byte Folded Reload
	cmp	x11, x8
	b.ne	.LBB8_41
	b	.LBB8_27
.LBB8_46:
	ldr	x20, [sp, #104]                 // 8-byte Folded Reload
	ldur	x22, [x29, #-112]               // 8-byte Folded Reload
	ldur	x24, [x29, #-72]                // 8-byte Folded Reload
	ldr	x23, [sp, #136]                 // 8-byte Folded Reload
	ldr	x10, [sp, #8]                   // 8-byte Folded Reload
.LBB8_47:                               // %.preheader488
	cmp	x23, #4
	b.lo	.LBB8_108
// %bb.48:                              // %.preheader487.lr.ph
	ldur	x8, [x29, #-56]                 // 8-byte Folded Reload
	cmp	x8, #16
	b.lo	.LBB8_89
// %bb.49:                              // %.preheader487.lr.ph
	and	x11, x20, #0x3f
	cbz	x11, .LBB8_89
// %bb.50:                              // %.preheader487.us.preheader
	ldur	x9, [x29, #-56]                 // 8-byte Folded Reload
	stur	x24, [x29, #-72]                // 8-byte Folded Spill
	stur	x22, [x29, #-112]               // 8-byte Folded Spill
	mov	x12, xzr
	lsl	x17, x20, #2
	lsl	x18, x11, #2
	lsr	x8, x9, #4
	mul	x9, x9, x10
	cmp	x8, #1
	and	x10, x20, #0x7fffffffffffffc0
	csinc	x8, x8, xzr, hi
	stur	x8, [x29, #-32]                 // 8-byte Folded Spill
	ldr	x8, [sp, #16]                   // 8-byte Folded Reload
	cmp	x8, #1
	csinc	x8, x8, xzr, hi
	stur	x8, [x29, #-48]                 // 8-byte Folded Spill
	ldr	x8, [sp, #24]                   // 8-byte Folded Reload
	add	x8, x8, x9, lsl #8
	stur	x8, [x29, #-64]                 // 8-byte Folded Spill
	ldr	x8, [sp, #112]                  // 8-byte Folded Reload
	add	x8, x8, x10, lsl #2
	stur	x8, [x29, #-24]                 // 8-byte Folded Spill
	lsl	x8, x20, #4
	stur	x8, [x29, #-80]                 // 8-byte Folded Spill
.LBB8_51:                               // %.preheader487.us
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB8_52 Depth 2
                                        //       Child Loop BB8_53 Depth 3
                                        //         Child Loop BB8_54 Depth 4
                                        //         Child Loop BB8_56 Depth 4
                                        //         Child Loop BB8_58 Depth 4
                                        //         Child Loop BB8_60 Depth 4
                                        //         Child Loop BB8_62 Depth 4
                                        //         Child Loop BB8_64 Depth 4
                                        //         Child Loop BB8_66 Depth 4
                                        //         Child Loop BB8_68 Depth 4
                                        //         Child Loop BB8_70 Depth 4
                                        //         Child Loop BB8_72 Depth 4
                                        //         Child Loop BB8_74 Depth 4
                                        //         Child Loop BB8_76 Depth 4
                                        //         Child Loop BB8_78 Depth 4
                                        //         Child Loop BB8_80 Depth 4
                                        //         Child Loop BB8_82 Depth 4
                                        //         Child Loop BB8_84 Depth 4
	mov	x9, xzr
	lsl	x0, x12, #2
	ldur	x1, [x29, #-64]                 // 8-byte Folded Reload
	stur	x12, [x29, #-40]                // 8-byte Folded Spill
.LBB8_52:                               // %.preheader486.us599
                                        //   Parent Loop BB8_51 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB8_53 Depth 3
                                        //         Child Loop BB8_54 Depth 4
                                        //         Child Loop BB8_56 Depth 4
                                        //         Child Loop BB8_58 Depth 4
                                        //         Child Loop BB8_60 Depth 4
                                        //         Child Loop BB8_62 Depth 4
                                        //         Child Loop BB8_64 Depth 4
                                        //         Child Loop BB8_66 Depth 4
                                        //         Child Loop BB8_68 Depth 4
                                        //         Child Loop BB8_70 Depth 4
                                        //         Child Loop BB8_72 Depth 4
                                        //         Child Loop BB8_74 Depth 4
                                        //         Child Loop BB8_76 Depth 4
                                        //         Child Loop BB8_78 Depth 4
                                        //         Child Loop BB8_80 Depth 4
                                        //         Child Loop BB8_82 Depth 4
                                        //         Child Loop BB8_84 Depth 4
	mov	w4, #1
	mov	w5, #2
	mov	w6, #3
	mov	w7, #4
	mov	w25, #5
	mov	w27, #6
	mov	w28, #7
	mov	w30, #8
	mov	w26, #9
	mov	w13, #10
	mov	w16, #11
	mov	w14, #12
	mov	w20, #13
	mov	w12, #14
	mov	w10, #15
	mov	x2, xzr
	lsl	x3, x9, #4
	bfi	x4, x9, #4, #60
	bfi	x5, x9, #4, #60
	bfi	x6, x9, #4, #60
	bfi	x7, x9, #4, #60
	bfi	x25, x9, #4, #60
	bfi	x27, x9, #4, #60
	bfi	x28, x9, #4, #60
	bfi	x30, x9, #4, #60
	bfi	x26, x9, #4, #60
	bfi	x13, x9, #4, #60
	bfi	x16, x9, #4, #60
	bfi	x14, x9, #4, #60
	bfi	x20, x9, #4, #60
	bfi	x12, x9, #4, #60
	bfi	x10, x9, #4, #60
	ldur	x15, [x29, #-24]                // 8-byte Folded Reload
	stur	x9, [x29, #-16]                 // 8-byte Folded Spill
.LBB8_53:                               // %.preheader485.us
                                        //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        // =>    This Loop Header: Depth=3
                                        //         Child Loop BB8_54 Depth 4
                                        //         Child Loop BB8_56 Depth 4
                                        //         Child Loop BB8_58 Depth 4
                                        //         Child Loop BB8_60 Depth 4
                                        //         Child Loop BB8_62 Depth 4
                                        //         Child Loop BB8_64 Depth 4
                                        //         Child Loop BB8_66 Depth 4
                                        //         Child Loop BB8_68 Depth 4
                                        //         Child Loop BB8_70 Depth 4
                                        //         Child Loop BB8_72 Depth 4
                                        //         Child Loop BB8_74 Depth 4
                                        //         Child Loop BB8_76 Depth 4
                                        //         Child Loop BB8_78 Depth 4
                                        //         Child Loop BB8_80 Depth 4
                                        //         Child Loop BB8_82 Depth 4
                                        //         Child Loop BB8_84 Depth 4
	ldur	x21, [x29, #-56]                // 8-byte Folded Reload
	add	x8, x2, x0
	mov	x22, x15
	mov	x24, x1
	ldur	x9, [x29, #-96]                 // 8-byte Folded Reload
	mul	x23, x8, x21
	mov	x21, x11
	add	x8, x23, x3
	ldr	s0, [x19, x8, lsl #2]
.LBB8_54:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x22], #4
	ldr	s2, [x24]
	add	x24, x24, x9
	subs	x21, x21, #1
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x8, lsl #2]
	b.ne	.LBB8_54
// %bb.55:                              // %..loopexit484_crit_edge.us
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x4
	mov	x8, xzr
	mov	w22, #4
	ldr	s0, [x19, x21, lsl #2]
.LBB8_56:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_56
// %bb.57:                              // %..loopexit484_crit_edge.us.1
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x5
	mov	x8, xzr
	mov	w22, #8
	ldr	s0, [x19, x21, lsl #2]
.LBB8_58:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_58
// %bb.59:                              // %..loopexit484_crit_edge.us.2
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x6
	mov	x8, xzr
	mov	w22, #12
	ldr	s0, [x19, x21, lsl #2]
.LBB8_60:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_60
// %bb.61:                              // %..loopexit484_crit_edge.us.3
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x7
	mov	x8, xzr
	mov	w22, #16
	ldr	s0, [x19, x21, lsl #2]
.LBB8_62:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_62
// %bb.63:                              // %..loopexit484_crit_edge.us.4
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x25
	mov	x8, xzr
	mov	w22, #20
	ldr	s0, [x19, x21, lsl #2]
.LBB8_64:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_64
// %bb.65:                              // %..loopexit484_crit_edge.us.5
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x27
	mov	x8, xzr
	mov	w22, #24
	ldr	s0, [x19, x21, lsl #2]
.LBB8_66:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_66
// %bb.67:                              // %..loopexit484_crit_edge.us.6
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x28
	mov	x8, xzr
	mov	w22, #28
	ldr	s0, [x19, x21, lsl #2]
.LBB8_68:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_68
// %bb.69:                              // %..loopexit484_crit_edge.us.7
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x30
	mov	x8, xzr
	mov	w22, #32
	ldr	s0, [x19, x21, lsl #2]
.LBB8_70:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_70
// %bb.71:                              // %..loopexit484_crit_edge.us.8
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x26
	mov	x8, xzr
	mov	w22, #36
	ldr	s0, [x19, x21, lsl #2]
.LBB8_72:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_72
// %bb.73:                              // %..loopexit484_crit_edge.us.9
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x13
	mov	x8, xzr
	mov	w22, #40
	ldr	s0, [x19, x21, lsl #2]
.LBB8_74:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_74
// %bb.75:                              // %..loopexit484_crit_edge.us.10
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x16
	mov	x8, xzr
	mov	w22, #44
	ldr	s0, [x19, x21, lsl #2]
.LBB8_76:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_76
// %bb.77:                              // %..loopexit484_crit_edge.us.11
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x14
	mov	x8, xzr
	mov	w22, #48
	ldr	s0, [x19, x21, lsl #2]
.LBB8_78:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_78
// %bb.79:                              // %..loopexit484_crit_edge.us.12
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x20
	mov	x8, xzr
	mov	w22, #52
	ldr	s0, [x19, x21, lsl #2]
.LBB8_80:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_80
// %bb.81:                              // %..loopexit484_crit_edge.us.13
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x12
	mov	x8, xzr
	mov	w22, #56
	ldr	s0, [x19, x21, lsl #2]
.LBB8_82:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_82
// %bb.83:                              // %..loopexit484_crit_edge.us.14
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x21, x23, x10
	mov	x8, xzr
	mov	w22, #60
	ldr	s0, [x19, x21, lsl #2]
.LBB8_84:                               //   Parent Loop BB8_51 Depth=1
                                        //     Parent Loop BB8_52 Depth=2
                                        //       Parent Loop BB8_53 Depth=3
                                        // =>      This Inner Loop Header: Depth=4
	ldr	s1, [x15, x8]
	add	x8, x8, #4
	ldr	s2, [x1, x22]
	add	x22, x22, x9
	cmp	x18, x8
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x21, lsl #2]
	b.ne	.LBB8_84
// %bb.85:                              // %..loopexit484_crit_edge.us.15
                                        //   in Loop: Header=BB8_53 Depth=3
	add	x2, x2, #1
	add	x15, x15, x17
	cmp	x2, #4
	b.ne	.LBB8_53
// %bb.86:                              // %.split594.us
                                        //   in Loop: Header=BB8_52 Depth=2
	ldur	x9, [x29, #-16]                 // 8-byte Folded Reload
	add	x1, x1, #64
	ldur	x8, [x29, #-32]                 // 8-byte Folded Reload
	add	x9, x9, #1
	cmp	x9, x8
	b.ne	.LBB8_52
// %bb.87:                              // %._crit_edge.split.us601
                                        //   in Loop: Header=BB8_51 Depth=1
	ldur	x8, [x29, #-24]                 // 8-byte Folded Reload
	ldur	x9, [x29, #-80]                 // 8-byte Folded Reload
	ldur	x12, [x29, #-40]                // 8-byte Folded Reload
	add	x8, x8, x9
	add	x12, x12, #1
	stur	x8, [x29, #-24]                 // 8-byte Folded Spill
	ldur	x8, [x29, #-48]                 // 8-byte Folded Reload
	cmp	x12, x8
	b.ne	.LBB8_51
// %bb.88:                              // %.preheader482
	ldr	x8, [sp, #136]                  // 8-byte Folded Reload
	ldr	x20, [sp, #104]                 // 8-byte Folded Reload
	ldur	x22, [x29, #-112]               // 8-byte Folded Reload
	ldur	x24, [x29, #-72]                // 8-byte Folded Reload
	cmp	x8, #4
	b.lo	.LBB8_108
.LBB8_89:                               // %.preheader481.lr.ph
	ldur	x8, [x29, #-56]                 // 8-byte Folded Reload
	ands	x9, x8, #0xf
	b.eq	.LBB8_108
// %bb.90:                              // %.preheader481.preheader
	ldur	x8, [x29, #-56]                 // 8-byte Folded Reload
	mov	x10, xzr
	ldr	x18, [sp, #112]                 // 8-byte Folded Reload
	lsl	x13, x20, #4
	and	x11, x8, #0x7ffffffffffffff0
	ldr	x8, [sp, #16]                   // 8-byte Folded Reload
	add	x15, x18, x20, lsl #2
	add	x16, x18, x20, lsl #3
	cmp	x8, #1
	csinc	x12, x8, xzr, hi
	ldr	x8, [sp, #24]                   // 8-byte Folded Reload
	add	x14, x8, x11, lsl #2
	add	x8, x20, x20, lsl #1
	lsl	x17, x8, #2
.LBB8_91:                               // %.preheader481
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB8_92 Depth 2
                                        //       Child Loop BB8_93 Depth 3
                                        //     Child Loop BB8_96 Depth 2
                                        //       Child Loop BB8_97 Depth 3
                                        //     Child Loop BB8_100 Depth 2
                                        //       Child Loop BB8_101 Depth 3
                                        //     Child Loop BB8_104 Depth 2
                                        //       Child Loop BB8_105 Depth 3
	ldur	x1, [x29, #-56]                 // 8-byte Folded Reload
	lsl	x0, x10, #2
	mov	x8, xzr
	mov	x2, x14
	mul	x1, x0, x1
.LBB8_92:                               // %.preheader478
                                        //   Parent Loop BB8_91 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB8_93 Depth 3
	add	x4, x8, x11
	mov	x3, xzr
	add	x4, x4, x1
	mov	x5, x2
	ldur	x6, [x29, #-96]                 // 8-byte Folded Reload
	ldr	s0, [x19, x4, lsl #2]
.LBB8_93:                               //   Parent Loop BB8_91 Depth=1
                                        //     Parent Loop BB8_92 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x18, x3, lsl #2]
	add	x3, x3, #1
	ldr	s2, [x5]
	add	x5, x5, x6
	cmp	x20, x3
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x4, lsl #2]
	b.ne	.LBB8_93
// %bb.94:                              // %._crit_edge
                                        //   in Loop: Header=BB8_92 Depth=2
	add	x8, x8, #1
	add	x2, x2, #4
	cmp	x8, x9
	b.ne	.LBB8_92
// %bb.95:                              // %..loopexit480_crit_edge
                                        //   in Loop: Header=BB8_91 Depth=1
	ldur	x2, [x29, #-56]                 // 8-byte Folded Reload
	orr	x1, x0, #0x1
	mov	x8, xzr
	mul	x1, x1, x2
	mov	x2, x14
.LBB8_96:                               // %.preheader478.1
                                        //   Parent Loop BB8_91 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB8_97 Depth 3
	add	x4, x8, x11
	mov	x3, xzr
	add	x4, x4, x1
	mov	x5, x2
	ldur	x6, [x29, #-96]                 // 8-byte Folded Reload
	ldr	s0, [x19, x4, lsl #2]
.LBB8_97:                               //   Parent Loop BB8_91 Depth=1
                                        //     Parent Loop BB8_96 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x15, x3, lsl #2]
	add	x3, x3, #1
	ldr	s2, [x5]
	add	x5, x5, x6
	cmp	x20, x3
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x4, lsl #2]
	b.ne	.LBB8_97
// %bb.98:                              // %._crit_edge.1
                                        //   in Loop: Header=BB8_96 Depth=2
	add	x8, x8, #1
	add	x2, x2, #4
	cmp	x8, x9
	b.ne	.LBB8_96
// %bb.99:                              // %..loopexit480_crit_edge.1
                                        //   in Loop: Header=BB8_91 Depth=1
	ldur	x2, [x29, #-56]                 // 8-byte Folded Reload
	orr	x1, x0, #0x2
	mov	x8, xzr
	mul	x1, x1, x2
	mov	x2, x14
.LBB8_100:                              // %.preheader478.2
                                        //   Parent Loop BB8_91 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB8_101 Depth 3
	add	x4, x8, x11
	mov	x3, xzr
	add	x4, x4, x1
	mov	x5, x2
	ldur	x6, [x29, #-96]                 // 8-byte Folded Reload
	ldr	s0, [x19, x4, lsl #2]
.LBB8_101:                              //   Parent Loop BB8_91 Depth=1
                                        //     Parent Loop BB8_100 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x16, x3, lsl #2]
	add	x3, x3, #1
	ldr	s2, [x5]
	add	x5, x5, x6
	cmp	x20, x3
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x4, lsl #2]
	b.ne	.LBB8_101
// %bb.102:                             // %._crit_edge.2
                                        //   in Loop: Header=BB8_100 Depth=2
	add	x8, x8, #1
	add	x2, x2, #4
	cmp	x8, x9
	b.ne	.LBB8_100
// %bb.103:                             // %..loopexit480_crit_edge.2
                                        //   in Loop: Header=BB8_91 Depth=1
	ldur	x1, [x29, #-56]                 // 8-byte Folded Reload
	orr	x0, x0, #0x3
	mov	x8, xzr
	mul	x0, x0, x1
	mov	x1, x14
.LBB8_104:                              // %.preheader478.3
                                        //   Parent Loop BB8_91 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB8_105 Depth 3
	add	x2, x8, x11
	mov	x3, x17
	add	x2, x2, x0
	mov	x4, x1
	mov	x5, x20
	ldur	x6, [x29, #-96]                 // 8-byte Folded Reload
	ldr	s0, [x19, x2, lsl #2]
.LBB8_105:                              //   Parent Loop BB8_91 Depth=1
                                        //     Parent Loop BB8_104 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	ldr	s1, [x18, x3]
	subs	x5, x5, #1
	ldr	s2, [x4]
	add	x4, x4, x6
	add	x3, x3, #4
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x2, lsl #2]
	b.ne	.LBB8_105
// %bb.106:                             // %._crit_edge.3
                                        //   in Loop: Header=BB8_104 Depth=2
	add	x8, x8, #1
	add	x1, x1, #4
	cmp	x8, x9
	b.ne	.LBB8_104
// %bb.107:                             // %..loopexit480_crit_edge.3
                                        //   in Loop: Header=BB8_91 Depth=1
	add	x10, x10, #1
	add	x18, x18, x13
	add	x15, x15, x13
	add	x16, x16, x13
	cmp	x10, x12
	b.ne	.LBB8_91
.LBB8_108:                              // %._crit_edge612
	ldr	x9, [sp, #136]                  // 8-byte Folded Reload
	ldr	x18, [sp, #24]                  // 8-byte Folded Reload
	ldur	x11, [x29, #-56]                // 8-byte Folded Reload
	ands	x8, x9, #0x3
	b.eq	.LBB8_123
// %bb.109:                             // %.preheader476.lr.ph
	and	x9, x9, #0x7ffffffffffffffc
	ldr	x13, [sp, #112]                 // 8-byte Folded Reload
	mov	x10, xzr
	ldur	x0, [x29, #-96]                 // 8-byte Folded Reload
	mul	x12, x9, x20
	mul	x11, x9, x11
	add	x12, x13, x12, lsl #2
	mov	x13, x18
.LBB8_110:                              // %.preheader
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB8_111 Depth 2
	add	x14, x10, x11
	mov	x15, x20
	mov	x16, x12
	mov	x17, x13
	ldr	s0, [x19, x14, lsl #2]
.LBB8_111:                              //   Parent Loop BB8_110 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	ldr	s1, [x16], #4
	ldr	s2, [x17]
	add	x17, x17, x0
	subs	x15, x15, #1
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x14, lsl #2]
	b.ne	.LBB8_111
// %bb.112:                             // %._crit_edge614
                                        //   in Loop: Header=BB8_110 Depth=1
	ldur	x14, [x29, #-56]                // 8-byte Folded Reload
	add	x10, x10, #1
	add	x13, x13, #4
	cmp	x10, x14
	b.ne	.LBB8_110
// %bb.113:                             // %._crit_edge616
	cmp	x8, #1
	b.eq	.LBB8_123
// %bb.114:                             // %.preheader476.1
	orr	x11, x9, #0x1
	ldr	x13, [sp, #112]                 // 8-byte Folded Reload
	mov	x10, xzr
	ldur	x0, [x29, #-96]                 // 8-byte Folded Reload
	mul	x12, x11, x20
	mul	x11, x11, x14
	add	x12, x13, x12, lsl #2
	mov	x13, x18
.LBB8_115:                              // %.preheader.1
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB8_116 Depth 2
	add	x14, x10, x11
	mov	x15, x12
	mov	x16, x13
	mov	x17, x20
	ldr	s0, [x19, x14, lsl #2]
.LBB8_116:                              //   Parent Loop BB8_115 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	ldr	s1, [x15], #4
	ldr	s2, [x16]
	subs	x17, x17, #1
	add	x16, x16, x0
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x14, lsl #2]
	b.ne	.LBB8_116
// %bb.117:                             // %._crit_edge614.1
                                        //   in Loop: Header=BB8_115 Depth=1
	ldur	x15, [x29, #-56]                // 8-byte Folded Reload
	add	x10, x10, #1
	add	x13, x13, #4
	cmp	x10, x15
	b.ne	.LBB8_115
// %bb.118:                             // %._crit_edge616.1
	cmp	x8, #2
	b.eq	.LBB8_123
// %bb.119:                             // %.preheader476.2
	orr	x9, x9, #0x2
	ldr	x11, [sp, #112]                 // 8-byte Folded Reload
	mov	x8, xzr
	ldur	x16, [x29, #-96]                // 8-byte Folded Reload
	mul	x10, x9, x20
	mul	x9, x9, x15
	add	x10, x11, x10, lsl #2
.LBB8_120:                              // %.preheader.2
                                        // =>This Loop Header: Depth=1
                                        //     Child Loop BB8_121 Depth 2
	add	x11, x8, x9
	mov	x12, x10
	mov	x13, x18
	mov	x14, x20
	ldr	s0, [x19, x11, lsl #2]
.LBB8_121:                              //   Parent Loop BB8_120 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	ldr	s1, [x12], #4
	ldr	s2, [x13]
	subs	x14, x14, #1
	add	x13, x13, x16
	fmadd	s0, s2, s1, s0
	str	s0, [x19, x11, lsl #2]
	b.ne	.LBB8_121
// %bb.122:                             // %._crit_edge614.2
                                        //   in Loop: Header=BB8_120 Depth=1
	add	x8, x8, #1
	add	x18, x18, #4
	cmp	x8, x15
	b.ne	.LBB8_120
.LBB8_123:                              // %.loopexit
	mov	x0, x22
	bl	free
	mov	x0, x24
	ldp	x20, x19, [sp, #464]            // 16-byte Folded Reload
	ldp	x22, x21, [sp, #448]            // 16-byte Folded Reload
	ldp	x24, x23, [sp, #432]            // 16-byte Folded Reload
	ldp	x26, x25, [sp, #416]            // 16-byte Folded Reload
	ldp	x28, x27, [sp, #400]            // 16-byte Folded Reload
	ldp	x29, x30, [sp, #384]            // 16-byte Folded Reload
	add	sp, sp, #480
	b	free
.Lfunc_end8:
	.size	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_, .Lfunc_end8-_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	.cfi_endproc
                                        // -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3                               // -- Begin function main
.LCPI9_0:
	.xword	0x3e7ad7f29abcaf49              // double 1.0000000000000001E-7
.LCPI9_1:
	.xword	0x3eb0c6f7a0b5ed8d              // double 9.9999999999999995E-7
	.text
	.globl	main
	.p2align	2
	.type	main,@function
main:                                   // @main
.Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 156, DW.ref.__gxx_personality_v0
	.cfi_lsda 28, .Lexception0
// %bb.0:
	sub	sp, sp, #192
	stp	d11, d10, [sp, #80]             // 16-byte Folded Spill
	stp	d9, d8, [sp, #96]               // 16-byte Folded Spill
	stp	x29, x30, [sp, #112]            // 16-byte Folded Spill
	add	x29, sp, #112
	str	x25, [sp, #128]                 // 8-byte Folded Spill
	stp	x24, x23, [sp, #144]            // 16-byte Folded Spill
	stp	x22, x21, [sp, #160]            // 16-byte Folded Spill
	stp	x20, x19, [sp, #176]            // 16-byte Folded Spill
	.cfi_def_cfa w29, 80
	.cfi_offset w19, -8
	.cfi_offset w20, -16
	.cfi_offset w21, -24
	.cfi_offset w22, -32
	.cfi_offset w23, -40
	.cfi_offset w24, -48
	.cfi_offset w25, -64
	.cfi_offset w30, -72
	.cfi_offset w29, -80
	.cfi_offset b8, -88
	.cfi_offset b9, -96
	.cfi_offset b10, -104
	.cfi_offset b11, -112
	cmp	w0, #2
	b.ne	.LBB9_8
// %bb.1:
	ldr	x0, [x1, #8]
	mov	x1, xzr
	mov	w2, #10
	bl	strtol
	mov	x22, x0
	cmp	w22, #0
	b.le	.LBB9_9
// %bb.2:
	and	x20, x22, #0xffffffff
	add	x0, sp, #56
	mov	x1, x20
	mov	x2, x20
	bl	_ZL10gen_matrixll
.Ltmp0:
	add	x0, sp, #32
	mov	x1, x20
	mov	x2, x20
	bl	_ZL10gen_matrixll
.Ltmp1:
// %bb.3:
.Ltmp3:
	add	x0, sp, #8
	mov	x1, x20
	mov	x2, x20
	bl	_ZL10gen_matrixll
.Ltmp4:
// %bb.4:
	ldp	x19, x8, [sp, #8]
	subs	x23, x8, x19
	b.eq	.LBB9_11
// %bb.5:
	mov	x8, #-3
	movk	x8, #32767, lsl #48
	cmp	x23, x8
	b.hs	.LBB9_22
// %bb.6:                               // %_ZNSt16allocator_traitsISaIfEE8allocateERS0_m.exit.i.i.i.i
.Ltmp6:
	mov	x0, x23
	bl	_Znwm
.Ltmp7:
// %bb.7:
	mov	x1, x19
	mov	x2, x23
	mov	x21, x0
	bl	memmove
	b	.LBB9_12
.LBB9_8:
	adrp	x0, .L.str
	ldr	x1, [x1]
	add	x0, x0, :lo12:.L.str
	bl	printf
	b	.LBB9_10
.LBB9_9:
	adrp	x0, .Lstr.4
	add	x0, x0, :lo12:.Lstr.4
	bl	puts
.LBB9_10:
	mov	w0, #1
	b	.LBB9_21
.LBB9_11:
	mov	x21, xzr
.LBB9_12:                               // %.thread
	adrp	x0, .Lstr
	add	x0, x0, :lo12:.Lstr
	bl	puts
	adrp	x0, .L.str.3
	mov	w1, w22
	add	x0, x0, :lo12:.L.str.3
	mov	w2, w22
	bl	printf
	mul	x25, x20, x20
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	ldr	x22, [sp, #56]
	mov	x1, x20
	ldr	x23, [sp, #32]
	mov	x2, x20
	mov	x3, x20
	mov	x6, x19
	mov	x4, x22
	mov	x24, x0
	mov	x5, x23
	bl	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	mul	x8, x25, x20
	lsl	x25, x8, #1
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	sub	x8, x0, x24
	adrp	x9, .LCPI9_0
	adrp	x24, .Lstr.3
	add	x24, x24, :lo12:.Lstr.3
	scvtf	d0, x8
	ldr	d9, [x9, :lo12:.LCPI9_0]
	mov	x0, x24
	fmul	d8, d0, d9
	bl	puts
	adrp	x8, .LCPI9_1
	scvtf	d0, x25
	fmov	d11, #6.25000000
	adrp	x0, .L.str.5
	add	x0, x0, :lo12:.L.str.5
	ldr	d1, [x8, :lo12:.LCPI9_1]
	fmul	d10, d0, d1
	fmov	d0, d8
	fdiv	d1, d10, d8
	fmul	d2, d1, d11
	bl	printf
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	mov	x25, x0
	bl	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	mov	x1, x20
	mov	x2, x20
	mov	x3, x20
	mov	x4, x22
	mov	x5, x23
	mov	x6, x19
	bl	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	sub	x8, x0, x25
	mov	x0, x24
	scvtf	d0, x8
	fmul	d8, d0, d9
	bl	puts
	fdiv	d1, d10, d8
	adrp	x0, .L.str.6
	fmov	d0, d8
	add	x0, x0, :lo12:.L.str.6
	fmul	d2, d1, d11
	bl	printf
	mov	x0, x24
	bl	puts
	cbz	x21, .LBB9_14
// %bb.13:
	mov	x0, x21
	bl	_ZdlPv
.LBB9_14:                               // %_ZNSt6vectorIfSaIfEED2Ev.exit
	cbz	x19, .LBB9_16
// %bb.15:
	mov	x0, x19
	bl	_ZdlPv
.LBB9_16:                               // %_ZNSt6vectorIfSaIfEED2Ev.exit110
	cbz	x23, .LBB9_18
// %bb.17:
	mov	x0, x23
	bl	_ZdlPv
.LBB9_18:                               // %_ZNSt6vectorIfSaIfEED2Ev.exit112
	cbz	x22, .LBB9_20
// %bb.19:
	mov	x0, x22
	bl	_ZdlPv
.LBB9_20:                               // %_ZNSt6vectorIfSaIfEED2Ev.exit114
	mov	w0, wzr
.LBB9_21:
	ldp	x20, x19, [sp, #176]            // 16-byte Folded Reload
	ldp	x22, x21, [sp, #160]            // 16-byte Folded Reload
	ldp	x24, x23, [sp, #144]            // 16-byte Folded Reload
	ldp	x29, x30, [sp, #112]            // 16-byte Folded Reload
	ldp	d9, d8, [sp, #96]               // 16-byte Folded Reload
	ldp	d11, d10, [sp, #80]             // 16-byte Folded Reload
	ldr	x25, [sp, #128]                 // 8-byte Folded Reload
	add	sp, sp, #192
	ret
.LBB9_22:                               // %.noexc.i.i
.Ltmp8:
	bl	_ZSt28__throw_bad_array_new_lengthv
.Ltmp9:
// %bb.23:                              // %.noexc
.LBB9_24:
.Ltmp5:
	mov	x20, x0
	ldr	x0, [sp, #32]
	cbz	x0, .LBB9_28
	b	.LBB9_31
.LBB9_25:
.Ltmp2:
	mov	x20, x0
	ldr	x0, [sp, #56]
	cbz	x0, .LBB9_29
	b	.LBB9_32
.LBB9_26:                               // %_ZNSt6vectorIfSaIfEED2Ev.exit116
.Ltmp10:
	mov	x20, x0
	cbnz	x19, .LBB9_30
// %bb.27:                              // %_ZNSt6vectorIfSaIfEED2Ev.exit118
	ldr	x0, [sp, #32]
	cbnz	x0, .LBB9_31
.LBB9_28:                               // %_ZNSt6vectorIfSaIfEED2Ev.exit120
	ldr	x0, [sp, #56]
	cbnz	x0, .LBB9_32
.LBB9_29:                               // %_ZNSt6vectorIfSaIfEED2Ev.exit122
	mov	x0, x20
	bl	_Unwind_Resume
.LBB9_30:
	mov	x0, x19
	bl	_ZdlPv
	ldr	x0, [sp, #32]
	cbz	x0, .LBB9_28
.LBB9_31:
	bl	_ZdlPv
	ldr	x0, [sp, #56]
	cbz	x0, .LBB9_29
.LBB9_32:
	bl	_ZdlPv
	mov	x0, x20
	bl	_Unwind_Resume
.Lfunc_end9:
	.size	main, .Lfunc_end9-main
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table9:
.Lexception0:
	.byte	255                             // @LPStart Encoding = omit
	.byte	255                             // @TType Encoding = omit
	.byte	1                               // Call site Encoding = uleb128
	.uleb128 .Lcst_end0-.Lcst_begin0
.Lcst_begin0:
	.uleb128 .Lfunc_begin0-.Lfunc_begin0    // >> Call Site 1 <<
	.uleb128 .Ltmp0-.Lfunc_begin0           //   Call between .Lfunc_begin0 and .Ltmp0
	.byte	0                               //     has no landing pad
	.byte	0                               //   On action: cleanup
	.uleb128 .Ltmp0-.Lfunc_begin0           // >> Call Site 2 <<
	.uleb128 .Ltmp1-.Ltmp0                  //   Call between .Ltmp0 and .Ltmp1
	.uleb128 .Ltmp2-.Lfunc_begin0           //     jumps to .Ltmp2
	.byte	0                               //   On action: cleanup
	.uleb128 .Ltmp3-.Lfunc_begin0           // >> Call Site 3 <<
	.uleb128 .Ltmp4-.Ltmp3                  //   Call between .Ltmp3 and .Ltmp4
	.uleb128 .Ltmp5-.Lfunc_begin0           //     jumps to .Ltmp5
	.byte	0                               //   On action: cleanup
	.uleb128 .Ltmp6-.Lfunc_begin0           // >> Call Site 4 <<
	.uleb128 .Ltmp7-.Ltmp6                  //   Call between .Ltmp6 and .Ltmp7
	.uleb128 .Ltmp10-.Lfunc_begin0          //     jumps to .Ltmp10
	.byte	0                               //   On action: cleanup
	.uleb128 .Ltmp7-.Lfunc_begin0           // >> Call Site 5 <<
	.uleb128 .Ltmp8-.Ltmp7                  //   Call between .Ltmp7 and .Ltmp8
	.byte	0                               //     has no landing pad
	.byte	0                               //   On action: cleanup
	.uleb128 .Ltmp8-.Lfunc_begin0           // >> Call Site 6 <<
	.uleb128 .Ltmp9-.Ltmp8                  //   Call between .Ltmp8 and .Ltmp9
	.uleb128 .Ltmp10-.Lfunc_begin0          //     jumps to .Ltmp10
	.byte	0                               //   On action: cleanup
	.uleb128 .Ltmp9-.Lfunc_begin0           // >> Call Site 7 <<
	.uleb128 .Lfunc_end9-.Ltmp9             //   Call between .Ltmp9 and .Lfunc_end9
	.byte	0                               //     has no landing pad
	.byte	0                               //   On action: cleanup
.Lcst_end0:
	.p2align	2
                                        // -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4                               // -- Begin function _ZL10gen_matrixll
.LCPI10_0:
	.xword	0x0000000000000000              // fp128 4294967296
	.xword	0x401f000000000000
.LCPI10_1:
	.xword	0x0000000000000000              // fp128 2
	.xword	0x4000000000000000
	.text
	.p2align	2
	.type	_ZL10gen_matrixll,@function
_ZL10gen_matrixll:                      // @_ZL10gen_matrixll
.Lfunc_begin1:
	.cfi_startproc
	.cfi_personality 156, DW.ref.__gxx_personality_v0
	.cfi_lsda 28, .Lexception1
// %bb.0:
	sub	sp, sp, #192
	stp	d9, d8, [sp, #80]               // 16-byte Folded Spill
	stp	x29, x30, [sp, #96]             // 16-byte Folded Spill
	add	x29, sp, #96
	stp	x28, x27, [sp, #112]            // 16-byte Folded Spill
	stp	x26, x25, [sp, #128]            // 16-byte Folded Spill
	stp	x24, x23, [sp, #144]            // 16-byte Folded Spill
	stp	x22, x21, [sp, #160]            // 16-byte Folded Spill
	stp	x20, x19, [sp, #176]            // 16-byte Folded Spill
	.cfi_def_cfa w29, 96
	.cfi_offset w19, -8
	.cfi_offset w20, -16
	.cfi_offset w21, -24
	.cfi_offset w22, -32
	.cfi_offset w23, -40
	.cfi_offset w24, -48
	.cfi_offset w25, -56
	.cfi_offset w26, -64
	.cfi_offset w27, -72
	.cfi_offset w28, -80
	.cfi_offset w30, -88
	.cfi_offset w29, -96
	.cfi_offset b8, -104
	.cfi_offset b9, -112
	adrp	x8, .L_MergedGlobals
	mov	x19, x2
	add	x8, x8, :lo12:.L_MergedGlobals
	mov	x21, x1
	mov	x20, x0
	ldarb	w8, [x8]
	tbz	w8, #0, .LBB10_21
.LBB10_1:
	adrp	x8, .L_MergedGlobals+8
	add	x8, x8, :lo12:.L_MergedGlobals+8
	ldarb	w8, [x8]
	tbz	w8, #0, .LBB10_24
.LBB10_2:
	mul	x22, x19, x21
	lsr	x8, x22, #61
	cbnz	x8, .LBB10_29
// %bb.3:                               // %_ZNSt6vectorIfSaIfEE17_S_check_init_lenEmRKS0_.exit.i
	stp	xzr, xzr, [x20]
	str	xzr, [x20, #16]
	cbz	x22, .LBB10_6
// %bb.4:                               // %.noexc11
	lsl	x21, x22, #2
	mov	x0, x21
	bl	_Znwm
	mov	x19, x0
	add	x8, x0, x21
	cmp	x22, #1
	str	x0, [x20]
	str	wzr, [x0], #4
	str	x8, [x20, #16]
	b.ne	.LBB10_7
// %bb.5:                               // %.thread21
	mov	x8, x0
	str	x0, [x20, #8]
	b	.LBB10_8
.LBB10_6:                               // %.thread
	stp	xzr, xzr, [x20]
	str	xzr, [x20, #16]
	b	.LBB10_20
.LBB10_7:
	sub	x2, x21, #4
	mov	w1, wzr
	mov	x21, x8
	bl	memset
	mov	x8, x21
	cmp	x21, x19
	str	x21, [x20, #8]
	b.eq	.LBB10_20
.LBB10_8:                               // %.lr.ph.i
	stur	x8, [x29, #-24]                 // 8-byte Folded Spill
	adrp	x8, .LCPI10_0
	mov	w20, #45279
	movk	w20, #39176, lsl #16
	ldr	q0, [x8, :lo12:.LCPI10_0]
	bl	logl
	adrp	x8, .LCPI10_1
	str	q0, [sp, #48]                   // 16-byte Folded Spill
	ldr	q0, [x8, :lo12:.LCPI10_1]
	bl	logl
	mov	v1.16b, v0.16b
	ldr	q0, [sp, #48]                   // 16-byte Folded Reload
	bl	__divtf3
	bl	__fixunstfdi
	add	x9, x0, #52
	adrp	x8, _ZZL10gen_matrixllE3rng+4992
	mov	x10, #-2147483648
	mov	w23, #2147483646
	udiv	x9, x9, x0
	mov	w24, #1
	adrp	x21, _ZZL10gen_matrixllE3rng
	mov	w25, #22144
	adrp	x22, _ZZL10gen_matrixllE3rng+1792
	ldur	x17, [x29, #-24]                // 8-byte Folded Reload
	add	x21, x21, :lo12:_ZZL10gen_matrixllE3rng
	movk	w25, #40236, lsl #16
	mov	w26, #-272236544
	mov	x27, #4751297606875873280
	ldr	x28, [x8, :lo12:_ZZL10gen_matrixllE3rng+4992]
	fmov	d8, #1.00000000
	cmp	x9, #1
	fmov	d9, #-1.00000000
	csinc	x18, x9, xzr, hi
	add	x22, x22, :lo12:_ZZL10gen_matrixllE3rng+1792
	dup	v17.2d, x10
	dup	v18.2d, x23
	dup	v19.2d, x24
.LBB10_9:                               // =>This Loop Header: Depth=1
                                        //     Child Loop BB10_11 Depth 2
                                        //       Child Loop BB10_13 Depth 3
                                        //       Child Loop BB10_15 Depth 3
	movi	d0, #0000000000000000
	mov	x8, x18
	fmov	d1, #1.00000000
	b	.LBB10_11
.LBB10_10:                              // %_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv.exit.i
                                        //   in Loop: Header=BB10_11 Depth=2
	mov	x9, x28
	add	x28, x28, #1
	fmov	d3, x27
	subs	x8, x8, #1
	str	x28, [x21, #4992]
	ldr	x9, [x21, x9, lsl #3]
	ubfx	x10, x9, #11, #32
	eor	x9, x10, x9
	lsl	w10, w9, #7
	and	x10, x10, x25
	eor	x9, x10, x9
	lsl	w10, w9, #15
	and	x10, x10, x26
	eor	x9, x10, x9
	eor	x9, x9, x9, lsr #18
	ucvtf	d2, x9
	fmadd	d0, d1, d2, d0
	fmul	d1, d1, d3
	b.eq	.LBB10_17
.LBB10_11:                              // %select.unfold.i.i.i.i.i.i
                                        //   Parent Loop BB10_9 Depth=1
                                        // =>  This Loop Header: Depth=2
                                        //       Child Loop BB10_13 Depth 3
                                        //       Child Loop BB10_15 Depth 3
	cmp	x28, #624
	b.lo	.LBB10_10
// %bb.12:                              // %vector.ph33
                                        //   in Loop: Header=BB10_11 Depth=2
	ld1r	{ v2.2d }, [x21]
	mov	x9, xzr
.LBB10_13:                              // %vector.body32
                                        //   Parent Loop BB10_9 Depth=1
                                        //     Parent Loop BB10_11 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	add	x10, x21, x9
	add	x9, x9, #32
	mov	v3.16b, v2.16b
	add	x11, x10, #3176
	add	x12, x10, #3192
	cmp	x9, #1792
	ldur	q4, [x10, #8]
	ldur	q2, [x10, #24]
	ldr	q16, [x11]
	ext	v3.16b, v3.16b, v4.16b, #8
	ext	v5.16b, v4.16b, v2.16b, #8
	and	v6.16b, v4.16b, v18.16b
	and	v7.16b, v2.16b, v18.16b
	and	v3.16b, v3.16b, v17.16b
	and	v5.16b, v5.16b, v17.16b
	and	v4.16b, v4.16b, v19.16b
	orr	v3.16b, v6.16b, v3.16b
	ldr	q6, [x12]
	orr	v5.16b, v7.16b, v5.16b
	and	v7.16b, v2.16b, v19.16b
	cmeq	v4.2d, v4.2d, #0
	ushr	v3.2d, v3.2d, #1
	ushr	v5.2d, v5.2d, #1
	cmeq	v7.2d, v7.2d, #0
	eor	v3.16b, v3.16b, v16.16b
	dup	v16.2d, x20
	eor	v5.16b, v5.16b, v6.16b
	bic	v4.16b, v16.16b, v4.16b
	bic	v6.16b, v16.16b, v7.16b
	eor	v3.16b, v3.16b, v4.16b
	eor	v4.16b, v5.16b, v6.16b
	stp	q3, q4, [x10]
	b.ne	.LBB10_13
// %bb.14:                              // %vector.ph
                                        //   in Loop: Header=BB10_11 Depth=2
	ldp	x10, x12, [x22, #8]
	mov	x11, v2.d[1]
	mov	x9, xzr
	ldr	x13, [x22, #3176]
	and	x14, x10, #0x7ffffffe
	and	x15, x10, #0xffffffff80000000
	and	x16, x12, #0x7ffffffe
	and	x11, x11, #0xffffffff80000000
	orr	x15, x16, x15
	ldr	x16, [x22, #3184]
	orr	x11, x14, x11
	ldr	x14, [x22, #24]
	sbfx	x10, x10, #0, #1
	and	x10, x10, x20
	eor	x11, x13, x11, lsr #1
	eor	x13, x16, x15, lsr #1
	eor	x10, x11, x10
	sbfx	x11, x12, #0, #1
	and	x12, x12, #0xffffffff80000000
	and	x15, x14, #0x7ffffffe
	ldr	x16, [x22, #3192]
	orr	x12, x15, x12
	and	x11, x11, x20
	eor	x11, x13, x11
	sbfx	x13, x14, #0, #1
	eor	x12, x16, x12, lsr #1
	and	x13, x13, x20
	eor	x12, x12, x13
	dup	v2.2d, x14
	stp	x10, x11, [x22]
	str	x12, [x22, #16]
.LBB10_15:                              // %vector.body
                                        //   Parent Loop BB10_9 Depth=1
                                        //     Parent Loop BB10_11 Depth=2
                                        // =>    This Inner Loop Header: Depth=3
	add	x10, x21, x9
	dup	v4.2d, x23
	dup	v5.2d, x24
	dup	v6.2d, x20
	add	x9, x9, #16
	ldr	q3, [x10, #1824]
	cmp	x9, #3168
	ext	v2.16b, v2.16b, v3.16b, #8
	and	v4.16b, v3.16b, v4.16b
	and	v2.16b, v2.16b, v17.16b
	orr	v2.16b, v4.16b, v2.16b
	and	v4.16b, v3.16b, v5.16b
	ldr	q5, [x10]
	add	x10, x10, #1816
	ushr	v2.2d, v2.2d, #1
	cmeq	v4.2d, v4.2d, #0
	eor	v2.16b, v2.16b, v5.16b
	bic	v4.16b, v6.16b, v4.16b
	eor	v4.16b, v2.16b, v4.16b
	mov	v2.16b, v3.16b
	str	q4, [x10]
	b.ne	.LBB10_15
// %bb.16:                              // %_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv.exit.i.i
                                        //   in Loop: Header=BB10_11 Depth=2
	ldr	x9, [x21, #4984]
	mov	x28, xzr
	ldr	x10, [x21]
	ldr	x12, [x21, #3168]
	and	x9, x9, #0xffffffff80000000
	and	x11, x10, #0x7ffffffe
	sbfx	x10, x10, #0, #1
	orr	x9, x11, x9
	and	x10, x10, x20
	eor	x9, x12, x9, lsr #1
	eor	x9, x9, x10
	str	x9, [x21, #4984]
	b	.LBB10_10
.LBB10_17:                              //   in Loop: Header=BB10_9 Depth=1
	fdiv	d0, d0, d1
	fcmp	d0, d8
	b.ge	.LBB10_19
// %bb.18:                              // %"_ZZL10gen_matrixllENK3$_0clEv.exit.i"
                                        //   in Loop: Header=BB10_9 Depth=1
	fadd	d1, d0, d9
	fadd	d0, d0, d1
	fcvt	s0, d0
	str	s0, [x19], #4
	cmp	x19, x17
	b.ne	.LBB10_9
	b	.LBB10_20
.LBB10_19:                              //   in Loop: Header=BB10_9 Depth=1
	movi	d1, #0000000000000000
	fmov	d0, #1.00000000
	str	q17, [sp, #48]                  // 16-byte Folded Spill
	str	x18, [sp, #40]                  // 8-byte Folded Spill
	stp	q19, q18, [sp]                  // 32-byte Folded Spill
	bl	nextafter
	ldp	q19, q18, [sp]                  // 32-byte Folded Reload
	ldr	x18, [sp, #40]                  // 8-byte Folded Reload
	ldr	q17, [sp, #48]                  // 16-byte Folded Reload
	ldur	x17, [x29, #-24]                // 8-byte Folded Reload
	fadd	d1, d0, d9
	fadd	d0, d0, d1
	fcvt	s0, d0
	str	s0, [x19], #4
	cmp	x19, x17
	b.ne	.LBB10_9
.LBB10_20:                              // %"_ZSt8generateIN9__gnu_cxx17__normal_iteratorIPfSt6vectorIfSaIfEEEEZL10gen_matrixllE3$_0EvT_S8_T0_.exit"
	ldp	x20, x19, [sp, #176]            // 16-byte Folded Reload
	ldp	x22, x21, [sp, #160]            // 16-byte Folded Reload
	ldp	x24, x23, [sp, #144]            // 16-byte Folded Reload
	ldp	x26, x25, [sp, #128]            // 16-byte Folded Reload
	ldp	x28, x27, [sp, #112]            // 16-byte Folded Reload
	ldp	x29, x30, [sp, #96]             // 16-byte Folded Reload
	ldp	d9, d8, [sp, #80]               // 16-byte Folded Reload
	add	sp, sp, #192
	ret
.LBB10_21:
	adrp	x0, .L_MergedGlobals
	add	x0, x0, :lo12:.L_MergedGlobals
	bl	__cxa_guard_acquire
	cbz	w0, .LBB10_1
// %bb.22:
.Ltmp11:
	adrp	x0, _ZZL10gen_matrixllE2rd
	add	x0, x0, :lo12:_ZZL10gen_matrixllE2rd
	bl	_ZNSt13random_deviceC2Ev
.Ltmp12:
// %bb.23:
	adrp	x0, _ZNSt13random_deviceD2Ev
	adrp	x1, _ZZL10gen_matrixllE2rd
	adrp	x2, __dso_handle
	add	x0, x0, :lo12:_ZNSt13random_deviceD2Ev
	add	x1, x1, :lo12:_ZZL10gen_matrixllE2rd
	add	x2, x2, :lo12:__dso_handle
	bl	__cxa_atexit
	adrp	x0, .L_MergedGlobals
	add	x0, x0, :lo12:.L_MergedGlobals
	bl	__cxa_guard_release
	b	.LBB10_1
.LBB10_24:
	adrp	x0, .L_MergedGlobals+8
	add	x0, x0, :lo12:.L_MergedGlobals+8
	bl	__cxa_guard_acquire
	cbz	w0, .LBB10_2
// %bb.25:
.Ltmp14:
	adrp	x0, _ZZL10gen_matrixllE2rd
	add	x0, x0, :lo12:_ZZL10gen_matrixllE2rd
	bl	_ZNSt13random_device9_M_getvalEv
.Ltmp15:
// %bb.26:                              // %_ZNSt13random_deviceclEv.exit
	mov	w8, w0
	adrp	x13, _ZZL10gen_matrixllE3rng
	mov	w10, #35173
	mov	w9, #1
	movk	w10, #27655, lsl #16
	mov	w11, #3361
	str	x8, [x13, :lo12:_ZZL10gen_matrixllE3rng]
	adrp	x13, _ZZL10gen_matrixllE3rng
	mov	w12, #624
	add	x13, x13, :lo12:_ZZL10gen_matrixllE3rng
.LBB10_27:                              // =>This Inner Loop Header: Depth=1
	ubfx	w14, w9, #4, #12
	lsr	x15, x8, #30
	eor	w8, w15, w8
	mul	w14, w14, w11
	mul	w8, w8, w10
	lsr	w14, w14, #17
	msub	w14, w14, w12, w9
	add	w8, w8, w14, uxth
	str	x8, [x13, x9, lsl #3]
	add	x9, x9, #1
	cmp	x9, #624
	b.ne	.LBB10_27
// %bb.28:
	adrp	x0, .L_MergedGlobals+8
	adrp	x8, _ZZL10gen_matrixllE3rng+4992
	add	x0, x0, :lo12:.L_MergedGlobals+8
	str	x9, [x8, :lo12:_ZZL10gen_matrixllE3rng+4992]
	bl	__cxa_guard_release
	b	.LBB10_2
.LBB10_29:                              // %.noexc
	adrp	x0, .L.str.9
	add	x0, x0, :lo12:.L.str.9
	bl	_ZSt20__throw_length_errorPKc
.LBB10_30:
.Ltmp16:
	mov	x19, x0
	adrp	x0, .L_MergedGlobals+8
	add	x0, x0, :lo12:.L_MergedGlobals+8
	b	.LBB10_32
.LBB10_31:
.Ltmp13:
	mov	x19, x0
	adrp	x0, .L_MergedGlobals
	add	x0, x0, :lo12:.L_MergedGlobals
.LBB10_32:
	bl	__cxa_guard_abort
	mov	x0, x19
	bl	_Unwind_Resume
.Lfunc_end10:
	.size	_ZL10gen_matrixll, .Lfunc_end10-_ZL10gen_matrixll
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table10:
.Lexception1:
	.byte	255                             // @LPStart Encoding = omit
	.byte	255                             // @TType Encoding = omit
	.byte	1                               // Call site Encoding = uleb128
	.uleb128 .Lcst_end1-.Lcst_begin1
.Lcst_begin1:
	.uleb128 .Lfunc_begin1-.Lfunc_begin1    // >> Call Site 1 <<
	.uleb128 .Ltmp11-.Lfunc_begin1          //   Call between .Lfunc_begin1 and .Ltmp11
	.byte	0                               //     has no landing pad
	.byte	0                               //   On action: cleanup
	.uleb128 .Ltmp11-.Lfunc_begin1          // >> Call Site 2 <<
	.uleb128 .Ltmp12-.Ltmp11                //   Call between .Ltmp11 and .Ltmp12
	.uleb128 .Ltmp13-.Lfunc_begin1          //     jumps to .Ltmp13
	.byte	0                               //   On action: cleanup
	.uleb128 .Ltmp14-.Lfunc_begin1          // >> Call Site 3 <<
	.uleb128 .Ltmp15-.Ltmp14                //   Call between .Ltmp14 and .Ltmp15
	.uleb128 .Ltmp16-.Lfunc_begin1          //     jumps to .Ltmp16
	.byte	0                               //   On action: cleanup
	.uleb128 .Ltmp15-.Lfunc_begin1          // >> Call Site 4 <<
	.uleb128 .Lfunc_end10-.Ltmp15           //   Call between .Ltmp15 and .Lfunc_end10
	.byte	0                               //     has no landing pad
	.byte	0                               //   On action: cleanup
.Lcst_end1:
	.p2align	2
                                        // -- End function
	.section	.text._ZNSt13random_deviceC2Ev,"axG",@progbits,_ZNSt13random_deviceC2Ev,comdat
	.weak	_ZNSt13random_deviceC2Ev        // -- Begin function _ZNSt13random_deviceC2Ev
	.p2align	2
	.type	_ZNSt13random_deviceC2Ev,@function
_ZNSt13random_deviceC2Ev:               // @_ZNSt13random_deviceC2Ev
.Lfunc_begin2:
	.cfi_startproc
	.cfi_personality 156, DW.ref.__gxx_personality_v0
	.cfi_lsda 28, .Lexception2
// %bb.0:                               // %._crit_edge.i.i
	sub	sp, sp, #64
	stp	x29, x30, [sp, #32]             // 16-byte Folded Spill
	add	x29, sp, #32
	str	x19, [sp, #48]                  // 8-byte Folded Spill
	.cfi_def_cfa w29, 32
	.cfi_offset w19, -16
	.cfi_offset w30, -24
	.cfi_offset w29, -32
	mov	w8, #25956
	mov	x9, sp
	mov	w10, #30049
	movk	w8, #24934, lsl #16
	movk	w10, #29804, lsl #16
	add	x19, x9, #16
	mov	w9, #7
	strb	wzr, [sp, #23]
	str	w8, [sp, #16]
	stur	w10, [sp, #19]
	stp	x19, x9, [sp]
.Ltmp17:
	mov	x1, sp
	bl	_ZNSt13random_device7_M_initERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.Ltmp18:
// %bb.1:
	ldr	x0, [sp]
	cmp	x0, x19
	b.eq	.LBB11_3
// %bb.2:
	bl	_ZdlPv
.LBB11_3:                               // %_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev.exit
	ldp	x29, x30, [sp, #32]             // 16-byte Folded Reload
	ldr	x19, [sp, #48]                  // 8-byte Folded Reload
	add	sp, sp, #64
	ret
.LBB11_4:
.Ltmp19:
	ldr	x8, [sp]
	mov	x9, x19
	mov	x19, x0
	cmp	x8, x9
	b.eq	.LBB11_6
// %bb.5:
	mov	x0, x8
	bl	_ZdlPv
.LBB11_6:                               // %_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev.exit4
	mov	x0, x19
	bl	_Unwind_Resume
.Lfunc_end11:
	.size	_ZNSt13random_deviceC2Ev, .Lfunc_end11-_ZNSt13random_deviceC2Ev
	.cfi_endproc
	.section	.gcc_except_table._ZNSt13random_deviceC2Ev,"aG",@progbits,_ZNSt13random_deviceC2Ev,comdat
	.p2align	2
GCC_except_table11:
.Lexception2:
	.byte	255                             // @LPStart Encoding = omit
	.byte	255                             // @TType Encoding = omit
	.byte	1                               // Call site Encoding = uleb128
	.uleb128 .Lcst_end2-.Lcst_begin2
.Lcst_begin2:
	.uleb128 .Ltmp17-.Lfunc_begin2          // >> Call Site 1 <<
	.uleb128 .Ltmp18-.Ltmp17                //   Call between .Ltmp17 and .Ltmp18
	.uleb128 .Ltmp19-.Lfunc_begin2          //     jumps to .Ltmp19
	.byte	0                               //   On action: cleanup
	.uleb128 .Ltmp18-.Lfunc_begin2          // >> Call Site 2 <<
	.uleb128 .Lfunc_end11-.Ltmp18           //   Call between .Ltmp18 and .Lfunc_end11
	.byte	0                               //     has no landing pad
	.byte	0                               //   On action: cleanup
.Lcst_end2:
	.p2align	2
                                        // -- End function
	.section	.text._ZNSt13random_deviceD2Ev,"axG",@progbits,_ZNSt13random_deviceD2Ev,comdat
	.weak	_ZNSt13random_deviceD2Ev        // -- Begin function _ZNSt13random_deviceD2Ev
	.p2align	2
	.type	_ZNSt13random_deviceD2Ev,@function
_ZNSt13random_deviceD2Ev:               // @_ZNSt13random_deviceD2Ev
.Lfunc_begin3:
	.cfi_startproc
	.cfi_personality 156, DW.ref.__gxx_personality_v0
	.cfi_lsda 28, .Lexception3
// %bb.0:
	stp	x29, x30, [sp, #-16]!           // 16-byte Folded Spill
	mov	x29, sp
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
.Ltmp20:
	bl	_ZNSt13random_device7_M_finiEv
.Ltmp21:
// %bb.1:
	ldp	x29, x30, [sp], #16             // 16-byte Folded Reload
	ret
.LBB12_2:
.Ltmp22:
	bl	__clang_call_terminate
.Lfunc_end12:
	.size	_ZNSt13random_deviceD2Ev, .Lfunc_end12-_ZNSt13random_deviceD2Ev
	.cfi_endproc
	.section	.gcc_except_table._ZNSt13random_deviceD2Ev,"aG",@progbits,_ZNSt13random_deviceD2Ev,comdat
	.p2align	2
GCC_except_table12:
.Lexception3:
	.byte	255                             // @LPStart Encoding = omit
	.byte	156                             // @TType Encoding = indirect pcrel sdata8
	.uleb128 .Lttbase0-.Lttbaseref0
.Lttbaseref0:
	.byte	1                               // Call site Encoding = uleb128
	.uleb128 .Lcst_end3-.Lcst_begin3
.Lcst_begin3:
	.uleb128 .Ltmp20-.Lfunc_begin3          // >> Call Site 1 <<
	.uleb128 .Ltmp21-.Ltmp20                //   Call between .Ltmp20 and .Ltmp21
	.uleb128 .Ltmp22-.Lfunc_begin3          //     jumps to .Ltmp22
	.byte	1                               //   On action: 1
.Lcst_end3:
	.byte	1                               // >> Action Record 1 <<
                                        //   Catch TypeInfo 1
	.byte	0                               //   No further actions
	.p2align	2
                                        // >> Catch TypeInfos <<
	.xword	0                               // TypeInfo 1
.Lttbase0:
	.p2align	2
                                        // -- End function
	.section	.text.__clang_call_terminate,"axG",@progbits,__clang_call_terminate,comdat
	.hidden	__clang_call_terminate          // -- Begin function __clang_call_terminate
	.weak	__clang_call_terminate
	.p2align	2
	.type	__clang_call_terminate,@function
__clang_call_terminate:                 // @__clang_call_terminate
// %bb.0:
	str	x30, [sp, #-16]!                // 8-byte Folded Spill
	bl	__cxa_begin_catch
	bl	_ZSt9terminatev
.Lfunc_end13:
	.size	__clang_call_terminate, .Lfunc_end13-__clang_call_terminate
                                        // -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	2                               // -- Begin function _GLOBAL__sub_I_test.cpp
	.type	_GLOBAL__sub_I_test.cpp,@function
_GLOBAL__sub_I_test.cpp:                // @_GLOBAL__sub_I_test.cpp
	.cfi_startproc
// %bb.0:
	stp	x29, x30, [sp, #-32]!           // 16-byte Folded Spill
	str	x19, [sp, #16]                  // 8-byte Folded Spill
	mov	x29, sp
	.cfi_def_cfa w29, 32
	.cfi_offset w19, -16
	.cfi_offset w30, -24
	.cfi_offset w29, -32
	adrp	x19, _ZStL8__ioinit
	add	x19, x19, :lo12:_ZStL8__ioinit
	mov	x0, x19
	bl	_ZNSt8ios_base4InitC1Ev
	adrp	x0, :got:_ZNSt8ios_base4InitD1Ev
	mov	x1, x19
	adrp	x2, __dso_handle
	add	x2, x2, :lo12:__dso_handle
	ldr	x0, [x0, :got_lo12:_ZNSt8ios_base4InitD1Ev]
	ldr	x19, [sp, #16]                  // 8-byte Folded Reload
	ldp	x29, x30, [sp], #32             // 16-byte Folded Reload
	b	__cxa_atexit
.Lfunc_end14:
	.size	_GLOBAL__sub_I_test.cpp, .Lfunc_end14-_GLOBAL__sub_I_test.cpp
	.cfi_endproc
                                        // -- End function
	.type	_ZStL8__ioinit,@object          // @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.type	_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk,@object // @_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	.local	_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	.comm	_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk,16384,4
	.type	.L.str,@object                  // @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Usage: %s <n>\n"
	.size	.L.str, 15

	.type	.L.str.3,@object                // @.str.3
.L.str.3:
	.asciz	"Multiplying two %d x %d matrices\n"
	.size	.L.str.3, 34

	.type	.L.str.5,@object                // @.str.5
.L.str.5:
	.asciz	"  Exo SGEMM took %5.1lf ms, or %4.1lf GFLOPS. That's %4.1lf percent of peak.\n"
	.size	.L.str.5, 78

	.type	.L.str.6,@object                // @.str.6
.L.str.6:
	.asciz	"  Gilbert SGEMM took %5.1lf ms, or %4.1lf GFLOPS. That's %4.1lf percent of peak.\n"
	.size	.L.str.6, 82

	.type	_ZZL10gen_matrixllE2rd,@object  // @_ZZL10gen_matrixllE2rd
	.local	_ZZL10gen_matrixllE2rd
	.comm	_ZZL10gen_matrixllE2rd,5000,8
	.type	_ZZL10gen_matrixllE3rng,@object // @_ZZL10gen_matrixllE3rng
	.local	_ZZL10gen_matrixllE3rng
	.comm	_ZZL10gen_matrixllE3rng,5000,8
	.type	.L.str.7,@object                // @.str.7
.L.str.7:
	.asciz	"default"
	.size	.L.str.7, 8

	.type	.L.str.9,@object                // @.str.9
.L.str.9:
	.asciz	"cannot create std::vector larger than max_size()"
	.size	.L.str.9, 49

	.section	.init_array,"aw",@init_array
	.p2align	3
	.xword	_GLOBAL__sub_I_test.cpp
	.type	.Lstr,@object                   // @str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lstr:
	.asciz	"\n\n\n"
	.size	.Lstr, 4

	.type	.Lstr.3,@object                 // @str.3
.Lstr.3:
	.asciz	"-----------------------------------------------------------"
	.size	.Lstr.3, 60

	.type	.Lstr.4,@object                 // @str.4
.Lstr.4:
	.asciz	"n < 1!!"
	.size	.Lstr.4, 8

	.type	.L_MergedGlobals,@object        // @_MergedGlobals
	.local	.L_MergedGlobals
	.comm	.L_MergedGlobals,16,8
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.DW.ref.__gxx_personality_v0,"aGw",@progbits,DW.ref.__gxx_personality_v0,comdat
	.p2align	3
	.type	DW.ref.__gxx_personality_v0,@object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.xword	__gxx_personality_v0
.set _ZGVZL10gen_matrixllE2rd, .L_MergedGlobals
	.size	_ZGVZL10gen_matrixllE2rd, 8
.set _ZGVZL10gen_matrixllE3rng, .L_MergedGlobals+8
	.size	_ZGVZL10gen_matrixllE3rng, 8
	.ident	"Ubuntu clang version 14.0.0-1ubuntu1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
	.addrsig_sym _GLOBAL__sub_I_test.cpp
	.addrsig_sym _Unwind_Resume
	.addrsig_sym _ZStL8__ioinit
	.addrsig_sym __dso_handle
	.addrsig_sym _ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	.addrsig_sym _ZZL10gen_matrixllE2rd
	.addrsig_sym .L_MergedGlobals
