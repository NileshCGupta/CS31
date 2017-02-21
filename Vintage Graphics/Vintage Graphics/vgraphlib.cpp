//
//  vgraphlib.cpp
//  Vintage Graphics
//
//  Created by Nilesh Gupta on 1/28/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cctype>
#include "vgraphlib.h"

using namespace std;
bool cmd_canvas_setup (int & height, int & width)
{
    cout << "Input the canvas height you'd like to use: ";
    cin >> height;
    cout << "Input the canvas width you'd like to use: ";
    cin >> width;
    if ((height > CANVAS_HEIGHT || height < 0) || (width > CANVAS_WIDTH || width < 0))
        return false;
    return true;
}
bool cmd_pen_selection (char & pen)
{
    cout << "Input the character you'd like to use: ";
    cin >> pen;
    return isprint(pen);
}
bool cmd_draw_vertical_line (char pen, int height)
{
    int shapeHeight;
    cout << "Input the height: ";
    cin >> shapeHeight;
    while (shapeHeight < 0 || shapeHeight > height)
    {
        cout << "Height must be between 0 and " << height << endl;
        cin >> shapeHeight;
    }
    for (int i = 0; i < shapeHeight; i++)
        cout << pen << endl;
    return true;
}
bool cmd_draw_horizontal_line (char pen, int width)
{
    int shapeWidth;
    cout << "Input the width: ";
    cin >> shapeWidth;
    while (shapeWidth < 0 || shapeWidth > width)
    {
        cout << "Width must be between 0 and " << width << endl;
        cin >> shapeWidth;
    }
    for (int i = 0; i < shapeWidth; i++)
        cout << pen;
    return true;
}
bool cmd_draw_rectangle (char pen, char type, int height, int width)
{
    int shapeHeight;
    cout << "Input the height: ";
    cin >> shapeHeight;
    while (shapeHeight < 0 || shapeHeight > height)
    {
        cout << "Height must be between 0 and " << height << endl;
        cin >> shapeHeight;
    }
    int shapeWidth;
    cout << "Input the width: ";
    cin >> shapeWidth;
    while (shapeWidth < 0 || shapeWidth > width)
    {
        cout << "Width must be between 0 and " << width << endl;
        cin >> shapeWidth;
    }
    if (type == 'S' || type == 's')
    {
        for (int i = 1; i <= shapeHeight; i++)
        {
            for (int j = 1; j <= shapeWidth; j++)
            {
                if (j == shapeWidth)
                    cout << pen << endl;
                else
                    cout << pen;
            }
        }
    }
    else if (type == 'H' || type == 'h')
    {
        for (int i = 1; i <= shapeHeight; i++)
        {
            for (int j = 1; j <= shapeWidth; j++)
            {
                if (j == shapeWidth)
                    cout << pen << endl;
                else if (j == 1)
                    cout << pen;
                else if (i == 1 || i == shapeHeight)
                    cout << pen;
                else
                    cout << " ";
            }
        }
    }
    return true;
}
bool cmd_draw_right_triangle (char pen, char type, int width)
{
    if (type == 'S' || type == 's')
    {
        for (int i = 1; i <= width; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                if (j == i)
                    cout << pen << endl;
                else
                    cout << pen;
            }
        }
    }
    else if (type == 'H' || type == 'h')
    {
        for (int i = 1; i <= width; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                if (j == i)
                    cout << pen << endl;
                else if (j == 1 && i > 1)
                    cout << pen;
                else if (i == width)
                    cout << pen;
                else
                    cout << " ";
            }
        }
    }
    return true;
}

