
add_executable(EBCppNuklearExample WIN32  main.cpp icon.rc)

target_link_libraries(EBCppNuklearExample ${EBCPP_LIBS})

target_sources(EBCppNuklearExample PRIVATE icon.rc)
