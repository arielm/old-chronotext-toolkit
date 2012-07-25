#pragma once

#include "cinder/Utilities.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <streambuf>

/*
 * ALLOWING FILE AND MEMORY BASED IO
 * SIMILAR TO JAVA'S DataInputStream, DataOutputStream
 * SIMILAR TO JAVA'S ByteArrayInputStream, ByteArrayOutputStream
 */

struct ReadStreamBuffer : public std::streambuf
{
    ReadStreamBuffer(ci::Buffer &buffer)
    {
        char *data = (char*)buffer.getData();
        size_t size = buffer.getDataSize();
        
        setg(data, data, data + size);
    }
};

struct WriteStreamBuffer : public std::streambuf
{
    WriteStreamBuffer(ci::Buffer &buffer)
    {
        char *data = (char*)buffer.getData();
        size_t size = buffer.getDataSize();

        setp(data, data + size);
    }
};

class DataStreamIO
{
public:
    static ci::Buffer toBuffer(std::stringstream &out, bool freeWhenDone)
    {
        out.seekg(0, std::ios::end);
        size_t size = out.tellg();
        out.seekg(0, std::ios::beg);
        
        if (freeWhenDone)
        {
            ci::Buffer buffer = ci::Buffer(size);
            out.read((char*)buffer.getData(), size);
            return buffer;
        }
        else
        {
            void *tmp = malloc(size);
            out.read((char*)tmp, size);
            return ci::Buffer(tmp, size);
        }
    }

    // ---

    template<typename T>
    static T readLittle(std::istream &in)
    {
        T t;
        in.read((char*)&t, sizeof(T));
        
#if BOOST_BIG_ENDIAN
        t = ci::swapEndian(t);
#endif
        
        return t;
    }
    
    template<typename T>
    static T readBig(std::istream &in)
    {
        T t;
        in.read((char*)&t, sizeof(T));
        
#ifndef BOOST_BIG_ENDIAN
    t = ci::swapEndian(t);
#endif

    return t;
    }
    
    // ---
    
    template<typename T>
    static void writeLittle(std::ostream &out, T t)
    {
#if BOOST_BIG_ENDIAN
    t = ci::swapEndian(t);
#endif
    
    out.write((char*)&t, sizeof(T));
    }
    
    template<typename T>
    static void writeBig(std::ostream &out, T t)
    {
#ifndef BOOST_BIG_ENDIAN
    t = ci::swapEndian(t);
#endif
    
    out.write((char*)&t, sizeof(T));
    }
    
    // ---
    
    static void writeStringLittle(std::ostream &out, const std::string &s)
    {
    uint16_t len = s.length();
    writeLittle(out, len);
    
    if (len > 0)
    {
        out.write(s.data(), len);
    }
    }
    
    static void writeStringBig(std::ostream &out, const std::string &s)
    {
    uint16_t len = s.length();
    writeBig(out, len);
    
    if (len > 0)
    {
        out.write(s.data(), len);
    }
    }
    
    // ---

    static std::string readStringLittle(std::istream &in)
    {
    std::string s;
    
    uint16_t len = readLittle<uint16_t>(in);
    if (len > 0)
    {
        char *data = new char[len];
        in.read(data, len);
        
        s.assign(data, len);
        delete[] data;
    }
    
    return s;
    }
    
    static std::string readStringBig(std::istream &in)
    {
    std::string s;
    
    uint16_t len = readBig<uint16_t>(in);
    if (len > 0)
    {
        char *data = new char[len];
        in.read(data, len);
        
        s.assign(data, len);
        delete[] data;
    }
    
    return s;
    }
};
