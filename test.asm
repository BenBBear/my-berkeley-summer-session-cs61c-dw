
.data 
test: .word 1


.text 
.globl main
j main


main:
	la $v0,test
	lw $v0,0($v0)
	
	
	li $v0,10
	syscall