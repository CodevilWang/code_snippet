// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <stdio.h>
#include <string>
#include <random>
#include <unordered_map>
#include <sstream>
class RandomStrGen {
    public:
        RandomStrGen(size_t str_len = 10, const std::unordered_map<int, char>* cm = &CHAR_MAP) :
            _str_len(str_len), _mt((std::random_device())()), _char_map(cm) {
        }
        ~RandomStrGen() {}
        std::string next() {
            std::uniform_int_distribution<int> dist(0, _char_map->size() - 1);
            std::ostringstream oss;
            for (size_t i = 0; i < _str_len; ++i) {
                oss << (*_char_map).at(dist(_mt));
            }
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

int main() {
    RandomStrGen rsg;
    for (int i = 0 ; i < 10; ++i) {
        printf("%s\n", rsg.next().c_str());
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
