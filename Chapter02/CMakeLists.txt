cmake_minimum_required(VERSION 3.30)

set(CHAPTER_02_01 "Chapter02_01")

add_subdirectory(${CHAPTER_02_01})

set_target_properties(
    ${CHAPTER_02_01}
    ${CHAPTER_02_02}
    PROPERTIES FOLDER "Chapter02"
)