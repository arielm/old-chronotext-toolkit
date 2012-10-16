#include "InputSource.h"

#include "cinder/app/App.h"
#include "cinder/Utilities.h"

using namespace std;
using namespace ci;
using namespace app;

InputSourceRef InputSource::getResource(const std::string &resourceName)
{
    InputSource *source = new InputSource(TYPE_RESOURCE);
    source->resourceName = source->filePathHint = resourceName;

#if defined(CINDER_COCOA)
    source->filePath = App::getResourcePath(resourceName);
#endif

    return InputSourceRef(source);
}

InputSourceRef InputSource::getResource(const string &resourceName, int mswID, const std::string &mswType)
{
#if defined(CINDER_MSW)
    InputSource *source = new InputSource(TYPE_RESOURCE_MSW);
#else
    InputSource *source = new InputSource(TYPE_RESOURCE);
#endif

    source->resourceName = source->filePathHint = resourceName;
    
#if defined(CINDER_MSW)
    source->mswID = mswID;
    source->mswType = mswType;
#endif
    
#if defined(CINDER_COCOA)
    source->filePath = App::getResourcePath(resourceName);
#endif
    
    return InputSourceRef(source);
}

InputSourceRef InputSource::getFileInDocuments(const std::string &relativePath)
{
    return InputSource::getFile(getDocumentsDirectory() / relativePath);
}

InputSourceRef InputSource::getFile(const fs::path &filePath)
{
    InputSource *source = new InputSource(TYPE_FILE);
    source->filePath = filePath;
    source->filePathHint = filePath.filename().string();
    
    return InputSourceRef(source);
}

DataSourceRef InputSource::loadDataSource()
{
    switch (type)
    {
        case TYPE_RESOURCE:
#if defined(CINDER_MSW)
			return DataSourcePath::create(resourceName);
#else
			return loadResource(resourceName);
#endif

        case TYPE_RESOURCE_MSW:
            return loadResource(resourceName, mswID, mswType);
            
        case TYPE_FILE:
            return DataSourcePath::create(filePath);
    }
    
    return DataSourceRef();
}

bool InputSource::isFile()
{
    return !filePath.empty();
}

fs::path InputSource::getFilePath()
{
    return filePath;
}

string InputSource::getFilePathHint()
{
    return filePathHint;
}

string InputSource::getUniqueName()
{
    switch (type)
    {
        case TYPE_RESOURCE:
            return "RESOURCE:" + resourceName;

		case TYPE_RESOURCE_MSW:
            return "RESOURCE_MSW:" + boost::lexical_cast<string>(mswID) + ":" + mswType;
            
        case TYPE_FILE:
            return "FILE:" + filePath.string();
    }

    return "";
}
