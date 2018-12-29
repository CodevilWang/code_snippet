// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
static const size_t framebit = 5;
void assign(uint32_t* out, uint32_t* out_bit_len, uint32_t value, const uint32_t& assign_bit_size) {
    uint32_t cur_uint32_cursor = (*out_bit_len) / 32;
    uint32_t left_bit = ((*out_bit_len) % 32) == 0 ? 0 : (32 - (*out_bit_len) % 32);
    if (left_bit >= assign_bit_size) {
        out[cur_uint32_cursor] |= (value << (left_bit - assign_bit_size));
        *out_bit_len += assign_bit_size;
    } else {
        assign(out, out_bit_len, value >> (assign_bit_size - left_bit), left_bit);
        assign(out, out_bit_len, value & ((1 << (assign_bit_size - left_bit)) - 1), assign_bit_size - left_bit);
    }
}
int compress(uint32_t* data, const size_t& data_len, uint32_t* out, uint32_t* out_bit_len) {
    uint32_t cursor = 0;
    *out_bit_len = 5;
    uint32_t out_corsor = 0;
    std::vector<uint32_t> exs;
    uint32_t* ex_cursor = 0;
    uint32_t last_ex_pos = 0;
    for (uint32_t i = 0; i < data_len; ++i) {
        if (data[i] < (1 << framebit)) {
            assign(out, out_bit_len, data[i], framebit);
        } else {
            exs.push_back(data[i]);
            assign(out, ex_cursor, i - last_ex_pos, framebit);
            last_ex_pos = i;
            ex_cursor = out_bit_len;
            *out_bit_len += framebit;
        }
    }
    for (int i = 0; i < exs.size(); ++i) {
        assign(out, out_bit_len, exs[i], 32);
    }
    return 0;
}

// int uncompress(const uint32_t* compressed, const size_t& bit_len) {
// 
// }

int main() {
    srand(time(NULL));
    static const uint32_t data_len = 128;
    uint32_t* data = new uint32_t(data_len);
    for (uint32_t i = 0; i < data_len; ++i) {
        if (rand() % 100 < 10) {
            data[i] = rand() % 100;
        }
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
