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


#include "EmptyEffect.h"


FFGL_PLUGIN(EmptyEffect,"DZ00","RGB Source",FF_SOURCE,"Sample FFGL Plugin",
    "by Darren Mothersele - www.darrenmothersele.com")


std::string fragmentShaderCode = R"GLSL(
uniform vec3 color;
void main()
{
    gl_FragColor = vec4(color,1);
}
)GLSL";

PluginConfig EmptyEffect::getConfig() {
    PluginConfig pluginConfig;
    pluginConfig.shaderCode = fragmentShaderCode;
    pluginConfig.params.push_back({"Red", FF_TYPE_STANDARD, 0.5f});
    pluginConfig.params.push_back({"Green", FF_TYPE_STANDARD, 0.5f});
    pluginConfig.params.push_back({"Blue", FF_TYPE_STANDARD, 0.5f});
    return pluginConfig;
}

void EmptyEffect::init(FFGLShader &shader) {
    colorLocation = shader.FindUniform("color");
}

void EmptyEffect::process(std::vector<float> &paramValues, FFGLExtensions &extensions)
{
    extensions.glUniform3fARB(colorLocation, paramValues[0], paramValues[1], paramValues[2]);
}

