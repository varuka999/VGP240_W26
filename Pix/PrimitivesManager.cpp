#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
    Matrix4 GetScreenTransform()
    {
        const float hw = gResolutionX * 0.5f;
        const float hh = gResolutionY * 0.5f;
        return
        {
              hw, 0.0f, 0.0f, 0.0f,
            0.0f,  -hh, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
              hw,   hh, 0.0f, 1.0f
        };
    }
}

PrimitivesManager::PrimitivesManager()
{
}

PrimitivesManager* PrimitivesManager::Get()
{
    static PrimitivesManager sInstance;
    return&sInstance;
}

bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
    mVertexBuffer.clear();
    mTopology = topology;
    mApplyTransform = applyTransform;
    mDrawBegin = true;
    return true;
}

void PrimitivesManager::AddVertex(const Vertex& vertex)
{
    if (mDrawBegin)
    {
        mVertexBuffer.push_back(vertex);
    }
}

bool PrimitivesManager::EndDraw()
{
    if (!mDrawBegin)
    {
        return false;
    }

    // to start, the triangle certices are in local space

    // this matrix transform the local vertices to world space
    Matrix4 matWorld = MatrixStack::Get()->GetTransform();
    // this matrix transforms the world vertices to local space of the camera
    Matrix4 matView = Camera::Get()->GetViewMatrix();
    // this matrix transform the camera local space vertices to NDC space
    Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
    // this matrix transform the NDC space vertices to screen space
    Matrix4 matScreen = GetScreenTransform();
    Matrix4 matFinal = matWorld * matView * matProj * matScreen;

    Rasterizer* rasterizer = Rasterizer::Get();
    switch (mTopology)
    {
    case Topology::Point:
    {
        for (uint32_t i = 0; i < mVertexBuffer.size(); ++i)
        {
            if (!Clipper::Get()->ClipPoint(mVertexBuffer[i]))
            {
                rasterizer->DrawPoint(mVertexBuffer[i]);
            }
        }
    }
    break;
    case Topology::Line:
    {
        for (uint32_t i = 1; i < mVertexBuffer.size(); i += 2)
        {
            if (!Clipper::Get()->ClipLine(mVertexBuffer[i - 1], mVertexBuffer[i]))
            {
                rasterizer->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
            }
        }
    }
    break;
    case Topology::Triangle:
    {
        for (uint32_t i = 2; i < mVertexBuffer.size(); i += 3)
        {
            std::vector<Vertex> triangle{ mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i] };
            if (mApplyTransform)
            {
                for (uint32_t v = 0; v < triangle.size(); ++v)
                {
                    triangle[v].pos = MathHelper::TransformCoord(triangle[v].pos, matFinal);
                    MathHelper::FlattenVectorScreenCoord(triangle[v].pos);
                }
            }
            if (!Clipper::Get()->ClipTriangle(triangle))
            {
                for (uint32_t v = 2; v < triangle.size(); ++v)
                {
                    rasterizer->DrawTriangle(triangle[0], triangle[v - 1], triangle[v]);
                }
            }
        }
    }
    break;
    default:
        return false;
    }

    return false;
}