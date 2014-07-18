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

$LABEL0: .asciiz "A truly nasty example of scoping in LIFC."
$LABEL1: .asciiz "Credit for it goes to Ulysse Manceron."
$LABEL2: .word 0
	.text
	.globl main
	j  main


	main:
	la $v0,$LABEL0
	la $v0,$LABEL1
	pushaa
	la $v1,$LABEL2
	lw $v0,0($v1)
	push $v1
	li $v0,21
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	move $v0,$zero
	pushaa
	la $v1,$LABEL2
	lw $v0,0($v1)
	push $v0
	li $v0,2
	move $a1,$v0
	pop $a0
	mul $v0,$a0,$a1
	popaa
	push $v0
	jal mycode
	pop $zero
	li $v0 10
	syscall
mycode:
	push $ra
	pushaa
	add $v1,$sp,12
	lw $v0,0($v1)
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pop $ra
	jr $ra
