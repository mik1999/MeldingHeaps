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
LeftistNode<T>::LeftistNode() {}

template <typename T>
LeftistNode<T>::LeftistNode(const T& key) : key_(key) {
	rank_ = 0;
	left_ = right_ = nullptr;
}

template <typename T>
class LeftistHeap :
	public BasicLHeap <LeftistNode<T>, T>
{
public:
	LeftistHeap();
	LeftistHeap(const T& key);
	virtual void meld(IHeap <T>* heap);
	virtual BasicLHeap <LeftistNode<T>, T>* create();
	~LeftistHeap();
};

template <typename T>
LeftistHeap <T>::LeftistHeap() {
	this->root_ = nullptr;
}
template <typename T>
LeftistHeap <T>::LeftistHeap(const T& key): BasicLHeap <LeftistNode<T>, T>(key) {
}
template <typename T>
LeftistHeap <T>::~LeftistHeap() {}

template <typename T>
int rank(LeftistNode <T>* node) {
	return (node == nullptr) ? 0 : node->rank();
}
template <typename T>
inline void renew(LeftistNode <T>* node) {
	if (!node)
		return;
	node->rank_ = min(::rank<T>(node->left_), ::rank<T>(node->right_)) + 1;
}
template <typename T>
LeftistNode<T>* meld(LeftistNode<T>* node1, LeftistNode<T>* node2) {
	if (node1 == nullptr)
		return node2;
	if (node2 == nullptr)
		return node1;
	if (node2->key() < node1->key()) {
		node2->left_ = meld(node1, node2->left_);
		renew(node2);
		if (::rank<T>(node2->left_) < ::rank<T>(node2->right_))
			swap(node2->left_, node2->right_);
		return node2;
	}
	node1->right_ = meld(node1->right_, node2);
	renew(node1);
	if (::rank<T>(node1->left_) < ::rank<T>(node1->right_))
		swap(node1->left_, node1->right_);
	return node1;
}

template <typename T>
void LeftistHeap <T>::meld(IHeap <T>* heap) {
	assert(heap != nullptr);
	LeftistHeap <T>* lheap = static_cast <LeftistHeap <T>*> (heap);
	this->root_ = ::meld<T>(this->root_, lheap->root_);
	lheap->root_ = nullptr;
}
template <typename T>
BasicLHeap <LeftistNode<T>, T>* LeftistHeap<T>::create() {
	LeftistHeap<T>* heap = new LeftistHeap<T>();
	return heap;
}
