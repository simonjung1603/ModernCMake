cmake_minimum_required(VERSION 3.10)

#main project
set(proj MidiBuddyConfigure)
project(${proj})

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/MidiBuddyBuild")
set(external_cmake_arguments)

#externals
include(ExternalProject)
file(GLOB EXTERNAL_PROJECTS cmake/externals/*.cmake)

foreach(external ${EXTERNAL_PROJECTS})
	include(${external})
endforeach()

ExternalProject_Add(${proj}
  DOWNLOAD_COMMAND "echo ${external_cmake_arguments}"
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bundles
  BINARY_DIR ${CMAKE_BINARY_DIR}/MidiBuddyBuild
  CMAKE_ARGS "${external_cmake_arguments}"
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )
add_dependencies(${proj} cppmicroservices rtmidi)


#build MidiBuddy
set(mb_build_cmd ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/MidiBuddyBuild --config ${CMAKE_CFG_INTDIR})
add_custom_target(MidiBuddyBuild ALL
  COMMAND ${mb_build_cmd}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/MidiBuddyBuild
  DEPENDS MidiBuddyConfigure
  )
