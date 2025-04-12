#include "sampler.h"
#include <random>

using namespace std;

Sampler::Sampler(uint32_t num){
    n = num;
    elements = new uint32_t[n];
    for(uint32_t i = 0; i < n; i++){
        elements[i] = i;
    }
}

Sampler::~Sampler() {
    delete[] elements;
}

uint32_t Sampler::getSample() {
    if(n == 0) {
        throw underflow_error("No more elements to sample");
    }

    static random_device rd;
    static mt19937 mt(rd());
    uniform_int_distribution<uint32_t> dist(0, n - 1);
    uint32_t i = dist(mt);      
    
    uint32_t selected = elements[i];
    n--;
    elements[i] = elements[n];

    return selected;
}