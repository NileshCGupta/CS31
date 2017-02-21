//
//  pinopay.h
//  CS31 Winter 2015
//  File: HW #1 – Show Me the Money
//  Author: Nilesh Gupta (nileshcgupta@gmail.com)
//  SID: 604489201
//  Date: 2015-1-12
//  Version: 1.0
//  Description: This is the HW #1
//
//  Created by Nilesh Gupta on 1/12/15.
//
//

#ifndef ____pinopay__
#define ____pinopay__
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cmath>

#endif /* defined(____pinopay__) */

using namespace std;

int main ()
{
    string name;
    string ID;
    double hoursWorked;
    double payRate;
    char taxWithheld;
    cout << "Employee Name (First Last):";
    getline (cin, name);
    
    if(name.length() == 0)
    {
        cerr << "You must enter an employee name.";
        return 0;
    }
    
    
    cout << "Employee ID (5 digit):";
    cin >> ID;
    
    if (ID.length() != 5 && ID.length() != 0)
    {
        cerr << "You must enter a 5-digit employee ID.";
        return 0;
    }
    if (ID.length() == 0)
    {
        cerr << "You must enter an employee ID.";
        return 0;
    }
    
    cout << "Number of Hours Worked:";
    cin >> hoursWorked;
    
    if (hoursWorked < 0.0)
    {
        cerr << "The number of working hours must be nonnegative.";
        return 0;
    }
    
    cout << "Pay Rate: $";
    cin >> payRate;
    
    if (payRate < 9.0)
    {
        cerr << "The pay rate must be at least $9.";
        return 0;
    }
    
    cout << "Federal Income Tax Withheld (Y/N):";
    cin >> taxWithheld;
    
    if (taxWithheld != 'Y' && taxWithheld != 'N')
    {
        cerr << "You must enter either Y or N.";
        return 0;
    }
    
    hoursWorked *= 2.0;
    int hoursWorkedInt = (int) hoursWorked;
    hoursWorked = (hoursWorkedInt / 2.0);
    
    double grossPay = payRate * hoursWorked;
    if (hoursWorked > 40)
    {
        grossPay = (40 * payRate) + ((hoursWorked - 40) * (1.5 * payRate));
    }
    double netPay = grossPay;
    if (netPay > 280.00)
    {
        if (taxWithheld == 'Y')
            netPay *= .85;
    }
    if (grossPay > 150.00)
        netPay -= 15;
    
    cout << name << "'s Weekly Gross Pay: $" << fixed << setprecision(2) << grossPay << endl;
    cout << name << "'s Weekly Net Pay: $" << fixed << setprecision(2) << netPay << endl;
    
    return 0;
}