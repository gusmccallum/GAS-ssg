Gus' Awesome SSG       
#####################################################################################

For contributors:

[Instructions for developing with Windows/Visual Studio]

-Install [clang-format](https://llvm.org/builds/) (add LLVM to PATH) and [Clang Power Tools](https://marketplace.visualstudio.com/items?itemName=caphyon.ClangPowerTools)   
-Run format.bat, tidy.bat and make relevant changes/re-test code before final submission     
-OR import GASClang-settings.json in Clang Power Tools to perform linting and formatting in Visual Studio     
-Compile using c++std=17 in your compiler of choice i.e        
`g++ -std=c++17 gasMain.cpp gasHeader.hpp -o gas`   


For testing:   
-Compile with test.cpp i.e     
`g++ -std=c++17 test.cpp catch.hpp gasHeader.hpp -o gas` 
