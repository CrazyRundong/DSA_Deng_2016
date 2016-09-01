#pragma once
#ifndef _EVAL_H_

#define _EVAL_H_
#define N_OPTR 9 // 运算符总数

// STL version
#include <stack>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <stdexcept>
#include <cmath>

typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; // 运算符集合
// 加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

const std::map<Operator, char> OP_TO_CHAR = { {ADD, '+'}, {SUB,'-'}, {MUL, '*'}, {DIV, '/'},
	{POW, '^'}, {FAC, '!'}, {L_P, '('}, {R_P, ')'}, {EOE, '\0'} };

const char OP_PRI[N_OPTR][N_OPTR] = { // 运算符优先等级 [栈顶] [当前]
/*              |-------------------- 当 前 运 算 符 --------------------| */
/*              +      -      *      /      ^      !      (      )      \0 */
/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
/* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
/* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
/* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
/* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
/* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};

float read_digit(const std::string &s, std::string::size_type &idx) {
	float buffer;
	auto last_idx = std::find_if(s.crbegin(), s.crend() - idx, isdigit);
	if (last_idx != s.crend()) {
		std::stringstream(s) >> buffer;
		idx = s.crend() - last_idx;
	} else {
		throw std::invalid_argument("Invalid eval input: contain non-digit character.");
	}

	return buffer;
}

size_t op_to_idx(const Operator op) {
	switch (op) {
	case(ADD):
		return 0;
	case(SUB):
		return 1;
	case(MUL):
		return 2;
	case(DIV):
		return 3;
	case(POW):
		return 4;
	case(FAC):
		return 5;
	case(L_P):
		return 6;
	case(R_P):
		return 7;
	case(EOE):
		return 8;
	default:
		throw std::invalid_argument("Invalid Operator input: no such a operator.");
		break;
	}
}

Operator char_to_op(const char c) {
	switch (c) {
	case('+'):
		return ADD;
	case('-'):
		return SUB;
	case('*'):
		return MUL;
	case('/'):
		return DIV;
	case('^'):
		return POW;
	case('!'):
		return FAC;
	case('('):
		return L_P;
	case(')'):
		return R_P;
	case('\0'):
		return EOE;
	default:
		throw std::invalid_argument("Invalid Operator input: no such a operator.");
		break;
	}
}

const char order_between(const Operator op1, const Operator op2) {
	return OP_PRI[op_to_idx(op1)][op_to_idx(op2)];
}

float eval(const std::string &s, std::string &RPN) {
	std::stack<Operator> stackOp;
	std::stack<float> stackNum;
	float opNumBuffer;
	char opOrderBuffer;

	stackOp.push(EOE);
	size_t eval_idx = 0;
	while(eval_idx <= s.size() && stackOp.size() != 0) {
		if (isdigit(s[eval_idx])) {  // current char starts a operand
			opNumBuffer = read_digit(s, eval_idx);
			stackNum.push(opNumBuffer);
			RPN.append(std::to_string(opNumBuffer));
		} else {  // it's a operator
			Operator op_buffer = stackOp.top();
			switch (opOrderBuffer = order_between(op_buffer, char_to_op(s[eval_idx]))) {
			case('<'):
				stackOp.push(char_to_op(s[eval_idx]));
				++eval_idx;
				break;
			case('='):
				stackOp.pop();
				++eval_idx;
				break;
			case('>'):
				// Operator op_buffer = stackOp.top();  
				stackOp.pop();
				RPN.append(std::to_string(OP_TO_CHAR.at(op_buffer)));
				if (op_buffer == FAC) {  // operator: !
					float result_buffer = 1.0, op_num_0 = stackNum.top();
					stackNum.pop();
					if (op_num_0 != 0.0)
						while (op_num_0 > 1.0)
							result_buffer *= op_num_0--;
					stackNum.push(result_buffer);
				} else {  // binary operator
					float result_buffer = 1.0, op_num_1 = stackNum.top();
					stackNum.pop();
					float op_num_0 = stackNum.top();
					stackNum.pop();
					switch (op_buffer) {
					case(ADD):
						result_buffer = op_num_0 + op_num_1;
						break;
					case(SUB):
						result_buffer = op_num_0 - op_num_1;
						break;
					case(MUL):
						result_buffer = op_num_0 * op_num_1;
						break;
					case(DIV):
						result_buffer = op_num_0 / op_num_1;
						break;
					case(POW):
						result_buffer = pow(op_num_0, op_num_1);
						break;
					default:
						break;
					}
					stackNum.push(result_buffer);
				}
				break;
			default:
				throw std::invalid_argument("Invalid eval input: something wrong in this eval.");
				break;
			}
		}
	}
	return stackNum.top();
}

#endif
