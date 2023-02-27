#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void collatz(int);

// The main function takes a starting number as a command line argument, forks a child process to generate
// the Collatz sequence, and waits for the child to complete before exiting.
int main(int argc, char * argv[])
{
	// Check that the program was invoked with only one argument
	if (argc != 2) {
		printf("Usage: %s <starting_number>\n", argv[0]);
		return 1;
	}

	// Convert the starting number from a string to an integer
	int n = atoi(argv[1]);

	// Validate that the starting number is positive
	if (n <= 0){
		printf("Starting point must be a positive integer.\n");
		return 1;
	}
	
	// Fork the process to create a child
	pid_t pid = fork();

	if(pid < 0){
		// If the fork failed, print an error message and exit with a non-zero exit code
		printf("Fork failed.\n");
		return 1;
	} else if (pid == 0) {
		// If the pid is zero, we are in the child process
		collatz(n);
	} else {
		// If the pid is greater than zero, we are in the parent process
		wait(NULL); // Wait for the child process to complete
	}

	return 0;
}

// This function implements the Collatz conjecture algorithm
void collatz(int n)
{
	// Print the starting number
	printf("%d ", n);

	// Generate the Collatz sequence
	while (n != 1){
		if(n % 2 == 0) {
			n = n / 2;
		} else {
			n = 3 * n + 1;
		}
		printf("%d ", n);
	}

	// Print a newline character to separate output from different runs 
	printf("\n");
}
