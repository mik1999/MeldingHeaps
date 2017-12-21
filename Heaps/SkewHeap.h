#pragma once
#include <assert.h>
#include "BasicLHeap.h"

template <typename T>
struct BasicLNode {
	BasicLNode();
	BasicLNode(const T& key);
	BasicLNode<T> * left_, *right_;
	T key_;
	unsigned int rank_;
	const T& key() const {
		return key_;
	}
	int rank() const {
		return rank_;
	}
	~BasicLNode();
};

template <typename T>
BasicLNode<T>::BasicLNode() {
}

template <typename T>
BasicLNode<T>::~BasicLNode() {
}

template <typename T>
BasicLNode<T>::BasicLNode(const T& key) : key_(key) {
	left_ = right_ = nullptr;
}

template <typename T>
class MeldSkewHeapAlg {
public:
	static bool swapPredicate(BasicLNode<T>* node1, BasicLNode<T>* node2) {
		return true;
	}
	static void renew(BasicLNode<T>* node1) {
		//do nothing
	}
};

template <typename T>
class SkewHeap :
	public BasicLHeap <BasicLNode<T>, T, MeldSkewHeapAlg<T> >
{
public:
	SkewHeap();
	SkewHeap(const T& key);
	virtual BasicLHeap <BasicLNode<T>, T, MeldSkewHeapAlg<T> >* create();
	~SkewHeap();
};

template <typename T>
SkewHeap<T>::SkewHeap()
{
}

template <typename T>
SkewHeap<T>::SkewHeap(const T& key):BasicLHeap <BasicLNode<T>, T, MeldSkewHeapAlg<T> >(key) {
}

template <typename T>
SkewHeap<T>::~SkewHeap()
{
}

template <typename T>
BasicLHeap <BasicLNode<T>, T, MeldSkewHeapAlg<T> >* SkewHeap<T>::create() {
	SkewHeap<T>* heap = new SkewHeap<T>();
	return heap;
}
