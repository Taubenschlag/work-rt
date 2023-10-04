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
This instruction is mandatory and can be present only once in the file.

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
***fov*** - Horizontal field of view in degrees in range [0,180].<br>
This instruction is mandatory (should be present at least once), can appear multiple times.

### Object describing instructions
Objects, that you'll actually see on the picture. All of them are optional, and can appear multiple times.

#### Plane
`pl` `coordinates orientation color`<br>
`pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225`<br>
***X,Y,Z coordinates*** - is a _point tuple_<br>
***X,Y,Z orientation vector*** - 3d normalized orientation vector. In range [-1,1] for each x,y,z axis <br>
***R,G,B color*** - is a _colour tuple_

#### Square
`sq`  `coordinates orientation size color`<br>
`sq  4,0,1       1,0,0       1           255,255,255`<br>
***X,Y,Z coordinates*** - is a _point tuple_<br>
***X,Y,Z orientation vector*** - 3d normalized orientation vector. In range [-1,1] for each x,y,z axis <br>
***size*** - _double_ side length <br>
***R,G,B color*** - is a _colour tuple_

#### Triangle
`tr` `A B C colour`<br>
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
`co` `coordinates orientation diameter height color`<br>
`co  -2,1,2      0,1,0       2       2   255,255,255`<br>
***X,Y,Z coordinates*** - is a _point tuple_<br>
***X,Y,Z orientation vector*** - 3d normalized orientation vector. In range [-1,1] for each x,y,z axis <br>
***diameter*** - _double_  <br>
***height*** - _double_  <br>
***R,G,B color*** - is a _colour tuple_

#### Cylinder
`cy` `coordinates orientation diameter height color`<br>
`cy  -2,1,2      0,1,0       2       2   255,255,255`<br>
***X,Y,Z coordinates*** - is a _point tuple_<br>
***X,Y,Z orientation vector*** - 3d normalized orientation vector. In range [-1,1] for each x,y,z axis <br>
***diameter*** - _double_  <br>
***height*** - _double_  <br>
***R,G,B color*** - is a _colour tuple_

#### Tor
*in progress..*

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

![wolf](https://raw.githubusercontent.com/Taubenschlag/work-rt/master/resources/wolf/0.bmp?token=GHSAT0AAAAAABZDCWC3NLNTLIMHXWA2YDBWY3BR24A)