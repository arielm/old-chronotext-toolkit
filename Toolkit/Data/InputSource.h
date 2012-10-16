#pragma once

#include "cinder/DataSource.h"

typedef std::shared_ptr<class InputSource> InputSourceRef;

class InputSource
{
    int type;
    
    std::string resourceName;
    int mswID;
    std::string mswType;
    ci::fs::path filePath;
    std::string filePathHint;
    
    InputSource(int type) : type(type) {}

public:
    enum
    {
        TYPE_RESOURCE,
        TYPE_RESOURCE_MSW,
        TYPE_FILE
    };
    
    static InputSourceRef getResource(const std::string &resourceName);
    static InputSourceRef getResource(const std::string &resourceName, int mswID, const std::string &mswType);
    static InputSourceRef getFileInDocuments(const std::string &relativePath);
    static InputSourceRef getFile(const ci::fs::path &filePath);
    
    ci::DataSourceRef loadDataSource();
    
    bool isFile();
    ci::fs::path getFilePath();
    
    std::string getFilePathHint();
    std::string getUniqueName();
};
