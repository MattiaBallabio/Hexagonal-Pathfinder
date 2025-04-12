#ifndef SAMPLER_H
#define SAMPLER_H

#include <cstdint>
#include <stdexcept>

using namespace std;

class Sampler {

    public:
        explicit Sampler(uint32_t n);
        ~Sampler();
        uint32_t getSample();

    private:
        uint32_t* elements;
        uint32_t n;
};

#endif