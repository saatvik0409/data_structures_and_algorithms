#include <iostream>

class Node{
    public:
        Node(long long int value){
            this->data = value;
        }
        Node* left {nullptr};
        Node* right {nullptr};
        Node* parent {nullptr};
        long long int data {};
};

class BinaryTree{
    public:
        Node* root {nullptr};
};

BinaryTree* Insert(BinaryTree* inp_binary_tree, long int value){
    Node* newNode = new Node(value);
    if (inp_binary_tree->root==nullptr){
        inp_binary_tree->root=newNode;
    }else{
        Node* current_node = inp_binary_tree->root;
        while (true){
            if (current_node->data < newNode->data){
                if(current_node->right!=nullptr){
                    current_node=current_node->right;
                }else{
                    current_node->right = newNode;
                    newNode->parent= current_node;
                    break;
                }
            }else{
                if (current_node->left!=nullptr){
                    current_node = current_node->left;
                }else{
                    current_node->left = newNode;
                    newNode->parent=current_node;
                    break;
                }
            }
        }
    }
    std::cout << std::endl << "......Node Inserted succesfully......." << std::endl; 
    std::cout << std::endl;
    return inp_binary_tree;
}

void Search(BinaryTree* inp_binary_tree, long int value){
    bool isfound {false};
    Node* root = inp_binary_tree->root;
    while (root!=nullptr){
        if (value > root->data){
            root=root->right;
        }else if (value < root->data){
            root = root->left;
        }else{
            std::cout << std::endl << "Found the node with value " << value << std::endl;
            isfound = true;
            break;
        }
    }
    if (!isfound){
        std::cout << std::endl << "Node not found!" << std::endl;
    }
    return;
}

BinaryTree* Delete(BinaryTree* inp_binary_tree){
    Node* root = inp_binary_tree->root;
    bool entered {false};
    if (root==nullptr){
        std::cout << std::endl << "Binary tree is empty, deletion not possible!" << std::endl;
        return inp_binary_tree;
    }
    while(root->right!=nullptr || root->left!=nullptr){
        entered=true;
        if (root->right == nullptr && root->left != nullptr){
            root=root->left;
        }else{
            root=root->right;
        }
    }
    if (entered){
        if (root == root->parent->left){
            root->parent->left = nullptr;
            delete root;
        }else{
            root->parent->right= nullptr;
            delete root;
        }
    }else{
        delete root;
        inp_binary_tree->root=nullptr;
    }
    return inp_binary_tree;
}

BinaryTree* Creator(){
    long long int num_nodes {};
    long long int value {};
    BinaryTree* inp_binary_tree = new BinaryTree;
    std::cout << std::endl;
    std::cout << "Enter the number of nodes in the tree : "; 
    std::cin >> num_nodes;
    std::cout << std::endl;
    for (int i {}; i < num_nodes;i++){
        std::cout << "Enter Node value : ";
        std::cin >> value;
        inp_binary_tree = Insert(inp_binary_tree,value);
    }
    return inp_binary_tree;
}

void inorder_traversal(Node* inp_node){
    if (inp_node== nullptr){
        return; 
    }else{
        inorder_traversal(inp_node->left);
        std::cout << inp_node->data << " ";
        inorder_traversal(inp_node->right);
    }
}

void caller(){
    std::cout << std::endl;
    std::cout << "Lets start by creating a binary tree! " << std::endl;
    BinaryTree* inp_binary_tree = Creator();
    std::cout << std::endl;
    std::cout << "Great, let's try out some operations now!" << std::endl;
    int options {};
    while (true){
        std::cout << std::endl;
        std::cout << "1. To insert a new node : " << std::endl;
        std::cout << "2. To search for a node : " << std::endl;
        std::cout << "3. To delete a node     : " << std::endl;
        std::cout << "4. To print the tree    : " << std::endl;
        std::cout << std::endl;
        std::cout << "Enter an option : ";
        std::cin >> options;
        int value{};
        switch(options){
            case 1:
                std::cout << std::endl << "Enter a value to be inserted : ";
                std::cin >> value;
                inp_binary_tree=Insert(inp_binary_tree,value);
                break;
            case 2:
                std::cout << std::endl << "Enter a value to be searched : ";
                std::cin >> value;
                Search(inp_binary_tree,value);
                break;               
            case 3:
                inp_binary_tree = Delete(inp_binary_tree);
                break;
            case 4:
                inorder_traversal(inp_binary_tree->root);
                break;
        }
    }
}

int main(){

    caller();

    return 0;
}