cmake_minimum_required(VERSION 3.30)

set(CHAPTER_10_01 "Chapter10_01")

add_subdirectory(${CHAPTER_10_01})

set_target_properties(
    ${CHAPTER_10_01}
    PROPERTIES FOLDER "Chapter10"
)