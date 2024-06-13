#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>
#include <bitset>
using namespace std;


struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct comp {
    bool operator()(Node* l, Node* r) {
        // highest priority item has lowest frequency
        return l->freq > r->freq;
    }
};

// Traverse the Huffman Tree and store Huffman Codes in a map.
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr)
        return;

    // found a leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Traverse the Huffman Tree and decode the encoded string
void decode(Node* root, int& index, const string& str, ofstream &decodedFile) {
    if (root == nullptr) {
        return;
    }
    if (!root->left && !root->right) {
        decodedFile << root->ch;        // found a leaf node
        return;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str, decodedFile);
    else
        decode(root->right, index, str, decodedFile);
}

// Function to get the size of a file
size_t getFileSize(const string& fileName) {
    ifstream file(fileName, ios::binary | ios::ate);
    return file.tellg();
}

// Utility function to pack encoded binary string into bytes and write to file
void writeEncodedFile(const string& encodedStr, const string& fileName) {
    ofstream encodedFile(fileName, ios::binary);
    if (encodedFile.is_open()) {
        // Convert string of '0's and '1's to bytes
        int size = encodedStr.size();
        for (int i = 0; i < size; i += 8) {
            bitset<8> byte(encodedStr.substr(i, 8));
            encodedFile.put(static_cast<unsigned char>(byte.to_ulong()));
        }
        encodedFile.close();
    } else {
        cerr << "Unable to open file for writing: " << fileName << endl;
    }
}

// Builds Huffman Tree and decode given input text
void buildHuffmanTree(const string& text, const string& encodedFileName, const string& decodedFileName) {
    // count frequency of appearance of each character and store it in a map
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // Create a priority queue to store nodes of 
    priority_queue<Node*, vector<Node*>, comp> pq;

  
for (auto pair : freq) { //node creation for each character
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // do till there is more than one node in the queue
    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();       
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }
    // root stores pointer to root of Huffman Tree
    Node* root = pq.top();

    // traverse the Huffman Tree and store Huffman Codes in a map. Also prints them
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Assign bits to charecters:\n" << '\n';
    for (auto pair : huffmanCode) {
       cout << pair.first << "->" << pair.second<<" ";
    }
    cout<<endl<<endl;

    // create encoded string
    string encodedStr = "";
    for (char ch : text) {
        encodedStr += huffmanCode[ch];
    }
    
    // Write the encoded string to a binary file
    writeEncodedFile(encodedStr, encodedFileName);

    
    // traverse the Huffman Tree again and this time decode the encoded string
    int index = -1;
    ofstream decodedFile(decodedFileName);
    if (decodedFile.is_open()) {
        while (index < (int)encodedStr.size() - 2) {
            decode(root, index, encodedStr, decodedFile);
        }
        decodedFile.close();
    } else {
        cerr << "Unable to open file for writing: " << decodedFileName << endl;
    }

    // Get and display file sizes
    size_t originalSize = text.size();
    size_t encodedSize = getFileSize(encodedFileName);

    cout << "\nOriginal file size: " << originalSize << " bytes" << endl;
    cout << "Encoded file size: " << encodedSize << " bytes" << endl;

    if (encodedSize < originalSize) {
        cout << "File size reduced by " << (originalSize - encodedSize) << " bytes." << endl;
    } else {
        cout << "File size increased by " << (encodedSize - originalSize) << " bytes." << endl;
    }
    
}

// Huffman coding algorithm
int main() {
    // Read input text from a file

    cout<<endl<<"Welcome"<<endl;
    string fname="";
    cout<<"Input file name with .txt"<<endl;
    
    cin>>fname;

    string inputFileName = fname;
    ifstream inputFile(inputFileName);
    string text;

    if (inputFile.is_open()) {
        getline(inputFile, text, '\0'); // Read the entire content of the file
        inputFile.close();
    } else {
        cerr << "Unable to open file: " << inputFileName << endl;
        return 1;
    }

    // Files to write encoded and decoded data
    string encodedFileName = "encoded.bin";
    string decodedFileName = "decoded.txt";
     

    buildHuffmanTree(text, encodedFileName, decodedFileName);
    _getch();
    return 0;
}