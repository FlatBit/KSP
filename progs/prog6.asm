	rdint
	popg	0
	rdint
	popg	1
	pushg	0
	pushg	1
	ne
	brf	L2
	pushg	0
	pushg	1
	gt
	brf	L3
	pushg	0
	pushg	1
	sub
	popg	0
	jmp	L4
	pushg	1
	pushg	0
	sub
	popg	1
	jmp	L1
	pushg	0
	wrint
	pushc	'\n'
	wrchr
	halt
