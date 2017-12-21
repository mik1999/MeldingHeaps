#pragma once
#include <assert.h>
#include "IHeap.h"

template <class RootNode, typename T, class MeldAlg>
class BasicLHeap : public IHeap <T> {
protected:
	RootNode * root_;
public:
	BasicLHeap();
	BasicLHeap(const T& key);
	BasicLHeap(const BasicLHeap<RootNode, T, MeldAlg>&);
	BasicLHeap<RootNode, T, MeldAlg>& operator =(const BasicLHeap<RootNode, T, MeldAlg>&);
	virtual void insert(const T& key);
	virtual const T& getMin() const;
	virtual void extractMin();
	virtual void meld(IHeap <T>* heap);
	virtual BasicLHeap<RootNode, T, MeldAlg>* create() = 0;
	virtual bool empty() const;
	~BasicLHeap();
};

template <class RootNode, typename T, class MeldAlg>
BasicLHeap <RootNode, T, MeldAlg>::BasicLHeap() {
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

template <class RootNode, typename T, class MeldAlg>
BasicLHeap <RootNode, T, MeldAlg>::~BasicLHeap() {
	recursiveDelete<RootNode>(root_);
}

template <class RootNode, typename T, class MeldAlg>
BasicLHeap <RootNode, T, MeldAlg>::BasicLHeap(const T& key) {
	root_ = new RootNode(key);
}

template <class RootNode, typename T, class MeldAlg>
BasicLHeap <RootNode, T, MeldAlg>::BasicLHeap(const BasicLHeap<RootNode, T, MeldAlg>& heap) {
	root_ = recursiveCopy(root_, heap.root_);
}

template <class RootNode, typename T, class MeldAlg>
BasicLHeap<RootNode, T, MeldAlg>& BasicLHeap <RootNode, T, MeldAlg>::operator =(const BasicLHeap<RootNode, T, MeldAlg>& heap) {
	if (this == &heap)
		return *this;
	recursiveDelete(root_);
	root_ = recursiveCopy(root_, heap.root_);
	return *this;
}

template <class RootNode, typename T, class MeldAlg>
void BasicLHeap <RootNode, T, MeldAlg>::insert(const T& key) {
	BasicLHeap <RootNode, T, MeldAlg>* newHeap = create();
	newHeap->root_ = new RootNode(key);
	meld(newHeap);
}
template <class RootNode, typename T, class MeldAlg>
const T& BasicLHeap <RootNode, T, MeldAlg>::getMin() const {
	assert(!empty());
	return root_->key_;
}
template <class RootNode, typename T, class MeldAlg>
void BasicLHeap <RootNode, T, MeldAlg>::extractMin() {
	assert(!empty());
	BasicLHeap <RootNode, T, MeldAlg> *heap1 = create(), *heap2 = create();
	heap1->root_ = root_->left_;
	heap2->root_ = root_->right_;
	heap1->meld(heap2);
	delete root_;
	root_ = heap1->root_;
}

template <class RootNode, typename T, class MeldAlg>
bool BasicLHeap <RootNode, T, MeldAlg>::empty() const {
	return root_ == nullptr;
}

template <class RootNode, typename T, class MeldAlg>
RootNode* meld(RootNode* node1, RootNode* node2) {
	if (node1 == nullptr)
		return node2;
	if (node2 == nullptr)
		return node1;
	if (node2->key() < node1->key()) {
		node2->left_ = meld<RootNode, T, MeldAlg>(node1, node2->left_);
		MeldAlg::renew(node2);
		if (MeldAlg::swapPredicate(node2->left_, node2->right_))
			swap(node2->left_, node2->right_);
		return node2;
	}
	node1->right_ = meld<RootNode, T, MeldAlg>(node1->right_, node2);
	MeldAlg::renew(node1);
	if (MeldAlg::swapPredicate(node1->left_, node1->right_))
		swap(node1->left_, node1->right_);
	return node1;
}

template <class RootNode, typename T, class MeldAlg>
void BasicLHeap <RootNode, T, MeldAlg>::meld(IHeap <T>* heap) {
	assert(heap != nullptr);
	BasicLHeap <RootNode, T, MeldAlg>* lheap = static_cast <BasicLHeap <RootNode, T, MeldAlg>*> (heap);
	this->root_ = ::meld<RootNode, T, MeldAlg>(this->root_, lheap->root_);
	lheap->root_ = nullptr;
}