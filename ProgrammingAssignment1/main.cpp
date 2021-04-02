#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T> class SimpleList {

    class Node {
        private:
            T value;
            T *next;

        public:
            T getValue() const {
                return value;
            }
            void setValue(T value) {
                Node::value = value;
            }
            T *getNext() const {
                return next;
            }
            void setNext(T *next) {
                Node::next = next;
            }
            Node(T value) : value(value) {

            }
        };

        virtual void push(T item);
        virtual T pop();
        virtual T peek();
        SimpleList() {

        };
    private:
        int length;
        Node *first;
        Node *last;
};

template <typename T> class Stack: public SimpleList<T> {


};

template <typename T> class Queue: public SimpleList<T> {


};

string getFileName() {
    string fileDir;
    cout << "Please type file name: ";
    getline(cin,fileDir);
    return fileDir;
}

void writeToFile(string str, ofstream& file) {
    file << str << "\n";
}

void readFile(string fileName, ofstream& outFile) {
    ifstream file;
    string read;
    file.open(fileName);
    while (getline(file, read)) {
        writeToFile(read, outFile);
    }
    file.close();
};

int main() {
    ofstream file;
    file.open("output1.txt");
    readFile(getFileName(), file);
    file.close();
    return 0;
}