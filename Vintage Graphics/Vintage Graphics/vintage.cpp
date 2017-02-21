//
//  vintage.cpp
//  Vintage Graphics
//
//  Created by Nilesh Gupta on 1/28/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include <iostream>
#include "vgraphlib.h"
#include <string>
using namespace std;

int main()
{
    string mainMenu = "=====================================\nvintage v1.0 - Copyright 2015 Simba\nMake the following selection:\n1 - Set up the canvas\n2 - Select the pen\n3 - Draw the shape\n4 - Exit\n=====================================\n";
    string shapeMenu = "=====================================\nvintage v1.0 - Copyright 2015 Simba\nSelect the shape you'd like to draw:\n1 - Vertical Line\n2 - Horizontal Line\n3 - Rectangle\n4 - Right Triangle\n5 - Return to Main Menu\n=====================================\n";
    int selection, height, width, shape, canvasHeight, canvasWidth;
    char pen, type;
    bool correctPen, correctCanvas;
    bool endProgram = false;
    bool canvasSet = false;
    bool penSet = false;
    
    while (!endProgram)
    {
        cout << mainMenu;
        cin >> selection;
        switch (selection)
        {
            case 1:
                correctCanvas = cmd_canvas_setup (canvasHeight, canvasWidth);
                if (!correctCanvas)
                {
                    cout << "Height must be between 0 and " << CANVAS_HEIGHT << endl;
                    cout << "Width must be between 0 and " << CANVAS_WIDTH << endl;
                }
                else
                    canvasSet = true;
                break;
            
            case 2:
                correctPen = cmd_pen_selection (pen);
                if (!correctPen)
                {
                    cout << "Pen must be a printable character.\n";
                }
                else
                    penSet = true;
                break;
            
                
            case 3:
                if (!canvasSet)
                {
                    cout << "Canvas must be set up first.\n";
                    break;
                }
                if (!penSet)
                {
                    cout << "Pen must be selected first.\n";
                    break;
                }
                cout << shapeMenu;
                cin >> shape;
                while (shape < 1 && shape > 5)
                {
                    cout << "Incorrect options. Try again\n";
                    cout << shapeMenu;
                    cin >> shape;
                }
                switch (shape)
                {
                    case 1:
                        cmd_draw_vertical_line (pen, canvasHeight);
                        break;
                    
                    case 2:
                        cmd_draw_horizontal_line (pen, canvasWidth);
                        break;
                        
                    case 3:
                        cout << "Input the type: ";
                        cin >> type;
                        while (type != 'H' && type != 'h' && type != 'S' && type != 's')
                        {
                            cout << "Type must be H/h or S/s\n";
                            cin >> type;
                        }
                        cmd_draw_rectangle (pen, type, canvasHeight, canvasWidth);
                        break;
                        
                    case 4:
                        cout << "Input the type: ";
                        cin >> type;
                        while (type != 'H' && type != 'h' && type != 'S' && type != 's')
                        {
                            cout << "Type must be H/h or S/s\n";
                            cin >> type;
                        }
                        int smallerMeasure;
                        if (canvasHeight < canvasWidth)
                            smallerMeasure = canvasHeight;
                        else
                            smallerMeasure = canvasWidth;
                        cout << "Input the width: ";
                        cin >> width;
                        while (width < 0 || width > smallerMeasure)
                        {
                            cout << "Width must be between 0 and " << smallerMeasure << endl;
                            cin >> width;
                        }
                        cmd_draw_right_triangle (pen, type, width);
                        break;
                        
                    case 5:
                        break;
                }
                break;
                
            case 4:
                cout << "Thank you. Bye now.\n";
                endProgram = true;
                break;
                
            default:
                cout << "Incorrect options. Try again\n";
                break;
        }
    }
    return 0;
}
