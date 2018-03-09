#
#   .__  ._____.
#   |  | |__\_ |__
#   |  | |  || __ \
#   |  |_|  || \_\ \     .__
#   |____/__||___  /____ |__| _____   ____
#                \/     \|  |/     \_/ __ \
#                |  Y Y  \  |  Y Y  \  ___/
#                |__|_|  /__|__|_|  /\___  >
#                      \/         \/     \/
#
#   libmime
#   A C++ library for inferring MIME content-types from pathnames
#
#   Copyright © 2018 D.E. Goodman-Wilson
#

# TODO This feels like a hack!
add_definitions(-DMIMEDB_FILE=\"${MIMEDB_FILE}\")

add_executable(${PROJECT_NAME}_tests
        main.cpp
        ${PROJECT_SOURCE_DIR}/mime/mime_impl.cpp
        ${PROJECT_SOURCE_DIR}/mime/mime_impl.h
        ${PROJECT_SOURCE_DIR}/mime/mime.h
        )

target_link_libraries(${PROJECT_NAME}_tests ${CONAN_LIBS})