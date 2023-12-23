FILE(GLOB_RECURSE SOURCES "*.cpp")
FILE(GLOB_RECURSE HEADERS "*.h")

if(CMAKE_GENERATOR MATCHES "Xcode")
    add_executable(simplelexer ${SOURCES} ${HEADERS})
else()
    add_executable(simplelexer ${SOURCES})
endif()

target_link_libraries(simplelexer PRIVATE ${llvm_libs})
