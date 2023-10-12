# Self-Evaluation

## Name(s):

Out of 20 points. Use output.txt created using
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes

- If the program does not compile or gives a segmentation error when run,
  the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: 0

- -1 for each public function not implemented
- Constructors: BSTMap(), BSTMap(const BSTMap &bst); BSTMap(const vector<value_type> &v);
- Destructor: ~BSTMap
- Equality: operator==, operator!=
- Traversal: inorder, preorder, postorder
- Rebalancing: rebalance
- Helpers: empty, size, height, clear, contains, count
- Accessor/Modifiers: operator[], getAll

Q: Bonus function - erase: +1

- +1 if erase has been successfully implemented

Q: -1 for each compilation warning, min -3: 0

- Check under _1. Compiles without warnings_
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: 0

- Check under _3. clang-tidy warnings_
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: 0

- Check under _4. clang-format does not find any formatting issues_

Q: Runs and produces correct output: 0

- Try running "./a.out cities.txt Sea" and other examples
- -2 if the output is not sorted by weight

Q: -2 for any detected memory leak: 0

- Check under _5. No memory leaks using g++_
- Check under _6. No memory leaks using valgrind_

Q: Do the tests sufficiently test the code: 0

- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under _7. Tests have full code coverage_ paying attention to _The lines below were never executed_

Q: Are all functions in .h and .cpp file documents (min -3): 0

- -1 for each function not documented

Q: Total points: +1
