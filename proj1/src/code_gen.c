#include "code_gen.h"
#include "parser.h"
#include<assert.h>
#include <stdlib.h>
/* char var_label[20]; */
/* char temp_label[20]; */
/* unsigned int var_number = 0; */
/* unsigned int temp_number = 0; */



char _label[30];
char _label2[30];
unsigned int _number = 0;



#define PRE_MARK -7
#define LABEL _label
#define LABEL2 _label2

#define FOR_LABEL_AGAIN _label
#define FOR_LABEL_OUT _label2

#define LOOP_LABEL_AGAIN _label
#define LOOP_LABEL_OUT _label2


char _stack[30];
int push_counter = 0;
#define GET_VARIABLE_IN_STACK(x) sprintf(_stack,"%d($sp)",(push_counter - x)*4)
#define GET_STACK_DIFF(x) sprintf(_stack,"%d" ,4*(push_counter - x))
#define LOCAL_VAR_ADDRESS _stack
#define SET_STACK_COUNTER(_x_) push_counter = _x_
#define ADD_STACK_COUNTER() push_counter++
#define SUB_STACK_COUNTER() push_counter--
#define STACK_COUNTER push_counter



#define ON 1
#define OFF 0
int assign_mark = 0;
#define TURN_ON_ASSIGN() assign_mark = 1
#define TURN_OFF_ASSIGN() assign_mark = 0
#define ASSIGN_MARK assign_mark


#define GET_LABEL()do{										\
		sprintf(_label,"LABEL%d",_number++);				\
	}while(0)

#define GET_LABEL2()do{										\
		sprintf(_label2,"LABEL%d",_number++);				\
	}while(0)

#define PUSHAA()do{									\
		printf("\tpushaa\n");						\
		ADD_STACK_COUNTER();ADD_STACK_COUNTER();	\
}while(0)
#define POPAA() do{ printf("\tpopaa\n");			\
		SUB_STACK_COUNTER();SUB_STACK_COUNTER();	\
}while(0)
#define PUSH(x)do{  printf("\tpush %s\n",x);	\
		ADD_STACK_COUNTER();					\
}while(0)
#define POP(x) do{ printf("\tpop %s\n",x);			\
		SUB_STACK_COUNTER();						\
			}while(0)
#define MOVE(x,y) printf("\tmove %s,%s\n",x,y)
#define LW(x,y) printf("\tlw %s,%s\n",x,y)
#define SW(x,y) printf("\tsw %s,%s\n",x,y)
#define LA(x,y)   printf("\tla %s,%s\n",x,y)
#define LI(x,y) printf("\tli %s,%s\n",x,y)
#define BEQ(x,y,b) printf("\tbeq %s,%s,%s\n",x,y,b)
#define PUT_LABEL(x) printf("%s:\n",x)
#define JAL(x) printf("\tjal %s\n",x)
#define J(x) printf("\tj %s\n",x)
#define JR(x) printf("\tjr %s\n",x)
#define ADD(x,y,z) printf("\tadd %s,%s,%s\n",x,y,z)
#define AND(x,y,z) printf("\tand %s,%s,%s\n",x,y,z)
#define SEQ(x,y,z) printf("\tseq %s,%s,%s\n",x,y,z)
#define OR(x,y,z) printf("\tor %s,%s,%s\n",x,y,z)

#define MUL(x,y,z) printf("\tmul %s,%s,%s\n",x,y,z)
#define DIV(x,y,z) printf("\tdiv %s,%s,%s\n",x,y,z)
#define SUB(x,y,z) printf("\tsub %s,%s,%s\n",x,y,z)
#define SLT(x,y,z) printf("\tslt %s,%s,%s\n",x,y,z)
#define SYSCALL() printf("\tsyscall\n");

#define PROLOG_OF_TWO() do{						\
		PUSHAA();								\
		emit_main(chd->val,fmark);				\
		PUSH("$v0");							\
		emit_main(chd->next->val,fmark);		\
		MOVE("$v0", "$a1");						\
		POP("$a0");								\
	}while(0)



#define REWIND_STACK() while(arg_number > 0){	\
		arg_number--;								\
		POP("$zero");								\
		}

/** True iff the data segment has already been partially printed. */
int data_seg_opened = 0;

/** True iff the text segment has already been partially printed. */
int text_seg_opened = 0;

smap* var_addr;
/* use
   testAB: .asciiz  "Testing linked lists A and B (should be 0): " */
void emit_strings(AST *ast) {
		if (ast->type == node_STRING){
			GET_LABEL();
			printf("%s: .asciiz %s\n",LABEL,ast->val);
			strcpy(ast->val,LABEL);
			return;
		}else{
			AST_lst* chd = ast->children;
			while(chd){
				emit_strings(chd->val);
				chd = chd->next;
			}
			return;
		}
}
void emit_structs(AST *ast){
	unsigned int i = 0;
	if (ast->type == node_STRUCT){
			GET_LABEL();
			printf("%s: .word ",LABEL);

			for(i = 0; i <AST_lst_len(ast->children);i++)
				printf("0 ");  	/* variable also use this method */

			printf("\n");
			strcpy(ast->val,LABEL);
			return;
		}else{
			AST_lst* chd = ast->children;
			while(chd){
				emit_structs(chd->val);
				chd = chd->next;
			}
			return;
	}
}


void emit_globals(AST *ast){
	if (ast->type != node_FUNCTION){
		if (ast->type == node_ASSIGN){
			GET_LABEL();
			smap_put(var_addr, ast->children->val->val, _number-1);
			printf("%s: .word 0",LABEL);
		}
	}else{
		return;
	}
}

/* first one */
/* .data
   C5:	.word 2 0
   C4:	.word 5 C5*/
void emit_static_memory() {
	printf(".data\n");
}

void emit_text(){
	printf("\t.text\n");
	printf("\t.globl main\n");
	printf("j  main");
}


char varaddress[20];
void emit_main(AST *ast,int fmark) {
	AST_lst* chd = ast->children;
	int struct_mem_count = 0;
	if (ast->type == node_FUNCTION){
		return;
	}else{

		switch(ast->type){
			///////////////////////////////////////////////////////////////////////////single value
		case node_VAR:
			if (fmark == 0 || strchr(ast->val,'-')){
				sprintf(varaddress,"LABEL%d",smap_get(var_addr, ast->val));
				if (ASSIGN_MARK == ON){
					LA("$v0", varaddress);
				}else{
					LA("$v0", varaddress);
					LW("$v0","0($v0)");
				}
			}else{
				GET_STACK_DIFF(smap_get(var_addr,ast->val));
				if (ASSIGN_MARK == ON){
					ADD("$v0","$sp",LOCAL_VAR_ADDRESS);
				}else{
					ADD("$v0","$sp",LOCAL_VAR_ADDRESS);
					LW("$v0","0($v0)");
				}
			}
			TURN_OFF_ASSIGN();
			break;

		case node_INT:
			LI("$v0",ast->val);
			break;

		case node_STRING:
			LA("$v0",ast->val);
			break;

		case node_STRUCT:
			PUSHAA();

			LA("$a0",ast->val);
			while(chd){
				emit_main(chd->val,fmark);
				sprintf(varaddress,"%d($a0)",4*struct_mem_count);
				SW("$v0",varaddress);
				struct_mem_count++;
				chd = chd->next;
			}

			MOVE("$v0","$a0");
			POPAA();
			break;
			/////////////////////////////////////////////////////////////////////////////two args
		case  node_ASSIGN:
			TURN_ON_ASSIGN();
			PROLOG_OF_TWO();

			SW("$a1","0($a0)");	/* here the a0 should be the address of the variable*/
			/* in other case the a0 should be the value of the variable */
			MOVE("$a1","$v0"); /* return the value of the variable */

			POPAA();
			break;

		case node_EQ:
			PROLOG_OF_TWO();

			SEQ("v0","$a0","$a1");

			POPAA();
			break;

		case node_AND:
			PROLOG_OF_TWO();

			AND("$v0","$a0","$a1");

			POPAA();
			break;
		case node_OR:
			PROLOG_OF_TWO();

			OR("$v0","$a0","$a1");

			POPAA();
			break;
		case node_LT:
			PROLOG_OF_TWO();
			SLT("$v0","$a0","$a1");
			POPAA();
			break;

		case node_DIV:
			PROLOG_OF_TWO();
			DIV("$v0","$a0","$a1");
			POPAA();
			break;
		case node_MUL:
			PROLOG_OF_TWO();
			MUL("$v0","$a0","$a1");
			POPAA();
			break;
		case node_PLUS:
			PROLOG_OF_TWO();
			ADD("$v0","$a0","$a1");
			POPAA();
			break;
		case node_MINUS:
			PROLOG_OF_TWO();
			SUB("$v0","$a0","$a1");
			POPAA();
			break;
		case node_ARROW:
			PROLOG_OF_TWO();
			MUL("$a1","$a1","4");
			ADD("$a1","$a1","$a0");
			LW("$v0","0($a1)");
			POPAA();
			break;


			////////////////////////////////////////////////////////////////////////////more args
		case node_IF:
			emit_main(ast->children->val,fmark);
			GET_LABEL();
			BEQ("$v0","$zero",LABEL);
			emit_main(ast->children->next->val,fmark);
			PUT_LABEL(LABEL);
			emit_main(ast->children->next->next->val,fmark);
			break;

		case node_CALL:
			while(chd){
				emit_main(chd->val,fmark);
				PUSH("$v0");
				chd = chd->next;
			}
			JAL(ast->val);

			break;

		case node_FOR:
			GET_LABEL();
			GET_LABEL2();
			emit_main(chd->val,fmark); /* for's INIT */

			PUT_LABEL(FOR_LABEL_AGAIN);
			emit_main(chd->next->val,fmark);
			BEQ("$v0","$zero",FOR_LABEL_OUT);
			emit_main(chd->next->next->val,fmark);
			chd = chd->next->next->next;
			while(chd){
				emit_main(chd->val,fmark);
				chd = chd->next;
			}
			J(FOR_LABEL_AGAIN);
			PUT_LABEL(FOR_LABEL_OUT);
			break;

		case node_WHILE:
			PUSHAA();
			emit_main(ast->children->val, fmark);
			GET_LABEL();
			GET_LABEL2();
			PUT_LABEL(LOOP_LABEL_AGAIN);

			BEQ("$v0","$zero",LOOP_LABEL_OUT);

			while(chd){
				emit_main(chd->val,fmark);
				chd = chd->next;
			}

			J(LOOP_LABEL_AGAIN);
			PUT_LABEL(LOOP_LABEL_OUT);
			POPAA();
			break;
		case node_SEQ:
			PUSHAA();

			while(chd){
				emit_main(chd->val,fmark);
				chd = chd->next;
			}

			POPAA();
			break;
			/////////////////////////error///////////////////////////////////////
		case node_FUNCTION:
			my_perror("Should not been here");
			break;
			//////////////////////////system call////////////////////////////////////
		case node_I_PRINT:
			PUSHAA();
			emit_main(ast->children->val, fmark);
			MOVE("$v0","$a0");
			LI("$v0","1");
			SYSCALL();
			POPAA();
			break;
		case node_S_PRINT:
			PUSHAA();
			emit_main(ast->children->val, fmark);
			MOVE("$v0","$a0");
			LI("$v0","4");
			SYSCALL();
			POPAA();
			break;
		case node_READ_INT:
			PUSHAA();
			LI("$v0","5");
			SYSCALL();
			POPAA();
			break;
		case node_READ_CHAR:
			PUSHAA();
			LI("$v0","12");
			SYSCALL();
			POPAA();
			break;
		}
	}
}

void emit_exit() {
    printf("    li $v0 10\n");
    printf("    syscall\n");
}



void emit_functions(AST *ast) {
	if (ast->type != node_FUNCTION){
		return;
	}else{
		AST_lst* BODY = ast->children->next;
		AST* FBODY_PART = NULL;
		AST* arguments = ast->children->val;

		PUT_LABEL(arguments->val);


		int arg_number = AST_lst_len(arguments->children);
		AST_lst* arglst = arguments->children;
		int begin = -arg_number+1;
		while(arglst){
			smap_put(var_addr, arglst->val->val, STACK_COUNTER+begin);
			begin++;
			arglst = arglst->next;
		}

		/* assert(begin == (-arg_number)); */

		PUSH("$ra");

		while(BODY){
			FBODY_PART = BODY->val;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			emit_main(FBODY_PART, 1);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			BODY = BODY->next;
		}
		POP("$ra");
		/* assert(STACK_COUNTER <= 0); */
		REWIND_STACK();

		JR("$ra");
	}
}



void emit_macro() {
	printf(".macro push (%%arg)\n");
	printf("add $sp,$sp,-4\n");
	printf("sw %%arg,0($sp)\n");
	printf(".end_macro\n\n");

	printf(".macro pop (%%arg)\n");
	printf("lw %%arg,0($sp)\n");
	printf("add $sp,$sp,4\n");
	printf(".end_macro\n\n");

	printf(".macro pushaa ()\n");
	printf("push $a0\n");
	printf("push $a1\n");
	printf(".end_macro\n");

	printf(".macro popaa ()\n");
	printf("pop $a1\n");
	printf("pop $a0\n");
	printf(".end_macro\n");

	printf(".macro pushall ()\n");
	printf("	push $v0\n");
	printf("	push $v1\n");
	printf("	push $a0\n");
	printf("	push $a1\n");
	printf("	push $a2\n");
	printf("	push $a3\n");
	printf("	push $t0\n");
	printf("	push $t1\n");
	printf("	push $t2\n");
	printf("	push $t3\n");
	printf("	push $t4\n");
	printf("	push $t5\n");
	printf("	push $t6\n");
	printf("	push $t7\n");
	printf("	push $s0\n");
	printf("	push $s1\n");
	printf("	push $s2\n");
	printf("	push $s3\n");
	printf("	push $s4\n");
	printf("	push $s5\n");
	printf("	push $s6\n");
	printf("	push $s7\n");
	printf(".end_macro\n");
	printf(".macro popall ()\n");
	printf("	pop $s7\n");
	printf("	pop $s6\n");
	printf("	pop $s5\n");
	printf("	pop $s4\n");
	printf("	pop $s3\n");
	printf("	pop $s2\n");
	printf("	pop $s1\n");
	printf("	pop $s0\n");
	printf("	pop $t7\n");
	printf("	pop $t6\n");
	printf("	pop $t5\n");
	printf("	pop $t4\n");
	printf("	pop $t3\n");
	printf("	pop $t2\n");
	printf("	pop $t1\n");
	printf("	pop $t0\n");
	printf("	pop $a3\n");
	printf("	pop $a2\n");
	printf("	pop $a1\n");
	printf("	pop $a0\n");//push all before the function call
	/* printf("	pop $v1\n"); */
	/* printf("	pop $v0\n"); */
	printf(".end_macro\n");
	return;
}
