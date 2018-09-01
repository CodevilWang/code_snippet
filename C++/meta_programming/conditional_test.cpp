// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <stdio.h>
#include <vector>
int main() {
    printf("%zu\n", sizeof(void*));
    static const std::uint64_t default_buffer_size =
        std::conditional<sizeof(void*) == 8,
        std::integral_constant<uint64_t, 1024lu * 1024 * 1024 * 1024 * 1024>,
        std::integral_constant<uint64_t, 1024 * 1024 * 1024>>::type::value;
    printf("%llu\n", default_buffer_size);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
