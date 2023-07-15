#include <iostream>
#include <unordered_map>

class Node{
    public:
        Node(long long int data){
            this->data = data;
        }
        long long int data{};
        Node* next {nullptr};
};

class LinkedList{
    public:
        Node* head {nullptr};
        Node* tail {nullptr};
};

std::unordered_map<LinkedList*,Array*> umap{};

class Array{
    public:
        Array(const long long int inp_val){
            this->arr = new long long int[inp_val*2] {};
            this->arr_len = inp_val;
            this->current_size=inp_val;
        }
        long long int* arr {nullptr};
        long long int arr_len{0};
        long long int current_size {arr_len};
};

void link_list_creator(long long int list_len){
    LinkedList* linklist = new LinkedList;
    Array* inp_arr = new Array(list_len);
    long long int node_val;
    for (long long int i {}; i < list_len; i++){
        std::cin >> node_val;
        inp_arr->arr[i] = node_val;
        Node* newNode = new Node(node_val);
        if (linklist->head == nullptr){
            linklist->head = newNode;
            linklist->tail = newNode;
        }else{
            linklist->tail->next = newNode;
            linklist->tail = newNode;
        }
    }
    umap[linklist] = inp_arr;
}

LinkedList* insert_tail(LinkedList* linklist, long long int node_val){
    Node* newNode = new Node(node_val);
    if (linklist->tail == nullptr){
        linklist->head = newNode;
        linklist->tail = newNode;
    }else{
        linklist->tail->next = newNode;
        linklist->tail = newNode;
    }
    return linklist;
}

LinkedList* insert_head(LinkedList* linklist, long long int node_val){
    Node* newNode = new Node(node_val);
    if (linklist->head == nullptr){
        linklist->head = newNode;
        linklist->tail = newNode;
    }else{
        newNode->next = linklist->head;
        linklist->head = newNode;
    }
    return linklist;
}

LinkedList* insert_k_position(LinkedList* linklist, long long int node_val,long long position){
    if (position==1){
        return insert_head(linklist,node_val);
    }else{
        long long int current_pos = 2;
        Node* current_node = linklist->head;
        while (current_pos < position && current_node!=nullptr){
            current_node=current_node->next;
            current_pos++;
        }
        if (current_node!=nullptr){
            if (current_node->next==nullptr){
                return insert_tail(linklist,node_val);
            }else{
                Node* newNode = new Node(node_val);
                newNode->next = current_node->next;
                current_node->next= newNode;
                return linklist;
            }
        }else{
            std::cout << "Invalid Position, please Try again!" << std::endl << std::endl;
            return linklist;
        }
    }
}

LinkedList* delete_head(LinkedList* linklist){
    if (linklist->head == nullptr){
        std::cout << "LinkList is empty, deletion not possible!" << std::endl << std::endl;
        return linklist;
    }else{
        Node* newHead = linklist->head->next;
        delete linklist->head;
        linklist->head = newHead;
        if (linklist->head == nullptr){
            linklist->tail = nullptr;
        }
    }
    return linklist;
}

LinkedList* delete_tail(LinkedList* linklist){
    if (linklist->tail == nullptr){
        std::cout << "LinkList is empty, deletion not possible!" << std::endl << std::endl;
        return linklist;
    }else{
        Node* prev_node{nullptr};
        Node* current_node {linklist->head};
        while (current_node!= linklist->tail){
            prev_node=current_node;
            current_node=current_node->next;
        }
        delete current_node;
        current_node = nullptr;
        if (prev_node!=nullptr){
            prev_node->next= nullptr;
            linklist->tail = prev_node;
        }else{
            linklist->tail = nullptr;
            linklist->head = nullptr;
        }
        return linklist;
    }
}

LinkedList* delete_k_position(LinkedList* linklist,long long position){
    if (position==1){
        return delete_head(linklist);
    }else{
        long long int current_pos = 2;
        Node* current_node = linklist->head;
        while (current_pos < position && current_node!=nullptr){
            current_node=current_node->next;
            current_pos++;
        }
        if (current_node!=nullptr){
            if (current_node->next==nullptr){
                return delete_tail(linklist);
            }else{
                Node* newNextNode = current_node->next->next;
                delete current_node->next;
                current_node->next = newNextNode;
                return linklist;
            }
        }else{
            std::cout << "Invalid Position, please Try again!" << std::endl << std::endl;
            return linklist;
        }
    }
}

LinkedList* push(LinkedList* linklist, long long int node_val){
    return insert_tail(linklist,node_val);
}

LinkedList* pop(LinkedList* linklist){
    return delete_tail(linklist);
}

Array* push(Array* inp_arr, long long int value){
    if (inp_arr->current_size >= (inp_arr->arr_len)*2){
        std::cout << "Stack Overflow! " << std::endl;
        return inp_arr;
    }else{
        inp_arr->arr[inp_arr->current_size] = value;
        inp_arr->current_size++;
        return inp_arr;
    }
}

Array* pop(Array* inp_arr){
    if (inp_arr->current_size==0){
        std::cout << "Stack Underflow! " << std::endl;
        return inp_arr;
    }else{
        inp_arr->arr[(inp_arr->current_size)-1] = 0;
        inp_arr->current_size--;
        return inp_arr;
    }    
}

void link_list_printer(LinkedList* linkList){
    Node* head = linkList->head;
    while (head!=nullptr){
        std::cout << head->data << " ";
        head=head->next;
    }
    std::cout << std::endl << std::endl;
    return;
}

void arr_printer(Array* inp_arr){
    long long int current_val = inp_arr->arr[0];
    long long int index {1};
    while (current_val!=0 && index < (inp_arr->arr_len)*2){
        std::cout << current_val << " ";
        current_val = inp_arr->arr[index];
        index++;
    }
    
    std::cout << std::endl;
}

void caller(){
    std::cout << std::endl << std::endl;
    std::cout << "Let's first make a linked list!" << std::endl;
    long long int list_len{};

    std::cout << "Enter the length of your list : ";
    std::cin >> list_len;

    std::cout << "Great, Now please Enter the elements of list : ";
    Array* inp_arr {};
    LinkedList* linklist {};

    for (auto x: umap){
        linklist = x.first;
        inp_arr = x.second;
    }

    std::cout << std::endl << "Cool! Now let's do some tasks!" << std::endl;
    std::cout << std::endl;

    long long int input {};

    while (input !=8){
        std::cout << std::endl;
        std::cout << "What operation will you like to perform : " << std::endl;
        std::cout << "1. Insert a node at head" << std::endl;
        std::cout << "2. Insert a node at tail" << std::endl;
        std::cout << "3. Insert a node at kth position" << std::endl;
        std::cout << "4. Delete a node at head" << std::endl;
        std::cout << "5. Delete a node at tail" << std::endl;
        std::cout << "6. Delete a node at kth position" << std::endl;
        std::cout << "7. Print the linked List" << std::endl;
        std::cout << "8. Quit" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter operation number : ";
        std::cin>>input;  
        if (input==1||input==2||input==3){
            long long int node_val {};
            std::cout << "Enter Node value : ";
            std::cin >> node_val;
            switch(input){
                case 1:
                    insert_head(linklist,node_val);
                    break;
                case 2:
                    insert_tail(linklist,node_val);
                    break;
                case 3:
                    {long long int position{};
                    std::cout << "Enter position : ";
                    std::cin >> position;
                    insert_k_position(linklist,node_val,position);
                    break;}
            }
        }else if (input!=8){
            switch(input){
                case 4:
                    delete_head(linklist);
                    break;
                case 5:
                    delete_tail(linklist);
                    break;
                case 6:
                    {long long int postion{};
                    std::cout << "Enter position : ";
                    std::cin >> postion;
                    delete_k_position(linklist,postion);
                    break;}
                case 7:
                    link_list_printer(linklist);
                    break;               
            }
        }else{
            break;
        }
    }
    std::cout << std::endl;
    std::cout << "Thank you for using my SoFtWaRe!" << std::endl;
    return;
}

int main(){
    caller();
    return 0;
}