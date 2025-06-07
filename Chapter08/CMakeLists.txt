cmake_minimum_required(VERSION 3.30)

set(CHAPTER_08_01 "Chapter08_01")

add_subdirectory(${CHAPTER_08_01})

set_target_properties(
    ${CHAPTER_08_01}
    PROPERTIES FOLDER "Chapter08"
)