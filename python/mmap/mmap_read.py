import os
import mmap

sample_str = "Hello, world"
print len(sample_str)
map = mmap.mmap(-1, 13)
map.write(sample_str)

pid = os.fork()
if pid == 0:
    map.seek(0)
    print(map.readline())
    map.close()
