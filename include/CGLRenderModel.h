//
// Created by joosep on 4/20/18.
//

#ifndef FRACTALVR_CGLRENDERMODEL_H
#define FRACTALVR_CGLRENDERMODEL_H

#include <string>
#include <openvr.h>
#include <SDL2/SDL_opengl.h>

class CGLRenderModel
{
public:
    CGLRenderModel( const std::__cxx11::string & sRenderModelName );
    ~CGLRenderModel();

    bool BInit(const vr::RenderModel_t & vrModel, const vr::RenderModel_TextureMap_t & vrDiffuseTexture );
    void Cleanup();
    void Draw();
    const std::__cxx11::string & GetName() const { return m_sModelName; }

private:
    GLuint m_glVertBuffer;
    GLuint m_glIndexBuffer;
    GLuint m_glVertArray;
    GLuint m_glTexture;
    GLsizei m_unVertexCount;
    std::__cxx11::string m_sModelName;
};

#endif //FRACTALVR_CGLRENDERMODEL_H
