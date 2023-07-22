#include <iostream>
#include <chrono>

class Node{
    public:
        Node(int value){
            this->data = value;
        }
        int data {};
        Node* left {};
        Node* right {};
        Node* parent {};
        int left_count {};
        int right_count {};
        int balance_factor{};
};

class avl_tree{
    public:
        Node* root {};
};

int max(int a, int b){
    if (a>b){return a;} else{return b;}
}

int* reset_directions(int* directions){
    *directions = 0;
    *(directions+1) = 0;
    return directions;
}

int* update_directions(int direction, int* direcitons){
    int copy_var;
    copy_var = *(direcitons);
    *(direcitons) = direction;
    *(direcitons+1) = copy_var;
    return direcitons;
}

Node* balance(Node* current_root_node, avl_tree* tree, int* direcitons,Node* parent){
    // std::cout << "at the first line of balance function" << std::endl; 
    int dir1 = *(direcitons);
    int dir2 = *(direcitons+1);
    Node* rep_child {};
    Node* newRootNode  {};
    Node* rep_child2{};
    int final_h {};
    // std::cout << "at the 49 line of balance function" << std::endl; 
    // std::cout << "Dir1 : " << dir1 << "; Dir2 : " << dir2 << std::endl;
    if (dir1 == 1 && dir2 == 1){
        // std::cout << "Entered LL Rotation !" << std::endl;
        rep_child = current_root_node->left->right;
        newRootNode = current_root_node->left;
        newRootNode->right = current_root_node;
        current_root_node->parent = newRootNode;
        current_root_node->left = rep_child;
        if (rep_child!=nullptr){
            rep_child->parent = current_root_node;
            newRootNode->right->left_count = max(rep_child->left_count,rep_child->right_count)+1;
        }else{newRootNode->right->left_count=0;}
        newRootNode->right->balance_factor = newRootNode->right->left_count-newRootNode->right->right_count;
        int left_node_h = max(newRootNode->left->left_count,newRootNode->left->right_count)+1;
        int right_node_h =max(newRootNode->right->left_count,newRootNode->right->right_count)+1;
        // std::cout << "right_node_h : " << right_node_h << std::endl;
        // std::cout << "left_node_h : " << left_node_h << std::endl;
        final_h = max(left_node_h,right_node_h);
        newRootNode->left_count=left_node_h;
        newRootNode->right_count = right_node_h;
        newRootNode->balance_factor = newRootNode->left_count-newRootNode->right_count;
    }else if (dir1 == 2 && dir2 == 2){
        // std::cout << "Entered the second if statement" << std::endl;
        rep_child = current_root_node->right->left;
        newRootNode = current_root_node->right;
        newRootNode->left = current_root_node;
        current_root_node->parent = newRootNode;
        current_root_node->right = rep_child;  
        if (rep_child!=nullptr){
            rep_child->parent = current_root_node;
            newRootNode->left->right_count = max(rep_child->left_count,rep_child->right_count)+1;
        }else{newRootNode->left->right_count=0;}
        newRootNode->left->balance_factor = newRootNode->left->left_count-newRootNode->left->right_count;
        int left_node_h = max(newRootNode->left->left_count,newRootNode->left->right_count)+1;
        int right_node_h =max(newRootNode->right->left_count,newRootNode->right->right_count)+1;
        final_h = max(left_node_h,right_node_h);
        newRootNode->left_count=left_node_h;
        newRootNode->right_count = right_node_h;
        newRootNode->balance_factor = newRootNode->left_count-newRootNode->right_count;
    }else if (dir1 == 1 && dir2 == 2){
        // std::cout << "Entered the if statement" << std::endl;
        rep_child = current_root_node->left->right->left;
        rep_child2 = current_root_node->left->right->right;
        newRootNode = current_root_node->left->right;
        newRootNode->left = current_root_node->left;
        newRootNode->right = current_root_node;
        newRootNode->left->parent = newRootNode;
        newRootNode->right->parent = newRootNode;
        if (rep_child!=nullptr){
            rep_child->parent = newRootNode->left;
            int left_child_count = max(rep_child->left_count,rep_child->right_count)+1;
            newRootNode->left->right_count = left_child_count;
        }else{newRootNode->left->right_count=0;}
        newRootNode->left->right = rep_child;
        newRootNode->left->balance_factor = newRootNode->left->left_count-newRootNode->left->right_count;

        if (rep_child2!=nullptr){
            rep_child2->parent = newRootNode->right;
            int right_child_count = max(rep_child2->left_count,rep_child2->right_count)+1;
            newRootNode->right->left_count = right_child_count;
        }else{newRootNode->right->left_count = 0;}
        newRootNode->right->left = rep_child2;
        newRootNode->right->balance_factor = newRootNode->right->left_count - newRootNode->right->right_count;

        int left_count = max(newRootNode->left->left_count,newRootNode->left->right_count)+1;
        int right_count = max(newRootNode->right->left_count,newRootNode->right->right_count)+1;
        newRootNode->left_count= left_count;
        newRootNode->right_count= right_count;
        final_h = max(left_count,right_count);
        newRootNode->balance_factor = left_count-right_count;

    }else if (dir1 == 2 && dir2 == 1){
        rep_child = current_root_node->right->left->left;
        rep_child2 = current_root_node->right->left->right;
        newRootNode = current_root_node->right->left;
        newRootNode->right = current_root_node->right;
        newRootNode->left = current_root_node;
        newRootNode->left->parent = newRootNode;
        newRootNode->right->parent = newRootNode;
        if (rep_child!=nullptr){
            rep_child->parent = newRootNode->left;
            int left_child_count = max(rep_child->left_count,rep_child->right_count)+1;
            newRootNode->left->right_count = left_child_count;
        }else{newRootNode->left->right_count=0;}
        newRootNode->left->right = rep_child;
        newRootNode->left->balance_factor = newRootNode->left->left_count-newRootNode->left->right_count;

        if (rep_child2!=nullptr){
            rep_child2->parent = newRootNode->right;
            int right_child_count = max(rep_child2->left_count,rep_child2->right_count)+1;
            newRootNode->right->left_count = right_child_count;
        }else{newRootNode->right->left_count = 0;}
        newRootNode->right->left = rep_child2;
        newRootNode->right->balance_factor = newRootNode->right->left_count - newRootNode->right->right_count;
        
        int left_count = max(newRootNode->left->left_count,newRootNode->left->right_count)+1;
        int right_count = max(newRootNode->right->left_count,newRootNode->right->right_count)+1;
        newRootNode->left_count= left_count;
        newRootNode->right_count= right_count;
        final_h = max(left_count,right_count);
        newRootNode->balance_factor = left_count-right_count;
    }
    if (parent!=nullptr){
        if (parent->left == current_root_node){
            newRootNode->parent =parent;
            parent->left=newRootNode;
        }else{
            newRootNode->parent=parent;
            parent->right=newRootNode;
        }
    }else{
        tree->root = newRootNode;
        newRootNode->parent=nullptr;
    }
    return newRootNode;
}

int current_height_finder(Node* inp_node){
    return max(inp_node->left_count,inp_node->right_count);
}

void printer(Node* parent){

    if (parent==nullptr){
        return;
    }
    std::cout << std::endl << "Value of current node : " << parent->data << std::endl;
    std::cout << "Address of current node : " << parent << std::endl;
    std::cout << std::endl;

    std::cout << "Children of current node : " << std::endl;
    std::cout << "Left child  : " << parent->left;
    if (parent->left!=nullptr){
        std::cout << " (" << parent->left->data << ")";
    }
    std::cout << std::endl;
    std::cout << "Right child : " << parent->right;
    if (parent->right!=nullptr){
        std::cout << " (" << parent->right->data << ")";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    printer(parent->left);
    printer(parent->right);
    return;
}

void inorder_traversal(Node* root){
    if (root==nullptr){
        return;
    }else{
        inorder_traversal(root->left);
        std::cout << root->data << " ";
        inorder_traversal(root->right);
    }

}

avl_tree* creator(){
    int num_nodes {};
    int value {};
    int* directions = new int[2] {};
    std::cout << std::endl << "Enter the number of nodes you want to insert : ";
    std::cin >> num_nodes;
    std::cout << std::endl;
    avl_tree* tree = new avl_tree;
    int values[num_nodes] {};

    for (int i {}; i < num_nodes;i++){
        std::cout << "Enter the value of node " << (i+1) << " : ";
        std::cin >> values[i];
    }
    auto beg = std::chrono::steady_clock::now();
    for (int i {}; i < num_nodes;i++){
        value = values[i];
        Node* current_node = tree->root;
        Node* newNode = new Node(value);
        if (current_node==nullptr){
            tree->root=newNode;
        }else{
            while(true){
                if (newNode->data > current_node->data && current_node->right!=nullptr){
                    current_node=current_node->right;
                }else if (newNode->data <= current_node->data && current_node->left!=nullptr){
                    current_node=current_node->left;
                }else if (newNode->data > current_node->data){
                    current_node->right = newNode;
                    newNode->parent=current_node;
                    break;
                }else{
                    current_node->left = newNode;
                    newNode->parent = current_node;
                    break;
                }
            }
            current_node=newNode->parent;
            int current_height {1};
            if (newNode==current_node->left){
                *directions = 1;
            }else{
                *directions = 2;
            }
            // std::cout << "here" << std::endl;
            int new_height {};
            while(current_node!=nullptr){
                if (*(directions) == 1){
                    if (current_height > current_node->left_count){
                        current_node->left_count = current_height;
                        current_node->balance_factor = current_node->left_count - current_node->right_count;
                        if (current_node->balance_factor > 1 || current_node->balance_factor < -1){
                            // balance();
                            // std::cout << "Balance Factor has been exceeded by 1 at node : " << current_node << " (" << current_node->data << ")" << std::endl;
                            // std::cout << "The balance factor is : " << current_node->balance_factor << std::endl; 
                            // std::cout << std::endl;
                            current_node = balance(current_node,tree,directions,current_node->parent);
                            current_height = current_height_finder(current_node);
                        }else{}
                    }else{}
                }else{
                    if (current_height > current_node->right_count){
                        current_node->right_count = current_height;
                        current_node->balance_factor = current_node->left_count - current_node->right_count;
                        if (current_node->balance_factor > 1 || current_node->balance_factor < -1){
                            // balance();
                            // std::cout << "Balance Factor has been exceeded by 1 at node : " << current_node << " (" << current_node->data << ")" << std::endl;
                            // std::cout << "The balance factor is : " << current_node->balance_factor << std::endl; 
                            // std::cout << std::endl;
                            current_node = balance(current_node,tree,directions,current_node->parent);
                            current_height = current_height_finder(current_node);
                        }else{}
                    }else{}
                }
                if (current_node->parent!=nullptr){
                    if (current_node == current_node->parent->left){
                        directions = update_directions(1,directions);
                    }else{
                        directions = update_directions(2,directions);
                    }
                    current_height++;
                    current_node=current_node->parent;
                }else{
                    break;
                }
            }
        // std::cout << "Height of current Node : " << current_height << std::endl;
        // std::cout << std::endl;
        directions = reset_directions(directions);
        }
    }
    inorder_traversal(tree->root);
    auto end = std::chrono::steady_clock::now();
    auto duration= end-beg;
    std::cout << duration.count() << std::endl;
    return tree;
}

int main(){

    avl_tree* tree = creator();

    return 0;
}