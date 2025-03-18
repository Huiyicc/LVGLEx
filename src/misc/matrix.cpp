//
// Created by 19254 on 25-3-17.
//
#include <LVGLEx/misc/matrix.h>

namespace LVGLEx {

Matrix::~Matrix() {}
Matrix::Matrix() { m_matrix = lv_matrix_t{}; }
Matrix::Matrix(const lv_matrix_t *matrix) { m_matrix = *matrix; }
Matrix::Matrix(const lv_matrix_t &matrix) { m_matrix = matrix; }

Matrix::Matrix(const Matrix &matrix) : m_matrix{} {
  m_matrix = matrix.m_matrix;
};

const lv_matrix_t *Matrix::get() const { return &m_matrix; };
lv_matrix_t *Matrix::getPtr() { return &m_matrix; };

Matrix &Matrix::identity() {
  lv_matrix_identity(&m_matrix);
  return *this;
}

Matrix &Matrix::translate(float dx, float dy) {
  lv_matrix_translate(&m_matrix, dx, dy);
  return *this;
}

Matrix &Matrix::scale(float scale_x, float scale_y) {
  lv_matrix_scale(&m_matrix, scale_x, scale_y);
  return *this;
}

Matrix &Matrix::rotate(float degree) {
  lv_matrix_rotate(&m_matrix, degree);
  return *this;
}

Matrix &Matrix::skew(float skew_x, float skew_y) {
  lv_matrix_skew(&m_matrix, skew_x, skew_y);
  return *this;
}

Matrix &Matrix::multiply(const lv_matrix_t *mul) {
  lv_matrix_multiply(&m_matrix, mul);
  return *this;
}

bool Matrix::inverse(const lv_matrix_t *m) {
  return lv_matrix_inverse(&m_matrix, m);
}

lv_point_precise_t
Matrix::transformPrecisePoint(const lv_point_precise_t *point) {
  return lv_matrix_transform_precise_point(&m_matrix, point);
}

lv_area_t Matrix::transformArea(const lv_area_t *area) {
  return lv_matrix_transform_area(&m_matrix, area);
}

bool Matrix::isIdentityOrTranslation() {
  return lv_matrix_is_identity_or_translation(&m_matrix);
}

} // namespace LVGLEx