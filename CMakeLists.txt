cmake_minimum_required(VERSION 3.1.0)
project(timespec_chrono_conversions VERSION 0.0.1 LANGUAGES C CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra -Werror=conversion -Werror=unused-but-set-variable -Werror=return-type)
endif()

add_library(
  ${CMAKE_PROJECT_NAME}
  INTERFACE
)
target_compile_features(
    ${CMAKE_PROJECT_NAME}
    INTERFACE
    cxx_std_23
)
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(
  ${CMAKE_PROJECT_NAME}
)

include(CMakePackageConfigHelpers)

set(GENERAL_INSTALL_DIR /usr/local)
set(INCLUDE_INSTALL_DIR ${GENERAL_INSTALL_DIR}/include) 

install(
  DIRECTORY include/
  DESTINATION ${INCLUDE_INSTALL_DIR}/${CMAKE_PROJECT_NAME}
)

configure_package_config_file(
${CMAKE_PROJECT_NAME}.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION /usr/local/lib/cmake/${CMAKE_PROJECT_NAME}
  PATH_VARS INCLUDE_INSTALL_DIR
)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake
  VERSION 0.0.1
  COMPATIBILITY AnyNewerVersion
)

install(
    TARGETS ${CMAKE_PROJECT_NAME}
    EXPORT ${CMAKE_PROJECT_NAME}Targets
)

install(
    EXPORT ${CMAKE_PROJECT_NAME}Targets
    FILE ${CMAKE_PROJECT_NAME}Targets.cmake
    DESTINATION /usr/local/lib/cmake/${CMAKE_PROJECT_NAME}
    
)

install(FILES 
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake 
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake
  DESTINATION /usr/local/lib/cmake/${CMAKE_PROJECT_NAME}
    
)

