project(vender-sqlite3)

set(SQLITE3_PROJECT_NAME sqlite3)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SQLIT3_FILES)

add_library(${SQLITE3_PROJECT_NAME}
    STATIC
    ${SQLIT3_FILES}
)
add_library(sqlite3::lib ALIAS ${SQLITE3_PROJECT_NAME})

target_include_directories(${SQLITE3_PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
