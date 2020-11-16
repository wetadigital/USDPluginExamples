file(GLOB PYTHONFILES *.py)
foreach(PYTHONFILE ${PYTHONFILES})
    usd_python_test(usdTriFileFormat ${PYTHONFILE})
endforeach()
