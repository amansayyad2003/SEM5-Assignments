project(cacli_lib)
add_library(calci SHARED calci.cpp)
target_include_directories(calci ${PROJECT_SOURCE_DIR}/calci)

