ExternalProject_Add(cppmicroservices
	GIT_REPOSITORY https://github.com/CppMicroServices/CppMicroServices.git
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
	INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
	GIT_TAG development
)