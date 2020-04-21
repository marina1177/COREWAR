#!/bin/bash

for filename in champions/*.s; do    
	./asm_linux $filename
done
