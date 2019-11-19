ExternalProject_Add(rtmidi
	GIT_REPOSITORY https://github.com/thestk/rtmidi.git
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
	INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
)