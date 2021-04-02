#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
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

void readFile(string fileName) {
    ifstream file;
    string out;
    file.open(fileName);
    while (getline(file, out)) {
        cout << out;
    }
    file.close();
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    readFile("C:\\cygwin64\\home\\jsigm\\dsa2021spring\\ProgrammingAssignment1\\commands1.txt");
    return 0;
}