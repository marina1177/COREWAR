#!/bin/bash

for filename in champions/*.s; do
	../asm $filename;
done