cmake_minimum_required(VERSION 3.30)

set(CHAPTER_04_01 "Chapter04_01")
set(CHAPTER_04_02 "Chapter04_02")

add_subdirectory(${CHAPTER_04_01})
add_subdirectory(${CHAPTER_04_02})

set_target_properties(
    ${CHAPTER_04_01}
    ${CHAPTER_04_02}
    PROPERTIES FOLDER "Chapter04"
)