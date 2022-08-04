project(messages-definition VERSION 1.0 LANGUAGES CXX)

set(PROJECTS_LIST
    lazarillo-hmi
    service-base
    web-gateway
)

foreach(project ${PROJECTS_LIST})
    message("Adding messages directory: ${project}")
    add_subdirectory(inc/messages/${target})
endforeach()

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
