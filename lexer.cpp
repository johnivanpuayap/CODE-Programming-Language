#include <string>
#include <iostream>

enum class TokenType {
    BEGIN_CODE,
    END_CODE,
    IDENTIFIER,
    INTEGER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    EQUAL,
    ASSIGN,
    PARENTHESES,
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

        if (source_.substr(current_pos_, 10) == "BEGIN CODE") {
            current_pos_ += 10;
            return {TokenType::BEGIN_CODE, "BEGIN CODE"};
        }
            
        
        if(source_.substr(current_pos_, 8) == "END CODE") {
            current_pos_ += 8;
            return {TokenType::END_CODE, "END CODE"};
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
                case '*':
                    current_pos_++;
                    return {TokenType::MULTIPLY, "*"};
                case '/':
                    current_pos_++;
                    return {TokenType::DIVIDE, "/"};
                case '=':
                    current_pos_++;
                    if(source_[current_pos_] == '=') {
                        current_pos_++;
                        return {TokenType::EQUAL, "=="};
                    } else {
                        return {TokenType::ASSIGN, "="};
                    }

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