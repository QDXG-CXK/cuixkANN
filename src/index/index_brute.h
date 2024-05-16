#include <iostream>
#include <faiss/IndexFlat.h>

#include "index.h"

template <typename T>
class Brute : public ANN<T> {
public:
    using ANN<T>::dim_; //让构造函数知道父类成员的存在
    Brute(const int dim) : ANN<T>(dim), index_(dim) { };
    ~Brute() {};
    void build(const size_t nb, const T *xb) final;
    void search(const size_t nq, const T *xq, const size_t K, T *D, idx_t *I) final;
private:
    faiss::IndexFlatL2 index_;
};

template<typename T>
void Brute<T>::build(const size_t nb, const T *xb){
    std::cout<<"brute->build(size_t nb, T *xb)\n"; //debug
    index_.add(nb, xb);
}


template<typename T>
void Brute<T>::search(const size_t nq, const T *xq, const size_t k, T *D, idx_t *I){
    std::cout<<"brute->search(const size_t nq, const T *xq, const size_t k, T *D, faiss::idx_t *I)\n"; //debug
    index_.search(nq, xq, k, D, I);
}