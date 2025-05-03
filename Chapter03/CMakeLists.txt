cmake_minimum_required(VERSION 3.30)

set(CHAPTER_03_01 "Chapter03_01")

add_subdirectory(${CHAPTER_03_01})

set_target_properties(
    ${CHAPTER_03_01}
    PROPERTIES FOLDER "Chapter03"
)