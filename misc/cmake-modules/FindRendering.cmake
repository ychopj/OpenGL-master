if (TARGET Rendering)
    return()
endif()

set(_Rendering_SourceDir ${CAD_ROOT_DIR}/DGERendering/)
set(_Rendering_BinaryDir ${CMAKE_BINARY_DIR}/DGERendering/)

add_subdirectory(${_Rendering_SourceDir} ${_Rendering_BinaryDir})

include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)

find_package_handle_standard_args(
        Rendering
        REQUIRED_VARS
        _Rendering_SourceDir
)