//
//  spi.cpp
//  SPI
//
//  Created by Nilesh Gupta on 2/20/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int TOTAL_NO_SONGS = 1000;
string song[TOTAL_NO_SONGS];
string singer[TOTAL_NO_SONGS];
enum SPI_Class
{
    SPI_PLATINUM = 1,
    SPI_GOLD,
    SPI_SILVER,
    SPI_COPPER,
    SPI_PAPER
};
enum SPI_Change
{
    SPI_CHANGE_NO = 0,
    SPI_CHANGE_UP = 1,
    SPI_CHANGE_DOWN = -1
};
SPI_Class spi[TOTAL_NO_SONGS];
int votes[TOTAL_NO_SONGS];
bool grammy[TOTAL_NO_SONGS];

int computeSPI(SPI_Class spi[], SPI_Change spi_change[], const int
               votes[], const bool grammy[], int size);
int getRankingList(const SPI_Class spi[], SPI_Class spi_class, int
                   songList[], int size);
int getChangeList(const SPI_Change spi_change[], SPI_Change
                  an_spi_change, int songList[], int size);
int getGrammyList(const bool grammy[], int songList[], int size);
int merge(const string a1[], int size1, const string a2[], int size2, string
            result[], int size);
int deleteDuplicates(string a[], int size);
int moveToStart(string a[], int n, int loc);
int moveToEnd(string a[], int n, int loc);

int main(int argc, const char * argv[])
{
    string favorite[6] = {
        "Style", "If", "So What?", "Clean", "Heaven", "Take Five"
    };
    int n = moveToEnd(favorite, 6, 1);
    for(int i = 0; i < 6; i++)
        cout << favorite[i] << " \n";
    cout << n;

    //
}

int computeSPI(SPI_Class spi[], SPI_Change spi_change[], const int
               votes[], const bool grammy[], int size)
{
    if(size < 0) return -1;
    for(int i = 0; i < size; i++)
    {
        SPI_Class initial = spi[i];
        // computes SPIs for all songs in spi[]
        if(grammy[i])
            spi[i] = SPI_PLATINUM;
        else if(votes[i] > 5000)
            spi[i] = SPI_GOLD;
        else if(votes[i] > 2000)
            spi[i] = SPI_SILVER;
        else if(votes[i] > 500)
            spi[i] = SPI_COPPER;
        else
            spi[i] = SPI_PAPER;
        
        if(initial == spi[i])
            spi_change[i] = SPI_CHANGE_NO;
        else if(initial < spi[i])
            spi_change[i] = SPI_CHANGE_DOWN;
        else
            spi_change[i] = SPI_CHANGE_UP;
    }
    return 0;
}
int getRankingList(const SPI_Class spi[], SPI_Class spi_class, int
                   songList[], int size)
{
    if(size < 0) return -1;
    int j = 0;
    for(int i = 0; i < size; i++)
    {
        if(spi[i] == spi_class)
            songList[j++] = i;
    }
    songList[j] = -1;
    return 0;
}
int getChangeList(const SPI_Change spi_change[], SPI_Change
                  an_spi_change, int songList[], int size)
{
    int j = 0;
    for(int i = 0; i < size; i++)
    {
        if(spi_change[i] == an_spi_change)
            songList[j++] = i;
    }
    songList[j] = -1;
    return 0;
}
int getGrammyList(const bool grammy[], int songList[], int size)
{
    if(size < 0) return -1;
    int j = 0;
    for(int i = 0; i < size; i++)
    {
        if(grammy[i])
            songList[j++] = i;
    }
    songList[j] = -1;
    return 0;
}
int merge(const string a1[], int size1, const string a2[], int size2, string
          result[], int size)
{
    if(size1 + size2 > size || size1 + size2 < 0 || size1 < 0 || size2 < 0 || size < 0)
        return -1;
    bool isIncreasing = true;
    // checks if a1[] is in non increasing order
    for(int a = 0; a < size1-1; a++)
    {
        if(a1[a] < a1[a+1])
            isIncreasing = false;
    }
    // checks if a2[] is in non increasing order
    for(int a = 0; a < size2-1; a++)
    {
        if(a2[a] < a2[a+1])
            isIncreasing = false;
    }
    if(!isIncreasing)
        return -1;
    // checks which array is larger
    int max = (size1 > size2)? size1: size2;
    int min = (size1 < size2)? size1: size2;
    int index = 0;
    // goes through min elements of both arrays
    for(int i = 0; i < min; i++)
    {
        // currentLargest is the greatest element in either array
        string currentLargest = a1[i];
        for(int j = 0; j < min; j++)
        {
            bool isAlreadyIn = false;
            if(a2[j] > currentLargest)
            {
                // checks if a2[j] has already been placed in result[]
                for(int k = 0; k < min*2; k++)
                {
                    if(result[k] == a2[j])
                        isAlreadyIn = true;
                }
                if(!isAlreadyIn)
                {
                    currentLargest = a2[j];
                    // decreasing i by 1 ensures all elements of a1[] are added
                    i--;
                }
            }
            
        }
        result[index++] = currentLargest;
    }
    // adds the elements left over from the longer array
    for(int i = min; i < max; i++)
    {
        if(size1 > size2)
            result[index++] = a1[i];
        else
            result[index++] = a2[i];
    }
    return size1 + size2;
}
int deleteDuplicates(string a[], int size)
{
    if(size < 0) {return -1;}
    for(int i = 0; i < size - 1; i++)
    {
        if(a[i] == a[i+1])
        {
            // shifts all elements after the duplicate to the left
            for(int j = i+1; j < size - 1; j++)
                a[j] = a[j+1];
        }
    }
    int retained = 0;
    // checks how many elements are retained
    for(int i = 0; i < size-1; i++)
    {
        if(a[i] !=  a[i+1])
            retained++;
    }
    // retained is one less than the number of nonconsecutively unique elements
    return retained + 1;
}
int moveToStart(string a[], int n, int loc)
{
    if(n < 0 || loc >= n) return -1;
    string element = a[loc];
    // shifts elements before loc one to the right
    for(int i = loc; i > 0; i--)
        a[i] = a[i-1];
    // assigns starting value as a[loc]
    a[0] = element;
    return loc;
}
int moveToEnd(string a[], int n, int loc)
{
    if(n < 0 || loc >= n) return -1;
    // added the else in this function since compiler was giving me "control may reach end of non void function" error
    else
    {
        string element = a[loc];
        // shifts elements after loc one to the left
        for(int i = loc; i < n - 1; i++)
            a[i] = a[i+1];
        // assigns last value as a[loc]
        a[n-1] = element;
            return loc;
    }
}
