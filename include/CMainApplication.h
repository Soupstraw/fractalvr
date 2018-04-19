//
// Created by joosep on 4/20/18.
//

#ifndef FRACTALVR_CMAINAPPLICATION_H
#define FRACTALVR_CMAINAPPLICATION_H

#ifndef _countof
#define _countof(x) (sizeof(x)/sizeof((x)[0]))
#endif

#include <openvr.h>
#include <vector>
#include "Matrices.h"
#include "CGLRenderModel.h"

class CMainApplication
{
public:
    CMainApplication( int argc, char *argv[] );
    virtual ~CMainApplication();

    bool BInit();
    bool BInitGL();
    bool BInitCompositor();

    void SetupRenderModels();

    void Shutdown();

    void RunMainLoop();
    bool HandleInput();
    void ProcessVREvent( const vr::VREvent_t & event );
    void RenderFrame();

    void SetupScene();

    void RenderControllerAxes();

    bool SetupStereoRenderTargets();
    void SetupCompanionWindow();
    void SetupCameras();

    void RenderStereoTargets();
    void RenderCompanionWindow();
    void RenderScene(vr::Hmd_Eye nEye, GLint renderWidth, GLint renderHeight );
    std::__cxx11::string LoadShader(std::__cxx11::string filename);

    Matrix4 GetHMDMatrixProjectionEye( vr::Hmd_Eye nEye );
    Matrix4 GetHMDMatrixPoseEye( vr::Hmd_Eye nEye );
    Matrix4 GetCurrentViewMatrix( vr::Hmd_Eye nEye );
    Matrix4 GetCurrentProjectionMatrix( vr::Hmd_Eye nEye );
    void UpdateHMDMatrixPose();

    Matrix4 ConvertSteamVRMatrixToMatrix4( const vr::HmdMatrix34_t &matPose );

    GLuint CompileGLShader( const char *pchShaderName, const char *pchVertexShader, const char *pchFragmentShader );
    bool CreateAllShaders();

    void SetupRenderModelForTrackedDevice( vr::TrackedDeviceIndex_t unTrackedDeviceIndex );
    CGLRenderModel *FindOrLoadRenderModel( const char *pchRenderModelName );

private:
    bool m_bDebugOpenGL;
    bool m_bVerbose;
    bool m_bPerf;
    bool m_bVblank;
    bool m_bGlFinishHack;
    bool m_bSteamVR;

    std::__cxx11::string raycastShader;
    std::__cxx11::string acceleratorShader;

    vr::IVRSystem *m_pHMD;
    vr::IVRRenderModels *m_pRenderModels;
    std::__cxx11::string m_strDriver;
    std::__cxx11::string m_strDisplay;
    vr::TrackedDevicePose_t m_rTrackedDevicePose[ vr::k_unMaxTrackedDeviceCount ];
    Matrix4 m_rmat4DevicePose[ vr::k_unMaxTrackedDeviceCount ];
    bool m_rbShowTrackedDevice[ vr::k_unMaxTrackedDeviceCount ];

private: // SDL bookkeeping
    SDL_Window *m_pCompanionWindow;
    uint32_t m_nCompanionWindowWidth;
    uint32_t m_nCompanionWindowHeight;

    SDL_GLContext m_pContext;

private: // OpenGL bookkeeping
    int m_iTrackedControllerCount;
    int m_iTrackedControllerCount_Last;
    int m_iValidPoseCount;
    int m_iValidPoseCount_Last;
    bool m_bShowCubes;

    std::__cxx11::string m_strPoseClasses;                            // what classes we saw poses for this frame
    char m_rDevClassChar[ vr::k_unMaxTrackedDeviceCount ];   // for each device, a character representing its class

    int m_iSceneVolumeInit;                                  // if you want something other than the default 20x20x20

    float m_fNearClip;
    float m_fFarClip;

    GLuint m_glSceneVertBuffer;
    GLuint m_unSceneVAO;
    GLuint m_unCompanionWindowVAO;
    GLuint m_glCompanionWindowIDVertBuffer;
    GLuint m_glCompanionWindowIDIndexBuffer;
    unsigned int m_uiCompanionWindowIndexSize;

    GLuint m_glControllerVertBuffer;
    GLuint m_unControllerVAO;
    unsigned int m_uiControllerVertcount;

    Matrix4 m_mat4HMDPose;
    Matrix4 m_mat4eyePosLeft;
    Matrix4 m_mat4eyePosRight;

    Matrix4 m_mat4ProjectionLeft;
    Matrix4 m_mat4ProjectionRight;

    struct VertexDataWindow
    {
        Vector2 position;
        Vector2 texCoord;

        VertexDataWindow( const Vector2 & pos, const Vector2 tex ) :  position(pos), texCoord(tex) {	}
    };

    GLuint m_unSceneProgramID;
    GLuint m_unAcceleratorProgramID;
    GLuint m_unCompanionWindowProgramID;
    GLuint m_unControllerTransformProgramID;
    GLuint m_unRenderModelProgramID;

    GLint m_nProjectLoc;
    GLint m_nViewMatrixLoc;
    GLint m_nProjectionMatrixLoc;
    GLint m_nScreenSizeLoc;
    GLint m_nControllerMatrixLocation;
    GLint m_nRenderModelMatrixLocation;

    int m_nKernelSize;

    struct FramebufferDesc
    {
        GLuint m_nDepthBufferId;
        GLuint m_nRenderTextureId;
        GLuint m_nRenderFramebufferId;
        GLuint m_nAcceleratedFramebufferId;
        GLuint m_nAcceleratedTextureId;
        GLuint m_nResolveTextureId;
        GLuint m_nResolveFramebufferId;
    };
    FramebufferDesc leftEyeDesc;
    FramebufferDesc rightEyeDesc;

    bool CreateFrameBuffer( int nWidth, int nHeight, FramebufferDesc &framebufferDesc );

    uint32_t m_nRenderWidth;
    uint32_t m_nRenderHeight;

    std::vector< CGLRenderModel * > m_vecRenderModels;
    CGLRenderModel *m_rTrackedDeviceToRenderModel[ vr::k_unMaxTrackedDeviceCount ];

    std::string
    GetTrackedDeviceString(vr::IVRSystem *pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop,
                           vr::TrackedPropertyError *peError);
};

#endif //FRACTALVR_CMAINAPPLICATION_H
