#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
    IDENTIFIER,
    INTEGER,
    PLUS,
    MINUS,
    SEMICOLON,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string lexeme;
};

class Lexer {
public:
    Lexer(const std::string& source) : source_(source), current_pos_(0) {}

    Token getNextToken() {
        // Skip whitespace
        while (isspace(source_[current_pos_])) {
            current_pos_++;
        }

        if (current_pos_ >= source_.size()) {
            return {TokenType::END_OF_FILE, ""};
        }

        char current_char = source_[current_pos_];
        if (isdigit(current_char)) {
            return lexNumber();
        } else if (isalpha(current_char)) {
            return lexIdentifier();
        } else {
            switch (current_char) {
                case '+':
                    current_pos_++;
                    return {TokenType::PLUS, "+"};
                case '-':
                    current_pos_++;
                    return {TokenType::MINUS, "-"};
                case ';':
                    current_pos_++;
                    return {TokenType::SEMICOLON, ";"};
                default:
                    // Handle unrecognized characters
                    std::cerr << "Error: Unexpected character '" << current_char << "'\n";
                    exit(1);
            }
        }
    }

private:
    Token lexNumber() {
        std::string number;
        while (isdigit(source_[current_pos_])) {
            number += source_[current_pos_];
            current_pos_++;
        }
        return {TokenType::INTEGER, number};
    }

    Token lexIdentifier() {
        std::string identifier;
        while (isalnum(source_[current_pos_])) {
            identifier += source_[current_pos_];
            current_pos_++;
        }
        return {TokenType::IDENTIFIER, identifier};
    }

    std::string source_;
    size_t current_pos_;
};

int main() {
    std::string source = "x = 10 + 20; y = x - 5;";
    Lexer lexer(source);
    Token token;
    do {
        token = lexer.getNextToken();
        std::cout << "Token: Type=" << static_cast<int>(token.type) << ", Lexeme='" << token.lexeme << "'\n";
    } while (token.type != TokenType::END_OF_FILE);

    return 0;
}