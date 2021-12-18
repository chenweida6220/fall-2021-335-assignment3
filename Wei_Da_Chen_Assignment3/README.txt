i.) All parts of Assignment 3 have been completed and compiles successfully.
ii.) Majority of the bugs I encountered were runtime errors from not accessing
the right elements and objects.
iii.)
To compile on terminal type
  make clean
  make all
  ./create_and_test_hash <words file name> <query words file name> <flag>
  ./create_and_test_hash words.txt query_words.txt quadratic
  ./create_and_test_hash words.txt query_words.txt linear
  ./create_and_test_hash words.txt query_words.txt double

  ./spell_check <document file> <dictionary file>
  ./spell_check document1.txt wordsEn.txt

To delete executables and object file type
  make clean

iv.)
Input files:
  document1.txt
  document1_short.txt
  query_words.txt
  words.txt
  wordsEn.txt
