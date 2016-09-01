#pragma once
#ifndef _EVAL_H_

#define _EVAL_H_
#define N_OPTR 9 // ���������

// STL version
#include <stack>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdexcept>

typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; // ���������
// �ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��

const char OP_PRI[N_OPTR][N_OPTR] = { // ��������ȵȼ� [ջ��] [��ǰ]
/*              |-------------------- �� ǰ �� �� �� --------------------| */
/*              +      -      *      /      ^      !      (      )      \0 */
/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
/* ջ  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
/* ��  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
/* ��  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
/* ��  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
/* ��  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};

float read_digit(const std::string &s, std::string::size_type &idx) {
	float buffer;
	std::locale loc;
	auto last_idx = std::find_if(s.crbegin(), s.crend() - idx, isdigit);
	if (last_idx != s.crend()) {
		std::stringstream(s) >> buffer;
		idx = s.crend() - last_idx;
	} else {
		throw std::invalid_argument("Input eval is invalid: contain non-digit character.");
	}

	return buffer;
}
#endif
