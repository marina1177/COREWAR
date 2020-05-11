#!/bin/bash

for filename in ../../../42_corewar1/test/unit_test/*.s; do
	dos2unix $filename;
	../../asm_linux $filename;
done