# Project5  

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

##### Step 3: run the build script
Enter the following command to run the build script

    ./Build.sh

###### **NOTE**: I have had issues with the Build.sh script being corrupted by windows (adding carriage returns to the new lines). If this happens the script wont run with the instructions provided.
###### **NOTE Continued**: If the Build.sh script is corrupted, one can either recreate it (its just two lines), or just manually enter its contents into a terminal in sequence (its two lines...)

#### Steps to run programs/tests  
##### Step 1: navigate to build directory  
The previouse steps have created and built the programs in a new directory. Enter the following to navigate to this directory  

    cd build/x64-Release

##### Step 2: run desired programs
To run the monolithic test suite enter the following

    ./runAllTargetTests

To run the project programs we need to navigate into their directories or include the path in the execute command. You can enter the following

To run the monolithic Assembler/Virtual Machine launch pad program  
(**note any file with a different extension that those explicitly supported will default to running on the Assembler. Both programs will run any file that is properly formatted regardless of the extension)  

    ./monoSystem <optional path to .asm or .bin>

To run the VM  

    ./VM_4380/VM4380 <optional path to bin>

To run the Assember  
    
    ./ASM_4380/ASM4380 <optional path to asm>

To run any target's unit tests  

    ./(target directory)/(target name)Tests

###### Note about project assembly programs/examples
All the .asm files made for the project from previouse iterations to this iteration are contained in the ProjASMs directory  
  You can assemble any of them by running either  

    ./monoSystem ../../ProjASMs/(name of assembly).asm  
  
  or  
  
    ./ASM_4380/ASM4380 ../../../ProjASMs/(name of assembly).asm  

  You can then execute the assembled binary by running either  

    ./monoSystem ../../ProjASMs/(name of assembly).bin  

  or  

    ./ASM_4380/ASM4380 ../../../ProjASMs/(name of assembly).bin  
