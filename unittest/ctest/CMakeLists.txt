cmake_minimum_required(VERSION 3.10)
project(ctest_example)
enable_testing()

add_test(NAME simple
  COMMAND sh test_ctest.sh
)

add_test(NAME simple2
  COMMAND sh test_fail.sh
)

add_custom_target(check
    COMMAND ctest --output-junit junit_report.xml
)


