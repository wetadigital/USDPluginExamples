usd_plugin(usdTriImaging

    CPPFILES
        triangleAdapter.cpp
        debugCodes.cpp

    LIBRARIES
        arch
        js
        plug
        usd
        tf
        sdf
        vt
        gf
        hd
        usdGeom
        usdImaging
        usdTri

    RESOURCE_FILES
        plugInfo.json
)

