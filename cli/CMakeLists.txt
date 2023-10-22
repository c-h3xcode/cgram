add_executable(cgram-cli main.c)

target_link_libraries(cgram-cli PRIVATE cgram)
target_include_directories(cgram-cli PRIVATE ../vendor/cJSON)

target_compile_options(cgram-cli PRIVATE -g -D_FORTIFY_SOURCE=2)

set_target_properties(cgram-cli PROPERTIES C_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

install(TARGETS cgram-cli DESTINATION bin)
