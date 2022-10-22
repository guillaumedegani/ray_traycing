# Ray Tracing

Ray tracing is a method fairly common in computer graphics, it's used to render complexe scenes and shapes with a more realistic appearence. The way it works is pretty simple, the idea is that you make a simulation where you track the path taken by light rays from a "source" to a "camera". In front of the camera there will be a screen that'll be composed of many pixels and each pixel will be set to a diffrent value depending on the ray that passed through it.  

# Planning the project

Before we start coding it's important to have an idea of how the algorithme that we're trying to implement works. To do so we divided the Ray Tracing process in different steps that are easier to implement and understand:

- Initialization of a scene with various 3D shapes, a light source and a screen. 
- Creation of the rays that start from the "eye" and goes through each "pixels" of the "screen", that will have a different value depending of how the ray evolves in the scene.
- Evaluate the evolution of the ray in the scenes with priorities as follow
    - If the ray intersects with a single object we can stop the process
    - If the ray intersects with a list of object you take the closests object to the screen, as it represents the first object met.
    - Finally, if no object is met, you set the color of the ray to the color of the background.
- Now depending on the point found we evaluate if it's lit by the light sources of the scene or not.  This will give the 3D effect to our ray tracing. 
- Finally we add shades, textures and reflection to our model using [ Phong Reflection Model ](https://en.wikipedia.org/wiki/Phong_reflection_model) which is a well known method for calculating realistic colors in raytracing

# Results optained for each step

The first image obtained is quite simple, the image is 2D and represents only the intersection of the rays with the shapes without taking into consideration wether they intersect with the light source or not. 


![2D representation](/assets/simple_intersection_2D_image.png)


After doing that we added the intersection with the light source and part of the Phong Reflection model. This gave the following results :

![2D representation](/assets/first_try_limits_at_edges.png)

We can observe some artefacts that are caused by approximations in the inequalities used to compute the intersections.


Here we add the cubic shape which is composed of 6 planes.  This shape is fairly complexe to implement if you want to be able to rotate it in all directions. Furthermore we fixed the issues with artefacts by reworking our inequalities for the intersections between the ray and the shapes and added the texture part of phong model.

![2D representation](/assets/lighting_fixe_no_reflectio.png) 

And finally we add the reflection. To do so we use a recursive function with a limit in the depth otherwise it would go on forvever. This is the final results that corespond to the specification of the project.

![2D representation](/assets/reflection_added.png)



# Running the project 

Please note that the output of the algorithm is .ppm format and not .png as asked in the subject. However this doesn't change anything to the effectiveness of the programm.
And if I were working in a professional environment requiring .png i woul have created a sim .sh scrpit using the following command:
convert img.ppm img.png

If you want to test the programm and need .png to view it simply run in command on linux:

convert untitled.ppm untitled.png

And your image will be converted to .png

To commpile my code I use the following line :
```
g++ -Wall main.cpp vector.cpp vector.hpp sphere.cpp sphere.hpp ray.cpp ray.hpp shape.hpp screen.cpp screen.hpp material.cpp material.hpp plane.cpp plane.hpp cube.cpp cube.hpp render.cpp render.hpp light.cpp light.hpp -o exec
```
