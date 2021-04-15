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

template <typename T> struct Node {
    T value;
    struct Node<T>* next;
    Node (T item) {
        value = item;
    }
};

//SimpleList class: Base structure for Stack and Queue class later.

template <typename T> class SimpleList {

    // Private Node class: Contains base structure for SimpleList

    protected:
        string name;
        int length;
        struct Node<T>* first;
        struct Node<T>* last;

    //Public functions and function declarations for SimpleList.

    public:

        const string &getName() const {
            return name;
        }

        int getLength() const {
            return length;
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
       //virtual T peek() = 0;

};

template <typename T> class Stack: public SimpleList<T> {

    private:
        int length;
        string name;

    public:

        Stack(const string &name) : name(name) {}

        bool isEmpty() {
            return length == 0;
        }

        void push(T item) {
            Node<T>* insertion = new Node<T>(item);
            insertion -> next = this -> getFirst();
            this -> setFirst(insertion);
            length++;
        }

        T pop() {
            Node<T>* extraction = this -> getFirst();
            this -> setFirst(extraction -> next);
            extraction -> next = NULL;
            length--;
            return extraction -> value;
        }

};

template <typename T> class Queue: public SimpleList<T> {

    private:
        int length;
        string name;

    public:

        Queue(const string &name) : name(name) {}

        void push(T item) {
            Node<T>* insertion = new Node<T>(item);

            if (this -> last==NULL) {
                this -> setFirst(insertion);
                this -> setLast(insertion);
                return;
            }

            //this -> last -> next = insertion;

            length++;
        }

        T pop() {
            Node<T>* extraction = this -> getFirst();
            this -> first = this -> first -> next;
            if (this -> first == NULL) {
                this -> last == NULL;
            }
            length--;
            return extraction -> value;
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
    cout << str << "\n";
}

template <typename T> SimpleList<T>* findObj(string name, list<SimpleList<T> *> listOf) {
    for (auto i : listOf) {
        if (i -> getName() == name) {
            return i;
        }
    }
    return listOf.front();
}

bool checkName(string name, list<string> names) {
    for (string &nameInList : names) {
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
            if (component == "stack\r") {
                if (name.substr(0,1)=="i")
                    intList.push_front(new Stack<int>(name));
                else if (name.substr(0,1)=="d")
                    doubleList.push_front(new Stack<double>(name));
                else if (name.substr(0,1)=="s")
                    strList.push_front(new Stack<string>(name));
            }

            if (component == "queue\r") {
                nameList.push_front(name);
                if (name.substr(0,1)=="i")
                    intList.push_front(new Queue<int>(name));
                else if (name.substr(0,1)=="d")
                    doubleList.push_front(new Queue<double>(name));
                else if (name.substr(0,1)=="s")
                    strList.push_front(new Queue<string>(name));
            }
        }

        if (!checkName(name, nameList)) {
            writeToFile("ERROR: This name does not exist!", outFile);
            continue;
        }

        if (component == "push") {

            read = read.substr(position+1);
            position = read.find(' ');
            component = read.substr(0, position);

            if (name.substr(0,1)=="i") {
                SimpleList<int>* list1 = findObj(name, intList);
                list1 -> push(stoi(component));
                continue;
            }

            if (name.substr(0,1)=="d") {
                SimpleList<double>* list2 = findObj(name, doubleList);
                list2 -> push(stod(component));
                continue;
            }

            if (name.substr(0,1)=="s") {
                SimpleList<string>* list3 = findObj(name, strList);
                list3 -> push(component);
                continue;
            }
        }
        if (component == "pop") {

        }
    }
    file.close();
    outFile.close();
};

int main() {
    ofstream file;
    file.open("output1.txt");
    readFile(/*getFileName()*/"commands1.txt", file);
    return 0;
}