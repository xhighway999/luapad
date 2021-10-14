cmake_minimum_required(VERSION 3.14.5)
project(app)




set(imgui_DIR xhfr/external/imgui)

set (CMAKE_CXX_STANDARD 17)

set(PROJECTNAME luapad)
add_executable(${PROJECTNAME} main.cpp)

include_directories(SYSTEM "./lua/src")


#asan
if(0)
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address")
    set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address")
endif()

#optimise size
if(0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -s -fdata-sections -ffast-math -ffunction-sections -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -s -fdata-sections -ffast-math -ffunction-sections -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables")
endif()

#gc sections
if(0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--gc-sections")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,--gc-sections")
    add_compile_options(-fdata-sections -ffunction-sections -Wl,--gc-sections)
    add_link_options(--gc-sections)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=0 -s USE_WEBGL2=1 -s WASM=1 -s FULL_ES3=1   -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=4 -s ASYNCIFY -s 'ASYNCIFY_IMPORTS=['copy','paste']'")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w  -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=0 -s USE_WEBGL2=1 -s WASM=1 -s FULL_ES3=1   -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=4 -s ASYNCIFY -s 'ASYNCIFY_IMPORTS=['copy','paste']'")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}  -w -s USE_PTHREADS=1")

    #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -s SAFE_HEAP=1 -s SAFE_HEAP_LOG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -s DISABLE_EXCEPTION_CATCHING=0")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -s ASSERTIONS=1  -O2 -g3 --source-map-base http://127.0.0.1:8000/ -s DISABLE_EXCEPTION_CATCHING=0 -s TOTAL_MEMORY=48MB")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -s ASSERTIONS=1  -O2 -g3 --source-map-base http://127.0.0.1:8000/ -s DISABLE_EXCEPTION_CATCHING=0 -s TOTAL_MEMORY=48MB")
#--source-map-base http://127.0.0.1:8000/
    set(CMAKE_EXE_LINKER_FLAGS "--shell-file ${CMAKE_CURRENT_SOURCE_DIR}/shell_luapad.html ${CMAKE_EXE_LINKER_FLAGS}    ")
    target_link_libraries(${PROJECTNAME} -lidbfs.js -lpthread)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
include_directories(SYSTEM xhfr/external/lua/src/)
endif()

add_subdirectory(xhfr)
add_subdirectory(app_code)
add_subdirectory(tinyide)
add_subdirectory(sol2)
add_subdirectory(lua)


target_link_libraries(${PROJECTNAME} xhfr app_code)




