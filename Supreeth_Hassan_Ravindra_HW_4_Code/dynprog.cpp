#include <cstring>
#include <iostream>
#include <limits.h>

#include "dynprog.h"

using namespace std;


/*
 * Question 1: Bottom up implementation of Smith-Waterman algorithm
 */
void SW_bottomUp(char* X, char* Y, char** P, int** H, int n, int m){
    int p1,p2,p3;
    for (int i = 0; i <=n; ++i){            //Initialize 1st column of both H and P to 0
        H[i][0] = 0;
        P[i][0] = '0';                      //P has a char data type
    }
    for (int i = 0; i <=m; ++i){            //Initialize 1st row of both H and P to 0
        H[0][i] = 0;
        P[0][i] = '0';                      //P has a char data type
    }
    for (int i = 1; i <=n; ++i){
        for (int j = 1; j <=m; ++j){
            if (X[i-1] == Y[j-1]){          //(i-1) and (j-1) because we need to adjust the indexes as the first column and rows are zeros in our table
                p1 = H[i-1][j-1]+2;
            }
            else{
                p1 = H[i-1][j-1]-1;
            }
            p2 = H[i-1][j]-1;
            p3 = H[i][j-1]-1;
            H[i][j] = max(p1,p2,p3);
            if (H[i][j] == p1){
                P[i][j] = 'd';
            }
            else{
                if (H[i][j] == p2){
                    P[i][j] = 'u';
                }
                else{
                    P[i][j] = 'l';
                }
            }       
        }
    }
}

/*
 * Question 2: Top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW(char* X, char* Y, char** P, int** H, int n, int m){
    for (int i = 0; i <=n; ++i){    //Initialize 1st column of both H and P to 0
        H[i][0] = 0;
        P[i][0] = '0';              //P has a char data type.
    }
    for (int i = 0; i <=m; ++i){    //Initialize the 1st row of both H and P to 0
        H[0][i] = 0;
        P[0][i] = '0';              //P has a char data type
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){   //Initialize whole H table apart from 1st row and column to be -(Infinity) in the case of C++ it would be the smallest possible value og int.
            H[i][j] = INT_MIN;
        }
    }
    memoized_SW_AUX(X,Y,P,H,n,m);
}

/*
 * Auxilary recursive function of top-down with memoization implementation of Smith-Waterman algorithm
 */
int memoized_SW_AUX(char* X, char* Y, char** P, int** H, int n, int m){
	int p1,p2,p3;
    if(n==0 || m==0)
        return 0;
    else{
        if(H[n][m]!=INT_MIN){       //If the cell H[n][m] is already computed it would have any value other then INT_MIN
            return H[n][m];         //If the cell has been previously computed return that cell value.
        }
        if(X[n-1]==Y[m-1]){
            p1 = memoized_SW_AUX(X,Y,P,H,n-1,m-1)+2; //Recursive definition for top down approach.
        }
        else{
            p1 = memoized_SW_AUX(X,Y,P,H,n-1,m-1)-1; //Recursive definition for top down approach.
        }
        p2 = memoized_SW_AUX(X,Y,P,H,n-1,m)-1;      //Recursive definition for top down approach.
        p3 = memoized_SW_AUX(X,Y,P,H,n,m-1)-1;      //Recursive definition for top down approach.
        H[n][m] = max(p1,p2,p3);
        if(H[n][m]==p1)
                P[n][m]= 'd';                   //To fill the direction table.
        else{
            if(H[n][m]==p2){
                P[n][m] = 'u';
            }else{
                P[n][m] = 'l';
            }
        }
        return H[n][m];
    }
}

int max(int x, int y, int z){   //To get the maximum value from the given 3
    if (x >= y) {
        if (x >= z) {
            return x;
        }
    }
    if (y >= x) {
        if (y >= z) {
            return y;
        }
    }
    return z;
}

/*
 * Question 3: Print X'
 */
void print_Seq_Align_X(char* X, char** P, int n, int m){
    if(n <= 0 || m <= 0) {      //We have recursive definition and m and n values are decreasing in each iteration so there would be a time when value would decreased to 0
        return;
    }
    if (P[n][m] == 'd') {
        print_Seq_Align_X(X, P, n - 1, m - 1);
        cout << X[n - 1];
    } else {
        if (P[n][m] == 'l') {
            print_Seq_Align_X(X, P, n, m - 1);
            cout << "-";
        } else {
            print_Seq_Align_X(X, P, n - 1, m);
            cout << X[n - 1];
        }
    }
}

/*
 * Question 3: Print Y'
 */
void print_Seq_Align_Y(char* Y, char** P, int n, int m){
    if(n <= 0 || m <= 0) {      //We have recursive definition and m and n values are decreasing in each iteration so there would be a time when value would decreased to 0
        return;
    }
    if (P[n][m] == 'd') {
        print_Seq_Align_Y(Y, P, n - 1, m - 1);
        cout << Y[m - 1];
    } else {
        if (P[n][m] == 'l') {
            print_Seq_Align_Y(Y, P, n, m - 1);
            cout << Y[m - 1];
        } else {
            print_Seq_Align_Y(Y, P, n - 1, m);
            cout << "-";
        }
    }
}