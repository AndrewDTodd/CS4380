#list the available presets for user's information
cmake --list-presets=all ./

#set the preset configuration to the x64 release mode
cmake --preset x64-release

#build directing cmake to the cache and configuration that should now be in the build/linux-x64-release directory
cmake --build ./build/x64-release
