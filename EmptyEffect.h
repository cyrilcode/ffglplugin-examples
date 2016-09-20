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


#ifndef FFGLPLUGIN_EMPTYEFFECT_H
#define FFGLPLUGIN_EMPTYEFFECT_H

#include "MyPlugin.h"

class EmptyEffect {

    float redness = 0.5f;
    float greenness = 0.5f;
    float blueness = 0.5f;
    GLint colorLocation;

public:
    PluginConfig getConfig();

    void init(FFGLShader &shader);
    void process(std::vector<float> &paramValues, FFGLExtensions &extensions);

};


#endif //FFGLPLUGIN_EMPTYEFFECT_H
