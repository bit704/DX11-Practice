#include "Light.hlsli"

// 像素着色器
float4 PS_Plane(VertexOut_Plane pIn) : SV_Target
{
    pIn.Tex.x += g_Time.x;
    float4 texColor = g_Tex0.Sample(g_SamLinear, pIn.Tex);
    texColor.a -= 0.7;
    clip(texColor.a - 0.1f);
    
    // 标准化法向量
    pIn.normalW = normalize(pIn.normalW);

    // 顶点指向眼睛的向量
    float3 toEyeW = normalize(g_EyePosW - pIn.posW);

    // 初始化为0 
    float4 ambient, diffuse, spec;
    float4 A, D, S;
    ambient = diffuse = spec = A = D = S = float4(0.0f, 0.0f, 0.0f, 0.0f);

    DirectionalLight dl = g_DirLight;
    PointLight pl1 = g_PointLight1, pl2 = g_PointLight2, pl3 = g_PointLight3;
    SpotLight sl = g_SpotLight;
    
    [flatten]
    if (g_IsReflection)
    {
        
        dl.direction = mul(g_DirLight.direction, (float3x3) (g_Reflection));
        
        pl1.position = mul(g_PointLight1.position, (float3x3) (g_Reflection));
        pl2.position = mul(g_PointLight2.position, (float3x3) (g_Reflection));
        pl3.position = mul(g_PointLight3.position, (float3x3) (g_Reflection));
        
        sl.direction = mul(g_SpotLight.direction, (float3x3) (g_Reflection));
        sl.position = mul(g_SpotLight.position, (float3x3) (g_Reflection));
    }
    
    ComputeDirectionalLight(g_Material, dl, pIn.normalW, toEyeW, A, D, S);
    ambient += A;
    diffuse += D;
    spec += S;

    ComputePointLight(g_Material, pl1, pIn.posW, pIn.normalW, toEyeW, A, D, S);
    ambient += A;
    diffuse += D;
    spec += S;
    
    ComputePointLight(g_Material, pl2, pIn.posW, pIn.normalW, toEyeW, A, D, S);
    ambient += A;
    diffuse += D;
    spec += S;
    
    ComputePointLight(g_Material, pl3, pIn.posW, pIn.normalW, toEyeW, A, D, S);
    ambient += A;
    diffuse += D;
    spec += S;

    ComputeSpotLight(g_Material, sl, pIn.posW, pIn.normalW, toEyeW, A, D, S);
    ambient += A;
    diffuse += D;
    spec += S;
    
    float4 litColor = texColor * (ambient + diffuse) + spec;
    litColor.a = texColor.a * g_Material.diffuse.a;
    
    return litColor;
}