/**
 * copied from https://github.com/zhangshaos/MonoPlanner.git
 */
#ifndef EXPLORER_MEAN_SHIFT_H
#define EXPLORER_MEAN_SHIFT_H

#include <vector>
#include <Eigen/Dense>

int
mean_shift_1d(std::vector<int> &elements_class,
              std::vector<double> &elements_mean,
              const std::vector<double> &elements,
              double r, double eps);

int
mean_shift_2d(std::vector<int> &elements_class,
              std::vector<Eigen::Vector2d > &elements_mean,
              const std::vector<Eigen::Vector2d > &elements,
              double r, double eps);


//输入数据为在同一个平面上的3D点
int
mean_shift_2d(std::vector<int> &elements_class,
              std::vector<Eigen::Vector3d > &elements_mean,
              const std::vector<Eigen::Vector3d > &elements,
              double r, double eps);

#endif //EXPLORER_MEAN_SHIFT_H
