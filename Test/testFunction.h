#include "../main.cpp"
#include <string>
#include <fstream>
#include <queue>
using namespace std;

void readFile(string fileName, queue<string> &in)
{
    if (!in.empty())
    {
        cout << "queue -in- is not empty." << endl;
    }
    fstream file("../Test/" + fileName, ios::in);
    if (!file.is_open())
        cout << "not open"<< endl;
    string read;
    while (getline(file, read))
    {
        in.push(read);
    }
    file.close();
}

void functionCommand(queue<string> &in, AVL_Tree &AVL)
{
    istringstream stream(in.front());
    string input, name, ID, output;
    in.pop();
    getline(stream, input, ' ');

    if (input == "insert") {
        getline(stream, name, ' ');
        getline(stream, ID, ' ');

        name = name.substr(1, name.length() - 2);
        AVL.insert(stoi(ID), name);
    } else if (input == "search") {
        getline(stream, input, ' ');
        try {
            int ID2 = stoi(input);
            AVL.searchID(ID2);
        } catch (exception e) {
            name = input;
            name = name.substr(1, name.length() - 2);
            AVL.searchName(name);
        }
    } else if (input == "printLevelCount") {
        AVL.printLevelCount();
    } else if (input == "printInorder") {
        output.clear();
        AVL.printInOrder(output);
        output = output.substr(0, output.length() - 2);
        cout << output << endl;
    } else if (input == "printPreorder") {
        output.clear();
        AVL.printPreOrder(output);
        output = output.substr(0, output.length() - 2);
        cout << output << endl;
    } else if (input == "printPostorder") {
        output.clear();
        AVL.printPostOrder(output);
        output = output.substr(0, output.length() - 2);
        cout << output << endl;
    } else if (input == "remove") {
        getline(stream, ID, ' ');
        AVL.remove(stoi(ID));
    } else if (input == "removeInorder") {
        getline(stream, input, ' ');
        AVL.removeInorder(stoi(input));
    } else {
        cout << "Hay!!!!!!!" << endl;
    }
}



//use nodeCount to test if insert successful.
int test_insert()
{
    queue<string> in;
    AVL_Tree AVL;
    int count = 0;
    readFile("test1.txt", in);
    while (!in.empty())
    {
        functionCommand(in, AVL);
    }
    AVL.UNIT_TEST_NodeCount(AVL.getRoot(), count);
    return count;
}

int test_remove()
{
    queue<string> in;
    AVL_Tree AVL;
    int count = 0;
    readFile("test2.txt", in); //insert 100, remove 99.
    while (!in.empty())
    {
        functionCommand(in, AVL);
    }
    AVL.UNIT_TEST_NodeCount(AVL.getRoot(), count);

    return count;
}

int test_removeInorder()
{
    queue<string> in;
    AVL_Tree AVL;
    int count = 0;
    readFile("test3.txt", in); //insert 30, (removeInorder 0) * 20.
    while (!in.empty())
    {
        functionCommand(in, AVL);
    }
    AVL.UNIT_TEST_NodeCount(AVL.getRoot(), count);

    return count;
}

int test_insert_RootNode()
{
    queue<string> in;
    AVL_Tree AVL;
    int count = 0;
    readFile("test4.txt", in); //insert 10, return correct root node.
    while (!in.empty())
    {
        functionCommand(in, AVL);
    }

    return AVL.getRoot()->gatorID;
}

int test_remove_RootNode()
{
    queue<string> in;
    AVL_Tree AVL;
    int count = 0;
    readFile("test5.txt", in); //insert 10, remove root, return new root.
    while (!in.empty())
    {
        functionCommand(in, AVL);
    }

    return AVL.getRoot()->gatorID;
}