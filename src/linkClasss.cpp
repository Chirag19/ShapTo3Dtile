#include <iostream>
#include "linkClasss.h"
 
extern bool ShapTo3Dtiles(const char* filename, const char* dest, const char* height);
bool ShapTo3Dtile(const char* filename, const char* dest, const char* height)
{
    if (ShapTo3Dtiles(filename, dest, height))
        return true;
    else
        return false;
}



