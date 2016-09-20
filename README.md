#FFGL Plugins

Framework for creating FFGL plugins for Resolume.


## Usage

MyPlugin.h abstracts some of the repetative stuff you have to do when 
creating FFGL plugins. 

See EmptyEffect for most basic use case.

Compile as 32-bit for Resolume compatibility. 

## Installation

Copy the compiled `*.bundle` files into your Resolume plugins folder.
Or preferably, create a new folder and link to it in the Resolume config.



## License  

These plugin source code files are licensed under WTFPL.
See LICENSE.md for details.

The FFGL Plugin code license is in ffgl-host/License.txt

Some of the plugins have code borrowed from ShaderToy. 
See individual plugin source files for more details.

* Evil Shader adapted from https://www.shadertoy.com/view/llS3WG
* Noise uses voronoise from the amazing Inigo Quilez 
  (http://www.iquilezles.org/www/articles/voronoise/voronoise.htm)
* Plasma Globe by nimitz (twitter: @stormoid)
* Spiral adapter from https://www.shadertoy.com/view/4st3WX
* Crazy Springs by eiffie https://www.shadertoy.com/view/ld23DG
* Underwater Life adapted from https://www.shadertoy.com/view/Mtf3Rr
