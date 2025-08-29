#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
using namespace std;

template <class T>
class Sorts {
public:

    int busqSecuencial(vector<int> list, int target) {
        for(int i = 0; i < list.size(); ++i) {
            if (target == list[i]) {
                return i;
            }
            
        }
        return -1;
    }


    void ordenaSeleccion(vector<int> &list) {
        
    }

    void ordenaBurbuja(vector<int> &list) {
        
    }

    void ordenaMerge(vector<int> &list) {
        
    }

    int busqBinaria(const vector<int> &list, int target) {
        int l = 0;
        int r = list.size()-1;
        
        while ( l <= r){
            int mid = r + (r-l)/2;

            if ( mid == target){
                return mid;
            }
            else if ( mid > target){
                l = mid + 1;
            }
            else{
                r = mid-1;
            }
        }

        return -1;
    }
};

#endif
