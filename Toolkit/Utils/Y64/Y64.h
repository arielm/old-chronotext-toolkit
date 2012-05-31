#pragma once

#include "cinder/Buffer.h"

#include <string>

extern "C" 
{
#include "cencode.h"
#include "cdecode.h"
}

/*
 * BASED ON https://github.com/cinder/Cinder/blob/master/src/cinder/Base64.cpp
 * AND THE libb64 LIBRARY: http://libb64.sourceforge.net
 *
 * MODIFIED TO BE URL-SAFE:
 * SEE THE Y64 VARIANT IN http://en.wikipedia.org/wiki/Base64#Variants_summary_table
 */

#pragma once

#include "cinder/Buffer.h"

#include <string>

namespace Y64
{
    std::string toBase64(const void *input, int inputSize);
    std::string toBase64(const ci::Buffer &input);
    
    ci::Buffer fromBase64(const void *input, size_t inputSize);
    ci::Buffer fromBase64(const std::string &input);
}
