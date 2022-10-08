#include "GameApp.h"
#include "d3dUtil.h"
#include "DXTrace.h"
#include <random>
#include <iostream>
#include <fstream>

#include "HardCode.h"
#include "WICTextureLoader11.h"
#include "DDSTextureLoader11.h"

using namespace DirectX;

GameApp::GameApp(HINSTANCE hInstance, const std::wstring& windowName, int initWidth, int initHeight)
    : D3DApp(hInstance, windowName, initWidth, initHeight), 
    m_VSConstantBuffer(),
    m_PSConstantBuffer(),
    m_DirLight(),
    m_PointLight1(),
    m_PointLight2(),
    m_PointLight3(),
    m_SpotLight(),
    m_IsWireframeMode(false)
{
}

GameApp::~GameApp()
{
}

bool GameApp::Init()
{
    if (!D3DApp::Init())
        return false;

    if (!InitEffect())
        return false;

    if (!InitResource())
        return false;

    return true;
}

void GameApp::OnResize()
{
    D3DApp::OnResize();
}

void GameApp::UpdateScene(float dt)
{
    //更新PS常量缓冲区的时间变量
    static float time = 0;
	time += dt;
    time = time >= 1.f ? 0 : time;
	m_PSConstantBuffer.time = XMFLOAT4(time, 0.f, 0.f, 0.f);

    // 获取IO事件
    ImGuiIO& io = ImGui::GetIO();

    //
    // 自定义IO
    //
    //汉字自旋角，汉字缩放，投影视场角
    static float  phi = 0.0f, theta = 0.0f, scale = 1.0f, fov = XM_PIDIV2;
    //WASD相机位移
    static float dWS = 0.f, dAD = 0.f;
    //QE相机滚筒旋转
    static float rollQE = 0.f;
    //鼠标滑动调整飞行方向(左右和仰俯)
    static float flyDirX = 0.f, flyDirY = 0.f;
    //绕汉字旋转的汉字的旋转角
    static float rotateAngle = 0;
    static bool animation = true, customColor = false;
    //是否开启动画
    if (animation)
    {
        //自转
        phi += 0.3f * dt, theta += 0.37f * dt;
        phi = XMScalarModAngle(phi);
        theta = XMScalarModAngle(theta);
        //公转
        rotateAngle += 2 * dt;
        rotateAngle = XMScalarModAngle(rotateAngle);
    }
    //光源开关
    static bool dirLightSwitch = true;
    static bool pointLightSwitch = false;
    static bool spotLightSwitch = false;

    //UI界面逻辑
    if (ImGui::Begin("ImGui"))
    {
        ImGui::Checkbox("Animation", &animation);

        if(dirLightSwitch)  ImGui::Text("dirLightSwitch is on !");
        else  ImGui::Text("dirLightSwitch is off !");

        if (pointLightSwitch)  ImGui::Text("pointLightSwitch is on !");
        else  ImGui::Text("pointLightSwitch is off !");

        if (spotLightSwitch)  ImGui::Text("spotLightSwitch is on !");
        else  ImGui::Text("spotLightSwitch is off !");

    }

    // 不允许在操作UI时漫游
    // IO逻辑
    if (!ImGui::IsAnyItemActive())
    {
        //WASD移动
        if (ImGui::IsKeyDown(ImGuiKey_W))
            dWS += dt * 2;
        if (ImGui::IsKeyDown(ImGuiKey_S))
            dWS -= dt * 2;
        if (ImGui::IsKeyDown(ImGuiKey_A))
            dAD += dt * 2;
        if (ImGui::IsKeyDown(ImGuiKey_D))
            dAD -= dt * 2;
        //QE滚筒旋转
        if (ImGui::IsKeyDown(ImGuiKey_Q))
            rollQE += dt * 2;
        if (ImGui::IsKeyDown(ImGuiKey_E))
            rollQE -= dt * 2;
        rollQE = XMScalarModAngle(rollQE);
        //鼠标滑动调整飞行方向
        flyDirX += io.MouseDelta.y * 0.0005f;
        flyDirY += io.MouseDelta.x * 0.0005f;
        flyDirX = XMScalarModAngle(flyDirX);
        flyDirY = XMScalarModAngle(flyDirY);
        //1 方向光
        if (ImGui::IsKeyPressed(ImGuiKey_1))
        {
            dirLightSwitch = !dirLightSwitch;
        }
        //2 点光
        if (ImGui::IsKeyPressed(ImGuiKey_2))
        {
            pointLightSwitch = !pointLightSwitch;
        }
        //3 聚光
        if (ImGui::IsKeyPressed(ImGuiKey_3))
        {
            spotLightSwitch = !spotLightSwitch;
        }
    }

    if (dirLightSwitch == false)  m_PSConstantBuffer.dirLight = DirectionalLight();
    else m_PSConstantBuffer.dirLight = m_DirLight;

    if (pointLightSwitch == false)
    {
        m_PSConstantBuffer.pointLight1 = PointLight();
        m_PSConstantBuffer.pointLight2 = PointLight();
        m_PSConstantBuffer.pointLight3 = PointLight();
    }
    else
    {
        m_PSConstantBuffer.pointLight1 = m_PointLight1;
        m_PSConstantBuffer.pointLight2 = m_PointLight2;
        m_PSConstantBuffer.pointLight3 = m_PointLight3;
    }

    if (spotLightSwitch == false) m_PSConstantBuffer.spotLight = SpotLight();
    else m_PSConstantBuffer.spotLight = m_SpotLight;

    ImGui::End();
    ImGui::Render();

    assert(m_pd3dImmediateContext);
    assert(m_pSwapChain);

    m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), reinterpret_cast<const float*>(&Colors::Black));
    m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    
    //相机漫游
    m_VSConstantBuffer.view = XMMatrixTranspose(
        XMMatrixLookAtLH(
            XMVectorSet(0.f, 0.f, dWS - 7.0f, 0.f), //WS前后移动
            XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
            XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)) *
        XMMatrixTranslation(dAD, 0.f, 0.f) * //AD左右移动
        XMMatrixRotationZ(rollQE) * //QE滚筒旋转
        XMMatrixRotationX(flyDirX) *
        XMMatrixRotationY(flyDirY)  //鼠标调整飞行方向
    );
    m_VSConstantBuffer.proj = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, AspectRatio(), 1.0f, 1000.0f));


    //点光运动
    std::default_random_engine e;
    std::uniform_real_distribution<float> u(-1., 1.);
    static XMVECTOR position1 = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    static XMVECTOR position2 = XMVectorSet(1.f, 1.f, 0.f, 1.f);
    static XMVECTOR position3 = XMVectorSet(-1.f, -1.f, 0.f, 1.f);
    position1 = XMVector4Transform(position1, XMMatrixTranslation(dt * u(e), dt * u(e), 0));
    position1 = XMVector4Transform(position1, XMMatrixRotationAxis({ 0,0,1 }, rotateAngle / 10.f));
    XMStoreFloat3(&m_PointLight1.position, position1);
    position2 = XMVector4Transform(position2, XMMatrixTranslation(dt * u(e), dt * u(e), 0));
    position2 = XMVector4Transform(position2, XMMatrixRotationAxis({ 0,0,1 }, rotateAngle / 10.f));
    XMStoreFloat3(&m_PointLight2.position, position2);
    position3 = XMVector4Transform(position3, XMMatrixTranslation(dt * u(e), dt * u(e), 0));
    position3 = XMVector4Transform(position3, XMMatrixRotationAxis({ 0,0,1 }, rotateAngle / 10.f));
    XMStoreFloat3(&m_PointLight3.position, position3);

    if (fabs(m_PointLight1.position.x) > 3.f || fabs(m_PointLight1.position.y) > 3.f)
        position1 = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    if (fabs(m_PointLight2.position.x) > 3.f || fabs(m_PointLight2.position.y) > 3.f)
        position2 = XMVectorSet(1.f, 1.f, 0.f, 1.f);
    if (fabs(m_PointLight3.position.x) > 3.f || fabs(m_PointLight3.position.y) > 3.f)
        position3 = XMVectorSet(-1.f, -1.f, 0.f, 1.f);

    //聚光跟随相机
    XMFLOAT4X4 inverse;
    //求视点矩阵的逆，取出相机位置和方向，设置聚光
    XMStoreFloat4x4(&inverse, XMMatrixInverse(nullptr, m_VSConstantBuffer.view));
    m_SpotLight.position = XMFLOAT3(inverse._14,inverse._24,inverse._34);
    m_SpotLight.direction = XMFLOAT3(inverse._13, inverse._23, inverse._33);
    //更新PS缓存区中的眼睛位置
    m_PSConstantBuffer.eyePos = XMFLOAT4(inverse._14, inverse._24, inverse._34,0.f);


    //调试
    //std::ofstream ofs;
    //ofs.open("test.txt", std::ios::out);
    //ofs << inverse._11 << "," << inverse._12 << "," << inverse._13 << "," << inverse._14 << std::endl;
    //ofs << inverse._21 << "," << inverse._22 << "," << inverse._23 << "," << inverse._24 << std::endl;
    //ofs << inverse._31 << "," << inverse._32 << "," << inverse._33 << "," << inverse._34 << std::endl;
    //ofs << inverse._41 << "," << inverse._42 << "," << inverse._43 << "," << inverse._44 << std::endl;
    //ofs.close();
    //exit(0);

    SetPlane();
    SetHanzi(scale,theta,phi,rotateAngle);

    // 下面这句话会触发ImGui在Direct3D的绘制
    // 因此需要在此之前将后备缓冲区绑定到渲染管线上
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    HR(m_pSwapChain->Present(0, 0));
}



//更新常量缓冲区
void GameApp::UpdateConstantBuffer()
{
    D3D11_MAPPED_SUBRESOURCE mappedData;
    HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[0].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
    memcpy_s(mappedData.pData, sizeof(VSConstantBuffer), &m_VSConstantBuffer, sizeof(VSConstantBuffer));
    m_pd3dImmediateContext->Unmap(m_pConstantBuffers[0].Get(), 0);

    HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[1].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
    memcpy_s(mappedData.pData, sizeof(PSConstantBuffer), &m_PSConstantBuffer, sizeof(PSConstantBuffer));
    m_pd3dImmediateContext->Unmap(m_pConstantBuffers[1].Get(), 0);
}


//初始化着色器和顶点布局
bool GameApp::InitEffect()
{
    ComPtr<ID3DBlob> blob;

    //Plane
    // 创建顶点着色器
    HR(CreateShaderFromFile(L"HLSL\\VS_Plane.cso", L"HLSL\\VS_Plane.hlsl", "VS", "vs_5_0", blob.ReleaseAndGetAddressOf()));
    HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader_Plane.GetAddressOf()));
    // 创建并绑定顶点布局
    HR(m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, ARRAYSIZE(VertexPosNormalTex::inputLayout),
        blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout_Plane.GetAddressOf()));
    // 创建像素着色器
    HR(CreateShaderFromFile(L"HLSL\\PS_Plane.cso", L"HLSL\\PS_Plane.hlsl", "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
    HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader_Plane.GetAddressOf()));

    //Hanzi
    // 创建顶点着色器
    HR(CreateShaderFromFile(L"HLSL\\VS_Hanzi.cso", L"HLSL\\VS_Hanzi.hlsl", "VS", "vs_5_0", blob.ReleaseAndGetAddressOf()));
    HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader_Hanzi.GetAddressOf()));
    // 创建并绑定顶点布局
    HR(m_pd3dDevice->CreateInputLayout(VertexPosNormalColor::inputLayout, ARRAYSIZE(VertexPosNormalColor::inputLayout),
        blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout_Hanzi.GetAddressOf()));
    // 创建几何着色器
    HR(CreateShaderFromFile(L"HLSL\\GS_Hanzi.cso", L"HLSL\\GS_Hanzi.hlsl", "GS", "gs_5_0", blob.ReleaseAndGetAddressOf()));
    HR(m_pd3dDevice->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pGeometryShader_Hanzi.GetAddressOf()));
    // 创建像素着色器
    HR(CreateShaderFromFile(L"HLSL\\PS_Hanzi.cso", L"HLSL\\PS_Hanzi.hlsl", "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
    HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader_Hanzi.GetAddressOf()));

    return true;
}

//仅需初始化一次的资源
bool GameApp::InitResource()
{
    // ******************
    // 初始化纹理和采样器状态
    //

    // 初始化照片纹理
    HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), L"Texture\\photo.png", nullptr, m_pPhoto.GetAddressOf()));
   
    // 初始化采样器状态
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    HR(m_pd3dDevice->CreateSamplerState(&sampDesc, m_pSamplerState.GetAddressOf()));


    // ******************
    // 设置常量缓冲区描述
    //
    D3D11_BUFFER_DESC cbd;
    ZeroMemory(&cbd, sizeof(cbd));
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.ByteWidth = sizeof(VSConstantBuffer);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    // 新建用于VS和PS的常量缓冲区
    HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[0].GetAddressOf()));
    cbd.ByteWidth = sizeof(PSConstantBuffer);
    HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[1].GetAddressOf()));

    // ******************
    // 初始化默认光照
    // 
    
    // 方向光
    // Crimson   猩红 
    m_DirLight.ambient = XMFLOAT4(.86f, .08f, .24f, 1.0f);
    m_DirLight.diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
    m_DirLight.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
    m_DirLight.direction = XMFLOAT3(-0.577f, -0.577f, 0.577f);
    // 点光
    // SlateBlue	板岩暗蓝灰
    m_PointLight1.position = XMFLOAT3(0.0f, 0.0f, -10.0f);
    m_PointLight1.ambient = XMFLOAT4(.42f, .35f, .8f, 1.0f);
    m_PointLight1.diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
    m_PointLight1.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
    m_PointLight1.att = XMFLOAT3(0.0f, 0.1f, 0.0f);
    m_PointLight1.range = 1.0f;
    // 聚光灯
    // Gold	金
    m_SpotLight.position = XMFLOAT3(0.0f, 0.0f, -5.0f);
    m_SpotLight.direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
    m_SpotLight.ambient = XMFLOAT4(1.f, .84f, 0.f, 1.0f);
    m_SpotLight.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_SpotLight.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_SpotLight.att = XMFLOAT3(1.0f, 0.0f, 0.0f);
    m_SpotLight.spot = 12.0f;
    m_SpotLight.range = 10000.0f;
    // 初始化用于VS的常量缓冲区的值
    m_VSConstantBuffer.world = XMMatrixIdentity();			
    m_VSConstantBuffer.view = XMMatrixTranspose(XMMatrixLookAtLH(
        XMVectorSet(0.0f, 0.0f, -7.0f, 0.0f),
        XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
        XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
    ));
    m_VSConstantBuffer.proj = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, AspectRatio(), 1.0f, 1000.0f));
    m_VSConstantBuffer.worldInvTranspose = XMMatrixIdentity();
    
    // 初始化用于PS的常量缓冲区的值
    // 白色
    m_PSConstantBuffer.material.ambient = XMFLOAT4(1.f, 1.f, 1.f, 1.0f);
    m_PSConstantBuffer.material.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_PSConstantBuffer.material.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
    
    m_PointLight2 = m_PointLight1;
    m_PointLight3 = m_PointLight1;


    // 注意不要忘记设置此处的观察位置，否则高亮部分会有问题
    m_PSConstantBuffer.eyePos = XMFLOAT4(0.0f, 0.0f, -7.0f, 0.0f);

    // 更新PS常量缓冲区资源
    D3D11_MAPPED_SUBRESOURCE mappedData;
    HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[1].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
    memcpy_s(mappedData.pData, sizeof(PSConstantBuffer), &m_PSConstantBuffer, sizeof(PSConstantBuffer));
    m_pd3dImmediateContext->Unmap(m_pConstantBuffers[1].Get(), 0);

    // ******************
    // 初始化光栅化状态
    //
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.DepthClipEnable = true;
    HR(m_pd3dDevice->CreateRasterizerState(&rasterizerDesc, m_pRSWireframe.GetAddressOf()));


    // ******************
    // 设置调试对象名
    //
    D3D11SetDebugObjectName(m_pConstantBuffers[0].Get(), "VSConstantBuffer");
    D3D11SetDebugObjectName(m_pConstantBuffers[1].Get(), "PSConstantBuffer");

    return true;
}



//设置Plane
void GameApp::SetPlane()
{
    // ******************
    // 设置顶点缓冲区和索引缓冲区
    //

    // 释放旧资源
    m_pVertexBuffer.Reset();
    m_pIndexBuffer.Reset();

    // 创建Plane顶点
    VertexPosNormalTex* vertices = nullptr;
    Plane::CreateVertexs(&vertices, m_VertexCount_Plane);

    // 设置顶点缓冲区描述
    D3D11_BUFFER_DESC vbd;
    ZeroMemory(&vbd, sizeof(vbd));
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = m_VertexCount_Plane * sizeof VertexPosNormalTex;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    // 新建顶点缓冲区
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertices;
    HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));

    // 输入装配阶段的顶点缓冲区设置
    UINT stride = sizeof(VertexPosNormalTex);	// 跨越字节数
    UINT offset = 0;							// 起始偏移量

    m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

    // 创建Plane索引
    DWORD* indices = nullptr;
    Plane::CreateIndices(&indices, m_IndexCount_Plane);

    // 设置索引缓冲区描述
    D3D11_BUFFER_DESC ibd;
    ZeroMemory(&ibd, sizeof(ibd));
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = m_IndexCount_Plane * sizeof(DWORD);
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    // 新建索引缓冲区
    InitData.pSysMem = indices;
    HR(m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf()));
    // 输入装配阶段的索引缓冲区设置
    m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

    // 设置调试对象名
    D3D11SetDebugObjectName(m_pVertexBuffer.Get(), "VertexBuffer");
    D3D11SetDebugObjectName(m_pIndexBuffer.Get(), "IndexBuffer");

    //释放堆内存
    delete[] vertices;
    delete[] indices;

    // ******************
    // 给渲染管线各个阶段绑定好所需资源
    //

    // 设置图元类型，设定输入布局
    m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout_Plane.Get());

    // 绑定VS
    m_pd3dImmediateContext->VSSetShader(m_pVertexShader_Plane.Get(), nullptr, 0);
    // VS常量缓冲区对应HLSL寄存于b0的常量缓冲区
    m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pConstantBuffers[0].GetAddressOf());
    // 取消GS绑定
    m_pd3dImmediateContext->GSSetShader(nullptr, nullptr, 0);
    // 绑定PS
    m_pd3dImmediateContext->PSSetShader(m_pPixelShader_Plane.Get(), nullptr, 0);
    // PS常量缓冲区对应HLSL寄存于b1的常量缓冲区
    m_pd3dImmediateContext->PSSetConstantBuffers(1, 1, m_pConstantBuffers[1].GetAddressOf());
    // PS设置采样器和纹理
    m_pd3dImmediateContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
    m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pPhoto.GetAddressOf());

    // ******************
    // 设置调试对象名
    //
    D3D11SetDebugObjectName(m_pVertexLayout_Plane.Get(), "VertexPosNormalColorLayout_Plane");
    D3D11SetDebugObjectName(m_pVertexShader_Plane.Get(), "VS_Plane_Plane");
    D3D11SetDebugObjectName(m_pPixelShader_Plane.Get(), "PS_Plane_Plane");


    //更新常量缓冲区
    m_VSConstantBuffer.world = XMMatrixTranspose(
        XMMatrixScalingFromVector(XMVectorSet(1.f,2.f,2.f,0.f)));

    UpdateConstantBuffer();
    // 绘制顶点
    m_pd3dImmediateContext->DrawIndexed(m_IndexCount_Plane, 0, 0);
}

//设置汉字
void GameApp::SetHanzi(float scale, float theta, float phi, float rotateAngle)
{
    // ******************
    // 设置顶点缓冲区和索引缓冲区
    //

    // 释放旧资源
    m_pVertexBuffer.Reset();
    m_pIndexBuffer.Reset();

    // 创建Plane顶点
    VertexPosNormalColor* vertices = nullptr;
    Hanzi::CreateVertexs(&vertices, m_VertexCount_Hanzi);

    // 设置顶点缓冲区描述
    D3D11_BUFFER_DESC vbd;
    ZeroMemory(&vbd, sizeof(vbd));
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = m_VertexCount_Hanzi * sizeof VertexPosNormalColor;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    // 新建顶点缓冲区
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertices;
    HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));

    // 输入装配阶段的顶点缓冲区设置
    UINT stride = sizeof(VertexPosNormalColor);	// 跨越字节数
    UINT offset = 0;							// 起始偏移量

    m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

    // 创建Plane索引
    DWORD* indices = nullptr;
    Hanzi::CreateIndices(&indices, m_IndexCount_Hanzi);

    // 设置索引缓冲区描述
    D3D11_BUFFER_DESC ibd;
    ZeroMemory(&ibd, sizeof(ibd));
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = m_IndexCount_Hanzi * sizeof(DWORD);
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    // 新建索引缓冲区
    InitData.pSysMem = indices;
    HR(m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf()));
    // 输入装配阶段的索引缓冲区设置
    m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

    // 设置调试对象名
    D3D11SetDebugObjectName(m_pVertexBuffer.Get(), "VertexBuffer");
    D3D11SetDebugObjectName(m_pIndexBuffer.Get(), "IndexBuffer");

    //释放堆内存
    delete[] vertices;
    delete[] indices;

    // ******************
    // 给渲染管线各个阶段绑定好所需资源
    //

    // 设置图元类型，设定输入布局
    m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout_Hanzi.Get());

    // 绑定VS
    m_pd3dImmediateContext->VSSetShader(m_pVertexShader_Hanzi.Get(), nullptr, 0);
    // VS常量缓冲区对应HLSL寄存于b0的常量缓冲区
    m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pConstantBuffers[0].GetAddressOf());
    // 绑定GS
    m_pd3dImmediateContext->GSSetShader(m_pGeometryShader_Hanzi.Get(), nullptr, 0);
    // GS常量缓冲区对应HLSL寄存于b0的常量缓冲区
    m_pd3dImmediateContext->GSSetConstantBuffers(0, 1, m_pConstantBuffers[0].GetAddressOf());
    // 绑定PS
    m_pd3dImmediateContext->PSSetShader(m_pPixelShader_Hanzi.Get(), nullptr, 0);
    // PS常量缓冲区对应HLSL寄存于b1的常量缓冲区
    m_pd3dImmediateContext->PSSetConstantBuffers(1, 1, m_pConstantBuffers[1].GetAddressOf());

    // ******************
    // 设置调试对象名
    //
    D3D11SetDebugObjectName(m_pVertexLayout_Hanzi.Get(), "VertexPosNormalColorLayout_Hanzi");
    D3D11SetDebugObjectName(m_pVertexShader_Hanzi.Get(), "VS_Hanzi");
    D3D11SetDebugObjectName(m_pGeometryShader_Hanzi.Get(), "GS_Hanzi");
    D3D11SetDebugObjectName(m_pPixelShader_Hanzi.Get(), "PS_Hanzi");

    //一次画50*50*3=7500个楠字，每个楠字有两个楠字围绕其旋转
    //帧率60左右
    //绘制汉字
    for (int i = 0; i < 50; ++i)
    {
        for (int j = 0; j < 50; ++j)
        {
            //根据 i j 设置每个楠字的矩阵
            m_VSConstantBuffer.world = XMMatrixTranspose(
                XMMatrixScalingFromVector(XMVectorReplicate(scale * 0.06f * (1 - 0.018f * i) * (1 - 0.018f * j))) *
                XMMatrixRotationX(theta) *
                XMMatrixRotationY(phi) *
                XMMatrixTranslation(-8.f + 0.18f * i, -4.5f + 0.18f * j, 0.f));
            UpdateConstantBuffer();
            m_pd3dImmediateContext->DrawIndexed(m_IndexCount_Hanzi, 0, 0);

            //绕每个楠字X轴旋转一个
            m_VSConstantBuffer.world = XMMatrixTranspose(
                XMMatrixScalingFromVector(XMVectorReplicate(scale * 0.06f * (1 - 0.018f * i) * (1 - 0.018f * j))) * //缩放
                XMMatrixTranslation(0.f, 0.06f, 0.06f) * //离旋转轴的距离
                XMMatrixRotationAxis({ 1,0,0 }, rotateAngle) * //绕旋转轴旋转
                XMMatrixTranslation(-8.f + 0.18f * i, -4.5f + 0.18f * j, 0.f)); //随旋转轴楠字的位置移动
            UpdateConstantBuffer();
            m_pd3dImmediateContext->DrawIndexed(m_IndexCount_Hanzi, 0, 0);

            //绕每个楠字Y轴旋转一个
            m_VSConstantBuffer.world = XMMatrixTranspose(
                XMMatrixScalingFromVector(XMVectorReplicate(scale * 0.06f * (1 - 0.018f * i) * (1 - 0.018f * j))) *
                XMMatrixTranslation(0.06f, 0.f, 0.06f) *
                XMMatrixRotationAxis({ 0,1,0 }, rotateAngle) *
                XMMatrixTranslation(-8.f + 0.18f * i, -4.5f + 0.18f * j, 0.f));
            UpdateConstantBuffer();
            m_pd3dImmediateContext->DrawIndexed(m_IndexCount_Hanzi, 0, 0);
        }
    }
    
}


