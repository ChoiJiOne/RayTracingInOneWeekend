cmake_minimum_required(VERSION 3.30)

set(CHAPTER_13_01 "Chapter13_01")

add_subdirectory(${CHAPTER_13_01})

set_target_properties(
    ${CHAPTER_13_01}
    PROPERTIES FOLDER "Chapter13"
)