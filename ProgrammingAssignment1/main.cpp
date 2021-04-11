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

    // Private Node class: Contains base structure for SimpleList

    private: class Node {

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

    //Protected variable declarations for SimpleList.

    protected:
        int length;
        Node *first;
        Node *last;
        string name;

    //Public functions and function declarations for SimpleList.

    public:

        const string &getName() const {
            return name;
        }

        int getLength() const {
            return length;
        }

        Node *getFirst() const {
            return first;
        }

        void setFirst(Node *first) {
            SimpleList::first = first;
        }

        Node *getLast() const {
            return last;
        }

        void setLast(Node *last) {
            SimpleList::last = last;
        }

        virtual void push(T item) = 0;
        virtual T pop() = 0;
       //virtual T peek() = 0;

};

template <typename T> class Stack: public SimpleList<T> {

    private:
        int length;
        string name;

    public:

        Stack(const string &name) : name(name) {}

        void push(T item) {
//            Node<T> current = this.getFirst();
//            setFirst(new Node(item));
//            setNext(current);
            length++;
        }

        T pop() {
//            Node<T> current = this.getFirst();
//            setFirst(current.getNext());
//            return current.getValue();
            length--;
            return 0;
        }

};

template <typename T> class Queue: public SimpleList<T> {

    private:
        int length;
        string name;

    public:

        Queue(const string &name) : name(name) {}

        void push(T item) {
//            Node<T> current = this.getFirst();
//            setFirst(new Node(item));
//            setNext(current);
            length++;
        }

        T pop() {
//            Node<T> current = this.getFirst();
//            setFirst(current.getNext());
//            return current.getValue();
            length--;
            return 0;
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

template <typename T> SimpleList<T> findObj(string name, list<SimpleList<T>> list) {
    for (SimpleList<T> l : list) {
        if (l.getName()==name) {
            return l;
        }
    }
}

bool checkName(string name, list<string> names) {
    for (string nameInList : names) {
        if (nameInList==name)
            return true;
    }
    return false;
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
    list<string> nameList;
    list<SimpleList<int> *> intList;
    list<SimpleList<double> *> doubleList;
    list<SimpleList<string> *> strList;
    file.open(fileName);
    while (getline(file, read)) {
        writeToFile("PROCESSING COMMAND: "+read, outFile);
        position = read.find(' ');
        component = read.substr(0, position);
        read = read.substr(position+1);
        position = read.find(' ');
        name = read.substr(0, position);
        //cout << component << '\n';
        if (component == "create") {
            if (checkName(name, nameList)) {
                writeToFile("ERROR: This name already exists!", outFile);
                continue;
            }
            nameList.push_front(name);
            //cout << name << '\n';
            read = read.substr(position+1);
            position = read.find(' ');
            component = read.substr(0, position);
            //cout << component << '\n';
            if (component == "stack") {
                if (name.substr(0,1)=="i")
                    intList.push_front(new Stack<int>(name));
                else if (name.substr(0,1)=="d")
                    doubleList.push_front(new Stack<double>(name));
                else if (name.substr(0,1)=="s")
                    strList.push_front(new Stack<string>(name));
            }

            if (component == "queue") {
                nameList.push_front(name);
                if (name.substr(0,1)=="i")
                    intList.push_front(new Queue<int>(name));
                else if (name.substr(0,1)=="d")
                    doubleList.push_front(new Queue<double>(name));
                else if (name.substr(0,1)=="s")
                    strList.push_front(new Queue<string>(name));
            }
        }

        if (component == "push") {
            if (!checkName(name, nameList)) {
                writeToFile("ERROR: This name does not exist!", outFile);
                continue;
            }

            if (name.substr(0,1)=="i") {
                for (SimpleList<int> *l : intList) {
                    if (l.getName()==name) {
                        SimpleList<int> found = l;
                    }
                }
                //SimpleList<int> found = findObj<int>(name, intList);
                found.push(1);
            }
            else if (name.substr(0,1)=="d") {
                SimpleList<double> found = findObj<double>(name, doubleList);
                found.push(1.0);
            }
            else if (name.substr(0,1)=="s") {
                SimpleList<string> found = findObj<string>(name, strList);
                found.push("1");
            }
        }
        if (component == "pop") {
            if (!checkName(name, nameList)) {
                writeToFile("ERROR: This name does not exist!", outFile);
                continue;
            }
        }
    }
    file.close();
};

int main() {
    ofstream file;
    file.open("output1.txt");
    readFile(/*getFileName()*/"commands1.txt", file);
    file.close();
    return 0;
}