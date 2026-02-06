#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"

PrimitivesManager::PrimitivesManager()
{
}

PrimitivesManager* PrimitivesManager::Get()
{
    static PrimitivesManager sInstance;
    return&sInstance;
}

bool PrimitivesManager::BeginDraw(Topology topology)
{
    mVertexBuffer.clear();
    mTopology = topology;
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