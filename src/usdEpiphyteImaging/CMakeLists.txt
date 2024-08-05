usd_plugin(usdEpiphyteImaging

    CPPFILES
        epiphyteAPIAdapter.cpp

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
        usdEpiphyte
        hdEpiphyte

    RESOURCE_FILES
        plugInfo.json
)