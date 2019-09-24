cmake_minimum_required(VERSION 3.11)

#main project
set(proj MidiBuddyConfigure)
project(${proj})

#externals
include(ExternalProject)
file(GLOB EXTERNAL_PROJECTS cmake/externals/*.cmake)

foreach(external ${EXTERNAL_PROJECTS})
	include(${external})
endforeach()


ExternalProject_Add(${proj}
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bundles
  BINARY_DIR ${CMAKE_BINARY_DIR}/MidiBuddyBuild
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )
add_dependencies(${proj} cppmicroservices)


#build MidiBuddy
set(mb_build_cmd ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/MidiBuddyBuild --config ${CMAKE_CFG_INTDIR})
add_custom_target(MidiBuddyBuild
  COMMAND ${mb_build_cmd}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/MidiBuddyBuild
  DEPENDS MidiBuddyConfigure
  )
