#pragma once
#include "BasicLHeap.h"

template <typename T>
class LeftistNode{
public:
	LeftistNode();
	LeftistNode(const T& key);
	LeftistNode<T> * left_, *right_;
	T key_;
	unsigned int rank_;
	const T& key() const{
		return key_;
	}
	int rank() const {
		return rank_;
	}
};

template <typename T>
int rank(LeftistNode <T>* node) {
	return (node == nullptr) ? 0 : node->rank();
}


template <typename T>
class MeldLeftistHeapAlg {
public:
	static bool swapPredicate(LeftistNode<T>* node1, LeftistNode<T>* node2) {
		LeftistNode <T>* lnode1 = static_cast <LeftistNode <T>*>(node1);
		LeftistNode <T>* lnode2 = static_cast <LeftistNode <T>*>(node2);
		return ::rank(node1) < ::rank(node2);
	}
	static void renew(LeftistNode<T>* node) {
		if (!node)
			return;
		node->rank_ = min(::rank<T>(node->left_), ::rank<T>(node->right_)) + 1;
	}
};

template <typename T>
LeftistNode<T>::LeftistNode() {}

template <typename T>
LeftistNode<T>::LeftistNode(const T& key) : key_(key) {
	rank_ = 0;
	left_ = right_ = nullptr;
}

template <typename T>
class LeftistHeap :
	public BasicLHeap <LeftistNode<T>, T, MeldLeftistHeapAlg<T> >
{
public:
	LeftistHeap();
	LeftistHeap(const T& key);
	virtual BasicLHeap <LeftistNode<T>, T, MeldLeftistHeapAlg<T> >* create();
	static bool swapPredicate(LeftistNode <T>* node1, LeftistNode <T>* node2);
	static void renew(LeftistNode <T>* node1);
	~LeftistHeap();
};

template <typename T>
LeftistHeap <T>::LeftistHeap() {
	this->root_ = nullptr;
}
template <typename T>
LeftistHeap <T>::LeftistHeap(const T& key): BasicLHeap <LeftistNode<T>, T, MeldLeftistHeapAlg<T> >(key) {
}
template <typename T>
LeftistHeap <T>::~LeftistHeap() {}

template <typename T>
BasicLHeap <LeftistNode<T>, T, MeldLeftistHeapAlg<T> >* LeftistHeap<T>::create() {
	LeftistHeap<T>* heap = new LeftistHeap<T>();
	return heap;
}