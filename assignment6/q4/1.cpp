#include <iostream>

//0 Means White
//1 Means Grey
//2 Means Black

class linklistNode{
    public:
        linklistNode(int data){
            this->data = data;
        }
        int data {};
        linklistNode* next {};
        linklistNode* prev {};
};

class LinkedList{
    public:
        linklistNode* head {};
        linklistNode* tail {};
};

class Node{
    public:
        Node(int node_number){
            this->node_number= node_number;
        }
        int node_number {};
        int in_count {};
        int adj_count {};
        int out_count {};
        LinkedList* adj_list {};
        int color {};
        int distance{};
        int finish {};
};

class graph{
    public:
        graph(int num_nodes){
            this->nodes = new Node*[num_nodes] {};
            this->num_nodes = num_nodes;
        }
    int num_nodes{};
    Node** nodes {};
};

void adj_list_creator(Node* inp_node,graph* inp_graph){
    int adj_count {};
    int adj_node {};
    std::cout << std::endl << "Enter number of nodes adjacent to node " << inp_node->node_number << " : ";
    std::cin >> adj_count;
    inp_node->adj_count = adj_count;
    LinkedList* linklist = new LinkedList;
    Node** first_node = inp_graph->nodes;
    int current_node = inp_node->node_number;
    current_node--;
    for (int i {}; i < adj_count; i++){
        std::cout << "Enter node number of adjacent node : ";
        std::cin >> adj_node;
        (*(first_node+current_node))->out_count+=1;
        (*(first_node+adj_node-1))->in_count+=1;
        linklistNode* newNode = new linklistNode(adj_node);
        if (linklist->head== nullptr){
            linklist->head = newNode;
            linklist->tail = newNode;
        }else{
            linklist->tail->next = newNode;
            newNode->prev = linklist->tail;
            linklist->tail = newNode;
        }
    }
    inp_node->adj_list = linklist;
}

graph* creator(){
    int num_nodes {};
    std::cout << std::endl << "Enter the number of nodes in graph : ";
    std::cin >> num_nodes;
    std::cout << std::endl;
    graph* inp_graph = new graph(num_nodes);
    Node** nodes_list = inp_graph->nodes;
    for (int i {}; i < num_nodes; i++){
        Node* newNode = new Node(i+1);
        *(nodes_list+i) = newNode;
    }
    Node* out_node {};
    for (int i {}; i < num_nodes;i++){
        out_node = *((inp_graph->nodes)+i);
        adj_list_creator(out_node,inp_graph);
    }
    return inp_graph;
}

void printer(graph* inp_graph){
    std::cout << std::endl << "PRINTING OUT THE GRAPH " << std::endl;
    std::cout << std::endl;
    Node* current_node {};
    std::cout << inp_graph->num_nodes << std::endl;
    for (int i {}; i < inp_graph->num_nodes; i++){
        // std::cout << "Crashed Here :) " << std::endl;
        current_node = *((inp_graph->nodes)+i);
        std::cout << "Node Number : " << current_node->node_number << std::endl;
        std::cout << "In Count    : " << current_node->in_count << std::endl;
        std::cout << "Out Count   : " << current_node->out_count << std::endl;
        std::cout << "Color       : " << current_node->color << std::endl;
        std::cout << "Arrival     : " << current_node->distance << std::endl;
        std::cout << "Departure   : " << current_node->finish << std::endl;
        std::cout << "Adj Nodes   : ";
        linklistNode* adj_nodes= current_node->adj_list->head;
        while (adj_nodes!=nullptr){
            std::cout << adj_nodes->data << " ";
            adj_nodes = adj_nodes->next;
        }
        std::cout << std::endl << std::endl;
    }
    return;

}


int dfs(Node* node, graph* inp_graph, int d){
    if (node->color==0){
        node->color=1;
        node->distance=d+1;
    }else{
        return d;
    }
    int f {d+1};
    linklistNode* current_node = node->adj_list->head;
    while (current_node!=nullptr){
        std::cout <<  " ~ " << current_node->data << " - " <<std::endl;
        Node* main_node = *(((inp_graph->nodes)+(current_node->data)-1));
        if (main_node->color!=0){
            current_node= current_node->next;
            continue;
        }
        f = dfs(main_node,inp_graph,d+1);
        current_node= current_node->next;

    }
    node->finish=f+1;
    node->color = 2;
    return f+1;
}

int main(){

    graph* inp_graph = creator();
    Node* first_node = *(inp_graph->nodes);
    dfs(first_node,inp_graph,0);
    printer(inp_graph);

    return 0;
}