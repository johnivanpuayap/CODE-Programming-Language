#include "Lexer.cpp"
#include <iostream>

int main() {
    std::string source = "BEGIN CODE x = 10 + BEGIN CODE 20 y = x - 5 END CODE";
    
    Lexer lexer(source);
    
    Token token;
    
    do {
        token = lexer.getNextToken();
        std::cout << "Token: Type=" << static_cast<int>(token.type) << ", Lexeme='" << token.lexeme << "'\n";
    } while (token.type != TokenType::END_OF_FILE);

    // Pass the lexer to the parser
    // Parse parser(lexer);
    // Parser should return a parse_tree
    // Parser.parse();

    // Perform Syntax Analysis
    // semantic_analysis(parse_tree);
    
    return 0;
}