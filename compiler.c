#include "compiler.h" // Contains the main logic of the compiler, including tokenization, parsing, AST construction, and code generation.

// Log messages to the log file
void log_message(const char *message) {
    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file) {
        fprintf(log_file, "%s\n", message);
        fclose(log_file);
    }
}

// Tokenize the input string
Token *tokenize(const char *input, int *token_count) {
    Token *tokens = malloc(MAX_TOKENS * sizeof(Token));
    *token_count = 0;

    char *token = strtok(strdup(input), " ");
    while (token != NULL) {
        if (strcmp(token, "MOV") == 0) {
            tokens[*token_count].type = TOKEN_MOV;
        } else if (strcmp(token, "ADD") == 0) {
            tokens[*token_count].type = TOKEN_ADD;
        } else if (strcmp(token, "SUB") == 0) {
            tokens[*token_count].type = TOKEN_SUB;
        } else if (strcmp(token, "JMP") == 0) {
            tokens[*token_count].type = TOKEN_JMP;
        } else if (strchr(token, ':')) {
            tokens[*token_count].type = TOKEN_LABEL;
        } else if (strncmp(token, "R", 1) == 0) {
            tokens[*token_count].type = TOKEN_REGISTER;
        } else if (isdigit(token[0])) {
            tokens[*token_count].type = TOKEN_NUMBER;
        } else {
            tokens[*token_count].type = TOKEN_INVALID;
            log_message("Error: Invalid token encountered.");
        }

        strncpy(tokens[*token_count].value, token, MAX_TOKEN_LENGTH);
        (*token_count)++;
        token = strtok(NULL, " ");
    }

    tokens[*token_count].type = TOKEN_EOF; // End of tokens
    return tokens;
}

// Create a new AST node for MOV
ASTNode* create_mov_node(char *dest, char *src) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_MOV;
    node->dest = strdup(dest);
    node->src = strdup(src);
    node->next = NULL;
    return node;
}

// Create a new AST node for ADD
ASTNode* create_add_node(char *dest, char *src) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_ADD;
    node->dest = strdup(dest);
    node->src = strdup(src);
    node->next = NULL;
    return node;
}

// Create a new AST node for SUB
ASTNode* create_sub_node(char *dest, char *src) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_SUB;
    node->dest = strdup(dest);
    node->src = strdup(src);
    node->next = NULL;
    return node;
}

// Create a new AST node for JMP
ASTNode* create_jmp_node(char *label) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_JMP;
    node->dest = strdup(label);
    node->src = NULL;
    node->next = NULL;
    return node;
}

// Create a new AST node for LABEL
ASTNode* create_label_node(char *label) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_LABEL;
    node->dest = strdup(label);
    node->src = NULL;
    node->next = NULL;
    return node;
}

// Parse the tokens and build the AST
ASTNode* parse(Token *tokens, int token_count) {
    ASTNode *head = NULL;
    ASTNode *tail = NULL;

    for (int i = 0; i < token_count; i++) {
        if (tokens[i].type == TOKEN_MOV) {
            ASTNode *node = create_mov_node(tokens[i + 1].value, tokens[i + 2].value);
            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
            i += 2; // Move past dest and src
        } else if (tokens[i].type == TOKEN_ADD) {
            ASTNode *node = create_add_node(tokens[i + 1].value, tokens[i + 2].value);
            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
            i += 2; // Move past dest and src
        } else if (tokens[i].type == TOKEN_SUB) {
            ASTNode *node = create_sub_node(tokens[i + 1].value, tokens[i + 2].value);
            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
            i += 2; // Move past dest and src
        } else if (tokens[i].type == TOKEN_JMP) {
            ASTNode *node = create_jmp_node(tokens[i + 1].value);
            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
            i++; // Move past label
        } else if (tokens[i].type == TOKEN_LABEL) {
            ASTNode *node = create_label_node(tokens[i].value);
            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
    }
    return head; // Return the head of the AST
}

// Print the AST
void print_ast(ASTNode *node) {
    while (node != NULL) {
        switch (node->type) {
            case NODE_LABEL:
                printf("LABEL: %s\n", node->dest);
                break;
            case NODE_MOV:
                printf("MOV %s, %s\n", node->dest, node->src);
                break;
            case NODE_ADD:
                printf("ADD %s, %s\n", node->dest, node->src);
                break;
            case NODE_SUB:
                printf("SUB %s, %s\n", node->dest, node->src);
                break;
            case NODE_JMP:
                printf("JMP %s\n", node->dest);
                break;
        }
        node = node->next;
    }
}

// Free the AST
void free_ast(ASTNode *node) {
    while (node != NULL) {
        ASTNode *temp = node;
        node = node->next;
        free(temp->dest);
        free(temp->src);
        free(temp);
    }
}

// Free tokens
void free_tokens(Token *tokens, int token_count) {
    free(tokens);
}

// Generate code from the AST (placeholder for actual code generation)
void generate_code(ASTNode *ast) {
    // Placeholder for code generation logic
    printf("Generating code...\n");
}

// Main function
int main() {
    char input[MAX_CODE_LENGTH];
    int token_count;
    Token *tokens;

    // Open log file
    freopen(LOG_FILE, "w", stdout);

    printf("Simple Assembly Compiler\n");
    printf("Enter assembly code (type 'exit' to quit):\n");

    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline

        if (strcmp(input, "exit") == 0) {
            break;
 }

        // Tokenize the input
        tokens = tokenize(input, &token_count);
        if (tokens == NULL) {
            log_message("Error: Tokenization failed.");
            continue;
        }

        // Parse the tokens and build the AST
        ASTNode *ast = parse(tokens, token_count);
        if (ast == NULL) {
            log_message("Error: AST construction failed.");
            free_tokens(tokens, token_count);
            continue;
        }

        // Print the AST
        print_ast(ast);

        // Generate code from the AST
        generate_code(ast);

        // Free the AST and tokens
        free_ast(ast);
        free_tokens(tokens, token_count);
    }

    fclose(stdout);
    return 0;
}
