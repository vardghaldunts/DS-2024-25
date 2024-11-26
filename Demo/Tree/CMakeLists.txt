project(qwerty)

add_executable(tree1Demo main1.cpp)
target_include_directories(tree1Demo PRIVATE ../../Utils/)


add_executable(tree2Demo main2.cpp)
target_include_directories(tree2Demo PRIVATE ../../Utils/)