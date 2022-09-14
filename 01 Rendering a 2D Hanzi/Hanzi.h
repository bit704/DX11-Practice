#ifndef HANZI_H
#define HANZI_H

#include "d3dapp.h"
using namespace DirectX;

class Hanzi
{
public:
    struct VertexPosColor
    {
        XMFLOAT3 pos;
        XMFLOAT4 color;
        static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
    };

    //创建顶点
    static VertexPosColor* CreateNanVertices()
    {
        VertexPosColor vertices[] =
        {
            //南的左下竖 
            { XMFLOAT3(-0.05f,  0.25f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.05f,  0.15f,  0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(-0.05f, -0.55f, 0.f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },

            { XMFLOAT3(0.05f,   0.15f,  0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.05f,  -0.55f,  0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.05f, -0.55f, 0.f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },

            //南的右下竖 
            { XMFLOAT3(0.55f, -0.55f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.55f,  0.15f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.65f,  0.25f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

            { XMFLOAT3(0.55f, -0.55f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.65f,  0.25f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.65f, -0.55f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

            //南中一横，连接左右下竖
            { XMFLOAT3(-0.05f,  0.25f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.65f,  0.25f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.05f,  0.15f,  0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(0.05f,  0.15f,  0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.65f,  0.25f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.55f,  0.15f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },

            //南中左点 
            { XMFLOAT3(0.15f,  0.05f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.25f,  0.05f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.15f, -0.05f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(0.25f,  0.05f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.25f, -0.05f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.15f, -0.05f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
           
            ////南中右点 
            { XMFLOAT3(0.35f,  0.05f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.45f,  0.05f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.45f, -0.05f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(0.45f, -0.05f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.35f, -0.05f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.35f,  0.05f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

            //南中”干“上面一横
            { XMFLOAT3(0.15f, -0.15f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.45f, -0.15f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.45f, -0.25f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(0.45f, -0.25f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.15f, -0.25f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.15f, -0.15f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

            //南中”干“下面一横
            { XMFLOAT3(0.15f, -0.35f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.45f, -0.35f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.45f, -0.45f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(0.45f, -0.45f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.15f, -0.45f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.15f, -0.35f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

            //南中”干“一竖
            { XMFLOAT3(0.25f, -0.15f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.35f, -0.15f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.35f, -0.55f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(0.35f, -0.55f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.25f, -0.55f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.25f, -0.15f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

            //南上”十“一横 
            { XMFLOAT3(0.05f,  0.45f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.55f,  0.45f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.55f,  0.35f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(0.55f,  0.35f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.05f,  0.35f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.05f,  0.45f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

            //南上”十“一竖 
            { XMFLOAT3(0.25f,  0.55f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.35f,  0.55f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.35f,  0.25f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(0.35f,  0.25f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(0.25f,  0.25f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(0.25f,  0.55f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

            //”木“一横 
            { XMFLOAT3(-0.65f,  0.25f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.15f,  0.25f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(-0.15f,  0.15f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(-0.15f,  0.15f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(-0.65f,  0.15f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.65f,  0.25f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

            //”木“一竖
            { XMFLOAT3(-0.45f,  0.55f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.35f,  0.55f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(-0.35f, -0.55f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(-0.35f, -0.55f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(-0.45f, -0.55f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.45f,  0.55f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

            //”木“一撇 
            { XMFLOAT3(-0.45f,  0.15f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.45f, -0.15f, 0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(-0.55f, -0.35f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(-0.55f, -0.35f, 0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(-0.65f, -0.25f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.45f,  0.15f, 0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

            //”木“一捺
            { XMFLOAT3(-0.35f,  0.15f, -0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.15f, -0.25f, -0.f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
            { XMFLOAT3(-0.25f, -0.35f, -0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

            { XMFLOAT3(-0.25f, -0.35f, -0.f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
            { XMFLOAT3(-0.35f, -0.15f, -0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
            { XMFLOAT3(-0.35f,  0.15f, -0.f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

        };
        return vertices;
    }

};


#endif