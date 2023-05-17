add_executable(task_complex complex.cpp test_complex.cpp )
add_executable(task_complex_abs complex.cpp test_abs.cpp)
add_test(NAME task_complex COMMAND test_complex)
add_test(NAME task_complex_abs COMMAND test_abs)
