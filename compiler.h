// Comments are added to show how everything works, comments are generated using AI because im to lazy to do it myself
#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 20
#define LOG_FILE "compiler.log"
#define MAX_CODE_LENGTH 256

// Token types
typedef enum {
    TOKEN_LABEL,
    TOKEN_MOV,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_JMP,
    TOKEN_REGISTER,
    TOKEN_NUMBER,
    TOKEN_INVALID,
    TOKEN_EOF
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

// AST Node Types
typedef enum {
    NODE_LABEL,
    NODE_MOV,
    NODE_ADD,
    NODE_SUB,
    NODE_JMP
} NodeType;

// AST Node Structure
typedef struct ASTNode {
    NodeType type;
    char *dest; // Destination register or label
    char *src;  // Source register or label
    struct ASTNode *next; // Pointer to the next node (for lists)
} ASTNode;

// Function prototypes
void log_message(const char *message);
Token *tokenize(const char *input, int *token_count);
ASTNode* parse(Token *tokens, int token_count);
void generate_code(ASTNode *ast);
void free_tokens(Token *tokens, int token_count);
void free_ast(ASTNode *node);

#endif // COMPILER_H
