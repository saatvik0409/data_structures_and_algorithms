#include <iostream>

class Heap{
    public:
        int main_arr[501] {0};
        int end {1};
};

Heap* heapify_up(Heap* inp_heap, int current_index){
    int current_value = (inp_heap->main_arr)[current_index];
    //std::cout << "Printing out current indices : " << std::endl;
    while (current_index!=1){
        int prev_current_index = current_index;
        //std::cout << "Current index inside heapify_up Function : " << current_index << " ";
        current_index=current_index/2;
        if (current_value <= (inp_heap->main_arr)[current_index]){
            break;
        }else{
            int exchange = (inp_heap->main_arr)[current_index];
            (inp_heap->main_arr)[current_index] = (inp_heap->main_arr)[prev_current_index];
            (inp_heap->main_arr)[prev_current_index] = exchange;    
        }
    }
    // std::cout << std::endl;
    return inp_heap;
}

int max(int a, int b){
    return (a>b) ? a:b;
}

Heap* heapify_down(Heap* inp_heap, int current_index){
    int current_value = (inp_heap->main_arr)[current_index];
    int left_value {1};
    int right_value {1};
    while (left_value!=0){
        left_value = (inp_heap->main_arr)[current_index*2];
        right_value =(inp_heap->main_arr)[(current_index*2)+1];
        // std::cout << "Left value : " << left_value << "; Right value : " << right_value << std::endl;
        if (max(left_value,right_value) > current_value){
            int copy {};
            if (left_value>right_value){
                copy = (inp_heap->main_arr)[current_index*2];
                (inp_heap->main_arr)[current_index*2] = current_value;
                (inp_heap->main_arr)[current_index] = copy;
                current_index= current_index*2;
            }else{
                copy = (inp_heap->main_arr)[(current_index*2)+1];
                (inp_heap->main_arr)[(current_index*2)+1] = current_value;
                (inp_heap->main_arr)[current_index] = copy;
                current_index= (current_index*2) + 1;               
            }
        }else{
            break;
        }
    }
    return inp_heap;
}

Heap* insert(Heap* inp_heap, int value){
    (inp_heap->main_arr)[inp_heap->end] = value;
    inp_heap->end++;
    //std::cout << "printing inp_heap->end - 1 : " << (inp_heap->end)-1 << " ";
    inp_heap = heapify_up(inp_heap,(inp_heap->end)-1);
    return inp_heap;
}

int heap_delete(Heap* inp_heap){
    // std::cout << "Entered Heap delete !" << std::endl;

    int ret_val = (inp_heap->main_arr)[1];
    // std::cout << "Element we are deleting : " << ret_val << std::endl;
    // std::cout << "Replacing with : " << (inp_heap->main_arr)[inp_heap->end-1] << std::endl;
    (inp_heap->main_arr)[1] = (inp_heap->main_arr)[inp_heap->end-1];
    (inp_heap->main_arr)[inp_heap->end-1] = 0;
    inp_heap->end--;
    inp_heap = heapify_down(inp_heap,1);
    return ret_val;
}

void heapsort(Heap* inp_heap){
    int loop_len = inp_heap->end;
    for (int i {}; i < loop_len-1; i++){
        int catch_val = heap_delete(inp_heap) ;
        std::cout << catch_val << " ";
        // std::cout << "ELEMENT : " << catch_val << " ";
        // std::cout << std::endl << "array : ";
        // for (int j {}; j < inp_heap->end; j++){
        //     std::cout << (inp_heap->main_arr)[j] << " ";
        // }
        // std::cout << "i : " << i << std::endl;
    }
    std::cout << std::endl;
}

Heap* creator(){
    int num_elements {};
    int values{};
    Heap* inp_heap = new Heap;
    std::cout << std::endl << "Let's start by creating a heap! " << std::endl;
    std::cout << std::endl << "Enter the number of element : "; 
    std::cin >> num_elements;
    std::cout << std::endl;
    for (int i {}; i < num_elements;i++){
        // std::cout << "Enter heap element : ";
        std::cin >> values;
        inp_heap = insert(inp_heap,values);
        // std::cout << "Printing the array created till now : ";
        // for (int j {}; j < inp_heap->end; j++){
        //     std::cout << (inp_heap->main_arr)[i] << " ";
        // }
        // std::cout << std::endl;
    }
    return inp_heap;
}

int main(){
    Heap* inp_heap {};
    inp_heap = creator();
    heapsort(inp_heap);
    return 0;
}