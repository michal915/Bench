project(cache-miss)

file(GLOB src "*.cpp")

add_executable(${PROJECT_NAME} ${src})
add_dependencies(${PROJECT_NAME} benchmark)

target_link_libraries(${PROJECT_NAME} libbenchmark.a pthread rt)
