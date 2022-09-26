#include "Light.hlsli"

/* 
    对任意平面 Ax+By+Cz+D=0 求镜像点
*/
void Symmetry(in float3 p, out float3 p_s)
{
    float A = 0.f, B = 0.f, C = 1.f, D = -2.f;
    float f1 = A * A + B * B + C * C;
    float f2 = A * p.x + B * p.y + C * p.z + D;
    p_s.x = p.x - 2 * A * (f2) / f1;
    p_s.y = p.y - 2 * B * (f2) / f1;
    p_s.z = p.z - 2 * C * (f2) / f1;
}


[maxvertexcount(6)]
void GS(
	triangle VertexOut input[3],
	inout TriangleStream<VertexOut> output
)
{
    VertexOut vOri[3], vNew[3];
    
	[unroll]
    for (uint i = 0; i < 3; i++)
	{
        vOri[i] = input[i];
        output.Append(vOri[i]);
        
        //镜像顶点
        Symmetry(input[i].posW, vNew[i].posW);
        
        //世界到裁剪矩阵
        matrix viewProj = mul(g_View, g_Proj);
        vNew[i].posH = mul(float4(vNew[i].posW, 1.0f), viewProj);
        
        //顶点自身颜色由白色改为 LimeGreen 酸橙绿
        vNew[i].color = float4(0.2f, 0.8f, 0.2f, 1.f);
        
        //镜像法线
        float3 normalWSta = input[i].posW;
        float3 normalWEnd = input[i].posW + input[i].normalW;
        Symmetry(normalWEnd, normalWEnd);
        vNew[i].normalW = normalWEnd - vNew[i].posW;
        
    }
    
    output.RestartStrip();
    
    [unroll]
    for (uint i = 0; i < 3; i++)
    {
        output.Append(vNew[i]);
    }
}
