#include <iostream>

class Node{
    public:
        Node(long long int data,long long int num_children){
            this->data = data;
            this->num_children = num_children;
        }

        long long int data{};
        long long int num_children{};
        Node* head {nullptr};
        Node* parent {nullptr};
        Node* next {};
        Node* tail {};
};

class unb_tree{
    public:
        Node* root {nullptr};
};

Node* creator(Node* parent){
    int value {};
    int num_children {};
    
    std::cout << std::endl << "Enter the value of node : ";
    std::cin >> value;

    std::cout << "Enter the number of children : ";
    std::cin >> num_children;

    Node* newNode = new Node(value, num_children);
    newNode->parent = parent;

    std::cout << std::endl << "Node created with address : " << newNode << "; and value = " << newNode->data << std::endl;
    for (int i {}; i < num_children;i++){
        std::cout << std::endl << "Enter details for child " << (i+1) << " (of " << newNode << "[" << newNode->data<<"]) : " << std::endl;
        Node* child_node_address = creator(newNode);
        if (newNode!=nullptr){
            if (newNode->tail == nullptr){
                newNode->head = child_node_address;
                newNode->tail = child_node_address;
            }else{
                newNode->tail->next = child_node_address;
                newNode->tail = child_node_address;
            }
        }
        std::cout << std::endl;
        continue;
    }

    std::cout << std::endl; 
    return newNode;
};

void printer(Node* parent){
    if (parent==nullptr){
        return;
    }
    std::cout << std::endl << "Value of current node : " << parent->data << std::endl;
    std::cout << "Address of current node : " << parent << std::endl;
    std::cout << std::endl;

    if (parent->num_children > 0){
        std::cout << std::endl << "Now we will print out each child : " << std::endl;
    }
    Node* current_node = parent->head;
    int i{};
    while (current_node!=nullptr){
        std::cout << "Child " << i+1 << " value : " << current_node->data << std::endl;
        std::cout << "Child " << i+1 << " address : " << current_node << std::endl;
        std::cout << std::endl;
        current_node=current_node->next;
        i++;
    }
    std::cout << std::endl << "We will now print out details for each child individually" << std::endl;
    
    current_node = parent->head;
    while (current_node!=nullptr){
        printer(current_node);
        current_node=current_node->next;
    }
 
    return;
}

int main(){

    unb_tree* tree = new unb_tree;
    tree->root = creator(nullptr);
    printer(tree->root);
    return 0;
}