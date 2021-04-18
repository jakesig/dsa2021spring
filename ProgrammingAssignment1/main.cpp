/** Jacob Sigman
 *  Programming Assignment 1
 *  Professor Sable
 *  main.cpp
 */

/** Library initializations:
 *  iostream for reading file names.
 *  fstream for reading files.
 *  string for getting lines from files.
 *  map for holding the Stacks and Queues.
 *  sstream for processing the lines of the input file.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

/** SimpleList class: Base structure for Stack and Queue class later.
 */

template <typename T> class SimpleList {

    /** Private Node struct: Contains base structure for SimpleList
     */

    private:
        struct Node {

            /** Public variables for SimpleList:
             *  value - Contains the value stored in the Node.
             *  next - Contains a pointer to another Node.
             */

            public:
                T value;
                struct Node* next;

            public:

                /** Node(): Initializes a node with value item
                 *  and next node next.
                 *
                 *  @param {T} item The value the node will hold.
                 *  @param {Node*} next The pointer of the next node.
                 */

                Node (T item, Node* next) {
                    value = item;
                    this -> next = next;
                }

                /** Node(): Initializes a node with value item
                 *  and next node null.
                 *
                 *  @param {T} item The value the node will hold.
                 */

                Node (T item) {
                    value = item;
                    this -> next = nullptr;
                }
        };

    /** Protected variables for SimpleList:
     *  length - Contains the length of the SimpleList.
     *  first - Contains a pointer to the first element of the SimpleList.
     *  last - Contains a pointer to the last element of the SimpleList.
     */

    protected:
        int length;
        struct Node* first;
        struct Node* last;

    public:

        /** SimpleList(): Creates a new SimpleList object with length of 0
         *  and the first and last pointer pointing to null.
         */

        SimpleList() {
            length = 0;
            first = nullptr;
            last = nullptr;
        }

        /** isEmpty(): Returns true if SimpleList contains no values.
         *
         *  @return {bool} Whether or not the list contains no values.
         */

        bool isEmpty () {
            return length == 0;
        }

        /** insertStart(): Inserts Node at the start of a SimpleList.
         *
         *  @param {T} newNode The value the node being inserted contains.
         */

        void insertStart(T newNode) {

            /** Base case: If the list is empty, set the first and
             *  last pointer equivalent to the node inputted.
             */

            if (isEmpty()) {
                last = first = new Node(newNode);
                length++;
                return;
            }

            /** Perform the insertion of the first node at the start
             *  by making a new node with the next pointer pointing to
             *  the first node, and the first pointer pointing to the
             *  new node.
             */

            auto insertion = new Node(newNode, first);
            first = insertion;
            length++;
        }

        /** insertEnd(): Inserts Node at the end of a SimpleList.
         *
         *  @param {T} newNode The value the node being inserted contains.
         */

        void insertEnd(T newNode) {

            /** Base case: If the list is empty, set the first and
             *  last pointer equivalent to the node inputted.
             */

            if (isEmpty()) {
                last = first = new Node(newNode);
                length++;
                return;
            }

            /** Perform the insertion of the last node at the end
             *  by reassigning the existing last node's next pointer
             *  to a new node and replacing the existing last pointer
             *  with the new node.
             */

            auto insertion = new Node(newNode);
            last -> next = insertion;
            last = insertion;
            length++;
        }

        /** removeStart(): Removes Node from the start of a SimpleList
         *
         *  @return {T} The value the node being removed contains.
         */

        T removeStart() {

            /** Case 1: If the SimpleList is empty, return 0.
             */

            if (isEmpty()) {
                return 0;
            }

            /** Create a value holding the value in the first pointer.
             */

            auto extraction = first;
            T returnVal = extraction -> value;

            /** Case 2: If the SimpleList has one item, set the first
             *  and last pointer to null.
             */

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

        /** Abstract methods to be implemented in subclasses of SimpleList.
         */

        virtual void push(T item) = 0;
        virtual T pop() = 0;

};

template <typename T> class Stack: public SimpleList<T> {

    using SimpleList<T>::SimpleList;

    public:

        /** push(): Inserts item at the top of a Stack.
         *
         *  @param {T} item The value to push onto the Stack.
         */

        void push(T item) {
            this -> insertStart(item);
        }

        /** pop(): Removes and returns item from the top of a Stack.
         *
         *  @return {T} The value popped from the Stack.
         */

        T pop() {
            return this -> removeStart();
        }

};

template <typename T> class Queue: public SimpleList<T> {

    using SimpleList<T>::SimpleList;

    public:

        /** push(): Inserts item at the front of a Queue.
         *
         *  @param {T} item The value to insert in the Queue.
         */

        void push(T item) {
            this -> insertEnd(item);
        }

        /** pop(): Removes and returns item at the end of the Queue.
         *
         *  @return {T} The value removed from the Queue.
         */

        T pop() {
            return this -> removeStart();
        }
};

/** getFileName(): Returns file name that the user inputs.
 *
 *  @return {string} The name of the file that the user inputted.
 */

string getFileName() {
    string fileDir;
    cout << " file name: ";
    getline(cin,fileDir);
    return fileDir;
}

/** split(): Returns an array of strings divided by a space character.
 *
 *  @param {string} str The string to split up.
 *  @param {string} output[] The array output of the divided string.
 */

void split(string str, string output[]) {
    stringstream stream(str);
    stream >> output[0];
    stream >> output[1];
    if (output[0] == "pop")
        return;
    stream >> output[2];
}

/** checkName(): Checks each map to see if there is a key containing a name of a SimpleList.
 *
 *  @param {string} name  The name of the SimpleList to look for.
 *  @param {map<string, SimpleList<int> *>} intMap The map containing integers to search.
 *  @param {map<string, SimpleList<double> *>} doubleMap The map containing doubles to search.
 *  @param {map<string, SimpleList<string> *>} strMap The map containing strings to search.
 */

bool checkName(string key, map<string, SimpleList<int> *> intMap, map<string, SimpleList<double> *> doubleMap, map<string, SimpleList<string> *> strMap) {
    return (intMap.find(key)!=intMap.end()) || (doubleMap.find(key)!=doubleMap.end()) || (strMap.find(key)!=strMap.end());
}

/** readFile(): Reads from input file and processes the commands inside of it.
 *
 *  @param {string} fileName The name of the file to be read from.
 *  @param {ofstream} outFile The output that is being written to.
 */

void readFile(string fileName, ofstream& outFile) {
    ifstream file;
    string read;
    string component1;
    string name;
    string component3;
    string processed[3];
    char type;
    map<string, SimpleList<int> *> intMap;
    map<string, SimpleList<double> *> doubleMap;
    map<string, SimpleList<string> *> strMap;
    file.open(fileName);
    while (getline(file, read)) {
        outFile <<"PROCESSING COMMAND: " << read << "\n";
        split(read, processed);
        component1 = processed[0];
        name = processed[1];
        type = name.at(0);
        component3 = processed[2];
        if (component1 == "create") {
            if (checkName(name, intMap, doubleMap, strMap)) {
                outFile << "ERROR: This name already exists!" << "\n";
                continue;
            }

            if (component3 == "stack") {
                switch (type) {
                    case 'i':
                        intMap.insert(pair<string, SimpleList<int> *>(name, new Stack<int>()));
                        break;
                    case 'd':
                        doubleMap.insert(pair<string, SimpleList<double> *>(name, new Stack<double>()));
                        break;
                    case 's':
                        strMap.insert(pair<string, SimpleList<string> *>(name, new Stack<string>()));
                        break;
                    default:
                        break;
                }
            }

            if (component3 == "queue") {
                if (name.substr(0,1)=="i")
                    intMap.insert(pair<string, SimpleList<int> *>(name, new Queue<int>()));
                else if (name.substr(0,1)=="d")
                    doubleMap.insert(pair<string, SimpleList<double> *>(name, new Queue<double>()));
                else if (name.substr(0,1)=="s")
                    strMap.insert(pair<string, SimpleList<string> *>(name, new Queue<string>()));
            }
        }

        if (component1 == "push") {
            if (!checkName(name, intMap, doubleMap, strMap)) {
                outFile << "ERROR: This name does not exist!" << "\n";
                continue;
            }

            switch (type) {
                case 'i':
                    intMap[name] -> push(stoi(component3));
                    break;
                case 'd':
                    doubleMap[name] -> push(stod(component3));
                    break;
                case 's':
                    strMap[name] -> push(component3);
                    break;
                default:
                    break;
            }
        }
        if (component1 == "pop") {
            if (!checkName(name, intMap, doubleMap, strMap)) {
                outFile << "ERROR: This name does not exist!" << "\n";
                continue;
            }

            switch (type) {
                case 'i':
                    if (intMap[name] -> isEmpty()) {
                        outFile << "ERROR: This list is empty!" << "\n";
                        break;
                    }
                    outFile << "Value popped: " << intMap[name] -> pop() << "\n";
                    break;
                case 'd':
                    if (doubleMap[name] -> isEmpty()) {
                        outFile << "ERROR: This list is empty!" << "\n";
                        break;
                    }
                    outFile << "Value popped: " << doubleMap[name] -> pop() << "\n";
                    break;
                case 's':
                    if (strMap[name] -> isEmpty()) {
                        outFile << "ERROR: This list is empty!" << "\n";
                        break;
                    }
                    outFile << "Value popped: " << strMap[name] -> pop() << "\n";
                    break;
                default:
                    break;
            }
        }
    }
    file.close();
    outFile.close();
};

int main() {
    ofstream file;
    cout << "Output";
    file.open(getFileName());
    cout << "Input";
    readFile(getFileName(), file);
    return 0;
}