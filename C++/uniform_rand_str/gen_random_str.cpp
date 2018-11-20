// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <random>
#include <unordered_map>
#include <sstream>
static const uint32_t STR_NUM = 1000000;
static const uint32_t STR_LEN = 100;
class RandomStrGen {
    public:
        RandomStrGen(size_t str_len = STR_LEN, const std::unordered_map<int, char>* cm = &CHAR_MAP) :
            _str_len(str_len), _mt((std::random_device())()), _char_map(cm) {
        }
        ~RandomStrGen() {}
        std::string next() {
            std::uniform_int_distribution<int> dist(0, _char_map->size() - 1);
            std::ostringstream oss;
            for (size_t i = 0; i < _str_len; ++i) {
                oss << (*_char_map).at(dist(_mt));
            }
            oss << '\n';
            return oss.str();
        }
        static std::unordered_map<int, char> CHAR_MAP;
        static class _default_map_initer {
            public:
                _default_map_initer() {
                    for (char i = 'a'; i <= 'z' ; ++i) {
                        CHAR_MAP[ i - 'a' ] = i;
                    }
                    for (char i = 'A'; i <= 'Z' ; ++i) {
                        CHAR_MAP[ i - 'A' + 'z' - 'a' + 1 ] = i;
                    }
                }
        } _dmi;
    private:
        std::mt19937 _mt;
        size_t _str_len;
        const std::unordered_map<int, char>* _char_map;
};
std::unordered_map<int, char> RandomStrGen::CHAR_MAP;
RandomStrGen::_default_map_initer RandomStrGen::_dmi;

int main(int argc, char** argv) {
    RandomStrGen rsg;
    int fd = 1;
    if (argc > 1) {
        fd = open(argv[1], O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);
    }
    for (int i = 0 ; i < STR_NUM; ++i) {
        std::string rand_str = rsg.next();
        write(fd, rand_str.c_str(), rand_str.length());
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
