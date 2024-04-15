if (TARGET imnodes)
    return()
endif()

set(_imnodes_SourceDir ${CAD_ROOT_DIR}/External/imnodes)
set(_imnodes_BinaryDir ${CMAKE_BINARY_DIR}/External/imnodes)

add_subdirectory(${_imnodes_SourceDir} ${_imnodes_BinaryDir})

include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)

find_package_handle_standard_args(
        imnodes
        REQUIRED_VARS
            _imnodes_SourceDir
)

