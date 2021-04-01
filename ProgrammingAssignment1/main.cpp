#include <iostream>
using namespace std;

template <typename T> class SimpleList {
    private:
        int length;
        Node *first;
        Node *last;
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

    public:
        virtual void push(T item);
        virtual T pop();
        virtual T peek();
        SimpleList() {

        };
}

template <typename T> class Stack: public SimpleList<T> {


};

template <typename T> class Queue: public SimpleList<T> {


};

void readFile(char[] filename) {

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}