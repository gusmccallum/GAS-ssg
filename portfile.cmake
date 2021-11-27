vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO gusmccallum/GAS-ssg
    REF v1.0.2
    SHA512 0
    HEAD_REF master
)

vcpkg_configure_cmake(
    SOURCE_PATH ${.}
    PREFER_NINJA
)
vcpkg_install_cmake()
file(INSTALL ${.}/COPYING DESTINATION ${.}/share/<project> RENAME copyright)