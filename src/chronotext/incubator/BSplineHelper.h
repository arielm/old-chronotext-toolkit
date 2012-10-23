#pragma once

#include "chronotext/path/FollowablePath.h"
#include "chronotext/path/SplinePath.h"

class BSplineHelper
{
public:
    static void readBSplinePath(FollowablePath *path, InputSourceRef inputSource);
    static void readBSplinePathFromStream(FollowablePath *path, std::istream &in);
};
