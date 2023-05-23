#ifndef _COMM_H_
#define _COMM_H_

#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<cassert>

#include"Log.hpp"

using namespace std;

#define MODE 0666
#define SIZE 128

string ipcPath = "./fifo.ipc";

#endif