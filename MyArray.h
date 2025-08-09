#ifndef MYARRAY_H
#define MYARRAY_H

#include <bits/stdc++.h>
using namespace std;

// ===== Generic Array Class =====
template <typename T>
class MyArray {
private:
    vector<T> data; // Internal storage

public:
    // Constructors
    MyArray() {}
    MyArray(initializer_list<T> list) : data(list) {}
    MyArray(vector<T> vec) : data(vec) {}

    // Sort ascending
    void sortAsc() {
        sort(data.begin(), data.end());
    }

    // Sort descending
    void sortDesc() {
        sort(data.rbegin(), data.rend());
    }

    // Reverse array
    void reverseArray() {
        reverse(data.begin(), data.end());
    }

    // Rotate array by k positions
    void rotateArray(int k) {
        if (data.empty()) return;
        k %= data.size();
        rotate(data.begin(), data.begin() + k, data.end());
    }

    // Append element
    void append(T val) {
        data.push_back(val);
    }

    // Delete element at index
    void deleteAt(int index) {
        if (index >= 0 && index < (int)data.size())
            data.erase(data.begin() + index);
    }

    // Merge another array
    void mergeWith(const MyArray<T> &other) {
        data.insert(data.end(), other.data.begin(), other.data.end());
    }

    // Add scalar to all elements
    void addScalar(T val) {
        for (auto &x : data) x += val;
    }

    // Display contents
    void print() const {
        for (auto &x : data) cout << x << " ";
        cout << "\n";
    }

    // Get raw vector
    vector<T> getData() const {
        return data;
    }
};

// ===== Utility String Functions =====
namespace MyString {
    // String to char array (vector<char>)
    inline vector<char> toCharArray(const string &s) {
        return vector<char>(s.begin(), s.end());
    }

    // String to array of words
    inline vector<string> toWordArray(const string &s) {
        stringstream ss(s);
        vector<string> words;
        string word;
        while (ss >> word) words.push_back(word);
        return words;
    }

    // Reverse a string
    inline string reverseString(string s) {
        reverse(s.begin(), s.end());
        return s;
    }
}

#endif // MYARRAY_H
