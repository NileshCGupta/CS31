//
//  vgraphlib.h
//  Vintage Graphics
//
//  Created by Nilesh Gupta on 1/28/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#ifndef _VGRAPHLIB_H
#define _VGRAPHLIB_H

//
// Global Constants
//

const int CANVAS_HEIGHT = 40;
const int CANVAS_WIDTH = 50;

//
// Functional Prototypes
//

bool cmd_canvas_setup (int & height, int & width);
bool cmd_pen_selection (char & pen);
bool cmd_draw_vertical_line (char pen, int height);
bool cmd_draw_horizontal_line (char pen, int width);
bool cmd_draw_rectangle (char pen, char type, int height, int width);
bool cmd_draw_right_triangle (char pen, char type, int width);

#endif // _VGRAPHLIB_H