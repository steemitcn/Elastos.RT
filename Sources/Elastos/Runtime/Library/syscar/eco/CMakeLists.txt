
set(CAR_FLAGS -e -A -k)
set(LUBE_FLAGS -e -k -z)
set(LUBE_TS -T uuidcpp)

xdk_compile_car(elastos_core_car ElastosCore.car)


add_custom_command(
    COMMENT "Copying ElastosCore.* to system..."
    OUTPUT "$ENV{XDK_USER_INC}/ElastosCore.h"
           "$ENV{XDK_USER_INC}/_ElastosCore.h"
    COMMAND ${CMAKE_COMMAND} -E copy ElastosCore.h $ENV{XDK_USER_INC}
    COMMAND ${CMAKE_COMMAND} -E copy _ElastosCore.h $ENV{XDK_USER_INC}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS elastos_core_car
            ${CMAKE_CURRENT_BINARY_DIR}/ElastosCore.h
            ${CMAKE_CURRENT_BINARY_DIR}/_ElastosCore.h
)

add_custom_target(copy_elastos_core_headers ALL DEPENDS
                      $ENV{XDK_USER_INC}/ElastosCore.h
                      $ENV{XDK_USER_INC}/_ElastosCore.h)

