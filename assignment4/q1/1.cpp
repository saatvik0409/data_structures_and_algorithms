#include <iostream>

class Node{
    public:
        Node(long long int data){
            this->data = data;
        }
        long long int data{};
        Node* next {nullptr};
        Node* prev {nullptr};
        Node* upper {};
        Node* lower {};
};

class LinkedList{
    public:
        Node* head {nullptr};
        Node* tail {nullptr};
        Node* head2 {nullptr};
        Node* tail2 {nullptr};
        Node* head3 {nullptr};
        Node* tail3 {nullptr};
};

LinkedList* link_list_creator(long long int list_len){
    LinkedList* linklist = new LinkedList;
    long long int node_val;
    for (long long int i {}; i < list_len; i++){
        std::cin >> node_val;
        Node* newNode = new Node(node_val);
        if (linklist->head == nullptr){
            linklist->head = newNode;
            linklist->tail = newNode;
        }else{
            linklist->tail->next = newNode;
            newNode->prev = linklist->tail;
            linklist->tail = newNode;
        }
    }
    return linklist;
}

LinkedList* skip_list_creator(LinkedList* linklist){
    Node* lvl2NodeCurrent {};
    Node* lvl3NodeCurrent {};
    Node* lvl1NodeCurrent {};

    Node* newNode = new Node(linklist->head->data);
    linklist->head2 = newNode;
    linklist->tail2 = newNode;
    lvl2NodeCurrent = newNode;

    newNode = new Node(linklist->head->data);
    linklist->head3 = newNode;
    linklist->tail3 = newNode;
    lvl3NodeCurrent = newNode;

    lvl1NodeCurrent = linklist->head;
    lvl2NodeCurrent = linklist->head2;
    lvl3NodeCurrent = linklist->head3;

    lvl1NodeCurrent->upper=lvl2NodeCurrent;
    lvl2NodeCurrent->upper=lvl3NodeCurrent;

    lvl3NodeCurrent->lower = lvl2NodeCurrent;
    lvl2NodeCurrent->lower = lvl1NodeCurrent;

    lvl1NodeCurrent=lvl1NodeCurrent->next;

    int i {1};
    while (lvl1NodeCurrent!=nullptr){
        Node* newNode2 {};
        Node* newNode3 {};
        if (i%2==0){
            newNode2 = new Node(lvl1NodeCurrent->data);
            lvl2NodeCurrent->next = newNode2;
            newNode2->prev = lvl2NodeCurrent;
            linklist->tail2 = newNode2;
            lvl2NodeCurrent = newNode2;
        }
        if(i%3 == 0){
            newNode3 = new Node(lvl1NodeCurrent->data);
            lvl3NodeCurrent->next = newNode3;
            newNode3->prev = lvl3NodeCurrent;
            linklist->tail3 = newNode3;
            lvl3NodeCurrent = newNode3;
      
        }
        if (i%3==0 && i%2!=0){
            newNode3->lower = lvl1NodeCurrent;
            lvl1NodeCurrent->upper = newNode3;               
        }else if (i%2==0 && i%3 != 0){
            newNode2->lower = lvl1NodeCurrent;
            lvl1NodeCurrent->upper = newNode2;
        }else if (i%2 == 0 && i%3 == 0){
            newNode3->lower = lvl2NodeCurrent;
            lvl2NodeCurrent->upper = newNode3;
            newNode2->lower = lvl1NodeCurrent;
            lvl1NodeCurrent->upper = newNode2;         
        }
        lvl1NodeCurrent=lvl1NodeCurrent->next;
        i++;
    }
    return linklist;
}

Node* skip_list_search(LinkedList* linklist,long long int inp_data){
    Node* current_node = linklist->head3;
    while (current_node!=nullptr){
        if (current_node->data < inp_data){
            if (current_node->next != nullptr){ 
                current_node=current_node->next;
            }else if (current_node->lower!=nullptr){
                current_node=current_node->lower;
            }else{
                std::cout << std::endl << "Node not found :(" << std::endl;
                break;
            }
            std::cout << "Arrived at node with value : " << current_node->data << std::endl;
        }else if (current_node->data > inp_data){
            if (current_node->prev!= nullptr){
                if (current_node->lower!=nullptr){
                    current_node=current_node->prev;
                    std::cout << "Arrived at node with value : " << current_node->data << std::endl;
                    current_node=current_node->lower;
                    std::cout << "Arrived at node with value : " << current_node->data << std::endl;
                }else{
                    std::cout << std::endl << "Node not found :(" << std::endl;
                    break;
                }
            }else{
                std::cout << std::endl << "Node not found :(" << std::endl;
                break;
            }
        }else{
            std::cout << "Node found with value : " << current_node->data << std::endl;
            return current_node;
        }
    }    
    if (current_node==nullptr){
        std::cout << std::endl << "Node not found :(" << std::endl;
    }
    return current_node;
}

Node* skip_list_printer(LinkedList* linklist){
    Node* current_node = linklist->head;
    std::cout << std::endl << "Level 1 list : " << std::endl;
    while(current_node!=nullptr){
        std::cout << current_node->data << " ";
        current_node=current_node->next;
    }
    current_node = linklist->head2;
    std::cout << std::endl << "Level 2 list : " << std::endl;
    while(current_node!=nullptr){
        std::cout << current_node->data << " ";
        current_node=current_node->next;
    }
    current_node = linklist->head3;
    std::cout << std::endl << "Level 3 list : " << std::endl;
    while(current_node!=nullptr){
        std::cout << current_node->data << " ";
        current_node=current_node->next;
    }
    std::cout << std::endl << "Printing connections" << std::endl;
    current_node=linklist->head3;
    while (current_node!=nullptr){
        if (current_node->lower->upper = current_node){
            std::cout << "Connections for level 3 node " << current_node->data << " are fine!" << std::endl;
            current_node= current_node->next;
        }
    }
    std::cout << std::endl;
    current_node=linklist->head2;
    while (current_node!=nullptr){
        if (current_node->lower->upper = current_node){
            std::cout << "Connections for level 2 node " << current_node->data << " are fine!" << std::endl;
            current_node= current_node->next;
        }
    }
}

LinkedList* insert(LinkedList* linklist,long long int inp_data){
    Node* current_node = skip_list_search(linklist,inp_data);
    Node* newNode = new Node (inp_data);
    while (current_node->lower!=nullptr){
        current_node=current_node->lower;
    }

    if (linklist->head!=nullptr){
        if (current_node==nullptr){
            linklist->tail->next = newNode;
            newNode->prev = linklist->tail;
            linklist->tail = newNode;
        }else if (current_node==linklist->head){
            Node* newNode2 = new Node(inp_data);
            Node* newNode3 = new Node(inp_data);
            newNode2->next = linklist->head2;
            linklist->head2->prev = newNode2;
            newNode3->next = linklist->head3;
            linklist->head3->prev = newNode3;
            newNode2->upper = newNode3;
            newNode3->lower = newNode2;
            newNode2->lower = newNode;
            newNode->upper = newNode2;
            newNode->next = linklist->head;
            linklist->head->prev=newNode;

            linklist->head = newNode;
            linklist->head2 = newNode2;
            linklist->head3 = newNode3;
        }else if (current_node==linklist->tail){
            linklist->tail->next = newNode;
            newNode->prev = linklist->tail;
            linklist->tail = newNode;
        } else{
            current_node=current_node->prev;
            newNode->next = current_node->next;
            newNode->prev = current_node;
            current_node->next->prev = newNode;
            current_node->next = newNode;
        }
    }else{
        Node* newNode2 = new Node(inp_data);
        Node* newNode3 = new Node(inp_data);
        newNode2->upper = newNode3;
        newNode3->lower = newNode2;
        newNode2->lower = newNode;
        newNode->upper = newNode2;

        linklist->head = newNode;
        linklist->head2 = newNode2;
        linklist->head3 = newNode3;        

        linklist->tail = newNode;
        linklist->tail2 = newNode2;
        linklist->tail3 = newNode3;        
    }

    return linklist;
}

int main(){

    long long int list_len {};
    long long int value {};

    std::cout << std::endl << "Enter the length of list : ";
    std::cin >> list_len;

    LinkedList* inp_link_list =  link_list_creator(list_len);

    inp_link_list = skip_list_creator(inp_link_list);

    std::cout << std::endl << "Enter the element you want to search : ";
    std::cin >> value;

    skip_list_search(inp_link_list,value);

    for (int i {}; i < 5;i++){
        std::cout << std::endl << "Enter a value to be inserted : ";
        std::cin >> value;
        inp_link_list = insert(inp_link_list,value);
        skip_list_printer(inp_link_list);
    }
}