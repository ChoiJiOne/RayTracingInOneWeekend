cmake_minimum_required(VERSION 3.27)

add_subdirectory(stb)
add_subdirectory(jsoncpp)
add_subdirectory(glm)

set_target_properties(
    stb
    jsoncpp
    glm
    PROPERTIES FOLDER "ThirdParty"
)