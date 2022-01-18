#include <stdlib.h>
#include "Scanner.h"
#include "cmm.h"

Scanner::Scanner(string source) 
	: source{ source },
	tokens{ vector<Token>() },
	start{ 0 }, current{ 0 }, line{ 1 } {
	// keywords
	keywords["and"] = AND;
	keywords["class"] = CLASS;
	keywords["else"] = ELSE;
	keywords["false"] = FALSE;
	keywords["for"] = FOR;
	keywords["fun"] = FUN;
	keywords["if"] = IF;
	keywords["nil"] = NIL;
	keywords["or"] = OR;
	keywords["print"] = PRINT;
	keywords["return"] = RETURN;
	keywords["super"] = SUPER;
	keywords["this"] = THIS;
	keywords["true"] = TRUE;
	keywords["var"] = VAR;
	keywords["while"] = WHILE;
}

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
		if (nextChar('/'))
			while (peek() != '\n' && !isDone()) next();
		else addToken(SLASH);
		break;
	case ' ':
	case '\r':
	case '\t':
		break;
	case '\n':
		line++;
		break;
	case '"': 
		traverseString();
		addToken(STRING, source.substr(start + 1, current - 1)); 
		break;
	default:
		if (isdigit(c)) {
			traverseNumber();
			double num = atof(source.substr(start, current).c_str());
			addToken(NUMBER, num);
		} else if (isalpha(c)) {
			addIdentifier();
		} else
			error(line, "Unexpected character.");
		break;
	}
}

int Scanner::isDone() {
	return current >= (int)source.length();
}

char Scanner::next() {
	return source[current++];
}

char Scanner::peek() {
	if (isDone()) return '\0';
	return source[current];
}

char Scanner::peekNext() {
	if (current + 1 >= (int)source.length()) return '\0';
	return source[current + 1];
}

bool Scanner::nextChar(char c) {
	if (isDone()) return false;
	if (source[current] != c) return false;
	current++;
	return true;
}

void Scanner::traverseString() {
	while (peek() != '"' && !isDone()) {
		if (peek() == '\n') line++;
		next();
	}
	if (isDone()) {
		error(line, "unterminated string");
		return;
	}
	next();
}

void Scanner::traverseNumber() {
	while (isdigit(peek())) next();
	if (peek() == '.' && isdigit(peekNext())) {
		next();
		while (isdigit(peek())) next();
	}
}

void Scanner::addIdentifier() {
	while (isalnum(peek())) next();
	string id = source.substr(start, current);
	if (keywords.find(id) == keywords.end()) {
		// not keyword => must be identifier
		addToken(IDENTIFIER);
		return;
	} // keyword
	addToken(keywords[id]);
}

void Scanner::addToken(tokenType type, Literal lit) {
	string lexeme = source.substr(start, current);
	tokens.push_back(Token(type, lexeme, lit, line));
}
