if (TARGET ScopeGuard)
    return()
endif()

set(_ScopeGuard_SourceDir ${CAD_ROOT_DIR}/External/ScopeGuard)
set(_ScopeGuard_BinaryDir ${CMAKE_BINARY_DIR}/External/ScopeGuard)

add_subdirectory(${_ScopeGuard_SourceDir} ${_ScopeGuard_BinaryDir})

include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)

find_package_handle_standard_args(
    ScopeGuard
    REQUIRED_VARS
        _ScopeGuard_SourceDir
)

