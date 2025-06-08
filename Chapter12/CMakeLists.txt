cmake_minimum_required(VERSION 3.30)

set(CHAPTER_12_01 "Chapter12_01")

add_subdirectory(${CHAPTER_12_01})

set_target_properties(
    ${CHAPTER_12_01}
    PROPERTIES FOLDER "Chapter12"
)