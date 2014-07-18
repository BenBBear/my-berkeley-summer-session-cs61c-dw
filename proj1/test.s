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
$LABEL1: .asciiz "helloword"
$LABEL2: .word 0 0 
$LABEL3: .word 0
$LABEL4: .word 0
$LABEL5: .asciiz "\n"
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
	la $v1,$LABEL3
	lw $v0,0($v1)
	push $v1
	pushaa
	la $a0,$LABEL2
	li $v0,1
	sw $v0,0($a0)
	la $v0,$LABEL1
	sw $v0,4($a0)
	move $v0,$a0
	popaa
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	la $v1,$LABEL4
	lw $v0,0($v1)
	push $v1
	pushaa
	li $v0,10
	push $v0
	move $v0,$zero
	move $a1,$v0
	pop $a0
	add $v0,$a0,$a1
	popaa
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	move $v0,$zero
	pushaa
	jal get_1
	push $v0
	la $v1,$LABEL4
	lw $v0,0($v1)
	move $a1,$v0
	pop $a0
	sub $v0,$a0,$a1
	popaa
	push $v0
	jal test_fun
	pop $zero
	move $v0,$zero
	li $v0,0
	push $v0
	li $v0,0
	push $v0
	jal all
	pop $zero
	pop $zero
	li $v0 10
	syscall
test_fun:
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
get_1:
	push $ra
	li $v0,1
	pop $ra
	jr $ra
all:
	push $ra
	pushaa
$LABEL6:
	pushaa
	add $v1,$sp,24
	lw $v0,0($v1)
	push $v0
	li $v0,10
	move $a1,$v0
	pop $a0
	slt $v0,$a0,$a1
	popaa
	beq $v0,$zero,$LABEL7
	pushaa
	add $v1,$sp,24
	lw $v0,0($v1)
	push $v0
	li $v0,7
	move $a1,$v0
	pop $a0
	seq $v0,$a0,$a1
	popaa
	beq $v0,$zero,$LABEL8
	pushaa
	jal get_1
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	j $LABEL9
$LABEL8:
	li $v0,0
$LABEL9:
	pushaa
$LABEL10:
	pushaa
	add $v1,$sp,28
	lw $v0,0($v1)
	push $v0
	li $v0,10
	move $a1,$v0
	pop $a0
	slt $v0,$a0,$a1
	popaa
	beq $v0,$zero,$LABEL11
	pushaa
	add $v1,$sp,28
	lw $v0,0($v1)
	push $v1
	pushaa
	li $v0,1
	push $v0
	add $v1,$sp,44
	lw $v0,0($v1)
	move $a1,$v0
	pop $a0
	add $v0,$a0,$a1
	popaa
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	add $v1,$sp,28
	lw $v0,0($v1)
	push $v0
	li $v0,5
	move $a1,$v0
	pop $a0
	slt $v0,$a0,$a1
	popaa
	beq $v0,$zero,$LABEL12
	pushaa
	pushaa
	la $v1,$LABEL3
	lw $v0,0($v1)
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
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	j $LABEL13
$LABEL12:
	pushaa
	pushaa
	la $v1,$LABEL3
	lw $v0,0($v1)
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
$LABEL13:
	pushaa
	la $v0,$LABEL5
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	j $LABEL10
$LABEL11:
	move $v0,$zero
	popaa
	pushaa
	add $v1,$sp,20
	lw $v0,0($v1)
	push $v1
	li $v0,0
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	add $v1,$sp,24
	lw $v0,0($v1)
	push $v1
	pushaa
	add $v1,$sp,36
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
	j $LABEL6
$LABEL7:
	move $v0,$zero
	popaa
	pop $ra
	jr $ra
