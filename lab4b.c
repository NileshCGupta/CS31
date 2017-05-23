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
int runflag = 1;
int reportsflag = 1;

int period = 1;
char *logfile;	// name of log file
FILE *log_file;	// log file descriptor
char scale;

char *input;
size_t len = 0;
ssize_t nread;
// STDIN pollfd data
struct pollfd ufd[1];
// Time data
time_t t;
struct tm *tm;

mraa_aio_context temp;
mraa_gpio_context button;

void handler(int signum) 
{
    fprintf(stderr, "Exit program, received signal: %d.\n", signum);
    runflag = 0;
}

void buttonpressed()
{
    printf("%d:%d:%d SHUTDOWN\n", tm->tm_hour, tm->tm_min, tm->tm_sec);

    if(logflag) {
		fprintf(log_file, "%d:%d:%d SHUTDOWN\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
	}

	runflag = 0;
}

void buttonread()
{
	int buttonState = mraa_gpio_read(button);
	// Button has been pressed
	if(buttonState)
		buttonpressed(); // SHUTDOWN
}

void tempread()
{	
    printf("%d:%d:%d ", tm->tm_hour, tm->tm_min, tm->tm_sec);

	uint16_t reading = mraa_aio_read(temp);

	float R = 1023.0/reading - 1.0;
	R = R0 * R;

	float temperature = 1.0/(log(R/R0)/B + 1/298.15) - 273.15;

	// FAHRENHEIT reading
	if(scale == 'F')
		temperature = 1.8 * temperature + 32;

	printf("%2.1f\n", temperature);
	
	if(logflag) {
		fprintf(log_file, "%d:%d:%d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
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
		buttonpressed();
	else if(strcmp(command, stop) == 0)
		reportsflag = 0;
	else if(strcmp(command, start) == 0)
		reportsflag = 1;
	else if(strcmp(command, scalef) == 0)
		scale = 'F';
	else if(strcmp(command, scalec) == 0)
		scale = 'C';
	// else if(strncmp(command, periodn) == 0)
	// {
		
	// }
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

	// Init pollfd
	ufd[0].fd = STDIN;
	ufd[0].events = POLLIN;

    signal(SIGINT, handler);
    int rv;

    t = time(NULL);
	tm = localtime(&t);
	long long currtime_sec = t;
	long long prevtime_sec = currtime_sec - period;

    while(runflag) {
    	buttonread();
    	if(!runflag)
    		break;
    	if(reportsflag & runflag)
    		// Check if prev read was a period or more before the current time
    		if(currtime_sec >= prevtime_sec + period) {
    			prevtime_sec = currtime_sec;
    			tempread();
    		}

    	// Update current time        
        t = time(NULL);
		tm = localtime(&t);
		currtime_sec = t;

        rv = poll(ufd, 1, 0);

        if(rv == -1) 
        	perror("ERROR: Poll");
        else if(rv == 1) {
        	getline(&input, &len, 0); // receive normal data
        	command_handler(input);
        } 
    }
    
    //  Close log file
    if(fclose(log_file)) {
        perror("Cannot close log file\n");
        exit(EXIT_FAILURE);
    }

    mraa_aio_close(temp);
    mraa_gpio_close(button);
	exit(0);
}