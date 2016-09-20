/*
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
                    Version 2, December 2004 

 Copyright (C) 2016 Darren Mothersele <me@daz.is> 

 Everyone is permitted to copy and distribute verbatim or modified 
 copies of this license document, and changing it is allowed as long 
 as the name is changed. 

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 

  0. You just DO WHAT THE FUCK YOU WANT TO.
*/


#ifndef FFGLPLUGIN_EVILSHADER_H
#define FFGLPLUGIN_EVILSHADER_H

#include "MyPlugin.h"

class EvilShader {

    GLint resValueLocation;
    GLint inputTextureLocation;

public:
    PluginConfig getConfig();

    void init(FFGLShader &shader);
    void process(std::vector<float> &paramValues, FFGLExtensions &extensions);


};


#endif //FFGLPLUGIN_EVILSHADER_H
