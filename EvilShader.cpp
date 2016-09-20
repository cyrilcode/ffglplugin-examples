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

#include "EvilShader.h"

FFGL_PLUGIN(EvilShader,"DZEV","Evil",FF_EFFECT,"Sample FFGL Plugin",
"by Darren Mothersele - www.darrenmothersele.com")


std::string fragmentShaderCode = R"GLSL(
// Adapted from https://www.shadertoy.com/view/llS3WG

uniform vec3      iResolution;
uniform sampler2D iChannel0;

#define T texture2D(iChannel0,.5+(p.xy*=.98))
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec3 p=gl_FragCoord.xyz/iResolution-.5, o=T.rbb;
	for (float i=0.;i<50.;i++) p.z+=pow(max(0.,.5-length(T.rg)),2.)*exp(-i*.1);
	fragColor=vec4(o*o+p.z,1);
}
void main(void) {
mainImage(gl_FragColor, gl_FragCoord.xy);
}

)GLSL";


PluginConfig EvilShader::getConfig() {
    PluginConfig pluginConfig;
    pluginConfig.shaderCode = fragmentShaderCode;
    pluginConfig.params.push_back({"Speed", FF_TYPE_STANDARD, 0.5f});
    pluginConfig.inputNames.push_back({"iChannel0"});
    return pluginConfig;
}

void EvilShader::init(FFGLShader &shader) {
    resValueLocation = shader.FindUniform("iResolution");
}

void EvilShader::process(std::vector<float> &paramValues, FFGLExtensions &extensions)
{
    float vpdim[4];
    glGetFloatv(GL_VIEWPORT, vpdim);
    extensions.glUniform3fARB(resValueLocation, vpdim[2], vpdim[3], 1.0);
}


