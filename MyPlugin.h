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

#ifndef FFGLPLUGIN_MYPLUGIN_H
#define FFGLPLUGIN_MYPLUGIN_H

#include <FFGLPluginSDK.h>
#include <FFGLExtensions.h>
#include <FFGLShader.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <FFGLLib.h>

#define FFGL_PLUGIN(CLASS,CODE,NAME,TYPE,DESC,ABOUT) \
    static CFFGLPluginInfo PluginInfo (MyPlugin<CLASS>::CreateInstance, \
    CODE,NAME,1,000,1,000,TYPE,DESC,ABOUT);

char *vertexShaderCode =
        "void main()"
                "{"
                "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
                "  gl_TexCoord[1] = gl_MultiTexCoord1;"
                "  gl_FrontColor = gl_Color;"
                "}";

class PluginParamInfo {
public:
    std::string name;
    DWORD type;
    float defaultValue;
    PluginParamInfo(std::string n, DWORD t, float d) : name(n), type(t), defaultValue(d) {}
};

class PluginConfig {
public:
    std::vector<std::string> inputNames;
    std::vector<PluginParamInfo> params;
    std::string shaderCode;
};

template <class FX>
class MyPlugin : public CFreeFrameGLPlugin {
    FX fx;
    PluginConfig config;
    std::unordered_map<std::string,DWORD> paramMap;
    std::vector<float> paramValues;
    DWORD paramCount;
    DWORD inputCount;
    std::vector<GLint> textureLocations;

public:
    MyPlugin() {
        fx = FX();
        config = fx.getConfig();
        SetMinInputs(static_cast<int>(config.inputNames.size()));
        SetMaxInputs(static_cast<int>(config.inputNames.size()));
        paramCount = 0;
        for (auto i : config.params)
        {
            paramMap.insert({i.name, paramCount});
            SetParamInfo(paramCount, i.name.c_str(), i.type, i.defaultValue);
            paramCount++;
        }
        paramValues.reserve(paramCount);
        inputCount = config.inputNames.size();
    }
    ~MyPlugin() {}

    DWORD ProcessOpenGL(ProcessOpenGLStruct* pGL)
    {
        if (pGL->numInputTextures < inputCount) return FF_FAIL;

        shader.BindShader();

        if (inputCount > 0)
        {
            FFGLTextureStruct &Texture = *(pGL->inputTextures[0]);
            extensions.glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, Texture.Handle);
            FFGLTexCoords maxCoords = GetMaxGLTexCoords(Texture);

            fx.process(paramValues, extensions);

            glEnable(GL_TEXTURE_2D);

            glBegin(GL_QUADS);

            //lower left
            glTexCoord2f(0,0);
            glVertex2f(-1,-1);

            //upper left
            glTexCoord2f(0, maxCoords.t);
            glVertex2f(-1,1);

            //upper right
            glTexCoord2f(maxCoords.s, maxCoords.t);
            glVertex2f(1,1);

            //lower right
            glTexCoord2f(maxCoords.s, 0);
            glVertex2f(1,-1);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, 0);
        }
        else
        {
            fx.process(paramValues, extensions);
            glBegin(GL_QUADS);
            glVertex2f(-1.0f, -1.0f);
            glVertex2f(-1.0f,  1.0);
            glVertex2f( 1.0,  1.0);
            glVertex2f( 1.0, -1.0f);
            glEnd();
        }

        shader.UnbindShader();
        return FF_SUCCESS;
    }
    DWORD InitGL(const FFGLViewportStruct *vp)
    {
        extensions.Initialize();
        if (extensions.multitexture==0 || extensions.ARB_shader_objects==0)
            return FF_FAIL;

        shader.SetExtensions(&extensions);
        shader.Compile(vertexShaderCode,config.shaderCode.c_str());
        shader.BindShader();
        for (auto i : config.inputNames)
        {
            GLint texLoc = shader.FindUniform(i.c_str());
            textureLocations.push_back(texLoc);
            extensions.glUniform1iARB(texLoc, 0);
        }
        fx.init(shader);
        shader.UnbindShader();
        return FF_SUCCESS;
    }
    DWORD DeInitGL()
    {
        shader.FreeGLResources();
        return FF_SUCCESS;
    }

    DWORD	SetParameter(const SetParameterStruct* pParam) {
        if (pParam != NULL) {
            if (pParam->ParameterNumber < paramCount) {
                paramValues[pParam->ParameterNumber] = *((float *)(unsigned)&(pParam->NewParameterValue));
                return FF_SUCCESS;
            }
        }
        return FF_FAIL;
    }

    static DWORD __stdcall CreateInstance(CFreeFrameGLPlugin **ppOutInstance) {
        *ppOutInstance = new MyPlugin();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

    FFGLExtensions extensions;
    FFGLShader shader;
};


#endif //FFGLPLUGIN_MYPLUGIN_H

