set(TestName KemterTests)

file(GLOB Sources
    "KemterHMapTests.cpp"
    "KemterHNodeTests.cpp"
)

add_executable(${TestName} ${Sources})
target_link_libraries(${TestName} gtest_main)

add_test(${TestName} ${TestName})