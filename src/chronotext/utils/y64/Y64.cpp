#include "chronotext/utils/y64/Y64.h"

extern "C" 
{
#include "chronotext/utils/y64/cencode.h"
#include "chronotext/utils/y64/cdecode.h"
}

using namespace std;
using namespace ci;

namespace Y64
{
    string toBase64(const void *input, int inputSize)
    {
        if (inputSize == 0)
        {
            return string();
        }
        
        char *buffer = new char[inputSize * 4 / 3 + 4];
        
        base64_encodestate state;
        base64_init_encodestate(&state);
        
        int resultSize = base64_encode_block(reinterpret_cast<const char*>(input), inputSize, &buffer[0], &state);
        resultSize += base64_encode_blockend(&buffer[resultSize], &state);
        buffer[resultSize] = 0; // NULL TERMINATE THE STRING
        
        string result(buffer);
        delete[] buffer;
        
        return result;
    }
    
    string toBase64(const Buffer &input)
    {
        return toBase64(input.getData(), input.getDataSize());
    }
    
    Buffer fromBase64(const void *input, size_t inputSize)
    {
        size_t outputSize = inputSize / 4 * 3;
        Buffer result = Buffer(outputSize);
        
        if (inputSize >= 4)
        {
            base64_decodestate state;
            base64_init_decodestate(&state);
            int actualSize = base64_decode_block(reinterpret_cast<const char*>(input), inputSize, (char*)result.getData(), &state);
            result.setDataSize(actualSize);
        }
        
        return result;
    }
    
    Buffer fromBase64(const string &input)
    {
        return fromBase64(input.c_str(), input.size());
    }
}
