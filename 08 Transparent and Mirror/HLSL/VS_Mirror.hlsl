#include "Light.hlsli"

// 顶点着色器
VertexOut_Mirror VS_Mirror(VertexIn_Mirror vIn)
{
    VertexOut_Mirror vOut;
    matrix viewProj = mul(g_View, g_Proj);
    float4 posW = mul(float4(vIn.posL, 1.0f), g_World);
    float3 normalW = mul(vIn.normalL, (float3x3) g_WorldInvTranspose);
    
    vOut.posH = mul(posW, viewProj);
    vOut.posW = posW.xyz;
    vOut.normalW = normalW;
    vOut.Tex = vIn.Tex;
    return vOut;
}
