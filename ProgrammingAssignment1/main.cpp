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
#include <map>

using namespace std;

//SimpleList class: Base structure for Stack and Queue class later.

template <typename T> class SimpleList {

    // Private Node class: Contains base structure for SimpleList
    private:
        struct Node {
            T value;
            struct Node* next;
            Node (T item, Node* next) {
                value = item;
                this -> next = next;
            }

            Node (T item) {
                value = item;
                this -> next = nullptr;
            }

        };

    protected:
        int length;
        struct Node* first;
        struct Node* last;

    //Public functions and function declarations for SimpleList.

    public:

        SimpleList() {
            first = nullptr;
            last = nullptr;
            length = 0;
        }

        int getLength() const {
            return length;
        }

    protected:

        Node *getFirst() const {
            return first;
        }

        void setFirst(Node *first) {
            SimpleList::first = first;
        }

        void insertStart(T newNode) {
            if (length == 0) {
                last = first = new Node(newNode);
                length++;
                cout << "Inserting at start..." << "\n";
                cout << "First Pointer: " << first -> value << "\n";
                cout << "Last Pointer: " << last -> value << "\n";
                cout << "---------------------------" << "\n";
                return;
            }
            auto insertion = new Node(newNode, first);
            first = insertion;
            length++;
            cout << "Inserting at start..." << "\n";
            cout << "First Pointer: " << first -> value << "\n";
            cout << "Last Pointer: " << last -> value << "\n";
            cout << "---------------------------" << "\n";
        }

        void insertEnd(T newNode) {
            if (length == 0) {
                last = first = new Node(newNode);
                length++;
                cout << "Inserting at start..." << "\n";
                cout << "First Pointer: " << first -> value << "\n";
                cout << "Last Pointer: " << last -> value << "\n";
                cout << "---------------------------" << "\n";
                return;
            }
            auto insertion = new Node(newNode);
            last -> next = insertion;
            last = insertion;
            length++;
            cout << "Inserting at end..." << "\n";
            cout << "First Pointer: " << first -> value << "\n";
            cout << "Last Pointer: " << last -> value << "\n";
            cout << "---------------------------" << "\n";
        }

        T removeStart() {
            if (length == 0) {
                cout << "dumdum" << "\n";
                return NULL;
            }
            auto extraction = first;
            T returnVal = extraction -> value;
            if (length == 1) {
                first = last = nullptr;
                cout << "Removed " << returnVal << " from start..." << "\n";
                cout << "Size: " << length << "\n";
                cout << "---------------------------" << "\n";
            }
            else {

                first = first->next;
                cout << "Removed " << returnVal << " from start..." << "\n";
                cout << "First Pointer: " << first->value << "\n";
                cout << "Last Pointer: " << last->value << "\n";
                cout << "Size: " << length << "\n";
                cout << "---------------------------" << "\n";
            }
            length--;
            delete(extraction);
            return returnVal;
        }

        bool isEmpty () {
            return length == 0;
        }

        virtual void push(T item) = 0;
        virtual T pop() = 0;

};

template <typename T> class Stack: public SimpleList<T> {

    public:
        void push(T item) {
            this -> insertStart(item);
        }

        T pop() {
            return this -> removeStart();
        }

};

template <typename T> class Queue: public SimpleList<T> {

    private:
        int length;
        string name;

    public:

        void push(T item) {
            this -> insertEnd(item);
        }

        T pop() {
            return this -> removeStart();
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
    map<string, SimpleList<int> *> intMap;
    map<string, SimpleList<double> *> doubleMap;
    map<string, SimpleList<string> *> strMap;
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
                    intMap.insert(std::pair<string, SimpleList<int> *>(name, new Stack<int>()));
                else if (name.substr(0,1)=="d")
                    doubleMap.insert(std::pair<string, SimpleList<double> *>(name, new Stack<double>()));
                else if (name.substr(0,1)=="s")
                    strMap.insert(std::pair<string, SimpleList<string> *>(name, new Stack<string>()));
            }

            if (component == "queue\r") {
                nameList.push_front(name);
                if (name.substr(0,1)=="i")
                    intMap.insert(std::pair<string, SimpleList<int> *>(name, new Queue<int>()));
                else if (name.substr(0,1)=="d")
                    doubleMap.insert(std::pair<string, SimpleList<double> *>(name, new Queue<double>()));
                else if (name.substr(0,1)=="s")
                    strMap.insert(std::pair<string, SimpleList<string> *>(name, new Queue<string>()));
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
//                SimpleList<int>* list1 = findObj(name, intList);
//                list1 -> push(stoi(component));
//                continue;
            }

            if (name.substr(0,1)=="d") {
//                SimpleList<double>* list2 = findObj(name, doubleList);
//                list2 -> push(stod(component));
//                continue;
            }

            if (name.substr(0,1)=="s") {
//                SimpleList<string>* list3 = findObj(name, strList);
//                list3 -> push(component);
//                continue;
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