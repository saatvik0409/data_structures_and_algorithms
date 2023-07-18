#include <iostream>
#include <cmath>

int* insert(long long int value, int* root){
    int i {1};
    while (*(root+i) != 0){
        if (value > *(root+i)){
             i= (2*i)+1;
        }else{
            i = 2*i;
        }
    }
    *(root+i) = value;
    return root;
}

void search(long long int value, int* root){    
    bool isfound {false};
    int i {1};
    while (*(root+i)!=0){
        if (*(root+i) < value){
            i = i*2;
        }else if (*(root+i) > value){
            i = (i*2 + 1);
        }else{
            std::cout << std::endl << "Found node at " << i <<"th index." << std::endl;
            isfound = true;
            break; 
        }
    }
    if (!isfound){
        std::cout << std::endl << "Node not found :(" << std::endl;
        return;
    }
    return;
}

int* creator(){
    std::cout << std::endl;
    std::cout << "Let's create a tree first" << std::endl;

    int height {};
    int nodes {};
    int value {};

    std::cout << std::endl << "Enter the height of your binary tree : ";
    std::cin >> height;

    int* tree = new int[pow(2,height)+1] {};
    
    std::cout << std::endl << "Enter the number of nodes : ";
    std::cin >> nodes;

    std::cout << std::endl;

    for (int i {}; i < nodes; i++){
        std::cout << "Enter the value of nodes : ";
        std::cin >> value;
        tree = insert(value, tree);
    }
}


void caller(){
    std::cout << std::endl;
    std::cout << "Lets start by creating a binary tree! " << std::endl;
    int* inp_binary_tree = creator();
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
int main(){
    
    
    

    return 0;
}