# GameEngine

Setup:

VisualStudio:

open the solution file in Visual Studio
Set the "Startup" project as startup
build. you get the error that <b>assimp-vc143-mt.dll</b> is mising

Copy the <b>assimp-vc143-mt.dll</b> from third_party/assimp/lib to Output/Build

it should run now.

AssetsPath:

in <b>AssetPath.h</b> modify the path to the assets folder <b>"X:\\Path\\To\\solution\\GameEngine\\Resources\\Assets\\"</b>

Build and run and you should see suzanne whith a nice texture on her facing the camera.


Hold RMB to fly look around and
W A S D move
