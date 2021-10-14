project(app_code)

set (CMAKE_CXX_STANDARD 17)

add_library(app_code STATIC
    App.hpp
    App.cpp
    AboutWindow.hpp
    AboutWindow.cpp

    ToolBar.hpp
    ToolBar.cpp

    Console.hpp
    Console.cpp

    ExecutionEngine.hpp
    ExecutionEngine.cpp
)

if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -s SAFE_HEAP=1 -s SAFE_HEAP_LOG")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s DISABLE_EXCEPTION_CATCHING=0 -s USE_PTHREADS=1 -s ASYNCIFY -s 'ASYNCIFY_IMPORTS=['copy']'")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s DISABLE_EXCEPTION_CATCHING=0 -s USE_PTHREADS=1 -s ASYNCIFY -s 'ASYNCIFY_IMPORTS=['copy']'")
include_directories(SYSTEM xhfr/external/lua/src/)
endif()

target_include_directories(app_code PUBLIC "../lua/src")
target_include_directories(app_code PUBLIC "../sol2/include")
target_link_libraries(app_code xhfr TinyIDE liblua sol2)
