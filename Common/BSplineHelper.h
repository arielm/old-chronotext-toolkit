#pragma once

#include "cinder/DataSource.h"

#include "FollowablePath.h"
#include "SplinePath.h"

class BSplineHelper
{
public:
    static void readBSplinePath(FollowablePathRef path, ci::DataSourceRef dataSource);
    static void readBSplinePathFromStream(FollowablePathRef path, std::istream &in);
};
