#include "Scanner.h"

Scanner::Scanner(string source) 
	: source{ source },
	tokens{ vector<Token>() },
	start{ 0 }, current{ 0 }, line{ 1 } {}

vector<Token> Scanner::scanTokens() {
	while (!isDone()) {
		start = current;
		scanToken();
	}
	tokens.push_back(Token(EoF, "", NULL, line));
	return tokens;
}

void Scanner::scanToken() {
	char c = next();
	switch (c) {
	case '(': addToken(LEFT_PAREN); break;
	case ')': addToken(RIGHT_PAREN); break;
	case '{': addToken(LEFT_BRACE); break;
	case '}': addToken(RIGHT_BRACE); break;
	case ',': addToken(COMMA); break;
	case '.': addToken(DOT); break;
	case '-': addToken(MINUS); break;
	case '+': addToken(PLUS); break;
	case ';': addToken(SEMICOLON); break;
	case '*': addToken(STAR); break;
	case '!':
		addToken(nextChar('=') ? BANG_EQUAL : BANG);
		break;
	case '=':
		addToken(nextChar('=') ? EQUAL_EQUAL : EQUAL);
		break;
	case '<':
		addToken(nextChar('=') ? LESS_EQUAL : LESS);
		break;
	case '>':
		addToken(nextChar('=') ? GREATER_EQUAL : GREATER);
		break;
	case '/':
		if (nextChar('/')) {
			// A comment goes until the end of the line.
			while (peek() != '\n' && !isDone()) next();
		}
		else {
			addToken(SLASH);
		}
		break;
	case ' ':
	case '\r':
	case '\t':
		break;
	case '\n':
		line++;
		break;
	default:
		error(line, "Unexpected character.");
		break;
	}
}

int Scanner::isDone() {
	return current >= source.length();
}

char Scanner::next() {
	return source[current++];
}

char Scanner::peek() {
	if (isDone) return '\0';
	return source[current];
}

bool Scanner::nextChar(char c) {
	if (isDone()) return false;
	if (source[current] != c) return false;
	current++;
	return true;
}

void Scanner::addToken(tokenType type, string literal = NULL) {
	string lexeme = source.substr(start, current);
	tokens.push_back(Token(type, lexeme, literal, line));
}