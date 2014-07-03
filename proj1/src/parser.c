#include "parser.h"
#include "lexer.h"
#include <string.h>
#include <stdlib.h>

#define ASTREE_NODE(r_tree,n_type,m_child,m_last_child)do {	\
		r_tree = malloc(sizeof(AST));						\
		r_tree->type = n_type;								\
		r_tree->val = malloc(strlen(lex->buffer)+1);		\
		strcpy(r_tree->val,lex->buffer);					\
		r_tree->children = m_child;							\
		r_tree->last_child =m_last_child;					\
	} while(0)

/** An array of the different string values of keywords. */
char *keywords[] = {"and", "or", "+", "-", "*", "/", "lt", "eq",
					"function", "struct", "arrow", "assign", "if",
					"while", "for", "sequence", "intprint", "stringprint",
					"readint"};
/** Sister array of keywords. Keeps track of the corresponding enum. */
int enums[] = {node_AND, node_OR, node_PLUS, node_MINUS, node_MUL, node_DIV,
			   node_LT, node_EQ, node_FUNCTION, node_STRUCT,
			   node_ARROW, node_ASSIGN, node_IF, node_WHILE, node_FOR,
			   node_SEQ, node_I_PRINT, node_S_PRINT, node_READ_INT};
/** A hashmap used for more efficient lookups of (keyword, enum) pairs. */
smap *keyword_str_to_enum;
smap *keyword_or_not;

/** Initializes keyword_str_to_enum so that it contains a map
 *  from the string value of a keyword to its corresponding enum. */
void initialize_keyword_to_enum_mapping();


void parse_init() {
    decls = smap_new();  //smap --> easy to use string hashmap
    stack_sizes = smap_new();
    num_args = smap_new();
    strings = smap_new();
    keyword_str_to_enum = smap_new();
	keyword_or_not = smap_new();
}

void parse_close() {
    smap_del_contents(decls);
    smap_del(decls);
    smap_del(stack_sizes);
    smap_del(num_args);
    smap_del(strings);
    smap_del(keyword_str_to_enum);
}

AST *build_ast (lexer *lex) { 	/* a big one!! */
    /* TODO: Implement me. */
    /* Hint: switch statements are pretty cool, and they work
     *       brilliantly with enums. */
	AST* r_tree = NULL;
	switch(lex->type){
	case token_STRING:
		ASTREE_NODE(r_tree, node_STRING,NULL,NULL);
		break;
	case token_INT:
		ASTREE_NODE(r_tree, node_INT, NULL, NULL);
		break;
	case token_OPEN_PAREN:
		/* here we need a while loop */
		read_token(lex);
		r_tree = build_ast(lex);
		read_token(lex);
		if (lex->type != token_CLOSE_PAREN){
			free_ast(r_tree);
			perror("Parentheses not match!!");
			return NULL;
		}
		break;
	case token_END:
		r_tree = NULL;
		break;
	case token_SENTINEL:		/* impossible in here */
		read_token(lex);
		r_tree = build_ast(lex);
		break;
	case token_CLOSE_PAREN: 	/* also impossible in here */
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case token_KEYWORD:			/* todo */
		break;
	case token_NAME: 			/* todo */
		break;
	}
    return r_tree;
}
/* struct AST { */
/*     node_type type; /\* The type of  *\/ */
/*     char *val; /\* The source text which spawned this node. *\/ */
/*     AST_lst *children; /\* A list of all of the children of this node*\/ */
/*     AST_lst *last_child; /\* A minor kludge to avoid O(n) insertion times. *\/ */
/* }; */

/* struct AST_lst { */
/*     AST *val; */
/*     AST_lst *next; */
/* }; */
void free_ast (AST *ptr) {
	if (ptr == NULL){
		return;
	}
	free(ptr->val);
	AST_lst* cursor = ptr->children,*prev = cursor;
	while(cursor){
		free_ast(cursor->val);
		prev = cursor;
		cursor = cursor->next;
		free(prev);
	}
	free(ptr);
	return;
}

void check_tree_shape(AST *ptr) {
    /* TODO: Implement me. */
    /* Hint: This function is just asking to be table-driven */
}

void gather_decls(AST *ast, char *env, int is_top_level) {
    /* TODO: Implement me. */
    /* Hint: switch statements are pretty cool, and they work
     *       brilliantly with enums. */
}

node_type lookup_keyword_enum(char *str) {
    if (smap_get(keyword_str_to_enum, keywords[0]) == -1) {
		initialize_keyword_to_enum_mapping();
    }
    return smap_get(keyword_str_to_enum, str);
}

int keyword_enum_or_not(char *str) {
    if (smap_get(keyword_or_not, keywords[0]) == -1) {
		initialize_keyword_to_enum_mapping();
    }
    return smap_get(keyword_or_not, str);
}



void initialize_keyword_to_enum_mapping() {
    /* Note that enums is an *array*, not a pointer, so this
     * sizeof business is reasonable. */
    size_t num_keywords = sizeof(enums) / sizeof(int);
    for (size_t i = 0; i < num_keywords; i += 1) {
		smap_put(keyword_str_to_enum, keywords[i], enums[i]);
		smap_put(keyword_or_not, keywords[i], 1);
    }
}

size_t AST_lst_len(AST_lst *lst) {
    int num_fields = 0;
    while (lst) {
		num_fields += 1;
		lst = lst->next;
    }
    return num_fields;
}


smap *decls;
smap *stack_sizes;
smap *num_args;
smap *strings;
