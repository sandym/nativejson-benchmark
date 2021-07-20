cmake_minimum_required(VERSION 3.16)
project(nativejson)

set(KAPPADIR /kappa CACHE PATH "path to kappa")

add_library(jsonclibs STATIC)
target_sources(jsonclibs PRIVATE
	src/cjsonlibs/ultrajsondec_all.c
	src/cjsonlibs/qajson4c_all.c
	src/cjsonlibs/jsonc_all.c
	src/cjsonlibs/parson_all.c
	src/cjsonlibs/udpjson_all.c
	src/cjsonlibs/juson_all.c
	src/cjsonlibs/jansson_all.c
	src/cjsonlibs/vincenthz_libjson_all.c
	src/cjsonlibs/facil.io_all.c
	src/cjsonlibs/yajl_all.c
	src/cjsonlibs/jsmn_all.c
	src/cjsonlibs/ujson4c_all.c
	src/cjsonlibs/sheredom_jsonh_all.c
	src/cjsonlibs/ccan_all.c
	src/cjsonlibs/cjson_all.c
	src/cjsonlibs/pjson_all.c
)
target_include_directories(jsonclibs PRIVATE
	thirdparty
	thirdparty/include
	thirdparty/ujson4c/3rdparty
	thirdparty/pjson/inc
	thirdparty/udp-json-parser
	thirdparty/facil.io/lib/facil/core/types/fiobj
	${CMAKE_BINARY_DIR}/thirdparty/include
)
add_library(jsonclibs2 STATIC)
target_sources(jsonclibs2 PRIVATE
	src/cjsonlibs/ultrajsondec_all.c
	src/cjsonlibs/qajson4c_all.c
	src/cjsonlibs/jsonc_all.c
	src/cjsonlibs/parson_all.c
	src/cjsonlibs/udpjson_all.c
	src/cjsonlibs/juson_all.c
	src/cjsonlibs/jansson_all.c
	src/cjsonlibs/vincenthz_libjson_all.c
	src/cjsonlibs/facil.io_all.c
	src/cjsonlibs/yajl_all.c
	src/cjsonlibs/jsmn_all.c
	src/cjsonlibs/ujson4c_all.c
	src/cjsonlibs/sheredom_jsonh_all.c
	src/cjsonlibs/ccan_all.c
	src/cjsonlibs/cjson_all.c
	src/cjsonlibs/pjson_all.c
)
target_include_directories(jsonclibs2 PRIVATE
	thirdparty
	thirdparty/include
	thirdparty/ujson4c/3rdparty
	thirdparty/pjson/inc
	thirdparty/udp-json-parser
	thirdparty/facil.io/lib/facil/core/types/fiobj
	${CMAKE_BINARY_DIR}/thirdparty/include
)
target_compile_definitions(jsonclibs2 PRIVATE
	USE_MEMORYSTAT=0
	TEST_PARSE=1
	TEST_STRINGIFY=0
	TEST_PRETTIFY=0
	TEST_TEST_STATISTICS=1
	TEST_SAXROUNDTRIP=0
	TEST_SAXSTATISTICS=0
	TEST_SAXSTATISTICSUTF16=0
	TEST_CONFORMANCE=0
	TEST_INFO=0
)

file(GLOB YAJL_HEADERS "thirdparty/yajl/src/api/*.h")
foreach(f IN LISTS YAJL_HEADERS)
	file(COPY ${f} DESTINATION thirdparty/include/yajl)
endforeach()

add_executable(nativejson)
target_sources(nativejson PRIVATE
	src/config.h
	src/memorystat.cpp
	src/test.h
	src/tests/strduptest.cpp
	src/tests/jsonxxtest.cpp
	src/tests/rapidjsoniterativetest.cpp
	src/tests/jsonspirittest.cpp
	src/tests/rapidjsonautoutftest.cpp
	src/tests/pocotest.cpp
	src/tests/janssontest.cpp
	src/tests/sheredomjsonhtest.cpp
	src/tests/nlohmanntest.cpp
	src/tests/configurutest.cpp
	src/tests/taocppnlohmanntest.cpp
	# src/tests/ULibtest.cpp
	src/tests/jeayesontest.cpp
	src/tests/voorheestest.cpp
	src/tests/rapidjsontest.cpp
	src/tests/boostjsontest.cpp
	src/tests/taocpptest.cpp
	src/tests/jusontest.cpp
	src/tests/rapidjsoninsitutest.cpp
	src/tests/jvartest.cpp
	src/tests/ujson4ctest.cpp
	src/tests/jsonconstest.cpp
	src/tests/simplejsontest.cpp
	src/tests/udpjsontest.cpp
	src/tests/follytest.cpp
	src/tests/qajson4ctest.cpp
	src/tests/cajuntest.cpp
	src/tests/cpprestsdktest.cpp
	src/tests/jsoncpptest.cpp
	src/tests/sajsontest.cpp
	src/tests/yajltest.cpp
	src/tests/parsontest.cpp
	src/tests/gasontest.cpp
	src/tests/arduinojsontest.cpp
	src/tests/v8test.cpp
	src/tests/qttest.cpp
	src/tests/tunnuztest.cpp
	src/tests/jsmntest.cpp
	src/tests/jzontest.cpp
	src/tests/pjsontest.cpp
	src/tests/jsonboxtest.cpp
	src/tests/ccantest.cpp
	src/tests/rapidjsonfullprectest.cpp
	src/tests/simdjsontest.cpp
	src/tests/nbsdxsimplejsontest.cpp
	src/tests/fastjsontest.cpp
	src/tests/dropboxjson11test.cpp
	src/tests/ujsontest.cpp
	src/tests/facil.io.cpp
	src/tests/picojsontest.cpp
	src/tests/jsonctest.cpp
	src/tests/vincenthzlibjsontest.cpp
	src/tests/cjsontest.cpp
	src/timer.h
	src/resultfilename.h
	src/memorystat.h
	src/main.cpp
)
set_target_properties(nativejson PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)
target_compile_options(nativejson PRIVATE -Wno-deprecated-register)
target_include_directories(nativejson PRIVATE
	thirdparty
	thirdparty/rapidjson/include
	thirdparty/simdjson/singleheader
	thirdparty/fastjson/include
	thirdparty/jsonbox/include
	thirdparty/pjson/inc
	thirdparty/include
	thirdparty/jsoncpp/include
	thirdparty/udp-json-parser
	thirdparty/facil.io/lib/facil/core/types/fiobj
	thirdparty/jsoncons/src
	thirdparty/jvar/include
	${CMAKE_BINARY_DIR}/thirdparty/include
	${CMAKE_BINARY_DIR}/boost/src/boost
)
target_link_libraries(nativejson PRIVATE jsonclibs)
add_dependencies(nativejson boost)

file(GLOB testfiles src/tests/*.cpp)
foreach(testfile ${testfiles})
	get_filename_component(base ${testfile} NAME_WE)
	if(${base} STREQUAL "ULibtest")
		continue()
	endif()
	if(${base} STREQUAL "kappajson" AND NOT IS_DIRECTORY ${KAPPADIR})
		continue()
	endif()
	add_executable("jsonstat_${base}")
	target_sources("jsonstat_${base}" PRIVATE
		src/jsonstat/jsonstatmain.cpp
		src/memorystat.cpp
		${testfile}
	)
	target_link_libraries("jsonstat_${base}" PRIVATE jsonclibs2)
	set_target_properties("jsonstat_${base}" PROPERTIES
		CXX_STANDARD 14
		CXX_STANDARD_REQUIRED ON
	)
	target_compile_definitions("jsonstat_${base}" PRIVATE
		USE_MEMORYSTAT=0
		TEST_PARSE=1
		TEST_STRINGIFY=0
		TEST_PRETTIFY=0
		TEST_TEST_STATISTICS=1
		TEST_SAXROUNDTRIP=0
		TEST_SAXSTATISTICS=0
		TEST_SAXSTATISTICSUTF16=0
		TEST_CONFORMANCE=0
		TEST_INFO=0
	)
	target_compile_options("jsonstat_${base}" PRIVATE -Wno-deprecated-register)
	target_include_directories("jsonstat_${base}" PRIVATE
		thirdparty
		thirdparty/rapidjson/include
		thirdparty/simdjson/singleheader
		thirdparty/fastjson/include
		thirdparty/jsonbox/include
		thirdparty/pjson/inc
		thirdparty/include
		thirdparty/jsoncpp/include
		thirdparty/udp-json-parser
		thirdparty/facil.io/lib/facil/core/types/fiobj
		thirdparty/jsoncons/src
		thirdparty/jvar/include
		${CMAKE_BINARY_DIR}/thirdparty/include
		${CMAKE_BINARY_DIR}/boost/src/boost
	)
endforeach()
add_dependencies(jsonstat_boostjsontest boost)

set_source_files_properties(
	src/tests/boostjsontest.cpp
	PROPERTIES
	COMPILE_OPTIONS "-std=c++17"
)

if(IS_DIRECTORY ${KAPPADIR})
	message("using kappa from ${KAPPADIR}")
	target_sources(nativejson PRIVATE src/tests/kappajson.cpp)
	target_include_directories(nativejson PRIVATE
		${KAPPADIR}/lib
		${KAPPADIR}/lib/kappa/utils
	)
	target_include_directories("jsonstat_kappajson" PRIVATE
		${KAPPADIR}/lib
		${KAPPADIR}/lib/kappa/utils
	)
	set_source_files_properties(
		src/tests/kappajson.cpp
		PROPERTIES
		COMPILE_OPTIONS "-std=c++17"
	)
endif()

include(ExternalProject)
ExternalProject_Add(
	boost
	PREFIX boost
	URL https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz
	URL_HASH MD5=e425bf1f1d8c36a3cd464884e74f007a
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_custom_target(run
	COMMAND ${CMAKE_BINARY_DIR}/nativejson
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
	DEPENDS nativejson
	USES_TERMINAL
)

add_custom_target(benchmark
	COMMAND make -f makefile
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/result
	DEPENDS run
	USES_TERMINAL
)

add_custom_target(show
	COMMAND open conformance.html
	COMMAND open performance_unknown_mac64_clang12.0.html
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/result
	USES_TERMINAL
)

