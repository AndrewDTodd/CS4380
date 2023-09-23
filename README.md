# Project0_BinaryConversion  

###### **NOTE: all steps assume user is on Ubuntu 22.04 or compatible Debian system**  
#### Steps to build  
##### Prolog: Clone the repo  
Navigate to the directory you what the repository to be cloned into and enter the following command  

If authenticating with SSH(recommended)  
  
    git clone git@github.com:AndrewDTodd/CS4380.git

If authenticating with HTTPS  

    git clone https://github.com/AndrewDTodd/CS4380.git

##### Step 1: navigate to repo  
Use the following command to navigate into the repositories directory  

    cd CS4380

##### Step 2: make Build shell script executable  
Run the following command to make the script executable  

    chmod +x Build.sh

#### Steps to run programs/tests  
##### Step 1: navigate to build directory  
The previouse steps have created and built the programs in a new directory. Enter the following to navigate to this directory  

    cd build/linux-x64-release

##### Step 2: run desired programs
To run the test suite

    ./runTests

To run the project program

    ./B10ToB2
