#pragma once

#include "cinder/Cinder.h"
#include "cinder/Path2d.h"
#include "cinder/DataSource.h"
#include "tesselator.h"

#include "FlashShape.h"
#include "StrokeHelper.h"

/*
 * BASED ON:
 * - cinder/Triangulate.h
 * - ofTessellator.h
 */

struct FXGPath
{
    std::string data;
    float scale;
    float ox;
    float oy;
    
    FXGPath() : scale(1), ox(0), oy(0) {}
    FXGPath(std::string data, float scale) : data(data), scale(scale), ox(0), oy(0) {}
};

class FlashTesselator
{
    TESStesselator *tess;
    
public:
    FlashTesselator();
    ~FlashTesselator();
    
    FlashShape* calculate(ci::DataSourceRef dataSource, float scale);
    FlashShape* calculate(const FXGPath &fxg);
    FlashShape* calculate(const ci::Path2d &path, float approximationScale = 1.0f);
    
    ci::Path2d fxgToPath(float ox, float oy, float scale, const std::string &data) const;
};
