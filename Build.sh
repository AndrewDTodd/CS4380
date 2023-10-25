#set the preset configuration to the x64 release mode
cmake --preset x64-Release

#build, directing cmake to the cache and configuration that should now be in the build/x64-Release directory
cmake --build ./build/x64-Release
