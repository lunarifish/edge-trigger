
file(GLOB_RECURSE TEST_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cc)
add_executable(test_edgetrigger ${TEST_SOURCES})
target_link_libraries(test_edgetrigger ${PROJECT_NAME})

add_test(NAME test_edgetrigger COMMAND test_edgetrigger)