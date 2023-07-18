#include <iostream>

int main(){

    int rows1 {};
    int columns1 {};

    std::cout << "Enter number of rows : ";
    std::cin >> rows1;

    std::cout << "Enter number of columns : ";
    std::cin >> columns1;

    std::cout << std::endl;

    int matrix1[rows1][columns1] {}; //replace with columns
    int value {};

    for (int i {}; i < rows1; i++){
        for (int j {}; j < columns1; j++){
            std::cin >> value;
            matrix1[i][j] = value;
        }
    }
    int rows2 {};
    int columns2 {};
    std::cout << std::endl;
    std::cout << "Enter number of rows : ";
    std::cin >> rows2;

    std::cout << "Enter number of columns : ";
    std::cin >> columns2;

    std::cout << std::endl;

    int matrix2[rows2][columns2] {}; //replace with columns

    for (int i {}; i < rows2; i++){
        for (int j {}; j < columns2; j++){
            std::cin >> value;
            matrix2[i][j] = value;
        }
    }
    std::cout << std::endl;
    int matrix3[columns2][rows1] {};
    int add_factor {}; 
    for (int i {}; i < rows1; i++){
        for (int j {}; j <columns2; j++){
            int value {};
            for (int k {}; k < columns1; k++){
                value+=matrix1[i][k]*matrix2[k][j];
            }
            matrix3[i][j] = value;
        }
    }
    std::cout << "Final Matrix : " << std::endl << std::endl;
    for (int i {}; i < columns2;i++){
        for (int j {}; j < rows1; j++){
            std::cout << matrix3[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}