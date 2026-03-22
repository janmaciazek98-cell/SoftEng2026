#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest/gtest.h>
#include "ShapeFactory.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(test_triangle, ValidTriangle)
{
    bool res = true;
    ShapeParam<float> param;

    // ustawiamy boki trójkąta 3-4-5
    res = param.set_attrib(ShapeParamIndex::PARAM_WIDTH, 3.f);
    ASSERT_NE(res, false);

    res = param.set_attrib(ShapeParamIndex::PARAM_HEIGHT, 4.f);
    ASSERT_NE(res, false);

    res = param.set_attrib(ShapeParamIndex::PARAM_DEPTH, 5.f);
    ASSERT_NE(res, false);

    param.type = ShapeType::PT_TRIANGLE;

    res = param.validate();
    ASSERT_NE(res, false);

    auto shape =
        std::unique_ptr<IShape<float>>(ShapeFactory<float>::create(param));

    ASSERT_NE(shape, nullptr);

    auto data = shape->compute();

    float area = data.get_attrib(ShapeResultIndex::RESULT_AREA);
    float perimeter = data.get_attrib(ShapeResultIndex::RESULT_PERIMETER);

    ASSERT_NEAR(area, 6.0f, 0.01f);
    ASSERT_NEAR(perimeter, 12.0f, 0.01f);
}

TEST(test_triangle, InvalidTriangle)
{
    ShapeParam<float> param;

    // NIE spełnia nierówności trójkąta
    param.set_attrib(ShapeParamIndex::PARAM_WIDTH, 1.f);
    param.set_attrib(ShapeParamIndex::PARAM_HEIGHT, 2.f);
    param.set_attrib(ShapeParamIndex::PARAM_DEPTH, 10.f);

    param.type = ShapeType::PT_TRIANGLE;

    auto shape =
        std::unique_ptr<IShape<float>>(ShapeFactory<float>::create(param));

    ASSERT_NE(shape, nullptr);

    auto data = shape->compute();

    float area = data.get_attrib(ShapeResultIndex::RESULT_AREA);

    ASSERT_EQ(area, 0.f);
}

TEST(test_triangle, ZeroValue)
{
    ShapeParam<float> param;

    param.set_attrib(ShapeParamIndex::PARAM_WIDTH, 0.f);
    param.set_attrib(ShapeParamIndex::PARAM_HEIGHT, 4.f);
    param.set_attrib(ShapeParamIndex::PARAM_DEPTH, 5.f);

    param.type = ShapeType::PT_TRIANGLE;

    auto shape =
        std::unique_ptr<IShape<float>>(ShapeFactory<float>::create(param));

    auto data = shape->compute();

    float area = data.get_attrib(ShapeResultIndex::RESULT_AREA);

    ASSERT_EQ(area, 0.f);
}