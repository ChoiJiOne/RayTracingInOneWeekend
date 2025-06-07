cmake_minimum_required(VERSION 3.30)

set(CHAPTER_09_01 "Chapter09_01")
set(CHAPTER_09_02 "Chapter09_02")
set(CHAPTER_09_03 "Chapter09_03")
set(CHAPTER_09_04 "Chapter09_04")

add_subdirectory(${CHAPTER_09_01})
add_subdirectory(${CHAPTER_09_02})
add_subdirectory(${CHAPTER_09_03})
add_subdirectory(${CHAPTER_09_04})

set_target_properties(
    ${CHAPTER_09_01}
    ${CHAPTER_09_02}
    ${CHAPTER_09_03}
    ${CHAPTER_09_04}
    PROPERTIES FOLDER "Chapter09"
)