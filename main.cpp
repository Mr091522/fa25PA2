//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;
struct Frame {
    int node;
    string code;
};

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}


// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}
//will soon fix this

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    if (nextFree == 0) return -1; //will help keep the input empty
    if (nextFree == 1) return 0; // this will make he 1 leaf a root
    MinHeap heap;
    // 2. Push all leaf node indices into the heap.
    for (int i = 0; i < nextFree; i++) {
        heap.push(i, weightArr);//this adds everything to the heap
    }
    //int parentIdx = nextFree; //Creates a new parent
    // 3. While the heap size is greater than 1:
    while (heap.size > 1) {
        //    - Pop two smallest nodes
        int leftChild = heap.pop(weightArr);
        int rightChild = heap.pop(weightArr);

        int parentIdx = nextFree; //Creates a new parent
        //    - Create a new parent node with combined weight
        weightArr[parentIdx] = weightArr[leftChild] + weightArr[rightChild];
    //    - Set left/right pointers
        leftArr[parentIdx] = leftChild;
        rightArr[parentIdx] = rightChild;
        //    - Push new parent index back into the heap
        charArr[parentIdx] = '\0';
        nextFree++;
        heap.push(parentIdx, weightArr);
}
    // 4. Return the index of the last remaining node (root)
    return heap.pop(weightArr); // fixed
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    if (root < 0) {
        return;
    }// checks if empty
    stack<int> nodeStack;
    stack<string> codeStack;
    stack<Frame> s;
    s.push({root, ""});//supposed to look at the string

    //will go when the stack is empty
    while (!s.empty()) {
        //pair<int, string> current = s.top();
        auto [nodeIdx, code] = s.top();
        s.pop();

        if (leftArr[nodeIdx] == -1 && rightArr[nodeIdx] == -1) {
            int charIdx = charArr[nodeIdx] - 'a';
            if ( 0 <= charIdx && charIdx < 26) {
                codes[charIdx] = code.empty() ? "0" : code;
            }
        }else{
            // Left edge adds '0', right edge adds '1'.
         if (rightArr[nodeIdx] != -1) {
             s.push({rightArr[nodeIdx], code + "1"});// when it is on right it will add one
         }
            if (leftArr[nodeIdx] != -1) {
             s.push({leftArr[nodeIdx], code + "0"});// when it is on left it will add zero
            }
         }
        }
    }
    // Record code when a leaf node is reached.

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}