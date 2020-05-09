#!/bin/bash

for filename in tests/o*/*.s; do    
	../../asm_linux $filename
done