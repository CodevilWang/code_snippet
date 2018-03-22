#!/usr/bin/env python
import sys
import time
class Timer(object):
    def __init__(self, type_value):
        self.fd = open("timer.out", "w")
        self.__start = None 
        self.__type = type_value
    def __enter__(self):
        print "in _enter__ func"
        self.__start = time.time()
    def __exit__(self, *args):
        end = time.time()
        self.fd.write("[{}] inter[{}]".format(self.__type, end - self.__start))

with Timer(1) as t:
    print "before sleep"
    time.sleep(3)
    print "after sleep"
