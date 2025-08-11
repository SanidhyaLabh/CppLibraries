#include <iostream>
#include "MyArray.h"
using namespace std;

int main() {
    MyArray<int> arr = {5, 2, 8, 1, 3};
    arr.sortAsc();
    arr.print(); // 1 2 3 5 8

    arr.reverseArray();
    arr.print(); // 8 5 3 2 1

    arr.rotateArray(2);
    arr.print(); // 3 2 1 8 5

    arr.append(10);
    arr.deleteAt(1);
    arr.addScalar(2);
    arr.print(); // modified array

    MyArray<int> arr2 = {100, 200};
    arr.mergeWith(arr2);
    arr.print();

    string s = "Hello World";
    auto chars = MyString::toCharArray(s);
    auto words = MyString::toWordArray(s);

    cout << MyString::reverseString(s) << "\n";

    return 0;
}
