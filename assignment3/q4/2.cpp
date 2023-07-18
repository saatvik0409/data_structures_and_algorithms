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

class Matrix{
    public:
        LinkedList** rows {nullptr};
        LinkedList** columns {nullptr};
        int num_rows {};
        int num_columns {};
};

void matrix_printer(Matrix* inp_matrix){

    LinkedList** rows = inp_matrix->rows;
    LinkedList* current_row = *rows;
    int i {};
    std::cout << std::endl;
    while(current_row!=nullptr){
        Node* current_node = current_row->head;
        while(current_node!= nullptr){
            std::cout << current_node->data << " ";
            current_node = current_node->next;
        }
        std::cout << std::endl;
        i++;
        current_row = *(rows+i);
    }
    return ;

}

Matrix* Matrix_creator(){
    std::cout << std::endl;
    
    int rows{};
    int columns{};
    int value{};

    Matrix* inp_matrix = new Matrix;

    std::cout << "Enter the number of rows : ";
    std::cin >> rows;

    std::cout << "Enter the number of columns : ";
    std::cin >> columns;

    LinkedList** rows_list = new LinkedList*[rows+1]{nullptr};
    LinkedList** columns_list = new LinkedList*[columns+1]{nullptr};
    inp_matrix->rows =rows_list;
    inp_matrix->columns = columns_list;
    inp_matrix->num_columns = columns;
    inp_matrix->num_rows = rows;
    for (int i {}; i < rows; i++){
        for (int j {}; j < columns; j++){
            std::cin >> value;
            Node* newNodeRow = new Node(value);
            Node* newNodeColumn = new Node(value);
            //std::cout << "Created new node" << std::endl;
            LinkedList* current_row = *(rows_list+i);
            LinkedList* current_column = *(columns_list+j);
            
            if (current_row==nullptr){
                current_row = new LinkedList;
                current_row->head = newNodeRow;
                current_row->tail = newNodeRow;
                //std::cout <<"Created new row" << std::endl;
                *(rows_list+i) = current_row;
            }else{
                //std::cout << "Added to existing row ! : " << current_row << std::endl;
                current_row->tail->next = newNodeRow;
                newNodeRow->prev = current_row->tail;
                current_row->tail = newNodeRow;
            }

            if (current_column == nullptr){
                current_column = new LinkedList;
                current_column->head = newNodeColumn;
                current_column->tail = newNodeColumn;
                //std::cout <<"Created new column!" << std::endl;
                *(columns_list+j) = current_column;
            }else{
                current_column->tail->next = newNodeColumn;
                newNodeColumn->prev=current_column->tail;
                current_column->tail = newNodeColumn;
            }
            //matrix_printer(inp_matrix);

        }
    }
    
    

    return inp_matrix;
}

Matrix* matrix_multiplier(Matrix* inp_matrix1, Matrix* inp_matrix2){
    LinkedList** rows1 = inp_matrix1->rows;
    LinkedList** columns2 = inp_matrix2->columns;
    LinkedList* current_row = *rows1;
    LinkedList* current_column {nullptr};
    int num_rows = inp_matrix1->num_rows;
    int num_columns = inp_matrix2->num_columns;
    LinkedList** rows = new LinkedList*[num_rows+1] {nullptr};
    LinkedList** columns = new LinkedList*[num_columns+1] {nullptr};
    int i {};
    Matrix* final_matrix = new Matrix;
    while(current_row!=nullptr){
        current_column = *(columns2);
        int j {};
        while(current_column!=nullptr){
            Node* node1 = current_row->head;
            Node* node2 = current_column->head;  
            int data  {};      
            while (node1!=nullptr){
                data+=((node1->data)*(node2->data));
                //std::cout << node1->data << "*" << node2->data << std::endl;
                node1= node1->next;
                node2=node2->next;
            }
            Node* newNodeRow = new Node(data);
            Node* newNodeCol = new Node(data);
            if (*(rows+i) == nullptr){
                LinkedList* newLinkList = new LinkedList;
                newLinkList->head = newNodeRow;
                newLinkList->tail = newNodeRow;
                *(rows+i) = newLinkList;
            }else{
                LinkedList* current_row1 = *(rows+i);
                current_row1->tail->next = newNodeRow;
                newNodeRow->prev=current_row1->tail;
                current_row1->tail = newNodeRow;
            }
            j++;
            //std::cout << "*(colummns+j) : " << *(columns2+j) << std::endl;
            current_column = *(columns2+j);
        }
        i++;
        current_row = *(rows1+i);
    }
    final_matrix->rows = rows;
    return final_matrix;
}
int main(){

    Matrix* inp_matrix1 = Matrix_creator();
    std::cout << std::endl;
    Matrix* inp_matrix2 = Matrix_creator();
    std::cout << std::endl;
    
    matrix_printer(matrix_multiplier(inp_matrix1,inp_matrix2));



}