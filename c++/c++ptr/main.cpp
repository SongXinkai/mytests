#include <iostream>

using namespace std;

int main(){
    int a[10];
    void* b = (void*)a;
    cout << a << ", " << a+1 << endl;
    cout << b << ", " << b+1 << endl;
    return 0;
}
