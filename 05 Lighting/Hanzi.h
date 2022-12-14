#ifndef HANZI_H
#define HANZI_H

#include "Vertex.h"

using namespace DirectX;

class Hanzi
{
public:

    //为了省事，共享顶点只设了一条法线，朝向屏幕外侧的面的顶点赋(0.f,0.f,-1.f)，内侧的赋(0.f,0.f,1.f)。
    static void CreateNanVertexs_PosNormalColor(VertexPosNormalColor** vertices,UINT m_VertexCount)
    {
        *vertices = new VertexPosNormalColor[m_VertexCount]
        {
            //南的左下竖 8
			{ XMFLOAT3(-0.1f,  0.5f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(0.1f,  0.3f, -0.1f),  XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(-0.1f, -1.1f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(0.1f, -1.1f, -0.1f),  XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(-0.1f,  0.5f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
			{ XMFLOAT3(0.1f,  0.3f,  0.1f),  XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(-0.1f, -1.1f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(0.1f, -1.1f,  0.1f),  XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
            //南的右下竖 8
            { XMFLOAT3(1.3f,  0.5f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(1.1f,  0.3f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(1.1f, -1.1f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(1.3f, -1.1f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(1.3f,  0.5f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(1.1f,  0.3f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(1.1f, -1.1f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(1.3f, -1.1f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			//南中左点 8
			{ XMFLOAT3(0.3f,  0.1f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(0.5f,  0.1f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(0.3f, -0.1f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(0.5f, -0.1f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(0.3f,  0.1f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(0.5f,  0.1f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(0.3f, -0.1f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(0.5f, -0.1f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
            //南中右点 8
            { XMFLOAT3(0.7f,  0.1f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f,  0.1f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f, -0.1f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.7f, -0.1f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.7f,  0.1f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f,  0.1f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f, -0.1f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.7f, -0.1f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            //南中”干“上面一横 8 
            { XMFLOAT3(0.3f, -0.3f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f, -0.3f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f, -0.5f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.3f, -0.5f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.3f, -0.3f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f, -0.3f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f, -0.5f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.3f, -0.5f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            //南中”干“下面一横 8
            { XMFLOAT3(0.3f, -0.7f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f, -0.7f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f, -0.9f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.3f, -0.9f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.3f, -0.7f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f, -0.7f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.9f, -0.9f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.3f, -0.9f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            //南中”干“一竖 8 加粗，防止重叠闪烁
            { XMFLOAT3(0.5f, -0.3f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.7f, -0.3f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.7f, -1.1f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.5f, -1.1f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.5f, -0.3f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.7f, -0.3f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.7f, -1.1f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.5f, -1.1f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            //南上”十“一横 8
            { XMFLOAT3(0.1f,  0.9f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(1.1f,  0.9f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(1.1f,  0.7f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.1f,  0.7f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.1f,  0.9f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(1.1f,  0.9f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(1.1f,  0.7f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.1f,  0.7f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            //南上”十“一竖 8 加粗
            { XMFLOAT3(0.5f,  1.1f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.7f,  1.1f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.7f,  0.5f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.5f,  0.5f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.5f,  1.1f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.7f,  1.1f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.7f,  0.5f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.5f,  0.5f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            //”木“一横 8
            { XMFLOAT3(-1.3f,  0.5f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.3f,  0.5f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.3f,  0.3f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-1.3f,  0.3f, -0.1f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-1.3f,  0.5f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.3f,  0.5f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.3f,  0.3f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-1.3f,  0.3f,  0.1f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            //”木“一竖 8 加粗
            { XMFLOAT3(-0.9f,  1.1f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.7f,  1.1f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.7f, -1.1f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.9f, -1.1f, -0.11f), XMFLOAT3(0.f,0.f,-1.f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.9f,  1.1f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.7f,  1.1f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.7f, -1.1f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.9f, -1.1f,  0.11f), XMFLOAT3(0.f,0.f,1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            //”木“一撇 8
            { XMFLOAT3(-0.9f,  0.3f, -0.1f), XMFLOAT3(0.f,0.f,-1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.9f, -0.3f, -0.1f), XMFLOAT3(0.f,0.f,-1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-1.1f, -0.7f, -0.1f), XMFLOAT3(0.f,0.f,-1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-1.3f, -0.5f, -0.1f), XMFLOAT3(0.f,0.f,-1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.9f,  0.3f,  0.1f), XMFLOAT3(0.f,0.f,1.f),   XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.9f, -0.3f,  0.1f), XMFLOAT3(0.f,0.f,1.f),   XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-1.1f, -0.7f,  0.1f), XMFLOAT3(0.f,0.f,1.f),   XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-1.3f, -0.5f,  0.1f), XMFLOAT3(0.f,0.f,1.f),   XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            //”木“一捺 8
            { XMFLOAT3(-0.7f,  0.3f, -0.1f), XMFLOAT3(0.f,0.f,-1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.3f, -0.5f, -0.1f), XMFLOAT3(0.f,0.f,-1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.5f, -0.7f, -0.1f), XMFLOAT3(0.f,0.f,-1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.7f, -0.3f, -0.1f), XMFLOAT3(0.f,0.f,-1.f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.7f,  0.3f,  0.1f), XMFLOAT3(0.f,0.f,1.f),   XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.3f, -0.5f,  0.1f), XMFLOAT3(0.f,0.f,1.f),   XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.5f, -0.7f,  0.1f), XMFLOAT3(0.f,0.f,1.f),   XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.7f, -0.3f,  0.1f), XMFLOAT3(0.f,0.f,1.f),   XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        };
    }

    //创建索引
    static void CreateNanIndices_PosNormalColor(DWORD** indices, UINT m_IndexCount)
    {
        *indices = new DWORD[m_IndexCount]
        {

            //南的左下竖 10
            0, 1, 2,
            2, 1, 3,
            5, 4, 6,
            7, 5, 6,
            4, 0, 2,
            6, 4, 2,
            2, 3, 7,
            6, 2, 7,
            1, 5, 7,
            3, 1, 7,
            //南的右下竖 10
            9, 8, 11,
            10, 9, 11,
            12, 13, 15,
            13, 14, 15,
            13, 9, 10,
            14, 13, 10,
            8, 12, 15,
            11, 8, 15,
            10, 11, 15,
            14, 10, 15,
            //南 连接左下竖和右下竖的横 8
             0, 8, 1,
             8, 9, 1,
             4, 12, 0,
             0, 12, 8,
             1, 9, 5,
             5 ,9, 13,
             5, 12, 4,
             5, 13, 12,
             //南中左点 12
             16, 17, 19,
             18, 16, 19,
             21, 20, 23,
             20, 22, 23,
             20, 21, 17,
             16, 20, 17,
             18, 19, 23,
             22, 18, 23,
             20, 16, 18,
             22, 20, 18,
             17, 21, 23,
             19, 17, 23,
             //南中右点 12
             24, 25, 26,
             27, 24, 26,
             29, 28, 30,
             30, 28, 31,
             28, 29, 25,
             24, 28, 25,
             27, 26, 30,
             31, 27, 30,
             28, 24, 27,
             31, 28, 27,
             25, 29, 30,
             26, 25, 30,
             //南中”干“上面一横 12
             32, 33, 34,
             35, 32, 34,
             37, 36, 38,
             36, 39, 38,
             36, 37, 33,
             32, 36, 33,
             33, 37, 38,
             34, 33, 38,
             35, 34, 38,
             39, 35, 38,
             36, 32, 35,
             39, 36, 35,
             //南中”干“下面一横 12
             40, 41, 42,
             43, 40, 42,
             45, 44, 46,
             44, 47, 46,
             44, 45, 41,
             40, 44, 41,
             41, 45, 46,
             42, 41, 46,
             43, 42, 46,
             47, 43, 46,
             44, 40, 43,
             47 ,44, 43,
             //南中”干“一竖 12
             48, 49, 50,
             51, 48, 50,
             53, 52, 54,
             52, 55, 54,
             52, 53, 49,
             48, 52, 49,
             49, 53, 54,
             50, 49, 54,
             51, 50, 54,
             55, 51, 54,
             52, 48, 51,
             55, 52, 51,
             //南上”十“一横 12
             56, 57, 58,
             59, 56, 58,
             61, 60, 62,
             60, 63, 62,
             60, 61, 57,
             56, 60, 57,
             57, 61, 62,
             58, 57, 62,
             59, 58, 62,
             63, 59, 62,
             60, 56, 59,
             63, 60, 59,
             //南上”十“一竖 12
             64, 65, 66,
             67, 64, 66,
             69, 68, 70,
             68, 71, 70,
             68, 69, 65,
             64, 68, 65,
             65, 69, 70,
             66, 65, 70,
             67, 66, 70,
             71, 67, 70,
             68, 64, 67,
             71, 68, 67,
             //”木“一横 12
             72, 73, 74,
             75, 72, 74,
             77, 76, 78,
             76, 79, 78,
             76, 77, 73,
             72, 76, 73,
             73, 77, 78,
             74, 73, 78,
             75, 74, 78,
             79, 75, 78,
             76, 72, 75,
             79, 76, 75,
             //”木“一竖 12
             80, 81, 82,
             83, 80, 82,
             85, 84, 86,
             84, 87, 86,
             84, 85, 81,
             80, 84, 81,
             81, 85, 86,
             82, 81, 86,
             83, 82, 86,
             87, 83, 86,
             84, 80, 83,
             87, 84, 83,
             //”木“一撇 12
             88, 89, 90,
             91, 88, 90,
             93, 92, 94,
             92, 95, 94,
             92, 93, 89,
             88, 92, 89,
             89, 93, 94,
             90, 89, 94,
             91, 90, 94,
             95, 91, 94,
             92, 88, 91,
             95, 92, 91,
             //”木“一捺 12
             96, 97, 98,
             99, 96, 98,
             101,100,102,
             100,103,102,
             100,101,97,
             96,100,97,
             97,101,102,
             98,97,102,
             99,98,102,
             103,99,102,
             100,96,99,
             103,100,99,
        };
    }



};


#endif