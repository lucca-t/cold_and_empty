#ifndef FUNCIONES_H_
#define FUNCIONES_H_

class Funciones{
    public:

    int sumaIterativa(int n){
        int sum = 0;
        for(int i = 1; i <= n; i++){
            sum += i;
        }
        return sum;
    }

    int sumaRecursiva(int n){
        if (n == 0 ){
            return 0;
        }
        return n + sumaRecursiva(n-1);
    }

    int sumaDirecta(int n){
        return n*(n+1)/2;
    }

};
#endif