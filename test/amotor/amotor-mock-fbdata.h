#pragma once

#include <fbt/test/mock-fbdata.hpp>
#include "amotor/amotor-fabric.h"

static inline AMOTOR_Fabric varAMOTOR_Fabric;

MockFbData AMOTOR_GetMockFbData() {
    return MockFbData(varAMOTOR_Fabric.GetParametersInfo(), varAMOTOR_Fabric.GetRetainInfo());
}
