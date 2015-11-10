#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

#define BUFSIZE 1024
#define BUFFSIZE 64
#define DELIM " \t\r\n\a"

int main(int argc, char **argv){
	loop();
	return EXIT_SUCCESS;
}

void loop(void){
	char *line;
	char **arg;
	int status;

	do{
		printf("> ");
		line = read_line();
		arg = split_line(line);
		status = execute(arg);

		free(line);
		free(arg);
	}
	while(status);
}

char *read_line(void){
	int bufsize = BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	if(!buffer){
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	while(1){
		c = getchar();
		if (c == EOF || c == '\n'){
			buffer[position] = '\0';
			return buffer;
		}
		else {
			buffer[position] = c;
		}
		position++;

		if (position >= bufsize){
			bufsize+= BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer){
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char **split_line(char *line){
	int bufsize = BUFFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if(!tokens){
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILRE);
	}
	token = strtok(line, DELIM);
	while(token != NULL){
		tokens[position] = token;
		position++;

		if (position >= bufsize){
			bufsize += BUFFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if(!tokens){
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

int launch(char **arg){
	pid_t pid1, pid2;
	int status;
	pid1 = fork();
	if(pid1 == 0){
		if(execvp(arg[0], arg) == -1){
			perror("lsh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid1 <  0){
		perror("lsh");
	}
	else{
		do{
			pid2 = waitpid1(pid1, &status, WUNTRACED);
		}
		while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

int cd(char **arg);
int help(char **arg);
int exit(char **arg);
char *builtin_str[] = {
	"cd",
	"help",
	"exit"
};
int (*builtin_func[]) (char **) = {
	&cd,
	&help,
	&exit
};

int num_builtin(){
	return sizeof(builtin_str) / sizeof(char*);
}

int cd(char **arg){
	if (arg[1] == NULL) {
		fprintf(stderr, "lsh: expected argument to \"cd\"\n");
	}
	else{
		if (chdir(arg[1] != 0){
			perror("lsh");
		}
	}
	return 1;
}

int help(char **arg){
	int i;
	for (i=0; i<num_builtin(); i++){
		printf(" %s\n", builtin_str[i]);
	}
	printf("Use the man command for information on other program\n);
	return 1;
}

int exit(char **arg){
	return 0;
}

int execute(char **arg){
	int i;
	if (arg[0] == NULL) {
		return 1;
	}
	for (i=0; i<num_builtin(); i++){
		if(strcmp(arg[0], builtin_str[i]) == 0){
			return (*builtin_func[i](arg);
		}
	}
	return launch(arg);
}
