file(GLOB CPPFILES *.cpp)

usd_plugin(hdTri

    CPPFILES
        ${CPPFILES}

    LIBRARIES
        arch
        js
        plug
        tf
        sdf
        vt
        gf
        hd
        hf

    RESOURCE_FILES
        plugInfo.json
)

