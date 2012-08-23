#include "FlashTesselator.h"

#include "cinder/Xml.h"

using namespace ci;
using namespace std;

void* memAllocator(void *userData, unsigned int size)
{
    return malloc(size);
}

void* memReallocator(void *userData, void* ptr, unsigned int size)
{
    return realloc(ptr, size);
}

void memFree(void *userData, void *ptr)
{
    free(ptr);
}

FlashTesselator::FlashTesselator()
{
    TESSalloc allocator;
    allocator.memalloc = memAllocator;
    allocator.memrealloc = memReallocator;
    allocator.memfree = memFree;
    allocator.meshEdgeBucketSize = 0;
    allocator.meshVertexBucketSize = 0;
    allocator.meshFaceBucketSize = 0;
    allocator.dictNodeBucketSize = 0;
    allocator.regionBucketSize = 0;
    allocator.extraVertices = 0;
    
    tess = tessNewTess(&allocator);
}

FlashTesselator::~FlashTesselator()
{
    tessDeleteTess(tess);
}

FlashShape* FlashTesselator::calculate(ci::DataSourceRef dataSource, float scale)
{
    XmlTree doc(dataSource);
    XmlTree path = doc.getChild("Graphic/Group/Path");
    
    FXGPath fxg(path.getAttributeValue<string>("data"), scale);
    
    if (path.hasAttribute("x"))
    {
        fxg.ox = path.getAttributeValue<float>("x");
    }
    
    if (path.hasAttribute("y"))
    {
        fxg.oy = path.getAttributeValue<float>("y");
    }
    
    return calculate(fxg);
}

FlashShape* FlashTesselator::calculate(const FXGPath &fxg)
{
    Path2d path = fxgToPath(fxg.ox, fxg.oy, fxg.scale, fxg.data);
    return calculate(path, 1.0f);
}

/*
 * TODO: THROW EXCEPTION IN CASE tessTesselate() RETURNS false
 */
FlashShape* FlashTesselator::calculate(const Path2d &path, float approximationScale)
{
    vector<Vec2f> subdivided = path.subdivide(approximationScale);
    
    tessAddContour(tess, 2, &subdivided[0], sizeof(float) * 2, subdivided.size());
    tessTesselate(tess, TESS_WINDING_ODD, TESS_POLYGONS, 3, 2, 0);
    
    // ---
    
    FlashShape *flashShape = new FlashShape;
    
    flashShape->appendVertices((Vec2f*)tessGetVertices(tess), tessGetVertexCount(tess));
    flashShape->appendIndices((uint32_t*)tessGetElements(tess), tessGetElementCount(tess) * 3);
    
    // ---
    
    StrokeHelper::stroke(subdivided, flashShape->strip, 2);
    
    return flashShape;
}

/*
 * TODO: COMPLETE AI PARSING, EVENTUALLY USING AIPath.java
 */
Path2d FlashTesselator::fxgToPath(float ox, float oy, float scale, const string &data) const
{
    istringstream iss(data);
    
    ci::Path2d out;
    char c;
    float x, y;
    float x1, y1, x2, y2, x3, y3;
    bool inL = false;
    bool inQ = false;
    bool inC = false;
    
    iss >> c;
    iss >> x;
    iss >> y;
    out.moveTo((x + ox) * scale, (y + oy) * scale);
    
    while (!(iss >> c).eof())
    {
        if (c == 'L')
        {
            inL = true;
            inQ = false;
            inC = false;
        }
        else if (c == 'Q')
        {
            inQ = true;
            inC = false;
            inL = false;
        }
        else if (c == 'C')
        {
            inC = true;
            inQ = false;
            inL = false;
        }
        else
        {
            iss.unget();
        }
        
        if (inL)
        {
            iss >> x;
            iss >> y;
            out.lineTo((x + ox) * scale, (y + oy) * scale);
        }
        else if (inQ)
        {
            iss >> x1;
            iss >> y1;
            iss >> x2;
            iss >> y2;
            out.quadTo((x1 + ox) * scale, (y1 + oy) * scale, (x2 + ox) * scale, (y2 + oy) * scale);
        }
        else if (inC)
        {
            iss >> x1;
            iss >> y1;
            iss >> x2;
            iss >> y2;
            iss >> x3;
            iss >> y3;
            out.curveTo((x1 + ox) * scale, (y1 + oy) * scale, (x2 + ox) * scale, (y2 + oy) * scale, (x3 + ox) * scale, (y3 + oy) * scale);
        }
    }
    
    return out;
}
