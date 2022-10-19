#ifndef RENDER_H
#define RENDER_H
#include"shape.hpp"
#include"vector.hpp"
#include"light.hpp"
/**
 * @brief Renders a given a list of Shapes and a Light 
 * 
 * @param light 
 * @param shapeArray 
 * @param img 
 * @param height 
 * @param width 
 * @param sizeShapeArray 
 */
void render(light light, shape** shapeArray,vector** &img,int height, int width,int sizeShapeArray);


#endif