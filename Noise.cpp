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

#include "Noise.h"

FFGL_PLUGIN(Noise,"DZNZ","Noise",FF_SOURCE,"Sample FFGL Plugin",
"by Darren Mothersele - www.darrenmothersele.com")


std::string fragmentShaderCode = R"GLSL(

uniform float     blur;
uniform float     voronoi;
uniform vec3      iResolution;
uniform float noiseSize;

vec3 hash3( vec2 p )
{
    vec3 q = vec3( dot(p,vec2(127.1,311.7)),
				   dot(p,vec2(269.5,183.3)),
				   dot(p,vec2(419.2,371.9)) );
	return fract(sin(q)*43758.5453);
}

float iqnoise( in vec2 x, float u, float v )
{
    vec2 p = floor(x);
    vec2 f = fract(x);

	float k = 1.0+63.0*pow(1.0-v,4.0);

	float va = 0.0;
	float wt = 0.0;
    for( int j=-2; j<=2; j++ )
    for( int i=-2; i<=2; i++ )
    {
        vec2 g = vec2( float(i),float(j) );
		vec3 o = hash3( p + g )*vec3(u,u,1.0);
		vec2 r = g - f + o.xy;
		float d = dot(r,r);
		float ww = pow( 1.0-smoothstep(0.0,1.414,sqrt(d)), k );
		va += o.z*ww;
		wt += ww;
    }

    return va/wt;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = fragCoord.xy / iResolution.xx;
    vec2 p = vec2(voronoi, blur);
	float f = iqnoise( noiseSize*uv, p.x, p.y );
	fragColor = vec4( f, f, f, 1.0 );
}

void main(void) {
mainImage(gl_FragColor, gl_FragCoord.xy);
}

)GLSL";

PluginConfig Noise::getConfig() {
    PluginConfig pluginConfig;
    pluginConfig.shaderCode = fragmentShaderCode;
    pluginConfig.params.push_back({"Voronoi", FF_TYPE_STANDARD, 0.5f});
    pluginConfig.params.push_back({"Blur", FF_TYPE_STANDARD, 0.5f});
    pluginConfig.params.push_back({"Size", FF_TYPE_STANDARD, 0.5f});
    pluginConfig.inputNames.push_back({"iChannel0"});
    return pluginConfig;
}

void Noise::init(FFGLShader &shader) {
    sizeLocation = shader.FindUniform("noiseSize");
    resolutionLocation = shader.FindUniform("iResolution");
    blurLocation = shader.FindUniform("blur");
    voronoiLocation = shader.FindUniform("voronoi");
}

void Noise::process(std::vector<float> &paramValues, FFGLExtensions &extensions)
{
    float vpdim[4];
    glGetFloatv(GL_VIEWPORT, vpdim);
    extensions.glUniform3fARB(resolutionLocation, vpdim[2], vpdim[3], 1.0);

    extensions.glUniform1fARB(voronoiLocation, paramValues[0]);
    extensions.glUniform1fARB(blurLocation, paramValues[1]);
    extensions.glUniform1fARB(sizeLocation, paramValues[2] * 128.0f);

}

