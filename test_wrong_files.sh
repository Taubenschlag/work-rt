for file in resources/disfunctional/*;
do
  valgrind --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  --verbose \
  --log-file=$file.txt \
  ./miniRT $file
done
