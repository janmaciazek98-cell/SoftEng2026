#include <memory>
#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest/gtest.h>
#include <chrono> // Do pomiaru czasu
#include "ShapeFactory.h"

// TEST 1: Wydajnoœæ i Pamiêæ (unique_ptr)
TEST(test_shape1, PerformanceAndMemoryTest)
{
    ShapeParam<double> param;
    param.set_attrib(ShapeParamIndex::PARAM_RADIUS, 1.0);
    param.type = ShapeType::PT_CIRCLE;

    // unique_ptr automatycznie sprz¹ta pamiêæ - brak wycieków! [cite: 461]
    auto shape =
        std::unique_ptr<IShape<double>>(ShapeFactory<double>::create(param));
    ASSERT_NE(shape, nullptr);

    // Pomiar czasu: 100 iteracji [cite: 462]
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i)
    {
        shape->compute();
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();
    // Warunek: czas < 1ms (1000 mikrosekund) [cite: 462]
    EXPECT_LT(duration, 1000);
}

// TEST 2: Obs³uga ró¿nych typów danych (Template) [cite: 462]
TEST(test_shape1, MultiTypeSupportTest)
{
    // Sprawdzamy typ float
    ShapeParam<float> pFloat;
    pFloat.type = ShapeType::PT_CIRCLE;
    pFloat.set_attrib(ShapeParamIndex::PARAM_RADIUS, 2.0f);
    auto sFloat =
        std::unique_ptr<IShape<float>>(ShapeFactory<float>::create(pFloat));
    EXPECT_GT(sFloat->compute().get_attrib(ShapeResultIndex::RESULT_AREA),
              0.0f);
}