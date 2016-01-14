#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "alarmsound.h"

#define WAV_PATH "/home/longlius/BuildDir/test.wav"
#define HOUR 20
#define MIN 25

void signal_handler(int signum) {
	if(signum == SIGINT) {
		exit(0);
	}
}

int main(void) {
	char *wp = WAV_PATH;
	time_t currepochtime;
	struct tm *currlocaltime;
	int currhour, currmin;
	
	// register a signal handler
	if(signal(SIGINT, signal_handler) == SIG_ERR){
		fprintf(stderr, "\ncan't catch SIGINT\n");
	}
	
	while(1) {
		// Get current time in epoch format
		currepochtime = time(NULL);
		// Convert it to formatted local time
		currlocaltime = localtime(&currepochtime);
		// Pull out the values
		currhour = currlocaltime->tm_hour;
		currmin = currlocaltime->tm_min;
		// Check the time
		if((currhour == HOUR) && (currmin == MIN)) {
			while(1) {
				wav_play(wp);
				sleep(5);
			}
		} else {
			sleep(15);
		}
	}
	
	return 0;
}
