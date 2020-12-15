from pxr import Tf
from pxr.Usdviewq.plugin import PluginContainer


def DefineChildTriangle(usdviewApi):
    for selectedPath in usdviewApi.selectedPaths:
        usdviewApi.stage.DefinePrim(selectedPath.AppendChild("triangle"), "Triangle")


class UsdviewTriPluginContainer(PluginContainer):

    def registerPlugins(self, plugRegistry, usdviewApi):
        self._defineChildTriangle = plugRegistry.registerCommandPlugin(
            "UsdviewTriPluginContainer.DefineChildTriangle",
            "Define Child Triangle",
            DefineChildTriangle)

    def configureView(self, plugRegistry, plugUIBuilder):
        triMenu = plugUIBuilder.findOrCreateMenu("Tri")
        triMenu.addItem(self._defineChildTriangle)


Tf.Type.Define(UsdviewTriPluginContainer)
