#include "utils.h"
#include "dataset.h"
#include "test/test.h"
#include "myLib/myLib.h"
#include "index/index.h"
#include "index/index_ivf.h"
#include "index/index_brute.h"

#include <argparse/argparse.hpp>

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <cassert>


typedef float DTYPE;//TODO: get type from main argument.
using namespace std;


// void testAll(){
//     func();
//     func2();
//     func3();
//     cout<<"test\n";
// }

enum ALGO_NAME{
    brute, ivf,
    Unknown
};

ALGO_NAME parse_ALGO(argparse::ArgumentParser &program) {
    static const std::unordered_map<std::string, ALGO_NAME> algoMap = {
        {"brute", ALGO_NAME::brute},
        {"ivf", ALGO_NAME::ivf},
    };

    const string str = program.get<string>("algorithm");
    ALGO_NAME algo;
    auto it = algoMap.find(str);
    if (it != algoMap.end()) {
        algo =  it->second;
    } else {
        string message;
        stringstream ss = program.help();
        while(getline(ss, message)){
            if (message.find("choose an algorithm in") != string::npos){ break; }
        }
        if (!message.empty()) { cerr << message << endl; }   
        assert(0);
    }

    return algo;
}

void config_arguments(argparse::ArgumentParser &program, int argc, char* argv[]) {
    program.add_argument("command").help("{build, search, both}");
    program.add_argument("--algorithm", "-a").help("choose an algorithm in {brute, ivf}")
        .default_value("ivf");
    program.add_argument("--dataset", "-d").help("Path should be writen in conf/dataset_path.json.")
        .default_value("sift1m");
    program.add_argument("--conf_path").help("defaulte: ../conf/dataset_path.json.")
        .default_value("../conf/dataset_path.json");
    program.add_argument("--quantization", "-c").help("{none, pq, opq}")
        .default_value("none");
    program.add_argument("--norecall").help("Whether to calculate recall.")
        .flag();
    program.add_argument("--gpu").help("Whether to use gpu version.")
        .flag();

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        cerr << err.what() << endl;
        cerr << program;
        assert(0);
    }
}

template <typename T>
std::unique_ptr<ANN<T>> create_algo(const ALGO_NAME algo, const int dim){
    std::unique_ptr<ANN<T>> ann;
    switch(algo){
        case ALGO_NAME::brute:
            ann = std::make_unique<Brute<T>>(dim);
            break;
        case ALGO_NAME::ivf:
            ann = std::make_unique<Ivf<T>>(dim);
            break;
    }
    return ann;
}

int main(int argc, char* argv[]){
    argparse::ArgumentParser program("cuixkANN");
    config_arguments(program, argc, argv);

    std::unique_ptr<BinDataset<DTYPE>> dataset;
    load_dataset<DTYPE>(dataset, program.get<string>("dataset"), program.get<string>("conf_path"));
    cout << dataset->base_set_size() << endl << dataset->query_set_size() << endl << dataset->dim() << endl;//debug
    
    ALGO_NAME algo = parse_ALGO(program);
    const auto ann = create_algo<DTYPE>(algo, dataset->dim());
    
    string cmd = program.get<string>("command");
    if (cmd == "build" || cmd == "both") {
        dynamic_cast<Brute<DTYPE>*>(ann.get())->build(dataset->base_set_size(), dataset->base_set());

        if (cmd == "build"){
            //TODO save index to disk
        }
    }

    if (cmd == "search" || cmd == "both") {
        if (cmd == "search"){
            //TODO load index from disk
        }
        const size_t k = 2;
        idx_t *I = new idx_t[k * dataset->query_set_size()];
        DTYPE *D = new DTYPE[k * dataset->query_set_size()];
        ann->search(dataset->query_set_size(), 
                    dataset->query_set(), 
                    k, D, I);
        std::cout<<"NN Index: "<<I[0]<<","<<I[1]<<std::endl;
    }
    
    return 0;
}