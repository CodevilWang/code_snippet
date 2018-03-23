#!/usr/bin/env python
import time
import functools
class Timer(object):
    def __init__(self, func, args_dict, obj = None, interval_name = None):
        self.func = func 
        self.args_dict = args_dict
        self.interval_name = interval_name 
        self.__start = 0
        self.obj = obj

    def __enter__(self):
        self.__start = time.time()

    def __exit__(self, *args):
        end = time.time() 
        interval = end - self.__start
        if self.interval_name:
            self.args_dict[self.interval_name] = interval
        if self.obj:
            self.func(self.obj, **self.args_dict)
        else:
            self.func(**self.args_dict)

class Record(object):
    def record(self, interval):
        with open("default.fn", "w") as f:
            f.write(str(interval))

with Timer(Record.record, {}, Record(), interval_name = "interval") as t:
    print "starting"
    time.sleep(3)
    print "ending"
