#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../main.cpp"
#include <string>
#include <queue>
using namespace std;

void functionCommand(queue<string> &in, AVL_Tree &AVL);
int test_insert();
int test_remove();
int test_removeInorder();
int test_insert_RootNode();
int test_remove_RootNode();

TEST_CASE("test_insert")
{
    //insert 100;
    REQUIRE(test_insert() == 10);
}

TEST_CASE("test_remove")
{
    //insert 100 and remove 99.
    REQUIRE(test_remove() == 1);
}

TEST_CASE("test_removeInorder")
{
    //insert 30 and (removeInorder 0) * 20.
    REQUIRE(test_removeInorder() == 5);
}

TEST_CASE("test_root_afterInsert")
{
    //insert 10 node and calculate root by hand. return gatorID.
    REQUIRE(test_insert_RootNode() == 45005211);
}

TEST_CASE("test_root_afterRemove")
{
    //insert 10 node and remove the root node, calculate new root by hand. return gatorID.
    REQUIRE(test_remove_RootNode() == 53455736);
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

    //pushing
    in.push("insert \"Milissa\" 14289383");
    in.push("insert \"Sima\" 46930886");
    in.push("insert \"Carolynn\" 71692777");
    in.push("insert \"Jannie\" 14636915");
    in.push("insert \"Vickie\" 77747793");
    in.push("insert \"Zane\" 74238335");
    in.push("insert \"Max\" 99885386");
    in.push("insert \"Travis\" 39760492");
    in.push("insert \"Ruthanne\" 66516649");
    in.push("insert \"Josphine\" 29641421");

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
    //insert 10, remove 9.
    in.push("insert \"Milissa\" 14289383");
    in.push("insert \"Sima\" 46930886");
    in.push("insert \"Carolynn\" 71692777");
    in.push("insert \"Jannie\" 14636915");
    in.push("insert \"Vickie\" 77747793");
    in.push("insert \"Zane\" 74238335");
    in.push("insert \"Max\" 99885386");
    in.push("insert \"Travis\" 39760492");
    in.push("insert \"Ruthanne\" 66516649");
    in.push("insert \"Josphine\" 29641421");
    in.push("remove 14289383");
    in.push("remove 46930886");
    in.push("remove 71692777");
    in.push("remove 14636915");
    in.push("remove 77747793");
    in.push("remove 74238335");
    in.push("remove 99885386");
    in.push("remove 39760492");
    in.push("remove 66516649");

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
    //insert 10, (removeInorder 0) * 5.
    in.push("insert \"Milissa\" 14289383");
    in.push("insert \"Sima\" 46930886");
    in.push("insert \"Carolynn\" 71692777");
    in.push("insert \"Jannie\" 14636915");
    in.push("insert \"Vickie\" 77747793");
    in.push("insert \"Zane\" 74238335");
    in.push("insert \"Max\" 99885386");
    in.push("insert \"Travis\" 39760492");
    in.push("insert \"Ruthanne\" 66516649");
    in.push("insert \"Josphine\" 29641421");
    in.push("removeInorder 4");
    in.push("removeInorder 2");
    in.push("removeInorder 1");
    in.push("removeInorder 0");
    in.push("removeInorder 0");
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
    //insert 10, return correct root node.
    in.push("insert \"Scot\" 44089172");
    in.push("insert \"Denyse\" 53455736");
    in.push("insert \"Matilda\" 45005211");
    in.push("insert \"Queen\" 81595368");
    in.push("insert \"Corrine\" 34702567");
    in.push("insert \"Talia\" 26956429");
    in.push("insert \"Giovanna\" 76465782");
    in.push("insert \"Shonda\" 61021530");
    in.push("insert \"Willodean\" 18722862");
    in.push("insert \"Sarita\" 63665123");

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
    //insert 10, remove root, return new root.
    in.push("insert \"Scot\" 44089172");
    in.push("insert \"Denyse\" 53455736");
    in.push("insert \"Matilda\" 45005211");
    in.push("insert \"Queen\" 81595368");
    in.push("insert \"Corrine\" 34702567");
    in.push("insert \"Talia\" 26956429");
    in.push("insert \"Giovanna\" 76465782");
    in.push("insert \"Shonda\" 61021530");
    in.push("insert \"Willodean\" 18722862");
    in.push("insert \"Sarita\" 63665123");
    in.push("remove 45005211");

    while (!in.empty())
    {
        functionCommand(in, AVL);
    }

    return AVL.getRoot()->gatorID;
}