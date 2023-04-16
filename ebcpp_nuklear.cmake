
include(${CMAKE_CURRENT_LIST_DIR}/dep/ebcpp/ebcpp.cmake)

include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

include_directories(${CMAKE_CURRENT_LIST_DIR}/dep/Nuklear)
include_directories(${CMAKE_CURRENT_LIST_DIR}/dep/Nuklear/demo)

if( "${EBCPP_NUKLEAR_RENDERER}" STREQUAL "GDI")

    add_definitions(-DEBCPP_NUKLEAR_RENDERER=GDI)
    #set(EBCPP_LIBS ${EBCPP_LIBS} -Wl,-subsystem,windows)
    set(EBCPP_LIBS ${EBCPP_LIBS} gdi32)

else()
    message(FATAL_ERROR "No renderer defined. Define EBCPP_NUKLEAR_RENDERER")
endif()
