#include "files/2/q.h"

#include <algorithm>

MyVector::MyVector() : data_(nullptr), size_(0), error_(ErrorCode::kNoError) {}

MyVector::MyVector(int size)
    : data_(nullptr), size_(0), error_(ErrorCode::kNoError) {
  if (size <= 0) {
    return;
  }
  size_ = size;
  data_ = new int[size_];
  for (int i = 0; i < size_; ++i) {
    data_[i] = 0;
  }
}

MyVector::MyVector(const MyVector& rhs)
    : data_(nullptr), size_(rhs.size_), error_(rhs.error_) {
  if (size_ == 0) {
    return;
  }
  data_ = new int[size_];
  for (int i = 0; i < size_; ++i) {
    data_[i] = rhs.data_[i];
  }
}

MyVector::~MyVector() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  error_ = ErrorCode::kNoError;
}

void MyVector::push_back(int value) {
  int* new_data = new int[size_ + 1];
  for (int i = 0; i < size_; ++i) {
    new_data[i] = data_[i];
  }
  new_data[size_] = value;
  delete[] data_;
  data_ = new_data;
  ++size_;
  error_ = ErrorCode::kNoError;
}

int MyVector::pop_back() {
  if (size_ == 0) {
    error_ = ErrorCode::kPopFromEmptyVector;
    return 0;
  }

  int result = data_[size_ - 1];
  if (size_ == 1) {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
  } else {
    int* new_data = new int[size_ - 1];
    for (int i = 0; i < size_ - 1; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    --size_;
  }
  error_ = ErrorCode::kNoError;
  return result;
}

void MyVector::push_front(int value) {
  int* new_data = new int[size_ + 1];
  new_data[0] = value;
  for (int i = 0; i < size_; ++i) {
    new_data[i + 1] = data_[i];
  }
  delete[] data_;
  data_ = new_data;
  ++size_;
  error_ = ErrorCode::kNoError;
}

int MyVector::pop_front() {
  if (size_ == 0) {
    error_ = ErrorCode::kPopFromEmptyVector;
    return 0;
  }

  int result = data_[0];
  if (size_ == 1) {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
  } else {
    int* new_data = new int[size_ - 1];
    for (int i = 1; i < size_; ++i) {
      new_data[i - 1] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    --size_;
  }
  error_ = ErrorCode::kNoError;
  return result;
}

void MyVector::insert(int value, int index) {
  if (index < -1 || index >= size_) {
    error_ = ErrorCode::kIndexError;
    return;
  }

  const int insert_pos = index + 1;
  int* new_data = new int[size_ + 1];
  for (int i = 0; i < insert_pos; ++i) {
    new_data[i] = data_ ? data_[i] : 0;
  }
  new_data[insert_pos] = value;
  for (int i = insert_pos; i < size_; ++i) {
    new_data[i + 1] = data_[i];
  }

  delete[] data_;
  data_ = new_data;
  ++size_;
  error_ = ErrorCode::kNoError;
}

int MyVector::at(int index) {
  if (index < 0 || index >= size_) {
    error_ = ErrorCode::kIndexError;
    return -1;
  }
  error_ = ErrorCode::kNoError;
  return data_[index];
}

int MyVector::find(int item) {
  for (int i = 0; i < size_; ++i) {
    if (data_[i] == item) {
      error_ = ErrorCode::kNoError;
      return i;
    }
  }
  error_ = ErrorCode::kNotFound;
  return -1;
}

ErrorCode MyVector::get_error() const { return error_; }

int MyVector::size() const { return size_; }

std::vector<int> MyVector::ConvertToStdVector() {
  std::vector<int> result;
  result.reserve(size_);
  for (int i = 0; i < size_; ++i) {
    result.push_back(data_[i]);
  }
  error_ = ErrorCode::kNoError;
  return result;
}
