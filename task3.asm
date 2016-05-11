;------------------------(1)
	ldc 10001
	st 0
	ldc 3
	st 1
	ldc 3
	st 6
	ldc 2
	st 3
	ldc 2
	st 4
;------------------------(2)
1:	ld 1
	st 5
	ld 3
	ldc 1
	add
	st 3
	ld 6
	ldc 2
	add
	st 6
1a:	ld 6
	st 2
;-----------------------(3)
2:	ld 5
	ld 2
	sub
	st 2
	ld 2
	br 2a
	jmp 1
2a:	ldc 0
	ld 2
	cmp
	ldc 1
	add
	br 2
;-----------------------(4)
	ld 5
	ldc 1
	add
	st 5
;-----------------------(5)
	ld 5
	ld 3
	cmp
	ldc 1
	add
	br 1a
;-----------------------(6)
	ld 4
	ldc 1
	add
	st 4
;-----------------------(7)
	ld 4
	ld 0
	cmp
	br 1
;-----------------------(8)
	ld 6
	ret
;результат: 104743
