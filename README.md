Это песочница, в которой содержится исходный код сборки под инструмент Точка из 3D Slicer

## Run building 3D Slicer code for web-assembly

This is repository about research building 3D Slicer for web-assembly


```
npx itk-wasm -i kitware/vtk-wasm -b ./build-emscripten -s . build
```

In current moment building only for vtkSlicerLineWidget.
