#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <list> 

using namespace std;

template <class T>
class Sorts {
private:
    void swap(vector<T> &v, int i, int j);
    void copyArray(vector<T> &A, vector<T> &B, int low, int high);
    void mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high);
    void mergeSplit(vector<T> &A, vector<T> &B, int low, int high);

public:
    void ordenaSeleccion(vector<T> &list);
    void ordenaBurbuja(vector<T> &list);
    void ordenaMerge(vector<T> &list);
    int busqSecuencial(const vector<T> &list, T target);
    int busqBinaria(const vector<T> &list, T target);
};


template <class T>
void Sorts<T>::swap(vector<T> &v, int i, int j) {
    T aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

template <class T>
void Sorts<T>::copyArray(vector<T> &A, vector<T> &B, int low, int high) {
    for (int i = low; i <= high; i++) {
        A[i] = B[i];
    }
}

template <class T>
void Sorts<T>::mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high) {
        if (A[i] < A[j]) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }
    while (j <= high) {
        B[k++] = A[j++];
    }
    while (i <= mid) {
        B[k++] = A[i++];
    }
}

template <class T>
void Sorts<T>::mergeSplit(vector<T> &A, vector<T> &B, int low, int high) {
    if ((high - low) < 1) {
        return;
    }
    int mid = (low + high) / 2;
    mergeSplit(A, B, low, mid);
    mergeSplit(A, B, mid + 1, high);
    mergeArray(A, B, low, mid, high);
    copyArray(A, B, low, high);
}


template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &list) {
    for (int i = 0; i < list.size(); i++) {
        int min_ind = i;
        for (int j = i + 1; j < list.size(); j++) {
            if (list[j] < list[min_ind]) {
                min_ind = j;
            }
        }
        swap(list, i, min_ind);
    }
}

template <class T>
void Sorts<T>::ordenaBurbuja(vector<T> &list) {
    for (int i = list.size() - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (list[j] > list[j + 1]) {
                swap(list, j, j + 1);
            }
        }
    }
}

template <class T>
void Sorts<T>::ordenaMerge(vector<T> &list) {
    int n = list.size();
    if (n <= 1) return;
    vector<T> tmp(n);
    mergeSplit(list, tmp, 0, n - 1);
}

template <class T>
int Sorts<T>::busqSecuencial(const vector<T> &list, T target) {
    for (int i = 0; i < list.size(); ++i) {
        if (target == list[i]) {
            return i;
        }
    }
    return -1;
}

template <class T>
int Sorts<T>::busqBinaria(const vector<T> &list, T target) {
    int l = 0;
    int r = list.size() - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (list[mid] == target) { 
            return mid;
        } else if (list[mid] < target) { 
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

#endif /* SORTS_H_ */