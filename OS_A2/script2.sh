#!/bin/bash
cd /usr/src/linux-4.4.4
make oldconfig
make -j4
