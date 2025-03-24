//
// Created by 19254 on 25-3-17.
//

#ifndef LVGLEX_MISC_MATRIX_H
#define LVGLEX_MISC_MATRIX_H

#include <LVGLEx/obj_pointer.h>
#include <memory>
#include <misc/lv_matrix.h>

namespace LVGLEx {

class Matrix {
private:
  struct MatrixPointerDeleter {
    void operator()(lv_matrix_t *ptr) const;
  };
  typedef PointerPack<lv_matrix_t, MatrixPointerDeleter> MatrixPointer;
  MatrixPointer m_matrix;

public:

  Matrix();
  Matrix(const lv_matrix_t *matrix);
  Matrix(const lv_matrix_t &matrix);
  Matrix(const Matrix &);
  ~Matrix();

  Matrix &operator=(const Matrix &);

  const lv_matrix_t *get() const;
  lv_matrix_t *getPtr() const;


  /**
   * @brief 设置为单位矩阵
   */
  Matrix& identity();

  /**
   * @brief 将矩阵平移到新的位置
   * @param dx x平移量
   * @param dy y平移量
   */
  Matrix& translate(float dx, float dy);

  /**
   * @brief 修改矩阵缩放因子
   * @param scale_x x缩放量
   * @param scale_y y缩放量
   */
  Matrix& scale(float scale_x, float scale_y);

  /**
   * @brief 旋转矩阵
   * @param degree 旋转角度
   */
  Matrix& rotate(float degree);

  /**
   * @brief 倾斜矩阵
   * @param skew_x x倾斜量
   * @param skew_y y倾斜量
   */
  Matrix& skew(float skew_x, float skew_y);

  /**
   * @brief 将自身与另一个矩阵相乘并将结果存储到自身。
   * @param mul 乘数矩阵
   */
  Matrix& multiply(const lv_matrix_t *mul);

  /**
   * @brief 计算矩阵的逆矩阵
   *
   * 此函数用于计算给定矩阵的逆矩阵。如果矩阵是可逆的，则返回true；如果矩阵是奇异的，无法求逆，则返回false。
   *
   * @param m     指向另一个矩阵的指针（可选）
   * @return true: 如果矩阵是可逆的；false: 如果矩阵是奇异的，无法求逆
   */
  bool inverse(const lv_matrix_t *m) const;

  /**
   *  @brief 使用矩阵变换一个精确点
   *
   * 根据给定的矩阵对一个精确点进行变换。
   *
   * @param point  指向一个精确点的指针
   * @return 返回变换后的精确点
   *
   */
  lv_point_precise_t
  transformPrecisePoint(const lv_point_precise_t *point) const;

  /**
   * @brief 通过矩阵变换区域
   *
   * @param area   指向一个区域的指针
   * @return 返回变换后的区域
   */
  lv_area_t transformArea(const lv_area_t *area) const;

  /**
   * @brief 检查矩阵是否为单位矩阵或平移矩阵
   *
   * 判断给定的矩阵是否为单位矩阵或平移矩阵。
   *
   * @return true 如果矩阵是单位矩阵或平移矩阵；否则返回 false
   */
  bool isIdentityOrTranslation() const;
};

} // namespace LVGLEx

#endif // LVGLEX_MISC_MATRIX_H
