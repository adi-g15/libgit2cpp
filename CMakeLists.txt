cmake_minimum_required(VERSION 3.12)

project (libgit2cpp
	DESCRIPTION "C++ wrapper for libgit2 library"
	LANGUAGES C CXX
	VERSION 1.1.0
	)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Build options
OPTION(USE_BOOST "Enable use of boost header libraries" OFF)

IF(USE_BOOST)
  add_definitions(-DUSE_BOOST=1)
  find_package(Boost REQUIRED)
  include_directories(${BOOST_INCLUDEDIR})
ENDIF()

if (MSVC)
  OPTION(BUNDLE_LIBGIT2 "use bundled libgit2" ON)
else()
  OPTION(BUNDLE_LIBGIT2 "use bundled libgit2" OFF)
endif()

# https://gist.github.com/scivision/bb1d47a9529e153617414e91ff5390af
include(cmake/AddGitSubmodule.cmake)
if (BUNDLE_LIBGIT2)
  add_git_submodule(libs/libgit2)	# clone it if user didn't clone explicitly
  add_subdirectory(libs/libgit2)
endif()

file(GLOB_RECURSE lib_sources
  src/*.cpp
  include/git2cpp/*.h
)

add_library(git2cpp ${lib_sources})

target_include_directories(git2cpp
  PRIVATE
    src
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if (USE_BOOST)
  target_include_directories(git2cpp PUBLIC ${Boost_INCLUDE_DIRS})
endif()

if (BUNDLE_LIBGIT2)
  target_include_directories(git2cpp
    PUBLIC libs/libgit2/include
  )
endif()

target_link_libraries(git2cpp git2)

option(BUILD_LIBGIT2CPP_EXAMPLES ON)

if(BUILD_LIBGIT2CPP_EXAMPLES)
  set(examples
    add
    branch
    cat-file
    diff
    log
    rev-list
    showindex
    status
    init
    rev-parse
    general
    remote
    checkout
    ls-files
    blame
  )
  
  foreach (example ${examples})
    add_executable("${example}-cpp" examples/${example}.cpp)
    target_link_libraries("${example}-cpp" git2cpp)
  endforeach(example)
  
  add_executable(commit-graph-generator examples/commit-graph-generator.cpp)
  target_link_libraries(commit-graph-generator git2cpp)
  
  file(COPY test.sh DESTINATION . FILE_PERMISSIONS ${EXE_PERM})
endif()
