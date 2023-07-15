#include <iostream>

void toh(int n, int a, int b, int c){

    if (n>0){

        toh(n-1,a,c,b);
        std::cout << "Move from " << a << " to " << c << "; And value of n is : " << n << std::endl;
        toh(n-1,b,a,c); 
    }

}


int main(){

    int num_discs{};
    std::cin >> num_discs;

    toh(num_discs,1,2,3);
    return 0;
}