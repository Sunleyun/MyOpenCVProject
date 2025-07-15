cmake_minimum_required(VERSION 3.10) # 最低CMake版本要求
project(MyOpenCVProject)             # 项目名称

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 寻找OpenCV库
find_package(OpenCV REQUIRED PATHS "D:/opencv/build") # 替换为你的OpenCV安装路径

# 包含OpenCV头文件
include_directories(${OpenCV_INCLUDE_DIRS})

# 创建可执行文件
add_executable(MyOpenCVProject 
	main.cpp 
	trainc.cpp 
	trainopen.cpp
	trainc.h
	trainopen.h
)

# 链接OpenCV库/PCL库
target_link_libraries(MyOpenCVProject ${OpenCV_LIBS})