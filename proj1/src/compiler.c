/* Author:  YOUR NAME HERE */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "code_gen.h"
#include "util/util.h"
#include <editline/readline.h>
#include <editline/history.h>
#define MAX(X,Y) (X > Y ? X : Y)










char* enum_String[] = {"token_INT"/* integer literal */,
					  "token_STRING" /* string literal*/,
					  "token_NAME" /* variable or function name */,
					  "token_KEYWORD" /* keyword */,
					  "token_OPEN_PAREN" /* '(' */,
					  "token_CLOSE_PAREN" /* ')' */,
					  "token_END" /* end of file */,
					  "token_SENTINEL" /* 'special' value */};

AST **top_level_asts = NULL;
size_t num_top_level_asts = 0;
size_t top_level_asts_cap = 0;



void print_ast(AST* tree){
	AST_lst* c = NULL;
	int r = rand() % 20;
	switch(tree->type){
	case node_INT:case  node_VAR:
		printf("%s ",tree->val);
		break;
	default:
		c = tree->children;
		printf("(");
		printf("%s ",tree->val);
		while(c){
			print_ast(c->val);
			c = c->next;
		}
		printf(")");
		if (r<5){ 				/*for formatting */
			printf("\n");
		}
		break;
	}
}

/* typedef enum node_type {node_INT /\* integer literal *\/, */
/* 						node_STRING /\* string literal*\/, */
/* 						node_VAR /\* Name of a variable or a function. *\/, */
/* 						node_CALL /\* A call to a function *\/, */
/* 						/\* The different built-in utilitites. *\/ */
/* 						node_AND, node_OR, node_PLUS, node_MINUS, node_MUL, */
/* 						node_LT, node_EQ, node_DIV, node_FUNCTION, */
/* 						node_STRUCT, node_ARROW, node_ASSIGN, node_IF, */
/* 						node_WHILE, node_FOR, node_SEQ, node_I_PRINT, */
/* 						node_S_PRINT, node_READ_INT, node_READ_CHAR} node_type; */

char* enum_to_str(node_type n){
	switch(n){
	case node_INT:
		return "node_INT";
		break;
	case node_STRING:
		return "node_STRING";
		break;
	case node_VAR:
		return "node_VAR";
		break;
	case node_CALL:
		return "node_CALL";
		break;
	case node_AND:
		return "node_AND";
		break;
	case node_OR:
		return "node_OR";
		break;
	case node_PLUS:
		return "node_PLUS";
		break;
	case node_MINUS:
		return "node_MINUS";
		break;
	case node_MUL:
		return "node_MUL";
		break;
	case node_LT:
		return "node_LT";
		break;
	case node_EQ:
		return "node_EQ";
		break;
	case node_DIV:
		return "node_DIV";
		break;
	case node_FUNCTION:
		return "node_FUNCTION";
		break;
	case	node_STRUCT:
		return "node_STRUCT";
		break;
	case node_ARROW:
		return "node_ARROW";
		break;
	case node_ASSIGN:
		return "node_ASSIGN";
		break;
	case node_IF:
		return "node_IF";
		break;
	case	node_WHILE:
		return "node_WHILE";
		break;
	case node_FOR:
		return "node_FOR";
		break;
	case node_SEQ:
		return "node_SEQ";
		break;
	case node_I_PRINT:
		return "node_I_PRINT";
		break;
	case node_S_PRINT:
		return "node_S_PRINT";
		break;
	case node_READ_INT:
		return "node_READ_INT";
		break;
	case node_READ_CHAR:
		return "node_READ_CHAR";
		break;
	}
	return "";
}

void print_ast_m(int t,AST* tree){
	int i = 0;
	if(tree == NULL){
		for(i = 0;i<t;i++)
			printf("\t");
		printf("EMPTY NODE\n\n");
		return;
	}

	for(i = 0;i<t;i++)
		printf("\t");
	printf("TYPE: %s\n", enum_to_str(tree->type));
	for(i = 0;i<t;i++)
		printf("\t");
	printf("VALUE: %s\n",tree->val);
	for(i = 0;i<t;i++)
		printf("\t");
	printf("CHILDREN:\n");
	AST_lst* chd = tree->children;
	t++;
	while(chd){
		print_ast_m(t, chd->val);
		chd = chd->next;
	}
}


/** Prints the appropriate usage of this executable. */
void usage() {
    fatal_error("Usage: lifcc DIR/BASE.lc\n");
}

void append_ast_to_top_level(AST *ast) {
    if (num_top_level_asts >= top_level_asts_cap) {
		top_level_asts_cap = MAX(1, 2 * top_level_asts_cap);
		top_level_asts = safe_realloc(top_level_asts,
									  top_level_asts_cap * sizeof(AST*));
    }
    top_level_asts[num_top_level_asts++] = ast;
}

/** Compiles the LIFC program residing in FILENAME and prints
 *  the results to stdout. */
void compile(char *filename) {

    lexer luthor;
    /* Initialize lexer. */
    init_lex(&luthor);
    open_file(&luthor, filename);


/////////////////////////////////////////////////////////////////////////////
    /* Run parser. */
    parse_init();
    while (peek_type(&luthor) != token_END) {

		/* printf("peek type is:%s, peek value is:%s \n",enum_String[luthor.type],luthor.buffer); */
		AST *ast = build_ast(&luthor);

		append_ast_to_top_level(ast);  //a array of ast

		read_token(&luthor);
		check_tree_shape(ast);
		gather_decls(ast, "", 1);
		/* print_ast_m(0,ast); */
		/* printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n"); */
    }
    /* Run code generation. */
	emit_macro();
	emit_static_memory();

    for (size_t i = 0; i < num_top_level_asts; i += 1) {
    	emit_strings(top_level_asts[i]); /* to put all the initial value into .data, include the value inside a struct,and struct*/
		/* and replace those string_node->val,int_node->val into the label in the mips */
		emit_structs(top_level_asts[i]);

		emit_globals(top_level_asts[i]);
    }

	emit_text();

    for (size_t i = 0; i < num_top_level_asts; i += 1) {
    	emit_main(top_level_asts[i],0); /* all variables stored in the static frame */
    }/* all the variable in here could assess from there mips label */
    emit_exit();

    for (size_t i = 0; i < num_top_level_asts; i += 1) {
    	emit_functions(top_level_asts[i]);
    }


/////////////////////////////////////////////////////////////////////////////
    /* Cleanup. */
    close_file(&luthor);
    parse_close();
    for (size_t i = 0; i < num_top_level_asts; i += 1) {
    	free_ast(top_level_asts[i]);
    }
    if (top_level_asts) {
    	free(top_level_asts);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
		usage();
    }
	var_addr = smap_new();
    compile(argv[1]);
	smap_del(var_addr);



    return 0;
}
