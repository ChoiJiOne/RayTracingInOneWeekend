cmake_minimum_required(VERSION 3.30)

set(CHAPTER_06_01 "Chapter06_01")
set(CHAPTER_06_02 "Chapter06_02")
set(CHAPTER_06_03 "Chapter06_03")
set(CHAPTER_06_04 "Chapter06_04")

add_subdirectory(${CHAPTER_06_01})
add_subdirectory(${CHAPTER_06_02})
add_subdirectory(${CHAPTER_06_03})
add_subdirectory(${CHAPTER_06_04})

set_target_properties(
    ${CHAPTER_06_01}
    ${CHAPTER_06_02}
    ${CHAPTER_06_03}
    ${CHAPTER_06_04}
    PROPERTIES FOLDER "Chapter06"
)