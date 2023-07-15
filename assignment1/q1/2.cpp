#include <iostream>
#include <cmath>
#include <chrono>

class Node{
    public:
        Node(long long int data){
            this->data = data;
        }
        long long int data {};
        Node* next {nullptr};
        Node* prev {nullptr};
};

class linkedList{
    public:
        Node* head {nullptr};
        Node* tail {nullptr};
        long long int list_len {0};
};

void printer(linkedList* linkList){
    Node* head = linkList->head;
    while(head!=nullptr){
        std::cout << head->data << " ";
        head = head->next;
    }
}

linkedList* sqrt_method(long long int inp_num){
    linkedList* linkList = new linkedList;
    long long int sqrt_num = pow(inp_num,0.5);
    for (long long int i{1};i<=sqrt_num;i++){
        if (inp_num%i == 0){
            if (linkList->head==nullptr){
                Node* newNode = new Node(i);
                linkList->head = newNode;
                linkList->tail = newNode;
            }else{
                Node* newNode = new Node(i);
                linkList->tail->next = newNode;
                newNode->prev = linkList->tail;
                linkList->tail = newNode;   
            }
        }
    }
    long long int tail_val = linkList->tail->data;
    Node* rev_node {nullptr};
    if (tail_val*tail_val == inp_num){
        rev_node = linkList->tail->prev;
    }else{
        rev_node = linkList->tail;
    }
    while (rev_node!=nullptr){
        long long int data_val = inp_num/(rev_node->data);
        Node* newNode = new Node(data_val);
        linkList->tail->next = newNode;
        newNode->prev = linkList->tail;
        linkList->tail = newNode;
        rev_node=rev_node->prev;
    }
    return linkList;
}

long long int GCDFinder(long long int int1, long long int int2){
    long long int rem {};
    rem = int1%int2;
    if (rem==0){
        return int2;
    }else{
        return GCDFinder(int2,rem);
    }
}

long long int GCDCaller(long long int int1,long long int int2){
    if (int1>int2){
        return GCDFinder(int1,int2);
    }else{return GCDFinder(int2,int1);}
}

auto time_starter(){
    auto beg = std::chrono::high_resolution_clock::now();
    return beg;
}

auto time_ender(auto beg){
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
    return duration;
}

int main(){

    long long int int1 {};
    long long int int2 {};

    std::cin >> int1;
    std::cin >> int2;
    
    auto start_time = time_starter();
    linkedList* linkList1 = sqrt_method(int1);
    linkedList* linkList2 = sqrt_method(int2);

    Node* current_node_1 = linkList1->head;
    Node* current_node_2 = linkList2->head;

    linkedList* newLinkList = new linkedList;
    while (true){
        if (current_node_1==nullptr||current_node_2==nullptr){
            break;
        }
        if (current_node_1->data == current_node_2->data){
            Node* newNode = new Node(current_node_1->data);
            current_node_1=current_node_1->next;
            current_node_2=current_node_2->next;
            if (newLinkList->head == nullptr){
                newLinkList->head = newNode;
                newLinkList->tail = newNode;
            }else{
                newLinkList->tail->next= newNode;
                newNode->prev = newLinkList->tail;
                newLinkList->tail = newNode;
            }
            continue;
        }
        if (current_node_1->data > current_node_2->data){
            current_node_2=current_node_2->next;
        }else{
            current_node_1=current_node_1->next;
        }
    }

    std::cout << "GCD is : " << newLinkList->tail->data;
    std::cout << "; Time Elapsed : " << time_ender(start_time).count() << std::endl;
    start_time = time_starter();
    long long int final_answer = GCDCaller(int1,int2);
    std::cout << "GCD is : " << final_answer;
    std::cout << "; Time Elapsed : " << time_ender(start_time).count() << std::endl;
    return 0;
}