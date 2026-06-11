#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

enum class TokenType {
    // Literales
    NUMBER,
    STRING,

    // Identificadores
    IDENTIFIER,

    // Keywords
    USE,
    FN,
    LET,
    MUT,
    WHILE,
    FOR,
    MOVE,

    // Operadores
    EQUALS,
    GREATER_THAN,
    DOUBLE_DOT,
    AMPERSAND,
    BANG,
    OR_OR,
    MINUS_EQUALS,
    SUB_EQUALS,

    // Separadores
    DOT,
    COMMA,
    SEMICOLON,
    COLON,
    DOUBLE_COLON,

    // Delimitadores
    OPEN_PAREN,
    CLOSE_PAREN,
    OPEN_BRACE,
    CLOSE_BRACE,
    OPEN_BRACKET,
    CLOSE_BRACKET,

    // Comentarios
    LINE_COMMENT,
    BLOCK_COMMENT,

    EOF_TOKEN
};

struct Token {
    std::string lexeme;
    TokenType type;
};


class Lexer {
private:

public:

std::vector<Token> tokenize(std::string& sourcecode);
std::vector<std::string> splitString(const std::string& sourcecode);
};