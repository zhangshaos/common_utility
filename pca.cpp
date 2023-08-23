#include "pca.h"
#undef NDEBUG
#include <cassert>


PCA_2D::PCA_2D(const std::vector<Eigen::Vector2d > &in_points)
  : ref_points{ in_points } {
  assert(in_points.size() > 1 && "points number for PCA must >= 2!");
  for (const auto &p : in_points) {
    center += p;
  }
  center /= (double) in_points.size();
  //构建协方差矩阵
  double xx=0, xy=0, yy=0;
  for (auto p : in_points) {
    p -= center;
    xx += p.x() * p.x();
    xy += p.x() * p.y();
    yy += p.y() * p.y();
  }
  xx /= double( in_points.size() );
  xy /= double( in_points.size() );
  yy /= double( in_points.size() );
  cov <<
  xx, xy,
  xy, yy;
}

void PCA_2D::pca() {
  auto svd_result = cov.jacobiSvd(Eigen::ComputeFullV);
  auto singulars = svd_result.singularValues();
  out_singular_0 = singulars(0);
  out_singular_1 = singulars(1);
  out_dir_0 = svd_result.matrixV().col(0);
  out_dir_1 = svd_result.matrixV().col(1);
  //计算最远和最近距离（带符号）
  double min_dist_along_dir_0 = 1e9, max_dist_along_dir_0 = -1e9,
         min_dist_along_dir_1 = 1e9, max_dist_along_dir_1 = -1e9;
  for (auto p : ref_points) {
    p -= center;
    double d_0 = p.dot(out_dir_0), d_1 = p.dot(out_dir_1);
    min_dist_along_dir_0 = std::min(min_dist_along_dir_0, d_0);
    max_dist_along_dir_0 = std::max(max_dist_along_dir_0, d_0);
    min_dist_along_dir_1 = std::min(min_dist_along_dir_1, d_1);
    max_dist_along_dir_1 = std::max(max_dist_along_dir_1, d_1);
  }
  out_length_along_dir_0 = max_dist_along_dir_0 - min_dist_along_dir_0;
  out_length_along_dir_1 = max_dist_along_dir_1 - min_dist_along_dir_1;
  if (out_length_along_dir_0 < 0 || out_length_along_dir_1 < 0) {
    throw std::runtime_error{"PCA_2D::pac(): length of points along every axis "
                             "should be not less than 0!"};
  }
}
