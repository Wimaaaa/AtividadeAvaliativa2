cmake_minimum_required(VERSION 3.29)
project(Reader C)

set(CMAKE_C_STANDARD 11)

add_executable(Reader Readers/Reader.c)
add_executable(Barrier Barriers/Barriers.c)
add_executable(Signal Signal/Signal.c)
add_executable(Locks Locks/Lock.c)


