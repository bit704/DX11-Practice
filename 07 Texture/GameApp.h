#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "d3dApp.h"
#include "LightHelper.h"
#include "Geometry.h"

class GameApp : public D3DApp
{
public:

    struct VSConstantBuffer
    {
        DirectX::XMMATRIX world;
        DirectX::XMMATRIX view;
        DirectX::XMMATRIX proj;
        DirectX::XMMATRIX worldInvTranspose;
        
    };

    struct PSConstantBuffer
    {
        DirectionalLight dirLight;
        PointLight pointLight1;
        PointLight pointLight2;
        PointLight pointLight3;
        SpotLight spotLight;
        Material material;
        DirectX::XMFLOAT4 eyePos;
        DirectX::XMFLOAT4 time;
    };



public:
    GameApp(HINSTANCE hInstance, const std::wstring& windowName, int initWidth, int initHeight);
    ~GameApp();

    bool Init();
    void OnResize();
    void UpdateScene(float dt);
    void UpdateConstantBuffer();
    void SetPlane();
    void SetHanzi(float scale, float theta, float phi, float rotateAngle);


private:
    bool InitEffect();
    bool InitResource();


private:
    
    ComPtr<ID3D11Buffer> m_pVertexBuffer;			// 顶点缓冲区
    ComPtr<ID3D11Buffer> m_pIndexBuffer;			// 索引缓冲区
    ComPtr<ID3D11Buffer> m_pConstantBuffers[2];	    // 常量缓冲区
    

    ComPtr<ID3D11ShaderResourceView> m_pPhoto;			    // 照片纹理
    ComPtr<ID3D11SamplerState> m_pSamplerState;				// 采样器状态

    //Plane
    ComPtr<ID3D11InputLayout> m_pVertexLayout_Plane;	    // 顶点输入布局
    ComPtr<ID3D11VertexShader> m_pVertexShader_Plane;	    // 顶点着色器
    ComPtr<ID3D11PixelShader> m_pPixelShader_Plane;		   // 像素着色器
    UINT m_VertexCount_Plane = 4;							    // 物体的顶点数组大小
    UINT m_IndexCount_Plane = 6;							    // 绘制物体的索引数组大小

    //Hanzi
    ComPtr<ID3D11InputLayout> m_pVertexLayout_Hanzi;	    // 顶点输入布局
    ComPtr<ID3D11VertexShader> m_pVertexShader_Hanzi;	    // 顶点着色器
    ComPtr<ID3D11GeometryShader> m_pGeometryShader_Hanzi;	    // 几何着色器
    ComPtr<ID3D11PixelShader> m_pPixelShader_Hanzi;		   // 像素着色器
    UINT m_VertexCount_Hanzi = 104;							    // 物体的顶点数组大小
    UINT m_IndexCount_Hanzi = 492;							    // 绘制物体的索引数组大小


    VSConstantBuffer m_VSConstantBuffer;			// 用于修改用于VS的GPU常量缓冲区的变量
    PSConstantBuffer m_PSConstantBuffer;			// 用于修改用于PS的GPU常量缓冲区的变量

    DirectionalLight m_DirLight;					// 默认环境光
    PointLight m_PointLight1;						// 默认点光
    PointLight m_PointLight2;
    PointLight m_PointLight3;
    SpotLight m_SpotLight;						    // 默认汇聚光

    ComPtr<ID3D11RasterizerState> m_pRSWireframe;	// 光栅化状态: 线框模式
    bool m_IsWireframeMode;							// 当前是否为线框模式
    
};


#endif