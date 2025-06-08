cmake_minimum_required(VERSION 3.30)

set(CHAPTER_11_01 "Chapter11_01")
set(CHAPTER_11_02 "Chapter11_02")
set(CHAPTER_11_03 "Chapter11_03")

add_subdirectory(${CHAPTER_11_01})
add_subdirectory(${CHAPTER_11_02})
add_subdirectory(${CHAPTER_11_03})

set_target_properties(
    ${CHAPTER_11_01}
    ${CHAPTER_11_02}
    ${CHAPTER_11_03}
    PROPERTIES FOLDER "Chapter11"
)