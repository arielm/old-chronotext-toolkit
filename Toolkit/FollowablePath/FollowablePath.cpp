#include "FollowablePath.h"

#include <cmath>
#include <limits>

using namespace ci;
using namespace std;

#define DEFAULT_CAPACITY 256
#define CAPACITY_INCREMENT 0 // 0 MEANS THAT CAPACITY IS MULTIPLIED BY 2 WHEN NECESSARY

static int search(float *array, float value, int min, int max)
{
    int mid = (min + max) >> 1;
    
    while (min < mid)
    {
        if (array[mid - 1] < value)
        {
            min = mid;
        }
        else if (array[mid - 1] > value)
        {
            max = mid;
        }
        else
        {
            min = max = mid;
        }
        mid = (min + max) >> 1;
    }
    
    return mid - 1;
}

static inline float boundf(float value, float range)
{
    float bound = fmod(value, range);
    return (bound < 0.0f) ? (bound + range) : bound;
}

FollowablePath::FollowablePath(int mode)
{
    capacity = DEFAULT_CAPACITY;
    this->mode = mode;
    
    x = new float[capacity];
    y = new float[capacity];
    len = new float[capacity];
}

FollowablePath::FollowablePath(int capacity, int mode)
{
    this->capacity = capacity;
    this->mode = mode;
    
    size = 0;
    x = new float[capacity];
    y = new float[capacity];
    len = new float[capacity];
}

FollowablePath::FollowablePath(const std::vector<ci::Vec2f> &points, int mode)
{
    capacity = points.size();
    this->mode = mode;
    
    x = new float[capacity];
    y = new float[capacity];
    len = new float[capacity];
    
    setPoints(points);
}

FollowablePath::FollowablePath(DataSourceRef dataSource, int mode)
{
    if (dataSource->isFilePath())
    {
        ifstream in(dataSource->getFilePath().c_str(), ifstream::binary);
        readFromStream(in);
        in.close();
    }
    else
    {
        ReadStreamBuffer tmp(dataSource->getBuffer());
        istream in(&tmp);
        readFromStream(in);
    }
    
    this->mode = mode;
}

FollowablePath::FollowablePath(const fs::path &path, int mode)
{
    ifstream in(path.c_str(), ifstream::binary);
    readFromStream(in);
    in.close();
    
    this->mode = mode;
}

FollowablePath::FollowablePath(Buffer &buffer, int mode)
{
    ReadStreamBuffer tmp(buffer);
    istream in(&tmp);
    readFromStream(in);
    
    this->mode = mode;
}

FollowablePath::~FollowablePath()
{
    delete[] x;
    delete[] y;
    delete[] len;
}

void FollowablePath::setPoints(const std::vector<ci::Vec2f> &points)
{
    ensureCapacity(points.size());
    size = 0;
    
    float lastX = numeric_limits<float>::max();
    float lastY = numeric_limits<float>::max();
    
    for (vector<Vec2f>::const_iterator it = points.begin(); it != points.end(); ++it)
    {
        if (!((it->x == lastX) && (it->y == lastY)))
        {
            add(it->x, it->y);
            lastX = it->x;
            lastY = it->y;
        }
    }
}

void FollowablePath::readFromStream(istream &in)
{
    capacity = DataStreamIO::readLittle<int>(in);
    
    size = 0;
    x = new float[capacity];
    y = new float[capacity];
    len = new float[capacity];
    
    for (int i = 0; i < capacity; i++)
    {
        float xx = DataStreamIO::readLittle<float>(in);
        float yy = DataStreamIO::readLittle<float>(in);
        add(xx, yy);
    }
}

void FollowablePath::write(const fs::path &path)
{
    ofstream out(path.c_str(), ifstream::binary);
    writeToStream(out);
    out.close();
}

Buffer FollowablePath::write()
{
    int bufferSize = sizeof(int) + 2 * size * sizeof(float);
    Buffer buffer = Buffer(bufferSize);
    
    WriteStreamBuffer tmp(buffer);
    ostream out(&tmp);
    
    writeToStream(out);
    return buffer;
}

void FollowablePath::writeToStream(ostream &out)
{
    DataStreamIO::writeLittle(out, size);
    
    for (int i = 0; i < size; i++)
    {
        DataStreamIO::writeLittle(out, x[i]);
        DataStreamIO::writeLittle(out, y[i]);
    }
}

void FollowablePath::ensureCapacity(int minCapacity)
{
    if (minCapacity > capacity)
    {
        capacity = (CAPACITY_INCREMENT > 0) ? (capacity + CAPACITY_INCREMENT) : (capacity * 2);
        
        x = (float*) realloc(x, capacity * sizeof(float));
        y = (float*) realloc(y, capacity * sizeof(float));
        len = (float*) realloc(len, capacity * sizeof(float));
    }
}

void FollowablePath::add(float xx, float yy)
{
    ensureCapacity(size + 1);
    
    x[size] = xx;
    y[size] = yy;
    
    if (size > 0)
    {
        float dx = xx - x[size - 1];
        float dy = yy - y[size - 1];
        len[size] = len[size - 1] + sqrtf(dx * dx + dy * dy);
    }
    else
    {
        len[0] = 0;
    }
    
    size++;
}

float FollowablePath::getLength()
{
    return len[size - 1];
}

void FollowablePath::clear()
{
    size = 0;
}

void FollowablePath::pos2Point(float pos, float *res)
{
    float length = len[size - 1];
    
    if (mode == MODE_LOOP || mode == MODE_MODULO)
    {
        pos = boundf(pos, length);
    }
    else
    {
        if (pos <= 0)
        {
            if (mode == MODE_BOUNDED)
            {
                *res++ = x[0];
                *res++ = y[0];
                *res   = 0;
                return;
            }
        }
        else if (pos >= length)
        {
            if (mode == MODE_BOUNDED)
            {
                *res++ = x[size - 1];
                *res++ = y[size - 1];
                *res   = length;
                return;
            }
        }
    }
    
    int index = search(len, pos, 1, size);
    
    float x0 = x[index];
    float y0 = y[index];
    
    float x1 = x[index + 1];
    float y1 = y[index + 1];
    
    float ratio = (pos - len[index]) / (len[index + 1] - len[index]);
    *res++ = x0 + (x1 - x0) * ratio;
    *res++ = y0 + (y1 - y0) * ratio;
    *res   = pos;
}

float FollowablePath::pos2Angle(float pos)
{
    float length = len[size - 1];
    
    if (mode == MODE_LOOP || mode == MODE_MODULO)
    {
        pos = boundf(pos, length);
    }
    else
    {
        if (pos <= 0)
        {
            if (mode == MODE_BOUNDED)
            {
                pos = 0;
            }
        }
        else if (pos >= length)
        {
            if (mode == MODE_BOUNDED)
            {
                pos = length;
            }
        }
    }
    
    int index = search(len, pos, 1, size);
    
    float x0 = x[index];
    float y0 = y[index];
    
    float x1 = x[index + 1];
    float y1 = y[index + 1];
    
    return atan2f(y1 - y0, x1 - x0);
}

float FollowablePath::pos2SampledAngle(float pos, float sampleSize)
{
    float res[2];
    pos2Gradient(pos, sampleSize, res);
    float dx = res[0];
    float dy = res[1];
    
    /*
     * WE USE AN EPSILON VALUE TO AVOID
     * DEGENERATED RESULTS IN SOME EXTREME CASES
     * (E.G. CLOSE TO 180 DEGREE DIFF. BETWEEN TWO SEGMENTS)
     */
    if ((dx * dx + dy * dy) > 1.0)
    {
        return atan2f(dy, dx);
    }
    else
    {
        return pos2Angle(pos);
    }
}

void FollowablePath::pos2Gradient(float pos, float sampleSize, float *res)
{
    float halfSampleSize = sampleSize / 2;
    
    float pm[3];
    pos2Point(pos - halfSampleSize, pm);
    
    float pp[3];
    pos2Point(pos + halfSampleSize, pp);
    
    float dx = pp[0] - pm[0];
    float dy = pp[1] - pm[1];
    
    *res++ = dx / 2;
    *res   = dy / 2;
}

/*
 * RETURNS false IF CLOSEST POINT IS FARTHER THAN min DISTANCE
 *
 * res[0]: CLOSEST-POINT X
 * res[1]: CLOSEST-POINT Y
 * res[2]: POSITION OF CLOSEST-POINT
 * res[3]: DISTANCE TO CLOSEST-POINT
 * 
 * REFERENCE: "Minimum Distance between a Point and a Line" BY Paul Bourke
 * http://local.wasp.uwa.edu.au/~pbourke/geometry/pointline
 */
bool FollowablePath::findClosestPoint(float xx, float yy, float min, float *res)
{
    min *= min; // BECAUSE WE COMPARE "MAGNIFIED DISTANCES" (FASTER...)
    
    int index = -1;
    float _x, _y, _len;
    
    for (int i = 0; i < size; i++)
    {
        int i0, i1;
        if (i == size - 1)
        {
            i0 = i - 1;
            i1 = i;
        }
        else
        {
            i0 = i;
            i1 = i + 1;
        }
        
        float d = len[i1] - len[i0];
        float x0 = x[i0];
        float y0 = y[i0];
        float x1 = x[i1];
        float y1 = y[i1];
        
        float u = ((xx - x0) * (x1 - x0) + (yy - y0) * (y1 - y0)) / (d * d);
        if (u >= 0 && u <= 1)
        {
            float xp = x0 + u * (x1 - x0);
            float yp = y0 + u * (y1 - y0);
            
            float dx = xp - xx;
            float dy = yp - yy;
            float mag = dx * dx + dy * dy;
            
            if (mag < min)
            {
                min = mag;
                index = i0;
                
                _x = xp;
                _y = yp;
                _len = len[index] + d * u;
            }
        }
        else
        {
            float dx0 = x0 - xx;
            float dy0 = y0 - yy;
            float mag1 = dx0 * dx0 + dy0 * dy0;
            
            float dx1 = x1 - xx;
            float dy1 = y1 - yy;
            float mag2 = dx1 * dx1 + dy1 * dy1;
            
            if ((mag1 < min) && (mag1 < mag2))
            {
                min = mag1;
                index = i0;
                
                _x = x0;
                _y = y0;
                _len = len[index];
            }
            else if ((mag2 < min) && (mag2 < mag1))
            {
                min = mag2;
                index = i1;
                
                _x = x1;
                _y = y1;
                _len = len[index];
            }
        }
    }
    
    if (index != -1)
    {
        res[0] = _x;
        res[1] = _y;
        res[2] = _len;
        res[3] = sqrtf(min);
        
        return true;
    }
    
    return false;
}

/*
 * segmentIndex MUST BE < size
 *
 * res[0]: CLOSEST-POINT X
 * res[1]: CLOSEST-POINT Y
 * res[2]: POSITION OF CLOSEST-POINT
 * res[3]: DISTANCE TO CLOSEST-POINT
 * 
 * REFERENCE: "Minimum Distance between a Point and a Line" BY Paul Bourke
 * http://local.wasp.uwa.edu.au/~pbourke/geometry/pointline
 */
void FollowablePath::closestPointFromSegment(float xx, float yy, int segmentIndex, float *res)
{
    int i0 = segmentIndex;
    int i1 = segmentIndex + 1;
    
    float d = len[i1] - len[i0];
    float x0 = x[i0];
    float y0 = y[i0];
    float x1 = x[i1];
    float y1 = y[i1];
    
    float u = ((xx - x0) * (x1 - x0) + (yy - y0) * (y1 - y0)) / (d * d);
    if (u >= 0 && u <= 1)
    {
        float xp = x0 + u * (x1 - x0);
        float yp = y0 + u * (y1 - y0);
        
        float dx = xp - xx;
        float dy = yp - yy;
        float mag = dx * dx + dy * dy;
        
        *res++ = xp;
        *res++ = yp;
        *res++ = len[i0] + d * u;
        *res   = sqrtf(mag);
    }
    else
    {
        float dx0 = x0 - xx;
        float dy0 = y0 - yy;
        float mag0 = dx0 * dx0 + dy0 * dy0;
        
        float dx1 = x1 - xx;
        float dy1 = y1 - yy;
        float mag1 = dx1 * dx1 + dy1 * dy1;
        
        if (mag0 < mag1)
        {
            *res++ = x0;
            *res++ = y0;
            *res++ = len[i0];
            *res   = sqrtf(mag0);
        }
        else
        {
            *res++ = x1;
            *res++ = y1;
            *res++ = len[i1];
            *res   = sqrtf(mag1);
        }
    }
}

void FollowablePath::measure(float *minX, float *minY, float *maxX, float *maxY)
{
    *minX = numeric_limits<float>::max();
    *minY = numeric_limits<float>::max();
    *maxX = numeric_limits<float>::min();
    *maxY = numeric_limits<float>::min();
    
    for (int i = 0; i < size; i++)
    {
        float xx = x[i];
        float yy = y[i];
        
        if (xx < *minX) *minX = xx;
        if (yy < *minY) *minY = yy;
        
        if (xx > *maxX) *maxX = xx;
        if (yy > *maxY) *maxY = yy;
    }
}
