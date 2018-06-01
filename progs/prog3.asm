//
// prog3.asm -- an assembler example with division with zero
//


// local Integer x;
// local Integer y;
// x = 2;
// y = x + 3;
// x = 7 * y + x;
// writeInteger(x + -33);
// writeCharacter('\n');
    
    asf	2
	pushc	2
	popl	0
	pushl	0
	pushc	-2
	add
	popl	1
	pushc	7
	pushl	1
	div
	pushl	0
	add
	popl	0
	pushl	0
	pushc	-33
	add
	wrint
	pushc	'\n'
	wrchr
	rsf
	halt
