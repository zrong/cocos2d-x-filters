
#ifndef CCCUSTOM_FILTER
#define CCCUSTOM_FILTER

#include "json/rapidjson.h"
#include "json/document.h"
#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== TestFilter

class CustomFilter : public Filter
{

public:
    static CustomFilter* create();
    static CustomFilter* create(std::string paramsStr);

    CustomFilter();

    void setParameter(const char* paramsStr);
protected:
    virtual GLProgram* loadShader();
    virtual void setUniforms(GLProgram* glp);
    
    std::string m_vertFile;
    std::string m_fragFile;
    rapidjson::Document m_json;
};

NS_CC_EXT_END

#endif //CCCUSTOM_FILTER
