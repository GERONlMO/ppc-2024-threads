// Copyright 2024 Ivanov Nikita
#pragma once

#include <string>
#include <vector>

#include "core/task/include/task.hpp"

typedef double (*func)(double a, double b);

class TestTaskSequentialSimpson : public ppc::core::Task {
 public:
  explicit TestTaskSequentialSimpson(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  int a{}, b{}, c{}, d{}, n{};
  double res{};
  func fun;
};

double linear_fun(double x, double y);
double sin_cos(double x, double y);
double x_mul_y(double x, double y);
