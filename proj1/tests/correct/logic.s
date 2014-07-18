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
	pushaa
	pushaa
	li $v0,0
	beq $v0,$zero,$LABEL0
	li $v0,0
	beq $v0,$zero,$LABEL0
	li $v0,1
	j $LABEL1
$LABEL0:
	move $v0,$zero
$LABEL1:
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	li $v0,0
	beq $v0,$zero,$LABEL2
	li $v0,2
	beq $v0,$zero,$LABEL2
	li $v0,1
	j $LABEL3
$LABEL2:
	move $v0,$zero
$LABEL3:
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	li $v0,3
	beq $v0,$zero,$LABEL4
	li $v0,0
	beq $v0,$zero,$LABEL4
	li $v0,1
	j $LABEL5
$LABEL4:
	move $v0,$zero
$LABEL5:
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	li $v0,4
	beq $v0,$zero,$LABEL6
	li $v0,5
	beq $v0,$zero,$LABEL6
	li $v0,1
	j $LABEL7
$LABEL6:
	move $v0,$zero
$LABEL7:
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	li $v0,0
	bne $v0,$zero,$LABEL9
	li $v0,0
	bne $v0,$zero,$LABEL9
	move $v0,$zero
	j $LABEL8
$LABEL9:
	li $v0,1
$LABEL8:
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	li $v0,0
	bne $v0,$zero,$LABEL11
	li $v0,2
	bne $v0,$zero,$LABEL11
	move $v0,$zero
	j $LABEL10
$LABEL11:
	li $v0,1
$LABEL10:
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	li $v0,3
	bne $v0,$zero,$LABEL13
	li $v0,0
	bne $v0,$zero,$LABEL13
	move $v0,$zero
	j $LABEL12
$LABEL13:
	li $v0,1
$LABEL12:
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	li $v0,4
	bne $v0,$zero,$LABEL15
	li $v0,5
	bne $v0,$zero,$LABEL15
	move $v0,$zero
	j $LABEL14
$LABEL15:
	li $v0,1
$LABEL14:
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	li $v0 10
	syscall
