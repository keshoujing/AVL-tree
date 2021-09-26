#include <iostream>
#include <vector>
#include <typeinfo>

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
    Node* autoBalance(Node* rootNode); //balance function using for both insert and remove function.
    Node* searchFatherNode(Node* node, Node* currentNode);
    Node* remove(Node* node, int ID);
    Node* removeInorder(Node* node, int N, int &count);
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
};

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
    rootNode->balanceFactor = height(rootNode->left) - height(rootNode->right); // check if there is any unbalance condition.

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

//public version.
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
    v.clear(); // clear all the node inside vector for next time using this function.
}

void AVL_Tree::printLevelCount() {
    cout << height(getRoot()) << endl;
}

/*void AVL_Tree::removeID(int ID) {
    Node* node = searchNode(getRoot(), ID);
    Node* temp = nullptr;
    if (node->left && node->right)
    {
        if (node->right->left) // there is a left node
        {
            temp = node->right;
            node->right->left->left = node->left;
            node->gatorID = node->right->gatorID;
            node->name = node->right->name;
            node->left = node->right->left;
            node->right = node->right->right;
            delete temp;
        } else // there is no left node
        {
            temp = node->right;
            node->gatorID = node->right->gatorID;
            node->name = node->right->name;
            node->right = node->right->right;
            delete temp;
        }
    } else if (node->left) // only left node
    {
        temp = node->left;
        node->gatorID = node->left->gatorID;
        node->name = node->left->name;
        node->left = nullptr;
        delete temp;
    } else if (node->right)// only right node
    {
        temp = node->right;
        node->gatorID = node->right->gatorID;
        node->name = node->right->name;
        node->right = nullptr;
        delete temp;
    } else
    {
        temp = searchFatherNode(getRoot(), ID); //father node of node.
        if (temp->right->gatorID == ID)
        {
            temp->right = nullptr;
        } else
        {
            temp->left = nullptr;
        }
        delete node;
    }
}*/

AVL_Tree::Node *AVL_Tree::autoBalance(Node* rootNode) {
    while (rootNode->balanceFactor > 1 || rootNode->balanceFactor < -1)
    {
        if (rootNode->balanceFactor > 1) //left heavy, right rotate.
        {
            if (rootNode->left->balanceFactor > 0)
                return rightRotate(rootNode);
            rootNode->left = leftRotate(rootNode->left);
            rootNode->left->balanceFactor = height(rootNode->left) - height(rootNode->right);
        }
        else //left rotate
        {
            if (rootNode->right->balanceFactor < 0)
                return leftRotate(rootNode);
            rootNode->right = rightRotate(rootNode->right);
            rootNode->right->balanceFactor = height(rootNode->left) - height(rootNode->right);
        }
    }
    return rootNode;
}

AVL_Tree::Node *AVL_Tree::searchFatherNode(AVL_Tree::Node* node, Node* currentNode) {
    if (!node->left && !node->right)
        return nullptr;
    if (node->right == currentNode || node->left == currentNode)
        return node;

    node = node > currentNode ? searchFatherNode(node->left, currentNode) : searchFatherNode(node->right,currentNode);

    return node;
}

AVL_Tree::Node *AVL_Tree::remove(AVL_Tree::Node* node, int ID) {
    Node* temp = nullptr;
    if (!node)
        return nullptr;

    if (node->gatorID > ID)
    {
        node = remove(node->left, ID);
    } else if (node->gatorID < ID)
    {
        node = remove(node->right, ID);
    } else //find the node that need to be delete.
    {
        if (node->left && node->right) //two children.
        {
            if (node->right->left) //smallest in inorder
            {
                temp = node->right;
                node->right->left->left = node->left;
                node->gatorID = node->right->gatorID;
                node->name = node->right->name;
                node->left = node->right->left;
                node->right = node->right->right;
                delete temp;
            } else
            {
                temp = node->right;
                node->gatorID = node->right->gatorID;
                node->name = node->right->name;
                node->right = node->right->right;
                delete temp;
            }
        } else if (node->left)
        {
            temp = node->left;
            node->gatorID = node->left->gatorID;
            node->name = node->left->name;
            node->left = nullptr;
            delete temp;
        } else if (node->right)
        {
            temp = node->right;
            node->gatorID = node->right->gatorID;
            node->name = node->right->name;
            node->right = nullptr;
            delete temp;
        } else
        {
            temp = searchFatherNode(getRoot(), node); //father node of node.
            if (temp->right->gatorID == ID)
            {
                temp->right = nullptr;
            } else
            {
                temp->left = nullptr;
            }
            delete node;
            return temp;
        }
    }

    node->balanceFactor = height(node->left) - height(node->right);

    node = autoBalance(node);

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
    }
}

AVL_Tree::Node *AVL_Tree::removeInorder(AVL_Tree::Node* node, int N, int &count) {
    Node* temp = nullptr;
    if (!node || count == N)
        return nullptr;


    removeInorder(node->left, N, count);
    count++;

    if (count == N) {
        if (node->left && node->right) //two children.
        {
            if (node->right->left) //smallest in inorder
            {
                temp = node->right;
                node->right->left->left = node->left;
                node->gatorID = node->right->gatorID;
                node->name = node->right->name;
                node->left = node->right->left;
                node->right = node->right->right;
                delete temp;
            } else {
                temp = node->right;
                node->gatorID = node->right->gatorID;
                node->name = node->right->name;
                node->right = node->right->right;
                delete temp;
            }
        } else if (node->left) {
            temp = node->left;
            node->gatorID = node->left->gatorID;
            node->name = node->left->name;
            node->left = nullptr;
            delete temp;
        } else if (node->right) {
            temp = node->right;
            node->gatorID = node->right->gatorID;
            node->name = node->right->name;
            node->right = nullptr;
            delete temp;
        } else {
            temp = searchFatherNode(getRoot(), node); //father node of node.
            if (temp->right == node) {
                temp->right = nullptr;
            } else {
                temp->left = nullptr;
            }
            delete node;
        }
        return node;
    }

    removeInorder(node->right, N, count);

    node->balanceFactor = height(node->left) - height(node->right);

    node = autoBalance(node);

    if (count < N)
        return nullptr;
    return node;
}

void AVL_Tree::removeInorder(int N)
{
    int count = -1; // index start from 0.
    Node* temp = removeInorder(getRoot(), N, count);

    if (temp)
    {
        root = temp;
        cout << "successful" << endl;
    } else
    {
        cout << "unsuccessful" << endl;
    }
}


int main() {
    AVL_Tree AVL;
    int firstInput = 0;
    cin >> firstInput;
    string input = "", name = "", output = "";
    int ID = 0;
    for (int i = 0; i < firstInput; ++i) {
        cin >> input;
        if (input == "insert")
        {
            cin >> name;
            cin >> ID;
            name = name.substr(1, name.length() - 2);
            AVL.insert(ID, name);
        } else if (input == "search")
        {
            cin >> input;
            try {
                ID = stoi(input);
                AVL.searchID(ID);
            }catch (exception e)
            {
                name = input;
                name = name.substr(1, name.length() - 2);
                AVL.searchName(name);
            }
        } else if (input == "printLevelCount")
        {
            AVL.printLevelCount();
        } else if (input == "printInorder")
        {
            output.clear();
            AVL.printInOrder(output);
            output = output.substr(0, output.length() - 2);
            cout << output << endl;
        } else if (input == "printPreorder")
        {
            output.clear();
            AVL.printPreOrder(output);
            output = output.substr(0, output.length() - 2);
            cout << output << endl;
        } else if (input == "printPostorder")
        {
            output.clear();
            AVL.printPostOrder(output);
            output = output.substr(0, output.length() - 2);
            cout << output << endl;
        } else if (input == "remove")
        {
            cin >> ID;
            AVL.remove(ID);
        } else if (input == "removeInorder")
        {
            cin >> input;
            AVL.removeInorder(stoi(input));
        } else
        {
            cout << "Hay!!!!!!!" << endl;
        }
    }

    return 0;
}
