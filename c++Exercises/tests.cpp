#include <iostream>
#include <vector>
using namespace std;

int iteratorTest();

int main(){
    iteratorTest();
}

int iteratorTest() {
    vector<int> myvector(3,100);
    vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert(it, 200);
    //cout << *it << "\n" ;

    myvector.insert(it, 2, 300);
    myvector.insert(it+2, 1, 111);
    //cout << *it << "\n" ;
    for (it = myvector.begin(); it != myvector.end();it++)
        cout << ' ' << *it ;
    cout << "\n";

    it= myvector.end();
    myvector.insert(it, 333);
    for (it = myvector.begin(); it != myvector.end();it++)
        cout << ' ' << *it ;
    cout << "\n";

// "it" no longer valid, get a new one:
    it = myvector.begin();

    vector<int> anothervector(2, 400);
    myvector.insert(it+2,anothervector.begin(),
                    anothervector.end());
    for (it = myvector.begin(); it != myvector.end();it++)
        cout << ' ' << *it ;
    cout << "\n";

    int myarray[] = { 501, 502, 503 };
    myvector.insert(myvector.begin(), myarray, myarray+3);

    cout << "myvector contains:";
    for (it = myvector.begin(); it != myvector.end();it++)
        cout << ' ' << *it;
    cout << '\n';
    return EXIT_SUCCESS;
} //myvector contains: 501 502 503 300 300 400 400 200 100 100 100

