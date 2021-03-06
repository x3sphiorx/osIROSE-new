cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

IF(ENABLE_TESTING_COVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
  set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
ENDIF() # ENABLE_TESTING_COVERAGE

IF( ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang )
  if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth=900 -Wno-macro-redefined")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth=900 -Wno-expansion-to-defined")
  endif()
ENDIF()

IF(ENABLE_TESTING)
  include_directories(
    SYSTEM ${GTEST_INCLUDE_DIR}
    SYSTEM ${GMOCK_INCLUDE_DIR}
  )
ENDIF() # ENABLE_TESTING

IF( ENABLE_ASAN )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address -fno-omit-frame-pointer")
  set(LINK_FLAGS "${LINK_FLAGS} -g -fsanitize=address")
ENDIF()

IF( DISABLE_CRYPT )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDISABLE_CRYPT")
ENDIF()

include_directories(
  SYSTEM ${ASIO_INCLUDE_DIR}
  SYSTEM ${EXTERNAL_INCLUDE_DIR}
  SYSTEM ${SPDLOG_ROOT}
  SYSTEM ${SOL2_ROOT}
  SYSTEM ${LUA_INCLUDE_DIR}
  SYSTEM ${CXXOPT_ROOT}
  SYSTEM ${ENTITYX_INCLUDE_DIR}
  SYSTEM ${SQLPP_INCLUDE_DIR}
  SYSTEM ${DATE_INCLUDE_DIR}
  SYSTEM ${CONFIGURU}
  SYSTEM ${VISIT_STRUCT}
)

link_directories(
  ${EXTERNAL_BINARY_DIR}
)

IF(ENABLE_MYSQL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENABLE_MYSQL")
  include_directories(
    SYSTEM ${MYSQL_INCLUDE_DIRS}
    SYSTEM ${SQLPP_CONNECTOR_MYSQL_INCLUDE_DIR}
  )

  link_directories(
    ${MYSQL_LIBRARY_PATH}
  )
ENDIF()

IF (MSVC)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LTCG /INCREMENTAL:NO /ignore:4075")
  set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /LTCG /ignore:4075")
ENDIF()

add_subdirectory(core)
add_subdirectory(rosecommon)
add_subdirectory(login)
add_subdirectory(char)
add_subdirectory(map)

add_subdirectory(bot)

IF(ENABLE_TESTING)
  add_subdirectory(tests)
ENDIF()

