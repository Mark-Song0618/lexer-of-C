#pragma once
#include "lexer.h"
#include "fsm.h"
#include <stdio.h>

TokenType _typeTable[TOTAL_STATUS] =
{
	INVALID,
	ID,
	INVALID,
	INVALID,
	INVALID,
	BIN,
	OCT,
	HEX,
	DEC,
	PARENTHESE_LEFT,
	PARENTHESE_RIGHT,
	BRACKET_LEFT, 
	BRACKET_RIGHT,
	BRACE_LEFT,
	BRACE_RIGHT,
	ADD,
	MINUS,
	MULTI,
	DIV,
	EQUAL,
	SEMICOLON,
	INVALID,
	STR,
	INVALID,
	INVALID,
	COMMENT,
	COMMENT,
	COMMENT,
	INVALID
};

transitHandler	  _transit[TOTAL_STATUS] = { transit_start,				// ST_START
											transit_ID,					// ST_ID
											transit_BIN_OCT_HEX,		// ST_BIN_OCT_HEX
											transit_BIN_SIGN,			// ST_BIN_SIGN
											transit_HEX_SIGN,			// ST_HEX_SIGN
											transit_BIN,				// ST_BIN
											transit_OCT,				// ST_OCT
											transit_HEX,				// ST_HEX
											transit_DEC,				// ST_DEC
											transit_SINGLE_CHAR,		// ST_PARENTHESE_LEFT
											transit_SINGLE_CHAR,		// ST_PARENTHESE_RIGHT
											transit_SINGLE_CHAR,		// ST_BRACKET_LEFT
											transit_SINGLE_CHAR,		// ST_BRACKET_RIGHT
											transit_SINGLE_CHAR,		// ST_BRACE_LEFT
											transit_SINGLE_CHAR,		// ST_BRACE_RIGHT
											transit_SINGLE_CHAR,		// ST_ADD
											transit_SINGLE_CHAR,		// ST_MINUS
											transit_SINGLE_CHAR,		// ST_MULTI
											transit_SLASH,				// ST_DIV
											transit_SINGLE_CHAR,		// ST_EQU 
											transit_SINGLE_CHAR,		// ST_SEMICOLON
											transit_UNCLOSE_STR,		// ST_UNCLOSE_STR
											transit_SINGLE_CHAR,		// ST_STR
											transit_SLASH_STAR,			// ST_SLASH_STAR
											transit_SLASH_STAR_STAR,	// ST_SLASH_STAR_STAR
											transit_SINGLE_CHAR,		// ST_MULTI_LINE_COMMENT
											transit_SLASH_SLASH,		// ST_SLASH_SLASH
											transit_SINGLE_CHAR,		// ST_SINGLE_LINE_COMMENT
											NULL};						// ST_UNRECOG

bool ParseFile(const char* fileName, Token* tokens, unsigned maxToken) {
	FILE* srcFile = fopen(fileName, "r");
	if (srcFile == NULL) {
		printf("source file: %s not exist, please check the file path\r\n", fileName);
		return false;
	}

	return fsm_run(srcFile, tokens, maxToken);
}

bool isSplitter(char c)
{
	if (c == ' ') {
		return true;
	}
	if (c == '\t') {
		return true;
	}
	if (c == '\r') {
		return true;
	}
	if (c == '\n') {
		return true;
	}
	// todo:
	//		comments, like int a/*this is a comment*/.
	//		operator, like a+b
	return false;
}

bool isComment(STATUS s) {
	if (s == ST_SLASH_SLASH || s == ST_SINGLE_LINE_COMMENT || s == ST_MULTI_LINE_COMMENT) {
		return true;
	}
	return false;
}

bool isAlpha(char c)
{
	if (c >= 'a' && c <= 'z') {
		return true;
	}
	else if (c >= 'A' && c <= 'Z') {
		return true;
	}
	else {
		return false;
	}
}

bool isUnderline(char c)
{
	if (c == '_') {
		return true;
	}
	else {
		return false;
	}
}

bool isBinary(char c)
{
	if (c == '0' || c == '1') {
		return true;
	}
	else {
		return false;
	}
}

bool isOctal(char c)
{
	if (c <= '7' && c >= '0') {
		return true;
	}
	else {
		return false;
	}
}

bool isDecimal(char c)
{
	if (c <= '9' && c >= '0') {
		return true;
	}
	else {
		return false;
	}
}

bool isHexadecimal(char c)
{
	if (c >= '0' && c <= '9') {
		return true;
	}
	else if (c >= 'a' && c <= 'z') {
		return true;
	}
	else if (c >= 'A' && c <= 'Z') {
		return true;
	}
	else {
		return false;
	}
}

bool isKeyword(const char* buf)
{
	if (!strcmp(buf, "char")) {
		return CHAR;
	}
	if (!strcmp(buf, "short")) {
		return SHORT;
	}
	if (!strcmp(buf, "int")) {
		return INT;
	}
	if (!strcmp(buf, "long")) {
		return LONG;
	}
	if (!strcmp(buf, "float")) {
		return FLOAT;
	}
	if (!strcmp(buf, "double")) {
		return DOUBLE;
	}
	if (!strcmp(buf, "+")) {
		return ADD;
	}
	if (!strcmp(buf, "-")) {
		return MINUS;
	}
	if (!strcmp(buf, "*")) {
		return MULTI;
	}
	if (!strcmp(buf, "/")) {
		return DIV;
	}
	if (!strcmp(buf, "if")) {
		return IF;
	}
	if (!strcmp(buf, "else")) {
		return ELSE;
	}
	if (!strcmp(buf, "while")) {
		return WHILE;
	}
	if (!strcmp(buf, "for")) {
		return FOR;
	}
	if (!strcmp(buf, "(")) {
		return PARENTHESE_LEFT;
	}
	if (!strcmp(buf, ")")) {
		return PARENTHESE_RIGHT;
	}
	if (!strcmp(buf, "[")) {
		return BRACKET_LEFT;
	}
	if (!strcmp(buf, "]")) {
		return BRACKET_RIGHT;
	}
	if (!strcmp(buf, "{")) {
		return BRACE_LEFT;
	}
	if (!strcmp(buf, "}")) {
		return BRACE_RIGHT;
	}
	return INVALID;
}

bool isKeywordType(TokenType type)
{
	if (type == CHAR) {
		return true;
	}
	if (type == SHORT) {
		return true;
	}
	if (type == INT) {
		return true;
	}
	if (type == LONG) {
		return true;
	}
	if (type == FLOAT) {
		return true;
	}
	if (type == DOUBLE) {
		return true;
	}
	if (type == ADD) {
		return true;
	}
	if (type == MINUS) {
		return true;
	}
	if (type == MULTI) {
		return true;
	}
	if (type == DIV) {
		return true;
	}
	if (type == IF) {
		return true;
	}
	if (type == ELSE) {
		return true;
	}
	if (type == WHILE) {
		return true;
	}
	if (type == FOR) {
		return true;
	}
	if (type == PARENTHESE_LEFT) {
		return true;
	}
	if (type == PARENTHESE_RIGHT) {
		return true;
	}
	if (type == BRACKET_LEFT) {
		return true;
	}
	if (type == BRACKET_RIGHT) {
		return true;
	}
	if (type == BRACE_LEFT) {
		return true;
	}
	if (type == BRACE_RIGHT) {
		return true;
	}
	if (type == SEMICOLON) {
		return true;
	}
	return false;
}

TokenType signedType(TokenType origType)
{
	switch (origType)
	{
	case BIN:
		return SIGNED_BIN;
	case OCT:
		return SIGNED_OCT;
	case DEC:
		return SIGNED_DEC;
	case HEX:
		return SIGNED_HEX;
	default:
		return INVALID;
	}
}

STATUS transit_start(char c)
{
	if (isAlpha(c) || isUnderline(c)) {
		return ST_ID;
	}

	if (c == '0') {
		return ST_BIN_OCT_HEX;
	}

	if (c >= '1' && c <= '9') {
		return ST_DEC;
	}

	if (c == '(') {
		return ST_PARENTHESE_LEFT;
	}

	if (c == ')') {
		return ST_PARENTHESE_RIGHT;
	}
	if (c == '[') {
		return ST_BRACKET_LEFT;
	}
	if (c == ']') {
		return ST_BRACKET_RIGHT;
	}
	if (c == '{') {
		return ST_BRACE_LEFT;
	}
	if (c == '}') {
		return ST_BRACE_RIGHT;
	}
	if (c == '+') {
		return ST_ADD;
	}
	if (c == '-') {
		return ST_MINUS;
	}
	if (c == '*') {
		return ST_MULTI;
	}
	if (c == '/') {
		return ST_DIV;
	}
	if (c == '=') {
		return ST_EQU;
	}
	if (c == '"') {
		return ST_UNCLOSE_STR;
	}
	if (c == ';') {
		return ST_SEMICOLON;
	}
	return ST_UNRECOG;
}

STATUS transit_ID(char c)
{
	if (isAlpha(c) || isUnderline(c) || isDecimal(c)) {
		return ST_ID;
	}

	return ST_UNRECOG;
}

STATUS transit_DEC(char c)
{
	if (isDecimal(c)) {
		return ST_DEC;
	}

	return ST_UNRECOG;
}

STATUS transit_UNCLOSE_STR(char c)
{
	if (c == '"') {
		return ST_STR;
	}
	return ST_UNCLOSE_STR;
}


STATUS transit_BIN_OCT_HEX(char c)
{
	if (c == 'b' || c == 'B') {
		return ST_BIN_SIGN;
	}

	if (c == 'x' || c == 'X') {
		return ST_HEX_SIGN;
	}

	if (c >= '0' && c <= '7') {
		return ST_OCT;
	}

	return ST_UNRECOG;
}

STATUS transit_BIN_SIGN(char c)
{
	if (isBinary(c)) {
		return ST_BIN;
	}

	return ST_UNRECOG;
}

STATUS transit_BIN(char c)
{
	if (isBinary(c)) {
		return ST_BIN;
	}

	return ST_UNRECOG;
}


STATUS transit_HEX_SIGN(char c)
{
	if (isHexadecimal(c)) {
		return ST_HEX;
	}

	return ST_UNRECOG;
}

STATUS transit_HEX(char c)
{
	if (isHexadecimal(c)) {
		return ST_HEX;
	}

	return ST_UNRECOG;
}

STATUS transit_OCT(char c)
{
	if (isOctal(c)) {
		return ST_OCT;
	}

	return ST_UNRECOG;
}

STATUS transit_SINGLE_CHAR(char c)
{
	return ST_UNRECOG;
}

STATUS transit_SLASH(char c)
{
	if (c == '*') {
		return ST_SLASH_STAR;
	}
	if (c == '/') {
		return ST_SLASH_SLASH;
	}
	return ST_UNRECOG;
}

STATUS transit_SLASH_STAR(char c)
{
	if (c == '*') {
		return ST_SLASH_STAR_STAR;
	}
	return ST_SLASH_STAR;
}

STATUS transit_SLASH_STAR_STAR(char c)
{
	if (c == '/') {
		return ST_MULTI_LINE_COMMENT;
	}
	if (c == '*') {
		return ST_SLASH_STAR_STAR;
	}
	return ST_SLASH_STAR;
}

STATUS transit_SLASH_SLASH(char c)
{
	if (c == '\r' || c == '\n') {
		return ST_SINGLE_LINE_COMMENT;
	}
	if (c == EOF) {
		return ST_UNRECOG; // will accept recognized str as comment
	} 
	return ST_SLASH_SLASH;
}
