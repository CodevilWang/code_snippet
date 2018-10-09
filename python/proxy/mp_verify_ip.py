#!/usr/bin/env python
#encoding=utf8
import sys
import os
import requests
import config
import random
from multiprocessing import Process

class PInfo(object):
    def __init__(self, pid):
        self.__pid = pid
        self.std_fd = None
        self.err_fd = None
    def init(self):
        self.std_fd = open("mp_proxy.{}.out".format(self.__pid), "w", buffering = 0)
        self.err_fd = open("mp_proxy.{}.err".format(self.__pid), "w", buffering = 0)
        return True

def VerifyIp(pipport, test_url, timeout, user_agent_list, p_info):
    p_info.err_fd.write("verifying ip[{}]\n".format(pipport));
    proxies = {"http": "http://{}".format(pipport), "https": "https://{}".format(al.strip())}
    try:
        url_content = requests.get(test_url,
                          proxies=proxies,
                          timeout=timeout,
                          headers={
                              'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
                              'Accept-Encoding': 'gzip, deflate, compress',
                              'Accept-Language': 'zh-CN,zh;q=0.8,en;q=0.6,ru;q=0.4',
                              'Cache-Control': 'max-age=0',
                              'Connection': 'keep-alive',
                              'User-Agent': random.choice(user_agent_list),
                          })

        if int(url_content.status_code) == int(200):
            p_info.std_fd.write("{}\n".format(pipport))
        else:
            p_info.err_fd.write("invalid prox [{}]\n".format(pipport))
    except Exception as e:
        p_info.err_fd.write("catch unexcept ex[{}] verfying [{}]\n".format(e, pipport))

def VerifyIplist(pipport_list, test_url, timeout, user_agent_list, p_info):
    for ipp in pipport_list:
        VerifyIp(ipp, test_url, timeout, user_agent_list, p_info)
    p_info.std_fd.flush()
    p_info.err_fd.flush()

if __name__ == "__main__":
    ip_file_name = sys.argv[1]
    n_process = len(sys.argv) > 2 and int(sys.argv[2]) or 4
    ip_list = []
    with open(ip_file_name) as f:
        for al in f:
            ip_list.append(al.strip())
    process_list = []
    cursor = 0 
    interval = len(ip_list) / n_process
    for i in range(0, n_process):
        p_info = PInfo(i)
        p_info.init()
        end = (i == n_process - 1) and len(ip_list) or (cursor + interval)
        p = Process(target = VerifyIplist, args = (ip_list[cursor : end], \
                                               "https://www.baidu.com", \
                                               20, config.UserAgents, p_info))
        cursor = end
        process_list.append(p)
    for p in process_list:
        p.start()
    for p in process_list:
        p.join()

