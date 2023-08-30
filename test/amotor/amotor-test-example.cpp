#include <fbt/test/unit-test.hpp>

#include "amotor-mock-fbdata.h"
#include "amotor/amotor.h"

FBT_AUTO_TEST_SUITE(test_amotor);

FBT_AUTO_TEST_CASE(test_template_case_1) {
    // arrange
    MockFbData data = AMOTOR_GetMockFbData();
    IParameter& param_name = data.GetMockParameter("FBNAME");
    param_name = string64_t{"TEST"};
    AMOTOR block{data};
    
    // act
    block.Init();
    for (size_t i = 0; i < 200; ++i) {
        block.Execute();
    }
    
    // assert
    FBT_TEST(static_cast<string64_t>(param_name) == string64_t{"TEST"});
    FBT_CHECK_EQUAL(static_cast<string64_t>(param_name), string64_t{"TEST"});
};

FBT_AUTO_TEST_SUITE_END();
