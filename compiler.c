#include "compiler.h" // Include the header file that contains declarations for the compiler's functions and structures

// Log messages to the log file, you might have to make the log file yourself!
void log_message(const char *message) {
    FILE *log_file = fopen(LOG_FILE, "a"); // Open the log file in append mode
    if (log_file) { // Check if the file was opened successfully
        fprintf(log_file, "%s\n", message); // Write the message to the log file
        fclose(log_file); // Close the log file
    }
}

// Tokenize the input string
Token *tokenize(const char *input, int *token_count) {
    Token *tokens = malloc(MAX_TOKENS * sizeof(Token)); // Allocate memory for tokens
    *token_count = 0; // Initialize token count to zero

    char *token = strtok(strdup(input), " "); // Split the input string into tokens using space as a delimiter
    while (token != NULL) { // Loop through each token
        // Check the type of the token and assign the appropriate TokenType
        if (strcmp(token, "MOV") == 0) {
            tokens[*token_count].type = TOKEN_MOV;
        } else if (strcmp(token, "ADD") == 0) {
            tokens[*token_count].type = TOKEN_ADD;
        } else if (strcmp(token, "SUB") == 0) {
            tokens[*token_count].type = TOKEN_SUB;
        } else if (strcmp(token, "JMP") == 0) {
            tokens[*token_count].type = TOKEN_JMP;
        } else if (strchr(token, ':')) { // Check if the token contains a label
            tokens[*token_count].type = TOKEN_LABEL;
        } else if (strncmp(token, "R", 1) == 0) { // Check if the token is a register (starts with 'R')
            tokens[*token_count].type = TOKEN_REGISTER;
        } else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) { // Check if the token is a number (including negative)
            tokens[*token_count].type = TOKEN_NUMBER;
        } else {
            tokens[*token_count].type = TOKEN_INVALID; // Mark as invalid token
            log_message("Error: Invalid token encountered."); // Log the error
        }

        strncpy(tokens[*token_count].value, token, MAX_TOKEN_LENGTH); // Copy the token value into the tokens array
        (*token_count)++; // Increment the token count
        token = strtok(NULL, " "); // Get the next token
    }

    tokens[*token_count].type = TOKEN_EOF; // Mark the end of tokens
    return tokens; // Return the array of tokens
}

// Create a new AST node for MOV
ASTNode* create_mov_node(char *dest, char *src) {
    ASTNode *node = malloc(sizeof(ASTNode)); // Allocate memory for a new AST node
    node->type = NODE_MOV; // Set the node type to MOV
    node->dest = strdup(dest); // Duplicate the destination string
    node->src = strdup(src); // Duplicate the source string
    node->next = NULL; // Initialize the next pointer to NULL
    return node; // Return the newly created node
}

// Create a new AST node for ADD
ASTNode* create_add_node(char *dest, char *src) {
    ASTNode *node = malloc(sizeof(ASTNode)); // Allocate memory for a new AST node
    node->type = NODE_ADD; // Set the node type to ADD
    node->dest = strdup(dest); // Duplicate the destination string
    node->src = strdup(src); // Duplicate the source string
    node->next = NULL; // Initialize the next pointer to NULL
    return node; // Return the newly created node
}

// Create a new AST node for SUB
ASTNode* create_sub_node(char *dest, char *src) {
    ASTNode *node = malloc(sizeof(ASTNode)); // Allocate memory for a new AST node
    node->type = NODE_SUB; // Set the node type to SUB
    node->dest = strdup(dest); // Duplicate the destination string
    node->src = strdup(src); // Duplicate the source string
    node->next = NULL; // Initialize the next pointer to NULL
    return node; // Return the newly created node
}

// Create a new AST node for JMP
ASTNode* create_jmp_node(char *label) {
    ASTNode *node = malloc(sizeof(ASTNode)); // Allocate memory for a new AST node
    node->type = NODE_JMP; // Set the node type to JMP
    node->dest = strdup(label); // Duplicate the label string
    node->src = NULL; // No source for JMP node->next = NULL; // Initialize the next pointer to NULL
    return node; // Return the newly created node
}

// Create a new AST node for LABEL
ASTNode* create_label_node(char *label) {
    ASTNode *node = malloc(sizeof(ASTNode)); // Allocate memory for a new AST node
    node->type = NODE_LABEL; // Set the node type to LABEL
    node->dest = strdup(label); // Duplicate the label string
    node->src = NULL; // No source for LABEL
    node->next = NULL; // Initialize the next pointer to NULL
    return node; // Return the newly created node
}

// Parse the tokens and build the AST
ASTNode* parse(Token *tokens, int token_count) {
    ASTNode *head = NULL; // Pointer to the head of the AST
    ASTNode *tail = NULL; // Pointer to the tail of the AST

    for (int i = 0; i < token_count; i++) { // Loop through each token
        if (tokens[i].type == TOKEN_MOV) { // If the token is a MOV instruction
            ASTNode *node = create_mov_node(tokens[i + 1].value, tokens[i + 2].value); // Create a MOV node
            if (head == NULL) { // If this is the first node
                head = node; // Set head to the new node
                tail = node; // Set tail to the new node
            } else { // If there are already nodes in the AST
                tail->next = node; // Link the new node to the end of the list
                tail = node; // Update the tail to the new node
            }
            i += 2; // Move past destination and source tokens
        } else if (tokens[i].type == TOKEN_ADD) { // If the token is an ADD instruction
            ASTNode *node = create_add_node(tokens[i + 1].value, tokens[i + 2].value); // Create an ADD node
            if (head == NULL) { // If this is the first node
                head = node; // Set head to the new node
                tail = node; // Set tail to the new node
            } else { // If there are already nodes in the AST
                tail->next = node; // Link the new node to the end of the list
                tail = node; // Update the tail to the new node
            }
            i += 2; // Move past destination and source tokens
        } else if (tokens[i].type == TOKEN_SUB) { // If the token is a SUB instruction
            ASTNode *node = create_sub_node(tokens[i + 1].value, tokens[i + 2].value); // Create a SUB node
            if (head == NULL) { // If this is the first node
                head = node; // Set head to the new node
                tail = node; // Set tail to the new node
            } else { // If there are already nodes in the AST
                tail->next = node; // Link the new node to the end of the list
                tail = node; // Update the tail to the new node
            }
            i += 2; // Move past destination and source tokens
        } else if (tokens[i].type == TOKEN_JMP) { // If the token is a JMP instruction
            ASTNode *node = create_jmp_node(tokens[i + 1].value); // Create a JMP node
            if (head == NULL) { // If this is the first node
                head = node; // Set head to the new node
                tail = node; // Set tail to the new node
            } else { // If there are already nodes in the AST
                tail->next = node; // Link the new node to the end of the list
                tail = node; // Update the tail to the new node
            }
            i++; // Move past the label token
        } else if (tokens[i].type == TOKEN_LABEL) { // If the token is a LABEL
            ASTNode *node = create_label_node(tokens[i].value); // Create a LABEL node
            if (head == NULL) { // If this is the first node
                head = node; // Set head to the new node
                tail = node; // Set tail to the new node
            } else { // If there are already nodes in the AST
                tail->next = node; // Link the new node to the end of the list
                tail = node; // Update the tail to the new node
            }
        }
    }
    return head; // Return the head of the constructed AST
}

// Print the AST
void print_ast(ASTNode *node ) {
    while (node != NULL) { // Loop through each node in the AST
        switch (node->type) { // Check the type of the current node
            case NODE_LABEL: // If the node is a LABEL
                printf("LABEL: %s\n", node->dest); // Print the label
                break;
            case NODE_MOV: // If the node is a MOV instruction
                printf("MOV %s, %s\n", node->dest, node->src); // Print the MOV instruction
                break;
            case NODE_ADD: // If the node is an ADD instruction
                printf("ADD %s, %s\n", node->dest, node->src); // Print the ADD instruction
                break;
            case NODE_SUB: // If the node is a SUB instruction
                printf("SUB %s, %s\n", node->dest, node->src); // Print the SUB instruction
                break;
            case NODE_JMP: // If the node is a JMP instruction
                printf("JMP %s\n", node->dest); // Print the JMP instruction
                break;
        }
        node = node->next; // Move to the next node in the AST
    }
}

// Free the AST
void free_ast(ASTNode *node) {
    while (node != NULL) { // Loop through each node in the AST
        ASTNode *temp = node; // Store the current node in a temporary variable
        node = node->next; // Move to the next node
        free(temp->dest); // Free the memory allocated for the destination string
        free(temp->src); // Free the memory allocated for the source string
        free(temp); // Free the memory allocated for the AST node
    }
}

// Free tokens
void free_tokens(Token *tokens, int token_count) {
    free(tokens); // Free the memory allocated for the tokens array
}

// Generate code from the AST (placeholder for actual code generation)
void generate_code(ASTNode *ast) {
    // Placeholder for code generation logic
    printf("Generating code...\n"); // Indicate that code generation is taking place
}

// Main function
int main() {
    char input[MAX_CODE_LENGTH]; // Buffer to hold user input
    int token_count; // Variable to hold the number of tokens
    Token *tokens; // Pointer to hold the array of tokens

    // Open log file
    freopen(LOG_FILE, "w", stdout); // Redirect standard output to the log file

    printf("Simple Assembly Compiler\n"); // Print the compiler's name
    printf("Enter assembly code (type 'exit' to quit):\n"); // Prompt the user for input

    while (1) { // Infinite loop to continuously accept user input
        printf("> "); // Print prompt
        fgets(input, sizeof(input), stdin); // Read a line of input from the user
        input[strcspn(input, "\n")] = 0; // Remove the newline character from the input

        if (strcmp(input, "exit") == 0) { // Check if the user wants to exit
            break; // Exit the loop
        }

        // Tokenize the input
        tokens = tokenize(input, &token_count); // Tokenize the input string
        if (tokens == NULL) { // Check if tokenization failed
            log_message("Error: Tokenization failed."); // Log the error
            continue; // Continue to the next iteration
        }

        // Parse the tokens and build the AST
        ASTNode *ast = parse(tokens, token_count); // Parse the tokens into an AST
        if (ast == NULL) { // Check if AST construction failed
            log_message("Error: AST construction failed."); // Log the error
            free_tokens(tokens, token_count); // Free the tokens
            continue; // Continue to the next iteration
        }

        // Print the AST
        print_ast(ast); // Print the constructed AST

        // Generate code from the AST
        generate_code(ast); // Generate code from the AST

        // Free the AST and tokens
        free_ast(ast); // Free the memory allocated for the AST
        free_tokens(tokens, token_count); // Free the memory allocated for the tokens
    }

    fclose(stdout); // Close the log file
    return 0; // Return success
}
