if(EXISTS "/Users/stanislav/Documents/Учеба/ершов/vektor/mybuild/example_tests[1]_tests.cmake")
  include("/Users/stanislav/Documents/Учеба/ершов/vektor/mybuild/example_tests[1]_tests.cmake")
else()
  add_test(example_tests_NOT_BUILT example_tests_NOT_BUILT)
endif()
