// b5e736b9ffe28a2aa3aee66ba6788251
// autogenerated file
#pragma once

#include <fbt/ifunction-block-fabric.hpp>

class AMOTOR_Fabric : public IFunctionalBlockFabric {
public:
    virtual std::vector<ParameterInfo> GetParametersInfo() const;
    virtual TechDataInfo GetRetainInfo() const;
    virtual FunctionBlockInfo GetFbInfo() const;
    virtual std::unique_ptr<IFunctionBlock> CreateBlock(IFunctionalBlockData& data);
};
