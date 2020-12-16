usd_plugin(usdTriFileFormat

    CPPFILES
        fileFormat.cpp

    LIBRARIES
        tf
        sdf
        vt
        gf
        pcp
        usd
        usdGeom

    RESOURCE_FILES
        plugInfo.json
)

add_subdirectory(tests)
