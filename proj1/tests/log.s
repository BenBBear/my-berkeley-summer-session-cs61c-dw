fib:

	
	beq $v0,$zero,LABEL2
	pushaa
	#########################################################(- n 1)
	push $v0 ## transfer argument
	jal fib
	###########################################################
	push $v0
	###suspicious, for the (+ (..) (..))	
	##########################################################
	
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
