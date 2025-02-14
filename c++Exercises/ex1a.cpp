#include <iostream>
#include <vector>


int main(){
    std::vector<int> vec ;

    std::cout << "How many numbers do you want to enter: " ;
    int v1 = 0;
    int v2 = 0;
    std::cin >> v1;
    for (int i = 0; i < v1; i++ ){
        std::cout << "Enter nr[" <<i+1 << "]: ";
        std::cin >> v2;
        vec.push_back(v2);
    }
    std::cout << "You entered: ";
    const char *sep = "";
    for(auto i:vec){
        std::cout << sep << i;
        sep = ", ";
    }

}