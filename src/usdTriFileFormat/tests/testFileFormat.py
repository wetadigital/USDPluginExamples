import os
import unittest
from pxr import Vt, Gf, Sdf, Usd, UsdGeom


class TestUsdTriangleFileFormat(unittest.TestCase):
    def testPayloadExpansion(self):
        # Create a new stage.
        stage = Usd.Stage.CreateInMemory()

        # Define a un-typed prim, with side length metadatum value of 5.
        prim = stage.DefinePrim("/triangle")
        prim.SetMetadata("Usd_Triangle_SideLength", 5)

        # Set payload path to ../scenes/empty.triangle.
        payloadPath = os.path.join(
            os.path.dirname(__file__), "..", "scenes", "empty.triangle"
        )
        prim.SetPayload(Sdf.Payload(payloadPath))

        # Should be expanded into a mesh!
        mesh = UsdGeom.Mesh(prim)
        self.assertTrue(mesh)

        # Validate mesh attribute values.
        self.assertEqual(mesh.GetFaceVertexCountsAttr().Get(), Vt.IntArray((3,)))
        self.assertEqual(mesh.GetFaceVertexIndicesAttr().Get(), Vt.IntArray((0, 1, 2,)))

        actualPoints = mesh.GetPointsAttr().Get()
        expectedPoints = Vt.Vec3fArray(
            (
                Gf.Vec3f(0.0, 2.88675, 0.0),
                Gf.Vec3f(-2.5, -1.44337, 0.0),
                Gf.Vec3f(2.5, -1.44337, 0.0),
            )
        )
        self.assertEqual(len(actualPoints), len(expectedPoints))
        for actualPoint, expectedPoint in zip(actualPoints, expectedPoints):
            self.assertTrue(Gf.IsClose(actualPoint, expectedPoint, 1e-5))


if __name__ == "__main__":
    unittest.main()
