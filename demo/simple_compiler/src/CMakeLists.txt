FILE(GLOB_RECURSE SOURCES "*.cpp")
FILE(GLOB_RECURSE HEADERS "*.h")

if(CMAKE_GENERATOR MATCHES "Xcode")
    add_executable(simple_compiler ${SOURCES} ${HEADERS})
else()
    add_executable(simple_compiler ${SOURCES})
endif()

# add_library(ZSTD::ZSTD INTERFACE IMPORTED)
# set_target_properties(ZSTD::ZSTD PROPERTIES INTERFACE_LINK_LIBRARIES "zstd::libzstd_shared")
target_link_libraries(simple_compiler PRIVATE ${llvm_libs})

