// This header file contains the declarations for the compiler. This file also includes comments for every line to explain what its for!
#ifndef COMPILER_H // Start of include guard to prevent multiple inclusions of this header file
#define COMPILER_H // Define the header file name

#include <stdio.h> // Include standard input/output library for printf, etc.
#include <stdlib.h> // Include standard library for memory allocation and other utilities
#include <string.h> // Include string manipulation functions
#include <ctype.h> // Include character type functions (e.g., isdigit)

// Define constants for maximum tokens and token lengths
#define MAX_TOKENS 100 // Maximum number of tokens that can be processed
#define MAX_TOKEN_LENGTH 20 // Maximum length of each token
#define LOG_FILE "compiler.log" // Name of the log file for logging messages
#define MAX_CODE_LENGTH 256 // Maximum length of the code line to be processed

// Enumeration for different token types
typedef enum {
    TOKEN_LABEL, // Represents a label token
    TOKEN_MOV, // Represents a MOV instruction token
    TOKEN_ADD, // Represents an ADD instruction token
    TOKEN_SUB, // Represents a SUB instruction token
    TOKEN_JMP, // Represents a JMP instruction token
    TOKEN_REGISTER, // Represents a register token
    TOKEN_NUMBER, // Represents a numeric value token
    TOKEN_INVALID, // Represents an invalid token
    TOKEN_EOF // Represents the end of file token
} TokenType; // Define the TokenType enumeration

// Structure to represent a token
typedef struct {
    TokenType type; // The type of the token (from TokenType enum)
    char value[MAX_TOKEN_LENGTH]; // The string value of the token
} Token; // Define the Token structure

// Enumeration for different AST (Abstract Syntax Tree) node types
typedef enum {
    NODE_LABEL, // Represents a label node in the AST
    NODE_MOV, // Represents a MOV node in the AST
    NODE_ADD, // Represents an ADD node in the AST
    NODE_SUB, // Represents a SUB node in the AST
    NODE_JMP // Represents a JMP node in the AST
} NodeType; // Define the NodeType enumeration

// Structure to represent a node in the AST
typedef struct ASTNode {
    NodeType type; // The type of the AST node (from NodeType enum)
    char *dest; // Pointer to the destination register or label
    char *src; // Pointer to the source register or label
    struct ASTNode *next; // Pointer to the next node in the list (for linked list structure)
} ASTNode; // Define the ASTNode structure

// Function prototypes for the compiler's functionality
void log_message(const char *message); // Function to log messages to a file
Token *tokenize(const char *input, int *token_count); // Function to tokenize input string into tokens
ASTNode* parse(Token *tokens, int token_count); // Function to parse tokens into an AST
void generate_code(ASTNode *ast); // Function to generate code from the AST
void free_tokens(Token *tokens, int token_count); // Function to free memory allocated for tokens
void free_ast(ASTNode *node); // Function to free memory allocated for the AST nodes

#endif // End of include guard for COMPILER_H
