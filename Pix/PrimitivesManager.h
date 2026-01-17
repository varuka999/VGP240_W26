#pragma once
#include "Vertex.h"

enum class Topology
{
    Point,
    Line,
    Triangle,
};

class PrimitivesManager
{
public:
    static PrimitivesManager* Get();

    // Start accepting vertices
    bool BeginDraw(Topology topology);
    // Add vertices to the list, onlly if drawing is enaabled
    void AddVertex(const Vertex& vertex);
    // Send all the stored vertices to the rasterizer as specified topology
    bool EndDraw();

private:
    PrimitivesManager();

    std::vector<Vertex> mVertexBuffer;
    Topology mTopology = Topology::Point;
    bool mDrawBegin = false;
};