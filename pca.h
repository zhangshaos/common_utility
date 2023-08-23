#ifndef EXPLORER_PCA_H
#define EXPLORER_PCA_H

#include <vector>
#include <Eigen/Dense>


class PCA_2D {
public:
  explicit PCA_2D(const std::vector<Eigen::Vector2d > &in_points);

  void pca();

  Eigen::Vector2d center{0, 0};
  double out_singular_0 = 0;
  double out_singular_1 = 0;
  Eigen::Vector2d out_dir_0{ 0.,0. };
  Eigen::Vector2d out_dir_1{ 0.,0. };
  double out_length_along_dir_0 = 0;
  double out_length_along_dir_1 = 0;
private:
  Eigen::Matrix2d cov;
  const std::vector<Eigen::Vector2d > &ref_points;
};


#endif //EXPLORER_PCA_H
