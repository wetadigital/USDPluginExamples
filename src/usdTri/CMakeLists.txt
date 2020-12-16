usd_shared_library(usdTri

    PUBLIC_HEADERS_INSTALL_PREFIX
        ${ORGANIZATION}

    PYTHON_INSTALL_PREFIX
        ${ORGANIZATION}

    LIBRARIES
        js
        plug
        tf
        sdf
        vt
        gf
        usd
        usdGeom

    PUBLIC_CLASSES
        triangle

    PUBLIC_HEADERS
        api.h
        tokens.h

    CPPFILES
        tokens.cpp

    PYTHON_CPPFILES
        moduleDeps.cpp

    PYMODULE_CPPFILES
        module.cpp
        wrapTokens.cpp
        wrapTriangle.cpp

    PYTHON_FILES
        __init__.py

    RESOURCE_FILES
        generatedSchema.usda
        plugInfo.json
)

add_subdirectory(tests)
