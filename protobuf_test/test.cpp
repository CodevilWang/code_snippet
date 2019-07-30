// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <assert.h>
#ifdef USE_PB3
#include "AddressBook.pb.h" 
#else
#include "AddressBook2.pb.h" 
#endif

int main() {
#ifdef USE_PB3
    example::Person p;
#else
    example2::Person p;
#endif
    p.set_name("wm");
    p.set_id(11);
    p.add_pid(12);
    p.add_pid(13);
    std::vector<int32_t> data;
    data.reserve(p.pid_size());
    printf("%d\n", p.pid(0));
    printf("%d\n", p.pid(1));

    // int32_t data1[3];
    // p.pid().CopyTo(data1, 0);
    int32_t data2[3];
    int32_t* data3 = new int[3];
    std::copy(p.pid().begin(), p.pid().end(), std::back_inserter(data));
    std::copy(p.pid().begin(), p.pid().end(), data2); 
    std::copy(p.pid().begin(), p.pid().end(), data3); 
    // memcpy(&(data[0]), p.mutable_pid(), p.pid_size());
    printf("%d\n", data[0]);
    printf("%d\n", data[1]);
    printf("%d\n", data2[0]);
    printf("%d\n", data2[1]);
    printf("%d\n", data3[0]);
    printf("%d\n", data3[1]);
    data.clear();
    printf("%d\n", p.pid_size());
    memcpy(data2, p.mutable_pid(), p.pid_size() * sizeof(int32_t));
    printf("%d\n", data2[0]);
    printf("%d\n", data2[1]);
#ifdef USE_PB3
    example::Contact c;
#else
    example2::Contact c;
#endif
    c.set_phone_num("1324555");
    c.set_address("beijing");
#ifdef USE_PB3
    c.set_ctype(example::ContactType::Home);
#else
    c.set_ctype(example2::ContactType::Home);
#endif
    std::string cstring;
    if (!c.SerializeToString(&cstring)) {
        printf("serialize failed.");
        return 1;
    }
    p.set_contact(cstring);

#ifdef USE_PB3
    example::Contact d;
#else
    example2::Contact d;
#endif
    if (!d.ParseFromString(p.contact())) {
        printf("deserialize failed.\n");
        return 1;
    }
    assert(d.phone_num() == "1324555");
    assert(d.address() == "beijing");
#ifdef USE_PB3
    assert(d.ctype() == example::ContactType::Home); 
#else
    assert(d.ctype() == example2::ContactType::Home); 
#endif
    printf("%s\n", d.phone_num().c_str());
    printf("%s\n", d.address().c_str());
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
