#ifndef PINFO_H
#define PINFO_H

#include "types.h"

struct proc_info {
int pid;
int state;
int tickets;
int burst_time;
int rtime;
int ctime;
int page_faults;
uint64 sz;
uint64 num_pages;
};

#endif