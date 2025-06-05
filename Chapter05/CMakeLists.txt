cmake_minimum_required(VERSION 3.30)

set(CHAPTER_05_01 "Chapter05_01")

add_subdirectory(${CHAPTER_05_01})

set_target_properties(
    ${CHAPTER_05_01}
    PROPERTIES FOLDER "Chapter05"
)