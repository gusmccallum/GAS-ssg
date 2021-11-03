# GAS-ssg
 Gus' Awesome SSG


Instructions: 

-Run with command line options:
   
   -i or --input to specify a file or folder to be converted
    i.e "gas -i ./folder" OR "gas --input abacus.txt"
    
    -c or --config to set a config.json file with input and (optional) output folders
    i.e "gas -c ssg-config.json" 
    
   -h or --help to get info on command line arguments possible
    i.e "gas -h"
    
   -v or --version to get version information
    i.e "gas -v"
    
-Will convert any txt or md files to html or recursively search through folders to find txt/md files to convert to html (Optional feature 1)
-Files will be placed in ./dist/ folder, will overwrite existing ./dist/ folder
-Title will be generated if first line is followed by two blank lines (Optional feature 2)
-If file is markdown file, "# " syntax will turn line into a \<h1>
