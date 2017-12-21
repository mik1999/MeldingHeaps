#pragma once
#include <assert.h>
#include "BasicLHeap.h"
template <typename T>
class SkewHeap :
	public BasicLHeap <BasicLNode<T>, T>
{
public:
	SkewHeap();
	SkewHeap(const T& key);
	virtual void meld(IHeap <T>* heap);
	virtual BasicLHeap <BasicLNode<T>, T>* create();
	~SkewHeap();
};

template <typename T>
SkewHeap<T>::SkewHeap()
{
}

template <typename T>
SkewHeap<T>::SkewHeap(const T& key):BasicLHeap <BasicLNode<T>, T>(key) {
}

template <typename T>
SkewHeap<T>::~SkewHeap()
{
}

template <typename T>
BasicLNode<T>* meld(BasicLNode<T>* node1, BasicLNode<T>* node2) {
	if (node1 == nullptr)
		return node2;
	if (node2 == nullptr)
		return node1;
	if (node2->key() < node1->key()) {
		node2->left_ = meld<T>(node1, node2->left_);
		swap(node2->left_, node2->right_);
		return node2;
	}
	node1->right_ = meld<T>(node1->right_, node2);
	swap(node1->left_, node1->right_);
	return node1;
}
template <typename T>
void SkewHeap<T>::meld(IHeap <T>* heap) {
	assert(heap != nullptr);
	SkewHeap <T>* lheap = static_cast <SkewHeap <T>*> (heap);
	this->root_ = ::meld<T>(this->root_, lheap->root_);
	lheap->root_ = nullptr;
}
template <typename T>
BasicLHeap <BasicLNode<T>, T>* SkewHeap<T>::create() {
	SkewHeap<T>* heap = new SkewHeap<T>();
	return heap;
}


