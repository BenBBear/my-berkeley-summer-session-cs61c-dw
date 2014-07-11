fib:

	push $ra
	pushaa
	add $v1,$sp,12
	lw $v0,0($v1)
	push $v0
	
	pushaa
	add $v1,$sp,24
	lw $v0,0($v1)
	push $v0
	li $v0,1 
	move $a1,$v0
	pop $a0
	sub $v0,$a0,$a1
	popaa
	
	move $a1,$v0
	pop $a0
	
	and $v0,$a0,$a1	
	popaa
	####THE STACK KEEP STILL
	
	beq $v0,$zero,LABEL2
	pushaa
	########################################################
	pushaa
	add $v1,$sp,20
	lw $v0,0($v1)
	push $v0
	li $v0,1
	move $a1,$v0
	pop $a0
	sub $v0,$a0,$a1
	popaa
	#########################################################(- n 1)
	push $v0 ## transfer argument
	jal fib
	###########################################################
	push $v0
	###suspicious, for the (+ (..) (..))	
	##########################################################
	pushaa
	add $v1,$sp,28
	lw $v0,0($v1)
	push $v0
	li $v0,2
	move $a1,$v0
	pop $a0
	sub $v0,$a0,$a1
	popaa
	#######################################################
	
	push $v0
	jal fib
	#####################################################add stuff
	move $a1,$v0
	pop $a0
	
	#######################################################
	add $v0,$a0,$a1
	popaa
	j LABEL1
LABEL2:
	add $v1,$sp,12
	lw $v0,0($v1)
	
		
		
LABEL1:
	pop $ra
