#include "BSplineHelper.h"

#define SPLINE_TOL 3.0

using namespace ci;
using namespace std;

void BSplineHelper::readBSplinePath(FollowablePathRef path, DataSourceRef dataSource)
{
    if (dataSource->isFilePath())
    {
        ifstream in(dataSource->getFilePath().c_str(), ifstream::binary);
        readBSplinePathFromStream(path, in);
        in.close();
    }
    else
    {
        ReadStreamBuffer tmp(dataSource->getBuffer());
        std::istream in(&tmp);
        readBSplinePathFromStream(path, in);
    }
}

void BSplineHelper::readBSplinePathFromStream(FollowablePathRef path, istream &in)
{
    int size = DataStreamIO::readLittle<int>(in);
    float *x = new float[size];
    float *y = new float[size];
    
    for (int i = 0; i < size; i++)
    {
        x[i] = DataStreamIO::readLittle<float>(in);
    }
    
    for (int i = 0; i < size; i++)
    {
        y[i] = DataStreamIO::readLittle<float>(in);
    }
    
    // ---
    
    SplinePath *spline = new SplinePath(256, SPLINE_TOL, GammaBSpline);
    
    // B-SPLINE: ADDING N POINTS AT THE BEGINNING
    for (int i = 0; i < 2; i++)
    {
        spline->add(x[0], y[0]);
    }
    
    for (int i = 0; i < size; i++)
    {
        spline->add(x[i], y[i]);
    }
    
    // B-SPLINE: ADDING N POINTS AT THE END
    for (int i = 0; i < 3; i++)
    {
        spline->add(x[size - 1], y[size - 1]);
    }
    
    path->clear();
    spline->compute(&*path);
    
    // ---
    
    delete[] x;
    delete[] y;
    delete spline;
}
