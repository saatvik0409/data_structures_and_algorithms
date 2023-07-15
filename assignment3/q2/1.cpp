#include <iostream>
#include <unordered_map>

std::unordered_map<char,char> umap {};

class Node{
    public:
        Node(char paranthesis){
            this->paranthesis = paranthesis;
        }
        char paranthesis {};
        Node* next {nullptr};
        Node* prev {nullptr};
};

class stack{
    public:
        Node* top {nullptr};
};

void umap_creator(){
    umap[']'] = '[';
    umap[')'] = '(';
    umap['}'] = '{';    
}

int main(){
    umap_creator();
    int paranthesis_count {};
    std::cout << "Enter the number of paranthesis : ";
    std::cin >> paranthesis_count;
    char paranthesis {};
    
    stack* linklist = new stack;

    for (int i {}; i < paranthesis_count;i++){
        std::cin >> paranthesis;
        Node* newNode = new Node(paranthesis);
        if (linklist->top == nullptr){
            linklist->top = newNode;
            continue;
        }else{
            if (umap[newNode->paranthesis] == linklist->top->paranthesis){   
                Node* newHead = linklist->top->next;
                delete linklist->top;
                linklist->top = newHead;
                delete newNode;
            }else{
                newNode->next = linklist->top;
                linklist->top->prev = newNode;
                linklist->top= newNode;
            }
        }
    }
    if (linklist->top == nullptr){
        std::cout << "Paranthesis are matching! Cool!" << std::endl;
    }else{
        std::cout << "Paranthesis matched hai hi 9" << std::endl;
    }
}