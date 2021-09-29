#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string>
#include <queue>
#include <iostream>
#include <vector>
using namespace std;

class AVL_Tree
{
    struct Node
    {
        int gatorID;
        string name;
        Node* left;
        Node* right;
        int balanceFactor;
        Node(int ID, string name) : gatorID(ID), left(nullptr), right(nullptr), balanceFactor(0), name(name){}
    };
    Node* root;
    //private functions
    Node* insertFunction(int ID, string name, Node* rootNode);
    Node* inOrderPrint(Node* node, string &output);
    Node* preOrderPrint(Node* node, string &output);
    Node* postOrderPrint(Node* node, string &output);
    Node* searchNode(Node* node, int ID);
    Node* searchNodeByName(Node* node, string name, vector<Node*> &v);
    Node* deleteHelper(Node* root);
    Node* leftRotate(Node* node);
    Node* rightRotate(Node* node);
    int height(Node* node); // this function is check the height of node itself, not balance factor, do (node->left - node->right) for balance factor of the node.
    int getBalanceFactor(Node* node);
    Node* autoBalance(Node* rootNode); //balance function using for both insert and remove function.
    Node* searchFatherNode(Node* node, Node* currentNode);
    Node* remove(Node* node, int ID);
    Node* removeInorder(Node* node, int N, int &count);
    Node* removeFunction(Node* node);
    void updateBalanceFactor(Node* node);
    Node* autoBalanceV2(Node* node);

public:
    AVL_Tree();
    ~AVL_Tree();
    Node* getRoot();
    void insert(int ID, string name);
    void printInOrder(string &output);
    void printPreOrder(string &output);
    void printPostOrder(string &output);
    void searchID(int ID);
    void searchName(string name);
    void printLevelCount();
    void remove(int ID);
    void removeInorder(int N);
    void UNIT_TEST_NodeCount(Node* node, int &count);
};


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

//class function
AVL_Tree::AVL_Tree()
{
    root = nullptr;
}

AVL_Tree::~AVL_Tree()
{
    deleteHelper(root);
}

//delete all node, build for destructor.
AVL_Tree::Node *AVL_Tree::deleteHelper(Node* root) {
    if (!root)
        return nullptr;

    if (root->left)
        deleteHelper(root->left);
    if (root->right)
        deleteHelper(root->right);

    delete root;
}

//insert node.
AVL_Tree::Node * AVL_Tree::insertFunction(int ID, string name, Node* rootNode) {
    if (!rootNode)
    {
        cout << "successful" << endl;
        return new Node(ID, name);
    }

    if (rootNode->gatorID < ID) //base on project instruction, there will be no equal situation.
    {
        rootNode->right = insertFunction(ID, name, rootNode->right);
    }
    else
    {
        rootNode->left = insertFunction(ID, name, rootNode->left);
    }

    //calculate balance factor.
    rootNode->balanceFactor = getBalanceFactor(rootNode); // check if there is any unbalance condition.

    //balance if this tree is unbalanced.
    rootNode = autoBalance(rootNode);

    return rootNode;
}

//public version of insert function.
void AVL_Tree::insert(int ID, string name) {
    root = insertFunction(ID, name, root);
}

AVL_Tree::Node *AVL_Tree::leftRotate(Node* node) {
//         o (node)
//        / \
//       o   o (node_right)
//          / \
//  (no_ri_le) o
//              \
//               o <-(insert node)
    Node* node_right = node->right;
    Node* node_right_left = node_right->left; // if there is no node, it will become nullptr.
    node_right->left = node; // move root to left side of a node.
    //     o (node)
//        / \
//       o   o (node_right)
//        \   \
//  (no_ri_le) o <-(insert node)
    node->right = node_right_left;
    return node_right;
}

//check height of current node, if want to check balance factor, do (node->left - node->right).
int AVL_Tree::height(AVL_Tree::Node *node) {
    int left = 0, right = 0;
    if (!node)
        return 0;
    left+= height(node->left) + 1;
    right+= height(node->right) + 1;
    return left > right ? left : right; //return the largest height.
}

//public function for get root only.
AVL_Tree::Node *AVL_Tree::getRoot() {
    return root;
}

//check left rotate notation for detail.
AVL_Tree::Node *AVL_Tree::rightRotate(AVL_Tree::Node *node) {
//         o (node
//        / \
//       o   o
//      / \
//     o empty
//    /
//   o (insert node)
    Node* node_left = node->left;
    Node* node_left_right = node_left->right;
    node_left->right = node;
    node->left = node_left_right;
    return node_left;
}

AVL_Tree::Node *AVL_Tree::inOrderPrint(AVL_Tree::Node *node, string &output) {
    if (!node)
        return nullptr;
    //left - root - right
    inOrderPrint(node->left, output);
    output.append(node->name);
    output.append(", ");
    inOrderPrint(node->right, output);
    return node;
}

//public version. in all test, the start root cannot be 0;
void AVL_Tree::printInOrder(string &output) {
    inOrderPrint(getRoot(), output);
}

//public version of search node.
void AVL_Tree::searchID(int ID) {
    Node* temp = searchNode(root, ID);
    if (temp)
    {
        cout << temp->name << endl;
    }
    else
    {
        cout << "unsuccessful" << endl;
    }
}

//node - left - right
AVL_Tree::Node *AVL_Tree::preOrderPrint(AVL_Tree::Node *node, string &output) {
    if (!node)
        return nullptr;
    output.append(node->name);
    output.append(", ");

    preOrderPrint(node->left, output);
    preOrderPrint(node->right, output);
    return node;
}

//public version
void AVL_Tree::printPreOrder(string &output) {
    preOrderPrint(getRoot(), output);
}

//left - right - node
AVL_Tree::Node *AVL_Tree::postOrderPrint(AVL_Tree::Node *node, string &output) {
    if (!node)
        return nullptr;

    postOrderPrint(node->left, output);
    postOrderPrint(node->right, output);

    output.append(node->name);
    output.append(", ");
    return node;
}

//use recursion and ID to find a node.
AVL_Tree::Node *AVL_Tree::searchNode(AVL_Tree::Node *node, int ID) {
    if (!node)
        return nullptr;
    if (node->gatorID == ID)
        return node;

    node = node->gatorID > ID ? searchNode(node->left, ID) : searchNode(node->right,ID);

    return node;
}

//public version
void AVL_Tree::printPostOrder(string &output) {
    postOrderPrint(getRoot(), output);
}

//use recursion to find node by name, there may be same name but different ID.
AVL_Tree::Node *AVL_Tree::searchNodeByName(AVL_Tree::Node *node, string name, vector<Node*> &v) {
    if (!node)
        return nullptr;
    if (node->name == name)
        v.push_back(node);

    searchNodeByName(node->left, name, v);
    searchNodeByName(node->right, name, v);

    return node;
}

//public version
void AVL_Tree::searchName(string name) {
    vector<Node*> v;
    searchNodeByName(getRoot(), name, v);
    if (!v.empty())
    {
        for (int i = 0; i < v.size(); ++i) {
            cout << v.at(i)->gatorID <<endl;
        }
    }
    else
        cout << "unsuccessful" << endl;
    v.clear();
}

void AVL_Tree::printLevelCount() {
    cout << height(getRoot()) << endl;
}

AVL_Tree::Node *AVL_Tree::autoBalance(Node* rootNode) {
    while (rootNode->balanceFactor > 1 || rootNode->balanceFactor < -1)
    {
        if (rootNode->balanceFactor > 1) //left heavy, right rotate.
        {
            if (rootNode->left->balanceFactor > 0)
                return rightRotate(rootNode);
            rootNode->left = leftRotate(rootNode->left);
            rootNode->left->balanceFactor = getBalanceFactor(rootNode);
        }
        else //left rotate
        {
            if (rootNode->right->balanceFactor < 0)
                return leftRotate(rootNode);
            rootNode->right = rightRotate(rootNode->right);
            rootNode->right->balanceFactor = getBalanceFactor(rootNode);
        }
    }
    return rootNode;
}

//use recursion to find father node.
AVL_Tree::Node *AVL_Tree::searchFatherNode(AVL_Tree::Node* node, Node* currentNode) {
    if (!node->left && !node->right)
        return nullptr;
    if (node->right == currentNode || node->left == currentNode)
        return node;

    node = node->gatorID > currentNode->gatorID ? searchFatherNode(node->left, currentNode) : searchFatherNode(node->right,currentNode);

    return node;
}

AVL_Tree::Node *AVL_Tree::remove(AVL_Tree::Node* node, int ID) {
    if (!node)
        return nullptr;

    if (node->gatorID > ID)
    {
        node->left = remove(node->left, ID);
    } else if (node->gatorID < ID)
    {
        node->right = remove(node->right, ID);
    } else
    {
        node = removeFunction(node); //delete node.
    }
    node = autoBalanceV2(node); //check balance of all node below node.
    return node;
}

void AVL_Tree::remove(int ID) {
    Node* temp = searchNode(getRoot(), ID);
    if (temp)
    {
        root = remove(getRoot(), ID);
        cout << "successful" << endl;
    } else
    {
        cout << "unsuccessful" << endl;
        cout << ID<< endl;
    }
}

//use recursion to remove node inorder.
AVL_Tree::Node *AVL_Tree::removeInorder(AVL_Tree::Node* node, int N, int &count) { // N is input index, N is the node need to be deleted, count start at -1.
    Node* temp = nullptr;
    if (!node || count == N)
        return nullptr;


    node->left = removeInorder(node->left, N, count);
    count++;

    if (count == N) { //find!!
        return removeFunction(node);
    }

    node->right = removeInorder(node->right, N, count);

    node = autoBalanceV2(node); //check balance after every delete.

    return node;
}

//public version
void AVL_Tree::removeInorder(int N)
{
    int count = -1; // index start from 0.
    Node* temp = removeInorder(getRoot(), N, count);
    if (!(count < N))
    {
        root = temp;
        cout << "successful" << endl;
    } else
    {
        cout << "unsuccessful" << endl;
    }
}

int AVL_Tree::getBalanceFactor(AVL_Tree::Node* node) {
    return height(node->left) - height(node->right);
}

//this function for both remove and removeInorder.
AVL_Tree::Node *AVL_Tree::removeFunction(AVL_Tree::Node* node) {
    Node* temp = nullptr;
    Node* temp2 = nullptr;
    if (node->left && node->right) //two children.
    {
        if (node->right->left) //smallest in inorder
        {
            temp = node->right;
            while (temp->left)
            {
                temp = temp->left; //find smallest in the right side of node.
            }
            node->gatorID = temp->gatorID; //copy data
            node->name = temp->name; //copy data
            temp2 = searchFatherNode(node, temp); //find it is father node.
            if (temp->right) //special case, if there is a node in the right side of smallest node.
            {
                Node* temp3 = temp->right;
                temp2->left = nullptr;
                temp3->right = temp2; //move the father node's right to temp3's right, and replace temp3 to father node's right.

                Node* temp4 = searchFatherNode(getRoot(), temp2);

                if (temp4->left == temp2)
                    temp4->left = temp3;
                else
                    temp4->right = temp3;

            } else
            {
                temp2->left = nullptr;
            }
            delete temp;
        } else { //there is no right node, just copy it's data and delete it.
            temp = node->right;
            node->gatorID = node->right->gatorID;
            node->name = node->right->name;
            node->right = node->right->right;
            delete temp;
        }
    } else if (node->left) { //only left node.
        temp = node->left;
        node->gatorID = temp->gatorID;
        node->name = temp->name;
        node->left = temp->left;
        delete temp;
    } else if (node->right) { //only right node.
        temp = node->right;
        node->gatorID = temp->gatorID;
        node->name = temp->name;
        node->right = temp->right;
        delete temp;
    } else { //no children.
        node = nullptr;
    }
    return node;
}

//update all balance factor below this node.
void AVL_Tree::updateBalanceFactor(AVL_Tree::Node* node) {
    if (node)
    {
        node->balanceFactor = getBalanceFactor(node); //update balance factor.

        if (node->left)
            updateBalanceFactor(node->left); //recursion
        if (node->right)
            updateBalanceFactor(node->right); //recursion
    }
}

//use recursion to balance all node.
AVL_Tree::Node* AVL_Tree::autoBalanceV2(AVL_Tree::Node* node)
{
    if (!node)
        return nullptr;
    if (!node->left && !node->right) // if there are no children, don't need to do rotate.
        return node;

    updateBalanceFactor(node); //check every time after any rotate.
    if (node->left)
        node->left = autoBalanceV2(node->left); //recursion
    updateBalanceFactor(node);
    if (node->right)
        node->right = autoBalanceV2(node->right); //recursion
    updateBalanceFactor(node);

    node = autoBalance(node); //rotate, if balance factor is in normal range, it return original node.

    return node;
}

void AVL_Tree::UNIT_TEST_NodeCount(AVL_Tree::Node* node, int &count)
{
    if (node)
    {
        count ++;
        if (node->left)
            UNIT_TEST_NodeCount(node->left, count);
        if (node->right)
            UNIT_TEST_NodeCount(node->right, count);
    }

}
