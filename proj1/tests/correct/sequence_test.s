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

$LABEL0: .word 0
$LABEL1: .word 0
$LABEL2: .asciiz "1234"
	.text
	.globl main
	j  main


	main:
	pushaa
	la $v1,$LABEL0
	lw $v0,0($v1)
	push $v1
	li $v0,1
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	la $v1,$LABEL1
	lw $v0,0($v1)
	push $v1
	li $v0,2
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	pushaa
	pushaa
	la $v1,$LABEL0
	lw $v0,0($v1)
	push $v0
	la $v1,$LABEL1
	lw $v0,0($v1)
	move $a1,$v0
	pop $a0
	add $v0,$a0,$a1
	popaa
	pushaa
	la $v1,$LABEL0
	lw $v0,0($v1)
	push $v0
	la $v1,$LABEL1
	lw $v0,0($v1)
	move $a1,$v0
	pop $a0
	sub $v0,$a0,$a1
	popaa
	la $v0,$LABEL2
	popaa
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	li $v0 10
	syscall
