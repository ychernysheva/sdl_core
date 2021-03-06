include(${CMAKE_SOURCE_DIR}/tools/cmake/helpers/sources.cmake)

include_directories(
  ${GMOCK_INCLUDE_DIRECTORY}
  ${COMPONENTS_DIR}/application_manager/rpc_plugins/app_service_rpc_plugin/include
  ${COMPONENTS_DIR}/application_manager/rpc_plugins/app_service_rpc_plugin/include/app_service_rpc_plugin/commands/
  ${COMPONENTS_DIR}/application_manager/test/include/
  ${POLICY_MOCK_INCLUDE_PATH}/
  ${CMAKE_SOURCE_DIR}/src
  ${COMPONENTS_DIR}/resumption/include
)  


set(COMMANDS_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/commands)

file(GLOB SOURCES
  ${COMPONENTS_DIR}/application_manager/test/mock_message_helper.cc
  ${COMPONENTS_DIR}/application_manager/test/mock_application_helper.cc
  ${COMPONENTS_DIR}/application_manager/src/smart_object_keys.cc
  ${COMMANDS_TEST_DIR}/hmi/*
  ${COMMANDS_TEST_DIR}/mobile/*
  ${COMPONENTS_DIR}/application_manager/src/message.cc
  ${COMPONENTS_DIR}/application_manager/src/event_engine/*
)

set(LIBRARIES
  gmock
  sdl_rpc_plugin_static
  app_service_rpc_plugin_static
)

create_cotired_test("app_services_commands_test" "${SOURCES}" "${LIBRARIES}" )

add_subdirectory("app_service_plugin")
