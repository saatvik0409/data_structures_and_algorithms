#include <iostream>


class graph{
    public:
        graph(int num_nodes){
            this->num_nodes = num_nodes;
            this->adjacency_matrix = new int[num_nodes*num_nodes] {};
            this->node_val = new int[num_nodes] {};
            this->in_degree = new int[num_nodes] {};
            this->out_degree = new int[num_nodes] {};
        }  
    int* adjacency_matrix {};
    int num_nodes{};
    int* node_val {};
    int* in_degree {};
    int* out_degree {};
};

graph* creator(){
    std::cout << std::endl << "Let's start by creating the graph! " << std::endl;
    std::cout << std::endl << "Enter the number of nodes : ";
    int num_nodes {};
    int value {};
    int adj_nodes {};
    int adj_node {};
    std::cin >> num_nodes;
    std::cout << std::endl; 
    std::cout << "Now enter value of each node and all the nodes connected to it!" << std::endl;
    graph* inp_graph = new graph(num_nodes);
    for (int i {}; i < num_nodes; i++){
        std::cout << "Enter the value of current node : ";
        std::cin >> value;
        *((inp_graph->node_val)+i) = value;
        std::cout << "How many nodes are adjacent to the given node : ";
        std::cin >> adj_nodes;
        std::cout << std::endl;
        for (int j {}; j < adj_nodes;j++){
            std::cout << "Enter the node number of adjacent node : ";
            std::cin >> adj_node;
            *((inp_graph->adjacency_matrix)+(i*num_nodes)+adj_node-1) = 1;
            *((inp_graph->out_degree)+i)+=1;
            *((inp_graph->in_degree)+adj_node-1) +=1; 
            std::cout << "Incremented out degree of : " << i+1 << std::endl;
            std::cout << "Incremented in degree of : " << adj_node << std::endl;

        }
        std::cout << std::endl << std::endl;
    }
    return inp_graph;
}

void printer(graph* inp_graph){
    std::cout << std::endl << "Let's print out the graph! : " << std::endl;
    std::cout << std::endl;
    int num_nodes = inp_graph->num_nodes;
    for (int i {}; i < num_nodes;i++){
        for (int j {}; j < num_nodes; j++){
            std::cout << *((inp_graph->adjacency_matrix)+(num_nodes*i) + j) << " ";
        }
        std::cout << std::endl;
    }
    for (int i {}; i < num_nodes;i++){
        std::cout << "Node Value : " << *((inp_graph->node_val)+i) << std::endl;
        std::cout << "In Degree : " << *((inp_graph->in_degree)+i) << "; Out Degree : " << *((inp_graph->out_degree)+i)  << std::endl;
        std::cout << "Adjacent Nodes : ";
        for (int j {}; j < num_nodes; j++){
            int is_adj = *((inp_graph->adjacency_matrix)+(i*num_nodes)+j);
            if (is_adj == 0){
                continue;
            }else{
                std::cout << j+1 << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int main(){

    graph* inp_graph = creator();
    printer(inp_graph);
}