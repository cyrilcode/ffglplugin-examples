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


#include "Spiral.h"


FFGL_PLUGIN(Spiral,"DZSP","Spiral Source",FF_SOURCE,"Sample FFGL Plugin",
"by Darren Mothersele - www.darrenmothersele.com")


std::string fragmentShaderCode = R"GLSL(

uniform vec3      iResolution;
uniform float     iGlobalTime;

// Original shader by s23b https://www.shadertoy.com/user/s23b
// Adapted from https://www.shadertoy.com/view/4st3WX
#define PI 3.14159265359

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord.xy / iResolution.xy / .5 - 1.;
    uv.x *= iResolution.x / iResolution.y;

    // make a tube
    float f = 1. / length(uv);

    // add the angle
    f += atan(uv.x, uv.y) / acos(0.);

    // let's roll
    f -= iGlobalTime;

    // make it black and white
    // old version without AA: f = floor(fract(f) * 2.);
    // new version based on Shane's suggestion:
    f = 1. - clamp(sin(f * PI * 2.) * dot(uv, uv) * iResolution.y / 15. + .5, 0., 1.);

    // add the darkness to the end of the tunnel
    f *= sin(length(uv) - .1);

    fragColor = vec4(f, f, f, 1.0);
}

void main(void) {
mainImage(gl_FragColor, gl_FragCoord.xy);
}

)GLSL";

PluginConfig Spiral::getConfig() {
    PluginConfig pluginConfig;
    pluginConfig.shaderCode = fragmentShaderCode;
    pluginConfig.params.push_back({"Speed", FF_TYPE_STANDARD, 0.5f});
    pluginConfig.inputNames.push_back({"iChannel0"});
    return pluginConfig;
}

void Spiral::init(FFGLShader &shader) {
    timeLocation = shader.FindUniform("iGlobalTime");
    resolutionLocation = shader.FindUniform("iResolution");
    start = std::chrono::steady_clock::now();
}

void Spiral::process(std::vector<float> &paramValues, FFGLExtensions &extensions)
{
    float vpdim[4];
    glGetFloatv(GL_VIEWPORT, vpdim);
    extensions.glUniform3fARB(resolutionLocation, vpdim[2], vpdim[3], 1.0);

    double lastTime = elapsedTime;
    elapsedTime = GetCounter()/1000.0;
    globalTime = globalTime + (float)(elapsedTime-lastTime) * (paramValues[0] - 0.5f) * 8.0f;
    extensions.glUniform1fARB(timeLocation, globalTime);
}


double Spiral::GetCounter()
{
    end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000.;
}