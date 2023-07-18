#include <iostream>

class Node{
    public:
        Node(long long int data){
            this->data = data;
        }
        long long int data {};
        Node* next {nullptr};
        Node* prev {nullptr};
};

class LinkedList{
    public:
        Node* head {nullptr};
        Node* tail {nullptr};
};

void printer(LinkedList* linkList){
    Node* head = linkList->head;
    while(head!=nullptr){
        std::cout << head->data << " ";
        head = head->next;
    }
}

LinkedList* insertionSort(LinkedList* linkList, long long int list_len){
    Node* current_node = linkList->head;
    long long int comparisons {};
    long long int swaps{};
    for (long long int i {}; i < list_len; i++){
        Node* itr_node = current_node;
        while(itr_node->prev!=nullptr && (itr_node->data < itr_node->prev->data)){
            long long int swap_var = itr_node->data;
            itr_node->data= itr_node->prev->data;
            itr_node->prev->data=swap_var;
            itr_node= itr_node->prev;
            comparisons++;
            swaps++;
        }
        if (itr_node->prev!=nullptr){
            comparisons++;
        }
        current_node=current_node->next;
    }
    printer(linkList);
    std::cout << std::endl;
    std::cout << "Comparions : " << comparisons << std::endl;
    std::cout << "Swaps : " << swaps << std::endl;
}

int main(){

    LinkedList* linkList = new LinkedList;
    long long int list_len {};
    long long int node_val{};
    std::cout << std::endl;
    std::cout << "Enter the Length of List : ";
    std::cin >> list_len;

    for (long long int i {};i < list_len; i++){
        std::cin >> node_val;
        Node* newNode = new Node(node_val);
        if (linkList->head == nullptr){
            linkList->head = newNode;
            linkList->tail = newNode;
        }else{
            linkList->tail->next = newNode;
            newNode->prev = linkList->tail;
            linkList->tail = newNode;
        }
    }
    insertionSort(linkList,list_len);


    return 0;
}