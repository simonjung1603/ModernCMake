get_filename_component(_bundle_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" _bundle_name ${_bundle_name})
set(${_bundle_name})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${_bundle_name}BundleDir="${CMAKE_CURRENT_BINARY_DIR}/" ${_bundle_name}BundleFile="${_bundle_name}.dll")

file(GLOB CODE_FILES *.cpp *.h)

# Set up dependencies to resources to track changes
usFunctionGetResourceSource(TARGET ${_bundle_name} OUT _SRCS)
# Generate bundle initialization code
usFunctionGenerateBundleInit(TARGET ${_bundle_name} OUT _SRCS)

add_library(${_bundle_name} ${CODE_FILES} ${_SRCS})
include(GenerateExportHeader)
generate_export_header(${_bundle_name})
target_include_directories(${_bundle_name} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(${_bundle_name} PROPERTIES
  # This is required for every bundle
  COMPILE_DEFINITIONS US_BUNDLE_NAME=${_bundle_name}
  # This is for convenience, used by other CMake functions
  US_BUNDLE_NAME ${_bundle_name}
  )
  
if(BUILD_SHARED_LIBS)
  set_target_properties(${_bundle_name} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
    )
endif()
  
  # Embed meta-data from a manifest.json file
usFunctionEmbedResources(TARGET ${_bundle_name}
  WORKING_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}
  FILES
    manifest.json
  )

find_package(rtmidi REQUIRED)
  
target_link_libraries(${_bundle_name} CppMicroServices core RtMidi::rtmidi)
target_include_directories(${_bundle_name} PRIVATE ${CMAKE_BINARY_DIR}/../rtmidi-prefix/src/rtmidi)

target_include_directories(${_bundle_name} INTERFACE 
    "${CMAKE_SOURCE_DIR}/${_bundle_name}"
)

install(TARGETS ${_bundle_name}
    ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/lib
    LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/lib
    RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin
)

if(BUILD_TESTING)
	#add_subdirectory(test)
endif()