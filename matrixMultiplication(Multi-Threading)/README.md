operating System Assignment (Multi-Threading)

A parallelized version of matrix multiplication can be done using one of these three methods:

1- A thread computes the output C matrix i.e. without multi-threading. (A thread per matrix).

2- A thread computes each row in the output C matrix. (A thread per row).

3- A thread computes each element in the output C matrix. (A thread per element).



How to run and compile :

-put your file.c in a directory and create file CMakeLists.txt and put some lines in it and then open the terminal from this directory

Steps

  ● $mkdir build

  ● $cd build

  ● $cmake

  ● $make

  Then after that you will be able to run your program from command

  ● $./matMultip ../test/file_name1../test/file_name1../test/outputfile_name
  
