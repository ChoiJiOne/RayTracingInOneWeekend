cmake_minimum_required(VERSION 3.27)

add_subdirectory(stb)
add_subdirectory(jsoncpp)

set_target_properties(
    stb
    jsoncpp
    PROPERTIES FOLDER "ThirdParty"
)