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

        bool isEmpty () {
            return length == 0;
        }

        virtual void push(T item) = 0;
        virtual T pop() = 0;

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
                return;
            }
            auto insertion = new Node(newNode, first);
            first = insertion;
            length++;
        }

        void insertEnd(T newNode) {
            if (length == 0) {
                last = first = new Node(newNode);
                length++;
                return;
            }
            auto insertion = new Node(newNode);
            last -> next = insertion;
            last = insertion;
            length++;
        }

        T removeStart() {
            if (length == 0) {
                return 0;
            }
            auto extraction = first;
            T returnVal = extraction -> value;
            if (length == 1) {
                first = last = nullptr;
            }
            else {
                first = first->next;
            }
            length--;
            delete(extraction);
            return returnVal;
        }

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

bool checkName(string key, map<string, SimpleList<int> *> intMap, map<string, SimpleList<double> *> doubleMap, map<string, SimpleList<string> *> strMap) {
    return (intMap.find(key)!=intMap.end()) || (doubleMap.find(key)!=doubleMap.end()) || (strMap.find(key)!=strMap.end());
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
        outFile <<"PROCESSING COMMAND: " << read << "\n";
        position = read.find(' ');
        component = read.substr(0, position);
        read = read.substr(position+1);
        position = read.find(' ');
        if (component == "create") {
            name = read.substr(0, position);
            if (checkName(name, intMap, doubleMap, strMap)) {
                outFile << "ERROR: This name already exists!" << "\n";
                continue;
            }
            nameList.push_front(name);
            read = read.substr(position+1);
            position = read.find(' ');
            component = read.substr(0, read.find('\n'));
            if (component == "stack") {
                if (name.substr(0,1)=="i")
                    intMap.insert(std::pair<string, SimpleList<int> *>(name, new Stack<int>()));
                else if (name.substr(0,1)=="d")
                    doubleMap.insert(std::pair<string, SimpleList<double> *>(name, new Stack<double>()));
                else if (name.substr(0,1)=="s")
                    strMap.insert(std::pair<string, SimpleList<string> *>(name, new Stack<string>()));
            }

            if (component == "queue") {
                nameList.push_front(name);
                if (name.substr(0,1)=="i")
                    intMap.insert(std::pair<string, SimpleList<int> *>(name, new Queue<int>()));
                else if (name.substr(0,1)=="d")
                    doubleMap.insert(std::pair<string, SimpleList<double> *>(name, new Queue<double>()));
                else if (name.substr(0,1)=="s")
                    strMap.insert(std::pair<string, SimpleList<string> *>(name, new Queue<string>()));
            }
        }

        if (component == "push") {
            name = read.substr(0, position);
            if (!checkName(name, intMap, doubleMap, strMap)) {
                outFile << "ERROR: This name does not exist!" << "\n";
                continue;
            }
            read = read.substr(position+1);
            position = read.find(' ');
            component = read.substr(0, position);

            if (name.substr(0,1)=="i") {
                intMap[name] -> push(stoi(component));
                continue;
            }

            if (name.substr(0,1)=="d") {
                doubleMap[name] -> push(stod(component));
                continue;
            }

            if (name.substr(0,1)=="s") {
                strMap[name] -> push(component);
                continue;
            }
        }
        if (component == "pop") {
            name = read.substr(0, read.find('\n'));
            if (!checkName(name, intMap, doubleMap, strMap)) {
                outFile << "ERROR: This name does not exist!" << "\n";
                continue;
            }
            if (name.substr(0,1)=="i") {
                if (intMap[name]-> isEmpty()) {
                    outFile << "ERROR: This list is empty!" << "\n";
                    continue;
                }
                outFile << "Value popped: " << intMap[name] -> pop() << "\n";
                continue;
            }

            if (name.substr(0,1)=="d") {
                if(doubleMap[name] -> isEmpty()) {
                    outFile << "ERROR: This list is empty!" << "\n";
                    continue;
                }
                outFile << "Value popped: " << doubleMap[name] -> pop() << "\n";
                continue;
            }

            if (name.substr(0,1)=="s") {
                if(strMap[name] -> isEmpty()) {
                    outFile << "ERROR: This list is empty!" << "\n";
                    continue;
                }
                outFile << "Value popped: " << strMap[name] -> pop() << "\n";
                continue;
            }
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