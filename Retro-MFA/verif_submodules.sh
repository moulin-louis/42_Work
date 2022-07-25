#!/bin/bash
shopt -s nullglob dotglob     # To include hidden files
files=(/LDLogger/*)
if [ ${#files[@]} -eq 0 ]; then git submodule init; git submodule update; fi