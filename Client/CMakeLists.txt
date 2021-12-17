cmake_minimum_required(VERSION 3.0)

project(socket_programing)
set(project_version_major 0)
set(project_version_minor 1)

set(libs
    #pthread
    #stdc++fs
    wsock32
)

add_executable(
    socket_programing

    #src/day07_01.cpp #TCP통신
    #src/day07_02.cpp
    #src/day08_01.cpp
    #src/day08_02.cpp
    #src/day09_01.cpp
    #src/day09_02.cpp
    #src/day09_03.cpp
    #src/day10_02.cpp
    #src/day11_01.cpp

    #src/day12_01.cpp #UDP통신
    #src/day12_03.cpp #파일
    #src/day12_04.cpp #에코
    #src/day12_05.cpp #계산기
    #src/day13_01.cpp #시간
    #src/day13_02.cpp #이미지파일
    #src/day14_01.cpp #브로드캐스트
    #src/day16_01.cpp #멀티캐스트

    #src/day17_01.cpp #스레드
    #src/day17_02.cpp
    #src/day17_03.cpp
    #src/day17_04.cpp
    #src/day17_05.cpp
    #src/day17_05.cpp
    src/day18_01.cpp #UDP채팅프로그램
)


 target_link_libraries(
    socket_programing
    PUBLIC
    ${libs}
)