/*
 * recursion.h
 *
 *  Created on: 10/09/2015
 *      Author: pperezm
 */

#ifndef BUSQUEDAS_H_
#define BUSQUEDAS_H_

#include "exception.h"
#include <iostream>
using namespace std;

int bs_seq(int arr[], int size, int val) {
	int l = 0;
    int r = size-1;
        
	while ( l <= r){
		int mid = l + (r-l)/2;

		if ( arr[mid] == val){
			return mid;
		}else if ( arr[mid] < val){
			l = mid + 1;
		}else{
			r = mid-1;
		}
	}

	return -1;
}

int bs_aux(int arr[], int low, int high, int val)	{
int mid;
	if ( low <= high){
		 mid = low + (high-low)/2;
		
		if (arr[mid] == val){
			return mid;
		}else if ( arr[mid] < val){
			return bs_aux(arr, mid+1, high,val);
		}else{
			return bs_aux(arr, low, mid-1,val);
		}
	}
	return -1;
}

int bs_rec(int arr[], int size, int val) {
	return bs_aux(arr, 0, size-1,val);
}
#endif
