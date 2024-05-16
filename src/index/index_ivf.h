#include <iostream>

#include "index.h"

template<typename T>
class Ivf : public ANN<T> {
public:
    Ivf(const int dim) : ANN<T>(dim) { };
    ~Ivf() {};
    void build(const size_t nb, const T *xb) final;
    void search(const size_t nq, const T *xq, const size_t K, T *D, idx_t *I) final;
private:
    //faiss::IndexIVF?? index_;//TODO:
};

template<typename T>
void Ivf<T>::build(const size_t nb, const T *xb){
    std::cout<<"ivf->build(const size_t nb, const T *xb)\n";//debug
}


template<typename T>
void Ivf<T>::search(const size_t nq, const T *xq, const size_t k, T *D, idx_t *I){
    std::cout<<"brute->search(const size_t nq, const T *xq, const size_t k, T *D, faiss::idx_t *I)\n"; //debug
    //index_.search(nq, xq, k, D, I);
}