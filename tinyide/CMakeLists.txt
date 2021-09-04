cmake_minimum_required(VERSION 3.14.5)
project(TinyIDE)


set (CMAKE_CXX_STANDARD 17)

add_library(ImGuiColorTextEdit
    ImGuiColorTextEdit/TextEditor.h
    ImGuiColorTextEdit/TextEditor.cpp)
target_link_libraries(ImGuiColorTextEdit imgui)

add_library(TinyIDE
    TinyIDE.hpp
    TinyIDE.cpp
    Log.hpp
    Log.cpp
    FileManager.hpp
    FileManager.cpp
    )
target_include_directories(TinyIDE PUBLIC ./)
target_link_libraries(TinyIDE ImGuiColorTextEdit xhfr)
