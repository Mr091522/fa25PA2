//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    //this will help with the min heap and it running properly
    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        // this will help place the new index at the end of this array
        if (size >= 64) {
            cerr << "Heap overflow\n";
            return;
        }
        data[size] = idx; //fixed down here
        size++;
        //will restore the heap when it is moving elements this will make sure the smallest number is fixed properly
        upheap(size-1, weightArr);
        //This will incremnet the size after it is put
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        //this will help with an empty heap case
        if (size == 0) {
            return -1;
        }
            //this will help with saving to (return later) the root
            int minIndx = data[0];
            size--;
            //this will then help with the downward new root if needed
            if (size > 0) {
                data[0] = data[size]; //will move the last root
                downheap(0, weightArr);
            }
            return minIndx;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        //will continue moving up till the correct root is found
        while (pos > 0) {
            //Then we have to calculate the parents index
            int parent = (pos - 1) / 2;
            //then we will have to compare with data from the position and parents
            //then with the weight we go from there
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                int tmp = data[pos]; data[pos] = data[parent]; data[parent] = tmp;// will not use std as per requirment
                pos = parent;
                //swaps the index if the child is smaller
                //will keep moving until everything is satisfed
            }else{
                return;
            }
        }
    }


    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            //will calculate the children in the index
            int leftChild = 2 * pos + 1;//left
            int rightChild = 2 * pos + 2;//right
            int smallest = pos;

            if (leftChild < size && weightArr[data[leftChild]] < weightArr[data[smallest]]) {
                smallest = leftChild; //left
            }
            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[smallest]]) {
                smallest = rightChild; //right
            }
            if (smallest == pos) return;
            int temp = data[pos]; data[pos] = data[smallest]; data[smallest] = temp;
            pos = smallest;
        }
    }
};

#endif