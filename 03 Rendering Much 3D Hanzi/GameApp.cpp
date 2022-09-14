#include "GameApp.h"
#include "d3dUtil.h"
#include "DXTrace.h"

using namespace DirectX;

const D3D11_INPUT_ELEMENT_DESC GameApp::VertexPosColor::inputLayout[2] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};


GameApp::GameApp(HINSTANCE hInstance, const std::wstring& windowName, int initWidth, int initHeight)
    : D3DApp(hInstance, windowName, initWidth, initHeight), m_CBuffer()
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
    // ImGui内部示例窗口
    //ImGui::ShowAboutWindow();
    //ImGui::ShowDemoWindow();
    //ImGui::ShowUserGuide();

    // 获取IO事件
    ImGuiIO& io = ImGui::GetIO();
    
    //
    // 自定义窗口与操作
    //
    static float tx = 0.0f, ty = 0.0f, phi = 0.0f, theta = 0.0f, scale = 1.0f, fov = XM_PIDIV2;
    static float rotateAngle = 0;
    static bool animation = true, customColor = false;
    if (animation)
    {
        phi += 0.3f * dt, theta += 0.37f * dt;
        phi = XMScalarModAngle(phi);
        theta = XMScalarModAngle(theta);
        rotateAngle += 2 * dt;
        rotateAngle = XMScalarModAngle(rotateAngle);
    }
    if (ImGui::Begin("ImGui"))
    {
        ImGui::Checkbox("Animation", &animation);
        ImGui::SameLine(0.0f, 25.0f);
        if (ImGui::Button("Reset Params"))
        {
            tx = ty = phi = theta = 0.0f;
            scale = 1.0f;
            fov = XM_PIDIV2;
        }
        ImGui::SliderFloat("Scale", &scale, 0.2f, 2.0f);

        ImGui::Text("Phi: %.2f degrees", XMConvertToDegrees(phi));
        ImGui::SliderFloat("##1", &phi, -XM_PI, XM_PI, "");     // 不显示文字，但避免重复的标签
        ImGui::Text("Theta: %.2f degrees", XMConvertToDegrees(theta));
        ImGui::SliderFloat("##2", &theta, -XM_PI, XM_PI, "");

        ImGui::Text("Position: (%.1f, %.1f, 0.0)", tx, ty);

    }
    ImGui::End();
 
    // 不允许在操作UI时操作物体
    if (!ImGui::IsAnyItemActive())
    {
        // 鼠标左键拖动平移
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        {
            tx += io.MouseDelta.x * 0.01f;
            ty -= io.MouseDelta.y * 0.01f;
        }
        // 鼠标右键拖动旋转
        else if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
        {
            phi -= io.MouseDelta.y * 0.01f;
            theta -= io.MouseDelta.x * 0.01f;
            phi = XMScalarModAngle(phi);
            theta = XMScalarModAngle(theta);
        }
        // 鼠标滚轮缩放
        else if (io.MouseWheel != 0.0f)
        {
            scale += 0.02f * io.MouseWheel;
            if (scale > 2.0f)
                scale = 2.0f;
            else if (scale < 0.2f)
                scale = 0.2f;
        }
    }
    

    assert(m_pd3dImmediateContext);
    assert(m_pSwapChain);

    static float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA = (0,0,0,255)
    m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), reinterpret_cast<const float*>(&black));
    m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    //一次画一百个楠字，每个楠字有两个楠字围绕其旋转
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            //根据 i j 设置每个楠字的矩阵
            m_CBuffer.world = XMMatrixTranspose(
                XMMatrixScalingFromVector(XMVectorReplicate(scale*0.3*(1-0.07*i)*(1-0.07*j))) *
                XMMatrixRotationX(theta) * 
                XMMatrixRotationY(phi) *
                XMMatrixTranslation(-5 + tx + i, -4.5 + ty + j, 0.0f));
            // 更新常量缓冲区
            D3D11_MAPPED_SUBRESOURCE mappedData;
            HR(m_pd3dImmediateContext->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
            memcpy_s(mappedData.pData, sizeof(m_CBuffer), &m_CBuffer, sizeof(m_CBuffer));
            m_pd3dImmediateContext->Unmap(m_pConstantBuffer.Get(), 0);
            // 绘制
            m_pd3dImmediateContext->DrawIndexed(492, 0, 0);

           
            //绕每个楠字X轴旋转一个
            m_CBuffer.world = XMMatrixTranspose(
                XMMatrixScalingFromVector(XMVectorReplicate(scale * 0.3 * (1 - 0.07 * i) * (1 - 0.07 * j))) * //缩放
                XMMatrixTranslation(0.3, 0.3, 0.3f) * //离旋转轴的距离
                XMMatrixRotationAxis({1,0,0},rotateAngle) * //绕旋转轴旋转
                XMMatrixTranslation(-5 + tx + i, -4.5 + ty + j, 0.0f)); //随旋转轴楠字的位置移动
            // 更新常量缓冲区
            HR(m_pd3dImmediateContext->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
            memcpy_s(mappedData.pData, sizeof(m_CBuffer), &m_CBuffer, sizeof(m_CBuffer));
            m_pd3dImmediateContext->Unmap(m_pConstantBuffer.Get(), 0);
            // 绘制
            m_pd3dImmediateContext->DrawIndexed(492, 0, 0);


            //绕每个楠字Y轴旋转一个
            m_CBuffer.world = XMMatrixTranspose(
                XMMatrixScalingFromVector(XMVectorReplicate(scale * 0.3 * (1 - 0.07 * i) * (1 - 0.07 * j))) *
                XMMatrixTranslation(0.3, 0.3, 0.3f) * 
                XMMatrixRotationAxis({ 0,1,0 }, rotateAngle) * 
                XMMatrixTranslation(-5 + tx + i, -4.5 + ty + j, 0.0f));
            // 更新常量缓冲区
            HR(m_pd3dImmediateContext->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
            memcpy_s(mappedData.pData, sizeof(m_CBuffer), &m_CBuffer, sizeof(m_CBuffer));
            m_pd3dImmediateContext->Unmap(m_pConstantBuffer.Get(), 0);
            // 绘制
            m_pd3dImmediateContext->DrawIndexed(492, 0, 0);


        }
    }


    ImGui::Render();
    // 下面这句话会触发ImGui在Direct3D的绘制
    // 因此需要在此之前将后备缓冲区绑定到渲染管线上
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    HR(m_pSwapChain->Present(0, 0));
   
}

void GameApp::DrawScene()
{
    //DrawScene()部分直接接在UpdateScene(float dt)后面
    // 
    //assert(m_pd3dImmediateContext);
    //assert(m_pSwapChain);

    //static float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA = (0,0,0,255)
    //m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), reinterpret_cast<const float*>(&black));
    //m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


    //// 绘制楠字
    //m_pd3dImmediateContext->DrawIndexed(492, 0, 0);

    //ImGui::Render();
    //ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    //HR(m_pSwapChain->Present(0, 0));
}


bool GameApp::InitEffect()
{
    ComPtr<ID3DBlob> blob;

    // 创建顶点着色器
    HR(CreateShaderFromFile(L"HLSL\\Cube_VS.cso", L"HLSL\\Cube_VS.hlsl", "VS", "vs_5_0", blob.ReleaseAndGetAddressOf()));
    HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));
    // 创建顶点布局
    HR(m_pd3dDevice->CreateInputLayout(VertexPosColor::inputLayout, ARRAYSIZE(VertexPosColor::inputLayout),
        blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf()));

    // 创建像素着色器
    HR(CreateShaderFromFile(L"HLSL\\Cube_PS.cso", L"HLSL\\Cube_PS.hlsl", "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
    HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf()));

    return true;
}

bool GameApp::InitResource()
{
    Hanzi::VertexPosColor* newVertices = Hanzi::CreateNanVertices();
    Hanzi::VertexPosColor vertices[104];
    memcpy(vertices, newVertices, 104 * sizeof(Hanzi::VertexPosColor));

    // 设置顶点缓冲区描述
    D3D11_BUFFER_DESC vbd;
    ZeroMemory(&vbd, sizeof(vbd));
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof vertices;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    // 新建顶点缓冲区
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertices;
    HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));

    // ******************
    // 索引数组
    //
    DWORD* newIndices = Hanzi::CreateNanIndices();
    DWORD indices[492];
    memcpy(indices, newIndices, 492 * sizeof(DWORD));

    // 设置索引缓冲区描述
    D3D11_BUFFER_DESC ibd;
    ZeroMemory(&ibd, sizeof(ibd));
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = sizeof indices;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    // 新建索引缓冲区
    InitData.pSysMem = indices;
    HR(m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf()));
    // 输入装配阶段的索引缓冲区设置
    m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);


    // ******************
    // 设置常量缓冲区描述
    //
    D3D11_BUFFER_DESC cbd;
    ZeroMemory(&cbd, sizeof(cbd));
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.ByteWidth = sizeof(ConstantBuffer);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    // 新建常量缓冲区，不使用初始数据
    HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffer.GetAddressOf()));


    // 初始化常量缓冲区的值
    // 如果你不熟悉这些矩阵，可以先忽略，待读完第四章后再回头尝试修改
    m_CBuffer.world = XMMatrixIdentity();	// 单位矩阵的转置是它本身
    m_CBuffer.view = XMMatrixTranspose(XMMatrixLookAtLH(
        XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f),
        XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
        XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
    ));
    m_CBuffer.proj = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, AspectRatio(), 1.0f, 1000.0f));
    m_CBuffer.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_CBuffer.useCustomColor = false;

    // ******************
    // 给渲染管线各个阶段绑定好所需资源
    //

    // 输入装配阶段的顶点缓冲区设置
    UINT stride = sizeof(VertexPosColor);	// 跨越字节数
    UINT offset = 0;						// 起始偏移量

    m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
    // 设置图元类型，设定输入布局
    m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
    // 将着色器绑定到渲染管线
    m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
    // 将更新好的常量缓冲区绑定到顶点着色器和像素着色器
    m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
    m_pd3dImmediateContext->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());

    m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

    // ******************
    // 设置调试对象名
    //
    D3D11SetDebugObjectName(m_pVertexLayout.Get(), "VertexPosColorLayout");
    D3D11SetDebugObjectName(m_pVertexBuffer.Get(), "VertexBuffer");
    D3D11SetDebugObjectName(m_pIndexBuffer.Get(), "IndexBuffer");
    D3D11SetDebugObjectName(m_pConstantBuffer.Get(), "ConstantBuffer");
    D3D11SetDebugObjectName(m_pVertexShader.Get(), "Cube_VS");
    D3D11SetDebugObjectName(m_pPixelShader.Get(), "Cube_PS");

    return true;
}