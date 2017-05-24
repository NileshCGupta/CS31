#include <inttypes.h>
#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <poll.h>
#include <string.h>

#include <mraa/aio.h>
#include <mraa/i2c.h>

const int B = 4275;
const int R0 = 100000;
// const int pinTempSensor = A0;

int logflag = 0;
int runflag = 1;		// run sensors in while loop
int reportsflag = 1;	// generate time + temp reports

int period = 1;
char *logfile;	// name of log file
FILE *log_file;	// log file stream
char scale;		// Celsius / Farenheit measure

char *input = NULL;		// buffer for input commands
size_t len = 0;
ssize_t nread;
// STDIN pollfd data
struct pollfd ufd[1];
// Time data
time_t t;
struct tm *tm;
// Temperature / Button contexts
mraa_aio_context temp;
mraa_gpio_context button;

// Close open files & sensors
void close_opens()
{
	//  Close log file
    if(fclose(log_file)) {
        perror("Cannot close log file\n");
        exit(EXIT_FAILURE);
    }

	mraa_aio_close(temp);
    mraa_gpio_close(button);
}

void handler(int signum) 
{
    fprintf(stderr, "Exit program, received signal: %d.\n", signum);
    close_opens();
    exit(0);
}

void buttonpressed()
{
	// No SHUTDOWN message to stdout
    // printf("%02d:%02d:%02d SHUTDOWN\n", tm->tm_hour, tm->tm_min, tm->tm_sec); 

    if(logflag) {
		fprintf(log_file, "%02d:%02d:%02d SHUTDOWN\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
	}

	close_opens();
	exit(0);
}

void buttonread()
{
	int buttonState = mraa_gpio_read(button);
	// Button has been pressed
	if(buttonState == -1) {
		perror("ERROR: Button");
		exit(EXIT_FAILURE);
	}
	else if(buttonState)
		buttonpressed(); // SHUTDOWN
}

void tempread()
{	
    printf("%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);

	uint16_t reading = mraa_aio_read(temp);

	float R = 1023.0/reading - 1.0;
	R = R0 * R;

	float temperature = 1.0/(log(R/R0)/B + 1/298.15) - 273.15;

	// FAHRENHEIT reading
	if(scale == 'F')
		temperature = 1.8 * temperature + 32;

	printf("%2.1f\n", temperature);
	
	if(logflag) {
		fprintf(log_file, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
		fprintf(log_file, "%2.1f\n", temperature);
	}
}

void command_handler(char* command)
{
	char* off = "OFF";
	char* stop = "STOP";
	char* start = "START";
	char* scalef = "SCALE=F";
	char* scalec = "SCALE=C";
	char* periodn = "PERIOD=";

	if(strcmp(command, off) == 0)
		buttonpressed();	// OFF command is equal to the button being pressed
	else if(strcmp(command, stop) == 0)
		reportsflag = 0;
	else if(strcmp(command, start) == 0)
		reportsflag = 1;
	else if(strcmp(command, scalef) == 0)
		scale = 'F';
	else if(strcmp(command, scalec) == 0)	
		scale = 'C';
	else if(strncmp(command, periodn, 7) == 0)	// Only campare up to 'PERIOD='
		period = atoi(command + 7);				// Get period argument
}

int main(int argc, char** argv)
{
	int opt = 0;

	static struct option long_opts[] =
	{
		{"period", required_argument, 0, 'p'},
		{"scale", required_argument, 0, 's'},
		{"log", required_argument, 0, 'l'},
		{0, 0, 0, 0}
	};

	while((opt = getopt_long(argc,argv,"p:s:l:",long_opts,NULL)) != -1)
	{
		switch(opt)
		{
			case 'p':
				period = atoi(optarg);
				break;

			case 's':
				if(optarg[0] != 'C' && optarg[0] != 'F') {
					perror("ERROR: Bad scale argument");
					exit(EXIT_FAILURE);
				}
				scale = optarg[0];
				break;

			case 'l':
				logflag = 1;
				logfile = optarg;
				break;

			default:
				fprintf(stderr, "Unrecognized argument\n");
				exit(1);
		}
	}

	if(logflag) {
		log_file = fopen(logfile, "w");
		if(log_file == NULL) {
			perror("Could not open log file\n"); 
			exit(1); 
		}
	}

	setenv("TZ", "PST8PDT", 1);
    tzset();

	// Init MRAA temperature & button contexts
	temp = mraa_aio_init(0);
	button = mraa_gpio_init(3);
	if(temp == NULL) { perror("ERROR: Cannot initialize MRAA temp context"); exit(EXIT_FAILURE); }
	if(button == NULL) { perror("ERROR: Cannot initialize MRAA button context"); exit(EXIT_FAILURE); }
	mraa_gpio_dir(button, MRAA_GPIO_IN);

	// Init pollfd for input from stdin stream
	ufd[0].fd = 0;
	ufd[0].events = POLLIN;

    signal(SIGINT, handler);
    signal(SIGSEGV, handler);
    int rv;

    t = time(NULL);
	tm = localtime(&t);
	long long currtime_sec = t;
	long long prevtime_sec = currtime_sec - period;	// runs at least once; equivalent to 'do while'

	// Main work loop
    while(runflag) {
    	// Read button
    	buttonread();
    	// If button was pressed, then runflag was changed
    	if(!runflag)
    		break;
    	if(reportsflag)
    		// Check if prev read was a period or more before the current time
    		if(currtime_sec >= prevtime_sec + period) {
    			prevtime_sec = currtime_sec;
    			tempread();
    		}

    	// Update current time        
        t = time(NULL);
		tm = localtime(&t);
		currtime_sec = t;

		// Poll for potential user input
        rv = poll(ufd, 1, 100);

        if(rv == -1) 
        	perror("ERROR: Poll");
        else if(rv == 1) {
        	if(ufd[0].revents & POLLIN) {
        		if(getline(&input, &len, stdin) == 0) { perror("ERROR: getline"); 
        												exit(EXIT_FAILURE); }
        		if(logflag)
        			fprintf(log_file, "%s", input);		// append command to logfile
        		strtok(input, "\n");		// remove newline char for strcmp purposes
        		command_handler(input);
        	}
        } 
    }

    // Close sensors and logfile & return
    close_opens();
	exit(0);
}