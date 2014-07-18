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

$LABEL0: .asciiz "success\n"
$LABEL1: .asciiz "fail\n"
$LABEL2: .asciiz "fail\n"
$LABEL3: .asciiz "success\n"
	.text
	.globl main
	j  main


	main:
	li $v0,1
	beq $v0,$zero,$LABEL4
	pushaa
	la $v0,$LABEL0
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	j $LABEL5
$LABEL4:
	pushaa
	la $v0,$LABEL1
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
$LABEL5:
	li $v0,0
	beq $v0,$zero,$LABEL6
	pushaa
	la $v0,$LABEL2
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	j $LABEL7
$LABEL6:
	pushaa
	la $v0,$LABEL3
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
$LABEL7:
	li $v0 10
	syscall
