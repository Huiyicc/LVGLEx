//
// Created by 19254 on 25-3-17.
//
#include <LVGLEx/misc/matrix.h>

namespace LVGLEx {

void Matrix::MatrixPointerDeleter::operator()(lv_matrix_t *ptr) const {
  if (ptr) {
    delete ptr;
  }
}

Matrix::Matrix() : m_matrix(new lv_matrix_t) {};
Matrix::Matrix(const lv_matrix_t &matrix) {
  m_matrix = MatrixPointer::makeQuote(&matrix);
};
Matrix::Matrix(const lv_matrix_t *matrix) {
  m_matrix = MatrixPointer::makeQuote(matrix);
};
Matrix::Matrix(const Matrix &matrix) {
  m_matrix = MatrixPointer::makePrivatePtr(new lv_matrix_t{0});
  *m_matrix = *matrix.m_matrix;
};

Matrix::~Matrix() =default;
Matrix &Matrix::operator=(const Matrix &data) {
  m_matrix = MatrixPointer::makePrivatePtr(new lv_matrix_t{0});
  *m_matrix = *data.m_matrix;
  return *this;
};


const lv_matrix_t *Matrix::get() const { return m_matrix.get(); };
lv_matrix_t *Matrix::getPtr() const { return m_matrix.get(); };

Matrix &Matrix::identity() {
  lv_matrix_identity(m_matrix.get());
  return *this;
}

Matrix &Matrix::translate(float dx, float dy) {
  lv_matrix_translate(m_matrix.get(), dx, dy);
  return *this;
}

Matrix &Matrix::scale(float scale_x, float scale_y) {
  lv_matrix_scale(m_matrix.get(), scale_x, scale_y);
  return *this;
}

Matrix &Matrix::rotate(float degree) {
  lv_matrix_rotate(m_matrix.get(), degree);
  return *this;
}

Matrix &Matrix::skew(float skew_x, float skew_y) {
  lv_matrix_skew(m_matrix.get(), skew_x, skew_y);
  return *this;
}

Matrix &Matrix::multiply(const lv_matrix_t *mul) {
  lv_matrix_multiply(m_matrix.get(), mul);
  return *this;
}

bool Matrix::inverse(const lv_matrix_t *m) const {
  return lv_matrix_inverse(m_matrix.get(), m);
}

lv_point_precise_t
Matrix::transformPrecisePoint(const lv_point_precise_t *point) const {
  return lv_matrix_transform_precise_point(m_matrix.get(), point);
}

lv_area_t Matrix::transformArea(const lv_area_t *area) const {
  return lv_matrix_transform_area(m_matrix.get(), area);
}

bool Matrix::isIdentityOrTranslation() const {
  return lv_matrix_is_identity_or_translation(m_matrix.get());
}

} // namespace LVGLEx