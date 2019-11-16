cmake_minimum_required(VERSION 3.12)
project(nativejson)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(jsonclibs STATIC)
file(GLOB_RECURSE CSRCS src/*.c)
target_sources(jsonclibs PRIVATE
	${CSRCS}
)
target_include_directories(jsonclibs PRIVATE
	thirdparty
	thirdparty/include
	thirdparty/ujson4c/3rdparty
	thirdparty/pjson/inc
	thirdparty/udp-json-parser
	# thirdparty/facil.io/lib/facil/core/types
	thirdparty/facil.io/lib/facil/core/types/fiobj
)

add_executable(nativejson_x64)

file(GLOB HEADERS src/*.h)
file(GLOB SRCS src/*.cpp)
file(GLOB TESTS src/tests/*.cpp)

target_sources(nativejson_x64 PRIVATE
	${HEADERS}
	${SRCS}
	${TESTS}
)
target_include_directories(nativejson_x64 PRIVATE
	thirdparty
	thirdparty/jsoncons/include
	thirdparty/fastjson/include
	thirdparty/jsonbox/include
	thirdparty/jsoncpp/include
	thirdparty/rapidjson/include
	# thirdparty/udp-json-parser
	thirdparty/include
	# thirdparty/json-voorhees/include
	# thirdparty/json-voorhees/src
	# thirdparty/jsoncons/src
	# thirdparty/ArduinoJson/include
	# thirdparty/include/jeayeson/include/dummy
	thirdparty/jvar/include
	thirdparty/pjson/inc
	# thirdparty/ULib/include
	# thirdparty/facil.io/lib/facil/core/types
	thirdparty/facil.io/lib/facil/core/types/fiobj
)
target_link_libraries(nativejson_x64 PRIVATE
	jsonclibs
)
