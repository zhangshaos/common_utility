#ifndef COMMON_UTILITY_EXT_DISJOINT_SET_H
#define COMMON_UTILITY_EXT_DISJOINT_SET_H

#include <unordered_map>

//（不连续ID的）并查集
template<typename T>
struct ExtDisjointSet {
  std::unordered_map<T,T> parent;//parent[i] 表示类别i的父类别

  void
  reserve(size_t n){
    parent.reserve( n );
  }
  bool
  contain_class(const T &c)const{
    return parent.count( c );
  }
  const T&
  find_root_class(const T &c)const{
    T result;
    if (contain_class(c)) {
      result = c;
      while (result != parent.at(result))
        result = parent.at(result);
    }
    return result;
  }
  bool
  is_root_class(const T &c)const{
    return contain_class(c) && find_root_class(c) == c;
  }
  bool
  try_add_class(const T &c){
    if (!contain_class(c)) {
      parent[c] = c;
      return true;
    } else {
      // this ID is existed.
      return false;
    }
  }
  void
  union_class(const T &c1, const T &c2){
    try_add_class(c1);
    try_add_class(c2);
    const auto &new_par = find_root_class(c1);
    parent.at(find_root_class(c2)) = new_par;
    //make find path shorter
    parent.at(c1) = new_par;
    parent.at(c2) = new_par;
  }
  void
  shorten_find_path(){
    for(auto &[k, v] : parent) {
      v = find_root_class(k);
    }
  }
};

#endif //COMMON_UTILITY_EXT_DISJOINT_SET_H
