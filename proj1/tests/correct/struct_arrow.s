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

$LABEL0: .word 0 0 0 0 0 0 
$LABEL1: .word 0 0 0 0 0 0 
$LABEL2: .word 0 0 0 0 
$LABEL3: .word 0 0 0 0 0 0 
$LABEL4: .word 0 0 0 0 0 
$LABEL5: .word 0 0 0 0 0 0 
$LABEL6: .asciiz "hi"
$LABEL7: .asciiz "string"
$LABEL8: .asciiz "\n"
$LABEL9: .word 0 0 0 0 
$LABEL10: .word 0 0 0 0 0 0 
$LABEL11: .word 0 0 0 0 0 0 
$LABEL12: .word 0 0 0 0 
$LABEL13: .word 0 0 0 0 0 0 
$LABEL14: .word 0 0 0 0 0 
$LABEL15: .word 0 0 0 0 0 0 
	.text
	.globl main
	j  main


	main:
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL0
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	li $v0,4
	sw $v0,16($a0)
	li $v0,5
	sw $v0,20($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,0
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL1
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	li $v0,4
	sw $v0,16($a0)
	li $v0,5
	sw $v0,20($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,1
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL2
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,2
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL3
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	li $v0,4
	sw $v0,16($a0)
	li $v0,5
	sw $v0,20($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,3
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL4
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	li $v0,4
	sw $v0,16($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,4
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL5
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	li $v0,4
	sw $v0,16($a0)
	li $v0,5
	sw $v0,20($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,5
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL9
	li $v0,0
	sw $v0,0($a0)
	la $v0,$LABEL6
	sw $v0,4($a0)
	la $v0,$LABEL7
	sw $v0,8($a0)
	la $v0,$LABEL8
	sw $v0,12($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,3
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL10
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	li $v0,4
	sw $v0,16($a0)
	li $v0,5
	sw $v0,20($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,0
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL11
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	li $v0,4
	sw $v0,16($a0)
	li $v0,5
	sw $v0,20($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,1
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL12
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,2
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL13
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	li $v0,4
	sw $v0,16($a0)
	li $v0,5
	sw $v0,20($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,3
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL14
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	li $v0,4
	sw $v0,16($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,4
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	pushaa
	la $a0,$LABEL15
	li $v0,0
	sw $v0,0($a0)
	li $v0,1
	sw $v0,4($a0)
	li $v0,2
	sw $v0,8($a0)
	li $v0,3
	sw $v0,12($a0)
	li $v0,4
	sw $v0,16($a0)
	li $v0,5
	sw $v0,20($a0)
	move $v0,$a0
	popaa
	push $v0
	li $v0,5
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	li $v0 10
	syscall
