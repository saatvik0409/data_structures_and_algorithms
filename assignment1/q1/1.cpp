#include <iostream>
#include <cmath>
#include <chrono>
#include <bits/stdc++.h>

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

linkedList* brute_force(long long int inp_num){
    linkedList* linkList = new linkedList;
    for (long long int i{1};i<inp_num+1;i++){
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
    return linkList;
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

linkedList* prime_factor_method(long long int inp_num){
    linkedList* linkList = new linkedList;
    long long int i {2};
    while (i*i <= inp_num){
        if (inp_num%i == 0){
            Node* newNode = new Node(i);
            inp_num=inp_num/i;
            if (linkList->head == nullptr){
                linkList->head = newNode;
                linkList->tail = newNode;
            }else{
                linkList->tail->next = newNode;
                newNode->prev = linkList->tail;
                linkList->tail = newNode;
            }
        }else{
            i++;
        }
    }
    if (inp_num!=1){
        Node* newNode = new Node(inp_num);
        if (linkList->tail!=nullptr){
            linkList->tail->next = newNode;
            newNode->prev = linkList->tail;
            linkList->tail = newNode;
        }else{
            linkList->head = newNode;
            linkList->tail = newNode;
        }

    }
    return linkList;
}

long long int product_finder(long long int* prime, long long int* power, long long int unique_segments){
    long long int product {1};
    for (long long int i {}; i < unique_segments;i++){
        long long int pow_val = round(pow(*(prime+i),*(power+i)));
        product = product*pow_val;      
    }
    return product;
}

void printer2(long long int* clone_arr,long long int unique_segments){
    // std::cout << "Here : ";
    for (long long int i {}; i < unique_segments;i++){
        std::cout << *(clone_arr+i) << " ";
    }   
}

long long int* ret_array(linkedList* linkList){
    long long int unique_segments {1};
    Node* current_node = linkList->head->next;
    while (current_node!=nullptr){
        if (current_node->data==current_node->prev->data){
            current_node=current_node->next;
            continue;
        }else{
            unique_segments+=1;
            current_node=current_node->next;
            continue;
        }
    }
    long long int factor[unique_segments] {};
    long long int frequency[unique_segments] {};
    long long int index {};
    long long int frequency_val{1};
    current_node = linkList->head->next;
    //std::cout << "here" << std::endl;
    while (current_node!=nullptr){
        if (current_node->data==current_node->prev->data){
            current_node=current_node->next;
            frequency_val+=1;
            continue;
        }else{
            factor[index] = current_node->prev->data;
            frequency[index] = frequency_val;
            frequency_val = 1; 
            current_node=current_node->next;
            index++;
            continue;
        }
    }   
    factor[index] = linkList->tail->data;
    frequency[index] = frequency_val;
    long long int factor_count {1};
    for (long long int x:frequency){
        factor_count=factor_count*(x+1);
    }
    long long int final_factors[factor_count] {};
    long long int clone_arr[unique_segments] {};
    for (long long int i {}; i <unique_segments;i++){
        clone_arr[i] = frequency[i];
    }
    long long int current_index {0};
    bool isWhile = false;
    long long int final_factors_index{1};
    final_factors[0] = product_finder(&factor[0],&clone_arr[0],unique_segments);
    while(clone_arr[unique_segments-1]<=frequency[unique_segments-1]){
        while (clone_arr[current_index]==0){
            clone_arr[current_index] = frequency[current_index];
            current_index+=1;
            if (!isWhile){isWhile=true;}
        }
        if(isWhile){clone_arr[current_index]-=1;current_index = 0;isWhile=false;}
        else{clone_arr[current_index]-=1;}
        long long int product = product_finder(&factor[0],&clone_arr[0],unique_segments);
        final_factors[final_factors_index] = product;
        final_factors_index+=1;
        // std::cout << "Here : ";
        // std::cout << clone_arr[0] << " " << clone_arr[1] << "; ";
        // std::cout << "Product : " << product << "; ";
        // std::cout << "Current Index : " << current_index << std::endl;
        if (product==1){
            break;
        }
    }

    std::sort(final_factors,final_factors+factor_count);
    //std::cout << "here" << std::endl;
    printer2(&final_factors[0],factor_count);

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
    long long int input_number {};
    std::cin >> input_number;
    auto start_time = time_starter();
    printer(brute_force(input_number));
    std::cout << "; Time Elapsed : " << time_ender(start_time).count() << std::endl;
    start_time = time_starter();
    printer(sqrt_method(input_number));
    std::cout << "; Time Elapsed : " << time_ender(start_time).count() << std::endl;
    start_time = time_starter();
    linkedList* linkListOut = prime_factor_method(input_number);
    //std::cout << "here" << std::endl;
    ret_array(linkListOut);
    std::cout << "; Time Elapsed : " << time_ender(start_time).count() << std::endl;
    
    return 0;
}