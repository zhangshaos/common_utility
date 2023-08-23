#include "mean_shift.h"
#include <algorithm>
#include <execution>

inline
bool
all_less(const std::vector<double> &elements, double v) {
  auto greater = std::find_if_not(
      std::execution::seq,
      elements.begin(),
      elements.end(),
      [&v](double a) { return a < v; });
  return greater == elements.end();
}

inline
double
distance_1d(double l, double r) {
  return abs(l - r);
}

int
mean_shift_1d(std::vector<int> &elements_class,
              std::vector<double> &elements_mean,
              const std::vector<double> &elements,
              double r, double eps) {
  //改进的MeanShift算法
  const size_t N = elements.size();
  elements_mean = elements;
  std::vector<double> new_means(N);
  std::vector<double> delta_distance(N);
  std::vector<double> radius(N, r);
  do {
    //更新new_means
    for (size_t i = 0; i < N; ++i) {
      double near_element_sum = 0;
      size_t near_element_count = 0;
      for (size_t j = 0; j < N; ++j) {
        if (distance_1d(elements_mean[i], elements_mean[j]) < radius[i]) {
          near_element_sum += elements_mean[j];
          ++near_element_count;
        }
      }//计算和 i 相邻的元素个数和它们的均值
      if (near_element_count > 1) {//最近元素包含自己
        if (radius[i] > r && delta_distance[i] > eps) {
          //如果上一次移动了，则复原原来的搜索半径
          radius[i] *= 0.5;
        }
        double new_mean =
            near_element_sum / (double) near_element_count;
        delta_distance[i] = distance_1d(new_mean, elements_mean[i]);
        new_means[i] = new_mean;
      } else {
        //如果找不到相邻的元素，将当前元素 i 对应的半径扩大一倍
        radius[i] *= 2;
        delta_distance[i] = 0;
        new_means[i] = elements_mean[i];
      }
    }//新均值中心计算完毕
    elements_mean.swap(new_means);
  } while ( !all_less(delta_distance, eps) );
  //合并means，得到类别
  elements_class.resize(N, -1);
  int max_class = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i - 1; j >= 0; --j) {
      if (distance_1d(elements_mean[i], elements_mean[j]) < r) {
        elements_class[i] = elements_class[j];
        break;
      }
    }
    if (elements_class[i] == -1) {
      elements_class[i] = max_class;
      ++max_class;
    }
  }
  return max_class;
}

inline
double
distance_2d(const Eigen::Vector2d &l, const Eigen::Vector2d &r) {
  double dx = l.x() - r.x(), dy = l.y() - r.y();
  return dx*dx + dy*dy;
}

int
mean_shift_2d(std::vector<int> &elements_class,
              std::vector<Eigen::Vector2d > &elements_mean,
              const std::vector<Eigen::Vector2d > &elements,
              double r, double eps) {
  //改进的MeanShift算法
  //使用L2距离的平方
  r = r*r;
  eps = eps*eps;
  const size_t N = elements.size();
  elements_mean = elements;
  std::vector<Eigen::Vector2d > new_means(N);
  std::vector<double> delta_distance(N);
  std::vector<double> radius(N, r);
  do {
    //更新new_means
    for (size_t i = 0; i < N; ++i) {
      Eigen::Vector2d near_element_sum{0, 0};
      size_t near_element_count = 0;
      for (size_t j = 0; j < N; ++j) {
        if (distance_2d(elements_mean[i], elements_mean[j]) < radius[i]) {
          near_element_sum += elements_mean[j];
          ++near_element_count;
        }
      }//计算和 i 相邻的元素个数和它们的均值
      if (near_element_count > 1) {//最近元素包含自己
        if (radius[i] > r && delta_distance[i] > eps) {
          //如果上一次移动了，则复原原来的搜索半径
          radius[i] *= 0.5;
        }
        Eigen::Vector2d new_mean =
            near_element_sum / (double) near_element_count;
        delta_distance[i] = distance_2d(new_mean, elements_mean[i]);
        new_means[i] = new_mean;
      } else {
        //如果找不到相邻的元素，将当前元素 i 对应的半径扩大一倍
        radius[i] *= 2;
        delta_distance[i] = 0;
        new_means[i] = elements_mean[i];
      }
    }//新均值中心计算完毕
    elements_mean.swap(new_means);
  } while ( !all_less(delta_distance, eps) );
  //合并means，得到类别
  elements_class.resize(N, -1);
  int max_class = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i - 1; j >= 0; --j) {
      if (distance_2d(elements_mean[i], elements_mean[j]) < r) {
        elements_class[i] = elements_class[j];
        break;
      }
    }
    if (elements_class[i] == -1) {
      elements_class[i] = max_class;
      ++max_class;
    }
  }
  return max_class;
}

inline
double
distance_2d(const Eigen::Vector3d &l, const Eigen::Vector3d &r) {
  //输入数据为在同一个平面上的3D点
  double dx = l.x() - r.x(), dy = l.y() - r.y(), dz = l.z() - r.z();
  return dx*dx + dy*dy + dz*dz;
}

int
mean_shift_2d(std::vector<int> &elements_class,
              std::vector<Eigen::Vector3d > &elements_mean,
              const std::vector<Eigen::Vector3d > &elements,
              double r, double eps) {
  //改进的MeanShift算法
  //使用L2距离的平方，输入数据为在同一个平面上的3D点
  r = r*r;
  eps = eps*eps;
  const size_t N = elements.size();
  elements_mean = elements;
  std::vector<Eigen::Vector3d > new_means(N);
  std::vector<double> delta_distance(N);
  std::vector<double> radius(N, r);
  do {
    //更新new_means
    for (size_t i = 0; i < N; ++i) {
      Eigen::Vector3d near_element_sum{0, 0, 0};
      size_t near_element_count = 0;
      for (size_t j = 0; j < N; ++j) {
        if (distance_2d(elements_mean[i], elements_mean[j]) < radius[i]) {
          near_element_sum += elements_mean[j];
          ++near_element_count;
        }
      }//计算和 i 相邻的元素个数和它们的均值
      if (near_element_count > 1) {//最近元素包含自己
        if (radius[i] > r && delta_distance[i] > eps) {
          //如果上一次移动了，则复原原来的搜索半径
          radius[i] *= 0.5;
        }
        Eigen::Vector3d new_mean =
          near_element_sum / (double) near_element_count;
        delta_distance[i] = distance_2d(new_mean, elements_mean[i]);
        new_means[i] = new_mean;
      } else {
        //如果找不到相邻的元素，将当前元素 i 对应的半径扩大一倍
        radius[i] *= 2;
        delta_distance[i] = 0;
        new_means[i] = elements_mean[i];
      }
    }//新均值中心计算完毕
    elements_mean.swap(new_means);
  } while ( !all_less(delta_distance, eps) );
  //合并means，得到类别
  elements_class.resize(N, -1);
  int max_class = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i - 1; j >= 0; --j) {
      if (distance_2d(elements_mean[i], elements_mean[j]) < r) {
        elements_class[i] = elements_class[j];
        break;
      }
    }
    if (elements_class[i] == -1) {
      elements_class[i] = max_class;
      ++max_class;
    }
  }
  return max_class;
}