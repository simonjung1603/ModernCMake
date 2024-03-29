ExternalProject_Add(cppmicroservices
	GIT_REPOSITORY https://github.com/CppMicroServices/CppMicroServices.git
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
	INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
	GIT_TAG development
)

ExternalProject_Get_Property(cppmicroservices binary_dir)
list(APPEND external_cmake_arguments "-DCppMicroServices_DIR=${binary_dir}")
