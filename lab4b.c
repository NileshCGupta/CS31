#include <inttypes.h>
#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <poll.h>

#include <mraa/aio.h>
#include <mraa/i2c.h>

const int B = 4275;
const int R0 = 100000;
// const int pinTempSensor = A0;

int logflag = 0;
int runflag = 1;

int period = 1;
char *logfile;
char scale;

char buff[10];
// STDIN pollfd data
struct pollfd ufd[1];
ufd[0].fd = 0;
ufd[0].events = POLLIN;

mraa_aio_context temp;

void handler(int signum) 
{
    fprintf(stderr, "Exit program, received signal: %d.\n", signum);
    runflag = 0;
}

// void command_handler(char[] command)
// {
// 	switch(command)
// 	{
// 		case "OFF":
// 			break;
// 		case "STOP":
// 			break;
// 		case "START":
// 			break;
// 		case "SCALE=F":
// 			break;
// 		case "SCALE=C":
// 			break;
// 		case "PERIOD="
// 	}
// }

void tempread()
{
	time_t t = time(NULL);

	uint16_t reading = mraa_aio_read(temp);

	// int reading = analogRead(0);

	float R = 1023.0/reading - 1.0;
	R = R0 * R;

	float temperature = 1.0/(log(R/R0)/B + 1/298.15) - 273.15;

	// FAHRENHEIT reading
	if(scale == 'F')
		temperature = 1.8 * temperature + 32;

	printf("temperature = %2.1f\n", temperature);
	
	if(logflag)
		printf(logfile, "temperature = %2.1f", temperature);
}

int main(int argc, char** argv)
{
	int opt = 0;
	FILE *log_file;

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
				scale = *optarg;
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

	// Init MRAA temperature context
	temp = mraa_aio_init(0);
	// if(temp == NULL) { perror("ERROR: Cannot initialize MRAA context"); exit(EXIT_FAILURE); }

    signal(SIGINT, handler);

    int rv;

    while(runflag) {
        tempread();
        rv = poll(ufd, 1, 500);

        if(rv == -1) 
        	perror("ERROR: Poll");
        else if(rv == 0)
        	printf("Timeout occured! No data received");
        else {
        	recv(s1, buff, sizeof(buff), 0); // receive normal data
        	command_handler(buff);
        }

        sleep(period);
    }
    
    //  Close log file
    if(fclose(log_file)) {
        perror("Cannot close log file\n");
        exit(EXIT_FAILURE);
    }

    mraa_aio_close(temp);
	exit(0);
}

// #include "mraa/aio.h"

// int
// main()
// {
//     mraa_aio_context adc_a0;
//     uint16_t adc_value = 0;
//     float adc_value_float = 0.0;
//     adc_a0 = mraa_aio_init(0);
//     if (adc_a0 == NULL) {
//         return 1;
//     }
//     for (;;) {
//         adc_value = mraa_aio_read(adc_a0);
//         adc_value_float = mraa_aio_read_float(adc_a0);
//         fprintf(stdout, "ADC A0 read %X - %d\n", adc_value, adc_value);
//         fprintf(stdout, "ADC A0 read float - %.5f\n", adc_value_float);
//     }
//     mraa_aio_close(adc_a0);
//     return MRAA_SUCCESS;
// }