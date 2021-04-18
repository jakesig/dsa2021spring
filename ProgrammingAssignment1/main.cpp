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
             *  Additionally increment the length.
             */

            if (isEmpty()) {
                last = first = new Node(newNode);
                length++;
                return;
            }

            /** Perform the insertion of the first node at the start
             *  by making a new node with the next pointer pointing to
             *  the first node, and the first pointer pointing to the
             *  new node. Additionally increment the length.
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
             *  Additionally increment the length.
             */

            if (isEmpty()) {
                last = first = new Node(newNode);
                length++;
                return;
            }

            /** Perform the insertion of the last node at the end
             *  by reassigning the existing last node's next pointer
             *  to a new node and replacing the existing last pointer
             *  with the new node. Additionally increment the length.
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

            /** Case 3: If the SimpleList has more than one item, set the first
             *  pointer to its next pointer.
             */

            else {
                first = first->next;
            }

            /** Deallocate the memory for the node removed, decrement the length
             *  and return the value stored in the removed node.
             */

            delete(extraction);
            length--;
            return returnVal;
        }

        /** Abstract methods to be implemented in subclasses of SimpleList.
         */

        virtual void push(T item) = 0;
        virtual T pop() = 0;

};

/** Stack class used in the implementation.
 *
 *  @tparam T
 */

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

/** Queue class used in the implementation.
 *
 *  @tparam T
 */

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
 *  @param {string} name The name of the SimpleList to look for.
 *  @param {map<string, SimpleList<int> *>} intMap The map containing integers to search.
 *  @param {map<string, SimpleList<double> *>} doubleMap The map containing doubles to search.
 *  @param {map<string, SimpleList<string> *>} strMap The map containing strings to search.
 */

bool checkName(string key, map<string, SimpleList<int> *> intMap, map<string, SimpleList<double> *> doubleMap, map<string, SimpleList<string> *> strMap) {
    return (intMap.find(key)!=intMap.end()) || (doubleMap.find(key)!=doubleMap.end()) || (strMap.find(key)!=strMap.end());
}

/** readFile(): Reads from input file and processes the commands inside of it.
 *
 *  @param {ifstream} inFile The input file that is being read from.
 *  @param {ofstream} outFile The output that is being written to.
 */

void readFile(ifstream& inFile, ofstream& outFile) {

    /** Variable initializations for the function.
     *  read - A string that will contain each line read from the input file.
     *  processed[3] - An array of strings containing each component of read.
     *  component1 - A string containing the first component of read.
     *  name - A string containing the second component of read (or the name of the Stack/Queue).
     *  component3 - A string containing the third component of read (if there is one).
     *  type - A character containing the type of each Stack/Queue (or the first character of the name).
     *  intMap - A map containing the name of each integer Stack/Queue and the Stack/Queue itself.
     *  doubleMap - A map containing the name of each double Stack/Queue and the Stack/Queue itself.
     *  stringMap - A map containing the name of each string Stack/Queue and the Stack/Queue itself.
     */

    string read;
    string processed[3];
    string component1;
    string name;
    string component3;
    char type;
    map<string, SimpleList<int> *> intMap;
    map<string, SimpleList<double> *> doubleMap;
    map<string, SimpleList<string> *> strMap;

    /** Main loop for reading each line of the input file.
     */

    while (getline(inFile, read)) {

        outFile <<"PROCESSING COMMAND: " << read << "\n";

        /** Divide each component of the command using the split() function
         *  defined above, giving the corresponding variables their values.
         */

        split(read, processed);
        component1 = processed[0];
        name = processed[1];
        type = name.at(0);
        component3 = processed[2];

        /** First condition: If the value stored in component1 is "create",
         *  create a new Stack/Queue based on what is in component3.
         */

        if (component1 == "create") {

            /** Check if the name stored already exists and if it does, output
             *  to the file, and move along to process the next line.
             */

            if (checkName(name, intMap, doubleMap, strMap)) {
                outFile << "ERROR: This name already exists!" << "\n";
                continue;
            }

            /** If the value stored in component3 is "stack", create a new stack based on its type,
             *  using a switch-case statement.
             */

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

            /** If the value stored in component3 is "queue", create a new queue based on its type,
             *  using a switch-case statement.
             */

            if (component3 == "queue") {
                switch (type) {
                    case 'i':
                        intMap.insert(pair<string, SimpleList<int> *>(name, new Queue<int>()));
                    case 'd':
                        doubleMap.insert(pair<string, SimpleList<double> *>(name, new Queue<double>()));
                    case 's':
                        strMap.insert(pair<string, SimpleList<string> *>(name, new Queue<string>()));
                    default:
                        break;
                }
            }
        }

        /** Second condition: If the value stored in component1 is "push",
         *  push the value of respective type in component3 onto the Stack/Queue
         *  using a switch-case statement.
         */

        if (component1 == "push") {

            /** Check if the name stored already exists and if it does not, output
             *  to the file, and move along to process the next line.
             */

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

        /** Third condition: If the value stored in component1 is "pop",
         *  pop the value of the Stack/Queue specified using a switch-case statement.
         *  At the beginning of each case, check if the Stack/Queue is empty, and
         *  if it is, output to the file, and move along to process the next line.
         */

        if (component1 == "pop") {

            /** Check if the name stored already exists and if it does not, output
             *  to the file, and move along to process the next line.
             */

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

    /** Close both the output and input file.
     */

    inFile.close();
    outFile.close();
};

/** main() method.
 *
 * @return 0
 */

int main() {

    /** Create and open both an output file and input file,
     *  prompting the user for names of both using getFileName().
     */

    ofstream outFile;
    ifstream inFile;
    cout << "Output";
    outFile.open(getFileName());
    cout << "Input";
    inFile.open(getFileName());

    /** Process the commands of the input file, outputting to the output
     *  file using the readFile() function.
     */

    readFile(inFile, outFile);

    /** Return 0.
     */

    return 0;
}