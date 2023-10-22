file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${cgram_SOURCE_DIR}/include/cgram/**/*.h")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${cgram_SOURCE_DIR}/src/**/*.c")

add_library(cgram SHARED cgram.c http.c params.c requests.c str.c types/User.c ${HEADER_LIST})

# link with curl
find_package(CURL REQUIRED)
target_link_libraries(cgram PRIVATE CURL::libcurl)

# link with cjson
target_link_libraries(cgram PRIVATE cjson)
target_include_directories(cgram PRIVATE ../vendor/cJSON)


# We need this directory, and users of our library will need it too
target_include_directories(cgram PUBLIC ../include)

target_compile_options(cgram PRIVATE -D_CG_VERSION=\"${PROJECT_VERSION}\" -Wall -Wextra -Wpedantic -Werror -Wno-missing-field-initializers -g)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

# install
install(TARGETS cgram DESTINATION lib)
install(FILES ${HEADER_LIST} DESTINATION include/cgram)
