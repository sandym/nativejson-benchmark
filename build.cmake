#!/usr/bin/env cmake -P

if(UNIX AND APPLE)
set(PREMAKE_URL
	https://github.com/premake/premake-core/releases/download/v5.0.0-alpha14/premake-5.0.0-alpha14-macosx.tar.gz
)
set(PREMAKE_FILENAME
	premake-5.0.0-alpha14-macosx.tar.gz
)
elseif(UNIX)

else()

endif()

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/build/premake5)
	message("--> downloading premake5")
	file(DOWNLOAD ${PREMAKE_URL}
		${CMAKE_CURRENT_LIST_DIR}/build/${PREMAKE_FILENAME}
	)
	execute_process(
		COMMAND ${CMAKE_COMMAND} -E tar zxf ${PREMAKE_FILENAME}
		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build
	)
	file(REMOVE ${CMAKE_CURRENT_LIST_DIR}/build/${PREMAKE_FILENAME})
endif()

if(UNIX AND NOT APPLE)
	execute_process(
		COMMAND ./configure
		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/thirdparty/ULib
	)
	execute_process(
		COMMAND make
		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/thirdparty/ULib
	)
endif()

execute_process(
	COMMAND make CONFIG=release_x64
	WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
