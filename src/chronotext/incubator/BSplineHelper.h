#pragma once

#include "cinder/DataSource.h"

#include "chronotext/path/FollowablePath.h"
#include "chronotext/path/SplinePath.h"

class BSplineHelper
{
public:
    static void readBSplinePath(FollowablePathRef path, ci::DataSourceRef dataSource);
    static void readBSplinePathFromStream(FollowablePathRef path, std::istream &in);
};
