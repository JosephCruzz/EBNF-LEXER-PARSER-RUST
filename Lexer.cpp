#include "Lexer.h"
#include <algorithm>

std::vector<Token> Lexer::tokenize(std::string& sourcecode)
{
    std::vector<Token> tokens;
    std::vector<std::string> src = splitString(sourcecode);

    // One map to rule them all (Keywords + Operators + Delimiters)
    static const std::unordered_map<std::string, TokenType> tokenLookup =
    {
        // palabras clave
        {"use",   TokenType::USE},
        {"fn",    TokenType::FN},
        {"let",   TokenType::LET},
        {"mut",   TokenType::MUT},
        {"while", TokenType::WHILE},
        {"for",   TokenType::FOR},
        {"move",  TokenType::MOVE},

        // operadores
        {"::",    TokenType::DOUBLE_COLON},
        {"..",    TokenType::DOUBLE_DOT},
        {"-=",    TokenType::SUB_EQUALS},
        {"=",     TokenType::EQUALS},
        {">",     TokenType::GREATER_THAN},
        {"&",     TokenType::AMPERSAND},
        {"!",     TokenType::BANG},

        // Delimiters
        {"(",     TokenType::OPEN_PAREN},
        {")",     TokenType::CLOSE_PAREN},
        {"{",     TokenType::OPEN_BRACE},
        {"}",     TokenType::CLOSE_BRACE},
        {"[",     TokenType::OPEN_BRACKET},
        {"]",     TokenType::CLOSE_BRACKET},
        {";",     TokenType::SEMICOLON},
        {",",     TokenType::COMMA},
        {".",     TokenType::DOT},
        {":",     TokenType::COLON}
    };

    for (const std::string& word : src)
    {
        Token token;
        token.lexeme = word;

        // 1. Check the map for Keywords, Operators, and Delimiters
        auto match = tokenLookup.find(word);
        if (match != tokenLookup.end())
        {
            token.type = match->second;
        }
        // 2. Dynamic Check: String literals (Cannot go in the map)
        else if (word.size() >= 2 && word.front() == '"' && word.back() == '"')
        {
            token.type = TokenType::STRING;
        }
        // 3. Dynamic Check: Numbers (Cannot go in the map)
        else if (!word.empty() && std::all_of(word.begin(), word.end(), [](unsigned char c) { return std::isdigit(c); }))
        {
            token.type = TokenType::NUMBER;
        }
        // 4. Fallback: Identifiers / Variable names (Cannot go in the map)
        else
        {
            token.type = TokenType::IDENTIFIER;
        }

        tokens.push_back(token);
    }

    return tokens;
}


std::vector<std::string> Lexer::splitString(const std::string& source)
{
    std::vector<std::string> result;
    std::string current;

    for (size_t i = 0; i < source.size(); i++)
    {
        char c = source[i];

        // ::
        if (c == ':' && i + 1 < source.size() && source[i + 1] == ':')
        {
            if (!current.empty())
            {
                result.push_back(current);
                current.clear();
            }

            result.push_back("::");
            i++;
            continue;
        }

        // ..
        if (c == '.' && i + 1 < source.size() && source[i + 1] == '.')
        {
            if (!current.empty())
            {
                result.push_back(current);
                current.clear();
            }

            result.push_back("..");
            i++;
            continue;
        }

        // String literal
        if (c == '"')
        {
            if (!current.empty())
            {
                result.push_back(current);
                current.clear();
            }

            std::string str;
            str += c; // opening quote

            i++;

            while (i < source.size())
            {
                str += source[i];

                if (source[i] == '"')
                    break;

                i++;
            }

            result.push_back(str);
            continue;
        }

        // Whitespace
        if (isspace(static_cast<unsigned char>(c)))
        {
            if (!current.empty())
            {
                result.push_back(current);
                current.clear();
            }

            continue;
        }

        // Single-character symbols
        if (
            c == '(' || c == ')' ||
            c == '{' || c == '}' ||
            c == '[' || c == ']' ||
            c == ';' || c == ',' ||
            c == '=' || c == '!' ||
            c == '&' || c == '>' ||
            c == '.' || c == ':' ||
            c == '+' || c == '-' ||
            c == '*' || c == '/'
        )
        {
            if (!current.empty())
            {
                result.push_back(current);
                current.clear();
            }

            result.push_back(std::string(1, c));
            continue;
        }

        current += c;
    }

    if (!current.empty())
    {
        result.push_back(current);
    }

    return result;
}