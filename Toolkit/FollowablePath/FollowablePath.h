#pragma once

#include "DataStreamIO.h"

#include "cinder/DataSource.h"
#include "cinder/Rect.h"

typedef boost::shared_ptr<class FollowablePath> FollowablePathRef;

class FollowablePath
{
    void ensureCapacity(int minCapacity);
    
public:
    enum
    {
        MODE_BOUNDED,
        MODE_LOOP,
        MODE_TANGENT,
        MODE_MODULO,
    };

    int size;
    int capacity;
    int mode;
    float *x;
    float *y;
    float *len;
    
    FollowablePath(int mode);
    FollowablePath(int capacity, int mode);
    FollowablePath(const std::vector<ci::Vec2f> &points, int mode);
    FollowablePath(ci::DataSourceRef dataSource, int mode);
    FollowablePath(const ci::fs::path &path, int mode);
    FollowablePath(ci::Buffer &buffer, int mode);

    ~FollowablePath();
    
    void setPoints(const std::vector<ci::Vec2f> &points);
    void readFromStream(std::istream &in);
    
    void write(const ci::fs::path &path);
    ci::Buffer write();
    void writeToStream(std::ostream &out);
    
    void add(float x, float y);
    float getLength();
    void clear();
    
    void pos2Point(float pos, float *res);
    float pos2Angle(float pos);
    float pos2SampledAngle(float pos, float sampleSize);
    void pos2Gradient(float pos, float sampleSize, float *res);
    
    bool findClosestPoint(float x, float y, float min, float *res);
    void closestPointFromSegment(float x, float y, int segmentIndex, float *res);
    
    ci::Rectf getBounds() const;
};
