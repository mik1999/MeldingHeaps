#include "pch.h"
#include "Heaps/MeldingHeaps.h"
#include <fstream>
#include <cmath>
#include <ctime>
#include <algorithm>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

enum testCases {
	Tinsert,
	Textract,
	Tmeld,
	Tgetmin,
	Tadd,
	Tsize
};

void print(int t) {
	EXPECT_TRUE(false) << t;
}

void InteractiveTest(long long temps) {
	MeldingHeaps <STDHeap<int>, int> Mheap0;
	MeldingHeaps <SkewHeap<int>, int> Mheap1;
	MeldingHeaps <LeftistHeap<int>, int> Mheap2;
	MeldingHeaps <BinomialHeap<int>, int> Mheap3;
	const long long size = (long long)sqrt(temps);
	for (long long i = 0; i < size; i++) {
		int key = rand();
		Mheap0.addHeap(key);
		Mheap1.addHeap(key);
		Mheap2.addHeap(key);
		Mheap3.addHeap(key);
	}
	for (long long i = 0; i < temps; i++) {
		int k = rand() % Tsize, key = rand();
		size_t index = rand() % size, index2 = rand() % size;
		switch (k) {
		case Tinsert:
			Mheap0.insert(index, key);
			Mheap1.insert(index, key);
			Mheap2.insert(index, key);
			Mheap3.insert(index, key);
			break;
		case Textract:
			if (Mheap0.empty(index))
				break;
			Mheap0.extractMin(index);
			Mheap1.extractMin(index);
			Mheap2.extractMin(index);
			Mheap3.extractMin(index);
			break;
		case Tmeld:
			if (index == index2)
				break;
			Mheap0.meld(index, index2);
			Mheap1.meld(index, index2);
			Mheap2.meld(index, index2);
			Mheap3.meld(index, index2);
			break;
		default:
			break;
		}
		for (index = 0; (int)index < size; index++) {
			if (Mheap0.empty(index))
				continue;
			ASSERT_EQ(Mheap0.getMin(index), Mheap1.getMin(index)) << "MHeaps 0 & 1";
			ASSERT_EQ(Mheap0.getMin(index), Mheap2.getMin(index)) << "MHeaps 0 & 2";
			ASSERT_EQ(Mheap0.getMin(index), Mheap3.getMin(index)) << "MHeaps 0 & 3";
		}
	}
	ASSERT_TRUE(Mheap0 == Mheap1);
	ASSERT_TRUE(Mheap0 == Mheap2);
	ASSERT_TRUE(Mheap0 == Mheap3);
}

TEST(ConstSizeTest, Test1) {
	InteractiveTest(100);
}

TEST(ConstSizeTest, Test2) {
	InteractiveTest(1000);
}

TEST(ConstSizeTest, Test3) {
	InteractiveTest(10000);
}

TEST(ConstSizeTest, Test4) {
	InteractiveTest(100000);
}

int numOfTests = 0;

const string DirectName = "C:/myFavoriteUniversity/myFavoriteSubject/";

void GenTest1(long long numOfOper, int size, int maxSize) {
	srand(time(NULL));
	numOfTests++;
	std::ofstream out(DirectName + "Test" + to_string(numOfTests) + ".txt");
	MeldingHeaps <STDHeap <int>, int> heap;
	out << size << "\n";
	for (int i = 0; i < size; i++) {
		int k = rand();
		heap.addHeap(k);
		out << k << ' ';
	}
	out << "\n";
	for (long long i = 0; i < numOfOper; i++) {
		int k = rand() % Tsize, key = rand(), index = rand() % size, index2 = rand() % size;
		switch (k) {
		case Tinsert:
			heap.insert(index, key);
			out << k << ' ' << index << ' ' << key << '\n';
			break;
		case Textract:
			if (heap.empty(index)) {
				i--;
				break;
			}
			heap.extractMin(index);
			out << k << ' ' << index << '\n';
			break;
		case Tmeld:
			if (index == index2) {
				i--;
				break;
			}
			heap.meld(index, index2);
			out << k << ' ' << index << ' ' << index2 << '\n';
			break;
		case Tgetmin:
			if (heap.empty(index)) {
				i--;
				break;
			}
			out << k << ' ' << index << '\n';
			break;
		case Tadd:
			if (size < maxSize) {
				size++;
				heap.addHeap(key);
				out << k << ' ' << key << '\n';
			}
			else
				i--;
			break;
		default:
			break;
		}
	}
}

void GenTest2(long long numOfOper, int deep, int size, int maxSize) {
	srand(time(NULL));
	numOfTests++;
	std::ofstream out(DirectName + "Test" + to_string(numOfTests) + ".txt");
	MeldingHeaps <STDHeap <int>, int> heap;
	out << size << "\n";
	for (int i = 0; i < size; i++) {
		int k = rand();
		heap.addHeap(k);
		out << k << ' ';
	}
	out << "\n";
	for (long long i = 0; i < numOfOper; i++) {
		int key = rand(), index = rand() % size, index2 = rand() % size;
		int k;
		if (rand() % 2) {
			if (rand() % 3)
				k = Tgetmin;
			else if (rand() % 2)
				k = Tmeld;
			else
				k = Tadd;
		}
		else {
			if (i % (2 * deep) < deep) {
				if (rand() % 10)
					k = Textract;
				else
					k = Tinsert;
			}
			else {
				if (rand() % 10)
					k = Tinsert;
				else
					k = Textract;
			}
		}
		switch (k) {
		case Tinsert:
			heap.insert(index, key);
			out << k << ' ' << index << ' ' << key << '\n';
			break;
		case Textract:
			if (heap.empty(index)) {
				i--;
				break;
			}
			heap.extractMin(index);
			out << k << ' ' << index << '\n';
			break;
		case Tmeld:
			if (index == index2) {
				i--;
				break;
			}
			heap.meld(index, index2);
			out << k << ' ' << index << ' ' << index2 << '\n';
			break;
		case Tgetmin:
			if (heap.empty(index)) {
				i--;
				break;
			}
			out << k << ' ' << index << '\n';
			break;
		case Tadd:
			if (size < maxSize) {
				size++;
				heap.addHeap(key);
				out << k << ' ' << key << '\n';
			}
			else
				i--;
			break;
		default:
			break;
		}
	}
}

const int MaxTestNum = 4 * 10;

void makeTests() {
	for (int i = 1; i <= MaxTestNum / 4; i++)
		GenTest1(100, 10000, 20000);
	for (int i = 1; i <= MaxTestNum / 4; i++)
		GenTest1(1000, 100, 300);
	for (int i = 1; i <= MaxTestNum / 4; i++)
		GenTest2(100, 30, 1000, 2000);
	for (int i = 1; i <= MaxTestNum / 4; i++)
		GenTest2(i * 100000, 4000, 10000, 30000);
}

template <class Heap>
void RunTest(int testNum) {
	cout << "Test " << testNum << " is running.\n";
	std::ifstream in(DirectName + "Test" + to_string(testNum) + ".txt");
	MeldingHeaps <STDHeap<int>, int> Mheap0;
	MeldingHeaps <Heap, int> Mheap1;
	int size;
	in.tie(NULL);
	in >> size;
	for (long long i = 0; i < size; i++) {
		int key;
		in >> key;
		Mheap0.addHeap(key);
		Mheap1.addHeap(key);
	}
	while (true) {
		int k, key;
		size_t index, index2;
		if (!(in >> k))
			break;
		switch (k) {
		case Tinsert:
			in >> index >> key;
			Mheap0.insert(index, key);
			Mheap1.insert(index, key);
			break;
		case Textract:
			in >> index;
			Mheap0.extractMin(index);
			Mheap1.extractMin(index);
			break;
		case Tmeld:
			in >> index >> index2;
			Mheap0.meld(index, index2);
			Mheap1.meld(index, index2);
			break;
		case Tgetmin:
			in >> index;
			ASSERT_EQ(Mheap0.getMin(index), Mheap1.getMin(index));
			break;
		case Tadd:
			in >> key;
			Mheap0.addHeap(key);
			Mheap1.addHeap(key);
			break;
		default:
			break;
		}
		for (index = 0; (int)index < size; index++) {
			if (Mheap0.empty(index))
				continue;
			ASSERT_EQ(Mheap0.getMin(index), Mheap1.getMin(index)) << "MHeaps 0 & 1";
		}
	}
	ASSERT_TRUE(Mheap0 == Mheap1);
}

template <class Heap>
void TimeTest(int testNum, string HeapName) {
	cout << "Test " << testNum << "is running.\n";
	std::ifstream in(DirectName + "Test" + to_string(testNum) + ".txt");
	MeldingHeaps <Heap, int> Mheap;
	int size;
	in.tie(NULL);
	in >> size;
	time_t begin = clock();
	for (long long i = 0; i < size; i++) {
		int key;
		in >> key;
		Mheap.addHeap(key);
	}
	int numOfOperations = 0;
	while (true) {
		int k, key;
		size_t index, index2;
		if (!(in >> k))
			break;
		numOfOperations++;
		switch (k) {
		case Tinsert:
			in >> index >> key;
			Mheap.insert(index, key);
			break;
		case Textract:
			in >> index;
			Mheap.extractMin(index);
			break;
		case Tmeld:
			in >> index >> index2;
			Mheap.meld(index, index2);
			break;
		case Tgetmin:
			in >> index;
			Mheap.getMin(index);
			break;
		case Tadd:
			in >> key;
			Mheap.addHeap(key);
			break;
		default:
			break;
		}
	}
	std::ofstream out(DirectName + HeapName + "test.txt", std::ios::in);
	out.seekp(0, std::ios::end);
	out << testNum << ' ' << numOfOperations << ' ' << (clock() - begin) * 1000 / CLOCKS_PER_SEC << endl;
	out.close();
}

TEST(SkewHeapTest, simpleTest) {
	for (int i = 0; i < MaxTestNum / 4; i++)
		RunTest <SkewHeap<int> >(i);
	ASSERT_TRUE(true);
}

TEST(SkewHeapTest, simpleTestStress) {
	for (int i = MaxTestNum / 4; i < MaxTestNum / 2; i++)
		RunTest <SkewHeap<int> >(i);
	ASSERT_TRUE(true);
}

TEST(SkewHeapTest, hardTest) {
	for (int i = MaxTestNum / 2; i < 3 * MaxTestNum / 4; i++)
		RunTest <SkewHeap<int> >(i);
	ASSERT_TRUE(true);
}

TEST(LeftistHeapTest, simpleTest) {
	for (int i = 0; i < MaxTestNum / 4; i++)
		RunTest <LeftistHeap<int> >(i);
	ASSERT_TRUE(true);
}

TEST(LeftistHeapTest, simpleTestStress) {
	for (int i = MaxTestNum / 4; i < MaxTestNum / 2; i++)
		RunTest <LeftistHeap<int> >(i);
	ASSERT_TRUE(true);
}

TEST(LeftistHeapTest, hardTest) {
	for (int i = MaxTestNum / 2; i < 3 * MaxTestNum / 4; i++)
		RunTest <LeftistHeap<int> >(i);
	ASSERT_TRUE(true);
}

TEST(BinomialHeapTest, simpleTest) {
	for (int i = 0; i < MaxTestNum / 4; i++)
		RunTest <BinomialHeap<int> >(i);
	ASSERT_TRUE(true);
}

TEST(BinomialHeapTest, simpleTestStress) {
	for (int i = MaxTestNum / 4; i < MaxTestNum / 2; i++)
		RunTest <BinomialHeap<int> >(i);
	ASSERT_TRUE(true);
}

TEST(BinomialHeapTest, hardTest) {
	for (int i = MaxTestNum / 2; i < 3 * MaxTestNum / 4; i++)
		RunTest <BinomialHeap<int> >(i);
	ASSERT_TRUE(true);
}

TEST(TimeTest, MainTest) {
	for (int i = 3 * MaxTestNum / 4; i < MaxTestNum; i++)
		TimeTest <SkewHeap<int> >(i, "SkewHeap");
	for (int i = 3 * MaxTestNum / 4; i < MaxTestNum; i++)
		TimeTest <LeftistHeap<int> >(i, "LeftistHeap");
	for (int i = 3 * MaxTestNum / 4; i < MaxTestNum; i++)
		TimeTest <BinomialHeap<int> >(i, "BinomialHeap");
	ASSERT_TRUE(true);
}


int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}