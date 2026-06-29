cmake_minimum_required(VERSION 3.23)

project(freelancer-sdk LANGUAGES CXX)

set(FLSDK_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(FLSDK_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/source)
file(GLOB_RECURSE TMP_FILES LIST_DIRECTORIES false
        "${FLSDK_INCLUDE_PATH}/*.c*"
        "${FLSDK_INCLUDE_PATH}/*.h*"
        "${FLSDK_SOURCE_PATH}/*.h*"
        "${FLSDK_SOURCE_PATH}/*.c*"
)

add_library(FreelancerSDK SHARED ${TMP_FILES})

target_include_directories(FreelancerSDK PUBLIC
        $<BUILD_INTERFACE:${FLSDK_INCLUDE_PATH}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(FreelancerSDK PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/FLCoreDALib.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/FLCoreDACom.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/FLCoreCommon.lib
        "Dsound.lib"
        "ws2_32.lib"
        "dxguid.lib"
)

target_link_options(FreelancerSDK PRIVATE
        /INCREMENTAL:NO
        /OPT:ICF
        /OPT:REF
)

target_compile_definitions(FreelancerSDK PRIVATE
        "FLSDK_IMPORT=__declspec(dllexport);"
)