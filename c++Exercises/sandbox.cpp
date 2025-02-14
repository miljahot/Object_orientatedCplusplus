#include <iostream>
#include <vector>

using namespace std;

int main() {
    std::vector<int>vector1;

    std::cout << "How many numbers?";
    int v1;
    int v2;

    std:cin >> v1;

    for(int i = 0; i < v1; i++){
        std::cout << "Enter nr[" << i +1 << "]:";
        std::cin >> v2;
        vector1.push_back(v2);
    };
    std::cout << "You entered: " ;
    for (auto i : vector1){
        std::cout << i << ", ";
    }

}