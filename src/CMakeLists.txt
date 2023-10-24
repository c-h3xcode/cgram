file(GLOB_RECURSE HEADER_LIST "${cgram_SOURCE_DIR}/include/cgram/*.h")
file(GLOB_RECURSE SOURCE_LIST "${cgram_SOURCE_DIR}/src/*.c")

add_library(cgram SHARED ${SOURCE_LIST} ${HEADER_LIST})

# link with curl
find_package(CURL REQUIRED)
target_link_libraries(cgram PRIVATE CURL::libcurl)

# link with cjson
target_link_libraries(cgram PRIVATE cjson)
target_include_directories(cgram PRIVATE ../vendor/cJSON)


# We need this directory, and users of our library will need it too
target_include_directories(cgram PUBLIC ../include)

target_compile_options(cgram PRIVATE -D_CG_VERSION=\"${PROJECT_VERSION}\" -Wall -Wextra -Wno-missing-field-initializers -Wno-gnu-empty-struct -Wno-unused-parameter)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

# install
install(TARGETS cgram DESTINATION lib)
install(FILES ${HEADER_LIST} DESTINATION include/cgram)
