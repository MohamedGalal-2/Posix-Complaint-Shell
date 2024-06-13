; AutoIt script to test custom CLI application

; Define the path to your custom CLI executable
Global $CLI_PATH = "E:\\Folder\\Projects\\C Programming\\Posix-Complaint-Shell\\Testing\\Test assets\\Posix-Complaint-Shell.exe"

; Function to run a command in the custom CLI
Func RunCommand($command)
    ; Run the custom CLI
    Local $pid = Run($CLI_PATH, "", @SW_SHOW)
    
    ; Wait for the CLI window to appear
    ; Use the AutoIt Window Info tool to get the correct window title and class
    WinWaitActive("[CLASS:CASCADIA_HOSTING_WINDOW_CLASS]", "", 10) ; Wait for up to 10 seconds for the window to become active

    ; Add debugging messages
    ConsoleWrite("CLI window is active." & @CRLF)

    ; Type the command
    Send($command & "{ENTER}")
    Sleep(250) ; Short delay after sending the command

    ; Wait for the command to execute and capture the output
    Sleep(250) ; Adjust this delay as necessary

    ; Add debugging messages
    ConsoleWrite("Command sent: " & $command & @CRLF)

    ; Capture the output
    Local $output = ""
    Local $line = ""
    For $i = 1 To 10 ; Try to read up to 10 lines of output
        $line = ControlGetText("[CLASS:CASCADIA_HOSTING_WINDOW_CLASS]", "", "")
        If $line <> "" Then
            $output &= $line & @CRLF
        EndIf
        Sleep(200) ; Adjust this delay as necessary
    Next

    ; Add debugging messages
    ConsoleWrite("Output captured: " & $output & @CRLF)

    ; Close the CLI
    ProcessClose($pid)

    ; Return the captured output
    Return $output
EndFunc

; Test commands
Global $testCommands[150] = [ _
    'echo', _
    'echo ', _
    'echo ""', _
    'echo " "', _
    'echo "Hello, World!"', _
    'echo "Special characters: \$%^&"', _
    'echo "Hello, File!" > file.txt', _
    'echo Hello, File! > file2.txt', _
    'cat', _
    'cat ', _
    'cat file.txt', _
    'cat file1.txt > file3.txt', _
    'cat nonexistent_file.txt', _
    'ls', _
    'ls ', _
    'ls ~', _
    'ls "E:\\Folder\\Projects\\C Programming\\Posix-Complaint-Shell\\Source Files"', _
    'ls "E:\\Folder\\Projects\\C Programming\\Posix-Complaint-Shell\\Source Files"', _
    'ls -af "E:\\Folder\\Projects\\C Programming\\Posix-Complaint-Shell\\Source Files"', _
    'ls -af "E:\\Folder\\Projects\\C Programming\\Posix-Complaint-Shell\\Source Files"', _
    'ls -a', _
    'ls -f', _
    'ls -af', _
    '.\\"E:\\Folder\\Projects\\C Programming\\Posix-Complaint-Shell\\Testing\\Test assets\\file.txt"', _
    './file.txt', _
    '.\\"file.txt"', _
    'type ls', _
    'type type echo sss lsss ls cd', _
    'cd', _
    'cd ', _
    'cd "E:\\Folder\\Projects\\C Programming"', _
    'cd "C:/"', _
    'cd "E:/Folder"', _
    'cd "/nonexistent/directory"', _
    'cd "E:\\Folder\\Projects\\C Programming\\Posix-Complaint-Shell\\Testing\\Test assets"', _
    'cd ~', _
    'cd ..', _
    'pwd', _
    'pwd ', _
    'help', _
    'help ls echo', _
	'date', _
    'date "%Y-%m-%d %H:%M:%S"', _
    'date "%Y-%m-%d %H:%M"', _
    'date "%m-%d-%Y %H:%M:%S"', _
    'clear', _
    'clear sss', _
    'grep', _
    'grep test grepTest', _
    'grep test grepTest.txt', _
    'grep -i test grepTest.txt', _
    'grep -v test grepTest.txt', _
    'grep -c test grepTest.txt', _
    'grep -l test grepTest.txt', _
    'grep -n test grepTest.txt', _
    'grep -w test grepTest.txt', _
    'grep -o test grepTest.txt', _
    'mkdir', _
    'mkdir Test 1', _
    'mkdir "E:\Folder\Projects\C Programming\Posix-Complaint-Shell\Testing\Test 2"', _
    'mkdir ..\Hello', _
    'mkdir ../../Hello', _
    'mkdir "   test 3"', _
    'mkdir    Test 4', _
    'mkdir    "    Test 5"', _
    'rmdir', _
    'rmdir Test 1', _
    'rmdir "E:\Folder\Projects\C Programming\Posix-Complaint-Shell\Testing\Test 2"', _
    'rmdir ..\Hello', _
    'rmdir ../../Hello', _
    'rmdir "   test 3"', _
    'rmdir    Test 4', _
    'rmdir    "    Test 5"', _
    'help', _
    'help ls echo', _
    'exit 0', _
	'exit', _
	'exit 1' _
]

; Execute each test command
For $i = 0 To UBound($testCommands) - 1
    Local $command = $testCommands[$i]
    ConsoleWrite("Executing command: " & $command & @CRLF)
    Local $output = RunCommand($command)
    ConsoleWrite("Output: " & @CRLF & $output & @CRLF & @CRLF)

    ; Stop condition: Check if the window is still active or timeout
    If Not WinExists("[CLASS:CASCADIA_HOSTING_WINDOW_CLASS]") Then
        ConsoleWrite("CLI window no longer exists. Stopping script." & @CRLF)
        ExitLoop
    EndIf
Next

; Add a message box or a console write to indicate the script has finished
ConsoleWrite("Script finished executing." & @CRLF)
MsgBox(0, "Info", "Script finished executing.")