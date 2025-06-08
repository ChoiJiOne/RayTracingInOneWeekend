cmake_minimum_required(VERSION 3.30)

set(CHAPTER_11_01 "Chapter11_01")

add_subdirectory(${CHAPTER_11_01})

set_target_properties(
    ${CHAPTER_11_01}
    PROPERTIES FOLDER "Chapter11"
)