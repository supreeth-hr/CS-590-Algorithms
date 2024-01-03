#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include "sort.h"

/* 
 * HW 2 part
 */
int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
	return -1;
      else
	return 1;
    }
} /*>>>*/

void insertion_sort(char** A, int l, int r)
{ 
  int i;
  char* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (string_compare(A[i], key) > 0))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}

void insertion_sort_digit(char** A, int* A_len, int l, int r, int d)
{
    int i;
    char* key;
    int key_len;

    for (int j = l + 1; j <= r; j++) {
        key = A[j];
        key_len = A_len[j];
        i = j - 1;

        while (i >= l && (key_len <= d || (i >= 0 && key_len > d && key[d] < A[i][d]))) {
            A[i + 1] = A[i];
            A_len[i + 1] = A_len[i];
            i--;
        }

        A[i + 1] = key;
        A_len[i + 1] = key_len;
    }
}

void radix_sort_is(char** A, int* A_len, int n, int m)
{ 
    for (int d = m - 1; d >= 0; d--) {
        insertion_sort_digit(A, A_len, 0, n - 1, d);
    }
}


void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d)
{
    const int k = 256; // Number of possible characters (ASCII)
    int C[k] = {0};

    // Count the occurrences of each character at position d
    for (int i = 0; i < n; i++) {
        if (A_len[i] <= d) {
            // String is shorter than d, treat it as having 0 at position d
            C[0]++;
        } else {
            C[A[i][d]]++;
        }
    }

    // Calculate cumulative counts
    for (int i = 1; i < k; i++) {
        C[i] += C[i - 1];
    }

    // Build the sorted array B and update A and A_len
    for (int i = n - 1; i >= 0; i--) {
        if (A_len[i] <= d) {
            // String is shorter than d, treat it as having 0 at position d
            B[C[0] - 1] = A[i];
            B_len[C[0] - 1] = A_len[i];
            C[0]--;
        } else {
            B[C[A[i][d]] - 1] = A[i];
            B_len[C[A[i][d]] - 1] = A_len[i];
            C[A[i][d]]--;
        }
    }

    // Copy the sorted values back to A and A_len
    for (int i = 0; i < n; i++) {
        A[i] = B[i];
        A_len[i] = B_len[i];
    }
}


void radix_sort_cs(char** A, int* A_len, int n, int m)
{ 
    char** temp = new char*[n];
    int* temp_len = new int[n];

    // Initialize temp and temp_len arrays
    for (int i = 0; i < n; i++) {
        temp[i] = new char[m + 1];
        temp_len[i] = A_len[i]; // Initialize with the original lengths
    }

    // Perform counting sort for each character from right to left
    for (int d = m - 1; d >= 0; d--) {
        counting_sort_digit(A, A_len, temp, temp_len, n, d);
        
        // Swap A and temp using std::swap for both the array and its lengths
        std::swap(A, temp);
        std::swap(A_len, temp_len);
    }
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r)
{
  for (int i = l+1; i < r; i++)
    if (string_compare(A[i-1],A[i]) > 0)
      return false;
  return true;
}
