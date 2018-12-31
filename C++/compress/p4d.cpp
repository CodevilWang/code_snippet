// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
int compress(const uint32_t* data, const uint32_t& data_len, uint32_t* out, uint32_t* out_bit_len) {
    uint32_t cursor = 0;
    *out_bit_len = framebit;
    uint32_t out_corsor = 0;
    std::vector<uint32_t> exs;
    uint32_t ex_cursor = 0;
    uint32_t last_ex_pos = 0;
    for (uint32_t i = 0; i < data_len; ++i) {
        if (data[i] < (1 << framebit)) {
            assign(out, out_bit_len, data[i], framebit);
        } else {
            exs.push_back(data[i]);
            assign(out, &ex_cursor, i - last_ex_pos, framebit);
            last_ex_pos = i;
            ex_cursor = *out_bit_len;
            *out_bit_len += framebit;
        }
    }
    for (int i = exs.size() - 1; i >= 0; --i) {
        assign(out, out_bit_len, exs[i], 32);
    }
    return 0;
}

void get_value(const uint32_t* compressed, const uint32_t& start_bit, const uint32_t& bit_len, uint32_t* out) {
    *out = 0;
    // same uint32_t
    if (start_bit / 32 == (start_bit + bit_len) / 32) {
        uint32_t value = compressed[start_bit / 32];
        (*out) |= ((value >> (32 - (start_bit + bit_len) % 32)) & ((1 << bit_len) - 1));
    } else {
        uint32_t out_a = 0;
        uint32_t first_len = bit_len - (start_bit + bit_len) % 32;
        get_value(compressed, start_bit, first_len, &out_a);
        uint32_t out_b = 0;
        get_value(compressed, start_bit + first_len, bit_len - first_len, &out_b);
        *out = (out_a << (bit_len - first_len)) | out_b; 
    }
}

int uncompress(const uint32_t* compressed, const uint32_t& bit_len, const uint32_t& init_len, std::vector<uint32_t>* out) {
    const uint32_t all_ex_cnt =  (bit_len - init_len * framebit) / 32;
    uint32_t ex_cnt = all_ex_cnt; 
    uint32_t last_ex_cursor = std::numeric_limits<uint32_t>::max();
    if (all_ex_cnt > 0) {
        get_value(compressed, 0, framebit, &last_ex_cursor);
    }
    uint32_t start_bit = framebit;
    for (uint32_t ex_cursor = 0; ex_cursor < bit_len - ex_cnt * 32; ++ex_cursor) {
        uint32_t value = 0;
        if (ex_cursor == last_ex_cursor && ex_cnt > 0) {
            get_value(compressed, start_bit + ex_cursor * framebit, framebit, &last_ex_cursor);
            get_value(compressed, bit_len - (all_ex_cnt - ex_cnt + 1) * 32, 32, &value);
            out->push_back(value);
            --ex_cnt;
        } else {
            get_value(compressed, start_bit + ex_cursor * framebit, framebit, &value);
            out->push_back(value);
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));
    static const uint32_t data_len = 128;
    uint32_t* data = new uint32_t(data_len);
    for (uint32_t i = 0; i < data_len; ++i) {
        if (i % 32 == 0) {
            data[i] = rand() % 32 + 32;
        } else if (rand() % 100 < 10) {
            data[i] = rand() % 100;
        } else {
            data[i] = rand() % 32;
        }
    }
    printf("before compress\n");
    for (uint32_t i = 0; i < data_len; ++i) {
        printf("%u", data[i]);
        if (i != data_len - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
    uint32_t* output = new uint32_t(128);
    uint32_t out_bit_len = 0;
    compress(data, data_len, output, &out_bit_len);
    std::vector<uint32_t> after_compress;
    uncompress(output, out_bit_len, data_len, &after_compress);
    printf("after compress\n");
    printf("compressed %u bits. ratio %f", out_bit_len, out_bit_len * 1.0 / (32 * data_len));
    assert(after_compress.size() == data_len);
    for (uint32_t i = 0; i < after_compress.size(); ++i) {
        assert(after_compress[i] == data[i]);
        printf("%u", after_compress[i]);
        if (i != after_compress.size() - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
