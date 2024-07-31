usd_plugin(usdTriImagingHd2

    CPPFILES
        triangleAdapter.cpp
        debugCodes.cpp
        dataSourceTri.cpp

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