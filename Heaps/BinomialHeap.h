#pragma once
#include "IHeap.h"
#include <vector>


template <typename T>
class BinomialHeap;

template <typename T>
class BinomialNode {
public:
	std::vector <BinomialNode<T> *> childs_;
	T min_;
	BinomialNode();
	const T& getMin() const;
	size_t size() const;
	BinomialNode(const T& key);
	BinomialNode(BinomialNode<T>* node1, BinomialNode<T>* node2);
};

template <typename T>
const T& BinomialNode<T>::getMin() const{
	return min_;
}

template <typename T>
size_t BinomialNode<T>::size() const{
	return childs_.size();
}

template <typename T>
BinomialNode<T>::BinomialNode(const T& key) : min_(key) {
}

template <typename T>
BinomialNode<T>::BinomialNode(BinomialNode<T>* node1, BinomialNode<T>* node2) {
	if (node2->min_ < node1->min_)
		swap(node1, node2);
	min_ = node1->min_;
	childs_.resize(node1->size() + 1);
	std::copy(node1->childs_.begin(), node1->childs_.end(), childs_.begin());
	childs_.back() = node2;
}

template <typename T>
class BinomialHeap :
	public IHeap <T> {
private:
	std::vector<BinomialNode<T>*>trees_;
	T min_;
	void align_();
public:
	BinomialHeap();
	BinomialHeap(const BinomialHeap<T>& heap);
	BinomialHeap<T>& operator =(const BinomialHeap<T>& heap);
	BinomialHeap(const T& key);
	virtual void insert(const T& key);
	virtual const T& getMin() const;
	virtual void extractMin();
	virtual void meld(IHeap <T>* heap);
	virtual bool empty() const;
	~BinomialHeap();
};

template <typename T>
void BinomialHeap<T>::align_() {
	while (!trees_.empty() && trees_.back() == nullptr)
		trees_.pop_back();
}

template <typename T>
BinomialHeap<T>::BinomialHeap() {
}

template <typename T>
BinomialHeap<T>::BinomialHeap(const T& key){
	BinomialNode<T>* node = new BinomialNode<T>(key);
	trees_.push_back(node);
	min_ = key;
}

template <typename T>
void recursiveDelete(BinomialNode<T>* node) {
	for (size_t i = 0; i < node->size(); i++)
		recursiveDelete(node->childs_[i]);
	delete node;
}

template <typename T>
BinomialNode<T>* recursiveCopy(BinomialNode<T>* dest, BinomialNode<T>* source) {
	if (!source)
		return nullptr;
	dest = new BinomialNode<T>(*source);
	for (size_t i = 0; i < dest->size(); i++)
		dest->childs_[i] = recursiveCopy(dest->childs_[i], source->childs_[i]);
	return dest;
}

template <typename T>
BinomialHeap<T>::BinomialHeap(const BinomialHeap<T>& heap) {
	min_ = heap.min_;
	trees_.resize(heap.trees_.size());
	for (size_t i = 0; i < trees_.size(); i++)
		trees_[i] = recursiveCopy(trees_[i], heap.trees_[i]);
}

template <typename T>
BinomialHeap<T>& BinomialHeap<T>::operator =(const BinomialHeap<T>& heap) {
	if (this == &heap)
		return *this;
	min_ = heap.min_;
	assert(trees_.size() == heap.trees_.size());
	for (size_t i = 0; i < trees_.size(); i++)
		if (trees_[i] != nullptr)
			recursiveDelete(trees_[i]);
	for (size_t i = 0; i < trees_.size(); i++)
		trees_[i] = recursiveCopy(trees_[i], heap.trees_[i]);
}


template <typename T>
BinomialHeap<T>::~BinomialHeap() {
	for (size_t i = 0; i < trees_.size(); i++)
		if (trees_[i] != nullptr)
			recursiveDelete(trees_[i]);
}

template <typename T>
const T& BinomialHeap<T>::getMin() const {
	assert(!empty());
	return min_;
}

template <typename T>
void BinomialHeap<T>::insert(const T& key) {
	BinomialHeap<T>* heap = new BinomialHeap<T>(key);
	meld(heap);
}

template <typename T>
void BinomialHeap<T>::extractMin() {
	assert(!empty());
	size_t pos = 0;
	for (; pos < trees_.size() && (!trees_[pos] || trees_[pos]->getMin() != min_); pos++);
	assert(pos < trees_.size());
	BinomialHeap<T> heap;
	heap.trees_ = trees_[pos]->childs_;
	delete trees_[pos];
	trees_[pos] = nullptr;
	align_();
	meld(&heap);
	bool flag = false;
	for (size_t i = 0; i < trees_.size(); i++)
		if (trees_[i]) {
			if (!flag) {
				flag = true;
				min_ = trees_[i]->min_;
			}
			else
				min_ = min(min_, trees_[i]->min_);
		}
}

template <typename T>
bool BinomialHeap<T>::empty() const {
	return trees_.empty();
}

template <typename T>
void BinomialHeap<T>::meld(IHeap <T>* heap) {
	assert(heap != nullptr);
	BinomialHeap <T>* bheap = static_cast <BinomialHeap <T>*> (heap);
	if (trees_.size() == 0) {
		if (bheap->trees_.size() != 0)
			min_ = bheap->getMin();
	} 
	else if (bheap->trees_.size() != 0)
		min_ = min(getMin(), bheap->getMin());
	trees_.resize(max(trees_.size(), bheap->trees_.size()) + 1);
	BinomialNode<T>* prevNode = nullptr;
	for (size_t i = 0; i < bheap->trees_.size(); i++) {
		if (prevNode && trees_[i] && bheap->trees_[i]) {
			prevNode = new BinomialNode<T>(prevNode, bheap->trees_[i]);
			continue;
		}
		if (!trees_[i])
			swap(prevNode, trees_[i]);
		if (!bheap->trees_[i])
			swap(prevNode, bheap->trees_[i]);
		if (trees_[i] && bheap->trees_[i]) {
			prevNode = new BinomialNode<T>(trees_[i], bheap->trees_[i]);
			trees_[i] = nullptr;
		}
		else if (!trees_[i])
			trees_[i] = bheap->trees_[i];
	}
	for (size_t i = bheap->trees_.size(); i < trees_.size(); i++) {
		if (trees_[i] && prevNode) {
			prevNode = new BinomialNode<T>(prevNode, trees_[i]);
			trees_[i] = nullptr;
		}
		else if (!trees_[i]) {
			trees_[i] = prevNode;
			prevNode = nullptr;
		}
	}
	align_();
	bheap->trees_.clear();
}