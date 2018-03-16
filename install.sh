git clone https://github.com/lanzhige/fisheye.git
cd ./fisheye
mkdir -p ./build
cd ./build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cd ..
cd ..
rm -rf ./output
mkdir -p ./output
cp ./fisheye/build/Release/fisheye.exe ./output
cp ./fisheye/bin/zlib.dll ./output
mkdir -p ./output/shaders
cp ./fisheye/shaders/* ./output/shaders/
cp ./fisheye/README.md ./output/
rm -rf ./fisheye