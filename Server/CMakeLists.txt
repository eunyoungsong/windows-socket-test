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
    #src/day01_01.cpp
    #src/day01_02.cpp
    #src/day01_03.cpp
    #src/day02_01.cpp
    #src/day02_02.cpp
    #src/day02_03.cpp
    #src/day02_04.cpp
    #src/day02_05.cpp
    #src/day02_06.cpp
    #src/day03_01.cpp
    #src/day03_02.cpp

    #src/day06_01.cpp
    #src/day06_02.cpp
    #src/day06_03.cpp
    #src/day06_04.cpp
    #src/day06_05.cpp

    #TCP/day07_01.cpp #------------TCP통신
    #TCP/day07_01_01.cpp
    #TCP/day07_01_02.cpp 
    #TCP/day08_01.cpp #IP/PORT 
    #TCP/day09_01.cpp #파일전송
    #TCP/day09_02.cpp #동적할당
    #TCP/day09_03.cpp #이미지파일전송1
    #TCP/day10_02.cpp #이미지파일전송2
    #TCP/day11_01.cpp #UpDown게임

    #UDP/day12_01.cpp #------------UDP통신
    #UDP/day12_01_01.cpp
    #UDP/day12_02.cpp #IP/PORT 
    #UDP/day12_03.cpp #파일전송
    #UDP/day12_04.cpp #에코서버구현
    #UDP/day12_05.cpp #계산기
    #UDP/day13_01.cpp #현재시간출력
    #UDP/day13_02.cpp #이미지파일업로드
    
    #UDP/day14_01.cpp #브로드캐스트
    #UDP/day16_01.cpp #멀티캐스트

    #Thread/day17_01.cpp #스레드생성
    #Thread/day17_02.cpp #생성
    #Thread/day17_03.cpp #대기
    #Thread/day17_04.cpp #일시중지
    #Thread/day17_05.cpp #재시작d
    #Thread/day17_06.cpp #동기화/임계영역
    Thread/day18_01.cpp #UDP채팅프로그램

    #Thread/day19_01.cpp #포트스캐너??
    #Thread/day20_01.cpp #TCP채팅프로그램
    
)

 target_link_libraries(
    socket_programing
    PUBLIC
    ${libs}
)