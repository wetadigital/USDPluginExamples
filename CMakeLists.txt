# Minimum CMake version aligned with release branch of USD.
cmake_minimum_required(VERSION 3.12)

# Define project.
project(
    USDPluginExamples
    VERSION 0.0.0
    DESCRIPTION "A collection of example plugins for Pixar's USD (Universal Scene Description)."
    LANGUAGES CXX
)

# Discover cmake modules.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/packages
)

# Exposes build options (with default values) for this project.
include(Options)

# Set project defaults.
include(Defaults)

# Import the package dependencies (USD, TBB, ...).
include(Packages)

# Include USD plugin building CMake utilities.
include(USDPluginTools)

# Recurse into source tree.
add_subdirectory(src)

# Export targets and install package files.
# This must come after source tree recursion as exporting targets
# requires the targets to be defined in the first place!
include(Export)
