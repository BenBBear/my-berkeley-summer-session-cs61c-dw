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
	.text
	.globl main
	j  main


	main:
	pushaa
	la $v1,$LABEL1
	lw $v0,0($v1)
	push $v1
	li $v0,0
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	li $v0,0
$LABEL2:
	pushaa
	la $v1,$LABEL1
	lw $v0,0($v1)
	push $v0
	li $v0,10
	move $a1,$v0
	pop $a0
	slt $v0,$a0,$a1
	popaa
	beq $v0,$zero,$LABEL3
	pushaa
	la $v1,$LABEL1
	lw $v0,0($v1)
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	la $v1,$LABEL1
	lw $v0,0($v1)
	push $v1
	pushaa
	la $v1,$LABEL1
	lw $v0,0($v1)
	push $v0
	li $v0,1
	move $a1,$v0
	pop $a0
	add $v0,$a0,$a1
	popaa
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	j $LABEL2
$LABEL3:
	move $v0,$zero
	li $v0 10
	syscall
