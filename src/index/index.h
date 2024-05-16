#pragma once

using idx_t = long int;

template <typename T>
class ANN {
public:
    ANN(int dim) : dim_(dim) {}
    virtual ~ANN() = default;
    virtual void build(const size_t nb, const T *xb) = 0;
    virtual void search(const size_t nq, const T *xq, const size_t K, T *D, idx_t *I) = 0;
protected:
    int dim_;
};