cmake_minimum_required(VERSION 3.16)

project(messaging-broker VERSION 1.0.0 LANGUAGES CXX)

set(_include_dir inc/messaging-broker)

set(PROJECT_SOURCES
    ${_include_dir}/pubsub/raw_messages/i_raw_data_processor.h
    ${_include_dir}/pubsub/raw_messages/i_raw_data_receiver.h
    ${_include_dir}/pubsub/i_message_receiver.h
    ${_include_dir}/pubsub/i_pub_sub_publisher.h
    ${_include_dir}/pubsub/i_pub_sub_subscriber.h
    ${_include_dir}/pubsub/msg_publisher.h
    ${_include_dir}/pubsub/msg_subscriber.h
    ${_include_dir}/pubsub/pubsub_factory.h
    ${_include_dir}/pubsub/receiver_worker.h
    ${_include_dir}/serialization/json_deserializer.h
    ${_include_dir}/serialization/json_serializer.h
    ${_include_dir}/serialization/serialization_factory.h
    ${_include_dir}/broker_helper.h
    ${_include_dir}/broker.h
    ${_include_dir}/redis_dispatcher.h
    ${_include_dir}/redis_receiver.h
    src/pubsub/msg_publisher.cpp
    src/pubsub/msg_subscriber.cpp
    src/pubsub/pubsub_factory.cpp
    src/pubsub/receiver_worker.cpp
    src/serialization/json_deserializer.cpp
    src/serialization/json_serializer.cpp
    src/serialization/serialization_factory.cpp
    src/broker.cpp
    src/redis_dispatcher.cpp
    src/redis_receiver.cpp
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

lzr_link_json(${PROJECT_NAME})
lzr_link_qt(${PROJECT_NAME})
lzr_link_redis(${PROJECT_NAME})
lzr_link_systemd(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE
    lazarillo-utils
    messages-definition
    serialization
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_include_directories(${PROJECT_NAME} PRIVATE src)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
