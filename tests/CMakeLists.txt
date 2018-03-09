# TODO This feels like a hack!
add_definitions(-DMIMEDB_FILE=\"${MIMEDB_FILE}\")

add_executable(${PROJECT_NAME}_tests
        main.cpp
        ${PROJECT_SOURCE_DIR}/mime/mime_impl.cpp
        ${PROJECT_SOURCE_DIR}/mime/mime_impl.h
        ${PROJECT_SOURCE_DIR}/mime/mime.h
        )

target_link_libraries(${PROJECT_NAME}_tests ${CONAN_LIBS})