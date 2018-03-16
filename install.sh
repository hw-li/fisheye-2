git clone https://github.com/lanzhige/fisheye.git
cd ./fisheye
mkdir -p ./build
cd ./build
cmake ..
cmake --build . --config Release
cd ..
cd ..
cp ./fisheye/build/src/Release/fisheye.exe ./
cp ./fisheye/bin/zlib.dll ./
mkdir -p ./shaders
cp ./fisheye/shaders/* ./shaders/
cp ./fisheye/README.md ./
rm -rf ./fisheye