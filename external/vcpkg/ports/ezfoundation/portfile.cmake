vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
  OUT_SOURCE_PATH SOURCE_PATH
  REPO ezEngine/ezEngine
  REF 1448308ab99bae0d8d2a292ad345ff3a757f3124 #21.10
  SHA512 20da87772366d1612795f534b31600123c0d04beba252d27d895c3c3cff7dae65952bd890629d79a7a691c2f3444601552c4b4eca99e8f8a99dc935ce2ebd284
  PATCHES
    ezFoundation_vcpkg.patch
)

vcpkg_cmake_configure(
  SOURCE_PATH "${SOURCE_PATH}"
  OPTIONS
    -DEZ_3RDPARTY_ENET_SUPPORT=OFF
    -DEZ_3RDPARTY_ZSTD_SUPPORT=OFF
    -DEZ_3RDPARTY_ZLIB_SUPPORT=OFF
    -DEZ_BUILD_FILTER=FoundationOnly
    -DEZ_BUILD_UNITTESTS=OFF
    -DEZ_ENABLE_FOLDER_UNITY_FILES=OFF
    -DEZ_ENABLE_QT_SUPPORT=OFF
    -DEZ_USE_PCH=OFF
  OPTIONS_DEBUG
    -DEZ_OUTPUT_DIRECTORY_LIB=${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-dbg/Output/Lib
    -DEZ_OUTPUT_DIRECTORY_DLL=${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-dbg/Output/Bin
  OPTIONS_RELEASE
    -DEZ_OUTPUT_DIRECTORY_LIB=${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-rel/Output/Lib
    -DEZ_OUTPUT_DIRECTORY_DLL=${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-rel/Output/Bin
)

vcpkg_cmake_build(TARGET Foundation)

# EzEngine does not support CMake-based install; copy headers and libraries manually.
file(GLOB_RECURSE FOUNDATION_INCLUDE_FILES RELATIVE "${SOURCE_PATH}/Code/Engine/Foundation" "${SOURCE_PATH}/Code/Engine/Foundation/*.h")
foreach(SOURCE_FILE ${FOUNDATION_INCLUDE_FILES})
    get_filename_component(SOURCE_FILE_DIR "${SOURCE_FILE}" DIRECTORY)
    if(SOURCE_FILE_DIR STREQUAL "")
        set(TARGET_DIR "${CURRENT_PACKAGES_DIR}/include/Foundation")
    else()
        set(TARGET_DIR "${CURRENT_PACKAGES_DIR}/include/Foundation/${SOURCE_FILE_DIR}")
    endif()
    file(COPY "${SOURCE_PATH}/Code/Engine/Foundation/${SOURCE_FILE}" DESTINATION "${TARGET_DIR}")
endforeach()

if(NOT DEFINED VCPKG_BUILD_TYPE OR VCPKG_BUILD_TYPE STREQUAL debug)
    set(LIB_SOURCE_DIR "${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-dbg/Output/Lib")
    set(LIB_TARGET_DIR "${CURRENT_PACKAGES_DIR}/debug/lib")
    file(GLOB_RECURSE LIB_FILES "${LIB_SOURCE_DIR}/*.lib")
    foreach(LIB_FILE ${LIB_FILES})
        file(COPY "${LIB_FILE}" DESTINATION "${LIB_TARGET_DIR}")
    endforeach()
endif()
if(NOT DEFINED VCPKG_BUILD_TYPE OR VCPKG_BUILD_TYPE STREQUAL release)
    set(LIB_SOURCE_DIR "${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-rel/Output/Lib")
    set(LIB_TARGET_DIR "${CURRENT_PACKAGES_DIR}/lib")
    file(GLOB_RECURSE LIB_FILES "${LIB_SOURCE_DIR}/*.lib")
    foreach(LIB_FILE ${LIB_FILES})
        file(COPY "${LIB_FILE}" DESTINATION "${LIB_TARGET_DIR}")
    endforeach()
endif()

file(INSTALL "${SOURCE_PATH}/LICENSE.md" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
