# Default build configurations for the USDPluginExamples project.

# By default, build for release.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Check if CTest should be enabled.
if (BUILD_TESTING)
    enable_testing()

    # Be very verbose on test failure.
    list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
endif()

if (MSVC)
    # From OpenUSD/cmake/defaults/msvcdefaults.cmake
    #
    # The /Zc:inline option strips out the "arch_ctor_<name>" symbols used for
    # library initialization by ARCH_CONSTRUCTOR starting in Visual Studio 2019,
    # causing release builds to fail. Disable the option for this and later
    # versions.
    #
    # For more details, see:
    # https://developercommunity.visualstudio.com/content/problem/914943/zcinline-removes-extern-symbols-inside-anonymous-n.html
    if (MSVC_VERSION GREATER_EQUAL 1920)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:inline-")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:inline")
    endif()
endif()
