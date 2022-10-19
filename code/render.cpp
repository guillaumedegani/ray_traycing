#include"render.hpp"
#include"screen.hpp"
#include"math.h"
#include"iostream"
#include<fstream>
#include<algorithm>

vector raytrace(light light, shape** shapeArray,ray Ray3f,int height, int width,int sizeShapeArray,int depth)
{
    vector reflectColour;
    vector out;
    int shapeHit = -1;
    int maxDepth = 3;
            double tMin = INFINITY;
            for (int k = 0; k < sizeShapeArray; k++)
            {
                //CALCULATION OF THE t AT WHICH THE SHAPE IS INTERSECTED BY RAY T = -1 IF NO INTERSECTIOn
                double t = shapeArray[k]->isHit(Ray3f);
                
                //SELECTION OF THE SMALLEST t TO SELECT THE FIRST SHAPE HIT
                if( t > 0.0 && t < tMin)
                {                    
                    tMin = t;
                    shapeHit = k;
                } 
            }
                //IF NO SHAPE IS HITTED SET COLOR TO COLOR OF BACKGROUND THIS CASE WHITE
                if (shapeHit == -1)
                {
                    return vector(1,1,1);
                }
                else
                {
                    int lightRayHitShape = -1;
                    vector pHit = Ray3f.pointHit(tMin);
                    //CALCULATING THE LIGHT RAY TO SEE IF IN SHADOW
                    ray lightRay = ray(pHit + (shapeArray[shapeHit]->getNormal(pHit).multiply(1e-4)), (light.getPosition() - pHit).normalize());
                    double t0 = tMin;
                    for(int i = 0; i < sizeShapeArray;i++)
                    {
                        double lightingHit = shapeArray[i]->isHit(lightRay);
                        //SELECTION OF THE FIRST SHAPE HIT
                        if(lightingHit > 0 && lightingHit < t0)
                        {
                            t0 = lightingHit;
                            lightRayHitShape = i;
                        }    
                    }
                    //IF LIGHT RAY HITS SHAPE SET COLOR TO SHADOW
                    if(lightRayHitShape != -1 )
                    {
                        //SETTING COLOR TO A SHADOW DEPENDING ON THE MATERIAL FOR ADDED REALISM
                        return shapeArray[lightRayHitShape]->getMaterial().getColor().time(vector(0.1,0.1,0.1).time(shapeArray[shapeHit]->getMaterial
                        ().getColor()));
                    }
                    else
                    {   //RECURSIVE CALL OF RAYTRACE WITH MAX DEPTH TO PREVENT INFINIT RAY BOUNCING
                        if((depth < maxDepth) && (shapeArray[shapeHit])->getMaterial().getShininess() > 0)
                        {
                            vector reflectionRayDirection = Ray3f.getDirection() - shapeArray[shapeHit]->getNormal(pHit).multiply(2*Ray3f.getDirection().scalar(shapeArray[shapeHit]->getNormal(pHit)));
                            vector reflectionRayOrigin = pHit + shapeArray[shapeHit]->getNormal(pHit).multiply(1e-4);
                            reflectColour = reflectColour + raytrace(light,shapeArray,ray(reflectionRayOrigin,reflectionRayDirection),height,width,sizeShapeArray,depth + 1).multiply(0.15);
                            return reflectColour + shapeArray[shapeHit]->calculateColor(pHit,light);
                        }
                        return shapeArray[shapeHit]->calculateColor(pHit,light);
                    }
                }
}

void render(light light, shape** shapeArray,vector** &img,int height, int width,int sizeShapeArray)
{
    ray eye = ray(vector(0,0,0),vector(1,0,0));
    screen screen1 = screen(height,width,1,eye);
    vector** pointS1 = screen1.GeneratePointsOfScreen();
    //ITERATION OF THE PIXELS OF SCREEN
    for (int x = 0; x <width   ; x++)
    {
        for (int y = 0; y <height; y++)
        {
            ray Ray3f = ray(vector(0,0,0),pointS1[x][y]);
            //CALUCLATION OF PIXEL COLOR USING RAY TRACING
            img[x][y] = raytrace(light,shapeArray,Ray3f,height,width,sizeShapeArray,0);
        }
    }
    //ADD COLOR TO .PPM FILE
    std::ofstream ofs("./untitled.ppm",std::ios::out | std::ios::binary);
    ofs << "P6\n" << width <<  " " << height << "\n255\n";
    for (int y = 0; y <height  ; y++)
    {
        for (int x = 0; x <width; x++)
        {
            ofs << (unsigned char)(std::min((double)1, (double)img[x][y].getX())*255) << 
            (unsigned char)(std::min((double)1, (double)img[x][y].getY())*255) <<
            (unsigned char)(std::min((double)1, (double)img[x][y].getZ())*255); 
        }
    }
    
}
