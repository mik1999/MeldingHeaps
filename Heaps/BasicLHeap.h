#pragma once
#include <assert.h>
#include "IHeap.h"
template <class RootNode, typename T>
class BasicLHeap;

template <typename T>
class BasicLNode {
public:
	BasicLNode();
	BasicLNode(const T& key);
	BasicLNode<T> * left_, * right_;
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

template <class RootNode, typename T>
class BasicLHeap : public IHeap <T> {
protected:
	RootNode * root_;
public:
	BasicLHeap();
	BasicLHeap(const T& key);
	BasicLHeap(const BasicLHeap<RootNode, T>&);
	BasicLHeap& operator =(const BasicLHeap<RootNode, T>&);
	virtual void insert(const T& key);
	virtual const T& getMin() const;
	virtual void extractMin();
	virtual void meld(IHeap <T>* heap) = 0;
	virtual BasicLHeap<RootNode, T>* create() = 0;
	virtual bool empty() const;
	~BasicLHeap();
};

template <class RootNode, typename T>
BasicLHeap <RootNode, T>::BasicLHeap() {
	root_ = nullptr;
}

template <class RootNode>
void recursiveDelete(RootNode* node) {
	if (!node)
		return;
	recursiveDelete<RootNode>(node->left_);
	recursiveDelete<RootNode>(node->right_);
	delete node;
}
template <class RootNode>
RootNode* recursiveCopy(RootNode* dest, const RootNode* source) {
	if (!source)
		return nullptr;
	dest = new RootNode(*source);
	dest->left_ = recursiveCopy<RootNode>(dest->left_, source->left_);
	dest->right_ = recursiveCopy<RootNode>(dest->right_, source->right_);
	return dest;
}

template <class RootNode, typename T>
BasicLHeap <RootNode, T>::~BasicLHeap() {
	recursiveDelete<RootNode>(root_);
}

template <class RootNode, typename T>
BasicLHeap <RootNode, T>::BasicLHeap(const T& key) {
	root_ = new RootNode(key);
}

template <class RootNode, typename T>
BasicLHeap <RootNode, T>::BasicLHeap(const BasicLHeap<RootNode, T>& heap) {
	root_ = recursiveCopy(root_, heap.root_);
}

template <class RootNode, typename T>
BasicLHeap<RootNode, T>& BasicLHeap <RootNode, T>::operator =(const BasicLHeap<RootNode, T>& heap) {
	if (this == &heap)
		return *this;
	recursiveDelete(root_);
	root_ = recursiveCopy(root_, heap.root_);
	return *this;
}

template <class RootNode, typename T>
void BasicLHeap <RootNode, T>::insert(const T& key) {
	BasicLHeap <RootNode, T>* newHeap = create();
	newHeap->root_ = new RootNode(key);
	meld(newHeap);
}
template <class RootNode, typename T>
const T& BasicLHeap <RootNode, T>::getMin() const {
	assert(!empty());
	return root_->key_;
}
template <class RootNode, typename T>
void BasicLHeap <RootNode, T>::extractMin() {
	assert(!empty());
	BasicLHeap <RootNode, T> *heap1 = create(), *heap2 = create();
	heap1->root_ = root_->left_;
	heap2->root_ = root_->right_;
	heap1->meld(heap2);
	delete root_;
	root_ = heap1->root_;
}
template <class RootNode, typename T>
bool BasicLHeap <RootNode, T>::empty() const {
	return root_ == nullptr;
}