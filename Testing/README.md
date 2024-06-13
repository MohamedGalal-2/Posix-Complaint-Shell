# TEST CASES

## Command Execution:

1. **echo command**:
   ```bash
   echo
   echo              
   echo ""
   echo " "
   echo "Hello, World!"
   echo "Special characters: \$%^&"
   echo Special characters: \$%^&
   echo "Hello, File!" > file.txt
   echo Hello, File! > file2.txt
   ```
 
2. **cat command**:
   ```bash
   cat
   cat 
   cat file.txt
   cat file1.txt > file3.txt
   cat nonexistent_file.txt
   ```

3. **ls command**:
   ```bash
   ls
   ls 
   ls ~
   ls E:\Folder\Projects\C Programming\Posix-Complaint-Shell\Source Files
   ls "E:\Folder\Projects\C Programming\Posix-Complaint-Shell\Source Files"
   ls -af E:\Folder\Projects\C Programming\Posix-Complaint-Shell\Source Files
   ls -af "E:\Folder\Projects\C Programming\Posix-Complaint-Shell\Source Files"
   ls -a
   ls -f
   ls -af
   ```

4. **execute_script command**:
   ```bash
   ./file.txt
   ./"file.txt"
   .\file.txt
   .\"file.txt"
   ```

5. **type command**:
   ```bash
   type ls
   type type echo sss lsss ls cd  
   ```

6. **cd command**:
   ```bash
   cd
   cd 
   cd "E:\Folder\Projects\C Programming"
   cd "E:\\Folder\Projects/C Programming"
   cd "C:/"
   cd "E:/Folder"
   cd "/nonexistent/directory"
   cd "E:\Folder\Projects\C Programming\Posix-Complaint-Shell\Testing\Test assets"
   cd ~\Videos\\\\\\
   cd       ~/Videos
   cd       "     ~\Videos\\"
   cd ~
   cd ..
   cd ../Testing
   cd ..
   cd ./Testing
   ```

7. **pwd command**:
   ```bash
   pwd
   pwd 
   ```

8. **date command**:
   ```bash
   date
   date 
   date "%Y-%m-%d %H:%M:%S"
   date "%Y-%m-%d %H:%M"
   date "%m-%d-%Y %H:%M:%S" 
   ```

9. **clear command**:
   ```bash
   clear
   clear 
   clear sss
   ```

10. **grep command**:
   ```bash
   grep
   grep 
   grep test grepTest
   grep test grepTest.txt
   grep -i test grepTest.txt
   grep -v test grepTest.txt
   grep -c test grepTest.txt
   grep -l test grepTest.txt
   grep -n test grepTest.txt
   grep -w test grepTest.txt
   grep -o test grepTest.txt
   ```

11. **mkdir command**:
   ```bash
   mkdir
   mkdir            
   mkdir Test 1
   mkdir "E:\Folder\Projects\C Programming\Posix-Complaint-Shell\Testing\Test 2"
   mkdir ..\Hello
   mkdir ../../Hello
   ls "E:\Folder\Projects\C Programming\Posix-Complaint-Shell\Testing"
   mkdir "   test 3"
   mkdir    Test 4 
   mkdir    "    Test 5"
   ```

12. **rmdir command**:
   ```bash
   rmdir
   rmdir            
   rmdir Test 1
   rmdir "E:\Folder\Projects\C Programming\Posix-Complaint-Shell\Testing\Test 2"
   rmdir ..\Hello
   rmdir ../../Hello
   ls "E:\Folder\Projects\C Programming\Posix-Complaint-Shell\Testing"
   rmdir "   test 3"
   rmdir    Test 4 
   rmdir    "    Test 5"
   ```

13. **help command**:
   ```bash
   help
   help ls echo 
   ```

14. **exit command**:
   ```bash
   exit
   exit 1
   ```

### Shell Behavior:

15. **Shell Startup**:
    ```bash
    ./Posix-Complaint-Shell
    ```

16. **Input and Output Redirection**:
    ```bash
    cat file.txt > output.txt
    cat input.txt
    echo "Append" >> output.txt
    ```

17. **Sequence Commands**:
    ```bash
    ls ; grep file
    ```

### Error Handling:

18. **Error Handling**:
    ```bash
    invalid_command
    ls -z
    cat
    ```

### Edge Cases:

19. **Edge Cases**:
    ```bash
    command_with_extremely_long_arguments_sooooooooooooooooooooooooooooooooooooo_looooooooooooong sooooooooooooooooooooooooooooooooooooo_looooooooooooongsssssssssssssssssssssss
    command with special characters//#@!#$%
    command with spaces
    
    ```

### Miscellaneous:

20. **User Interaction**:
    - Test user input and output interactions manually.

These commands cover various scenarios and test cases for each function in the POSIX-compliant shell. You can run these commands in the POSIX terminal to validate the behavior of the implementation.