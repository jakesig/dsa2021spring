/**Jacob Sigman
 * Programming Assignment 1
 * Professor Sable
 * main.cpp
 */

/**Library initializations:
 * iostream for reading file names.
 * fstream for reading files.
 * string for getting lines from files.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

// Node class: Contains base structure for SimpleList

template <typename T> class Node {

    //Private variable declarations for Node

    private:
        T value;
        Node* next;

    //Public functions for Node

    public:

        //Node Constructor

        Node(T value) : value(value) {}

        //Getters and Setters

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

};

//SimpleList class: Base structure for Stack and Queue class later.

template <typename T> class SimpleList {

    //Protected variable declarations for SimpleList.

    protected:
        int length;
        Node <T> *first;
        Node <T> *last;
        string name;

    //Public functions and function declarations for SimpleList.

    public:

        //SimpleList Constructor

        SimpleList(const string &name) : name(name) {}

        const string &getName() const {
            return name;
        }

        int getLength() const {
            return length;
        }

        void setLength(int length) {
            SimpleList::length = length;
        }

        Node<T> *getFirst() const {
            return first;
        }

        void setFirst(Node<T> *first) {
            SimpleList::first = first;
        }

        Node<T> *getLast() const {
            return last;
        }

        void setLast(Node<T> *last) {
            SimpleList::last = last;
        }

        virtual void push(T item) = 0;
        virtual T pop() = 0;
        virtual T peek() = 0;

};

template <typename T> class Stack: public SimpleList<T> {

    private: string name;

    public:
        Stack(const string &name) : name(name) {}

        void push(T item) {
            Node current = this.getFirst();
            setFirst(new Node(item));
            setNext(current);
        }

        T pop() {
            Node current = this.getFirst();
            setFirst(current.getNext());
            return current.getValue();
        }

};

template <typename T> class Queue: public SimpleList<T> {

    private: string name;

    public:
        Queue(const string &name) : name(name) {}

        void push(T item) {
            Node current = this.getFirst();
            setFirst(new Node(item));
            setNext(current);
        }

        T pop() {
            Node current = this.getFirst();
            setFirst(current.getNext());
            return current.getValue();
        }
};

/** getFileName(): Returns file name that the user inputs.
 *
 * @return {string} The name of the file that the user inputted.
 */

string getFileName() {
    string fileDir;
    cout << "Please type file name: ";
    getline(cin,fileDir);
    return fileDir;
}

/** writeToFile(): A one-line function that writes to the output file opened in main.
 *
 * @param {string} str The string to write to the file.
 * @param {ofstream} file The output that is being written to.
 */

void writeToFile(string str, ofstream& file) {
    file << str << "\n";
}

/**readFile(): Reads from input file and processes the commands inside of it.
 *
 * @param {string} fileName The name of the file to be read from.
 * @param {ofstream} outFile The output that is being written to.
 */

void readFile(string fileName, ofstream& outFile) {
    ifstream file;
    string read;
    string component;
    string name;
    int position;
    int previousPosition;
    list<string> nameList;
    list<SimpleList<int> *> intList;
    list<SimpleList<double> *> doubleList;
    list<SimpleList<string> *> strList;
    file.open(fileName);
    while (getline(file, read)) {
        writeToFile(read, outFile);
        position = read.find(' ');
        component = read.substr(0, position);
        if (component == "create") {

        }
        if (component=="push") {

        }
        if (component=="pop") {

        }
    }
    file.close();
};

bool checkName(string name, list<string> names) {
    for (string nameInList : names) {
        if (nameInList==name)
            return true;
    }
    return false;
}

int main() {
    ofstream file;
    file.open("output1.txt");
    readFile(getFileName(), file);
    file.close();
    return 0;
}