# Project0_BinaryConversion

Steps to build
prolog: though this step isn't strictly necessary to actually build the project it helps to make sure the user is in the right directory and all necessary configuration files have been downloaded correctly.
  In the bash terminal navigate to the directory of the cloned repository. For isntance home/CS4380.
  in this root directory for the repo there should be a CMakePresets.json document.
  verify its contents are correct by running the following command
  
    cmake --list-presets=all

  after running this command you should see a dialog saying that the available configure presets are
    "linux-x64-debug" and "linux-x64-release"

Step 1:
  This is where the actual necessary steps to build and run begin

  while in the root directory of the repositories clone (such as home/CS4380) run the following command to set the cmake build configuration

    cmake --preset linux-x64-release

  Cmake will configure for the build now. The last line of the dialog will tell you what directory the build cache files have been made in.
  It will be ${root}/build/linux-x64-release (CS4380/build/linux-x64-release)

 Step 2:
   now run the following command

     cmake --build ./build/linux-x64-release

   you will see a 14 step build process proceed
   upon completion navigate to the build/linux-x64-release directory with the following command

     cd build/linux-x64-release

 Step 3:
   the built executables can now be run

   To run the unit tests in the test suite

     ./runTests

   you will see 5 tests execute and report

   To run the B10ToB2 program

     ./B10ToB2

   you will be prompted for input by the program
