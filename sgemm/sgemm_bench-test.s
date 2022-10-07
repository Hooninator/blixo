	.arch armv8-a
	.file	"test.cpp"
	.text
	.section	.text._ZNSt13random_deviceD2Ev,"axG",@progbits,_ZNSt13random_deviceD5Ev,comdat
	.align	2
	.p2align 4,,11
	.weak	_ZNSt13random_deviceD2Ev
	.type	_ZNSt13random_deviceD2Ev, %function
_ZNSt13random_deviceD2Ev:
.LFB2430:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2430
	stp	x29, x30, [sp, -16]!
	.cfi_def_cfa_offset 16
	.cfi_offset 29, -16
	.cfi_offset 30, -8
	mov	x29, sp
	bl	_ZNSt13random_device7_M_finiEv
	ldp	x29, x30, [sp], 16
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE2430:
	.global	__gxx_personality_v0
	.section	.gcc_except_table._ZNSt13random_deviceD2Ev,"aG",@progbits,_ZNSt13random_deviceD5Ev,comdat
.LLSDA2430:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2430-.LLSDACSB2430
.LLSDACSB2430:
.LLSDACSE2430:
	.section	.text._ZNSt13random_deviceD2Ev,"axG",@progbits,_ZNSt13random_deviceD5Ev,comdat
	.size	_ZNSt13random_deviceD2Ev, .-_ZNSt13random_deviceD2Ev
	.weak	_ZNSt13random_deviceD1Ev
	.set	_ZNSt13random_deviceD1Ev,_ZNSt13random_deviceD2Ev
	.text
	.align	2
	.p2align 4,,11
	.type	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.0, %function
_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.0:
.LFB9016:
	.cfi_startproc
	stp	x29, x30, [sp, -96]!
	.cfi_def_cfa_offset 96
	.cfi_offset 29, -96
	.cfi_offset 30, -88
	mov	x29, sp
	ldp	x2, x4, [x2]
	stp	d8, d9, [sp, 16]
	ldp	x0, x6, [x0]
	stp	d10, d11, [sp, 32]
	add	x5, x4, x4, lsl 1
	lsl	x3, x4, 2
	add	x11, x5, 4
	lsl	x4, x4, 3
	lsl	x10, x5, 2
	add	x12, x2, x3
	ldp	x1, x5, [x1]
	add	x10, x10, 48
	lsl	x11, x11, 2
	lsl	x7, x6, 1
	stp	d12, d13, [sp, 48]
	add	x16, x4, 16
	add	x15, x4, 32
	stp	d14, d15, [sp, 64]
	.cfi_offset 72, -80
	.cfi_offset 73, -72
	.cfi_offset 74, -64
	.cfi_offset 75, -56
	.cfi_offset 76, -48
	.cfi_offset 77, -40
	.cfi_offset 78, -32
	.cfi_offset 79, -24
	add	x13, x11, 16
	add	x14, x12, x3
	ldr	q8, [x2, x10]
	add	x30, x3, 16
	add	x18, x3, 32
	add	x17, x3, 48
	add	x4, x4, 48
	add	x9, x7, x6
	add	x8, x0, 256
	lsl	x5, x5, 2
	ldp	q30, q29, [x2]
	ldr	q16, [x2, x13]
	ldr	q17, [x2, x11]
	ldr	q18, [x14, x3]
	ldr	q22, [x12, x3]
	ldr	q25, [x2, x30]
	ldr	q24, [x2, x18]
	ldr	q23, [x2, x17]
	ldr	q21, [x2, x16]
	ldr	q20, [x2, x15]
	ldr	q19, [x2, x4]
	ldr	q26, [x2, x3]
	ldr	q28, [x2, 32]
	ldr	q27, [x2, 48]
	str	q8, [sp, 80]
	.p2align 3,,7
.L5:
	ldr	s4, [x0, x6, lsl 2]
	ldp	q1, q0, [x1, 32]
	ldr	s3, [x0, x7, lsl 2]
	ldr	s6, [x0, x9, lsl 2]
	ld1r	{v5.4s}, [x0]
	add	x0, x0, 4
	ldp	q2, q7, [x1]
	add	x1, x1, x5
	fmul	v14.4s, v5.4s, v1.4s
	fmul	v11.4s, v1.4s, v4.s[0]
	fmul	v8.4s, v1.4s, v3.s[0]
	fmul	v1.4s, v1.4s, v6.s[0]
	fmul	v13.4s, v2.4s, v4.s[0]
	fmul	v12.4s, v7.4s, v4.s[0]
	fmul	v31.4s, v5.4s, v2.4s
	fmul	v15.4s, v5.4s, v7.4s
	fmul	v10.4s, v2.4s, v3.s[0]
	fmul	v9.4s, v7.4s, v3.s[0]
	fmul	v5.4s, v5.4s, v0.4s
	fmul	v4.4s, v0.4s, v4.s[0]
	fmul	v3.4s, v0.4s, v3.s[0]
	fadd	v16.4s, v16.4s, v1.4s
	ldr	q1, [sp, 80]
	fmul	v0.4s, v0.4s, v6.s[0]
	fmul	v2.4s, v2.4s, v6.s[0]
	fmul	v7.4s, v7.4s, v6.s[0]
	fadd	v30.4s, v30.4s, v31.4s
	fadd	v0.4s, v1.4s, v0.4s
	fadd	v29.4s, v29.4s, v15.4s
	fadd	v28.4s, v28.4s, v14.4s
	fadd	v27.4s, v27.4s, v5.4s
	fadd	v26.4s, v26.4s, v13.4s
	str	q0, [sp, 80]
	fadd	v25.4s, v25.4s, v12.4s
	fadd	v24.4s, v24.4s, v11.4s
	fadd	v23.4s, v23.4s, v4.4s
	fadd	v22.4s, v22.4s, v10.4s
	fadd	v21.4s, v21.4s, v9.4s
	fadd	v20.4s, v20.4s, v8.4s
	fadd	v19.4s, v19.4s, v3.4s
	fadd	v18.4s, v18.4s, v2.4s
	fadd	v17.4s, v17.4s, v7.4s
	cmp	x0, x8
	bne	.L5
	stp	q30, q29, [x2]
	stp	q28, q27, [x2, 32]
	str	q26, [x2, x3]
	str	q25, [x2, x30]
	str	q24, [x2, x18]
	str	q23, [x2, x17]
	str	q22, [x12, x3]
	str	q21, [x2, x16]
	str	q20, [x2, x15]
	str	q19, [x2, x4]
	str	q18, [x14, x3]
	str	q17, [x2, x11]
	str	q16, [x2, x13]
	str	q0, [x2, x10]
	ldp	d8, d9, [sp, 16]
	ldp	d10, d11, [sp, 32]
	ldp	d12, d13, [sp, 48]
	ldp	d14, d15, [sp, 64]
	ldp	x29, x30, [sp], 96
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 78
	.cfi_restore 79
	.cfi_restore 76
	.cfi_restore 77
	.cfi_restore 74
	.cfi_restore 75
	.cfi_restore 72
	.cfi_restore 73
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE9016:
	.size	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.0, .-_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.0
	.align	2
	.p2align 4,,11
	.type	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.1, %function
_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.1:
.LFB9017:
	.cfi_startproc
	stp	x29, x30, [sp, -96]!
	.cfi_def_cfa_offset 96
	.cfi_offset 29, -96
	.cfi_offset 30, -88
	mov	x29, sp
	ldp	x2, x4, [x2]
	stp	d8, d9, [sp, 16]
	ldp	x0, x6, [x0]
	stp	d10, d11, [sp, 32]
	add	x5, x4, x4, lsl 1
	lsl	x3, x4, 2
	add	x11, x5, 4
	lsl	x4, x4, 3
	lsl	x10, x5, 2
	add	x12, x2, x3
	ldp	x1, x5, [x1]
	add	x10, x10, 48
	lsl	x11, x11, 2
	lsl	x7, x6, 1
	stp	d12, d13, [sp, 48]
	add	x16, x4, 16
	add	x15, x4, 32
	stp	d14, d15, [sp, 64]
	.cfi_offset 72, -80
	.cfi_offset 73, -72
	.cfi_offset 74, -64
	.cfi_offset 75, -56
	.cfi_offset 76, -48
	.cfi_offset 77, -40
	.cfi_offset 78, -32
	.cfi_offset 79, -24
	add	x13, x11, 16
	add	x14, x12, x3
	ldr	q8, [x2, x10]
	add	x30, x3, 16
	add	x18, x3, 32
	add	x17, x3, 48
	add	x4, x4, 48
	add	x9, x7, x6
	add	x8, x0, 256
	lsl	x5, x5, 2
	ldp	q30, q29, [x2]
	ldr	q16, [x2, x13]
	ldr	q17, [x2, x11]
	ldr	q18, [x14, x3]
	ldr	q22, [x12, x3]
	ldr	q25, [x2, x30]
	ldr	q24, [x2, x18]
	ldr	q23, [x2, x17]
	ldr	q21, [x2, x16]
	ldr	q20, [x2, x15]
	ldr	q19, [x2, x4]
	ldr	q26, [x2, x3]
	ldr	q28, [x2, 32]
	ldr	q27, [x2, 48]
	str	q8, [sp, 80]
	.p2align 3,,7
.L9:
	ldr	s4, [x0, x6, lsl 2]
	ldp	q1, q0, [x1, 32]
	ldr	s3, [x0, x7, lsl 2]
	ldr	s6, [x0, x9, lsl 2]
	ld1r	{v5.4s}, [x0]
	add	x0, x0, 4
	ldp	q2, q7, [x1]
	add	x1, x1, x5
	fmul	v14.4s, v5.4s, v1.4s
	fmul	v11.4s, v1.4s, v4.s[0]
	fmul	v8.4s, v1.4s, v3.s[0]
	fmul	v1.4s, v1.4s, v6.s[0]
	fmul	v13.4s, v2.4s, v4.s[0]
	fmul	v12.4s, v7.4s, v4.s[0]
	fmul	v31.4s, v5.4s, v2.4s
	fmul	v15.4s, v5.4s, v7.4s
	fmul	v10.4s, v2.4s, v3.s[0]
	fmul	v9.4s, v7.4s, v3.s[0]
	fmul	v5.4s, v5.4s, v0.4s
	fmul	v4.4s, v0.4s, v4.s[0]
	fmul	v3.4s, v0.4s, v3.s[0]
	fadd	v16.4s, v16.4s, v1.4s
	ldr	q1, [sp, 80]
	fmul	v0.4s, v0.4s, v6.s[0]
	fmul	v2.4s, v2.4s, v6.s[0]
	fmul	v7.4s, v7.4s, v6.s[0]
	fadd	v30.4s, v30.4s, v31.4s
	fadd	v0.4s, v1.4s, v0.4s
	fadd	v29.4s, v29.4s, v15.4s
	fadd	v28.4s, v28.4s, v14.4s
	fadd	v27.4s, v27.4s, v5.4s
	fadd	v26.4s, v26.4s, v13.4s
	str	q0, [sp, 80]
	fadd	v25.4s, v25.4s, v12.4s
	fadd	v24.4s, v24.4s, v11.4s
	fadd	v23.4s, v23.4s, v4.4s
	fadd	v22.4s, v22.4s, v10.4s
	fadd	v21.4s, v21.4s, v9.4s
	fadd	v20.4s, v20.4s, v8.4s
	fadd	v19.4s, v19.4s, v3.4s
	fadd	v18.4s, v18.4s, v2.4s
	fadd	v17.4s, v17.4s, v7.4s
	cmp	x0, x8
	bne	.L9
	stp	q30, q29, [x2]
	stp	q28, q27, [x2, 32]
	str	q26, [x2, x3]
	str	q25, [x2, x30]
	str	q24, [x2, x18]
	str	q23, [x2, x17]
	str	q22, [x12, x3]
	str	q21, [x2, x16]
	str	q20, [x2, x15]
	str	q19, [x2, x4]
	str	q18, [x14, x3]
	str	q17, [x2, x11]
	str	q16, [x2, x13]
	str	q0, [x2, x10]
	ldp	d8, d9, [sp, 16]
	ldp	d10, d11, [sp, 32]
	ldp	d12, d13, [sp, 48]
	ldp	d14, d15, [sp, 64]
	ldp	x29, x30, [sp], 96
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 78
	.cfi_restore 79
	.cfi_restore 76
	.cfi_restore 77
	.cfi_restore 74
	.cfi_restore 75
	.cfi_restore 72
	.cfi_restore 73
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE9017:
	.size	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.1, .-_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.1
	.section	.rodata._ZNSt13random_deviceC2Ev.str1.8,"aMS",@progbits,1
	.align	3
.LC1:
	.string	"default"
	.section	.text._ZNSt13random_deviceC2Ev,"axG",@progbits,_ZNSt13random_deviceC5Ev,comdat
	.align	2
	.p2align 4,,11
	.weak	_ZNSt13random_deviceC2Ev
	.type	_ZNSt13random_deviceC2Ev, %function
_ZNSt13random_deviceC2Ev:
.LFB2424:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2424
	adrp	x2, .LC1
	add	x2, x2, :lo12:.LC1
	stp	x29, x30, [sp, -64]!
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	mov	x3, 7
	mov	x29, sp
	ldr	w4, [x2]
	add	x1, sp, 32
	ldr	w2, [x2, 3]
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -48
	.cfi_offset 20, -40
	add	x19, sp, 48
	str	w4, [sp, 48]
	strb	wzr, [sp, 55]
	str	w2, [x19, 3]
	stp	x19, x3, [sp, 32]
.LEHB0:
	bl	_ZNSt13random_device7_M_initERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE0:
	ldr	x0, [sp, 32]
	cmp	x0, x19
	beq	.L12
	ldr	x1, [sp, 48]
	add	x1, x1, 1
	bl	_ZdlPvm
.L12:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
.L16:
	.cfi_restore_state
	ldr	x2, [sp, 32]
	mov	x20, x0
	cmp	x2, x19
	beq	.L15
	ldr	x1, [sp, 48]
	mov	x0, x2
	add	x1, x1, 1
	bl	_ZdlPvm
.L15:
	mov	x0, x20
.LEHB1:
	bl	_Unwind_Resume
.LEHE1:
	.cfi_endproc
.LFE2424:
	.section	.gcc_except_table._ZNSt13random_deviceC2Ev,"aG",@progbits,_ZNSt13random_deviceC5Ev,comdat
.LLSDA2424:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2424-.LLSDACSB2424
.LLSDACSB2424:
	.uleb128 .LEHB0-.LFB2424
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L16-.LFB2424
	.uleb128 0
	.uleb128 .LEHB1-.LFB2424
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSE2424:
	.section	.text._ZNSt13random_deviceC2Ev,"axG",@progbits,_ZNSt13random_deviceC5Ev,comdat
	.size	_ZNSt13random_deviceC2Ev, .-_ZNSt13random_deviceC2Ev
	.weak	_ZNSt13random_deviceC1Ev
	.set	_ZNSt13random_deviceC1Ev,_ZNSt13random_deviceC2Ev
	.text
	.align	2
	.p2align 4,,11
	.global	_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.type	_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_, %function
_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_:
.LFB8109:
	.cfi_startproc
	stp	x29, x30, [sp, -112]!
	.cfi_def_cfa_offset 112
	.cfi_offset 29, -112
	.cfi_offset 30, -104
	mov	x29, sp
	ldp	x4, x0, [x4]
	stp	d8, d9, [sp, 32]
	ldr	x7, [x2, 8]
	stp	d10, d11, [sp, 48]
	lsl	x5, x0, 2
	lsl	x6, x0, 3
	add	x8, x0, x0, lsl 1
	add	x13, x4, x5
	ldr	x0, [x2]
	add	x12, x8, 4
	lsl	x8, x8, 2
	str	x19, [sp, 16]
	add	x11, x8, 48
	lsl	x12, x12, 2
	add	x8, x0, x1, lsl 2
	lsl	x9, x7, 1
	ldp	x1, x2, [x3]
	stp	d12, d13, [sp, 64]
	add	x17, x6, 16
	stp	d14, d15, [sp, 80]
	.cfi_offset 72, -80
	.cfi_offset 73, -72
	.cfi_offset 74, -64
	.cfi_offset 75, -56
	.cfi_offset 19, -96
	.cfi_offset 76, -48
	.cfi_offset 77, -40
	.cfi_offset 78, -32
	.cfi_offset 79, -24
	add	x16, x6, 32
	add	x14, x12, 16
	ldr	q8, [x4, x11]
	add	x15, x13, x5
	add	x30, x5, 32
	add	x18, x5, 48
	add	x6, x6, 48
	add	x19, x5, 16
	add	x10, x9, x7
	lsl	x2, x2, 2
	ldr	q16, [x4, x14]
	ldr	q17, [x4, x12]
	ldr	q18, [x15, x5]
	ldr	q22, [x13, x5]
	ldr	q25, [x4, x19]
	ldr	q24, [x4, x30]
	ldr	q23, [x4, x18]
	ldr	q21, [x4, x17]
	ldr	q20, [x4, x16]
	ldr	q19, [x4, x6]
	ldr	q26, [x4, x5]
	ldp	q30, q29, [x4]
	ldp	q28, q27, [x4, 32]
	str	q8, [sp, 96]
	.p2align 3,,7
.L19:
	ldr	s4, [x0, x7, lsl 2]
	ldp	q1, q0, [x1, 32]
	ldr	s3, [x0, x9, lsl 2]
	ldr	s6, [x0, x10, lsl 2]
	ld1r	{v5.4s}, [x0]
	add	x0, x0, 4
	ldp	q2, q7, [x1]
	add	x1, x1, x2
	fmul	v14.4s, v5.4s, v1.4s
	fmul	v11.4s, v1.4s, v4.s[0]
	fmul	v8.4s, v1.4s, v3.s[0]
	fmul	v1.4s, v1.4s, v6.s[0]
	fmul	v13.4s, v2.4s, v4.s[0]
	fmul	v12.4s, v7.4s, v4.s[0]
	fmul	v31.4s, v5.4s, v2.4s
	fmul	v15.4s, v5.4s, v7.4s
	fmul	v10.4s, v2.4s, v3.s[0]
	fmul	v9.4s, v7.4s, v3.s[0]
	fmul	v5.4s, v5.4s, v0.4s
	fmul	v4.4s, v0.4s, v4.s[0]
	fmul	v3.4s, v0.4s, v3.s[0]
	fadd	v16.4s, v16.4s, v1.4s
	ldr	q1, [sp, 96]
	fmul	v0.4s, v0.4s, v6.s[0]
	fmul	v2.4s, v2.4s, v6.s[0]
	fmul	v7.4s, v7.4s, v6.s[0]
	fadd	v30.4s, v30.4s, v31.4s
	fadd	v0.4s, v1.4s, v0.4s
	fadd	v29.4s, v29.4s, v15.4s
	fadd	v28.4s, v28.4s, v14.4s
	fadd	v27.4s, v27.4s, v5.4s
	fadd	v26.4s, v26.4s, v13.4s
	str	q0, [sp, 96]
	fadd	v25.4s, v25.4s, v12.4s
	fadd	v24.4s, v24.4s, v11.4s
	fadd	v23.4s, v23.4s, v4.4s
	fadd	v22.4s, v22.4s, v10.4s
	fadd	v21.4s, v21.4s, v9.4s
	fadd	v20.4s, v20.4s, v8.4s
	fadd	v19.4s, v19.4s, v3.4s
	fadd	v18.4s, v18.4s, v2.4s
	fadd	v17.4s, v17.4s, v7.4s
	cmp	x0, x8
	bne	.L19
	stp	q30, q29, [x4]
	stp	q28, q27, [x4, 32]
	str	q26, [x4, x5]
	str	q25, [x4, x19]
	str	q24, [x4, x30]
	str	q23, [x4, x18]
	str	q22, [x13, x5]
	str	q21, [x4, x17]
	str	q20, [x4, x16]
	str	q19, [x4, x6]
	str	q18, [x15, x5]
	str	q17, [x4, x12]
	str	q16, [x4, x14]
	str	q0, [x4, x11]
	ldr	x19, [sp, 16]
	ldp	d8, d9, [sp, 32]
	ldp	d10, d11, [sp, 48]
	ldp	d12, d13, [sp, 64]
	ldp	d14, d15, [sp, 80]
	ldp	x29, x30, [sp], 112
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 19
	.cfi_restore 78
	.cfi_restore 79
	.cfi_restore 76
	.cfi_restore 77
	.cfi_restore 74
	.cfi_restore 75
	.cfi_restore 72
	.cfi_restore 73
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE8109:
	.size	_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_, .-_Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.align	2
	.p2align 4,,11
	.global	_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_
	.type	_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_, %function
_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_:
.LFB8110:
	.cfi_startproc
	stp	x29, x30, [sp, -208]!
	.cfi_def_cfa_offset 208
	.cfi_offset 29, -208
	.cfi_offset 30, -200
	mov	x7, x5
	mov	x5, x3
	mov	x29, sp
	stp	x25, x26, [sp, 64]
	mov	x0, x1
	mov	x1, x2
	stp	x27, x28, [sp, 80]
	asr	x2, x0, 4
	.cfi_offset 25, -144
	.cfi_offset 26, -136
	.cfi_offset 27, -128
	.cfi_offset 28, -120
	ldp	x27, x3, [x4]
	stp	x21, x22, [sp, 32]
	ldp	x26, x4, [x5]
	stp	x23, x24, [sp, 48]
	.cfi_offset 21, -176
	.cfi_offset 22, -168
	.cfi_offset 23, -160
	.cfi_offset 24, -152
	ldp	x28, x22, [x7]
	lsl	x6, x4, 1
	add	x7, x6, x4
	add	x10, x22, x22, lsl 1
	lsl	x9, x22, 2
	cbz	x2, .L34
	add	x12, x10, 4
	lsl	x11, x22, 3
	lsl	x10, x10, 2
	lsl	x1, x1, 2
	lsl	x12, x12, 2
	lsl	x25, x2, 6
	add	x30, x12, 16
	add	x13, x9, 16
	add	x14, x9, 32
	add	x15, x9, 48
	add	x16, x11, 16
	add	x17, x11, 32
	add	x18, x11, 48
	lsl	x22, x22, 4
	lsl	x3, x3, 2
	add	x5, x26, x1
	lsl	x23, x4, 4
	mov	x21, x26
	mov	x8, x2
	stp	x19, x20, [sp, 16]
	.cfi_offset 20, -184
	.cfi_offset 19, -192
	add	x19, x10, 48
	add	x20, x28, x25
	mov	w24, 16
	stp	x26, x28, [sp, 192]
	stp	d8, d9, [sp, 96]
	.cfi_offset 73, -104
	.cfi_offset 72, -112
	stp	d10, d11, [sp, 112]
	.cfi_offset 75, -88
	.cfi_offset 74, -96
	stp	d12, d13, [sp, 128]
	.cfi_offset 77, -72
	.cfi_offset 76, -80
	stp	d14, d15, [sp, 144]
	.cfi_offset 79, -56
	.cfi_offset 78, -64
.L24:
	sub	x26, x20, x25
	mov	x28, x27
	str	x27, [sp, 184]
	.p2align 3,,7
.L26:
	ldr	q8, [x26, x30]
	mov	x27, x28
	ldr	q18, [x26, x9]
	mov	x2, x21
	ldr	q17, [x26, x13]
	str	q8, [sp, 160]
	ldr	q16, [x26, x14]
	ldr	q15, [x26, x15]
	ldr	q14, [x26, x11]
	ldr	q13, [x26, x16]
	ldr	q12, [x26, x17]
	ldr	q11, [x26, x18]
	ldr	q10, [x26, x10]
	ldr	q9, [x26, x12]
	ldr	q23, [x26, x19]
	ldp	q22, q21, [x26]
	ldp	q20, q19, [x26, 32]
	.p2align 3,,7
.L25:
	ldp	q2, q7, [x27]
	ldr	s4, [x2, x4, lsl 2]
	ldr	s3, [x2, x6, lsl 2]
	ldr	s6, [x2, x7, lsl 2]
	ld1r	{v5.4s}, [x2]
	add	x2, x2, 4
	ldp	q1, q0, [x27, 32]
	add	x27, x27, x3
	fmul	v28.4s, v2.4s, v4.s[0]
	fmul	v31.4s, v5.4s, v2.4s
	fmul	v25.4s, v2.4s, v3.s[0]
	fmul	v2.4s, v2.4s, v6.s[0]
	fmul	v29.4s, v5.4s, v1.4s
	fmul	v26.4s, v1.4s, v4.s[0]
	fmul	v8.4s, v1.4s, v3.s[0]
	fadd	v10.4s, v10.4s, v2.4s
	ldr	q2, [sp, 160]
	fmul	v1.4s, v1.4s, v6.s[0]
	fmul	v27.4s, v7.4s, v4.s[0]
	fmul	v30.4s, v5.4s, v7.4s
	fmul	v24.4s, v7.4s, v3.s[0]
	fadd	v1.4s, v2.4s, v1.4s
	fmul	v5.4s, v5.4s, v0.4s
	fmul	v4.4s, v0.4s, v4.s[0]
	fmul	v3.4s, v0.4s, v3.s[0]
	fmul	v7.4s, v7.4s, v6.s[0]
	str	q1, [sp, 160]
	fmul	v0.4s, v0.4s, v6.s[0]
	fadd	v22.4s, v22.4s, v31.4s
	fadd	v21.4s, v21.4s, v30.4s
	fadd	v20.4s, v20.4s, v29.4s
	fadd	v19.4s, v19.4s, v5.4s
	fadd	v18.4s, v18.4s, v28.4s
	fadd	v17.4s, v17.4s, v27.4s
	fadd	v16.4s, v16.4s, v26.4s
	fadd	v15.4s, v15.4s, v4.4s
	fadd	v14.4s, v14.4s, v25.4s
	fadd	v13.4s, v13.4s, v24.4s
	fadd	v12.4s, v12.4s, v8.4s
	fadd	v11.4s, v11.4s, v3.4s
	fadd	v9.4s, v9.4s, v7.4s
	fadd	v23.4s, v23.4s, v0.4s
	cmp	x5, x2
	bne	.L25
	stp	q22, q21, [x26]
	add	x28, x28, 64
	stp	q20, q19, [x26, 32]
	str	q18, [x26, x9]
	str	q17, [x26, x13]
	str	q16, [x26, x14]
	str	q15, [x26, x15]
	str	q14, [x26, x11]
	str	q13, [x26, x16]
	str	q12, [x26, x17]
	str	q11, [x26, x18]
	str	q10, [x26, x10]
	str	q9, [x26, x12]
	str	q1, [x26, x30]
	str	q23, [x26, x19]
	add	x26, x26, 64
	cmp	x20, x26
	bne	.L26
	ldr	x27, [sp, 184]
	add	x20, x20, x22
	add	x21, x21, x23
	add	x5, x5, x23
	subs	w24, w24, #1
	bne	.L24
	ldp	x26, x28, [sp, 192]
	ands	x0, x0, 15
	bne	.L45
	ldp	x19, x20, [sp, 16]
	.cfi_restore 20
	.cfi_restore 19
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	d8, d9, [sp, 96]
	.cfi_restore 73
	.cfi_restore 72
	ldp	d10, d11, [sp, 112]
	.cfi_restore 75
	.cfi_restore 74
	ldp	d12, d13, [sp, 128]
	.cfi_restore 77
	.cfi_restore 76
	ldp	d14, d15, [sp, 144]
	.cfi_restore 79
	.cfi_restore 78
	ldp	x29, x30, [sp], 208
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 27
	.cfi_restore 28
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_def_cfa_offset 0
	ret
.L34:
	.cfi_def_cfa_offset 208
	.cfi_offset 21, -176
	.cfi_offset 22, -168
	.cfi_offset 23, -160
	.cfi_offset 24, -152
	.cfi_offset 25, -144
	.cfi_offset 26, -136
	.cfi_offset 27, -128
	.cfi_offset 28, -120
	.cfi_offset 29, -208
	.cfi_offset 30, -200
	lsl	x22, x22, 4
	lsl	x1, x1, 2
	lsl	x3, x3, 2
	lsl	x23, x4, 4
	mov	x2, 0
.L23:
	lsl	x4, x4, 2
	add	x26, x26, x1
	add	x27, x27, x2, lsl 2
	add	x0, x0, x2
	mov	w14, 0
.L32:
	mov	x10, x26
	mov	x8, x28
	mov	w13, 4
.L29:
	sub	x12, x10, x1
	mov	x7, x2
	mov	x11, x27
	.p2align 3,,7
.L33:
	ldr	s0, [x8, x7, lsl 2]
	mov	x6, x11
	mov	x5, x12
	.p2align 3,,7
.L30:
	ldr	s1, [x6]
	add	x6, x6, x3
	ldr	s2, [x5], 4
	fmadd	s0, s2, s1, s0
	str	s0, [x8, x7, lsl 2]
	cmp	x5, x10
	bne	.L30
	add	x7, x7, 1
	add	x11, x11, 4
	cmp	x7, x0
	bne	.L33
	add	x8, x8, x9
	add	x10, x5, x4
	subs	w13, w13, #1
	bne	.L29
	add	w14, w14, 4
	add	x28, x28, x22
	add	x26, x26, x23
	cmp	w14, 64
	bne	.L32
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 27
	.cfi_restore 28
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_def_cfa_offset 0
	ret
.L45:
	.cfi_def_cfa_offset 208
	.cfi_offset 19, -192
	.cfi_offset 20, -184
	.cfi_offset 21, -176
	.cfi_offset 22, -168
	.cfi_offset 23, -160
	.cfi_offset 24, -152
	.cfi_offset 25, -144
	.cfi_offset 26, -136
	.cfi_offset 27, -128
	.cfi_offset 28, -120
	.cfi_offset 29, -208
	.cfi_offset 30, -200
	.cfi_offset 72, -112
	.cfi_offset 73, -104
	.cfi_offset 74, -96
	.cfi_offset 75, -88
	.cfi_offset 76, -80
	.cfi_offset 77, -72
	.cfi_offset 78, -64
	.cfi_offset 79, -56
	ldp	x19, x20, [sp, 16]
	.cfi_restore 20
	.cfi_restore 19
	lsl	x2, x8, 4
	ldp	d8, d9, [sp, 96]
	.cfi_restore 73
	.cfi_restore 72
	ldp	d10, d11, [sp, 112]
	.cfi_restore 75
	.cfi_restore 74
	ldp	d12, d13, [sp, 128]
	.cfi_restore 77
	.cfi_restore 76
	ldp	d14, d15, [sp, 144]
	.cfi_restore 79
	.cfi_restore 78
	b	.L23
	.cfi_endproc
.LFE8110:
	.size	_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_, .-_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_
	.align	2
	.p2align 4,,11
	.global	_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_
	.type	_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_, %function
_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_:
.LFB8111:
	.cfi_startproc
	stp	x29, x30, [sp, -336]!
	.cfi_def_cfa_offset 336
	.cfi_offset 29, -336
	.cfi_offset 30, -328
	mov	x29, sp
	str	x0, [sp, 128]
	ldr	x0, [x4]
	str	x0, [sp, 144]
	ldr	x0, [x6]
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -320
	.cfi_offset 20, -312
	asr	x19, x1, 6
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	.cfi_offset 21, -304
	.cfi_offset 22, -296
	.cfi_offset 23, -288
	.cfi_offset 24, -280
	mov	x24, x2
	stp	x25, x26, [sp, 64]
	str	x3, [sp, 104]
	str	x0, [sp, 152]
	and	x0, x1, 63
	str	x0, [sp, 136]
	ldp	x23, x21, [x5]
	.cfi_offset 25, -272
	.cfi_offset 26, -264
	ldr	x25, [x6, 8]
	ldr	x22, [x4, 8]
	cbz	x19, .L50
	stp	x27, x28, [sp, 80]
	.cfi_offset 28, -248
	.cfi_offset 27, -256
	lsl	x0, x22, 8
	mov	x20, 0
	ldp	x28, x27, [sp, 144]
	mov	x26, 1
	str	x0, [sp, 120]
	lsl	x0, x25, 8
	str	x0, [sp, 112]
	.p2align 3,,7
.L49:
	ldr	x0, [sp, 120]
	stp	x28, x22, [sp, 264]
	add	x20, x20, 1
	add	x28, x28, x0
	add	x0, sp, 512
	stp	x23, x21, [sp, 288]
	add	x5, sp, 160
	add	x4, sp, 192
	ldp	x10, x11, [x0, -248]
	stp	x10, x11, [sp, 224]
	add	x3, sp, 224
	ldr	x0, [sp, 112]
	stp	x26, x27, [sp, 304]
	mov	x1, x24
	ldp	x10, x11, [sp, 288]
	add	x27, x27, x0
	add	x0, sp, 512
	stp	x10, x11, [sp, 192]
	stp	x25, x26, [sp, 320]
	ldp	x10, x11, [x0, -200]
	stp	x10, x11, [sp, 160]
	ldr	x2, [sp, 104]
	str	x26, [sp, 176]
	ldr	x0, [sp, 128]
	str	x26, [sp, 208]
	str	x26, [sp, 240]
	str	x26, [sp, 280]
	bl	_Z9GEBP_edgeP18c_code_str_Contextll12exo_win_2f32S1_S1_
	cmp	x19, x20
	bne	.L49
	ldr	x0, [sp, 136]
	ldp	x27, x28, [sp, 80]
	.cfi_restore 28
	.cfi_restore 27
	cbnz	x0, .L50
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 336
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
.L50:
	.cfi_restore_state
	lsl	x19, x19, 6
	lsl	x21, x21, 2
	ldr	x0, [sp, 104]
	lsl	x9, x22, 2
	mul	x7, x19, x22
	lsl	x10, x25, 2
	mul	x19, x19, x25
	mov	x8, 0
	add	x5, x0, x7
	ldr	x0, [sp, 144]
	add	x7, x0, x7, lsl 2
	add	x5, x0, x5, lsl 2
	ldr	x0, [sp, 152]
	add	x4, x0, x19, lsl 2
	.p2align 3,,7
.L48:
	mov	x6, x23
	mov	x3, 0
	.p2align 3,,7
.L54:
	ldr	s0, [x4, x3, lsl 2]
	mov	x2, x6
	mov	x0, x7
	.p2align 3,,7
.L52:
	ldr	s1, [x2]
	add	x2, x2, x21
	ldr	s2, [x0], 4
	fmadd	s0, s2, s1, s0
	str	s0, [x4, x3, lsl 2]
	cmp	x5, x0
	bne	.L52
	add	x3, x3, 1
	add	x6, x6, 4
	cmp	x24, x3
	bne	.L54
	ldr	x0, [sp, 136]
	add	x8, x8, 1
	add	x7, x7, x9
	add	x4, x4, x10
	add	x5, x5, x9
	cmp	x8, x0
	blt	.L48
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 336
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE8111:
	.size	_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_, .-_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_
	.align	2
	.p2align 4,,11
	.global	_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_
	.type	_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_, %function
_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_:
.LFB8112:
	.cfi_startproc
	stp	x29, x30, [sp, -112]!
	.cfi_def_cfa_offset 112
	.cfi_offset 29, -112
	.cfi_offset 30, -104
	mov	x4, x1
	mov	x29, sp
	ldp	x7, x0, [x3]
	stp	d8, d9, [sp, 32]
	stp	d10, d11, [sp, 48]
	stp	d12, d13, [sp, 64]
	add	x1, x0, x0, lsl 1
	lsl	x8, x0, 2
	lsl	x0, x0, 3
	add	x11, x1, 4
	add	x17, x0, 16
	lsl	x1, x1, 2
	add	x16, x0, 32
	add	x9, x0, 48
	add	x10, x1, 48
	ldp	x0, x3, [x4]
	lsl	x11, x11, 2
	ldp	x1, x2, [x2]
	str	x19, [sp, 16]
	add	x13, x7, x8
	stp	d14, d15, [sp, 80]
	.cfi_offset 72, -80
	.cfi_offset 73, -72
	.cfi_offset 74, -64
	.cfi_offset 75, -56
	.cfi_offset 76, -48
	.cfi_offset 77, -40
	.cfi_offset 19, -96
	.cfi_offset 78, -32
	.cfi_offset 79, -24
	add	x14, x11, 16
	ldr	q8, [x7, x10]
	lsl	x4, x3, 1
	add	x15, x13, x8
	add	x30, x8, 32
	add	x18, x8, 48
	add	x19, x8, 16
	add	x6, x4, x3
	add	x5, x0, 256
	lsl	x2, x2, 2
	ldr	q16, [x7, x14]
	ldr	q17, [x7, x11]
	ldr	q18, [x15, x8]
	ldr	q22, [x13, x8]
	ldr	q25, [x7, x19]
	ldr	q24, [x7, x30]
	ldr	q23, [x7, x18]
	ldr	q21, [x7, x17]
	ldr	q20, [x7, x16]
	ldr	q19, [x7, x9]
	ldr	q26, [x7, x8]
	ldp	q30, q29, [x7]
	ldp	q28, q27, [x7, 32]
	str	q8, [sp, 96]
	.p2align 3,,7
.L61:
	ldr	s4, [x0, x3, lsl 2]
	ldp	q1, q0, [x1, 32]
	ldr	s3, [x0, x4, lsl 2]
	ldr	s6, [x0, x6, lsl 2]
	ld1r	{v5.4s}, [x0]
	add	x0, x0, 4
	ldp	q2, q7, [x1]
	add	x1, x1, x2
	fmul	v14.4s, v5.4s, v1.4s
	fmul	v11.4s, v1.4s, v4.s[0]
	fmul	v8.4s, v1.4s, v3.s[0]
	fmul	v1.4s, v1.4s, v6.s[0]
	fmul	v13.4s, v2.4s, v4.s[0]
	fmul	v12.4s, v7.4s, v4.s[0]
	fmul	v31.4s, v5.4s, v2.4s
	fmul	v15.4s, v5.4s, v7.4s
	fmul	v10.4s, v2.4s, v3.s[0]
	fmul	v9.4s, v7.4s, v3.s[0]
	fmul	v5.4s, v5.4s, v0.4s
	fmul	v4.4s, v0.4s, v4.s[0]
	fmul	v3.4s, v0.4s, v3.s[0]
	fadd	v16.4s, v16.4s, v1.4s
	ldr	q1, [sp, 96]
	fmul	v0.4s, v0.4s, v6.s[0]
	fmul	v2.4s, v2.4s, v6.s[0]
	fmul	v7.4s, v7.4s, v6.s[0]
	fadd	v30.4s, v30.4s, v31.4s
	fadd	v0.4s, v1.4s, v0.4s
	fadd	v29.4s, v29.4s, v15.4s
	fadd	v28.4s, v28.4s, v14.4s
	fadd	v27.4s, v27.4s, v5.4s
	fadd	v26.4s, v26.4s, v13.4s
	str	q0, [sp, 96]
	fadd	v25.4s, v25.4s, v12.4s
	fadd	v24.4s, v24.4s, v11.4s
	fadd	v23.4s, v23.4s, v4.4s
	fadd	v22.4s, v22.4s, v10.4s
	fadd	v21.4s, v21.4s, v9.4s
	fadd	v20.4s, v20.4s, v8.4s
	fadd	v19.4s, v19.4s, v3.4s
	fadd	v18.4s, v18.4s, v2.4s
	fadd	v17.4s, v17.4s, v7.4s
	cmp	x0, x5
	bne	.L61
	stp	q30, q29, [x7]
	stp	q28, q27, [x7, 32]
	str	q26, [x7, x8]
	str	q25, [x7, x19]
	str	q24, [x7, x30]
	str	q23, [x7, x18]
	str	q22, [x13, x8]
	str	q21, [x7, x17]
	str	q20, [x7, x16]
	str	q19, [x7, x9]
	str	q18, [x15, x8]
	str	q17, [x7, x11]
	str	q16, [x7, x14]
	str	q0, [x7, x10]
	ldr	x19, [sp, 16]
	ldp	d8, d9, [sp, 32]
	ldp	d10, d11, [sp, 48]
	ldp	d12, d13, [sp, 64]
	ldp	d14, d15, [sp, 80]
	ldp	x29, x30, [sp], 112
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 19
	.cfi_restore 78
	.cfi_restore 79
	.cfi_restore 76
	.cfi_restore 77
	.cfi_restore 74
	.cfi_restore 75
	.cfi_restore 72
	.cfi_restore 73
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE8112:
	.size	_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_, .-_Z16neon_microkernelP18c_code_str_Context12exo_win_2f32S1_S1_
	.align	2
	.p2align 4,,11
	.global	_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.type	_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_, %function
_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_:
.LFB8113:
	.cfi_startproc
	stp	x29, x30, [sp, -304]!
	.cfi_def_cfa_offset 304
	.cfi_offset 29, -304
	.cfi_offset 30, -296
	mov	x5, x2
	asr	x6, x1, 4
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	.cfi_offset 19, -288
	.cfi_offset 20, -280
	.cfi_offset 21, -272
	.cfi_offset 22, -264
	.cfi_offset 23, -256
	.cfi_offset 24, -248
	.cfi_offset 25, -240
	.cfi_offset 26, -232
	.cfi_offset 27, -224
	.cfi_offset 28, -216
	ldp	x24, x19, [x3]
	ldp	x13, x2, [x4]
	ldp	x12, x27, [x5]
	cbz	x6, .L97
	add	x8, x2, x2, lsl 1
	lsl	x7, x2, 2
	lsl	x22, x2, 3
	add	x10, x8, 4
	lsl	x23, x8, 2
	lsl	x19, x19, 2
	add	x0, x23, 48
	stp	x0, x2, [sp, 280]
	add	x0, x7, 16
	str	x0, [sp, 232]
	add	x0, x7, 32
	str	x0, [sp, 240]
	add	x0, x7, 48
	str	x0, [sp, 248]
	add	x0, x22, 16
	lsl	x25, x10, 2
	str	x0, [sp, 256]
	add	x0, x22, 32
	add	x26, x25, 16
	lsl	x28, x27, 1
	str	x0, [sp, 264]
	add	x0, x22, 48
	add	x21, x28, x27
	lsl	x15, x2, 4
	mov	x3, x25
	mov	x2, x26
	mov	x20, 0
	str	x0, [sp, 272]
	mov	x0, x19
	mov	x25, x20
	mov	x26, x21
	mov	x19, x22
	mov	x20, x3
	mov	x22, x23
	mov	x21, x2
	mov	x23, x0
	stp	x12, x24, [sp, 184]
	mov	x24, x7
	lsl	x6, x6, 4
	lsl	x14, x27, 4
	stp	x13, x6, [sp, 200]
	stp	x14, x15, [sp, 216]
	str	x1, [sp, 296]
	stp	d8, d9, [sp, 96]
	.cfi_offset 73, -200
	.cfi_offset 72, -208
	stp	d10, d11, [sp, 112]
	.cfi_offset 75, -184
	.cfi_offset 74, -192
	stp	d12, d13, [sp, 128]
	.cfi_offset 77, -168
	.cfi_offset 76, -176
	stp	d14, d15, [sp, 144]
	.cfi_offset 79, -152
	.cfi_offset 78, -160
.L72:
	mov	x0, 4096
	bl	malloc
	add	x3, x0, 4096
	ldr	x1, [sp, 192]
	lsl	x5, x25, 2
	add	x2, x1, x5
	mov	x1, x0
.L69:
	ldp	q0, q2, [x2]
	ldr	q1, [x2, 32]
	stp	q0, q2, [x1]
	add	x1, x1, 64
	ldr	q0, [x2, 48]
	str	q1, [x1, -32]
	add	x2, x2, x23
	str	q0, [x1, -16]
	cmp	x3, x1
	bne	.L69
	ldr	x1, [sp, 200]
	mov	w13, 16
	ldp	x4, x6, [sp, 232]
	add	x5, x1, x5
	ldp	x7, x8, [sp, 248]
	ldp	x9, x10, [sp, 264]
	ldr	x14, [sp, 184]
	ldr	x11, [sp, 280]
.L71:
	mov	x1, x0
	ldr	q8, [x5, x21]
	mov	x2, x14
	ldr	q18, [x5, x24]
	ldr	q17, [x5, x4]
	str	q8, [sp, 160]
	ldr	q16, [x5, x6]
	ldr	q15, [x5, x7]
	ldr	q14, [x5, x19]
	ldr	q13, [x5, x8]
	ldr	q12, [x5, x9]
	ldr	q11, [x5, x10]
	ldr	q10, [x5, x22]
	ldr	q9, [x5, x20]
	ldr	q23, [x5, x11]
	ldp	q22, q21, [x5]
	ldp	q20, q19, [x5, 32]
	.p2align 3,,7
.L70:
	ldp	q2, q7, [x1]
	ldr	s4, [x2, x27, lsl 2]
	ldr	s3, [x2, x28, lsl 2]
	ldr	s6, [x2, x26, lsl 2]
	ld1r	{v5.4s}, [x2]
	add	x2, x2, 4
	ldp	q1, q0, [x1, 32]
	add	x1, x1, 64
	fmul	v28.4s, v2.4s, v4.s[0]
	fmul	v31.4s, v5.4s, v2.4s
	fmul	v25.4s, v2.4s, v3.s[0]
	fmul	v2.4s, v2.4s, v6.s[0]
	fmul	v29.4s, v5.4s, v1.4s
	fmul	v26.4s, v1.4s, v4.s[0]
	fmul	v8.4s, v1.4s, v3.s[0]
	fadd	v10.4s, v10.4s, v2.4s
	ldr	q2, [sp, 160]
	fmul	v1.4s, v1.4s, v6.s[0]
	fmul	v27.4s, v7.4s, v4.s[0]
	fmul	v30.4s, v5.4s, v7.4s
	fmul	v24.4s, v7.4s, v3.s[0]
	fadd	v1.4s, v2.4s, v1.4s
	fmul	v5.4s, v5.4s, v0.4s
	fmul	v4.4s, v0.4s, v4.s[0]
	fmul	v3.4s, v0.4s, v3.s[0]
	fmul	v7.4s, v7.4s, v6.s[0]
	str	q1, [sp, 160]
	fmul	v0.4s, v0.4s, v6.s[0]
	fadd	v22.4s, v22.4s, v31.4s
	fadd	v21.4s, v21.4s, v30.4s
	fadd	v20.4s, v20.4s, v29.4s
	fadd	v19.4s, v19.4s, v5.4s
	fadd	v18.4s, v18.4s, v28.4s
	fadd	v17.4s, v17.4s, v27.4s
	fadd	v16.4s, v16.4s, v26.4s
	fadd	v15.4s, v15.4s, v4.4s
	fadd	v14.4s, v14.4s, v25.4s
	fadd	v13.4s, v13.4s, v24.4s
	fadd	v12.4s, v12.4s, v8.4s
	fadd	v11.4s, v11.4s, v3.4s
	fadd	v9.4s, v9.4s, v7.4s
	fadd	v23.4s, v23.4s, v0.4s
	cmp	x3, x1
	bne	.L70
	stp	q22, q21, [x5]
	subs	w13, w13, #1
	stp	q20, q19, [x5, 32]
	str	q18, [x5, x24]
	str	q17, [x5, x4]
	str	q16, [x5, x6]
	str	q15, [x5, x7]
	str	q14, [x5, x19]
	str	q13, [x5, x8]
	ldr	x1, [sp, 216]
	str	q12, [x5, x9]
	str	q11, [x5, x10]
	add	x14, x14, x1
	str	q10, [x5, x22]
	ldr	x1, [sp, 224]
	str	q9, [x5, x20]
	str	q1, [x5, x21]
	str	q23, [x5, x11]
	add	x5, x5, x1
	bne	.L71
	bl	free
	add	x25, x25, 16
	ldr	x0, [sp, 208]
	cmp	x0, x25
	bne	.L72
	ldp	x2, x1, [sp, 288]
	mov	x7, x24
	ldp	d8, d9, [sp, 96]
	.cfi_restore 73
	.cfi_restore 72
	mov	x6, x0
	ldp	d10, d11, [sp, 112]
	.cfi_restore 75
	.cfi_restore 74
	mov	x19, x23
	ldp	d12, d13, [sp, 128]
	.cfi_restore 77
	.cfi_restore 76
	ands	x1, x1, 15
	ldp	d14, d15, [sp, 144]
	.cfi_restore 79
	.cfi_restore 78
	ldp	x12, x24, [sp, 184]
	ldr	x13, [sp, 200]
	ldp	x14, x15, [sp, 216]
	bne	.L66
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 27
	.cfi_restore 28
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
.L97:
	.cfi_restore_state
	lsl	x19, x19, 2
	lsl	x15, x2, 4
	lsl	x14, x27, 4
	lsl	x7, x2, 2
.L66:
	add	x24, x24, x6, lsl 2
	add	x1, x1, x6
	lsl	x23, x27, 2
	add	x17, x12, 256
	mov	x16, x13
	mov	w11, 0
	mov	x10, 0
	mov	x9, 0
.L68:
	mov	x21, x10
	mov	x8, x17
	mov	x5, x16
	mov	x20, x9
	mov	w18, 4
.L76:
	add	x26, x13, x21, lsl 2
	add	x25, x12, x20, lsl 2
	mov	x4, x6
	mov	x22, x24
.L74:
	ldr	s0, [x26, x4, lsl 2]
	mov	x3, x22
	mov	x0, x25
	.p2align 3,,7
.L75:
	ldr	s1, [x3]
	add	x3, x3, x19
	ldr	s2, [x0], 4
	fmadd	s0, s2, s1, s0
	str	s0, [x5, x4, lsl 2]
	cmp	x8, x0
	bne	.L75
	add	x4, x4, 1
	add	x22, x22, 4
	cmp	x1, x4
	bne	.L74
	add	x20, x20, x27
	add	x5, x5, x7
	add	x8, x8, x23
	add	x21, x21, x2
	subs	w18, w18, #1
	bne	.L76
	add	w11, w11, 4
	add	x9, x9, x23
	add	x16, x16, x15
	add	x17, x17, x14
	add	x10, x10, x7
	cmp	w11, 64
	bne	.L68
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 27
	.cfi_restore 28
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE8113:
	.size	_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_, .-_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.align	2
	.p2align 4,,11
	.global	_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_
	.type	_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_, %function
_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_:
.LFB8114:
	.cfi_startproc
	stp	x29, x30, [sp, -352]!
	.cfi_def_cfa_offset 352
	.cfi_offset 29, -352
	.cfi_offset 30, -344
	mov	x29, sp
	stp	x23, x24, [sp, 48]
	.cfi_offset 23, -304
	.cfi_offset 24, -296
	mov	x23, x1
	mov	x1, x2
	stp	x27, x28, [sp, 80]
	.cfi_offset 27, -272
	.cfi_offset 28, -264
	ldp	x28, x24, [x3]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	.cfi_offset 19, -336
	.cfi_offset 20, -328
	.cfi_offset 21, -320
	.cfi_offset 22, -312
	asr	x22, x23, 6
	and	x23, x23, 63
	stp	x25, x26, [sp, 64]
	.cfi_offset 25, -288
	.cfi_offset 26, -280
	lsl	x20, x24, 2
	ldp	x12, x19, [x4]
	ldr	x25, [x5, 8]
	ldr	x5, [x5]
	cbz	x22, .L99
	adrp	x27, .LANCHOR0
	adrp	x11, _ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	adrp	x21, _ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk+16384
	add	x27, x27, :lo12:.LANCHOR0
	add	x11, x11, :lo12:_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	lsl	x14, x25, 8
	add	x21, x21, :lo12:_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk+16384
	mov	x10, x5
	lsl	x13, x24, 8
	mov	x9, x28
	lsl	x20, x24, 2
	mov	x8, 0
	mov	x26, 1
.L100:
	mov	x3, x11
	mov	x4, x9
	b	.L107
	.p2align 2,,3
.L105:
	ldr	q0, [x4]
	add	x3, x3, 256
	str	q0, [x3, -256]
	ldr	q0, [x4, 16]
	str	q0, [x3, -240]
	ldr	q0, [x4, 32]
	str	q0, [x3, -224]
	ldr	q0, [x4, 48]
	str	q0, [x3, -208]
	ldr	q0, [x4, 64]
	str	q0, [x3, -192]
	ldr	q0, [x4, 80]
	str	q0, [x3, -176]
	ldr	q0, [x4, 96]
	str	q0, [x3, -160]
	ldr	q0, [x4, 112]
	str	q0, [x3, -144]
	ldr	q0, [x4, 128]
	str	q0, [x3, -128]
	ldr	q0, [x4, 144]
	str	q0, [x3, -112]
	ldr	q0, [x4, 160]
	str	q0, [x3, -96]
	ldr	q0, [x4, 176]
	str	q0, [x3, -80]
	ldr	q0, [x4, 192]
	str	q0, [x3, -64]
	ldr	q0, [x4, 208]
	str	q0, [x3, -48]
	ldr	q0, [x4, 224]
	str	q0, [x3, -32]
	ldr	q0, [x4, 240]
	add	x4, x4, x20
	str	q0, [x3, -16]
	cmp	x3, x21
	beq	.L104
.L107:
	add	x2, x4, 4
	sub	x2, x3, x2
	cmp	x2, 8
	bhi	.L105
	mov	x2, 0
	.p2align 3,,7
.L102:
	ldr	s0, [x4, x2]
	str	s0, [x3, x2]
	add	x2, x2, 4
	cmp	x2, 256
	bne	.L102
	add	x3, x3, 256
	add	x4, x4, x20
	cmp	x3, x21
	bne	.L107
.L104:
	ldr	x15, [x27, 16]
	stp	x15, x12, [sp, 296]
	add	x8, x8, 1
	stp	x19, x26, [sp, 312]
	add	x9, x9, x13
	add	x2, sp, 240
	ldp	x6, x7, [sp, 304]
	stp	x12, x5, [sp, 160]
	add	x5, sp, 512
	stp	x6, x7, [sp, 208]
	add	x4, sp, 176
	add	x3, sp, 208
	stp	x10, x25, [sp, 328]
	add	x10, x10, x14
	str	x26, [sp, 344]
	stp	x0, x1, [sp, 104]
	ldp	x6, x7, [x5, -184]
	stp	x6, x7, [sp, 176]
	ldp	x6, x7, [x27]
	stp	x6, x7, [x5, -232]
	stp	x9, x13, [sp, 120]
	str	x10, [sp, 136]
	stp	x14, x8, [sp, 144]
	str	x26, [sp, 192]
	str	x26, [sp, 224]
	stp	x6, x7, [sp, 240]
	str	x15, [sp, 256]
	bl	_Z4GEBPP18c_code_str_Contextl12exo_win_2f32S1_S1_
	ldp	x8, x12, [sp, 152]
	adrp	x2, _ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	ldp	x0, x1, [sp, 104]
	add	x11, x2, :lo12:_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	ldp	x9, x13, [sp, 120]
	ldp	x10, x14, [sp, 136]
	ldr	x5, [sp, 168]
	cmp	x8, x22
	bne	.L100
	cbnz	x23, .L99
.L98:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 352
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 27
	.cfi_restore 28
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
.L99:
	.cfi_restore_state
	lsl	x7, x22, 6
	add	x3, x28, 256
	lsl	x19, x19, 2
	lsl	x14, x25, 2
	mov	x11, 0
	mul	x10, x7, x24
	mul	x7, x7, x25
	lsl	x2, x10, 2
	lsl	x0, x7, 2
	add	x3, x3, x2
	add	x6, x5, x0
.L101:
	add	x8, x5, x0
	add	x9, x28, x2
	mov	x13, x12
	mov	x4, 0
.L111:
	ldr	s0, [x8, x4, lsl 2]
	mov	x2, x13
	mov	x0, x9
	.p2align 3,,7
.L109:
	ldr	s1, [x2]
	add	x2, x2, x19
	ldr	s2, [x0], 4
	fmadd	s0, s2, s1, s0
	str	s0, [x6, x4, lsl 2]
	cmp	x3, x0
	bne	.L109
	add	x4, x4, 1
	add	x13, x13, 4
	cmp	x1, x4
	bne	.L111
	add	x11, x11, 1
	add	x10, x10, x24
	add	x6, x6, x14
	add	x3, x3, x20
	add	x7, x7, x25
	cmp	x23, x11
	ble	.L98
	lsl	x0, x7, 2
	lsl	x2, x10, 2
	b	.L101
	.cfi_endproc
.LFE8114:
	.size	_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_, .-_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_
	.align	2
	.p2align 4,,11
	.global	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	.type	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_, %function
_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_:
.LFB8115:
	.cfi_startproc
	stp	x29, x30, [sp, -448]!
	.cfi_def_cfa_offset 448
	.cfi_offset 29, -448
	.cfi_offset 30, -440
	mov	x7, x3
	mov	x10, x1
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	mov	x8, x4
	.cfi_offset 19, -432
	.cfi_offset 20, -424
	asr	x20, x3, 6
	stp	x25, x26, [sp, 64]
	mov	x1, x5
	.cfi_offset 25, -384
	.cfi_offset 26, -376
	mov	x26, x2
	stp	x27, x28, [sp, 80]
	mov	x4, x6
	and	x3, x3, 63
	str	x0, [sp, 120]
	.cfi_offset 27, -368
	.cfi_offset 28, -360
	cbz	x20, .L130
	lsl	x0, x10, 8
	lsl	x19, x2, 2
	stp	x21, x22, [sp, 32]
	.cfi_offset 22, -408
	.cfi_offset 21, -416
	lsl	x21, x7, 2
	add	x25, sp, 272
	add	x27, sp, 240
	add	x28, sp, 208
	stp	x23, x24, [sp, 48]
	.cfi_offset 24, -392
	.cfi_offset 23, -400
	mov	x23, x21
	mov	x24, x5
	mov	x21, x19
	str	x0, [sp, 144]
	lsl	x0, x2, 8
	str	x8, [sp, 96]
	str	x0, [sp, 104]
	lsl	x0, x20, 6
	str	xzr, [sp, 112]
	stp	x10, x6, [sp, 128]
	str	x0, [sp, 160]
	stp	x20, x3, [sp, 168]
	stp	x7, x8, [sp, 184]
	str	x5, [sp, 200]
.L123:
	ldr	x19, [sp, 144]
	mov	x0, x19
	bl	malloc
	ldr	x1, [sp, 96]
	mov	x20, x0
	add	x2, x19, x0
	.p2align 3,,7
.L121:
	ldp	q0, q1, [x1]
	stp	q0, q1, [x0]
	ldp	q0, q1, [x1, 32]
	stp	q0, q1, [x0, 32]
	ldp	q0, q1, [x1, 64]
	stp	q0, q1, [x0, 64]
	ldp	q0, q1, [x1, 96]
	stp	q0, q1, [x0, 96]
	ldp	q0, q1, [x1, 128]
	stp	q0, q1, [x0, 128]
	ldp	q0, q1, [x1, 160]
	stp	q0, q1, [x0, 160]
	ldp	q0, q1, [x1, 192]
	stp	q0, q1, [x0, 192]
	ldp	q0, q1, [x1, 224]
	add	x1, x1, x23
	stp	q0, q1, [x0, 224]
	add	x0, x0, 256
	cmp	x2, x0
	bne	.L121
	ldr	x0, [sp, 104]
	mov	x22, x24
	mov	w19, 64
	bl	malloc
	mov	x3, x0
	str	x0, [sp, 152]
	.p2align 3,,7
.L122:
	mov	x1, x22
	mov	x0, x3
	mov	x2, x21
	bl	memcpy
	add	x22, x22, x21
	add	x3, x0, x21
	subs	w19, w19, #1
	bne	.L122
	adrp	x0, .LC2
	str	x20, [sp, 304]
	ldr	x19, [sp, 152]
	stp	x19, x26, [sp, 328]
	add	x6, sp, 512
	ldr	q0, [x0, #:lo12:.LC2]
	add	x0, sp, 512
	str	x26, [sp, 360]
	mov	x5, x28
	ldr	x1, [sp, 128]
	str	q0, [x0, -200]
	mov	x0, 1
	str	x0, [sp, 344]
	mov	x4, x27
	ldr	x0, [sp, 112]
	mov	x3, x25
	ldp	x8, x9, [sp, 304]
	add	x22, x0, 64
	ldr	x0, [sp, 136]
	str	x0, [sp, 352]
	ldr	x0, [sp, 104]
	str	x22, [sp, 112]
	mov	x2, x26
	add	x24, x24, x0
	ldr	x0, [sp, 96]
	add	x0, x0, 256
	str	x0, [sp, 96]
	mov	x0, 1
	str	x0, [sp, 368]
	stp	x8, x9, [x25]
	ldr	x8, [sp, 320]
	ldr	x0, [sp, 120]
	str	x8, [x25, 16]
	ldp	x8, x9, [x6, -184]
	stp	x8, x9, [x27]
	ldr	x8, [sp, 344]
	str	x8, [x27, 16]
	ldp	x8, x9, [sp, 352]
	stp	x8, x9, [x28]
	ldr	x8, [sp, 368]
	str	x8, [x28, 16]
	bl	_Z4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_
	mov	x0, x20
	bl	free
	mov	x0, x19
	bl	free
	ldr	x0, [sp, 160]
	cmp	x0, x22
	bne	.L123
	ldp	x20, x3, [sp, 168]
	ldp	x21, x22, [sp, 32]
	.cfi_restore 22
	.cfi_restore 21
	ldp	x23, x24, [sp, 48]
	.cfi_restore 24
	.cfi_restore 23
	ldp	x10, x4, [sp, 128]
	ldp	x7, x8, [sp, 184]
	ldr	x1, [sp, 200]
	cbnz	x3, .L124
	ldp	x19, x20, [sp, 16]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 448
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 27
	.cfi_restore 28
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
.L130:
	.cfi_restore_state
	add	x25, sp, 272
	add	x27, sp, 240
	add	x28, sp, 208
.L124:
	add	x8, x8, x20, lsl 8
	add	x0, sp, 624
	mul	x20, x26, x20
	stp	x8, x7, [sp, 376]
	mov	x8, 1
	str	x8, [sp, 416]
	mov	x2, x26
	add	x20, x1, x20, lsl 8
	stp	x20, x26, [sp, 400]
	mov	x5, x27
	ldp	x0, x1, [x0, -248]
	stp	x0, x1, [sp, 272]
	mov	x6, x28
	stp	x4, x26, [sp, 424]
	mov	x1, x10
	mov	x4, x25
	str	x8, [sp, 440]
	ldr	x0, [sp, 120]
	str	x8, [x25, 16]
	ldp	x8, x9, [sp, 400]
	stp	x8, x9, [sp, 240]
	ldr	x7, [sp, 416]
	str	x7, [x27, 16]
	add	x7, sp, 624
	ldp	x8, x9, [x7, -200]
	stp	x8, x9, [sp, 208]
	ldr	x7, [sp, 440]
	str	x7, [x28, 16]
	bl	_Z9GEPP_edgeP18c_code_str_Contextlll12exo_win_2f32S1_S1_
	ldp	x19, x20, [sp, 16]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 448
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 27
	.cfi_restore 28
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE8115:
	.size	_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_, .-_Z9sgemm_exoP18c_code_str_ContextlllPfS1_S1_
	.align	2
	.p2align 4,,11
	.global	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.type	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_, %function
_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_:
.LFB8116:
	.cfi_startproc
	stp	x29, x30, [sp, -112]!
	.cfi_def_cfa_offset 112
	.cfi_offset 29, -112
	.cfi_offset 30, -104
	mov	x29, sp
	ldp	x4, x0, [x4]
	stp	d8, d9, [sp, 32]
	ldr	x7, [x2, 8]
	stp	d10, d11, [sp, 48]
	lsl	x5, x0, 2
	lsl	x6, x0, 3
	add	x8, x0, x0, lsl 1
	add	x13, x4, x5
	ldr	x0, [x2]
	add	x12, x8, 4
	lsl	x8, x8, 2
	str	x19, [sp, 16]
	add	x11, x8, 48
	lsl	x12, x12, 2
	add	x8, x0, x1, lsl 2
	lsl	x9, x7, 1
	ldp	x1, x2, [x3]
	stp	d12, d13, [sp, 64]
	add	x17, x6, 16
	stp	d14, d15, [sp, 80]
	.cfi_offset 72, -80
	.cfi_offset 73, -72
	.cfi_offset 74, -64
	.cfi_offset 75, -56
	.cfi_offset 19, -96
	.cfi_offset 76, -48
	.cfi_offset 77, -40
	.cfi_offset 78, -32
	.cfi_offset 79, -24
	add	x16, x6, 32
	add	x14, x12, 16
	ldr	q8, [x4, x11]
	add	x15, x13, x5
	add	x30, x5, 32
	add	x18, x5, 48
	add	x6, x6, 48
	add	x19, x5, 16
	add	x10, x9, x7
	lsl	x2, x2, 2
	ldr	q16, [x4, x14]
	ldr	q17, [x4, x12]
	ldr	q18, [x15, x5]
	ldr	q22, [x13, x5]
	ldr	q25, [x4, x19]
	ldr	q24, [x4, x30]
	ldr	q23, [x4, x18]
	ldr	q21, [x4, x17]
	ldr	q20, [x4, x16]
	ldr	q19, [x4, x6]
	ldr	q26, [x4, x5]
	ldp	q30, q29, [x4]
	ldp	q28, q27, [x4, 32]
	str	q8, [sp, 96]
	.p2align 3,,7
.L132:
	ldr	s4, [x0, x7, lsl 2]
	ldp	q1, q0, [x1, 32]
	ldr	s3, [x0, x9, lsl 2]
	ldr	s6, [x0, x10, lsl 2]
	ld1r	{v5.4s}, [x0]
	add	x0, x0, 4
	ldp	q2, q7, [x1]
	add	x1, x1, x2
	fmul	v14.4s, v5.4s, v1.4s
	fmul	v11.4s, v1.4s, v4.s[0]
	fmul	v8.4s, v1.4s, v3.s[0]
	fmul	v1.4s, v1.4s, v6.s[0]
	fmul	v13.4s, v2.4s, v4.s[0]
	fmul	v12.4s, v7.4s, v4.s[0]
	fmul	v31.4s, v5.4s, v2.4s
	fmul	v15.4s, v5.4s, v7.4s
	fmul	v10.4s, v2.4s, v3.s[0]
	fmul	v9.4s, v7.4s, v3.s[0]
	fmul	v5.4s, v5.4s, v0.4s
	fmul	v4.4s, v0.4s, v4.s[0]
	fmul	v3.4s, v0.4s, v3.s[0]
	fadd	v16.4s, v16.4s, v1.4s
	ldr	q1, [sp, 96]
	fmul	v0.4s, v0.4s, v6.s[0]
	fmul	v2.4s, v2.4s, v6.s[0]
	fmul	v7.4s, v7.4s, v6.s[0]
	fadd	v30.4s, v30.4s, v31.4s
	fadd	v0.4s, v1.4s, v0.4s
	fadd	v29.4s, v29.4s, v15.4s
	fadd	v28.4s, v28.4s, v14.4s
	fadd	v27.4s, v27.4s, v5.4s
	fadd	v26.4s, v26.4s, v13.4s
	str	q0, [sp, 96]
	fadd	v25.4s, v25.4s, v12.4s
	fadd	v24.4s, v24.4s, v11.4s
	fadd	v23.4s, v23.4s, v4.4s
	fadd	v22.4s, v22.4s, v10.4s
	fadd	v21.4s, v21.4s, v9.4s
	fadd	v20.4s, v20.4s, v8.4s
	fadd	v19.4s, v19.4s, v3.4s
	fadd	v18.4s, v18.4s, v2.4s
	fadd	v17.4s, v17.4s, v7.4s
	cmp	x0, x8
	bne	.L132
	stp	q30, q29, [x4]
	stp	q28, q27, [x4, 32]
	str	q26, [x4, x5]
	str	q25, [x4, x19]
	str	q24, [x4, x30]
	str	q23, [x4, x18]
	str	q22, [x13, x5]
	str	q21, [x4, x17]
	str	q20, [x4, x16]
	str	q19, [x4, x6]
	str	q18, [x15, x5]
	str	q17, [x4, x12]
	str	q16, [x4, x14]
	str	q0, [x4, x11]
	ldr	x19, [sp, 16]
	ldp	d8, d9, [sp, 32]
	ldp	d10, d11, [sp, 48]
	ldp	d12, d13, [sp, 64]
	ldp	d14, d15, [sp, 80]
	ldp	x29, x30, [sp], 112
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 19
	.cfi_restore 78
	.cfi_restore 79
	.cfi_restore 76
	.cfi_restore 77
	.cfi_restore 74
	.cfi_restore 75
	.cfi_restore 72
	.cfi_restore 73
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE8116:
	.size	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_, .-_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.align	2
	.p2align 4,,11
	.global	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	.type	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_, %function
_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_:
.LFB8117:
	.cfi_startproc
	sub	sp, sp, #608
	.cfi_def_cfa_offset 608
	mov	x0, 16384
	stp	x29, x30, [sp]
	.cfi_offset 29, -608
	.cfi_offset 30, -600
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -592
	.cfi_offset 20, -584
	mov	x19, x1
	mov	x20, x5
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -576
	.cfi_offset 22, -568
	asr	x21, x1, 2
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	.cfi_offset 23, -560
	.cfi_offset 24, -552
	.cfi_offset 25, -544
	.cfi_offset 26, -536
	mov	x26, x6
	stp	x27, x28, [sp, 80]
	.cfi_offset 27, -528
	.cfi_offset 28, -520
	mov	x28, x3
	mov	x27, x2
	str	x4, [sp, 104]
	str	x1, [sp, 160]
	bl	malloc
	mov	x23, x0
	mov	x0, 16384
	bl	malloc
	mov	x25, x23
	ldr	x4, [sp, 104]
	asr	x1, x28, 6
	mov	x22, x0
	cbz	x1, .L136
	asr	x2, x19, 6
	asr	x13, x27, 6
	lsl	x19, x27, 8
	lsl	x23, x28, 8
	lsl	x24, x27, 4
	cbz	x2, .L137
	adrp	x3, .LC2
	lsl	x11, x1, 6
	lsl	x23, x28, 8
	lsl	x24, x27, 4
	mov	x7, 0
	lsl	x0, x27, 2
	add	x6, x25, 16384
	mov	x9, x20
	ldr	q0, [x3, #:lo12:.LC2]
	lsl	x15, x28, 2
	mov	x5, x1
	mov	x3, x28
	mov	x8, x20
	mov	x28, x22
	mov	x20, x4
	mov	x22, x7
	mov	x1, x19
	mov	x7, x25
	mov	x19, x11
	mov	x10, x21
	mov	x11, x24
	mov	x25, x6
	mov	x24, x0
	mov	x4, x23
.L138:
	add	x0, x20, x22, lsl 2
	mov	x12, x22
	mov	x17, x5
	mov	x22, x0
	mov	x21, 0
	mov	x0, x19
	add	x23, x28, 256
	mov	x19, x21
	mov	x16, x10
	mov	x14, x20
	mov	x5, x25
.L147:
	lsl	w18, w19, 6
	mov	x10, x22
	mov	x6, x7
.L139:
	ldp	q1, q2, [x10]
	stp	q1, q2, [x6]
	ldp	q1, q2, [x10, 32]
	stp	q1, q2, [x6, 32]
	ldp	q1, q2, [x10, 64]
	stp	q1, q2, [x6, 64]
	ldp	q1, q2, [x10, 96]
	stp	q1, q2, [x6, 96]
	ldp	q1, q2, [x10, 128]
	stp	q1, q2, [x6, 128]
	ldp	q1, q2, [x10, 160]
	stp	q1, q2, [x6, 160]
	ldp	q1, q2, [x10, 192]
	stp	q1, q2, [x6, 192]
	ldp	q1, q2, [x10, 224]
	add	x10, x10, x15
	stp	q1, q2, [x6, 224]
	add	x6, x6, 256
	cmp	x5, x6
	bne	.L139
	cbz	x13, .L140
	uxtw	x25, w18
	mov	x30, x0
	mov	x18, x12
	add	x20, x28, 16384
	mov	x12, x26
	mov	x10, x22
	mul	x25, x25, x27
	mov	x6, 0
	mov	x21, 1
	add	x25, x26, x25, lsl 2
	mov	x26, x9
	mov	x0, x25
.L141:
	mov	x25, x26
	mov	x22, x28
	.p2align 3,,7
.L142:
	ldp	q1, q2, [x25]
	stp	q1, q2, [x22]
	ldp	q1, q2, [x25, 32]
	stp	q1, q2, [x22, 32]
	ldp	q1, q2, [x25, 64]
	stp	q1, q2, [x22, 64]
	ldp	q1, q2, [x25, 96]
	stp	q1, q2, [x22, 96]
	ldp	q1, q2, [x25, 128]
	stp	q1, q2, [x22, 128]
	ldp	q1, q2, [x25, 160]
	stp	q1, q2, [x22, 160]
	ldp	q1, q2, [x25, 192]
	stp	q1, q2, [x22, 192]
	ldp	q1, q2, [x25, 224]
	add	x25, x25, x24
	stp	q1, q2, [x22, 224]
	add	x22, x22, 256
	cmp	x20, x22
	bne	.L142
	mov	x22, x7
	stp	x10, x19, [sp, 136]
	mov	x19, x5
	stp	x24, x16, [sp, 216]
	mov	x24, x0
	stp	x20, x1, [sp, 264]
	mov	x20, x11
	stp	x30, x18, [sp, 104]
	stp	x9, x7, [sp, 120]
	str	x15, [sp, 152]
	stp	x26, x17, [sp, 168]
	stp	x2, x13, [sp, 184]
	stp	x0, x6, [sp, 200]
	stp	x3, x14, [sp, 232]
	stp	x8, x12, [sp, 248]
	str	x4, [sp, 280]
.L143:
	mov	x26, x24
	mov	x25, x28
.L144:
	add	x0, sp, 512
	str	x22, [sp, 384]
	str	x25, [sp, 416]
	add	x2, sp, 288
	stp	x26, x27, [sp, 440]
	add	x1, sp, 320
	add	x25, x25, 64
	str	q0, [x0, -120]
	add	x26, x26, 64
	ldp	x4, x5, [sp, 384]
	str	q0, [x0, -88]
	stp	x4, x5, [sp, 352]
	ldp	x4, x5, [sp, 416]
	stp	x4, x5, [sp, 320]
	str	x21, [sp, 456]
	ldr	x3, [sp, 400]
	ldp	x4, x5, [x0, -72]
	str	x3, [sp, 368]
	ldr	x3, [sp, 432]
	add	x0, sp, 352
	stp	x4, x5, [sp, 288]
	str	x21, [sp, 304]
	str	x3, [sp, 336]
	bl	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.1
	adrp	x0, .LC2
	cmp	x23, x25
	ldr	q0, [x0, #:lo12:.LC2]
	bne	.L144
	add	x22, x22, 1024
	add	x24, x24, x20
	cmp	x19, x22
	bne	.L143
	ldp	x0, x6, [sp, 200]
	mov	x5, x19
	ldp	x26, x17, [sp, 168]
	mov	x11, x20
	ldp	x2, x13, [sp, 184]
	add	x6, x6, 1
	add	x0, x0, 256
	ldp	x30, x18, [sp, 104]
	add	x26, x26, 256
	ldp	x9, x7, [sp, 120]
	ldp	x10, x19, [sp, 136]
	ldr	x15, [sp, 152]
	ldp	x24, x16, [sp, 216]
	ldp	x3, x14, [sp, 232]
	ldp	x8, x12, [sp, 248]
	ldp	x20, x1, [sp, 264]
	ldr	x4, [sp, 280]
	cmp	x13, x6
	bne	.L141
	mov	x26, x12
	mov	x0, x30
	mov	x22, x10
	mov	x12, x18
.L140:
	add	x19, x19, 1
	add	x22, x22, x4
	cmp	x2, x19
	bne	.L147
	add	x22, x12, 64
	mov	x25, x5
	mov	x19, x0
	mov	x10, x16
	mov	x20, x14
	mov	x5, x17
	add	x9, x9, x1
	cmp	x0, x22
	bne	.L138
	mov	x22, x28
	mov	x19, x1
	mov	x23, x4
	mov	x25, x7
	mov	x21, x16
	mov	x28, x3
	mov	x24, x11
	mov	x1, x17
	mov	x4, x14
	mov	x20, x8
.L137:
	lsl	x3, x2, 4
	lsl	x0, x13, 6
	asr	x12, x27, 4
	stp	x26, x25, [sp, 104]
	mov	x25, x28
	mul	x6, x3, x27
	stp	x22, x21, [sp, 120]
	mul	x3, x3, x28
	mov	x22, x20
	str	x23, [sp, 200]
	add	x5, x26, x6, lsl 4
	stp	x0, x5, [sp, 168]
	ubfx	x0, x27, 4, 2
	str	x0, [sp, 144]
	and	x0, x21, 15
	str	x0, [sp, 136]
	lsl	x0, x28, 4
	mov	x23, x24
	mov	x28, x27
	mov	x26, x12
	mov	x24, x2
	mov	x21, x1
	mov	x27, x4
	str	x0, [sp, 152]
	mov	x0, 0
	mov	x20, x0
	lsl	x3, x3, 2
	mov	x6, 1
	stp	x3, x19, [sp, 184]
.L148:
	cbz	x24, .L160
.L153:
	ldr	x0, [sp, 144]
	cbz	x0, .L161
	lsl	w19, w20, 6
	mov	x8, x25
	ldr	x10, [sp, 104]
	sxtw	x0, w19
	add	x3, x27, w19, sxtw 2
	mov	x1, x27
	mov	x25, x3
	mov	w2, w19
	mul	x0, x0, x28
	mov	x7, x23
	mov	x4, x26
	mov	x23, x24
	mov	x5, 0
	mov	x26, x21
	add	x0, x22, x0, lsl 2
	mov	x19, x5
	mov	x27, x0
	mov	x3, x8
	mov	x0, x20
	mov	x24, x10
.L162:
	ldr	x21, [sp, 168]
	mov	x10, x26
	mov	x11, x23
	mov	x26, x25
	mov	x13, x22
	mov	x20, 0
	mov	x25, x24
	mov	x12, x19
	mov	x23, x20
	mov	x22, x21
.L152:
	lsl	x5, x22, 2
	mov	x21, x26
	add	x24, x5, x27
	add	x19, x25, x5
	stp	x25, x26, [sp, 208]
	mov	x25, x10
	mov	x26, x11
	stp	x27, x22, [sp, 224]
	mov	x27, x0
	mov	x22, x3
	stp	x23, x1, [sp, 240]
	mov	x23, x7
	mov	w20, 16
	str	w2, [sp, 256]
.L149:
	ldr	x0, [sp, 152]
	stp	x21, x22, [sp, 464]
	add	x2, sp, 288
	ldp	x8, x9, [sp, 464]
	add	x21, x21, x0
	add	x0, sp, 704
	stp	x8, x9, [sp, 352]
	add	x1, sp, 320
	stp	x6, x24, [sp, 480]
	stp	x28, x6, [sp, 496]
	ldp	x8, x9, [x0, -216]
	add	x0, sp, 512
	stp	x8, x9, [sp, 320]
	str	x19, [sp, 512]
	add	x19, x19, x23
	str	x28, [sp, 520]
	str	x6, [sp, 528]
	stp	x12, x13, [sp, 264]
	ldp	x8, x9, [x0]
	add	x0, sp, 352
	str	x4, [sp, 280]
	stp	x8, x9, [sp, 288]
	str	x6, [sp, 304]
	str	x6, [sp, 336]
	str	x6, [sp, 368]
	bl	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.1
	ldp	x12, x13, [sp, 264]
	subs	w20, w20, #1
	ldr	x4, [sp, 280]
	mov	x6, 1
	bne	.L149
	mov	x7, x23
	mov	x0, x27
	ldp	x23, x1, [sp, 240]
	mov	x3, x22
	ldp	x27, x22, [sp, 224]
	mov	x10, x25
	ldr	x5, [sp, 144]
	mov	x11, x26
	add	x23, x23, x6
	ldr	w2, [sp, 256]
	ldp	x25, x26, [sp, 208]
	add	x22, x22, 16
	cmp	x5, x23
	bne	.L152
	ldr	x5, [sp, 200]
	mov	x24, x25
	mov	x25, x26
	add	x19, x12, 1
	add	x25, x25, x5
	mov	x23, x11
	ldr	x5, [sp, 192]
	mov	x26, x10
	mov	x22, x13
	add	x24, x24, x5
	cmp	x11, x19
	bne	.L162
	mov	w19, w2
	mov	x8, x7
	mov	x7, x3
	mov	x21, x0
	ldr	x3, [sp, 136]
	sxtw	x0, w19
	mov	x25, x10
	mov	x26, x11
	mov	x2, x13
	mov	x9, x4
	mul	x20, x0, x28
	cbnz	x3, .L235
.L226:
	mov	x24, x26
	mov	x20, x21
	mov	x27, x1
	mov	x21, x25
	mov	x22, x2
	mov	x25, x7
	mov	x23, x8
	mov	x26, x9
.L154:
	add	x20, x20, 1
	cmp	x21, x20
	bne	.L148
.L228:
	mov	x1, x21
	mov	x4, x27
	mov	x20, x22
	mov	x27, x28
	ldp	x22, x21, [sp, 120]
	mov	x28, x25
	ldp	x26, x25, [sp, 104]
.L136:
	asr	x12, x27, 4
	ldr	x0, [sp, 160]
	and	x19, x0, 3
	cbnz	x21, .L163
.L180:
	lsl	x0, x21, 2
	lsl	x11, x27, 2
	mov	x6, 0
	mul	x3, x0, x28
	mul	x0, x0, x27
	lsl	x5, x3, 2
.L164:
	add	x3, x3, x28
	add	x12, x4, x5
	mov	x2, x20
	add	x9, x26, x0, lsl 2
	lsl	x5, x3, 2
	mov	x1, 0
	add	x10, x4, x5
.L184:
	ldr	s0, [x9, x1, lsl 2]
	mov	x8, x2
	mov	x7, x12
.L182:
	ldr	s1, [x8]
	add	x8, x8, x11
	ldr	s2, [x7], 4
	fmadd	s0, s2, s1, s0
	str	s0, [x9, x1, lsl 2]
	cmp	x10, x7
	bne	.L182
	add	x1, x1, 1
	add	x2, x2, 4
	cmp	x27, x1
	bne	.L184
	add	x6, x6, 1
	add	x0, x0, x27
	cmp	x6, x19
	blt	.L164
	b	.L181
.L221:
	add	x20, x20, 1
	cmp	x20, x21
	beq	.L228
.L161:
	cbz	x26, .L221
	lsl	w19, w20, 6
.L234:
	mov	x7, x25
	mov	x9, x26
	mov	x25, x21
	mov	x1, x27
	mov	x21, x20
	mov	x2, x22
	mov	x8, x23
	mov	x26, x24
.L159:
	ldr	x3, [sp, 136]
	sxtw	x0, w19
	mul	x20, x0, x28
	cbz	x3, .L226
.L235:
	ldp	x23, x3, [sp, 176]
	mov	x4, x7
	add	x20, x2, x20, lsl 2
	mov	x10, x21
	mov	x7, x26
	add	x27, sp, 584
	mov	x21, x20
	mov	x26, x4
	mov	x22, 0
	add	x0, x0, x3
	add	x3, sp, 536
	add	x19, x1, x0, lsl 2
	mov	x0, x25
	mov	x25, x19
.L155:
	mov	x20, x23
	mov	x19, x25
	stp	x23, x22, [sp, 208]
	mov	x23, x0
	mov	x22, x8
	stp	x25, x1, [sp, 224]
	mov	x25, x7
	mov	x24, 0
	str	x2, [sp, 240]
.L156:
	add	x4, sp, 536
	add	x5, sp, 576
	ldr	x0, [sp, 152]
	add	x2, sp, 288
	stp	x19, x26, [x4]
	add	x1, sp, 320
	add	x19, x19, x0
	add	x0, sp, 512
	stp	x6, x20, [x5]
	add	x24, x24, 1
	stp	x28, x6, [x5, 16]
	add	x20, x20, x22
	stp	x21, x28, [x4, 24]
	ldp	x4, x5, [x3]
	stp	x4, x5, [sp, 352]
	ldp	x4, x5, [x0, 48]
	stp	x4, x5, [sp, 320]
	add	x0, sp, 352
	ldp	x4, x5, [x27]
	stp	x10, x9, [sp, 248]
	stp	x4, x5, [sp, 288]
	str	x6, [sp, 304]
	str	x6, [sp, 336]
	str	x6, [sp, 368]
	str	x6, [sp, 552]
	bl	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.1
	ldr	x0, [sp, 136]
	add	x3, sp, 536
	ldp	x10, x9, [sp, 248]
	mov	x6, 1
	cmp	x0, x24
	bne	.L156
	mov	x0, x23
	mov	x8, x22
	ldp	x23, x22, [sp, 208]
	mov	x7, x25
	ldp	x25, x1, [sp, 224]
	add	x21, x21, 64
	ldr	x2, [sp, 240]
	add	x22, x22, x6
	add	x23, x23, 64
	cmp	x9, x22
	bne	.L155
	mov	x25, x0
	add	x21, x10, x6
	mov	x0, x26
	mov	x26, x7
	mov	x7, x0
	cmp	x25, x21
	beq	.L157
	cbz	x26, .L236
	mov	x24, x26
	mov	x20, x21
	mov	x27, x1
	mov	x21, x25
	mov	x22, x2
	mov	x25, x0
	mov	x23, x8
	mov	x26, x9
	b	.L153
.L236:
	lsl	w19, w21, 6
	b	.L159
.L157:
	ldp	x22, x21, [sp, 120]
	mov	x27, x28
	mov	x4, x1
	mov	x28, x0
	ldr	x0, [sp, 160]
	mov	x1, x25
	ldp	x26, x25, [sp, 104]
	mov	x20, x2
	mov	x12, x9
	and	x19, x0, 3
.L163:
	and	x0, x28, 63
	cbz	x12, .L185
	cbnz	x0, .L237
.L166:
	lsl	x12, x12, 4
	ands	x0, x27, 15
	bne	.L165
.L174:
	cbnz	x19, .L180
.L181:
	mov	x0, x25
	bl	free
	ldp	x29, x30, [sp]
	mov	x0, x22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	add	sp, sp, 608
	.cfi_remember_state
	.cfi_restore 29
	.cfi_restore 30
	.cfi_restore 27
	.cfi_restore 28
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	b	free
.L185:
	.cfi_restore_state
	mov	x0, x27
	mov	x12, 0
.L165:
	add	x3, x0, x12
	mov	w16, w21
	lsl	x14, x27, 2
	add	x15, x20, x12, lsl 2
	mov	w7, 0
	mov	w6, 0
.L175:
	sxtw	x0, w7
	mov	w8, 4
	mul	x2, x28, x0
	mul	x0, x27, x0
	lsl	x5, x2, 2
	add	x0, x26, x0, lsl 2
.L178:
	add	x2, x2, x28
	add	x17, x4, x5
	mov	x1, x12
	mov	x9, x15
	lsl	x5, x2, 2
	add	x13, x4, x5
.L176:
	ldr	s0, [x0, x1, lsl 2]
	mov	x11, x9
	mov	x10, x17
.L177:
	ldr	s1, [x11]
	add	x11, x11, x14
	ldr	s2, [x10], 4
	fmadd	s0, s2, s1, s0
	str	s0, [x0, x1, lsl 2]
	cmp	x13, x10
	bne	.L177
	add	x1, x1, 1
	add	x9, x9, 4
	cmp	x3, x1
	bne	.L176
	add	x0, x0, x14
	subs	w8, w8, #1
	bne	.L178
	add	w6, w6, 1
	add	w7, w7, 4
	cmp	w6, w16
	bne	.L175
	b	.L174
.L237:
	lsl	x2, x1, 6
	mov	w5, w21
	add	x18, x0, x2
	lsl	x8, x27, 2
	mov	w9, 4
	mov	w3, 0
	mul	x24, x2, x27
.L167:
	lsl	w15, w3, 2
	mov	w17, w12
	mov	w10, 0
	mov	w1, 0
.L173:
	sxtw	x14, w10
	mov	w7, w15
	add	x0, x14, x24
	add	x30, x14, 16
	str	x25, [sp, 112]
	add	x6, x20, x0, lsl 2
.L172:
	sxtw	x0, w7
	mov	x23, x14
	mov	x25, x6
	mul	x16, x0, x28
	mul	x0, x0, x27
	add	x11, x16, x2
	add	x16, x18, x16
	add	x0, x26, x0, lsl 2
	add	x16, x4, x16, lsl 2
	add	x11, x4, x11, lsl 2
	str	x11, [sp, 104]
.L169:
	ldr	x11, [sp, 104]
	mov	x13, x25
	ldr	s0, [x0, x23, lsl 2]
.L168:
	ldr	s1, [x13]
	add	x13, x13, x8
	ldr	s2, [x11], 4
	fmadd	s0, s2, s1, s0
	str	s0, [x0, x23, lsl 2]
	cmp	x16, x11
	bne	.L168
	add	x23, x23, 1
	add	x25, x25, 4
	cmp	x30, x23
	bne	.L169
	add	w7, w7, 1
	cmp	w9, w7
	bne	.L172
	add	w1, w1, 1
	add	w10, w10, 16
	ldr	x25, [sp, 112]
	cmp	w1, w17
	bne	.L173
	add	w3, w3, 1
	add	w9, w9, 4
	cmp	w3, w5
	bne	.L167
	b	.L166
.L160:
	lsl	w19, w20, 6
	cbnz	x26, .L234
	b	.L154
	.cfi_endproc
.LFE8117:
	.size	_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_, .-_Z11sgemm_exo_gP18c_code_str_ContextlllPfS1_S1_
	.section	.text._ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv,"axG",@progbits,_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv,comdat
	.align	2
	.p2align 4,,11
	.weak	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	.type	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv, %function
_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv:
.LFB8993:
	.cfi_startproc
	adrp	x2, .LC4
	adrp	x1, .LC3
	add	x5, x0, 1816
	ldr	q5, [x2, #:lo12:.LC4]
	adrp	x2, .LC5
	ldr	q6, [x1, #:lo12:.LC3]
	add	x1, x0, 8
	ldr	q4, [x2, #:lo12:.LC5]
	adrp	x2, .LC6
	ldr	q1, [x2, #:lo12:.LC6]
	.p2align 3,,7
.L239:
	add	x1, x1, 16
	ldr	q0, [x1, -24]
	ldr	q3, [x1, -16]
	and	v0.16b, v0.16b, v6.16b
	ldr	q2, [x1, 3152]
	and	v3.16b, v3.16b, v5.16b
	orr	v0.16b, v0.16b, v3.16b
	ushr	v3.2d, v0.2d, 1
	and	v0.16b, v0.16b, v4.16b
	eor	v2.16b, v2.16b, v3.16b
	cmeq	v0.2d, v0.2d, #0
	eor	v3.16b, v2.16b, v1.16b
	bsl	v0.16b, v2.16b, v3.16b
	str	q0, [x1, -24]
	cmp	x5, x1
	bne	.L239
	ldr	x2, [x0, 1808]
	add	x6, x0, 1824
	ldr	x4, [x0, 1816]
	mov	x3, 0
	ldr	x1, [x0, 4984]
	bfi	x2, x4, 0, 31
	adrp	x4, .LC3
	eor	x1, x1, x2, lsr 1
	tst	x2, 1
	adrp	x2, .LC5
	ldr	q6, [x4, #:lo12:.LC3]
	adrp	x4, .LC4
	ldr	q4, [x2, #:lo12:.LC5]
	fmov	x2, d1
	ldr	q5, [x4, #:lo12:.LC4]
	adrp	x4, .LC6
	ldr	q3, [x4, #:lo12:.LC6]
	eor	x2, x1, x2
	csel	x1, x2, x1, ne
	str	x1, [x0, 1808]
.L241:
	ldr	q0, [x5, x3]
	ldr	q2, [x6, x3]
	and	v0.16b, v0.16b, v6.16b
	ldr	q1, [x0, x3]
	and	v2.16b, v2.16b, v5.16b
	orr	v0.16b, v0.16b, v2.16b
	ushr	v2.2d, v0.2d, 1
	and	v0.16b, v0.16b, v4.16b
	eor	v1.16b, v1.16b, v2.16b
	cmeq	v0.2d, v0.2d, #0
	eor	v2.16b, v1.16b, v3.16b
	bsl	v0.16b, v1.16b, v2.16b
	str	q0, [x5, x3]
	add	x3, x3, 16
	cmp	x3, 3168
	bne	.L241
	ldr	x3, [x0]
	str	xzr, [x0, 4992]
	ldr	x1, [x0, 4984]
	ldr	x2, [x0, 3168]
	bfi	x1, x3, 0, 31
	eor	x2, x2, x1, lsr 1
	tst	x1, 1
	fmov	x1, d3
	eor	x1, x2, x1
	csel	x2, x1, x2, ne
	str	x2, [x0, 4984]
	ret
	.cfi_endproc
.LFE8993:
	.size	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv, .-_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC7:
	.string	"cannot create std::vector larger than max_size()"
	.text
	.align	2
	.p2align 4,,11
	.type	_ZL10gen_matrixll, %function
_ZL10gen_matrixll:
.LFB8118:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA8118
	stp	x29, x30, [sp, -96]!
	.cfi_def_cfa_offset 96
	.cfi_offset 29, -96
	.cfi_offset 30, -88
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -80
	.cfi_offset 20, -72
	mov	x19, x8
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -64
	.cfi_offset 22, -56
	mov	x21, x0
	adrp	x22, .LANCHOR1
	add	x22, x22, :lo12:.LANCHOR1
	stp	x23, x24, [sp, 48]
	.cfi_offset 23, -48
	.cfi_offset 24, -40
	mov	x23, x1
	ldar	x0, [x22]
	tbnz	x0, 0, .L250
	mov	x0, x22
	bl	__cxa_guard_acquire
	cbnz	w0, .L282
.L250:
	add	x0, x22, 8
	ldar	x1, [x0]
	tbnz	x1, 0, .L253
	bl	__cxa_guard_acquire
	cbnz	w0, .L283
.L253:
	mul	x20, x21, x23
	mov	x0, 2305843009213693951
	cmp	x20, x0
	bgt	.L284
	stp	xzr, xzr, [x19]
	lsl	x22, x20, 2
	mov	x0, x22
	str	xzr, [x19, 16]
.LEHB2:
	bl	_Znwm
.LEHE2:
	mov	x24, x0
	add	x23, x0, x22
	str	x0, [x19]
	str	x23, [x19, 16]
	mov	x21, x0
	str	wzr, [x24], 4
	cmp	x20, 1
	beq	.L257
	cmp	x24, x23
	beq	.L258
	sub	x2, x22, #4
	mov	x0, x24
	mov	w1, 0
	bl	memset
.L258:
	mov	x24, x23
.L257:
	str	x24, [x19, 8]
	cmp	x24, x21
	beq	.L248
	adrp	x1, _ZZL10gen_matrixllE3rng
	add	x20, x1, :lo12:_ZZL10gen_matrixllE3rng
	mov	x0, 4895412794951729152
	mov	x1, 4751297606875873280
	mov	x23, 22144
	mov	x22, 4022730752
	movk	x23, 0x9d2c, lsl 16
	stp	d8, d9, [sp, 64]
	.cfi_offset 73, -24
	.cfi_offset 72, -32
	fmov	d9, x0
	mov	x0, 4323455642275676160
	stp	d10, d11, [sp, 80]
	.cfi_offset 75, -8
	.cfi_offset 74, -16
	fmov	d10, x1
	ldr	x1, [x20, 4992]
	fmov	d11, x0
	b	.L265
	.p2align 2,,3
.L260:
	ldr	x0, [x20, x1, lsl 3]
	add	x2, x1, 1
	str	x2, [x20, 4992]
	ubfx	x1, x0, 11, 32
	eor	x0, x0, x1
	and	x1, x23, x0, lsl 7
	eor	x0, x0, x1
	and	x1, x22, x0, lsl 15
	eor	x0, x0, x1
	eor	x0, x0, x0, lsr 18
	ucvtf	d8, x0
	cmp	x2, 623
	bhi	.L285
.L261:
	ldr	x0, [x20, x2, lsl 3]
	add	x1, x2, 1
	str	x1, [x20, 4992]
	ubfx	x2, x0, 11, 32
	eor	x0, x0, x2
	and	x2, x23, x0, lsl 7
	eor	x0, x0, x2
	and	x2, x22, x0, lsl 15
	eor	x0, x0, x2
	eor	x0, x0, x0, lsr 18
	ucvtf	d0, x0
	fmadd	d0, d0, d10, d8
	fcmpe	d0, d9
	bge	.L262
	fmov	d1, -1.0e+0
	fmadd	d0, d0, d11, d1
	fcvt	s0, d0
	str	s0, [x21], 4
	cmp	x24, x21
	beq	.L281
.L265:
	cmp	x1, 623
	bls	.L260
	mov	x0, x20
	bl	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	ldr	x1, [x20, 4992]
	b	.L260
	.p2align 2,,3
.L285:
	mov	x0, x20
	bl	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	ldr	x2, [x20, 4992]
	b	.L261
	.p2align 2,,3
.L262:
	fmov	s0, 1.0e+0
	str	s0, [x21], 4
	cmp	x24, x21
	bne	.L265
	.p2align 3,,7
.L281:
	ldp	d8, d9, [sp, 64]
	.cfi_restore 73
	.cfi_restore 72
	ldp	d10, d11, [sp, 80]
	.cfi_restore 75
	.cfi_restore 74
.L248:
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
.L283:
	.cfi_restore_state
	adrp	x0, _ZZL10gen_matrixllE2rd
	add	x0, x0, :lo12:_ZZL10gen_matrixllE2rd
.LEHB3:
	bl	_ZNSt13random_device9_M_getvalEv
.LEHE3:
	adrp	x1, _ZZL10gen_matrixllE3rng
	mov	x4, 35173
	add	x20, x1, :lo12:_ZZL10gen_matrixllE3rng
	uxtw	x2, w0
	mov	x3, 1
	str	x2, [x1, #:lo12:_ZZL10gen_matrixllE3rng]
	movk	x4, 0x6c07, lsl 16
	.p2align 3,,7
.L255:
	eor	x2, x2, x2, lsr 30
	madd	w2, w2, w4, w3
	str	x2, [x20, x3, lsl 3]
	add	x3, x3, 1
	cmp	x3, 624
	bne	.L255
	add	x0, x22, 8
	str	x3, [x20, 4992]
	bl	__cxa_guard_release
	b	.L253
.L282:
	adrp	x20, _ZZL10gen_matrixllE2rd
	add	x20, x20, :lo12:_ZZL10gen_matrixllE2rd
	mov	x0, x20
.LEHB4:
	bl	_ZNSt13random_deviceC1Ev
.LEHE4:
	mov	x1, x20
	adrp	x2, __dso_handle
	add	x2, x2, :lo12:__dso_handle
	adrp	x0, _ZNSt13random_deviceD1Ev
	add	x0, x0, :lo12:_ZNSt13random_deviceD1Ev
	bl	__cxa_atexit
	mov	x0, x22
	bl	__cxa_guard_release
	b	.L250
.L284:
	adrp	x0, .LC7
	add	x0, x0, :lo12:.LC7
	stp	d8, d9, [sp, 64]
	.cfi_remember_state
	.cfi_offset 73, -24
	.cfi_offset 72, -32
	stp	d10, d11, [sp, 80]
	.cfi_offset 75, -8
	.cfi_offset 74, -16
.LEHB5:
	bl	_ZSt20__throw_length_errorPKc
.L268:
	.cfi_restore_state
	mov	x19, x0
	mov	x0, x22
	stp	d8, d9, [sp, 64]
	.cfi_remember_state
	.cfi_offset 73, -24
	.cfi_offset 72, -32
	stp	d10, d11, [sp, 80]
	.cfi_offset 75, -8
	.cfi_offset 74, -16
	bl	__cxa_guard_abort
	mov	x0, x19
	bl	_Unwind_Resume
.L269:
	.cfi_restore_state
	mov	x19, x0
	add	x0, x22, 8
	stp	d8, d9, [sp, 64]
	.cfi_offset 73, -24
	.cfi_offset 72, -32
	stp	d10, d11, [sp, 80]
	.cfi_offset 75, -8
	.cfi_offset 74, -16
	bl	__cxa_guard_abort
	mov	x0, x19
	bl	_Unwind_Resume
.LEHE5:
	.cfi_endproc
.LFE8118:
	.section	.gcc_except_table,"a",@progbits
.LLSDA8118:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE8118-.LLSDACSB8118
.LLSDACSB8118:
	.uleb128 .LEHB2-.LFB8118
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB3-.LFB8118
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L269-.LFB8118
	.uleb128 0
	.uleb128 .LEHB4-.LFB8118
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L268-.LFB8118
	.uleb128 0
	.uleb128 .LEHB5-.LFB8118
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
.LLSDACSE8118:
	.text
	.size	_ZL10gen_matrixll, .-_ZL10gen_matrixll
	.section	.rodata.str1.8
	.align	3
.LC8:
	.string	"Usage: %s <n>\n"
	.align	3
.LC9:
	.string	"n < 1!!"
	.align	3
.LC10:
	.string	"\n\n\n"
	.align	3
.LC11:
	.string	"Multiplying two %d x %d matrices\n"
	.align	3
.LC12:
	.string	"-----------------------------------------------------------"
	.align	3
.LC13:
	.string	"  Exo SGEMM took %5.1lf ms, or %4.1lf GFLOPS. That's %4.1lf percent of peak.\n"
	.align	3
.LC14:
	.string	"  Gilbert SGEMM took %5.1lf ms, or %4.1lf GFLOPS. That's %4.1lf percent of peak.\n"
	.section	.text.startup,"ax",@progbits
	.align	2
	.p2align 4,,11
	.global	main
	.type	main, %function
main:
.LFB8132:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA8132
	sub	sp, sp, #1712
	.cfi_def_cfa_offset 1712
	stp	x29, x30, [sp]
	.cfi_offset 29, -1712
	.cfi_offset 30, -1704
	mov	x29, sp
	cmp	w0, 2
	beq	.L287
	ldr	x1, [x1]
	adrp	x0, .LC8
	add	x0, x0, :lo12:.LC8
.LEHB6:
	bl	printf
.L288:
	mov	w0, 1
.L286:
	ldp	x29, x30, [sp]
	add	sp, sp, 1712
	.cfi_remember_state
	.cfi_restore 29
	.cfi_restore 30
	.cfi_def_cfa_offset 0
	ret
.L287:
	.cfi_restore_state
	ldr	x0, [x1, 8]
	mov	w2, 10
	mov	x1, 0
	stp	x23, x24, [sp, 48]
	.cfi_offset 24, -1656
	.cfi_offset 23, -1664
	bl	strtol
	str	w0, [sp, 1288]
	mov	x23, x0
	cmp	w0, 0
	ble	.L516
	sxtw	x24, w0
	add	x8, sp, 1472
	mov	x1, x24
	mov	x0, x24
	stp	x19, x20, [sp, 16]
	.cfi_offset 20, -1688
	.cfi_offset 19, -1696
	stp	x21, x22, [sp, 32]
	.cfi_offset 22, -1672
	.cfi_offset 21, -1680
	stp	x25, x26, [sp, 64]
	.cfi_offset 26, -1640
	.cfi_offset 25, -1648
	stp	x27, x28, [sp, 80]
	.cfi_offset 28, -1624
	.cfi_offset 27, -1632
	stp	d8, d9, [sp, 96]
	.cfi_offset 73, -1608
	.cfi_offset 72, -1616
	stp	d10, d11, [sp, 112]
	.cfi_offset 75, -1592
	.cfi_offset 74, -1600
	bl	_ZL10gen_matrixll
.LEHE6:
	mov	x1, x24
	mov	x0, x24
	add	x8, sp, 1496
.LEHB7:
	bl	_ZL10gen_matrixll
.LEHE7:
	add	x8, sp, 1520
	mov	x1, x24
	mov	x0, x24
.LEHB8:
	bl	_ZL10gen_matrixll
.LEHE8:
	ldr	x21, [sp, 1520]
	ldr	x19, [sp, 1528]
	subs	x28, x19, x21
	beq	.L290
	mov	x0, 9223372036854775804
	cmp	x28, x0
	bhi	.L517
	mov	x0, x28
.LEHB9:
	bl	_Znwm
.LEHE9:
	mov	x25, x0
	cmp	x19, x21
	beq	.L518
.L293:
	mov	x2, x28
	mov	x1, x21
	mov	x0, x25
	bl	memmove
	adrp	x0, .LC10
	add	x0, x0, :lo12:.LC10
.LEHB10:
	bl	puts
.LEHE10:
	adrp	x0, .LC11
	mov	w2, w23
	add	x0, x0, :lo12:.LC11
	mov	w1, w23
.LEHB11:
	bl	printf
.LEHE11:
.L296:
	smull	x0, w23, w23
	and	x3, x24, -64
	and	x19, x23, 63
	asr	x1, x24, 6
	add	x4, x19, x3
	asr	x9, x24, 4
	lsl	x2, x24, 3
	mul	x27, x24, x3
	mul	x0, x0, x24
	mov	x20, x1
	fmov	d0, x0
	lsl	x1, x1, 8
	str	x3, [sp, 168]
	and	x3, x24, -16
	shl	d8, d0, 1
	str	x4, [sp, 432]
	lsl	x4, x4, 8
	lsl	x26, x24, 8
	stp	x26, x9, [sp, 152]
	lsl	x22, x24, 2
	str	x3, [sp, 192]
	str	x2, [sp, 208]
	str	x1, [sp, 288]
	str	x27, [sp, 360]
	str	x4, [sp, 424]
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	add	x1, x21, x27, lsl 2
	str	x1, [sp, 312]
	mov	w27, 92
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	str	x20, [sp, 176]
	ldr	x4, [sp, 1496]
	mov	w1, 3
	str	x0, [sp, 408]
	mov	w7, 48
	ldr	x0, [sp, 176]
	smull	x5, w23, w1
	madd	x11, x26, x20, x4
	str	x4, [sp, 136]
	mov	w4, 60
	add	x16, x5, 4
	mov	w17, 12
	mov	w10, 36
	mov	w1, 76
	smull	x7, w23, w7
	smull	x4, w23, w4
	mov	w3, 68
	mov	w8, 44
	smull	x17, w23, w17
	smull	x10, w23, w10
	lsl	x16, x16, 2
	smull	x1, w23, w1
	mov	w9, 40
	mov	w18, 80
	str	x4, [sp, 1104]
	add	x4, x22, 16
	str	x7, [sp, 1136]
	lsl	x7, x0, 14
	lsl	x0, x24, 3
	smull	x8, w23, w8
	mov	w15, 20
	mov	w14, 24
	mov	w13, 28
	mov	w6, 52
	mov	w2, 72
	str	x4, [sp, 232]
	smull	x4, w23, w3
	str	x5, [sp, 392]
	mov	w5, 56
	str	x1, [sp, 1072]
	add	x1, x0, 16
	str	x10, [sp, 1160]
	add	x10, x16, 16
	mov	w20, 84
	str	x1, [sp, 256]
	smull	x1, w23, w18
	str	x4, [sp, 1088]
	add	x4, x22, 32
	str	x8, [sp, 1144]
	add	x8, x17, 48
	stp	x10, x8, [sp, 344]
	smull	x10, w23, w9
	asr	x9, x24, 4
	smull	x15, w23, w15
	smull	x14, w23, w14
	str	x4, [sp, 240]
	smull	x13, w23, w13
	str	x1, [sp, 1064]
	smull	x6, w23, w6
	add	x1, x0, 32
	smull	x4, w23, w2
	add	x0, x0, 48
	smull	x5, w23, w5
	str	x17, [sp, 264]
	str	x1, [sp, 320]
	smull	x1, w23, w20
	str	x16, [sp, 336]
	and	x3, x24, -16
	str	x7, [sp, 400]
	mov	w30, 96
	str	x4, [sp, 1080]
	add	x4, x22, 48
	str	x4, [sp, 248]
	mov	w12, 252
	str	x5, [sp, 1112]
	mov	w20, 10
	str	x6, [sp, 1120]
	lsl	x6, x9, 6
	str	x6, [sp, 304]
	str	x10, [sp, 1152]
	str	x13, [sp, 1184]
	lsl	x13, x19, 2
	str	x14, [sp, 1192]
	add	x14, x11, x9, lsl 6
	str	x15, [sp, 1200]
	and	x15, x23, 15
	ldr	x26, [sp, 1472]
	str	x1, [sp, 1048]
	str	x0, [sp, 328]
	mov	w0, 88
	smull	x0, w23, w0
	str	x0, [sp, 1032]
	add	x0, x15, x3
	str	x0, [sp, 376]
	smull	x0, w23, w27
	str	x0, [sp, 1016]
	and	w0, w23, 63
	str	w0, [sp, 204]
	smull	x0, w23, w30
	str	x0, [sp, 1000]
	lsl	x15, x24, 1
	mov	w0, 100
	mov	x27, x25
	mov	x25, x15
	smull	x0, w23, w0
	str	x0, [sp, 984]
	and	w0, w23, 15
	str	w0, [sp, 200]
	mov	w0, 104
	smull	x0, w23, w0
	str	x0, [sp, 968]
	lsl	x0, x24, 6
	str	x0, [sp, 1224]
	mov	w0, 108
	smull	x0, w23, w0
	str	x0, [sp, 952]
	lsl	x0, x24, 4
	str	x0, [sp, 144]
	mov	w0, 112
	smull	x0, w23, w0
	str	x0, [sp, 936]
	lsl	x0, x24, 5
	str	x0, [sp, 1176]
	mov	w0, 116
	smull	x0, w23, w0
	str	x0, [sp, 920]
	lsl	x0, x24, 7
	str	x0, [sp, 872]
	mov	w0, 120
	smull	x0, w23, w0
	str	x0, [sp, 904]
	mov	w0, 124
	smull	x0, w23, w0
	str	x0, [sp, 888]
	mov	w0, 132
	smull	x0, w23, w0
	str	x0, [sp, 856]
	mov	w0, 136
	smull	x0, w23, w0
	str	x0, [sp, 840]
	mov	w0, 140
	smull	x0, w23, w0
	str	x0, [sp, 824]
	mov	w0, 144
	smull	x0, w23, w0
	str	x0, [sp, 808]
	mov	w0, 148
	smull	x0, w23, w0
	str	x0, [sp, 792]
	mov	w0, 152
	smull	x0, w23, w0
	str	x0, [sp, 776]
	mov	w0, 156
	smull	x0, w23, w0
	str	x0, [sp, 760]
	mov	w0, 160
	smull	x0, w23, w0
	str	x0, [sp, 744]
	mov	w0, 164
	smull	x0, w23, w0
	str	x0, [sp, 728]
	mov	w0, 168
	smull	x0, w23, w0
	str	x0, [sp, 712]
	mov	w0, 172
	smull	x0, w23, w0
	str	x0, [sp, 696]
	mov	w0, 176
	smull	x0, w23, w0
	str	x0, [sp, 680]
	mov	w0, 180
	smull	x0, w23, w0
	str	x0, [sp, 664]
	mov	w0, 184
	smull	x0, w23, w0
	str	x0, [sp, 648]
	mov	w0, 188
	smull	x0, w23, w0
	str	x0, [sp, 632]
	mov	w0, 192
	str	x24, [sp, 184]
	mov	x24, x14
	stp	x23, x21, [sp, 272]
	smull	x0, w23, w0
	str	x0, [sp, 616]
	mov	w0, 196
	smull	x0, w23, w0
	str	x0, [sp, 600]
	mov	w0, 200
	smull	x0, w23, w0
	str	x0, [sp, 584]
	mov	w0, 204
	smull	x0, w23, w0
	str	x0, [sp, 568]
	mov	w0, 208
	smull	x0, w23, w0
	str	x0, [sp, 552]
	mov	w0, 212
	smull	x0, w23, w0
	str	x0, [sp, 536]
	mov	w0, 216
	smull	x0, w23, w0
	str	x0, [sp, 528]
	mov	w0, 220
	smull	x0, w23, w0
	str	x0, [sp, 520]
	mov	w0, 224
	smull	x0, w23, w0
	str	x0, [sp, 512]
	mov	w0, 228
	smull	x0, w23, w0
	str	x0, [sp, 496]
	mov	w0, 232
	smull	x0, w23, w0
	str	x0, [sp, 488]
	mov	w0, 236
	smull	x0, w23, w0
	str	x0, [sp, 480]
	mov	w0, 240
	smull	x0, w23, w0
	str	x0, [sp, 472]
	mov	w0, 244
	smull	x0, w23, w0
	str	x0, [sp, 456]
	mov	w0, 248
	smull	x0, w23, w0
	str	x0, [sp, 448]
	smull	x0, w23, w12
	mov	x23, x11
	mov	x12, x13
	str	x0, [sp, 440]
.L339:
	ldr	x0, [sp, 176]
	cbz	x0, .L299
	str	x27, [sp, 384]
	mov	x27, x22
	adrp	x1, _ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	adrp	x0, _ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk+16384
	add	x1, x1, :lo12:_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	add	x0, x0, :lo12:_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk+16384
	str	x1, [sp, 368]
	str	x0, [sp, 1232]
	str	x12, [sp, 1240]
.L337:
	add	x8, sp, 1248
	str	xzr, [sp, 296]
	ldr	x0, [sp, 136]
	stp	x26, x0, [sp, 216]
	stp	x23, x25, [x8]
	stp	x24, x26, [x8, 16]
	str	x19, [sp, 1280]
	str	w20, [sp, 1292]
	str	x28, [sp, 1296]
.L318:
	ldr	x19, [sp, 152]
	mov	x0, x19
	bl	malloc
	ldr	x1, [sp, 216]
	mov	x22, x0
	add	x2, x19, x0
.L300:
	ldp	q0, q1, [x1]
	stp	q0, q1, [x0]
	ldp	q0, q1, [x1, 32]
	stp	q0, q1, [x0, 32]
	ldp	q0, q1, [x1, 64]
	stp	q0, q1, [x0, 64]
	ldp	q0, q1, [x1, 96]
	stp	q0, q1, [x0, 96]
	ldp	q0, q1, [x1, 128]
	stp	q0, q1, [x0, 128]
	ldp	q0, q1, [x1, 160]
	stp	q0, q1, [x0, 160]
	ldp	q0, q1, [x1, 192]
	stp	q0, q1, [x0, 192]
	ldp	q0, q1, [x1, 224]
	add	x1, x1, x27
	stp	q0, q1, [x0, 224]
	add	x0, x0, 256
	cmp	x2, x0
	bne	.L300
	ldr	x0, [sp, 152]
	mov	w19, 64
	bl	malloc
	mov	x21, x0
	ldr	x20, [sp, 224]
	mov	x4, x0
.L301:
	mov	x1, x20
	mov	x0, x4
	mov	x2, x27
	bl	memcpy
	add	x20, x20, x27
	add	x4, x0, x27
	subs	w19, w19, #1
	bne	.L301
	ldr	x0, [sp, 400]
	mov	x19, x22
	ldr	x28, [sp, 264]
	add	x20, x22, x0
	ldr	x0, [sp, 304]
	ldr	x24, [sp, 280]
	add	x25, x21, x0
	str	x24, [sp, 1216]
.L302:
	ldr	x0, [sp, 368]
	mov	x1, x19
	mov	x2, 16384
	mov	x23, 0
	bl	memcpy
.L307:
	mov	x0, 4096
	bl	malloc
	lsl	x1, x23, 6
	add	x5, x0, 4096
	add	x3, x21, x1
	mov	x2, x0
.L304:
	ldp	q0, q2, [x3]
	ldr	q1, [x3, 32]
	stp	q0, q2, [x2]
	add	x2, x2, 64
	ldr	q0, [x3, 48]
	str	q1, [x2, -32]
	add	x3, x3, x27
	str	q0, [x2, -16]
	cmp	x5, x2
	bne	.L304
	ldp	x6, x7, [sp, 232]
	add	x1, x24, x1
	ldp	x8, x10, [sp, 248]
	ldp	x11, x12, [sp, 320]
	ldp	x13, x14, [sp, 336]
	ldr	x4, [sp, 368]
	ldr	x9, [sp, 208]
	mov	x26, x4
	ldr	x15, [sp, 352]
.L306:
	mov	x2, x0
	ldr	q24, [x1, x27]
	mov	x3, x4
	ldr	q23, [x1, x6]
	ldr	q22, [x1, x7]
	ldr	q21, [x1, x8]
	ldr	q20, [x1, x9]
	ldr	q19, [x1, x10]
	ldr	q18, [x1, x11]
	ldr	q17, [x1, x12]
	ldr	q16, [x1, x28]
	ldr	q11, [x1, x13]
	ldr	q10, [x1, x14]
	ldr	q9, [x1, x15]
	ldp	q28, q27, [x1]
	ldp	q26, q25, [x1, 32]
	.p2align 3,,7
.L305:
	ldp	q5, q2, [x2]
	ldp	q1, q0, [x2, 32]
	add	x2, x2, 64
	ld1r	{v4.4s}, [x3]
	add	x3, x3, 4
	ldr	s6, [x3, 252]
	ldr	s3, [x3, 508]
	fmul	v30.4s, v4.4s, v2.4s
	ldr	s7, [x3, 764]
	fmul	v29.4s, v4.4s, v1.4s
	fmul	v31.4s, v4.4s, v5.4s
	fmul	v4.4s, v4.4s, v0.4s
	fadd	v27.4s, v27.4s, v30.4s
	fadd	v26.4s, v26.4s, v29.4s
	fmul	v30.4s, v5.4s, v6.s[0]
	fmul	v29.4s, v2.4s, v6.s[0]
	fadd	v25.4s, v25.4s, v4.4s
	fmul	v4.4s, v1.4s, v6.s[0]
	fadd	v24.4s, v24.4s, v30.4s
	fmul	v6.4s, v0.4s, v6.s[0]
	fmul	v30.4s, v5.4s, v3.s[0]
	fadd	v23.4s, v23.4s, v29.4s
	fmul	v5.4s, v5.4s, v7.s[0]
	fmul	v29.4s, v2.4s, v3.s[0]
	fadd	v22.4s, v22.4s, v4.4s
	fmul	v2.4s, v2.4s, v7.s[0]
	fmul	v4.4s, v1.4s, v3.s[0]
	fmul	v3.4s, v0.4s, v3.s[0]
	fmul	v1.4s, v1.4s, v7.s[0]
	fmul	v0.4s, v0.4s, v7.s[0]
	fadd	v28.4s, v28.4s, v31.4s
	fadd	v21.4s, v21.4s, v6.4s
	fadd	v20.4s, v20.4s, v30.4s
	fadd	v19.4s, v19.4s, v29.4s
	fadd	v18.4s, v18.4s, v4.4s
	fadd	v17.4s, v17.4s, v3.4s
	fadd	v16.4s, v16.4s, v5.4s
	fadd	v11.4s, v11.4s, v2.4s
	fadd	v10.4s, v10.4s, v1.4s
	fadd	v9.4s, v9.4s, v0.4s
	cmp	x5, x2
	bne	.L305
	stp	q28, q27, [x1]
	add	x4, x4, 1024
	stp	q26, q25, [x1, 32]
	str	q24, [x1, x27]
	str	q23, [x1, x6]
	str	q22, [x1, x7]
	str	q21, [x1, x8]
	str	q20, [x1, x9]
	str	q19, [x1, x10]
	str	q18, [x1, x11]
	str	q17, [x1, x12]
	ldr	x2, [sp, 144]
	str	q16, [x1, x28]
	str	q11, [x1, x13]
	str	q10, [x1, x14]
	str	q9, [x1, x15]
	add	x1, x1, x2
	ldr	x2, [sp, 1232]
	cmp	x2, x4
	bne	.L306
	bl	free
	add	x23, x23, 1
	ldr	x0, [sp, 160]
	cmp	x23, x0
	blt	.L307
	ldr	w0, [sp, 200]
	cbnz	w0, .L519
.L309:
	ldr	x0, [sp, 152]
	add	x19, x19, 16384
	add	x24, x24, x0
	cmp	x20, x19
	bne	.L302
	ldr	w0, [sp, 204]
	cbz	w0, .L315
	ldr	x0, [sp, 424]
	mov	x1, x20
	add	x30, x21, x27
	add	x0, x22, x0
	str	x0, [sp, 416]
	ldr	x0, [sp, 208]
	add	x18, x21, x0
	ldr	x0, [sp, 264]
	add	x17, x21, x0
	ldr	x0, [sp, 144]
	add	x0, x21, x0
	str	x0, [sp, 1208]
	ldr	x0, [sp, 1200]
	add	x16, x21, x0
	ldr	x0, [sp, 1192]
	add	x15, x21, x0
	ldr	x0, [sp, 1184]
	add	x14, x21, x0
	ldr	x0, [sp, 1176]
	add	x0, x21, x0
	str	x0, [sp, 1168]
	ldr	x0, [sp, 1160]
	add	x13, x21, x0
	ldr	x0, [sp, 1152]
	add	x12, x21, x0
	ldr	x0, [sp, 1144]
	add	x11, x21, x0
	ldr	x0, [sp, 1136]
	add	x0, x21, x0
	str	x0, [sp, 1128]
	ldr	x0, [sp, 1120]
	add	x10, x21, x0
	ldr	x0, [sp, 1112]
	add	x9, x21, x0
	ldr	x0, [sp, 1104]
	add	x8, x21, x0
	ldr	x0, [sp, 1224]
	add	x0, x21, x0
	str	x0, [sp, 1096]
	ldr	x0, [sp, 1088]
	add	x7, x21, x0
	ldr	x0, [sp, 1080]
	add	x6, x21, x0
	ldr	x0, [sp, 1072]
	add	x5, x21, x0
	ldr	x0, [sp, 1064]
	add	x0, x21, x0
	str	x0, [sp, 1056]
	ldr	x0, [sp, 1048]
	add	x0, x21, x0
	str	x0, [sp, 1040]
	ldr	x0, [sp, 1032]
	add	x0, x21, x0
	str	x0, [sp, 1024]
	ldr	x0, [sp, 1016]
	add	x0, x21, x0
	str	x0, [sp, 1008]
	ldr	x0, [sp, 1000]
	add	x0, x21, x0
	str	x0, [sp, 992]
	ldr	x0, [sp, 984]
	add	x0, x21, x0
	str	x0, [sp, 976]
	ldr	x0, [sp, 968]
	add	x0, x21, x0
	str	x0, [sp, 960]
	ldr	x0, [sp, 952]
	add	x0, x21, x0
	str	x0, [sp, 944]
	ldr	x0, [sp, 936]
	add	x0, x21, x0
	str	x0, [sp, 928]
	ldr	x0, [sp, 920]
	add	x0, x21, x0
	str	x0, [sp, 912]
	ldr	x0, [sp, 904]
	add	x0, x21, x0
	str	x0, [sp, 896]
	ldr	x0, [sp, 888]
	add	x0, x21, x0
	str	x0, [sp, 880]
	ldr	x0, [sp, 872]
	add	x0, x21, x0
	str	x0, [sp, 864]
	ldr	x0, [sp, 856]
	add	x0, x21, x0
	str	x0, [sp, 848]
	ldr	x0, [sp, 840]
	add	x0, x21, x0
	str	x0, [sp, 832]
	ldr	x0, [sp, 824]
	add	x0, x21, x0
	str	x0, [sp, 816]
	ldr	x0, [sp, 808]
	add	x0, x21, x0
	str	x0, [sp, 800]
	ldr	x0, [sp, 792]
	add	x0, x21, x0
	str	x0, [sp, 784]
	ldr	x0, [sp, 776]
	add	x0, x21, x0
	str	x0, [sp, 768]
	ldr	x0, [sp, 760]
	add	x0, x21, x0
	str	x0, [sp, 752]
	ldr	x0, [sp, 744]
	add	x0, x21, x0
	str	x0, [sp, 736]
	ldr	x0, [sp, 728]
	add	x0, x21, x0
	str	x0, [sp, 720]
	ldr	x0, [sp, 712]
	add	x0, x21, x0
	str	x0, [sp, 704]
	ldr	x0, [sp, 696]
	add	x0, x21, x0
	str	x0, [sp, 688]
	ldr	x0, [sp, 680]
	add	x0, x21, x0
	str	x0, [sp, 672]
	ldr	x0, [sp, 664]
	add	x0, x21, x0
	str	x0, [sp, 656]
	ldr	x0, [sp, 648]
	add	x0, x21, x0
	str	x0, [sp, 640]
	ldr	x0, [sp, 632]
	add	x0, x21, x0
	str	x0, [sp, 624]
	ldr	x0, [sp, 616]
	add	x0, x21, x0
	str	x0, [sp, 608]
	ldr	x0, [sp, 600]
	add	x0, x21, x0
	str	x0, [sp, 592]
	ldr	x0, [sp, 584]
	add	x0, x21, x0
	str	x0, [sp, 576]
	ldr	x0, [sp, 568]
	add	x0, x21, x0
	str	x0, [sp, 560]
	ldr	x0, [sp, 552]
	add	x0, x21, x0
	str	x0, [sp, 544]
	ldr	x0, [sp, 536]
	add	x20, x21, x0
	ldr	x0, [sp, 528]
	add	x28, x21, x0
	ldr	x0, [sp, 520]
	add	x26, x21, x0
	ldr	x0, [sp, 512]
	add	x0, x21, x0
	str	x0, [sp, 504]
	ldr	x0, [sp, 496]
	add	x25, x21, x0
	ldr	x0, [sp, 488]
	ldr	x4, [sp, 312]
	add	x24, x21, x0
	ldr	x0, [sp, 480]
	add	x23, x21, x0
	ldr	x0, [sp, 472]
	add	x0, x21, x0
	str	x0, [sp, 464]
	ldr	x0, [sp, 456]
	add	x19, x21, x0
	ldr	x0, [sp, 448]
	add	x3, x21, x0
	ldr	x0, [sp, 440]
	add	x2, x21, x0
.L316:
	ldp	q24, q23, [x1]
	str	x22, [sp, 1304]
	ldp	q22, q21, [x1, 32]
	mov	x22, x1
	ldp	q20, q19, [x1, 64]
	mov	x0, 0
	ldp	q18, q17, [x1, 96]
	ldp	q16, q7, [x1, 128]
	ldp	q6, q5, [x1, 160]
	ldp	q4, q3, [x1, 192]
	ldp	q2, q1, [x1, 224]
.L317:
	ldr	x1, [sp, 1208]
	ldr	s9, [x16, x0, lsl 2]
	ldr	s11, [x15, x0, lsl 2]
	ldr	s0, [x1, x0, lsl 2]
	ldr	x1, [sp, 1168]
	ins	v0.s[1], v9.s[0]
	ldr	s25, [x30, x0, lsl 2]
	ldr	s27, [x21, x0, lsl 2]
	ldr	s26, [x1, x0, lsl 2]
	ldr	x1, [sp, 1128]
	ins	v27.s[1], v25.s[0]
	ldr	s10, [x14, x0, lsl 2]
	ins	v0.s[2], v11.s[0]
	ldr	s9, [x18, x0, lsl 2]
	ldr	s11, [x13, x0, lsl 2]
	ldr	s28, [x17, x0, lsl 2]
	ins	v27.s[2], v9.s[0]
	ldr	s9, [x1, x0, lsl 2]
	ldr	x1, [sp, 1096]
	ins	v0.s[3], v10.s[0]
	ldr	s25, [x12, x0, lsl 2]
	ins	v26.s[1], v11.s[0]
	ldr	s10, [x10, x0, lsl 2]
	ins	v27.s[3], v28.s[0]
	ldr	s28, [x9, x0, lsl 2]
	ldr	s29, [x8, x0, lsl 2]
	fmul	v0.4s, v0.4s, v23.4s
	ldr	s11, [x11, x0, lsl 2]
	ins	v26.s[2], v25.s[0]
	ldr	s25, [x1, x0, lsl 2]
	ldr	x1, [sp, 1056]
	fmla	v0.4s, v27.4s, v24.4s
	ins	v9.s[1], v10.s[0]
	ldr	s10, [x7, x0, lsl 2]
	ins	v26.s[3], v11.s[0]
	ldr	s27, [x1, x0, lsl 2]
	ldr	x1, [sp, 1040]
	ins	v9.s[2], v28.s[0]
	ldr	s11, [x6, x0, lsl 2]
	ins	v25.s[1], v10.s[0]
	ldr	s28, [x5, x0, lsl 2]
	fmla	v0.4s, v26.4s, v22.4s
	ldr	s10, [x1, x0, lsl 2]
	ldr	x1, [sp, 1024]
	ins	v9.s[3], v29.s[0]
	ins	v27.s[1], v10.s[0]
	ins	v25.s[2], v11.s[0]
	ldr	s29, [x1, x0, lsl 2]
	ldr	x1, [sp, 992]
	fmla	v0.4s, v9.4s, v21.4s
	ins	v25.s[3], v28.s[0]
	ins	v27.s[2], v29.s[0]
	ldr	s26, [x1, x0, lsl 2]
	ldr	x1, [sp, 976]
	fmla	v0.4s, v25.4s, v20.4s
	ldr	s25, [x4, x0, lsl 2]
	ldr	s10, [x1, x0, lsl 2]
	ldr	x1, [sp, 1008]
	ins	v26.s[1], v10.s[0]
	ldr	s11, [x1, x0, lsl 2]
	ldr	x1, [sp, 960]
	ins	v27.s[3], v11.s[0]
	ldr	s28, [x1, x0, lsl 2]
	ldr	x1, [sp, 928]
	ins	v26.s[2], v28.s[0]
	fmla	v0.4s, v27.4s, v19.4s
	ldr	s9, [x1, x0, lsl 2]
	ldr	x1, [sp, 912]
	ldr	s10, [x1, x0, lsl 2]
	ldr	x1, [sp, 944]
	ins	v9.s[1], v10.s[0]
	ldr	s30, [x1, x0, lsl 2]
	ldr	x1, [sp, 896]
	ins	v26.s[3], v30.s[0]
	ldr	s11, [x1, x0, lsl 2]
	ldr	x1, [sp, 880]
	ins	v9.s[2], v11.s[0]
	fmla	v0.4s, v26.4s, v18.4s
	ldr	s29, [x1, x0, lsl 2]
	ldr	x1, [sp, 864]
	ins	v9.s[3], v29.s[0]
	ldr	s28, [x1, x0, lsl 2]
	ldr	x1, [sp, 848]
	fmla	v0.4s, v9.4s, v17.4s
	ldr	s10, [x1, x0, lsl 2]
	ldr	x1, [sp, 832]
	ins	v28.s[1], v10.s[0]
	ldr	s11, [x1, x0, lsl 2]
	ldr	x1, [sp, 800]
	ins	v28.s[2], v11.s[0]
	ldr	s27, [x1, x0, lsl 2]
	ldr	x1, [sp, 784]
	ldr	s10, [x1, x0, lsl 2]
	ldr	x1, [sp, 816]
	ins	v27.s[1], v10.s[0]
	ldr	s29, [x1, x0, lsl 2]
	ldr	x1, [sp, 768]
	ins	v28.s[3], v29.s[0]
	ldr	s11, [x1, x0, lsl 2]
	ldr	x1, [sp, 736]
	ins	v27.s[2], v11.s[0]
	fmla	v0.4s, v28.4s, v16.4s
	ldr	s26, [x1, x0, lsl 2]
	ldr	x1, [sp, 720]
	ldr	s10, [x1, x0, lsl 2]
	ldr	x1, [sp, 752]
	ins	v26.s[1], v10.s[0]
	ldr	s29, [x1, x0, lsl 2]
	ldr	x1, [sp, 704]
	ins	v27.s[3], v29.s[0]
	ldr	s11, [x1, x0, lsl 2]
	ldr	x1, [sp, 672]
	ins	v26.s[2], v11.s[0]
	fmla	v0.4s, v27.4s, v7.4s
	ldr	s9, [x1, x0, lsl 2]
	ldr	x1, [sp, 656]
	ldr	s10, [x1, x0, lsl 2]
	ldr	x1, [sp, 688]
	ins	v9.s[1], v10.s[0]
	ldr	s29, [x1, x0, lsl 2]
	ldr	x1, [sp, 640]
	ins	v26.s[3], v29.s[0]
	ldr	s11, [x1, x0, lsl 2]
	ldr	x1, [sp, 608]
	ins	v9.s[2], v11.s[0]
	fmla	v0.4s, v26.4s, v6.4s
	ldr	s28, [x1, x0, lsl 2]
	ldr	x1, [sp, 592]
	ldr	s10, [x1, x0, lsl 2]
	ldr	x1, [sp, 624]
	ins	v28.s[1], v10.s[0]
	ldr	s10, [x20, x0, lsl 2]
	ldr	s29, [x1, x0, lsl 2]
	ldr	x1, [sp, 576]
	ins	v9.s[3], v29.s[0]
	ldr	s11, [x1, x0, lsl 2]
	ldr	x1, [sp, 544]
	ins	v28.s[2], v11.s[0]
	ldr	s11, [x28, x0, lsl 2]
	fmla	v0.4s, v9.4s, v5.4s
	ldr	s27, [x1, x0, lsl 2]
	ldr	x1, [sp, 560]
	ins	v27.s[1], v10.s[0]
	ldr	s10, [x25, x0, lsl 2]
	ldr	s29, [x1, x0, lsl 2]
	ldr	x1, [sp, 504]
	ins	v28.s[3], v29.s[0]
	ins	v27.s[2], v11.s[0]
	ldr	s26, [x1, x0, lsl 2]
	ldr	s29, [x26, x0, lsl 2]
	ldr	x1, [sp, 464]
	ins	v26.s[1], v10.s[0]
	ldr	s11, [x24, x0, lsl 2]
	fmla	v0.4s, v28.4s, v4.4s
	ldr	s10, [x19, x0, lsl 2]
	ins	v27.s[3], v29.s[0]
	ldr	s9, [x1, x0, lsl 2]
	ldr	s28, [x23, x0, lsl 2]
	ins	v26.s[2], v11.s[0]
	ldr	s11, [x3, x0, lsl 2]
	ins	v9.s[1], v10.s[0]
	ldr	s10, [x2, x0, lsl 2]
	fmla	v0.4s, v27.4s, v3.4s
	ldr	x1, [sp, 184]
	ins	v26.s[3], v28.s[0]
	ins	v9.s[2], v11.s[0]
	fmla	v0.4s, v26.4s, v2.4s
	ins	v9.s[3], v10.s[0]
	fmla	v0.4s, v9.4s, v1.4s
	faddp	v0.4s, v0.4s, v0.4s
	faddp	v0.4s, v0.4s, v0.4s
	fadd	s25, s25, s0
	str	s25, [x4, x0, lsl 2]
	add	x0, x0, 1
	cmp	x1, x0
	bgt	.L317
	ldr	x0, [sp, 416]
	add	x1, x22, 256
	ldr	x22, [sp, 1304]
	add	x4, x4, x27
	cmp	x0, x1
	bne	.L316
.L315:
	ldr	x1, [sp, 296]
	mov	x0, x22
	add	x19, x1, 64
	str	x19, [sp, 296]
	bl	free
	mov	x0, x21
	bl	free
	ldr	x1, [sp, 152]
	ldr	x0, [sp, 224]
	add	x0, x0, x1
	str	x0, [sp, 224]
	ldr	x0, [sp, 216]
	add	x0, x0, 256
	str	x0, [sp, 216]
	ldr	x0, [sp, 168]
	cmp	x19, x0
	bne	.L318
	ldr	w0, [sp, 204]
	add	x7, sp, 1248
	ldr	x19, [sp, 1280]
	ldp	x23, x25, [x7]
	ldp	x24, x26, [x7, 16]
	ldr	x28, [sp, 1296]
	ldr	w20, [sp, 1292]
	cbnz	w0, .L520
	subs	w20, w20, #1
	bne	.L337
	ldr	x24, [sp, 184]
	mov	x22, x27
	ldp	x23, x21, [sp, 272]
	ldr	x25, [sp, 384]
	b	.L338
.L516:
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 27
	.cfi_restore 28
	.cfi_restore 72
	.cfi_restore 73
	.cfi_restore 74
	.cfi_restore 75
	adrp	x0, .LC9
	add	x0, x0, :lo12:.LC9
.LEHB12:
	bl	puts
.LEHE12:
	ldp	x23, x24, [sp, 48]
	.cfi_restore 24
	.cfi_restore 23
	b	.L288
.L290:
	.cfi_offset 19, -1696
	.cfi_offset 20, -1688
	.cfi_offset 21, -1680
	.cfi_offset 22, -1672
	.cfi_offset 23, -1664
	.cfi_offset 24, -1656
	.cfi_offset 25, -1648
	.cfi_offset 26, -1640
	.cfi_offset 27, -1632
	.cfi_offset 28, -1624
	.cfi_offset 72, -1616
	.cfi_offset 73, -1608
	.cfi_offset 74, -1600
	.cfi_offset 75, -1592
	cmp	x19, x21
	beq	.L521
	mov	x25, 0
	b	.L293
.L521:
	adrp	x0, .LC10
	add	x0, x0, :lo12:.LC10
.LEHB13:
	bl	puts
	adrp	x0, .LC11
	mov	w2, w23
	add	x0, x0, :lo12:.LC11
	mov	w1, w23
	bl	printf
.LEHE13:
	mov	x25, 0
	b	.L296
.L299:
	ldr	w0, [sp, 204]
	cbnz	w0, .L522
.L335:
	subs	w20, w20, #1
	bne	.L339
	ldp	x23, x21, [sp, 272]
	mov	x25, x27
	ldr	x24, [sp, 184]
.L338:
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	ldr	x1, [sp, 408]
	sub	x1, x0, x1
	adrp	x0, .LC15
	scvtf	d9, x1
	ldr	d0, [x0, #:lo12:.LC15]
	adrp	x0, .LC12
	add	x0, x0, :lo12:.LC12
	str	x0, [sp, 280]
	fmul	d9, d9, d0
.LEHB14:
	bl	puts
	adrp	x0, .LC16
	scvtf	d8, d8
	fmov	d0, d9
	ldr	d2, [x0, #:lo12:.LC16]
	adrp	x0, .LC17
	ldr	d1, [x0, #:lo12:.LC17]
	mov	x0, 4636737291354636288
	fmul	d11, d8, d2
	fmov	d3, x0
	adrp	x0, .LC13
	add	x0, x0, :lo12:.LC13
	fmul	d10, d8, d1
	fdiv	d2, d11, d9
	fdiv	d1, d10, d9
	fmul	d2, d2, d3
	bl	printf
	asr	x19, x24, 2
	str	x19, [sp, 184]
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	mov	x20, x0
	ldr	x3, [sp, 176]
	stp	x25, x20, [sp, 288]
	mul	x2, x19, x24
	ldr	x4, [sp, 136]
	mul	x1, x24, x3
	ldr	x5, [sp, 304]
	mov	x0, x1
	and	w27, w23, 3
	add	x1, x26, x1, lsl 8
	add	x0, x21, x0, lsl 8
	add	x4, x4, x5
	stp	x0, x4, [sp, 264]
	mov	x25, x22
	ldp	x20, x0, [sp, 152]
	str	x28, [sp, 152]
	mov	x28, x24
	str	x1, [sp, 248]
	lsl	x1, x2, 4
	str	x1, [sp, 256]
	and	x0, x0, 3
	str	x0, [sp, 216]
	ubfx	x0, x24, 2, 4
	str	x0, [sp, 208]
	lsl	w0, w3, 4
	str	w0, [sp, 240]
	add	x0, x22, x26
	str	x0, [sp, 224]
	mov	w0, 10
	str	w0, [sp, 232]
.L392:
	mov	x0, 16384
	bl	malloc
	mov	x23, x0
	mov	x0, 16384
	bl	malloc
	mov	x19, x0
	ldr	x0, [sp, 176]
	cbz	x0, .L523
	ldr	x0, [sp, 136]
	add	x2, x26, 4
	add	x15, x23, 16384
	mov	x1, x25
	add	x5, x0, 4
	mov	x0, 0
	mov	x4, x26
	mov	x3, x28
	mov	x26, x21
	mov	x28, x23
	mov	w21, w27
	mov	x25, x0
	add	x12, x19, 256
	add	x16, x19, 16384
	mov	x22, x20
	mov	x23, x2
	mov	x0, x19
	mov	x27, x5
	mov	x11, 1
.L358:
	mov	x2, x27
	mov	w24, 0
	mov	x19, x26
	mov	x6, x25
	mov	x27, x0
	mov	w25, w24
	mov	x20, x23
	mov	x24, x26
	mov	x5, x23
	mov	w7, w21
	mov	x26, x22
	mov	x0, x2
.L360:
	mov	x9, x20
	mov	x8, x28
	b	.L357
.L345:
	ldr	q0, [x9, -4]
	add	x8, x8, 256
	str	q0, [x8, -256]
	ldr	q0, [x9, 12]
	str	q0, [x8, -240]
	ldr	q0, [x9, 28]
	str	q0, [x8, -224]
	ldr	q0, [x9, 44]
	str	q0, [x8, -208]
	ldr	q0, [x9, 60]
	str	q0, [x8, -192]
	ldr	q0, [x9, 76]
	str	q0, [x8, -176]
	ldr	q0, [x9, 92]
	str	q0, [x8, -160]
	ldr	q0, [x9, 108]
	str	q0, [x8, -144]
	ldr	q0, [x9, 124]
	str	q0, [x8, -128]
	ldr	q0, [x9, 140]
	str	q0, [x8, -112]
	ldr	q0, [x9, 156]
	str	q0, [x8, -96]
	ldr	q0, [x9, 172]
	str	q0, [x8, -80]
	ldr	q0, [x9, 188]
	str	q0, [x8, -64]
	ldr	q0, [x9, 204]
	str	q0, [x8, -48]
	ldr	q0, [x9, 220]
	str	q0, [x8, -32]
	ldr	q0, [x9, 236]
	add	x9, x9, x1
	str	q0, [x8, -16]
	cmp	x15, x8
	beq	.L415
.L357:
	sub	x2, x8, x9
	cmp	x2, 8
	bhi	.L345
	sub	x10, x9, #4
	mov	x2, 0
.L342:
	ldr	s0, [x10, x2]
	str	s0, [x8, x2]
	add	x2, x2, 4
	cmp	x2, 256
	bne	.L342
	add	x8, x8, 256
	add	x9, x9, x1
	cmp	x15, x8
	bne	.L357
.L415:
	mov	x2, x26
	mov	w9, w25
	mov	x21, 0
	mov	x25, x1
	mov	x23, x0
	mov	x1, x24
	mov	x8, x19
	mov	x24, x19
	mov	x22, x21
	mov	x26, x12
.L344:
	mov	x12, x23
	mov	x10, x27
	b	.L355
.L350:
	ldr	q0, [x12, -4]
	add	x10, x10, 256
	str	q0, [x10, -256]
	ldr	q0, [x12, 12]
	str	q0, [x10, -240]
	ldr	q0, [x12, 28]
	str	q0, [x10, -224]
	ldr	q0, [x12, 44]
	str	q0, [x10, -208]
	ldr	q0, [x12, 60]
	str	q0, [x10, -192]
	ldr	q0, [x12, 76]
	str	q0, [x10, -176]
	ldr	q0, [x12, 92]
	str	q0, [x10, -160]
	ldr	q0, [x12, 108]
	str	q0, [x10, -144]
	ldr	q0, [x12, 124]
	str	q0, [x10, -128]
	ldr	q0, [x12, 140]
	str	q0, [x10, -112]
	ldr	q0, [x12, 156]
	str	q0, [x10, -96]
	ldr	q0, [x12, 172]
	str	q0, [x10, -80]
	ldr	q0, [x12, 188]
	str	q0, [x10, -64]
	ldr	q0, [x12, 204]
	str	q0, [x10, -48]
	ldr	q0, [x12, 220]
	str	q0, [x10, -32]
	ldr	q0, [x12, 236]
	add	x12, x12, x25
	str	q0, [x10, -16]
	cmp	x16, x10
	beq	.L416
.L355:
	sub	x13, x10, x12
	cmp	x13, 8
	bhi	.L350
	sub	x14, x12, #4
	mov	x13, 0
	.p2align 3,,7
.L347:
	ldr	s0, [x14, x13]
	str	s0, [x10, x13]
	add	x13, x13, 4
	cmp	x13, 256
	bne	.L347
	add	x10, x10, 256
	add	x12, x12, x25
	cmp	x16, x10
	bne	.L355
.L416:
	mov	x19, x28
	mov	x10, x23
	mov	x23, x3
	mov	x3, x25
	mov	x25, x1
	mov	x1, x28
	mov	x28, x2
	mov	x2, x15
	mov	x14, x22
	mov	x15, x24
	mov	x22, x24
	mov	x24, x2
	str	x20, [sp, 304]
	mov	x20, x19
.L349:
	mov	x21, x22
	mov	x19, x27
	stp	x22, x24, [sp, 328]
	mov	x22, x1
	mov	x24, x6
	stp	x5, x0, [sp, 312]
	str	x16, [sp, 344]
.L352:
	adrp	x0, .LC2
	str	x20, [sp, 1408]
	str	x19, [sp, 1440]
	add	x2, sp, 1312
	ldr	q0, [x0, #:lo12:.LC2]
	add	x0, sp, 1536
	str	x8, [sp, 352]
	add	x1, sp, 1344
	str	w7, [sp, 368]
	add	x19, x19, 64
	str	q0, [x0, -120]
	ldp	x16, x17, [x0, -128]
	add	x0, sp, 1696
	str	w9, [sp, 376]
	stp	x3, x10, [sp, 384]
	str	q0, [x0, -248]
	add	x0, sp, 1536
	stp	x14, x15, [sp, 400]
	str	x4, [sp, 416]
	str	x21, [sp, 1544]
	add	x21, x21, 64
	str	x23, [sp, 1552]
	str	x11, [sp, 1560]
	stp	x16, x17, [x0, -160]
	ldp	x16, x17, [x0, -96]
	stp	x16, x17, [x0, -192]
	add	x0, sp, 1696
	ldp	x16, x17, [x0, -152]
	add	x0, sp, 1536
	stp	x16, x17, [x0, -224]
	add	x0, sp, 1376
	ldr	x16, [sp, 1424]
	str	x16, [sp, 1392]
	ldr	x16, [sp, 1456]
	str	x11, [sp, 1328]
	str	x16, [sp, 1360]
	bl	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.0
	ldr	x8, [sp, 352]
	cmp	x26, x19
	ldp	x3, x10, [sp, 384]
	mov	x11, 1
	ldp	x14, x15, [sp, 400]
	ldr	x4, [sp, 416]
	ldr	w7, [sp, 368]
	ldr	w9, [sp, 376]
	bne	.L352
	mov	x1, x22
	mov	x6, x24
	ldp	x22, x24, [sp, 328]
	add	x20, x20, 1024
	ldr	x2, [sp, 144]
	ldp	x5, x0, [sp, 312]
	ldr	x16, [sp, 344]
	add	x22, x22, x2
	cmp	x24, x20
	bne	.L349
	mov	x2, x28
	mov	x28, x1
	mov	x1, x25
	mov	x25, x3
	mov	x3, x23
	mov	x23, x10
	mov	x10, x24
	mov	x24, x15
	mov	x15, x10
	add	x22, x14, 64
	ldr	x10, [sp, 168]
	add	x24, x24, 256
	ldr	x20, [sp, 304]
	add	x23, x23, 256
	cmp	x10, x22
	bne	.L344
	mov	x12, x26
	add	x19, x8, x2
	mov	x26, x2
	add	x20, x20, x2
	ldr	w2, [sp, 240]
	mov	x24, x1
	mov	x1, x25
	add	w25, w9, 16
	cmp	w2, w25
	bne	.L360
	mov	x2, x0
	mov	x22, x26
	mov	x0, x27
	add	x27, x2, x22
	ldr	x2, [sp, 168]
	add	x25, x6, 64
	mov	x26, x24
	mov	w21, w7
	add	x23, x5, 256
	cmp	x2, x25
	bne	.L358
	ldr	x2, [sp, 136]
	mov	x23, x28
	ldr	x6, [sp, 248]
	mov	w27, w7
	mov	x25, x1
	mov	x26, x4
	mov	x28, x3
	mov	x19, x2
	stp	x23, x0, [sp, 304]
	mov	x23, x6
	mov	x20, x22
	mov	x21, x24
	mov	x22, 1
	mov	x24, 0
.L359:
	ldr	x0, [sp, 216]
	cbz	x0, .L369
	add	x11, x26, x24, lsl 2
	mov	x1, 0
	mov	x5, x1
	mov	w0, w27
	mov	x3, x24
	mov	x2, x25
	mov	x1, x19
	mov	x4, x26
	add	x9, sp, 1592
	mov	x27, x21
	mov	x24, x20
	mov	x26, x11
	mov	x19, x5
	mov	x25, x21
.L363:
	ldr	x21, [sp, 168]
	mov	x5, x26
	mov	x8, x27
	mov	x10, x24
	mov	x11, x23
	mov	x26, x1
	mov	x20, 0
	mov	x27, x25
	mov	x12, x19
	mov	x24, x20
	mov	x1, x5
	mov	x23, x21
.L366:
	lsl	x5, x23, 2
	mov	x21, x1
	add	x25, x26, x5
	add	x19, x27, x5
	stp	x26, x27, [sp, 320]
	mov	w26, w0
	mov	x27, x2
	stp	x1, x23, [sp, 336]
	mov	x23, x8
	mov	w20, 16
	str	x24, [sp, 352]
	mov	x24, x10
.L361:
	ldr	x0, [sp, 144]
	add	x5, sp, 1568
	add	x6, sp, 1608
	stp	x11, x3, [sp, 368]
	add	x2, sp, 1312
	stp	x21, x28, [x5]
	add	x21, x21, x0
	add	x1, sp, 1344
	stp	x22, x19, [x6]
	add	x19, x19, x0
	add	x0, sp, 1536
	stp	x28, x22, [x6, 16]
	ldp	x6, x7, [x0, 32]
	stp	x25, x28, [x5, 24]
	stp	x12, x4, [sp, 384]
	str	x22, [sp, 1584]
	stp	x6, x7, [x0, -160]
	ldp	x6, x7, [x9]
	stp	x6, x7, [x0, -192]
	ldp	x6, x7, [x0, 80]
	stp	x6, x7, [x0, -224]
	add	x0, sp, 1376
	str	x22, [sp, 1328]
	str	x22, [sp, 1360]
	str	x22, [sp, 1392]
	bl	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.0
	ldp	x11, x3, [sp, 368]
	subs	w20, w20, #1
	ldp	x12, x4, [sp, 384]
	add	x9, sp, 1592
	bne	.L361
	mov	x8, x23
	mov	x10, x24
	ldp	x1, x23, [sp, 336]
	mov	w0, w26
	ldr	x24, [sp, 352]
	mov	x2, x27
	ldr	x5, [sp, 216]
	add	x24, x24, 1
	ldp	x26, x27, [sp, 320]
	add	x23, x23, 16
	cmp	x5, x24
	bne	.L366
	mov	x5, x1
	mov	x1, x26
	add	x26, x5, x10
	mov	x25, x27
	ldr	x5, [sp, 176]
	add	x19, x12, 1
	mov	x24, x10
	mov	x23, x11
	mov	x27, x8
	add	x25, x25, x10
	cmp	x5, x19
	bgt	.L363
	mov	x21, x8
	mov	x20, x10
	mov	w27, w0
	mov	x25, x2
	mov	x19, x1
	mov	x24, x3
	mov	x26, x4
.L369:
	ldr	x0, [sp, 208]
	cbz	x0, .L365
	ldr	x2, [sp, 264]
	mov	x1, 0
	mov	x7, x24
	mov	x8, x26
	mov	x24, x1
	mov	x26, x23
	mov	w1, w27
	add	x11, sp, 1640
	add	x10, sp, 1688
	mov	x0, x20
	mov	x6, x19
	mov	x27, x21
	mov	x23, x19
	str	x25, [sp, 320]
	mov	x25, x2
.L364:
	mov	x21, x25
	mov	x20, x26
	stp	x26, x25, [sp, 328]
	mov	x25, x24
	mov	w26, w1
	mov	x24, x0
	mov	x19, 0
.L367:
	ldr	x0, [sp, 144]
	add	x3, sp, 1640
	add	x4, sp, 1680
	stp	x6, x7, [sp, 344]
	add	x2, sp, 1312
	stp	x20, x28, [x3]
	add	x20, x20, x0
	add	x1, sp, 1344
	stp	x22, x21, [x4]
	add	x21, x21, x0
	add	x0, sp, 1536
	stp	x23, x28, [x3, 24]
	add	x19, x19, 1
	stp	x28, x22, [x4, 16]
	ldp	x4, x5, [x11]
	str	x8, [sp, 368]
	str	x22, [sp, 1656]
	stp	x4, x5, [x0, -160]
	ldp	x4, x5, [x0, 128]
	stp	x4, x5, [x0, -192]
	ldp	x4, x5, [x10]
	stp	x4, x5, [x0, -224]
	add	x0, sp, 1376
	str	x22, [sp, 1328]
	str	x22, [sp, 1360]
	str	x22, [sp, 1392]
	bl	_Z18neon_microkernel_gP18c_code_str_Contextl12exo_win_2f32S1_S1_.constprop.0
	ldr	x0, [sp, 208]
	add	x10, sp, 1688
	ldp	x6, x7, [sp, 344]
	add	x11, sp, 1640
	ldr	x8, [sp, 368]
	cmp	x19, x0
	bne	.L367
	mov	x0, x24
	mov	w1, w26
	add	x24, x25, 1
	add	x23, x23, 64
	ldp	x26, x25, [sp, 328]
	ldr	x2, [sp, 160]
	add	x25, x25, 64
	cmp	x2, x24
	bgt	.L364
	ldr	x25, [sp, 320]
	mov	x21, x27
	mov	x23, x26
	mov	x20, x0
	mov	w27, w1
	mov	x19, x6
	mov	x24, x7
	mov	x26, x8
.L365:
	ldr	x0, [sp, 168]
	add	x24, x24, 64
	add	x19, x19, x20
	add	x23, x23, 256
	cmp	x0, x24
	bne	.L359
	ldr	w0, [sp, 204]
	ldp	x23, x19, [sp, 304]
	cbz	w0, .L381
.L525:
	ldr	w0, [sp, 184]
	mov	w5, 4
	mov	w2, 0
.L379:
	ldr	w1, [sp, 160]
	lsl	w10, w2, 2
	mov	w6, 0
	mov	w3, 0
.L382:
	ldr	x4, [sp, 360]
	sxtw	x11, w6
	mov	w8, w10
	add	x16, x11, 16
	add	x9, x11, x4
	ldr	x4, [sp, 136]
	add	x9, x4, x9, lsl 2
.L378:
	ldr	w4, [sp, 1288]
	mov	x7, x11
	ldr	x12, [sp, 168]
	mov	x14, x9
	smull	x4, w8, w4
	add	x13, x4, x12
	ldr	x12, [sp, 432]
	add	x13, x26, x13, lsl 2
	add	x12, x12, x4
	add	x4, x21, x4, lsl 2
	add	x12, x26, x12, lsl 2
.L373:
	ldr	s0, [x4, x7, lsl 2]
	mov	x17, x14
	mov	x15, x13
.L372:
	ldr	s1, [x17]
	add	x17, x17, x25
	ldr	s2, [x15], 4
	fmadd	s0, s2, s1, s0
	str	s0, [x4, x7, lsl 2]
	cmp	x15, x12
	bne	.L372
	add	x7, x7, 1
	add	x14, x14, 4
	cmp	x7, x16
	bne	.L373
	add	w8, w8, 1
	cmp	w5, w8
	bne	.L378
	add	w3, w3, 1
	add	w6, w6, 16
	cmp	w3, w1
	bne	.L382
	add	w2, w2, 1
	add	w5, w5, 4
	cmp	w2, w0
	bne	.L379
	ldr	w0, [sp, 200]
	cbnz	w0, .L524
.L371:
	cbz	w27, .L388
	ldr	x0, [sp, 256]
	mov	w4, 0
.L387:
	ldr	x1, [sp, 224]
	add	x6, x21, x0
	ldr	x2, [sp, 136]
	add	x7, x26, x0
	add	x8, x0, x1
	mov	x1, 0
.L391:
	ldr	s0, [x6, x1, lsl 2]
	mov	x5, x7
	mov	x3, x2
.L389:
	ldr	s1, [x3]
	add	x3, x3, x25
	ldr	s2, [x5], 4
	fmadd	s0, s2, s1, s0
	str	s0, [x6, x1, lsl 2]
	cmp	x5, x8
	bne	.L389
	add	x1, x1, 1
	add	x2, x2, 4
	cmp	x28, x1
	bne	.L391
	add	w4, w4, 1
	add	x0, x0, x25
	cmp	w4, w27
	bne	.L387
.L388:
	mov	x0, x23
	bl	free
	mov	x0, x19
	bl	free
	ldr	w0, [sp, 232]
	subs	w0, w0, #1
	str	w0, [sp, 232]
	bne	.L392
	ldp	x25, x20, [sp, 288]
	ldr	x28, [sp, 152]
	bl	_ZNSt6chrono3_V212steady_clock3nowEv
	ldr	x19, [sp, 280]
	sub	x1, x0, x20
	adrp	x0, .LC15
	scvtf	d8, x1
	ldr	d0, [x0, #:lo12:.LC15]
	mov	x0, x19
	fmul	d8, d8, d0
	bl	puts
	fdiv	d2, d11, d8
	mov	x0, 4636737291354636288
	fdiv	d1, d10, d8
	fmov	d3, x0
	fmov	d0, d8
	adrp	x0, .LC14
	add	x0, x0, :lo12:.LC14
	fmul	d2, d2, d3
	bl	printf
	mov	x0, x19
	bl	puts
.LEHE14:
	cbz	x25, .L393
	mov	x1, x28
	mov	x0, x25
	bl	_ZdlPvm
.L393:
	cbz	x21, .L394
	ldr	x1, [sp, 1536]
	mov	x0, x21
	sub	x1, x1, x21
	bl	_ZdlPvm
.L394:
	ldr	x0, [sp, 136]
	cbz	x0, .L395
	ldr	x1, [sp, 1512]
	sub	x1, x1, x0
	bl	_ZdlPvm
.L395:
	cbz	x26, .L396
	ldr	x1, [sp, 1488]
	mov	x0, x26
	sub	x1, x1, x26
	bl	_ZdlPvm
.L396:
	ldp	x19, x20, [sp, 16]
	.cfi_remember_state
	.cfi_restore 20
	.cfi_restore 19
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	.cfi_restore 22
	.cfi_restore 21
	ldp	x23, x24, [sp, 48]
	.cfi_restore 24
	.cfi_restore 23
	ldp	x25, x26, [sp, 64]
	.cfi_restore 26
	.cfi_restore 25
	ldp	x27, x28, [sp, 80]
	.cfi_restore 28
	.cfi_restore 27
	ldp	d8, d9, [sp, 96]
	.cfi_restore 73
	.cfi_restore 72
	ldp	d10, d11, [sp, 112]
	.cfi_restore 75
	.cfi_restore 74
	b	.L286
.L518:
	.cfi_restore_state
	adrp	x0, .LC10
	add	x0, x0, :lo12:.LC10
.LEHB15:
	bl	puts
	adrp	x0, .LC11
	mov	w2, w23
	add	x0, x0, :lo12:.LC11
	mov	w1, w23
	bl	printf
.LEHE15:
	b	.L296
.L522:
	ldr	x0, [sp, 288]
	ldr	x8, [sp, 136]
	add	x3, x26, x0
.L409:
	ldr	x10, [sp, 184]
	mov	x5, 0
	ldr	x1, [sp, 312]
	ldr	x6, [sp, 360]
.L332:
	mov	x7, x8
	add	x11, x3, x6, lsl 2
	mov	x0, 0
.L336:
	ldr	s0, [x1, x0, lsl 2]
	mov	x9, x7
	mov	x4, 0
.L333:
	ldr	s2, [x11, x4, lsl 2]
	add	x4, x4, 1
	ldr	s1, [x9]
	add	x9, x9, x22
	fmadd	s0, s2, s1, s0
	str	s0, [x1, x0, lsl 2]
	cmp	x4, x19
	blt	.L333
	add	x0, x0, 1
	add	x7, x7, 4
	cmp	x10, x0
	bne	.L336
	add	x5, x5, 1
	add	x6, x6, x10
	add	x1, x1, x22
	cmp	x5, x19
	blt	.L332
	b	.L335
.L523:
	ldr	x0, [sp, 184]
	cbz	x0, .L371
	ldr	x0, [sp, 160]
	cbz	x0, .L381
	ldr	w0, [sp, 204]
	cbnz	w0, .L525
.L381:
	ldr	w0, [sp, 200]
	cbz	w0, .L371
.L524:
	ldr	x1, [sp, 192]
	mov	w5, 0
	ldr	w2, [sp, 184]
	mov	w4, 0
	add	x11, x1, w0, sxtw
.L380:
	ldr	w0, [sp, 1288]
	mov	w3, 4
	smull	x0, w5, w0
	lsl	x0, x0, 2
.L386:
	ldr	x1, [sp, 224]
	add	x9, x21, x0
	ldr	x6, [sp, 272]
	add	x12, x1, x0
	ldr	x1, [sp, 192]
	add	x10, x26, x0
.L383:
	ldr	s0, [x9, x1, lsl 2]
	mov	x8, x10
	mov	x7, x6
.L384:
	ldr	s1, [x7]
	add	x7, x7, x25
	ldr	s2, [x8], 4
	fmadd	s0, s2, s1, s0
	str	s0, [x9, x1, lsl 2]
	cmp	x12, x8
	bne	.L384
	add	x1, x1, 1
	add	x6, x6, 4
	cmp	x11, x1
	bne	.L383
	add	x0, x0, x25
	subs	w3, w3, #1
	bne	.L386
	add	w4, w4, 1
	add	w5, w5, 4
	cmp	w4, w2
	bne	.L380
	b	.L371
.L519:
	mov	x4, x24
	mov	x0, 256
.L308:
	sub	x5, x0, #256
	mov	x2, x4
	mov	x3, x26
.L313:
	ldr	x1, [sp, 192]
	mov	x6, x25
	add	x9, x3, 256
.L310:
	ldr	s0, [x2, x1, lsl 2]
	mov	x8, x6
	mov	x7, x3
	.p2align 3,,7
.L311:
	ldr	s2, [x7], 4
	ldr	s1, [x8]
	add	x8, x8, x27
	fmadd	s0, s2, s1, s0
	str	s0, [x2, x1, lsl 2]
	cmp	x9, x7
	bne	.L311
	ldr	x7, [sp, 376]
	add	x1, x1, 1
	add	x6, x6, 4
	cmp	x7, x1
	bne	.L310
	add	x5, x5, 64
	add	x2, x2, x27
	cmp	x0, x5
	beq	.L526
	mov	x3, x9
	b	.L313
.L526:
	ldr	x1, [sp, 144]
	add	x0, x0, 256
	add	x26, x26, 1024
	add	x4, x4, x1
	mov	x1, 4352
	cmp	x0, x1
	bne	.L308
	b	.L309
.L520:
	ldr	x0, [sp, 288]
	mov	x22, x27
	ldp	x30, x15, [sp, 320]
	add	x3, x26, x0
	ldp	x11, x5, [sp, 336]
	mov	x18, x1
	ldr	x6, [sp, 144]
	mov	x1, x3
	ldr	x14, [sp, 264]
	mov	x4, 0
	ldr	x10, [sp, 352]
	ldr	x27, [sp, 384]
	ldr	x7, [sp, 1216]
	ldr	x12, [sp, 1240]
.L331:
	mov	x13, x7
	mov	x16, x1
	mov	w0, 16
.L320:
	add	x2, x16, x12
	mov	x21, x23
	str	x2, [sp, 216]
	mov	x2, x13
	mov	x17, 0
.L322:
	ldr	x8, [sp, 232]
	mov	x9, x21
	ldr	q24, [x2, x22]
	str	x16, [sp, 224]
	ldr	q23, [x2, x8]
	str	w0, [sp, 224]
	ldr	x8, [sp, 240]
	ldr	q18, [x2, x30]
	ldr	q22, [x2, x8]
	ldr	x8, [sp, 248]
	ldr	q17, [x2, x15]
	ldr	q21, [x2, x8]
	ldr	x8, [sp, 208]
	ldr	q16, [x2, x14]
	ldr	q20, [x2, x8]
	ldr	x8, [sp, 256]
	ldr	q11, [x2, x11]
	ldr	q10, [x2, x5]
	ldr	q9, [x2, x10]
	ldp	q28, q27, [x2]
	ldp	q26, q25, [x2, 32]
	ldr	q19, [x2, x8]
	mov	x8, x16
.L321:
	ldp	q6, q2, [x9]
	ldp	q1, q0, [x9, 32]
	add	x9, x9, x22
	ldr	x0, [sp, 184]
	ld1r	{v4.4s}, [x8]
	ldr	s3, [x8, x25, lsl 2]
	ldr	s5, [x8, x0, lsl 2]
	fmul	v30.4s, v4.4s, v2.4s
	fmul	v29.4s, v4.4s, v1.4s
	fmul	v31.4s, v4.4s, v6.4s
	fmul	v4.4s, v4.4s, v0.4s
	ldr	x0, [sp, 392]
	fadd	v27.4s, v27.4s, v30.4s
	fadd	v26.4s, v26.4s, v29.4s
	fmul	v30.4s, v6.4s, v5.s[0]
	ldr	s7, [x8, x0, lsl 2]
	fmul	v29.4s, v2.4s, v5.s[0]
	add	x8, x8, 4
	fadd	v25.4s, v25.4s, v4.4s
	fmul	v4.4s, v1.4s, v5.s[0]
	fadd	v24.4s, v24.4s, v30.4s
	fmul	v5.4s, v0.4s, v5.s[0]
	fmul	v30.4s, v6.4s, v3.s[0]
	fadd	v23.4s, v23.4s, v29.4s
	fadd	v22.4s, v22.4s, v4.4s
	fmul	v29.4s, v2.4s, v3.s[0]
	fmul	v4.4s, v1.4s, v3.s[0]
	fmul	v6.4s, v6.4s, v7.s[0]
	fmul	v3.4s, v0.4s, v3.s[0]
	fmul	v2.4s, v2.4s, v7.s[0]
	fmul	v1.4s, v1.4s, v7.s[0]
	fmul	v0.4s, v0.4s, v7.s[0]
	ldr	x0, [sp, 216]
	fadd	v28.4s, v28.4s, v31.4s
	fadd	v21.4s, v21.4s, v5.4s
	fadd	v20.4s, v20.4s, v30.4s
	fadd	v19.4s, v19.4s, v29.4s
	fadd	v18.4s, v18.4s, v4.4s
	fadd	v17.4s, v17.4s, v3.4s
	fadd	v16.4s, v16.4s, v6.4s
	fadd	v11.4s, v11.4s, v2.4s
	fadd	v10.4s, v10.4s, v1.4s
	fadd	v9.4s, v9.4s, v0.4s
	cmp	x0, x8
	bne	.L321
	ldr	x8, [sp, 232]
	stp	q28, q27, [x2]
	add	x17, x17, 1
	stp	q26, q25, [x2, 32]
	add	x21, x21, 64
	ldr	w0, [sp, 224]
	str	q24, [x2, x22]
	str	q23, [x2, x8]
	ldr	x8, [sp, 240]
	str	q22, [x2, x8]
	ldr	x8, [sp, 248]
	str	q21, [x2, x8]
	ldr	x8, [sp, 208]
	str	q20, [x2, x8]
	ldr	x8, [sp, 256]
	str	q19, [x2, x8]
	str	q18, [x2, x30]
	str	q17, [x2, x15]
	str	q16, [x2, x14]
	ldr	x8, [sp, 160]
	str	q11, [x2, x11]
	str	q10, [x2, x5]
	str	q9, [x2, x10]
	add	x2, x2, 64
	cmp	x8, x17
	bgt	.L322
	add	x16, x16, x6
	add	x13, x13, x6
	subs	w0, w0, #1
	bne	.L320
	ldr	w2, [sp, 200]
	cbnz	w2, .L527
.L324:
	ldr	x0, [sp, 176]
	add	x4, x4, 1
	add	x7, x7, x18
	add	x1, x1, x18
	cmp	x4, x0
	blt	.L331
	mov	x8, x23
	b	.L409
.L527:
	add	x13, x1, x12
	mov	x8, 0
.L330:
	mov	x2, x8
	mov	w17, 4
	str	x27, [sp, 296]
	str	x18, [sp, 368]
.L325:
	add	x9, x13, x2
	add	x18, x1, x2
	stp	x9, x18, [sp, 216]
	mov	x16, x24
	add	x27, x7, x2
	ldr	x9, [sp, 192]
.L329:
	mov	x18, x16
	ldr	x21, [sp, 224]
	str	w0, [sp, 384]
	ldr	s0, [x27, x9, lsl 2]
.L326:
	ldr	s1, [x18]
	add	x18, x18, x22
	ldr	s2, [x21], 4
	ldr	x0, [sp, 216]
	fmadd	s0, s2, s1, s0
	str	s0, [x27, x9, lsl 2]
	cmp	x0, x21
	bne	.L326
	ldr	x18, [sp, 376]
	add	x9, x9, 1
	ldr	w0, [sp, 384]
	add	x16, x16, 4
	cmp	x18, x9
	bne	.L329
	add	x2, x2, x22
	subs	w17, w17, #1
	bne	.L325
	add	w0, w0, 4
	add	x8, x8, x6
	ldr	x27, [sp, 296]
	ldr	x18, [sp, 368]
	cmp	w0, 64
	bne	.L330
	b	.L324
.L517:
.LEHB16:
	bl	_ZSt28__throw_bad_array_new_lengthv
.LEHE16:
.L423:
.L515:
	mov	x1, x28
	mov	x19, x0
	mov	x0, x25
	bl	_ZdlPvm
	ldr	x1, [sp, 1536]
	sub	x1, x1, x21
.L298:
	mov	x0, x21
	bl	_ZdlPvm
.L405:
	ldr	x0, [sp, 1496]
	ldr	x1, [sp, 1512]
	sub	x1, x1, x0
	cbz	x0, .L407
	bl	_ZdlPvm
.L407:
	ldr	x0, [sp, 1472]
	ldr	x1, [sp, 1488]
	sub	x1, x1, x0
	cbz	x0, .L408
	bl	_ZdlPvm
.L408:
	mov	x0, x19
.LEHB17:
	bl	_Unwind_Resume
.LEHE17:
.L424:
	b	.L515
.L421:
	mov	x19, x0
.L403:
	ldr	x1, [sp, 1536]
	sub	x1, x1, x21
	cbnz	x21, .L298
	b	.L405
.L419:
	mov	x19, x0
	b	.L407
.L420:
	mov	x19, x0
	b	.L405
.L422:
	mov	x19, x0
	cbz	x25, .L403
.L402:
	mov	x1, x28
	mov	x0, x25
	bl	_ZdlPvm
	b	.L403
.L426:
	mov	x19, x0
	b	.L402
.L425:
	mov	x19, x0
	b	.L403
	.cfi_endproc
.LFE8132:
	.section	.gcc_except_table
.LLSDA8132:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE8132-.LLSDACSB8132
.LLSDACSB8132:
	.uleb128 .LEHB6-.LFB8132
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB7-.LFB8132
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L419-.LFB8132
	.uleb128 0
	.uleb128 .LEHB8-.LFB8132
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L420-.LFB8132
	.uleb128 0
	.uleb128 .LEHB9-.LFB8132
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L421-.LFB8132
	.uleb128 0
	.uleb128 .LEHB10-.LFB8132
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L424-.LFB8132
	.uleb128 0
	.uleb128 .LEHB11-.LFB8132
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L423-.LFB8132
	.uleb128 0
	.uleb128 .LEHB12-.LFB8132
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB13-.LFB8132
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L425-.LFB8132
	.uleb128 0
	.uleb128 .LEHB14-.LFB8132
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L422-.LFB8132
	.uleb128 0
	.uleb128 .LEHB15-.LFB8132
	.uleb128 .LEHE15-.LEHB15
	.uleb128 .L426-.LFB8132
	.uleb128 0
	.uleb128 .LEHB16-.LFB8132
	.uleb128 .LEHE16-.LEHB16
	.uleb128 .L421-.LFB8132
	.uleb128 0
	.uleb128 .LEHB17-.LFB8132
	.uleb128 .LEHE17-.LEHB17
	.uleb128 0
	.uleb128 0
.LLSDACSE8132:
	.section	.text.startup
	.size	main, .-main
	.align	2
	.p2align 4,,11
	.type	_GLOBAL__sub_I__Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_, %function
_GLOBAL__sub_I__Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_:
.LFB9013:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	str	x19, [sp, 16]
	.cfi_offset 19, -16
	adrp	x19, .LANCHOR1
	add	x19, x19, :lo12:.LANCHOR1
	add	x19, x19, 16
	mov	x0, x19
	bl	_ZNSt8ios_base4InitC1Ev
	mov	x1, x19
	adrp	x2, __dso_handle
	ldr	x19, [sp, 16]
	add	x2, x2, :lo12:__dso_handle
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 19
	.cfi_def_cfa_offset 0
	adrp	x0, _ZNSt8ios_base4InitD1Ev
	add	x0, x0, :lo12:_ZNSt8ios_base4InitD1Ev
	b	__cxa_atexit
	.cfi_endproc
.LFE9013:
	.size	_GLOBAL__sub_I__Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_, .-_GLOBAL__sub_I__Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.section	.init_array,"aw"
	.align	3
	.xword	_GLOBAL__sub_I__Z21neon_microkernel_edgeP18c_code_str_Contextl12exo_win_2f32S1_S1_
	.section	.rodata.cst16,"aM",@progbits,16
	.align	4
.LC2:
	.xword	64
	.xword	1
	.align	4
.LC3:
	.xword	-2147483648
	.xword	-2147483648
	.align	4
.LC4:
	.xword	2147483647
	.xword	2147483647
	.align	4
.LC5:
	.xword	1
	.xword	1
	.align	4
.LC6:
	.xword	2567483615
	.xword	2567483615
	.section	.rodata.cst8,"aM",@progbits,8
	.align	3
.LC15:
	.word	-1698910390
	.word	1048238066
	.align	3
.LC16:
	.word	-1598689907
	.word	1047578359
	.align	3
.LC17:
	.word	-1598689907
	.word	1051772663
	.section	.rodata
	.align	3
	.set	.LANCHOR0,. + 0
.LC0:
	.xword	_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk
	.xword	64
	.xword	1
	.bss
	.align	4
	.set	.LANCHOR1,. + 0
	.type	_ZGVZL10gen_matrixllE2rd, %object
	.size	_ZGVZL10gen_matrixllE2rd, 8
_ZGVZL10gen_matrixllE2rd:
	.zero	8
	.type	_ZGVZL10gen_matrixllE3rng, %object
	.size	_ZGVZL10gen_matrixllE3rng, 8
_ZGVZL10gen_matrixllE3rng:
	.zero	8
	.type	_ZStL8__ioinit, %object
	.size	_ZStL8__ioinit, 1
_ZStL8__ioinit:
	.zero	1
	.zero	15
	.type	_ZZL10gen_matrixllE3rng, %object
	.size	_ZZL10gen_matrixllE3rng, 5000
_ZZL10gen_matrixllE3rng:
	.zero	5000
	.type	_ZZL10gen_matrixllE2rd, %object
	.size	_ZZL10gen_matrixllE2rd, 5000
_ZZL10gen_matrixllE2rd:
	.zero	5000
	.type	_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk, %object
	.size	_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk, 16384
_ZZ4GEPPP18c_code_str_Contextll12exo_win_2f32S1_S1_E5A_blk:
	.zero	16384
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align	3
	.type	DW.ref.__gxx_personality_v0, %object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.xword	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
