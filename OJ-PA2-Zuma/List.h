#pragma once
#ifndef _LIST_H_
#define _LIST_H_
#include <iostream>

/**********************************
 *       Struct: ListNode         *
 **********************************/
#define ListNodePosi(T) ListNode<T>*
typedef int Rank;

// template <typename T> typedef ListNode<T>* ListNodePosi;

template <typename T> struct ListNode {
	T _data;
	ListNodePosi(T) _pred;
	ListNodePosi(T) _succ;
	// Constructor:
	ListNode() {}
	ListNode(T const &data, ListNodePosi(T) pred = NULL, ListNodePosi(T) succ = NULL):
		_data(data), _pred(pred), _succ(succ) { }
	ListNodePosi(T) insertAsPred(T const &e);
	ListNodePosi(T) insertAsSucc(T const &e);
};

template <typename T> ListNodePosi(T) ListNode<T>::insertAsPred(T const &e) {
	ListNodePosi(T) x = new ListNode(e, _pred, this);
	_pred->_succ = x;
	_pred = x;
	return x;
}

template <typename T> ListNodePosi(T) ListNode<T>::insertAsSucc(T const &e) {
	ListNodePosi(T) x = new ListNode(e, this, _succ);
	_succ->_pred = x;
	_succ = x;
	return x;
}


/**********************************
 *           Class: List           *
 **********************************/
template <typename T> class List {
private:
	int _size; ListNodePosi(T) _header; ListNodePosi(T) _trailer;
	// functions:
	void remove(ListNodePosi(T) p);
	bool valid(ListNodePosi(T) p) {
		return p && (_trailer != p) && (_header != p);
	}
public:
	List();
	~List();
	void de3duplicate(ListNodePosi(T) p);
	ListNodePosi(T) insert(T const &e, Rank const idx);
	ListNodePosi(T) push_back(T const &e);
	T pop();
	void show_result();
};

template <typename T> List<T>::List() {
	_header = new ListNode<T>;  _trailer = new ListNode<T>;
	_header->_succ = _trailer;  _header->_pred = NULL;
	_trailer->_pred = _header;  _trailer->_succ = NULL;
	_size = 0;
}

template <typename T> List<T>::~List() {
	ListNodePosi(T) opPtr = _trailer->_pred;
	while (opPtr != _header) {
		remove(opPtr);
		opPtr = _trailer->_pred;
	}
	delete this->_trailer;
	delete this->_header;
}

template <typename T> void List<T>::remove(ListNodePosi(T) p) {
	if (!valid(p)) return;
	p->_pred->_succ = p->_succ;
	p->_succ->_pred = p->_pred;
	delete p;
	--_size;
}

template <typename T> ListNodePosi(T) List<T>::push_back(T const &e) {
	++_size;
	return _trailer->insertAsPred(e);
}

template <typename T> T List<T>::pop() {
	T elem_backup = _header->_succ->_data;
	remove(_header->_succ);
	return elem_backup;
}

template <typename T> ListNodePosi(T) List<T>::insert(T const &e, Rank const idx) {
	if (idx > _size) return _trailer;
	ListNodePosi(T) opPtr = _header;
	for (int i = 0; i < idx; ++i)
		opPtr = opPtr->_succ;
	++_size;
	return opPtr->insertAsSucc(e);
}

template <typename T> void List<T>::de3duplicate(ListNodePosi(T) p) {
	if (_size < 3) return;
	ListNodePosi(T) b = p->_pred; ListNodePosi(T) e = p->_succ;
	int same_count = 1;
	// search pred:
	while (b != _header && ((p->_data) == (b->_data)) && same_count < 3) {
		++same_count;
		b = b->_pred;
	}
	// search succ:
	while (e != _trailer && ((p->_data) == (e->_data)) && same_count < 3) {
		++same_count;
		e = e->_succ;
	}
	// check if need remove Node:
	if (same_count < 3)
		// std::cout << "no repeat." << std::endl;
		return;
	else {
		while (same_count != 0) {
			remove(b->_succ);
			--same_count;
		}
		de3duplicate(b);
	}
}

template <typename T> void List<T>::show_result() {
	if (_size == 0)
		std::cout << "-" << std::endl;
	else {
		ListNodePosi(T) opPtr = _header;
		while (opPtr->_succ != _trailer) {
			std::cout << opPtr->_succ->_data;
			opPtr = opPtr->_succ;
		}
		std::cout << std::endl;
	}
}

#endif // !_LIST_H_
