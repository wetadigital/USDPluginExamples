usd_python_test(usdTri_python testTriangle.py)

usd_test(usdTri_testTriangle

    CPPFILES
        testTriangle.cpp

    LIBRARIES
        tf
        sdf
        usd
        usdTri
)
