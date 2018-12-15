Goal:
To simulate linux shell using c systemcalls

Implementation:
We used a c program to make use of system call execv to take commands from user and run it in the program output simulating the linux shell commands


Major Features:
- Chdir errors
- Any amount of spaces between cd and arguments
- Exit command

Program Explanation:
- the user input will be stored in input variable.
- We use fork at first as it will create a child process from that place
- This fork command will be useful when we run the execv command, as it will replace the whole program with the execv output result.
- In the program we used a for loop to find the number of arguments passed and we are splitting accordingly
- If the argument is related to cd
- Then it goes to another loop
- In the cd loop,
    - If only cd is given then it will take the src of HOME and will change directory to that.
    - If cd has any other parameters appending to that, then that will be passed to the chdir, where it will change the present working directory
    - All this is pleased above the fork command as cd should work to parent and child as well.
    - The cd is designed in such a way that any number of spaces can be given between any commands
    - We also added error detection where if the chdir fails, it shows the appropriate command.
- And in the other loop
    - We take the arguments and we pass them along to the execv command.
- The child process will end in the if(fork 0) as the child will go to that only and then the parent will continue to the while loop

How to run:
- Execute the program.
- Now you can use exactly all the shell commands
- e.g.: ls
- You can even change the directory
- e.g. ‘cd’ ‘cd ..’ ‘cd .’ ‘cd /‘ ‘cd Hello’
- And in the changed directory also, all the commands work swell
- If you want to execute form the shell, just like a Nepal shell run the exit command.
