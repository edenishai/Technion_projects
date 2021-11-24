# MTM_EX3_TESTS

HELLO DEAR STUDENTS!!!

These are tests for the 3rd hw for MATAM!
to be able to run the tests, i'll provide a few simple steps to ensure that the tests run smoothly on your computer.

First, i'd like to talk about the directory hierarchy:
in the main directory (doesn't really matter what name), there should be 4 directoeries:

1) partA, which consists of date_wrap.c and date_wrap.h (if you linked the date library from hw1 then all good, if not then be sure to add date.c to your cmake in add_executable)

2) partB: which consists of all the files you used to implement the said part.

3) partC: as said in part2 directory.

4) provided: which has the following files:

       I) the test files I provided in the repository.
                
       II) the files the segel provided (such as date.h).
                
       III) 3 directories, for partA, partB and partC, each containing two directories, expected and your_outputs.
   Alternatively, change the FILE_PATH variable at the top of the file to the path of the test outputs.

the test files i provided are named exactly as the test files of the segel, so be sure to overwrite them :)


IMPORTANT!!!


you need to configure the path in each test depending on where your cmake_build_debug directory is. (the path is tests are when the said directory is in part2)

example:
  if the said directory is in the main directory, you're going to need to change the path in each MACRO ( ASSERT and OPEN_FILE) depending on the path (or change the FILE_PATH).
    
  to run the test on the SSH (sharat) of the faculty, the file path in each macro should start without the ../../provided, instead it should start with ./provided.
 you can change the path as you like but be sure to put the expected outputs in a correct directory depending on the path given.
  
 Always check regulary for added tests :)
 
 
 
