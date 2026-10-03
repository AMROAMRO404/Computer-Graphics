//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.02.2021
//


#pragma once

#include <functional>

// Scan-conversion algorithms. They do not draw anything themselves: every
// pixel they choose is handed to `plot`, so they are independent of Qt and
// can be tested without a window.
namespace raster
{

using PlotFn = std::function<void(int x, int y)>;

// DDA line. Works for any direction, including vertical lines.
void lineDDA(double x1, double y1, double x2, double y2, const PlotFn &plot);

// Bresenham line (integer arithmetic only). Works for any direction.
void lineBresenham(int x1, int y1, int x2, int y2, const PlotFn &plot);

// Midpoint circle. A radius of 0 plots the center; a negative one plots nothing.
void circleMidpoint(int xc, int yc, int r, const PlotFn &plot);

// Circular arc between two angles given in degrees. Angles are measured from
// the positive x axis and grow towards positive y (clockwise on screen).
void arc(double xc, double yc, double r, double startDeg, double endDeg, const PlotFn &plot);

}
