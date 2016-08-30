#pragma once
#ifndef _STACK_H_
#define _STACK_H_

#ifndef _OJ_
#include "..\OJ-PA1-Range\Vector.h"
#include "..\OJ-PA2-Zuma\List.h"
#endif // !_OJ_

#ifdef _OJ_
#include "Vector.h"
#include "List.h"
#endif // !_OJ_

template <typename T> class Stack {
public:
	Stack() {};
	~Stack() {};
	// Functions: read only
	T &top() { return _data[_data.size()]; }
	Rank size() { return _data.size(); }
	// Functions: write or delete
	void push_back(const T &e) { _data.push_back(e); }
	T &pop() { return _data.remove_back(); }

private:
	Vector<T> _data;
};

template <typename T> class Queene {
public:
	Queene() {};
	~Queene() {};
	// Functions: write or delete
	void push_back(const T &e) { _data.push_back(e); }
	T pop() { return _data.pop(); }

private:
	List<T> _data;
};

#endif // !_STACK_H_
