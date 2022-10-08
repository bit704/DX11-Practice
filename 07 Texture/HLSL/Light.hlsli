#include "LightHelper.hlsli"

Texture2D g_Tex : register(t0);
SamplerState g_SamLinear : register(s0);

cbuffer VSConstantBuffer : register(b0)
{
    matrix g_World; 
    matrix g_View;  
    matrix g_Proj;  
    matrix g_WorldInvTranspose;
}

cbuffer PSConstantBuffer : register(b1)
{
    DirectionalLight g_DirLight;
    PointLight g_PointLight1;
    PointLight g_PointLight2;
    PointLight g_PointLight3;
    SpotLight g_SpotLight;
    Material g_Material;
    float3 g_EyePosW;
    float g_Pad;
    float4 g_Time;
}

struct VertexIn_Plane
{
    float3 posL : POSITION;
    float3 normalL : NORMAL;
    float2 Tex : TEXCOORD;
};

struct VertexOut_Plane
{
    float4 posH : SV_POSITION;
    float3 posW : POSITION;     // 在世界中的位置
    float3 normalW : NORMAL;    // 法向量在世界中的方向
    float2 Tex : TEXCOORD;
};

struct VertexIn_Hanzi
{
    float3 posL : POSITION;
    float3 normalL : NORMAL;
    float4 color : COLOR;
};

struct VertexOut_Hanzi
{
    float4 posH : SV_POSITION;
    float3 posW : POSITION; // 在世界中的位置
    float3 normalW : NORMAL; // 法向量在世界中的方向
    float4 color : COLOR;
};

