
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {

	while (1) {
		wait();
		printf(">");
		char input[1000];

		//getting the input from user
		fgets(input, 1000, stdin);

		//making this empty before using, as there are previous values retaining
		char path[1000] = "";

		//to exit the shell upon exit command
		if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i'
				&& input[3] == 't') {
			printf("Exited.");
			exit(0);
		}

		//checks the spaces and allows any number of spaces before a command and after cd
		if (input[0] == 'c' && input[1] == 'd'
				&& (input[2] == ' ' || input[2] == '\n')) {
			int i, j = 0;

			for (i = 3; i < sizeof(input); i++) {
				if (input[i] == '\0' || input[i] == NULL || input[i] == '\n') {
					//                    printf("null\n");
					break;
				} else if (isspace(input[i])) {
					//                    printf("space");
				} else {
					path[j] = input[i];
					j++;
				}
			}
			//            printf("path:%s\n", &path);

			//if only cd is entered, then it will take home directory path and it will chdir to HOME
			if (strcmp(&path, "") == 0) {
				const char *homedir = getenv("HOME");
				strcpy(path, homedir);
			}

			int t = chdir(&path);

			if (t == 0) {
				printf("Directory change Successful\n");
			} else {
				switch (t) {
				case EACCES:
					perror("Permission Denied");
					break;
				case EIO:
					perror("Input/Output Error");
					break;
				case ENAMETOOLONG:
					perror("Path too long");
					break;
				case ENOTDIR:
					perror("Not a directory");
					break;
				case ENOENT:
					perror("No such file or directory");
					break;
				default:
					perror("Error");
					break;
				}
			}
		} else { //if theres any other command other than cd, the command will be passed through the execv
			pid_t result = fork();

			//child process will enter the if loop and parent process will go to while again
			if (result == 0) {
				char *args[1000];
				args[0] = "/bin/sh";
				args[1] = "-c";
				args[2] = &input[0];
				args[3] = NULL;

				execv("/bin/sh", args);
			}
		}
	}
	return 0;
}
