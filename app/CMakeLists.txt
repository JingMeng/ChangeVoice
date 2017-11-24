cmake_minimum_required(VERSION 3.4.1)

# 配置根目录
set(distribution_DIR ../../../../libs)


# 添加自己的library
add_library( # Sets the name of the library.
             native-lib
             SHARED
             src/main/cpp/common_platform.cpp
             src/main/cpp/common.cpp
             src/main/cpp/play_sound.cpp )

# 添加已有库library
add_library( fmod-lib
             SHARED
             IMPORTED)


# 设置目标库属性(文件位置)
set_target_properties( fmod-lib
                      PROPERTIES IMPORTED_LOCATION
                      ${distribution_DIR}/armeabi/libfmod.so)

# 添加已有库library
add_library( fmodL-lib
             SHARED
             IMPORTED)


# 设置目标库属性(文件位置)
set_target_properties( fmodL-lib
                      PROPERTIES IMPORTED_LOCATION
                      ${distribution_DIR}/armeabi/libfmodL.so)


# 链接所有库打包成一个库
target_link_libraries( # Specifies the target library.
                       native-lib
                       fmod-lib
                       fmodL-lib)