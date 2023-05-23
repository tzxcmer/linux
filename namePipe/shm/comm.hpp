#pragma once

#include<iostream>
#include<cstdio>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<cassert>

#include"Log.hpp"

using namespace std;

#define PATH_NAME "/home/tzx"
#define PROJ_ID 0x66
#define SHM_SIZE 4096 //共享内存的大小