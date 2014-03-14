find_package(DBus)

set(INTERGEN_CMD ${CMAKE_BINARY_DIR}/tools/intergen/bin/intergen)
set(GENERATED_LIB_DEPENDENCIES rpc_base jsoncpp)
set(GENERATED_LIB_HEADER_DEPENDENCIES
  ${CMAKE_SOURCE_DIR}/src/components/rpc_base/include
  ${CMAKE_SOURCE_DIR}/src/thirdPartyLibs/jsoncpp/include
  ${DBUS_INCLUDE_DIRS}
)

# Generates interface library from given xml file and builds it
# in CMAKE_CURRENT_BINARY_DIR
# |xml_file_name| contains path to xml spec files
# |generated_interface_names| should contain list of generated interfaces
# if |AUTO_FUNC_IDS| is added to argument list, intergen is called with "-a"
#   flag telling intergen to generate function ids automatically
# from xml_file (intergen creates separate directory for every interface).
# Their names are written lowercase_underscored_style.
macro (GenerateInterfaceLibrary xml_file_name generated_interface_names)
  set(options AUTO_FUNC_IDS)
  cmake_parse_arguments(GenerateInterfaceLibrary "${options}" "" "" ${ARGN})
  if (GenerateInterfaceLibrary_AUTO_FUNC_IDS)
    set(intergen_flags "-a")
  endif()

  foreach(interface_name ${generated_interface_names})
    set(HEADERS
        ${interface_name}/enums.h
        ${interface_name}/types.h
        ${interface_name}/functions.h
        ${interface_name}/interface.h
    )
    set(SOURCES
        ${interface_name}/enums.cc
        ${interface_name}/types.cc
        ${interface_name}/functions.cc
        ${interface_name}/validation.cc
        ${interface_name}/interface.cc
    )
    add_custom_command( OUTPUT ${HEADERS} ${SOURCES}
                        COMMAND ${INTERGEN_CMD} -f ${CMAKE_CURRENT_SOURCE_DIR}/${xml_file_name} -i ${interface_name} ${intergen_flags}
                        DEPENDS ${INTERGEN_CMD} ${xml_file_name}
                        COMMENT "Generating interface ${interface_name} from ${xml_file_name}"
                        VERBATIM
                       )
    include_directories(
      ${CMAKE_CURRENT_BINARY_DIR}
      ${GENERATED_LIB_HEADER_DEPENDENCIES}
    )
    add_library(${interface_name} ${SOURCES})

    # |previous_interface| ensures that interface libraries are built in the same order
    # as they defined in |generated_interface_names|
    target_link_libraries(${interface_name} ${GENERATED_LIB_DEPENDENCIES} ${previous_interface})
    set(previous_interface ${interface_name})
  endforeach(interface_name)
endmacro(GenerateInterfaceLibrary xml_file_name generated_interface_names)
