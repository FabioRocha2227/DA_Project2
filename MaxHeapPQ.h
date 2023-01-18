//
// Created by nmls1 on 30/05/2022.
//

#ifndef PROJETODA_2_MAXHEAPPQ_H
#define PROJETODA_2_MAXHEAPPQ_H

#include <vector>
#include <unordered_map>

template <class K, class V>
class MaxHeapPQ {
    struct Node {
        K key;
        V value;
    };
    int size;
    int maxSize;
    std::vector<Node> H;
    std::unordered_map<K, int> pos;
    const K KEY_NOT_FOUND;
    void shiftUp(int i);
    void shiftDown(int i);
    void swap(int i1, int i2);
public:
    MaxHeapPQ(int n, const K& notFound);
    bool empty();
    bool hasKey(const K& key);
    void insert(const K& key, const V& value);
    int getSize();
    //T * extractMin();
    K extractMax();
    void increaseKey(const K& key, const V& value);
    void changePriority(int x);
    K * getMax();
    void print();
};

#define rightChild(i) ((2 * i) + 1)
#define leftChild(i) ((2 * i))
#define parent(i) ((i) / 2)

//int H[50];
//int size = -1;

// Function to return the index of the
// parent node of a given node
/*int parent(int i)
{

    return (i - 1) / 2;
}*/

// Function to return the index of the
// left child of the given node
/*int leftChild(int i)
{

    return ((2 * i) + 1);
}
*/
// Function to return the index of the
// right child of the given node
/*int rightChild(int i)
{

    return ((2 * i) + 2);
}*/

template <class K, class V>
MaxHeapPQ<K, V>::MaxHeapPQ(int n, const K& notFound) : KEY_NOT_FOUND(notFound), size(0), maxSize(n), H(n+1){}
    // indices will be used starting in 1
    // to facilitate parent/child calculations

// Function to shift up the node in order
// to maintain the heap property
template <class K, class V>
bool MaxHeapPQ<K, V>::empty() {
    return size == 0;
}

template <class K, class V>
int MaxHeapPQ<K,V>::getSize() {
    return size;
}

template <class K, class V>
bool MaxHeapPQ<K, V>::hasKey(const K& key) {
    return pos.find(key) != pos.end();
}

template <class K, class V>
void MaxHeapPQ<K,V>::increaseKey(const K& key, const V& value) {
    if (!hasKey(key)) return; // key does not exist, do nothing
    int i = pos[key];
    if (value < H[i].value) return; // value would increase, do nothing
    H[i].value = value;
    shiftUp(i);
}

template <class K, class V>
void MaxHeapPQ<K, V>::shiftUp(int i)
{
    while (i>1 && H[i].value > H[parent(i)].value) { // while pos larger than parent, keep swapping to upper position
        swap(i, parent(i));
        i = parent(i);
    }
}

// Function to shift down the node in
// order to maintain the heap property
template <class K, class V>
void MaxHeapPQ<K, V>::shiftDown(int i) {
    while (leftChild(i) <= size) { // while within heap limits
        int j = leftChild(i);
        if (rightChild(i)<=size && H[rightChild(i)].value > H[j].value) j = rightChild(i); // choose larger child
        if (H[i].value > H[j].value) break;   // node already larger than children, stop
        swap(i, j);                    // otherwise, swap with larger child
        i = j;
    }
}

template <class K, class V>
void MaxHeapPQ<K,V>::swap(int i1, int i2) {
    Node tmp = H[i1]; H[i1] = H[i2]; H[i2] = tmp;
    pos[H[i1].key] = i1;
    pos[H[i2].key] = i2;
}

// Function to insert a new element
// in the Binary Heap
template <class K, class V>
void MaxHeapPQ<K, V>::insert(const K& key, const V& value) {
    if(size == maxSize) return;
    if(hasKey(key)) return;
    H[++size] = {key, value};
    pos[key] = size;
    shiftUp(size);
}

// Function to extract the element with
// maximum priority
template <class K, class V>
K MaxHeapPQ<K, V>::extractMax() {
    if(size == 0) return KEY_NOT_FOUND;
    K max = H[1].key;
    pos.erase(max);
    H[1] = H[size--];
    shiftDown(1);
    return max;
}

// Function to change the priority
// of an element
template <class K, class V>
void MaxHeapPQ<K, V>::changePriority(int x){
    shiftDown(size);
}

// Function to get value of the current
// maximum element
template <class K, class V>
K * MaxHeapPQ<K, V>::getMax()
{

    return H[1];
}

// Function to remove the element
// located at given index
/*void remove(int i)
{
    H[i] = getMax() + 1;

    // Shift the node to the root
    // of the heap
    shiftUp(i);

    // Extract the node
    extractMax();
}*/
template <class K, class V>
void MaxHeapPQ<K, V>::print(){
    int i = 1;
    std::cout << "\nPriority Queue : " /*<< H[1]->cap*/;

    //std::cout << H[1]->cap;
    while (i <= 6) {
        std::cout << H[i].value << " ";
        i++;
    }
}

/*template <class K, class V>
void MaxHeapPQ<K, V>::set(unsigned i, K * x) {
    H[i] = x;
    x->queueIndex = i;
}*/


#endif //PROJETODA_2_MAXHEAPPQ_H
