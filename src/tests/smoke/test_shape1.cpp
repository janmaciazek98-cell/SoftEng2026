#include <memory>
#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest/gtest.h>
#include <chrono>
#include "ShapeFactory.h"

TEST(test_shape1, PerformanceAndMemoryTest)
{
    ShapeParam<double> param;
    param.set_attrib(ShapeParamIndex::PARAM_RADIUS, 1.0);
    param.type = ShapeType::PT_CIRCLE;

    auto shape =
        std::unique_ptr<IShape<double>>(ShapeFactory<double>::create(param));
    ASSERT_NE(shape, nullptr);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i)
    {
        shape->compute();
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();
    EXPECT_LT(duration, 1000);
}

TEST(test_shape1, MultiTypeSupportTest)
{
    ShapeParam<float> pFloat;
    pFloat.type = ShapeType::PT_CIRCLE;
    pFloat.set_attrib(ShapeParamIndex::PARAM_RADIUS, 2.0f);
    auto sFloat =
        std::unique_ptr<IShape<float>>(ShapeFactory<float>::create(pFloat));
    EXPECT_GT(sFloat->compute().get_attrib(ShapeResultIndex::RESULT_AREA),
              0.0f);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}