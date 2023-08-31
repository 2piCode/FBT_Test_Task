#include <fbt/test/unit-test.hpp>

#include "amotor-mock-fbdata.h"
#include "amotor/amotor.h"

FBT_AUTO_TEST_SUITE(test_amotor);

FBT_AUTO_TEST_CASE(test_template_case_1) {
    MockFbData data = AMOTOR_GetMockFbData();
    IParameter& param_name = data.GetMockParameter("FBNAME");
    param_name = string64_t{"TEST"};
    AMOTOR block{data};

    block.Init();
    for (size_t i = 0; i < 200; ++i) {
        block.Execute();
    }

    FBT_TEST(static_cast<string64_t>(param_name) == string64_t{"TEST"});
    FBT_CHECK_EQUAL(static_cast<string64_t>(param_name), string64_t{"TEST"});
};

namespace continuous_mode {
    FBT_AUTO_TEST_CASE(continuous_count_value_once_execute) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        AMOTOR block{data};

        block.Init();
        block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{1});
    }

    FBT_AUTO_TEST_CASE(continuous_count_value_once_execute_with_ud) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& ud = data.GetMutableParameter("ud");
        ud = bool_t{true};
        AMOTOR block{data};

        block.Init();
        block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{-1});
    }

    FBT_AUTO_TEST_CASE(continuous_count_value_200_executes) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        AMOTOR block{data};

        block.Init();
        for (size_t i = 0; i < 200; i++)
            block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{200});
    }

    FBT_AUTO_TEST_CASE(continuous_count_value_with_different_delta) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& delta = data.GetMutableParameter("delta");
        delta = lint_t{3};
        AMOTOR block{data};

        block.Init();
        block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{3});
    }
}

namespace rising_mode
{
    FBT_AUTO_TEST_CASE(rising_count_value_once_execute) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& mode = data.GetMutableParameter("mode");
        mode = lint_t{1};
        AMOTOR block{data};

        block.Init();
        block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{0});
    }

    FBT_AUTO_TEST_CASE(rising_count_value_200_execute) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& mode = data.GetMutableParameter("mode");
        mode = lint_t{1};
        AMOTOR block{data};

        block.Init();
        for(int i = 0; i < 200; i++)
            block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{0});
    }

    FBT_AUTO_TEST_CASE(rising_count_value_with_different_in) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& mode = data.GetMutableParameter("mode");
        IParameter& in = data.GetMutableParameter("in");
        mode = lint_t{1};
        AMOTOR block{data};

        block.Init();
        for(int i = 0; i < 200; i++)
        {
            block.Execute();
            in = !static_cast<bool_t>(in);
        }

        FBT_TEST(static_cast<lint_t>(count) == lint_t{100});
    }
}

namespace falling_mode
{
    FBT_AUTO_TEST_CASE(falling_count_value_once_execute) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& mode = data.GetMutableParameter("mode");
        mode = lint_t{1};
        AMOTOR block{data};

        block.Init();
        block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{0});
    }

    FBT_AUTO_TEST_CASE(falling_count_value_200_execute) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& mode = data.GetMutableParameter("mode");
        IParameter& in = data.GetMutableParameter("in");
        mode = lint_t{1};
        AMOTOR block{data};

        block.Init();
        for(int i = 0; i < 200; i++)
            block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{0});
    }

    FBT_AUTO_TEST_CASE(falling_count_value_with_different_in) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& mode = data.GetMutableParameter("mode");
        IParameter& in = data.GetMutableParameter("in");
        mode = lint_t{1};
        AMOTOR block{data};

        block.Init();
        for(int i = 0; i < 200; i++)
        {
            block.Execute();
            in = !static_cast<bool_t>(in);
        }

        FBT_TEST(static_cast<lint_t>(count) == lint_t{100});
    }
}

namespace general {
    FBT_AUTO_TEST_CASE(count_value_with_different_qufa) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& qufa = data.GetMutableParameter("qufa");
        qufa = lreal_t{2.5};
        AMOTOR block{data};
        block.Init();
        block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{3});
    }

    FBT_AUTO_TEST_CASE(count_value_with_min_max) {
        MockFbData data = AMOTOR_GetMockFbData();
        IParameter& min_parameter = data.GetMutableParameter("min");
        IParameter& max_parameter = data.GetMutableParameter("max");
        const IParameter& count = data.GetMutableParameter("count");
        min_parameter = lint_t {0};
        max_parameter = lint_t {1};
        AMOTOR block{data};

        block.Init();
        FBT_TEST(static_cast<lint_t>(count) == lint_t{0});
        for (size_t i = 0; i < 200; i++)
            block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{200});
    }

    FBT_AUTO_TEST_CASE(lim_value_with_min_max) {
        MockFbData data = AMOTOR_GetMockFbData();
        IParameter& min_parameter = data.GetMutableParameter("min");
        IParameter& max_parameter = data.GetMutableParameter("max");
        IParameter& lim = data.GetMutableParameter("lim");
        min_parameter = lint_t {0};
        max_parameter = lint_t {1};
        AMOTOR block{data};

        block.Init();
        block.Execute();
        FBT_TEST(static_cast<bool_t>(lim) == bool_t{false});

        block.Execute();
        FBT_TEST(static_cast<bool_t>(lim) == bool_t{true});
    }

    FBT_AUTO_TEST_CASE(count_value_with_round) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& round = data.GetMutableParameter("round");
        IParameter& min = data.GetMutableParameter("min");
        IParameter& max = data.GetMutableParameter("max");
        round = bool_t{true};
        min = lint_t{0};
        max = lint_t{10};
        AMOTOR block{data};

        block.Init();
        for (size_t i = 0; i < 11; i++)
            block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{1});
    }

    FBT_AUTO_TEST_CASE(count_value_with_round_and_ud) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& round = data.GetMutableParameter("round");
        IParameter& ud = data.GetMutableParameter("ud");
        IParameter& min = data.GetMutableParameter("min");
        IParameter& max = data.GetMutableParameter("max");
        round = bool_t{true};
        ud = bool_t{true};
        min = lint_t{0};
        max = lint_t{10};
        AMOTOR block{data};

        block.Init();
        for (size_t i = 0; i < 11; i++)
            block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{9});
    }

    FBT_AUTO_TEST_CASE(count_value_with_reset) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& reset = data.GetMutableParameter("reset");
        const IParameter& cumcount = data.GetMutableParameter("cumcount");
        const IParameter& pcum = data.GetMutableParameter("pcum");
        AMOTOR block{data};

        block.Init();
        for(int i = 0; i < 10; i++)
            block.Execute();
        FBT_TEST(static_cast<lint_t>(count) == lint_t{10});
        FBT_TEST(static_cast<lint_t>(cumcount) == lint_t{10});

        reset = bool_t{true};
        block.Execute();
        FBT_TEST(static_cast<lint_t>(count) == lint_t{0});
        FBT_TEST(static_cast<bool_t>(reset) == bool_t{false});
        FBT_TEST(static_cast<lint_t>(cumcount) == lint_t{0});
        FBT_TEST(static_cast<lint_t>(pcum) == lint_t{11});
    }

    FBT_AUTO_TEST_CASE(count_value_with_clr) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        IParameter& clr = data.GetMutableParameter("clr");
        AMOTOR block{data};

        block.Init();
        for(int i = 0; i < 10; i++)
            block.Execute();
        FBT_TEST(static_cast<lint_t>(count) == lint_t{10});

        clr = bool_t{true};
        block.Execute();
        FBT_TEST(static_cast<lint_t>(count) == lint_t{0});
        FBT_TEST(static_cast<bool_t>(clr) == bool_t{false});
    }

    FBT_AUTO_TEST_CASE(count_value_with_hold) {
        MockFbData data = AMOTOR_GetMockFbData();
        const IParameter& count = data.GetMutableParameter("count");
        const IParameter& cumcount = data.GetMutableParameter("cumcount");
        IParameter& hold = data.GetMutableParameter("hold");
        IParameter& min = data.GetMutableParameter("min");
        IParameter& max = data.GetMutableParameter("max");
        hold = bool_t{true};
        min = lint_t{0};
        max = lint_t{10};
        AMOTOR block{data};

        block.Init();
        for (size_t i = 0; i < 50; i++)
            block.Execute();

        FBT_TEST(static_cast<lint_t>(count) == lint_t{11});
        FBT_TEST(static_cast<lint_t>(cumcount) == lint_t{50});
    }
}

FBT_AUTO_TEST_SUITE_END();
