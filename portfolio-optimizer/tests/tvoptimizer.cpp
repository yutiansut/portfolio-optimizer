//
// Created by wegamekinglc on 3/16/18.
//

#include <cmath>
#include <gtest/gtest.h>
#include <pfopt/tvoptimizer.hpp>
#include <pfopt/types.hpp>
#include <iostream>

using namespace pfopt;

TEST(TVOptimizerTest, SimpleCase) {
    constexpr int n = 3;
    double er[] = {0.1, 0.2, 0.3};
    double cov[] = {0.05, 0.01, 0.02, 0.01, 0.06, 0.03, 0.02, 0.03, 0.07};
    double lb[] = {-0.3, -0.3, -0.3};
    double ub[] = {0.5, 0.5, 0.5};
    double target_vol = 0.1;

    TVOptimizer opt(n, er, cov, lb, ub, 0, nullptr, nullptr, nullptr, target_vol, target_vol);
    auto x_values = opt.xValue();
    auto y_value = opt.feval();

    MatrixXd varMatrix = Map<MatrixXd>(cov, n, n);
    VectorXd x_real  = Map<VectorXd>(x_values.data(), n);
    double calculated_vol = sqrt(x_real.dot(varMatrix * x_real));

    double x_expected[] = {0.0231776, 0.1274768, 0.30130881};
    ASSERT_NEAR(calculated_vol, target_vol, 1e-8);
    for(size_t i=0; i!=n; ++i) {
        ASSERT_NEAR(x_values[i], x_expected[i], 1e-6);
    }
}

TEST(TVOptimizerTest, SimpleCaseWithLinearConstraints) {
    constexpr int n = 3;
    double er[] = {0.1, 0.2, 0.3};
    double cov[] = {0.05, 0.01, 0.02, 0.01, 0.06, 0.03, 0.02, 0.03, 0.07};
    double lb[] = {-0.3, -0.3, -0.3};
    double ub[] = {0.5, 0.5, 0.5};

    constexpr  int n_cons = 1;
    double cons_matrix[] = {1., 1., 1.};
    double clb[] = {0.};
    double cub[] = {0.};
    double target_vol = 0.1;

    TVOptimizer opt(n, er, cov, lb, ub, 1, cons_matrix, clb, cub, 0., target_vol);
    auto x_values = opt.xValue();
    auto y_value = opt.feval();

    MatrixXd varMatrix = Map<MatrixXd>(cov, n, n);
    VectorXd x_real  = Map<VectorXd>(x_values.data(), n);
    double calculated_vol = sqrt(x_real.dot(varMatrix * x_real));

    double x_expected[] = {-0.3, -0.10919033, 0.40919033};
    ASSERT_NEAR(calculated_vol, target_vol, 1e-6);
    for(size_t i=0; i!=n; ++i) {
        ASSERT_NEAR(x_values[i], x_expected[i], 1e-6);
    }
}

TEST(TVOptimizerTest, SimpleCaseWithLinearConstraintsAndEqualVolCons) {
    constexpr int n = 3;
    double er[] = {0.1, 0.2, 0.3};
    double cov[] = {0.05, 0.01, 0.02, 0.01, 0.06, 0.03, 0.02, 0.03, 0.07};
    double lb[] = {-0.3, -0.3, -0.3};
    double ub[] = {0.5, 0.5, 0.5};

    constexpr  int n_cons = 1;
    double cons_matrix[] = {1., 1., 1.};
    double clb[] = {0.};
    double cub[] = {0.};
    double target_vol = 0.1;

    TVOptimizer opt(n, er, cov, lb, ub, 1, cons_matrix, clb, cub, target_vol, target_vol);
    auto x_values = opt.xValue();
    auto y_value = opt.feval();

    MatrixXd varMatrix = Map<MatrixXd>(cov, n, n);
    VectorXd x_real  = Map<VectorXd>(x_values.data(), n);
    double calculated_vol = sqrt(x_real.dot(varMatrix * x_real));

    double x_expected[] = {-0.3, -0.10919033, 0.40919033};
    ASSERT_NEAR(calculated_vol, target_vol, 1e-6);
    for(size_t i=0; i!=n; ++i) {
        ASSERT_NEAR(x_values[i], x_expected[i], 1e-6);
    }
}
