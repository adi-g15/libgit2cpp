# https://gist.github.com/scivision/bb1d47a9529e153617414e91ff5390af
function(add_git_submodule dir)
# add a Git submodule directory to CMake, assuming the
# Git submodule directory is a CMake project.
#
# Usage: in CMakeLists.txt
# 
# include(AddGitSubmodule.cmake)
# add_git_submodule(mysubmod_dir)

find_package(Git REQUIRED)

if(NOT EXISTS ${dir}/CMakeLists.txt)
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- ${dir}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    RESULT_VARIABLE _err)

  if(NOT _err EQUAL 0)
    message(SEND_ERROR "Could not retrieve Git submodule ${dir}.")
  endif()
endif()

add_subdirectory(${dir})

endfunction(add_git_submodule)
