#ifndef FILES_2_Q_H_
#define FILES_2_Q_H_

#include <vector>

enum class ErrorCode {
  kNoError = 0,
  kPopFromEmptyVector,
  kIndexError,
  kNotFound,
};

class MyVector {
 public:
  MyVector();
  explicit MyVector(int size);
  MyVector(const MyVector& rhs);
  ~MyVector();

  void push_back(int value);
  int pop_back();

  void push_front(int value);
  int pop_front();

  // Inserts value after the element at ``index``.  Passing ``-1`` inserts at
  // the front of the vector.  Out-of-range indices leave the vector unchanged
  // and set the error code to ``ErrorCode::kIndexError``.
  void insert(int value, int index);

  // Returns the element at ``index``.  An out-of-range index sets the error
  // code to ``ErrorCode::kIndexError`` and returns -1.
  int at(int index);

  // Returns the index of ``item`` or -1 if the item does not exist.  On
  // failure the error code is set to ``ErrorCode::kNotFound``.
  int find(int item);

  ErrorCode get_error() const;
  int size() const;

  std::vector<int> ConvertToStdVector();

 private:
  int* data_;
  int size_;
  ErrorCode error_;
};

#endif  // FILES_2_Q_H_
