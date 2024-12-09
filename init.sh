#!/bin/bash

alias test="mkdir -p output && gcc ./src/strings_r.c ./test/strings_r_tests.c -o ./output/strings_tests && ./output/strings_tests"