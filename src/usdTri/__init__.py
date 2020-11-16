from . import _usdTri
from pxr import Tf

Tf.PrepareModule(_usdTri, locals())
del Tf

try:
    from . import __DOC

    __DOC.Execute(locals())
    del __DOC
except Exception:
    pass
