#include "Clipper.h"
#include "Viewport.h"

const short BIT_INSIDE = 0;      //0000
const short BIT_LEFT = 1 << 1; //0001
const short BIT_RIGHT = 1 << 2; //0010
const short BIT_BOTTOM = 1 << 3; //0100
const short BIT_TOP = 1 << 4; //1000

short GetOutputCode(float x, float y)
{
    Viewport* vp = Viewport::Get();

    short code = BIT_INSIDE;

    if (x < vp->GetMinX())
    {
        code |= BIT_LEFT;
    }
    else if (x > vp->GetMaxX())
    {
        code |= BIT_RIGHT;
    }

    if (y < vp->GetMinY())
    {
        code |= BIT_TOP;
    }
    else if (y > vp->GetMaxY())
    {
        code |= BIT_BOTTOM;
    }

    return code;
}

enum ClipEdge
{
    CE_LEFT,
    CE_TOP,
    CE_RIGHT,
    CE_BOTTOM,
    CE_COUNT,
};

bool IsInFront(ClipEdge edge, const Vector3& pos)
{
    Viewport* vp = Viewport::Get();
    switch (edge)
    {
    case CE_LEFT:   return pos.x > vp->GetMinX();
    case CE_TOP:    return pos.y > vp->GetMinY();
    case CE_RIGHT:  return pos.x < vp->GetMaxX();
    case CE_BOTTOM: return pos.y < vp->GetMaxY();
    default:
        break;
    }

    return false;
}

Vertex ComputeIntersection(ClipEdge edge, const Vertex& v, const Vertex& vPO)
{
    Viewport* vp = Viewport::Get();
    float t = 0.0f;
    switch (edge)
    {
    case CE_LEFT:   t = (vp->GetMinX() - v.pos.x) / (vPO.pos.x - v.pos.x);
        break;
    case CE_TOP:    t = (vp->GetMinY() - v.pos.y) / (vPO.pos.y - v.pos.y);
        break;
    case CE_RIGHT:  t = (vp->GetMaxX() - v.pos.x) / (vPO.pos.x - v.pos.x);
        break;
    case CE_BOTTOM: t = (vp->GetMaxY() - v.pos.y) / (vPO.pos.y - v.pos.y);
        break;
    default:
        break;
    }

    return LerpVertex(v, vPO, t);
}

Clipper::Clipper()
{

}

Clipper* Clipper::Get()
{
    static Clipper sInstance;
    return &sInstance;
}

void Clipper::OnNewFrame()
{
    mIsClipping = false;
}

bool Clipper::ClipPoint(const Vertex& v)
{
    if (!mIsClipping)
    {
        return false;
    }

    Viewport* vp = Viewport::Get();
    float minX = vp->GetMinX();
    float minY = vp->GetMinY();
    float maxX = vp->GetMaxX();
    float maxY = vp->GetMaxY();

    return v.pos.x < minX || v.pos.x > maxX || v.pos.y < minY || v.pos.y > maxY;
}

bool Clipper::ClipLine(Vertex& a, Vertex& b)
{
    if (!mIsClipping)
    {
        return false;
    }

    Viewport* vp = Viewport::Get();
    float minX = vp->GetMinX();
    float minY = vp->GetMinY();
    float maxX = vp->GetMaxX();
    float maxY = vp->GetMaxY();

    short codeA = GetOutputCode(a.pos.x, a.pos.y);
    short codeB = GetOutputCode(b.pos.x, b.pos.y);

    while (true)
    {
        if (!(codeA | codeB))
        {
            // if both a and b are 0000, draw the line
            break;
        }
        else if (codeA & codeB)
        {
            // both lines are on the same side, so not crossing the screen
            break;
        }

        float t = 0.0f;
        short outCode = codeB > codeA ? codeB : codeA;

        if (outCode & BIT_TOP) { t = (minY - a.pos.y) / (b.pos.y - a.pos.y); }
        else if (outCode & BIT_BOTTOM) { t = (maxY - a.pos.y) / (b.pos.y - a.pos.y); }
        else if (outCode & BIT_LEFT) { t = (minX - a.pos.x) / (b.pos.x - a.pos.x); }
        else if (outCode & BIT_RIGHT) { t = (maxX - a.pos.x) / (b.pos.x - a.pos.x); }

        if (outCode == codeA)
        {
            a = LerpVertex(a, b, t);
            codeA = GetOutputCode(a.pos.x, a.pos.y);
        }
        else
        {
            b = LerpVertex(a, b, t);
            codeB = GetOutputCode(b.pos.x, b.pos.y);
        }
    }

    return (codeA | codeB);
}

bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{
    if (!mIsClipping)
    {
        return false;
    }

    std::vector<Vertex> newVertices;
    for (int i = 0; i < CE_COUNT; ++i)
    {
        newVertices.clear();
        ClipEdge edge = (ClipEdge)i;

        for (size_t n = 0; n < vertices.size(); ++n)
        {
            size_t nPO = (n + 1) % vertices.size();
            const Vertex& v = vertices[n];
            const Vertex& vPO = vertices[nPO];

            bool nIsInFront = IsInFront(edge, v.pos);
            bool nPOIsInFront = IsInFront(edge, vPO.pos);

            // c1 both in front
            if (nIsInFront && nPOIsInFront)
            {
                newVertices.push_back(vPO);
            }
            // c2 both are behind
            if (!nIsInFront && !nPOIsInFront)
            {
                
            }
            // c3 v in front vPO behind
            if (nIsInFront && !nPOIsInFront)
            {
                newVertices.push_back(ComputeIntersection(edge, v, vPO));
            }
            // c4 v behind vPO in front
            if (!nIsInFront && nPOIsInFront)
            {
                newVertices.push_back(ComputeIntersection(edge, v, vPO));
                newVertices.push_back(vPO);
            }
        }

        vertices = newVertices;
    }

    return newVertices.empty();
}

bool Clipper::IsClipping() const
{
    return mIsClipping;
}

void Clipper::SetClipping(bool enable)
{
    mIsClipping = enable;
}