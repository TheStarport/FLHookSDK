cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)
project(freelancer-sdk LANGUAGES CXX)

set(FLSDK_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE TMP_FILES LIST_DIRECTORIES false
        "${FLSDK_INCLUDE_PATH}/*.c*"
        "${FLSDK_INCLUDE_PATH}/*.h*"
)

add_library(FreelancerSDK SHARED ${TMP_FILES})

target_include_directories(FreelancerSDK PUBLIC
        $<BUILD_INTERFACE:${FLSDK_INCLUDE_PATH}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(FreelancerSDK PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/FLCoreCommon.lib
)

target_link_options(FreelancerSDK PRIVATE
        /INCREMENTAL:NO
        /OPT:ICF
        /OPT:REF
)

target_compile_definitions(FreelancerSDK PRIVATE
        "FLSDK_IMPORT=__declspec(dllexport);"
)