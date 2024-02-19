#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <sstream>
#include <list>
#include <cctype>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// DocumentItem structure to store document information

struct DocumentItem {

    string documentName;

    int count;


    // Constructor to initialize DocumentItem

    DocumentItem(string  name, int cnt) : documentName(move(name)), count(cnt) {}



};



// WordItem structure to store word information including a list of DocumentItems

struct WordItem {

    string word;

    vector<DocumentItem> documentList;



    // Default constructor

    WordItem() : word(""), documentList() {}

    // Updated constructor to accept two arguments

    WordItem(string  w, const vector<DocumentItem>& docList)

        : word(move(w)), documentList(docList) {}



    // Kopyalama operatörü

    WordItem& operator=(const WordItem& other) {

        if (this != & other) {

            word = other.word;

            documentList = other.documentList;

        }

        return *this;

    }

};
    std::vector<std::string> splitWord(const std::string& word) {
    std::vector<std::string> result;
    std::string currentPart;

    for (char c : word) {
        if (isalpha(c)) {
            // If character is alphabetical, add to existing track
            
            currentPart += tolower(c);
        } 
        else {
            // If character is not alphabetical, add current fragment to vector and reset
            if (!currentPart.empty()) {
                result.push_back(currentPart);
                currentPart.clear();
            }
        }
    }

    // Don't forget to add the current part at the end of the loop
    if (!currentPart.empty()) {
        result.push_back(currentPart);
    }

    return result;
}



// Comparison function sorts WordItems by word name

bool compareWordItem(const WordItem& a, const WordItem& b) {

    return a.word < b.word;

}



// Median selection process

int medianSelection(vector<WordItem>& arr, int low, int high) {

    int middle = low + (high - low) / 2;

    int pivotIndex;



    // Find the median by sorting

    sort(arr.begin() + low, arr.begin() + high + 1, compareWordItem);



    // Find index of middle element in index

    for (int i = low; i <= high; ++i) {

        if (arr[i].word == arr[middle].word) {

            pivotIndex = i;

            break;

        }

    }



    return pivotIndex;

}



// Quick Sort algorithm

void quickSortMedian(vector<WordItem>& arr, int low, int high) {

    if (low < high) {

        // Use median selection for pivot selection

        int pivotIndex = medianSelection(arr, low, high);



        // Sort elements around pivot

        sort(arr.begin() + low, arr.begin() + high + 1, compareWordItem);



        // Find the correct position of the pivot

        int i = low - 1;

        int j = high + 1;



        while (true) {

            do {

                ++i;

            } while (arr[i].word < arr[pivotIndex].word);



            do {

                --j;

            } while (arr[j].word > arr[pivotIndex].word);



            if (i >= j)

                break;



            swap(arr[i], arr[j]);

        }



        // Move pivot to correct position

        swap(arr[pivotIndex], arr[j]);



        // The pivot is in the correct position when we divide it in half

        // So call Quick Sort recursively for both parts

        quickSortMedian(arr, low, j);

        quickSortMedian(arr, j + 1, high);

    }

}



// Random pivot selection process

int randomPivotSelection(int low, int high) {

    return low + rand() % (high - low + 1);

}



// Random Quick Sort algorithm

void quickSortRandom(vector<WordItem>& arr, int low, int high) {

    if (low < high) {

        // Random pivot selection

        int pivotIndex = randomPivotSelection(low, high);



        // Sort elements around pivot

        sort(arr.begin() + low, arr.begin() + high + 1, compareWordItem);



        // Find the correct position of the pivot

        int i = low - 1;

        int j = high + 1;



        while (true) {

            do {

                ++i;

            } while (arr[i].word < arr[pivotIndex].word);



            do {

                --j;

            } while (arr[j].word > arr[pivotIndex].word);



            if (i >= j)

                break;



            swap(arr[i], arr[j]);

        }



        // Move pivot to correct position

        swap(arr[pivotIndex], arr[j]);



        // The pivot is in the correct position when we divide it in half

        // So call Quick Sort recursively for both parts

        quickSortRandom(arr, low, j);

        quickSortRandom(arr, j + 1, high);

    }

}



// Quick Sort(First) algorithm

void quickSortFirst(vector<WordItem>& arr, int low, int high) {

    if (low < high) {

        // Select first element of array as pivot

        int pivotIndex = low;



        // Sort elements around pivot

        sort(arr.begin() + low, arr.begin() + high + 1, compareWordItem);



        // Find the correct position of the pivot

        int i = low - 1;

        int j = high + 1;



        while (true) {

            do {

                ++i;

            } while (arr[i].word < arr[pivotIndex].word);



            do {

                --j;

            } while (arr[j].word > arr[pivotIndex].word);



            if (i >= j)

                break;



            swap(arr[i], arr[j]);

        }



        // Move pivot to correct position

        swap(arr[pivotIndex], arr[j]);



        // The pivot is in the correct position when we divide it in half

        // So call Quick Sort recursively for both parts

        quickSortFirst(arr, low, j);

        quickSortFirst(arr, j + 1, high);

    }

}



// Merge function

void merge(vector<WordItem>& arr, int low, int mid, int high) {

    int n1 = mid - low + 1;

    int n2 = high - mid;



    // Create temporary vectors

    vector<WordItem> leftArr(n1);

    vector<WordItem> rightArr(n2);



    // Copy left half

    for (int i = 0; i < n1; i++)

        leftArr[i] = arr[low + i];



    // Copy right half

    for (int j = 0; j < n2; j++)

        rightArr[j] = arr[mid + 1 + j];



    // merge process

    int i = 0, j = 0, k = low;



    while (i < n1 && j < n2) {

        if (compareWordItem(leftArr[i], rightArr[j])) {

            arr[k] = leftArr[i];

            i++;

        }

        else {

            arr[k] = rightArr[j];

            j++;

        }

        k++;

    }



    // Combine remaining elements

    while (i < n1) {

        arr[k] = leftArr[i];

        i++;

        k++;

    }



    while (j < n2) {

        arr[k] = rightArr[j];

        j++;

        k++;

    }

}



// Merge Sort algorithm

void mergeSort(vector<WordItem>& arr, int low, int high) {

    if (low < high) {

        int mid = low + (high - low) / 2;



        // Sort left half

        mergeSort(arr, low, mid);



        // Sort right half

        mergeSort(arr, mid + 1, high);



        // combine

        merge(arr, low, mid, high);

    }

}



// Heapify functions

void heapify(vector<WordItem>& arr, int n, int i) {

    int largest = i;  // Index of largest element

    int left = 2 * i + 1;

    int right = 2 * i + 2;



    // If the left child is the oldest

    if (left < n && compareWordItem(arr[left], arr[largest]))

        largest = left;



    // If the right child is the oldest

    if (right < n && compareWordItem(arr[right], arr[largest]))

        largest = right;



    // If largest element is not root

    if (largest != i) {

        swap(arr[i], arr[largest]);



        // Fix modified subtree with heapify

        heapify(arr, n, largest);

    }

}



// Heap creation function

void makeHeap(vector<WordItem>& arr) {

    int n = arr.size();



    // Apply heapify starting from the last node

    for (int i = n / 2 - 1; i >= 0; i--) {

        heapify(arr, n, i);

    }

}



// Heap Sort algorithm

void heapSort(vector<WordItem>& arr) {

    int n = arr.size();



    // Create heap

    makeHeap(arr);



    // Sort vector by sequentially removing elements from heap

    for (int i = n - 1; i > 0; i--) {

        swap(arr[0], arr[i]);

        heapify(arr, i, 0);

    }

}



// Insertion Sort algorithm

void insertionSort(vector<WordItem>& arr) {

    int n = arr.size();

    for (int i = 1; i < n; i++) {

        WordItem key = arr[i];

        int j = i - 1;



        // If previous element is greater than key, swap

        while (j >= 0 && compareWordItem(arr[j], key)) {

            arr[j + 1] = arr[j];

            j = j - 1;

        }

        arr[j + 1] = key;

    }

}



// Function to print WordItem vector

void printWordItemVector(const vector<WordItem>& wordVector) {

    for (const auto& wordItem : wordVector) {

        cout << "Word: " << wordItem.word << endl;

        cout << "Documents:" << endl;



        for (const auto& documentItem : wordItem.documentList) {

            cout << "  Document Name: " << documentItem.documentName << endl;

            cout << "  Count: " << documentItem.count << endl;

            cout << "------------------------" << endl;

        }



        cout << "========================" << endl;

    }

}



// Binary Search algorithm

int binarySearch(const vector<WordItem>& arr, const string& target) {

    int low = 0;

    int high = arr.size() - 1;



    while (low <= high) {

        int mid = low + (high - low) / 2;



        // Compare target to median element

        if (arr[mid].word == target)

            return mid;  // Target found, return index



        // If the target is smaller than the median element, check the left half

        else if (arr[mid].word > target)

            high = mid - 1;



        // If the target is larger than the median element, check the right half

        else

            low = mid + 1;

    }



    return -1;  // Target not found

}



// Binary Search Tree Node

struct TreeNode {

    WordItem data;

    TreeNode* left;

    TreeNode* right;



    // Constructor to initialize TreeNode

    TreeNode(WordItem w) : data(w), left(nullptr), right(nullptr) {}

};



class BST {

private:

    TreeNode* root;



    // Private helper method to insert a WordItem into the BST

    TreeNode* insertHelper(TreeNode* node, const WordItem& item) {

        if (node == nullptr) {

            return new TreeNode(item);

        }



        if (item.word < node->data.word) {

            node->left = insertHelper(node->left, item);

        }

        else if (item.word > node->data.word) {

            node->right = insertHelper(node->right, item);

        }



        return node;

    }



    // Private helper method to update a WordItem in the BST

    TreeNode* updateHelper(TreeNode* node, const WordItem& item) {

        if (node == nullptr) {

            // Word not found, insert the new WordItem

            return new TreeNode(item);

        }



        if (item.word < node->data.word) {

            node->left = updateHelper(node->left, item);

        }

        else if (item.word > node->data.word) {

            node->right = updateHelper(node->right, item);

        }

        else {

            // Word found, update the documentList

            node->data.documentList = item.documentList;

        }



        return node;

    }



    // Private helper method to search for a WordItem in the BST

    WordItem* searchHelper(TreeNode* node, const string& word) {

        if (node == nullptr) {

            return nullptr; // Word not found

        }



        if (word < node->data.word) {

            return searchHelper(node->left, word);

        }

        else if (word > node->data.word) {

            return searchHelper(node->right, word);

        }

        else {

            return &node->data; // Word found

        }

    }





public:

    // Constructor to initialize BST

    BST() : root(nullptr) {}



    // Public method to insert a WordItem into the BST

    void insert(const WordItem& item) {

        root = insertHelper(root, item);

    }



    // Public method to update a WordItem in the BST

    void update(const WordItem& item) {

        root = updateHelper(root, item);

    }



    // Public method to search for a WordItem in the BST

    WordItem* search(const string& word) {

        return searchHelper(root, word);

    }



    // Function to print the BST using in-order traversal

    void printInOrder(TreeNode* node) {

        if (node != nullptr) {

            printInOrder(node->left);

            cout << "word :" << node->data.word << " documentList : " << node->data.documentList[0].count << endl;

            printInOrder(node->right);

        }

    }





    // Function to print the BST (wrapper function)

    void print() {

        printInOrder(root);

    }

};



// HashTable class using separate chaining

template <typename T>

class HashTable {

private:

    vector<list<T>> table;

    size_t itemCount;

    size_t capacity;

    double loadFactorThreshold;

    std::vector<int> primeNumbers;



    // Hash function to generate hash values for WordItem structs

    size_t hashFunction(const string& key) const {

        hash<string> hasher;

        return hasher(key) % capacity;

    }

    size_t hashFunction(const string& key, size_t tableSize) const {

        hash<string> hasher;

        return hasher(key) % tableSize;

    }



    // Rehash the table to ensure the load factor threshold is not exceeded

    void rehash() {

        size_t newCapacity = capacity * 2;  // Kapasiteyi iki katına çıkar

        vector<list<T>> newTable(newCapacity);



        for (auto& chain : table) {

            for (auto& item : chain) {

                size_t newIndex = hashFunction(item.word, newCapacity);

                newTable[newIndex].push_back(item);

            }

        }



        // Tabloyu ve kapasiteyi güncelle

        table = move(newTable);

        capacity = newCapacity;;

    }

    // Kapasite kontrolü ve gerekirse artırma

    void checkAndIncreaseCapacity() {

        double currentLoadFactor = static_cast<double>(itemCount) / capacity;



        // Eğer load factor threshold'ı geçiyorsa kapasiteyi artır

        if (currentLoadFactor > loadFactorThreshold) {

            size_t newCapacity = capacity * 2;  // Kapasiteyi iki katına çıkar

            vector<list<T>> newTable(newCapacity);



            // Elemanları yeni tabloya taşı

            for (auto& chain : table) {

                for (auto& item : chain) {

                    size_t newIndex = hashFunction(item.word);

                    newTable[newIndex].push_back(item);

                }

            }



            // Yeni tabloyu ve kapasiteyi güncelle

            table = move(newTable);

            capacity = newCapacity;

        }

    }



public:

    // Constructor

    HashTable(size_t initialCapacity, double loadFactor)

        : itemCount(0), capacity(initialCapacity), loadFactorThreshold(loadFactor) {

        table.resize(capacity);

    }





    bool isPrime(size_t n) {

        if (n <= 1) {

            return false;

        }

        for (size_t i = 2; i <= sqrt(n); ++i) {

            if (n % i == 0) {

                return false;

            }

        }

        return true;

    }

    size_t getNextPrime(size_t n) {

        while (!isPrime(n)) {

            ++n;

        }

        return n;

    }

    void insert(const T& item) {

        size_t index = hashFunction(item.word);



        // Always update by adding a new node

        table[index].push_back(item);

        itemCount++;



        double currentLoadFactor = static_cast<double>(itemCount) / capacity;

        checkAndIncreaseCapacity();

    }



    // Search for an item in the hash table

    vector<DocumentItem> search(const string& key) {

        size_t index = hashFunction(key);



        // Find the item in the chain

        auto it = find_if(table[index].begin(), table[index].end(),

            [&key](const T& item) { return item.word == key; });



        if (it != table[index].end()) {

            // Item found, return the documents information

            return vector<DocumentItem>(it->documents.begin(), it->documents.end());

        }

        else {

            // Item not found

            return {};

        }

    }

    // Function that updates node

        void updateNode(const string& word, const string& documentName) 
    {
            size_t index = hashFunction(word);

            auto it = find_if(table[index].begin(), table[index].end(),
                [&word](const T& existingItem) { return existingItem.word == word; });

            if (it != table[index].end()) {
                vector<DocumentItem>& docList = it->documentList;
                for (int i = 0; i < docList.size(); i++) {
                    if (docList[i].documentName == documentName) {
                        docList[i].count+=1;
                        return;
                    }
                }
                DocumentItem newDocItem(documentName, 1);
                docList.push_back(newDocItem);
            }
        }

    //Hash Table printing function

    void printTable() const {

        for (size_t i = 0; i < capacity; ++i) {

            cout << "Index " << i << ": ";

            for (const auto& item : table[i]) {

                cout << "(" << item.word << ", [";

                for (const auto& docItem : item.documentList) {

                    cout << "{" << docItem.documentName << ", " << docItem.count << "}, ";

                }

                cout << "]), ";

            }

            cout << "\n";

        }

    }

    // Get the current item count in the hash table

    size_t getItemCount() const {

        return itemCount;

    }



    // Get the current load factor in the hash table

    double getLoadFactor() const {

        return static_cast<double>(itemCount) / capacity;

    }



    // Function: Search for WordItem of a specific word in Hashtable

    T findWord(const string& word) const {

        size_t index = hashFunction(word);



        auto it = find_if(table[index].begin(), table[index].end(),

            [&word](const T& item) { return item.word == word; });



        if (it != table[index].end()) {

            // Word found, return corresponding WordItem

            return *it;

        }

        else {

            // Word not found, return an empty WordItem

            return T{ "", {} };

        }

    }

};





int main() {
    
    // Set seed for random number generation
    
    srand(time(nullptr));
    
    
    
    //BST object created
    
    BST bst;
    
    
    
    // HashTable object created
    
    HashTable<WordItem> hashTable(53, 0.9); // Initial capacity: 53, Load factor threshold: 0.9
    
    
    
    vector<WordItem> wordItems = {};
    
    int numberFiles;    //Number of files
    
    cout << "Enter number of input files: ";   //Getting the number of files from the user
    
    cin >> numberFiles;
    
    vector<string> filenames(numberFiles); // Vector where file names are stored
    
    
    
    for (int i = 0; i < numberFiles; i++) { //getting file names from user
        
        cout << "Enter " << i + 1 << ". file name: ";
        
        cin >> filenames[i];
        
    }
    
    
    
    for (int i = 0; i < numberFiles; i++) {
        
        ifstream file(filenames[i]);   //Opening the file
        
        string word;
        
        while (file >> word) {
            
            auto parts = splitWord(word);   //word preprocessing
            
            for (const std::string& part : parts) {
                
                bool isword = false;
                
                for (auto& wordItem : wordItems) {
                    
                    bool isdoc = false;
                    
                    if (wordItem.word == part) {
                        
                        isword = true;
                        
                        for (auto& docItem : wordItem.documentList) {
                            
                            if (docItem.documentName == filenames[i]) {
                                
                                docItem.count = docItem.count + 1;
                                
                                isdoc = true;
                                
                            }
                            
                        }
                        
                        if (!isdoc) {
                            
                            DocumentItem docItem = { filenames[i], 1 };
                            
                            wordItem.documentList.push_back(docItem);
                            
                        }
                        
                    }
                    
                }
                
                if (!isword) {
                    
                    DocumentItem docItem = { filenames[i], 1 };
                    
                    WordItem wordItem = { part,{docItem} };
                    
                    wordItems.push_back(wordItem);
                    
                }
                
                
                
                WordItem wordItem = hashTable.findWord(part);   //Searching for the word in hashtable
                
                if (!wordItem.word.empty()) {     //If the word is in the hash table, the update will be done.
                    
                    hashTable.updateNode(wordItem.word, filenames[i]);
                    
                }
                
                else {  //If the word is not in the hash table, it will be added to the hash table.
                    
                    wordItem.word = part;
                    
                    wordItem.documentList.push_back({ filenames[i], 1 });
                    
                    hashTable.insert(wordItem);
                    
                }
                
                
                
                // Searching for a WordItem in the BST
                
                WordItem* result = bst.search(part);
                
                if (result != nullptr) {
                    
                    bool isFile = false;
                    
                    for (int j = 0; j < result->documentList.size(); j++) {
                        
                        /*
                         
                         * Document Item is searched on the node returned from the search function,
                         
                         * and if there is matching data, the data will be updated.
                         
                         */
                        
                        if (result->documentList[j].documentName == filenames[i]) {
                            
                            isFile = true;
                            
                            DocumentItem* documentItem = &(result->documentList[j]);
                            
                            documentItem->count += 1;
                            
                        }
                        
                    }
                    
                    if (!isFile) {
                        
                        /*
                         
                         * DocumentItem is searched on the node returned from the search function.
                         
                         * Since there is no matching data, new data will be added to the node.
                         
                         */
                        
                        result->documentList.emplace_back(filenames[i], 1);
                        
                    }
                    
                }
                
                else {
                    
                    DocumentItem doc(filenames[i], 1);
                    
                    // Creating WordItem
                    
                    WordItem wordItem(part, { doc });
                    
                    bst.insert(wordItem);
                    
                }
                
            }
            
        }
        
        file.close();
        
    }
    
    // Creating a copy vector using the assignment operator
    
    std::vector<WordItem> quickMedian = wordItems;
    
    // Sort vector<WordItem> using Quick Sort
    
    quickSortMedian(quickMedian, 0, quickMedian.size() - 1);
    
    // Creating a copy vector using the assignment operator
    
    std::vector<WordItem> quickRandom = wordItems;
    
    // Sort vector<WordItem> using Quick Sort
    
    quickSortRandom(quickRandom, 0, quickRandom.size() - 1);
    
    
    
    // Creating a copy vector using the assignment operator
    
    std::vector<WordItem> quickFirst = wordItems;
    
    // Sort vector<WordItem> using Quick Sort
    
    quickSortFirst(quickFirst, 0, quickFirst.size() - 1);
    
    std::vector<WordItem> mergeItems = wordItems;
    
    // Sort vector<WordItem> using Merge Sort
    
    mergeSort(mergeItems, 0, mergeItems.size() - 1);
    
    
    
    std::vector<WordItem> heapItems = wordItems;
    
    // Sort vector<WordItem> using Heap Sort
    
    heapSort(heapItems);
    
    std::vector<WordItem> insertionItems = wordItems;
    
    // Sort vector<WordItem> using Insertion Sort
    
    insertionSort(insertionItems);
    
    
    
    cout << "\nAfter preprocessing, the unique word count is " << hashTable.getItemCount() << ". Current load ratio is " << hashTable.getLoadFactor() << endl;
    
    
    
    string inputLine;
    
    cout << "Enter queried words in one line: ";
    
    while (true) {    //Receiving the data to be queried from the user
        
        
        
        getline(cin, inputLine);
        
        if (inputLine.empty()) {
            
            continue;
            
        }
        
        break;
        
    }
    
    istringstream iss(inputLine);
    
    vector<string> words; //Vector where the words to be queried will be stored
    
    // Separating words from stringstream
    
    string word;
    
    while (iss >> word) {
        
        // Convert to lowercase
        
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        auto parts = splitWord(word);   //word preprocessing
        
        for (const std::string& part : parts) {
            
            // Add the separated words to the vector
            
            words.push_back(part);
            
        }
        
    }
    
    int resishsh = 0;   //Whether queries can be found in files or not
    
    for (int i = 0; i < numberFiles; i++) {
        
        int checkfilename = 0; //Whether queries can be found in the file or not
        
        int filecheck = 0;
        
        for (const auto& w : words) {   //Checks whether words exist in the hashtable
            
            WordItem wordItem = hashTable.findWord(w);
            
            if (!wordItem.word.empty()) {
                
                for (int j = 0; j < wordItem.documentList.size(); j++) {
                    
                    if (wordItem.documentList[j].documentName == filenames[i]) {
                        
                        filecheck += 1;
                        
                    }
                    
                }
                
            }
            
        }
        
        if (filecheck == words.size()) {    //If the words are found in the hashtable, the results will be displayed on the screen.
            
            for (const auto& w : words) {
                
                WordItem wordItem = hashTable.findWord(w);  //Searching queries in the hash table
                
                if (!wordItem.word.empty()) {
                    
                    //The process of displaying the results on the screen
                    
                    for (int j = 0; j < wordItem.documentList.size(); j++) {
                        
                        if (wordItem.documentList[j].documentName == filenames[i]) {
                            
                            resishsh += 1;
                            
                            checkfilename += 1;
                            
                            if (checkfilename == 1) {
                                
                                cout << "in Document " << filenames[i];
                                
                            }
                            
                            cout << ", " << wordItem.word << " found " << wordItem.documentList[j].count << " times";
                            
                        }
                        
                    }
                    
                }
                
            }
            
            if (checkfilename != 0) {
                
                cout << "." << endl;
                
            }
            
        }
        
    }
    
    if (resishsh == 0) {
        
        cout << "No document contains the given query" << endl;
        
    }
    
    int resbin = 0; //Whether queries can be found in files or not
    
    for (int i = 0; i < numberFiles; i++) {
        
        int checkfilename = 0; //Whether queries can be found in the file or not
        
        int filecheck = 0;
        
        for (const auto& w : words) {   //Checks whether words exist in the vector
            
            int index = binarySearch(quickFirst, w);
            
            WordItem wordItem = quickFirst[index];
            
            if (!wordItem.word.empty()) {
                
                for (int j = 0; j < wordItem.documentList.size(); j++) {
                    
                    if (wordItem.documentList[j].documentName == filenames[i]) {
                        
                        filecheck += 1;
                        
                    }
                    
                }
                
            }
            
        }
        
        if (filecheck == words.size()) {    //If the words are found in the vector, the results will be displayed on the screen.
            
            for (const auto& w : words) {
                
                int index = binarySearch(quickFirst, w);
                
                WordItem wordItem = quickFirst[index];
                
                if (!wordItem.word.empty()) {
                    
                    //The process of displaying the results on the screen
                    
                    for (int j = 0; j < wordItem.documentList.size(); j++) {
                        
                        if (wordItem.documentList[j].documentName == filenames[i]) {
                            
                            resbin += 1;
                            
                            checkfilename += 1;
                            
                            if (checkfilename == 1) {
                                
                                cout << "in Document " << filenames[i];
                                
                            }
                            
                            cout << ", " << wordItem.word << " found " << wordItem.documentList[j].count << " times";
                            
                        }
                        
                    }
                    
                }
                
            }
            
            if (checkfilename != 0) {
                
                cout << "." << endl;
                
            }
            
        }
        
    }
    
    if (resbin == 0) {
        
        cout << "No document contains the given query" << endl;
        
    }
    
    int resis = 0;   //Whether queries can be found in files or not
    
    for (int i = 0; i < numberFiles; i++) {
        
        int checkfilename = 0; //Whether queries can be found in the file or not
        
        int filecheck = 0;
        
        for (const auto& w : words) {
            
            WordItem* wordNode = bst.search(w); //Checks whether words exist in the BST
            
            if (wordNode != nullptr) {
                
                for (int j = 0; j < wordNode->documentList.size(); j++) {
                    
                    if (wordNode->documentList[j].documentName == filenames[i]) {
                        
                        filecheck += 1;
                        
                    }
                    
                }
                
            }
            
        }
        
        if (filecheck == words.size()) {    //If the words are found in the BST, the results will be displayed on the screen.
            
            for (const auto& w : words) {
                
                WordItem* wordNode = bst.search(w);  //Searching queries in the tree
                
                if (wordNode != nullptr) {
                    
                    //The process of displaying the results on the screen
                    
                    for (int j = 0; j < wordNode->documentList.size(); j++) {
                        
                        if (wordNode->documentList[j].documentName == filenames[i]) {
                            
                            resis += 1;
                            
                            checkfilename += 1;
                            
                            if (checkfilename == 1) {
                                
                                cout << "in Document " << filenames[i];
                                
                            }
                            
                            cout << ", " << wordNode->word << " found " << wordNode->documentList[j].count << " times";
                            
                        }
                        
                    }
                    
                }
                
            }
            
            if (checkfilename != 0) {
                
                cout << "." << endl;
                
            }
            
        }
        
    }
    
    if (resis == 0) {
        
        cout << "No document contains the given query" << endl;
        
    }
    
    
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 100; i++) {   //Time BST start
        
        //In BST, the time of finding words is measured.
        
        for (int i = 0; i < numberFiles; i++) {
            
            int checkfilename = 0; //Whether queries can be found in the file or not
            
            int filecheck = 0;
            
            for (const auto& w : words) {   //Checks whether words exist in the BST
                
                WordItem* wordNode = bst.search(w);
                
                if (wordNode != nullptr) {
                    
                    for (int j = 0; j < wordNode->documentList.size(); j++) {
                        
                        if (wordNode->documentList[j].documentName == filenames[i]) {
                            
                            filecheck += 1;
                            
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    
    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    cout << "\nBinary Search Tree Time: " << BSTTime.count() / 100 << "\n";
    
    auto startHash = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {   //Time HTT start
        //In HTT, the time of finding words is measured.
        for (int i = 0; i < numberFiles; i++) {
            int checkfilename = 0; //Whether queries can be found in the file or not
            int filecheck = 0;
            for (const auto& w : words) {
                WordItem wordItem = hashTable.findWord(w);
                if (!wordItem.word.empty()) {
                    for (int j = 0; j < wordItem.documentList.size(); j++) {
                        if (wordItem.documentList[j].documentName == filenames[i]) {
                            filecheck += 1;
                        }
                    }
                }
            }
        }
    }
    //Time HTT finish
    auto HTTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startHash);
    cout << "Hash Table Time: " << HTTTime.count() / 100 << "\n";
    
    auto startBinary = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {   //Time Binary start
        //In Binary, the time of finding words is measured.
        for (int i = 0; i < numberFiles; i++) {
            int checkfilename = 0; //Whether queries can be found in the file or not
            int filecheck = 0;
            for (const auto& w : words) {
                int index = binarySearch(quickFirst, w);
                WordItem wordItem = quickFirst[index];
                if (!wordItem.word.empty()) {
                    for (int j = 0; j < wordItem.documentList.size(); j++) {
                        if (wordItem.documentList[j].documentName == filenames[i]) {
                            filecheck += 1;
                        }
                    }
                }
            }
        }
    }
    //Time Binary finish
    auto BinaryTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startBinary);
    cout << "Binary Search Time: " << BinaryTime.count() / 100 << "\n";
    auto startQuickFirst = std::chrono::high_resolution_clock::now();
    
    // Perform Quick Sort (First) once
    quickSortFirst(wordItems, 0, wordItems.size() - 1);
    
    // Calculate the time taken for a single Quick Sort (First) operation
    auto QuickFirstTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startQuickFirst);
    
    // Print Quick Sort (First) Time
    std::cout << "Quick Sort(first) Time: " << QuickFirstTime.count() / 100 << "\n";
    
    auto startQuickRandom = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {   //Time Quick Sort(random) start
        // Sort vector<WordItem> using Quick Sort
        quickSortRandom(wordItems, 0, wordItems.size() - 1);
    }
    //Time Quick Sort(random) finish
    auto QuickRandomTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startQuickRandom);
    cout << "Quick Sort(random) Time: " << QuickRandomTime.count() / 100 << "\n";
    
    
    auto startQuickMedian = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {   //Time Quick Sort(median) start
        // Sort vector<WordItem> using Quick Sort
        quickSortMedian(wordItems, 0, wordItems.size() - 1);
    }
    //Time Quick Sort(median) finish
    auto QuickMedianTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startQuickMedian);
    cout << "\nQuick Sort(median) Time: " << QuickMedianTime.count() / 100 << "\n";
    
    auto startMerge = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {   //Time Merge Sort start
        // Sort vector<WordItem> using Merge Sort
        mergeSort(wordItems, 0, wordItems.size() - 1);
    }
    //Time Merge Sort finish
    auto MergeSortTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startMerge);
    cout << "Merge Sort Time: " << MergeSortTime.count() / 100 << "\n";
    
    auto startHeap = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {   //Time Heap Sort start
        // Sort vector<WordItem> using Heap Sort
        heapSort(wordItems);
    }
    //Time Heap Sort finish
    auto HeapTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startHeap);
    cout << "Heap Sort Time: " << HeapTime.count() / 100 << "\n";
    
    auto startInsertion = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {   //Time Insertion Sort start
        // Sort vector<WordItem> using Insertion Sort
        insertionSort(wordItems);
    }
    //Time Insertion Sort finish
    auto InsertionTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startInsertion);
    cout << "Insertion Sort Time: " << InsertionTime.count() / 100 << "\n";
    
    //Calculating Speed Up
    double speedUp = static_cast<double>(BSTTime.count()) / HTTTime.count();
    cout << "\nSpeed Up BST/HST: " << speedUp << endl;
    
    //Calculating Speed Up
    double speedUpMQ = static_cast<double>(MergeSortTime.count()) / QuickMedianTime.count();
    cout << "Speed Up Merge Sort/Quick Sort(Median): " << speedUpMQ << endl;
    
    double speedUpHQ = static_cast<double>(HeapTime.count()) / QuickMedianTime.count();
    cout << "Speed Up Heap Sort/Quick Sort(Median): " << speedUpHQ << endl;
    
    double speedUpIQ = static_cast<double>(InsertionTime.count()) / QuickMedianTime.count();
    cout << "Speed Up Insertion Sort/Quick Sort(Median): " << speedUpIQ << endl;
    
    double speedUpBST = static_cast<double>(BinaryTime.count()) / BSTTime.count();
    cout << "\nSpeed Up Binary Search / Binary Search Tree Time: " << speedUpBST << endl;
    
    double speedUpHTT = static_cast<double>(BinaryTime.count()) / HTTTime.count();
    cout << "Speed Up Binary Search / Hash Table Time: " << speedUpHTT << endl;
    
    return 0;
}
