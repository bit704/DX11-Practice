#include "Light.hlsli"

// 顶点着色器
VertexOut_Plane VS_Plane(VertexIn_Plane vIn)
{
    VertexOut_Plane vOut;
    matrix viewProj = mul(g_View, g_Proj);
    float4 posW = mul(float4(vIn.posL, 1.0f), g_World);
    float3 normalW = mul(vIn.normalL, (float3x3) g_WorldInvTranspose);
    
    // 若当前在绘制反射物体，先进行反射操作
    [flatten]
    if (g_IsReflection)
    {
        posW = mul(posW, g_Reflection);
        normalW = mul(normalW, (float3x3) g_Reflection);
    }

    vOut.posH = mul(posW, viewProj);
    vOut.posW = posW.xyz;
    vOut.normalW = normalW;
    vOut.Tex = vIn.Tex; 
    return vOut;
}
