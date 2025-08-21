/*
 * recursion.h
 *
 *  Created on: 10/09/2015
 *      Author: pperezm
 */

#ifndef RECURSION_H_
#define RECURSION_H_

#include "exception.h"
#include <iostream>
#include <vector> 

long sum_seq(int n) {
	int res = 0;
	for(int i = 0; i <= n; i++){
		res += i;
	}
	return res;
}

long sum_rec(int n) {
	if ( n == 0 ){
		return 0;
	}
	return n + sum_rec(n-1);
}

long fact_seq(int n) {
	int res = 1;
	for(int i = 2; i <= n; i ++){ // =n
		res = res * i;
	}
	return res; 
}

long fact_rec(int n) {
	if (n == 0) {
		return 1;
	}
	return n * fact_seq(n-1);
	
}

long fib_seq(int n) {
	/*int res = 1;
	int prev = 0;
	if (n == 0){
		return 0;
	}
	for(int i = 1; i < n; i ++){
		int temp = res;
		res = res + prev;
		prev = temp;
	}
	return res;*/

	int resultado = 0;
	int anterior_1 = 1;
	int anterior_2 = 0;
	for (int i = 1; i < n; i++) {
		resultado = anterior_1 + anterior_2;
		anterior_2 = anterior_1;
		anterior_1 = resultado;
	}
	return resultado;
}

long fib_rec(int n) {
	if ( n == 0){
		return 0;
	}
	else if(n == 1){
		return 1;
	}
	return  fib_rec(n-1) + fib_rec(n-2);
}

long gcd_seq(long a, long b) {
	/*int div = 0;
	for( int i = 1; i < (std::min(a,b))/2; i ++){
		if ( (a%i == 0) && (b%i == 0)){
			div = i; 
		}
	}
	return div;
	*/
	while ( b!= 0){
		int temp = a%b;
		a = b;
		b = temp;
	}
	return a;
}

long gcd_rec(long a, long b) {
	if ( b == 0){
		return a;
	}
	return gcd_rec(b,a%b);
}

bool find_seq(int arr[], int size, int val) {

	for( int i = 0; i < size; i ++){
		if (arr[i] == val){
			return true;
		}
	}
	return false;
}

bool find_rec(int arr[], int low, int high, int val) {
	if( low == high){
		return false;
	}
	if( arr[low] == val){
		return true;
	}

	return find_rec(arr,  low+1,  high,  val);
}

int max_seq(int arr[], int size) {
	int max = arr[0];
	for(int i = 0; i < size; i ++){
		if( max < arr[i]){
			max = arr[i];
		}
	}		
	return max;
}

int max_rec(int arr[], int low, int high) {
	if(low == high){
		return arr[low];
	}else if (arr[low] > arr[high]){
		return max_rec(arr, low, high-1);
	}else{
		return max_rec(arr, low+1, high);
	}
}

int unimodal_seq(int arr[], int size) {
	return 0;
}

int unimodal_rec(int arr[], int low, int high) {
	if(low == high){
		return low;
	}else if (arr[low] > arr[high]){
		return max_rec(arr, low, high-1);
	}else{
		return max_rec(arr, low+1, high);
	}
}

int unimodal_rec(int arr[], int size) {
	return 0;
}

#endif /* RECURSION_H_ */
