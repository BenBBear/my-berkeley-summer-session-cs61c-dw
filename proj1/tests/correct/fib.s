.macro push (%arg)
add $sp,$sp,-4
sw %arg,0($sp)
.end_macro

.macro pop (%arg)
lw %arg,0($sp)
add $sp,$sp,4
.end_macro

.macro pushaa ()
push $a0
push $a1
.end_macro
.macro popaa ()
pop $a1
pop $a0
.end_macro
.data

	.text
	.globl main
	j  main


	main:
	move $v0,$zero
	pushaa
	li $v0,5
	push $v0
	jal fib
	pop $zero
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	li $v0 10
	syscall
fib:
	push $ra
	pushaa
	add $v1,$sp,12
	lw $v0,0($v1)
	beq $v0,$zero,$LABEL0
	pushaa
	add $v1,$sp,20
	lw $v0,0($v1)
	push $v0
	li $v0,1
	move $a1,$v0
	pop $a0
	sub $v0,$a0,$a1
	popaa
	beq $v0,$zero,$LABEL0
	li $v0,1
	j $LABEL1
$LABEL0:
	move $v0,$zero
$LABEL1:
	popaa
	beq $v0,$zero,$LABEL2
	pushaa
	pushaa
	add $v1,$sp,20
	lw $v0,0($v1)
	push $v0
	li $v0,1
	move $a1,$v0
	pop $a0
	sub $v0,$a0,$a1
	popaa
	push $v0
	jal fib
	pop $zero
	push $v0
	pushaa
	add $v1,$sp,24
	lw $v0,0($v1)
	push $v0
	li $v0,2
	move $a1,$v0
	pop $a0
	sub $v0,$a0,$a1
	popaa
	push $v0
	jal fib
	pop $zero
	move $a1,$v0
	pop $a0
	add $v0,$a0,$a1
	popaa
	j $LABEL3
$LABEL2:
	add $v1,$sp,4
	lw $v0,0($v1)
$LABEL3:
	pop $ra
	jr $ra
