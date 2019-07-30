all: gen_proto
	g++ test.cpp AddressBook.pb.cc -o out.a -lprotobuf -std=c++11 -DUSE_PB3
all2: gen_proto
	g++ test.cpp AddressBook2.pb.cc -o out.a -lprotobuf -std=c++11 -DUSE_PB2
gen_proto:
	protoc *proto --cpp_out=./
