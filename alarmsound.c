#include <SDL2/SDL.h>
#include <stdio.h>

// Static variable section
static Uint8 *wav_pos;	// pointer to sound buffer (global)
static Uint32 wav_len;	// sample length (global)

// callback function
// copies data from PCM buffer into the stream
void wav_blit_callback(void *data, Uint8 *stream, int len) {
	if (wav_len != 0) {
		len = (len > wav_len ? wav_len : len);
		SDL_MixAudio(stream, wav_pos, len, SDL_MIX_MAXVOLUME);
		wav_pos += len;
		wav_len -= len;
	}
	return;
}

// function to play sound
int wav_play(char *wavpath) {
	// Initialize SDL
	if(SDL_Init(SDL_INIT_AUDIO) < 0) {
		return 1;
	}
	
	// local variables
	static Uint32 wav_length;
	static Uint8 *wav_buffer;
	static SDL_AudioSpec wav_spec;
	
	/* Load the WAV */
	// the specs, length, and buffer of our wav are filled
	if(SDL_LoadWAV(wavpath, &wav_spec, &wav_buffer, &wav_length) == NULL) {
		return 1;
	}
	// set the callback function
	wav_spec.callback = wav_blit_callback;
	wav_spec.userdata = NULL;
	// set global vars
	wav_pos = wav_buffer;
	wav_len = wav_length;
	// Open the audio device
	if(SDL_OpenAudio(&wav_spec, NULL) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}
	// Start playing
	SDL_PauseAudio(0);
	
	// wait until we're not playing
	while(wav_len > 0) {
		SDL_Delay(100);
	}
	
	// SHUT. DOWN. EVERYTHING!
	SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);
	
	return 0;
}
