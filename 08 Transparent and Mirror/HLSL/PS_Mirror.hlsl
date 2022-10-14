#include "Light.hlsli"

float4 PS_Mirror(VertexOut_Mirror pIn) : SV_Target
{
    float4 texColor = g_Tex1.Sample(g_SamLinear, pIn.Tex);
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