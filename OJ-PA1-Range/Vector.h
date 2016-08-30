#pragma once
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

typedef int Rank;
const int DEFAULT_CAPACITY = 10;

/*! \brief My own Vecor Class */
template <typename T> class Vector {
protected:
	Rank _size;
	int _capacity;
	T *_elem;
	/*! \brief declaration of Protected Functions */
	void expand();
	void merge(Rank lo, Rank mi, Rank hi);

public:
	/*! \brief constructors */
	Vector(int capacity = DEFAULT_CAPACITY, int size = 0, T elem = 0) {
		_elem = new T[_capacity = capacity];
		for (_size = 0; _size < size; _elem[_size++] = elem);
	}
	/*! \brief Destructor */
	~Vector() { delete[] _elem; }

	/*! \brief Functions Read only */
	Rank search(const T &) const;
	Rank size() { return _size; }
	void print_all() {
		for (int i = 0; i < _size; ++i)
			std::cout << _elem[i] << std::endl;
	}
	void sort(Rank lo, Rank hi);

	/*! \brief Functions to Write & Read */
	T& operator [] (Rank idx) const;
	Rank insert(const T &, const Rank);
	Rank push_back(const T &);
	T& remove_back();
};

/*! \brief definitions of Protected Functions */
template <typename T> void Vector<T>::expand() {
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	// alloc new space and copy old elements
	T *old_elem = _elem;
	_elem = new T[_capacity * 2];
	for (int idx = 0; idx < _capacity; ++idx) {
		_elem[idx] = old_elem[idx];
	}
	delete[] old_elem;
}

template <typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	T *A = _elem + lo;  // A[0, hi - lo) == _elem[lo, hi)
	Rank lb = mi - lo;
	T *B = new T[lb];  // B[0, lb) == _elem[lo, mi)
	for (Rank idx = 0; idx < lb; B[idx] = A[idx++]);
	Rank lc = hi - mi;
	T *C = _elem + lc;  // C[0, lc) == _elem[mi, hi)
	// append min(B[j], C[k]) to A[i]
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); ) {
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
			A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (C[k] <= B[j])))
			A[i++] = C[k++];
	}
	delete[]B;
}

/*! \brief Functions Read only */
template <typename T> Rank Vector<T>::search(const T & elem) const {
	Rank middle, low = 0, high = _size;
	while (low < high) {
		middle = (low + high) / 2;
		if (elem < _elem[middle]) {
			high = middle;
		} else {
			low = middle + 1;
		}
	}
	return --low;
}

template <typename T> void Vector<T>::sort(Rank lo, Rank hi) {
	if (hi - lo < 2)
		return;
	Rank mi = (hi + lo) / 2;
	sort(lo, mi);
	sort(mi, hi);
	merge(lo, mi, hi);
}

/*! \brief Functions to Write & Read */
template <typename T> T& Vector<T>::operator [] (Rank idx) const {
	return _elem[(idx < _size)? idx : (_size - 1)];
}

template <typename T> Rank Vector<T>::insert(const T & elem, const Rank rank_insert) {
	Rank idx_end = _size++;  // _elem[idx_end] don't exist
	expand();
	while ( rank_insert < idx_end ) {
		_elem[idx_end] = _elem[idx_end - 1];
		--idx_end;
	}
	_elem[idx_end] = elem;
	return idx_end;
}

template <typename T> Rank Vector<T>::push_back(const T & elem) {
	return insert(elem, _size);
}

template <typename T> T& Vector<T>::remove_back() {
	return _elem[_size--];
}

#endif // !_VECTOR_H_
