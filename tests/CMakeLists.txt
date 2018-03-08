# TODO This feels like a hack!
add_definitions(-DMIMEDB_FILE=\"${MIMEDB_FILE}\")

add_executable(${PROJECT_NAME}_tests
        main.cpp
        ../mime/mime.cpp
        ../mime/mime.h
        )

target_link_libraries(${PROJECT_NAME}_tests ${CONAN_LIBS})