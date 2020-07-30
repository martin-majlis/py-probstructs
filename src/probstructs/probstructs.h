#include <cstdint>
#include <cassert>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <climits>
#include <cmath>
#include "MurmurHash3.h"

#ifndef ECM_SKETCH_ECM_SKETCH_H
#define ECM_SKETCH_ECM_SKETCH_H

// http://users.softnet.tuc.gr/~adeli/papers/journals/VLDBJ2015.pdf

#ifdef NDEBUG
#define DEBUG(x) 
#else
#define DEBUG(x) do { std::cerr << x << std::endl; } while (0)
#endif

class Hash {
private:
    uint32_t seed;

public:
    Hash(uint32_t seed) {
        this->seed = seed;
    }

    uint32_t hash(const std::string &key) {
        uint32_t res = 0;
        MurmurHash3_x86_32(key.c_str(), key.length(), seed, &res);
        return res;
    }
};


const int MAX_HASH_NUM = 24;

template<class T>
class CountMinSketch {
private:
    uint32_t width = 0;
    uint8_t depth = 0;
    T *counter[MAX_HASH_NUM] = { nullptr };
    Hash * hash[MAX_HASH_NUM] = { nullptr };

    uint32_t index(const std::string &key, int l) {
        return hash[l]->hash(key) % width;
    }

public:
    CountMinSketch(uint32_t width, uint8_t depth) {
        assert(depth < MAX_HASH_NUM);

        this->depth = depth;
        this->width = width;

        for(int i = 0; i < depth; i++)
        {
            counter[i] = new T[width];
            std::memset(counter[i], 0, sizeof(T) * width);

            hash[i] = new Hash(i);
        }
    }

    ~CountMinSketch()
    {
        for(int i = 0; i < depth; i++)
        {
            delete []counter[i];
            delete hash[i];
        }
    }

    void inc(const std::string &key, T delta) {
        for(int i = 0; i < depth; i++)
        {
            counter[i][index(key, i)] += delta;
        }
    }

    T get(const std::string &key) {
        T res = INT_MAX;
        for(int i = 0; i < depth; i++)
        {
            res = std::min(res, counter[i][index(key, i)]);
        }
        return res;
    }
};

// !!! TODO: https://stackoverflow.com/a/255744
template <class T>
class ExponentialHistorgram {

private:
    float* counts = nullptr;
    uint32_t size = 0;
    uint32_t last_tick = 0;
    float total = 0;

    uint32_t window_size(uint32_t bucket) {
        if (bucket <= 1) {
            return 1;
        } else {
            return 1 << (bucket - 1);
        }
    }

public:
    ExponentialHistorgram(): counts(nullptr), size(0) {}
    ExponentialHistorgram(uint32_t window) {
        size = std::log2(window) + 1;
        DEBUG("Window: " << window << "; Size: " << size);

        counts = new float[size];
        std::memset(counts, 0, sizeof(T) * size);
    }

    ~ExponentialHistorgram() {
        delete []counts;
    }

    // Copy constructor needs more work
    ExponentialHistorgram(ExponentialHistorgram const& copy)
    {
        counts = new float[copy.size];
        size = copy.size;
        last_tick = copy.last_tick;
        total = copy.total;

        std::copy(&copy.counts[0],&copy.counts[copy.size], size);

    }

    ExponentialHistorgram& operator=(ExponentialHistorgram rhs)
    {
        rhs.swap(*this); // Now swap data with the copy.
        // The rhs parameter will delete the array when it
        // goes out of scope at the end of the function
        return *this;
    }

    void swap(ExponentialHistorgram& s) noexcept
    {
        using std::swap;
        swap(this->counts,s.counts);
        swap(this->size, s.size);
        swap(this->last_tick, s.last_tick);
        swap(this->total, s.total);
    }

    // C++11
    ExponentialHistorgram(ExponentialHistorgram&& src) noexcept
    : counts(nullptr)
    , size(0)
    , last_tick(0)
    , total(0)
    {
        src.swap(*this);
    }
/*
    ExponentialHistorgram& operator=(ExponentialHistorgram&& src) noexcept
    {
        src.swap(*this);     // You are moving the state of the src object
        // into this one. The state of the src object
        // after the move must be valid but indeterminate.
        //
        // The easiest way to do this is to swap the states
        // of the two objects.
        //
        // Note: Doing any operation on src after a move
        // is risky (apart from destroy) until you put it
        // into a specific state. Your object should have
        // appropriate methods for this.
        //
        // Example: Assignment (operator = should work).
        //          std::vector() has clear() which sets
        //          a specific state without needing to
        //          know the current state.
        return *this;
    }
*/

    void inc(uint32_t tick, T delta) {
        DEBUG("INC - TS: " << last_tick << "; T: " << tick << "; D: " << delta);

        uint32_t tick_diff = tick - last_tick;

        if (tick_diff != 0) {
            // we have to move stuff around
            float diff = 0;

            uint b = size - 1;
            while ( b >= 0 ) {
                uint w = window_size(b);
                // figure out how much stuff should be moved
                if (tick_diff >= w) {
                    diff = counts[b];
                } else {
                    diff = counts[b] * (float(tick_diff) / w);
                }

                DEBUG("B: " << b << "; W: " << w << "; Diff: " << diff);

                // remove it from the current bucket
                counts[b] -= diff;

                // move it to the proper next bucket
                // TODO: implement properly
                uint32_t next_b = b + 1;
                uint32_t wd = 0;
                while (next_b < size) {
                    wd += window_size(next_b);
                    if (wd >= tick_diff) {
                        break;
                    } else {
                        next_b += 1;
                    }
                }
                DEBUG("TD: " << tick_diff << "; B: " << b << "; NextB: " << next_b);

                if (next_b < size) {
                    counts[next_b] += diff;
                } else {
                    total -= diff;
                }
                if (b == 0) {
                    break;
                } else {
                    b--;
                }
            }
        }

        counts[0] += delta;
        total += delta;

        last_tick = tick;
        DEBUG("INC - TS: " << last_tick << "; Total: " << total);
    }

    T get(uint32_t window, uint32_t tick) {
        DEBUG("GET - TS: " << last_tick << "; T: " << tick << "; W: " << window);

        DEBUG("Total - BEF: " << total);

        // TODO: This only works if T in integer => it is not good idea?
        // if there is nothing, there is no need to compute anything
        if (total == 0) {
            return 0;
        }

        // increase by 0 to trigger bucket merging
        inc(tick, 0);


        DEBUG("Total - AFT: " << total);

        // if there is nothing, there is no need to compute anything
        if (total == 0) {
            return 0;
        }


        float res = 0;
        uint32_t b = 0;
        while ( b < size && window > 0) {
            uint w = window_size(b);
            if (window >= w) {
                res += counts[b];
                window -= w;
            } else {
                res += counts[b] * (float(window) / w);
                window = 0;
            }
            DEBUG("B: " << b << "; W: " << w << "; RemW: " << window << "; Res: " << res);
            b++;
        }

        DEBUG("GET - TS: " << last_tick << "; T: " << tick << "; W: " << window << "; Result: " << res);
        return std::ceil(res);
    }
};

template<class T>
class ExponentialCountMinSketch
{
private:
    uint32_t width;
    uint8_t depth;
    ExponentialHistorgram<T> *counter[MAX_HASH_NUM];
    Hash * hash[MAX_HASH_NUM];

    uint32_t index(const std::string &key, int l) {
        return hash[l]->hash(key) % width;
    }

public:
    ExponentialCountMinSketch(uint32_t width, uint8_t depth, uint32_t window) {
        assert(depth < MAX_HASH_NUM);

        this->depth = depth;
        this->width = width;

        for(int i = 0; i < depth; i++)
        {
            counter[i] = new ExponentialHistorgram<T>[width];
            for (uint j = 0; j < width; ++j) {
                counter[i][j] = ExponentialHistorgram<T>(window);
            }
            hash[i] = new Hash(i);
        }
    }

    ~ExponentialCountMinSketch() {
        for (int i = 0; i < depth; i++) {
            delete[]counter[i];
            delete hash[i];
        }
    }

    void inc(const std::string &key, uint32_t tick, T delta) {
        for(int i = 0; i < depth; i++)
        {
            counter[i][index(key, i)].inc(tick, delta);
        }
    }

    T get(const std::string &key, uint32_t window, uint32_t tick) {
        T res = INT_MAX;
        for(int i = 0; i < depth; i++)
        {
            res = std::min(res, counter[i][index(key, i)].get(window, tick));
        }
        return res;
    }
};

#endif //ECM_SKETCH_SKETCH_H
