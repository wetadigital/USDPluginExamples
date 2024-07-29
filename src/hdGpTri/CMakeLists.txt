usd_plugin(hdGpTri

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
        hdGp
        arch

    CPPFILES
        triGenerative.cpp
        debugCodes.cpp

    RESOURCE_FILES
        plugInfo.json
)
