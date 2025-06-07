cmake_minimum_required(VERSION 3.30)

set(CHAPTER_07_01 "Chapter07_01")

add_subdirectory(${CHAPTER_07_01})

set_target_properties(
    ${CHAPTER_07_01}
    PROPERTIES FOLDER "Chapter07"
)