# 42's miniRT project

Raytracer, written in plain old C.<br>
The program renders static images using naive ray tracing and the Phong model.
It can show images using 42's GUI lib _minilibx_, or save pictures to `.bmp` files.

![miniRT](https://raw.githubusercontent.com/Taubenschlag/work-rt/master/resources/everything/0.bmp?token=GHSAT0AAAAAABZDCWC2MCXFHDI7OLVR4I5SY3BR36Q)

## Try it!
1. `git clone`
2. `make`
3. `./miniRT` `[--save]` `path/to/file.rt`

## How to use
**miniRT** creates images for each camera entry in the `.rt` file.
The program opens a minilibx GUI window with rendered scenes by default, you can navigate using arrows and quit with `Esc`.
#####`--save`
Instead of opening GUI - it saves rendered scenes to image files, from `0.bmp` to `n` - number of cameras in `.rt` file.
To open the file it is required to set the correct permissions (`chmod`).

## Scene description
Scenes are described in the `.rt` files. Each non-empty row is the instruction.

### Service instructions

#### Resolution
`R`  `x y`<br>
`R 300 300`<br>
***x*** and ***y*** are _positive ints_, the size of the picture in pixels.<br>
This instruction is can be present only once in the file.

#### Ambient light
`A` `brightness color`<br>
`A 0.2 255,255,255`<br>
***brightness*** - _double_ from 0 to 1.0.<br>
***color*** - is a _colour tuple_ - contains 3 double values. Red, Green and Blue - respectively, in range [0,255]
This instruction is optional but can be present only once in the file.

#### Camera
`c` `position direction up fov`<br>
`c 0,5,-14 0,0,1 0,1,0 70`<br>
***position*** - is a _point tuple_, describing camera position in the coordinate space. X, Y and Z respectively.<br>
***direction*** - is a _vector tuple_, describing a direction of observation<br>
***up*** - is a _vector tuple_, describing orientation of the camera. For most cases `0,1,0` is recommended, unless camera isn't located on the *Y* axis <br>
***fov*** - Horizontal field of view in degrees in range [0,180]. Basically a zoom function. The bigger number - sthe smaller are objects<br>
This instruction is mandatory (should be present at least once), can appear multiple times.

### Object describing instructions
Objects, that you'll actually see on the picture. All of them are optional, and can appear multiple times.

#### Plane
`pl` `coordinates	orientation	paterrn	color`<br>
`pl          0,0,0		0,1,0		40		255,250,150`<br>
***X,Y,Z coordinates*** - is a _point tuple_<br>
***X,Y,Z orientation vector*** - 3d normalized orientation vector. In range [-1,1] for each x,y,z axis <br>
***size of square*** - positive integer that defines check-square pattern. The smaller is number - the smaller are squares <br>
***R,G,B color*** - is a _colour tuple_

#### Square
`sq`  `coordinates orientation size color`<br>
`sq  4,0,1       1,0,0       1           255,255,255`<br>
***X,Y,Z coordinates*** - is a _point tuple_<br>
***X,Y,Z orientation vector*** - 3d normalized orientation vector. In range [-1,1] for each x,y,z axis <br>
***size*** - _double_ side length <br>
***R,G,B color*** - is a _colour tuple_

#### Triangle
`tr` `A B C color`<br>
`tr  -1.5,0,4    0,1.5,4     1.5,0,4     255,255,255`<br>
***A coordinates*** - is a _point tuple_<br>
***B coordinates*** - is a _point tuple_<br>
***C coordinates*** - is a _point tuple_<br>
***R,G,B color*** - is a _colour tuple_

#### Sphere
`sp`  `center diameter color`<br>
`sp  -1,0,-1                 2           255,255,255`<br>
***center*** - is a _point tuple_<br>
***diameter*** - _double_  <br>
***R,G,B color*** - is a _colour tuple_

#### Cube
`cu`  `center orientation side color`<br>
`cu`  `2,0,2 1,1,0 2 25.5,255,255`<br>
***center*** - is a _point tuple_<br>
***X,Y,Z orientation vector*** - 3d normalized orientation vector. In range [-1,1] for each x,y,z axis <br>
***size*** - _double_ side length <br>
***R,G,B color*** - is a _colour tuple_

#### Cone
`co` `coordinates orientation diameter    height      is closed   color`<br>
`co  -2,1,2      0,1,0       2       2   1 255,255,255`<br>
***X,Y,Z coordinates*** - is a _point tuple_<br>
***X,Y,Z orientation vector*** - 3d normalized orientation vector. In range [-1,1] for each x,y,z axis <br>
***diameter*** - _double_  <br>
***height*** - _double_  <br>
***is_closed*** - bool, 1 or 0. if set - cone will have a solid plane in it's base, or will be hollow, like a cocktail glass otherwise  <br>
***R,G,B color*** - is a _colour tuple_

#### Cylinder
`cy` `coordinates orientation diameter    height      is closed   color`<br>
`cy  -2,1,2      0,1,0       2       2   255,255,255`<br>
***X,Y,Z coordinates*** - is a _point tuple_<br>
***X,Y,Z orientation vector*** - 3d normalized orientation vector. In range [-1,1] for each x,y,z axis <br>
***diameter*** - _double_  <br>
***height*** - _double_  <br>
***is_closed*** - bool, 1 or 0. if set - cylinder will have a solid planes on it's ends, or will be hollow, like a pipe otherwise  <br>
***R,G,B color*** - is a _colour tuple_

## How it works
The whole process can be broken down into those basic steps:
1. Arguments check
2. File check
3. Scene parsing
4. Creating the image canvas
    - Creating a ray for each canvas pixel and look for the intersections with described objects.
    - Creating rays from the intersection point to every light source
    - Calculating the colour of each canvas pixel
5. Converting canvas to `.bmp` or `Ximage`

## Main idea

It's all about matrices. The 4x4 matrices are used to  perform various transformations on points and objects in 3D space. Then - actual ray tracing happens.

1. ***Model Transformation***: Matrices are used to transform individual objects in your scene. For example, you can 
apply translation, rotation, scaling, and shearing transformations to an object by multiplying its position (a 3D point)
 by a transformation matrix. This changes the object's position, orientation, and size.
2. ***World Transformation***: To position objects in the world, a world transformation matrix is applied to each
object's transformation matrix. This allows to place objects at specific locations and orientations within the scene.
3. ***View Transformation***: The view transformation matrix simulates the camera's position and orientation. By applying
 this matrix, you can transform the entire scene from world space to camera space, making it appear as if the camera is 
 at the origin and looking down the negative Z-axis.
4. ***Ray Tracing***: After determining which pixels are covered by objects, ray tracing calculations are performed for
each pixel to determine the color of the pixel. This involves casting rays from the camera through each pixel,
intersecting them with objects in the scene, and calculating lighting and shading.
5. ***Combining Effects***: Finally, the pixel colors are combined and we are good to go!

### The mighty ray tracing itself:

   - Pixel Loop:
       Iterate over each pixel on the image plane.
   - Ray Generation:
       For each pixel, cast a primary ray from the camera's position through the pixel.
       The primary ray's direction is calculated based on the pixel's position and the camera's parameters.
   - Intersection Testing:
       Check for intersections between the primary ray and all objects in the scene.
   - Shading and Lighting:
       Once an intersection is found, calculate the shading at the point of intersection.
       Consider the material properties (Phong check's out!) of the object and calculate lighting effects, such as diffuse and specular reflection, based on the positions and properties of light sources.
   - Shadow Rays:
       Cast shadow rays from the intersection point toward each light source.
       Check for occlusions (i.e., intersections with other objects) along these rays.
   - Color Accumulation:
       Combine the colors calculated from various rays at the intersection point.
       Account for the material's properties and the relative intensities of light sources.
   - Final Pixel Color:
       Assign the calculated color to the pixel on the image plane.
       
![wolf](https://raw.githubusercontent.com/Taubenschlag/work-rt/master/resources/wolf/0.bmp?token=GHSAT0AAAAAABZDCWC3NLNTLIMHXWA2YDBWY3BR24A)