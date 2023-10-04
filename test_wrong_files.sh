#!/usr/bin/bash

# for file in resources/disfunctional/*;
# do
file=resources/everything/everything.rt
  valgrind --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  --verbose \
  --log-file=$file.txt \
  ./miniRT --save $file
# done
