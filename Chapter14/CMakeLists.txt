cmake_minimum_required(VERSION 3.30)

set(CHAPTER_14_01 "Chapter14_01")

add_subdirectory(${CHAPTER_14_01})

set_target_properties(
    ${CHAPTER_14_01}
    PROPERTIES FOLDER "Chapter14"
)