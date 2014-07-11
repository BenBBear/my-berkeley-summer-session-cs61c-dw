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

LABEL0: .word 0
LABEL1: .asciiz "hello"
LABEL2: .word 0
LABEL3: .word 0
LABEL4: .asciiz "world"
LABEL5: .word 0
	.text
	.globl main
	j  main


	main:
	pushaa
	la $v1,LABEL3
	lw $v0,0($v1)
	push $v1
	li $v0,3
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	la $v1,LABEL5
	lw $v0,0($v1)
	push $v1
	la $v0,LABEL1
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	la $v1,LABEL3
	lw $v0,0($v1)
	move $a0,$v0
	li $v0,1
	syscall
	popaa
	pushaa
	la $v1,LABEL5
	lw $v0,0($v1)
	move $a0,$v0
	li $v0,4
	syscall
	popaa
	pushaa
	pushaa
	la $v1,LABEL3
	lw $v0,0($v1)
	push $v1
	li $v0,5
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	popaa
	pushaa
	pushaa
	la $v1,LABEL5
	lw $v0,0($v1)
	push $v1
	la $v0,LABEL4
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	move $a0,$v0
	li $v0,4
	syscall
	popaa
	pushaa
	la $v1,LABEL5
	lw $v0,0($v1)
	move $a0,$v0
	li $v0,1
	syscall
	popaa
	li $v0 10
	syscall
