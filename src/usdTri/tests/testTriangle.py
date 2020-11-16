import unittest
from pxr import Gf, Vt, Usd, UsdGeom
from usdpluginexamples import UsdTri


class TestTriangle(unittest.TestCase):
    def testComputeExtent(self):
        # Create a stage.
        stage = Usd.Stage.CreateInMemory()

        # Define a Triangle.
        triangle = UsdTri.Triangle.Define(stage, "/triangle")
        self.assertTrue(triangle)
        self.assertEqual(triangle.GetSideLengthAttr().Get(), 1)

        # Compute extent & validate.
        boundable = UsdGeom.Boundable(triangle.GetPrim())
        self.assertTrue(boundable)
        extent = UsdGeom.Boundable.ComputeExtentFromPlugins(
            boundable, Usd.TimeCode.Default()
        )
        expectedExtent = Vt.Vec3fArray(((0.5, -0.28867513, 0), (0.5, 0.57735026, 0)))
        for actualValue, expectedValue in zip(extent, expectedExtent):
            self.assertTrue(Gf.IsClose(actualValue, expectedValue, 1e-5))


if __name__ == "__main__":
    unittest.main()
