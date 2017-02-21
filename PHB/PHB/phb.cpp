//
//  main.cpp
//  PHB
//
//  Created by Nilesh Gupta on 3/8/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include <iostream>
#include <cstdlib>
using namespace std;

const int PHB_LIST_LENGTH = 1000;
const int PHB_LIST_MAX_VAL = 100;
const int PHB_LIST_MAGIC_NUM = 31;
enum PHB_LIST_ORDER {
    PHB_LIST_ORDER_INC,
    PHB_LIST_ORDER_DEC
};

bool PHB_list_check(const int *in_list, const int *in_len, int *out_list);
bool PHB_list_delete_duplicates(int *in_list, const int *len);
bool PHB_list_fill_up(int *list, const int *len);
bool PHB_list_reverse(int *list, const int *len);
bool PHB_list_sort(int *list, const int *len, const PHB_LIST_ORDER *ord);
bool PHB_list_sum_31(const int *in_list, const int *in_len, int *out_list,
                        int *out_len);

int main(int argc, const char * argv[])
{
    int len_5 = 8;
    int in_list_5[] = { 9, 5, 16, 22, 1, 37, 26, 14 };
    int* in_len_5 = &len_5;
    int* out_list_1 = new int;
    int* out_len_1 = new int;
    
    bool test = PHB_list_sum_31(in_list_5, in_len_5, out_list_1, out_len_1);
    
    cout << "Test: " << test << endl;
    
    for (int i = 0; i < *out_len_1; i++)
    { cout << out_list_1[i] << endl;
    }
    delete[] out_list_1;
    delete out_len_1;
}

bool PHB_list_check(const int *in_list, const int *in_len, int *out_list)
{
    // checks for any bad arguments
    if (*in_len < 0)
        return false;
    for (int i = 0; i < *in_len; i++)
    {
        if (*(in_list + i) < 0)
            return false;
    }
    
    bool validValues = true;
    for (int i = 0; i < *in_len; i++)
    {
        // checks if the values are in 1-100 range inclusive
        if((*(in_list + i)) > 100 || (*(in_list + i)) < 1)
        {
            *out_list++ = i;
            validValues = false;
        }
    }
    return validValues;
}
bool PHB_list_delete_duplicates(int *in_list, const int *len)
{
    // checks for any bad arguments
    if (*len < 0)
        return false;
    for (int i = 0; i < *len; i++)
    {
        if (*(in_list + i) < 0)
            return false;
    }
    
    for (int i = 0; i < *len-1; i++)
    {
        // checks for duplicates and "erases" them
        if (*(in_list + i) == *(in_list + i + 1))
        {
            for (int j = i+1; j < *len-1; j++)
                *(in_list + j) = *(in_list + j + 1);
        }
    }
    return true;
}
bool PHB_list_fill_up(int *list, const int *len)
{
    // checks for any bad arguments
    if (*len < 0)
        return false;
    for (int i = 0; i < *len; i++)
    {
        if (*(list + i) < 0)
            return false;
    }
    
    // sets each value of array pointed to by *list to a random value from 1-100
    for (int i = 0; i < *len; i++)
        *(list + i) = rand() % 100 + 1;
    return true;
}
bool PHB_list_reverse(int *list, const int *len)
{
    // checks for any bad arguments
    if (*len < 0)
        return false;
    for (int i = 0; i < *len; i++)
    {
        if (*(list + i) < 0)
            return false;
    }
    
    // *len/2 ensures that for even numbered arrays, we access each element and for odd numbered arrays, we access each element except the very middle one but we don't need to because it will be the same reversed
    for (int i = 0; i < *len/2; i++)
    {
        // maintains the first element of the array before we change its value
        int a = *(list + i);
        // swaps two elements equally far from the midpoint of the array
        *(list + i) = *(list + *len - 1 - i);
        *(list + *len - 1 - i) = a;
    }
    return true;
}
bool PHB_list_sort(int *list, const int *len, const PHB_LIST_ORDER *ord)
{
    // checks for any bad arguments
    if (*len < 0)
        return false;
    for (int i = 0; i < *len; i++)
    {
        if (*(list + i) < 0)
            return false;
    }
    
    for (int i = 1; i < *len; i++)
    {
        // this loop ensures the value *(list + j) will be in the lowest position it should be in
        for (int j = i; j > 0; j--)
        {
            if (*(list + j) < *(list + j - 1))
            {
                // swaps two consecutive elements if they are not in increasing order
                int a = *(list + j);
                *(list + j) = *(list + j - 1);
                *(list + j - 1) = a;
            }
        }
    }
    if (*ord == PHB_LIST_ORDER_DEC)
        PHB_list_reverse(list, len);
    return true;
}
bool PHB_list_sum_31(const int *in_list, const int *in_len, int *out_list,
                     int *out_len)
{
    // checks for any bad arguments
    if (*in_len < 0)
        return false;
    for (int i = 0; i < *in_len; i++)
    {
        if (*(in_list + i) < 0)
            return false;
    }
    
    // accounts for case when array is smaller than 5
    if (*in_len < 5)
    {
        // sum represents sum of all elements in the array
        int sum = 0;
        for (int j = 0; j < *in_len; j++)
        {
            sum += *(in_list + j);
            // checks if any individual element is 31
            if (*(in_list + j) == 31)
            {
                *out_len = 1;
                *out_list = j;
                return true;
            }
            for (int k = 0; k < *in_len; k++)
            {
                if (k == j) // no element can be used twice
                    continue;
                // checks for all possible combinations of 2 numbers in the array
                if (*(in_list + j) + *(in_list + k) == 31)
                {
                    *out_len = 2;
                    *out_list = j;
                    *(out_list+1) = k;
                    return true;
                }
                for (int l = 0; l < *in_len; l++)
                {
                    if (l == k || l == j) // no element used twice
                        continue;
                    // checks for all possible combinations of 3 numbers in the array
                    if (*(in_list + j) + *(in_list + k) + *(in_list + l) == 31)
                    {
                        *out_len = 3;
                        *out_list = j;
                        *(out_list+1) = k;
                        *(out_list+2) = l;
                        return true;
                    }
                }
            }
        }
        // checks if sum of all elements is 31
        if (sum == 31)
        {
            *out_len = *in_len;
            for (int i = 0; i < *in_len; i++)
                *(out_len + i) = i;
        }
        return true;
    }
    // when array is 5 or bigger
    for (int i = 0; i+4 < *in_len; i++)
    {
        // check sum of the 5 elements
        if (*(in_list + i) + *(in_list + i + 1) + *(in_list + i + 2) + *(in_list + i + 3) + *(in_list + i + 4) == 31)
        {
            *out_len = 5;
            *out_list = i;
            *(out_list+1) = i+1;
            *(out_list+2) = i+2;
            *(out_list+3) = i+3;
            *(out_list+4) = i+4;
            return true;
        }
        for (int j = i; j < i+5; j++)
        {
            // checks if any individual element is 31
            if (*(in_list + j) == 31)
            {
                *out_len = 1;
                *out_list = j;
                return true;
            }
            for (int k = i; k < i+5; k++)
            {
                if (k == j) // no element can be used twice
                    continue;
                // checks for all possible combinations of 2 numbers out of the 5
                if (*(in_list + j) + *(in_list + k) == 31)
                {
                    *out_len = 2;
                    *out_list = j;
                    *(out_list+1) = k;
                    return true;
                }
                for (int l = i; l < i+5; l++)
                {
                    if (l == k || l == j) // no element used twice
                        continue;
                    // checks for all possible combinations of 3 numbers out of the 5
                    if (*(in_list + j) + *(in_list + k) + *(in_list + l) == 31)
                    {
                        *out_len = 3;
                        *out_list = j;
                        *(out_list+1) = k;
                        *(out_list+2) = l;
                        return true;
                    }
                    for (int m = i; m < i+5; m++)
                    {
                        if (m == k || m == j || m == l) // no element used twice
                            continue;
                        // checks for all possible combinations of 4 numbers out of the 5
                        if (*(in_list + j) + *(in_list + k) + *(in_list + l) + *(in_list + m) == 31)
                        {
                            *out_len = 4;
                            *out_list = j;
                            *(out_list+1) = k;
                            *(out_list+2) = l;
                            *(out_list+3) = m;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return true;
}




