set(TestName KemterTests)

file(GLOB Sources
    "*.cpp"
)

add_executable(${TestName} ${Sources})
target_link_libraries(${TestName} PUBLIC
    gtest_main
)

add_test(${TestName} ${TestName})