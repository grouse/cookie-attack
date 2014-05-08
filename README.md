Cookie Attack!
====
To further the development of JEngine, I take to space with asteroids-esque gameplay and movement system. The news for the engine as a result of this project are as follows:

+ __Entity & Component System__: the engine now features a data-driven entity-component system, using sub-systems to handle the logic that couples the components together and make up the game mechanics.
+ __Textures__: using the power of OpenGL and stb_image library, the engine now supports texture loading using the common image formats.
+ __Improved Collision System__: the new and improved collision system handles collision between rotated bounding boxes.

## Dependencies
The code is compiled using g++ -std=c++11 and requires installed OpenGL and SDL2.0 libraries.

## License
The code in this project is under a zlib license, attached below, and you are as such free to use any and all code for whatever purpose you see fit. Any and all assets included are my property and my explicit permission is required to use them for any purpose.

### zlib license
Copyright (c) 2014 Jesper "Grouse" Stefansson

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
