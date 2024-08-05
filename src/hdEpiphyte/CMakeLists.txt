usd_library(hdEpiphyte

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
        usdImaging
        hd

    PUBLIC_CLASSES
        hdEpiphyteSchema


    CPPFILES
        sceneIndexPlugin.cpp
        epiphyteSceneIndex.cpp

    RESOURCE_FILES
        plugInfo.json
)