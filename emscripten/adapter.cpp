/*
* This file adapts  "m_s98.kpi v1.0r8 by Mamiya"  to the interface expected by my generic JavaScript player.
*
* Copyright (C) 2018 Juergen Wothke
*
*
* Credits:   
* 
* The project is based on: http://www.vesta.dti.ne.jp/~tsato/soft_s98v3.html (by Mamiya, et al.)
* FM Sound Generator rel.008 (C) cisc 1998-2003. 
* emu2413 by Mitsutaka Okazaki 2001-2004
* zlib (C) 1995-2005 Jean-loup Gailly and Mark Adler
*
* Notes:
* 
* The sources currently available (above link or also the link here: http://www.purose.net/befis/download/lib/t98/ins98131s.zip
* all seem to point to outdated old versions and also the KBMediaPlayer plugin sources that I used here
* to NOT even match the plugin-binary that is provided on the same page: These sources doesn't compile before fixing a non existing
* enum reference. The sources date from 2006/10/19 whereas there has been some update of the winamp sources on 2011/05/31 -
* in case that update made any improvements on the emulator then these unfortunately will not be reflected here.
*
* License:
*
* NOT GPL: The code builds on FM Sound Generator with OPN/OPM interface Copyright (C) by cisc 1998, 2003.
* As the author of FM Sound Generator states, this is free software but for any commercial application
* the prior consent of the author is explicitly required. 
* The same licence is here extended to any of the add-ons that are part of this project.
*/

#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>     

#include <iostream>
#include <fstream>

#include "s98types.h"
#include <m_s98.h>


#ifdef EMSCRIPTEN
#define EMSCRIPTEN_KEEPALIVE __attribute__((used))
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

static const std::string chars = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
std::string base64_encode(unsigned char* input, unsigned int len) {
  int i, j = 0;
  unsigned char arr3[3];
  unsigned char arr4[4];
  std::string ret;
  
  while (len--) {
    arr3[i++] = *(input++);
    if (i == 3) {
      arr4[0] = (arr3[0] & 0xfc) >> 2;
      arr4[1] = ((arr3[0] & 0x03) << 4) + ((arr3[1] & 0xf0) >> 4);
      arr4[2] = ((arr3[1] & 0x0f) << 2) + ((arr3[2] & 0xc0) >> 6);
      arr4[3] = arr3[2] & 0x3f;

      for(i = 0; (i <4) ; i++) {
        ret += chars[arr4[i]];
		}
      i = 0;
    }
  }
  if (i) {
    for(j = i; j < 3; j++) {
      arr3[j] = '\0';
	}
    arr4[0] = ( arr3[0] & 0xfc) >> 2;
    arr4[1] = ((arr3[0] & 0x03) << 4) + ((arr3[1] & 0xf0) >> 4);
    arr4[2] = ((arr3[1] & 0x0f) << 2) + ((arr3[2] & 0xc0) >> 6);

    for (j = 0; (j < i + 1); j++) {
      ret += chars[arr4[j]];
	}
    while((i++ < 3)) {
      ret += '=';
	}
  }
  return ret;
}



char *getEmscriptenRhythmPath() {
	return "/";	// placeholder in case this is actually needed..
}

#define CHANNELS 2				
#define BYTES_PER_SAMPLE 2
#define SAMPLE_BUF_SIZE	1024
#define SAMPLE_FREQ	44100


Int16 sample_buffer[SAMPLE_BUF_SIZE * CHANNELS];
int samples_available= 0;

char* info_texts[9];


#define TEXT_MAX	255
char title_str[TEXT_MAX];
char artist_str[TEXT_MAX];
char game_str[TEXT_MAX];
char year_str[TEXT_MAX];
char genre_str[TEXT_MAX];
char comment_str[TEXT_MAX];
char copyright_str[TEXT_MAX];
char s98by_str[TEXT_MAX];
char system_str[TEXT_MAX];

#define RAW_INFO_MAX	1024
char raw_info_buffer[RAW_INFO_MAX];

struct StaticBlock {
    StaticBlock(){
		info_texts[0]= title_str;
		info_texts[1]= artist_str;
		info_texts[2]= game_str;
		info_texts[3]= year_str;
		info_texts[4]= genre_str;
		info_texts[5]= comment_str;
		info_texts[6]= copyright_str;
		info_texts[7]= s98by_str;
		info_texts[8]= system_str;
    }
};

static StaticBlock g_emscripen_info;

unsigned char* buffer_copy= NULL;

void trash_buffer_copy() {
	if (buffer_copy) {
		free(buffer_copy);
		buffer_copy= NULL;		
	}
}

unsigned char * get_buffer_copy(const void * inBuffer, size_t inBufSize) {
	trash_buffer_copy();
	
	buffer_copy= (unsigned char*)malloc(inBufSize);
	memcpy ( buffer_copy, inBuffer, inBufSize );
	return buffer_copy;
}

// now to the S98 stuff:
SOUNDINFO g_soundinfo;
s98File *g_s98 = 0;
int g_loop_detected= 0;


extern "C" void emu_teardown (void)  __attribute__((noinline));
extern "C" void EMSCRIPTEN_KEEPALIVE emu_teardown (void) {
	trash_buffer_copy();
			
	memset(&g_soundinfo, 0, sizeof(SOUNDINFO));
	
	title_str[0]= artist_str[0]= game_str[0]= year_str[0]= 
		genre_str[0]= comment_str[0]= copyright_str[0]= 
		s98by_str[0]= system_str[0] = 0;
	
	g_loop_detected= 0;
	
	if (g_s98) {
		delete g_s98;
		g_s98= 0;
	}
}

// C/C++ crap: when inlining this code directly within the below 'extern "C"' functions
// then the passed arguments will be total garbage... when they get to the invoked 
// C++ functions.. (e.g. the "void *inBuffer" for OpenFromBuffer)
int loadBuffer(void *inBuffer, uint32_t inBufSize ) {
	// Emscripten passes its original cached data -- so we better use a copy..
	inBuffer= get_buffer_copy(inBuffer, inBufSize);

	g_s98= new s98File();
	g_soundinfo.dwSamplesPerSec= SAMPLE_FREQ;

	return g_s98->OpenFromBuffer((unsigned char *)inBuffer, inBufSize, &g_soundinfo);
}

std::string stringToUpper(std::string strToConvert) {
    std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

    return strToConvert;
}
void extractFromInfoLine(std::string line) {
	std::string delimiter = "=";

	size_t pos = 0;
	if ((pos= line.find(delimiter)) != std::string::npos) {
		std::string key = stringToUpper(line.substr(0, pos));
		std::string value = line.substr(pos+1, line.length());
		
		// seems the "garbage" is actually unicode chars.. 
		// unless everthing is encoded there is no chance of
		// getting it uncorrupted to the rendering...
		value = base64_encode((unsigned char*)value.c_str(), value.length());
		
		if (!key.compare("TITLE")) {
			snprintf(title_str, TEXT_MAX, "%s", value.c_str());	
		} else if (!key.compare("ARTIST")) {
			snprintf(artist_str, TEXT_MAX, "%s", value.c_str());	
		} else if (!key.compare("GAME")) {
			snprintf(game_str, TEXT_MAX, "%s", value.c_str());	
		} else if (!key.compare("YEAR")) {
			snprintf(year_str, TEXT_MAX, "%s", value.c_str());	
		} else if (!key.compare("GENRE")) {
			snprintf(genre_str, TEXT_MAX, "%s", value.c_str());	
		} else if (!key.compare("COMMENT")) {
			snprintf(comment_str, TEXT_MAX, "%s", value.c_str());	
		} else if (!key.compare("COPYRIGHT")) {
			snprintf(copyright_str, TEXT_MAX, "%s", value.c_str());	
		} else if (!key.compare("S98BY")) {
			snprintf(s98by_str, TEXT_MAX, "%s", value.c_str());	
		} else if (!key.compare("SYSTEM")) {
			snprintf(system_str, TEXT_MAX, "%s", value.c_str());	
		}  
	} else {
		fprintf(stderr, "garbage info: [%s]\n", line.c_str());
	}
}

void extractStructFileInfo(char *filename) {
	g_s98->getRawFileInfo((unsigned char*)raw_info_buffer, TEXT_MAX, 0);	// !g_soundinfo.dwIsV3
	if (strlen(raw_info_buffer) == 0) {
		// fallback: just use the filename
		std::string title= filename;
		title.erase( title.find_last_of( '.' ) );	// remove ext
		snprintf(title_str, TEXT_MAX, "%s", title.c_str());	
	} else {
		/*
		note: V3 files contain tagged info, e.g.
		[S98]
		"title=Opening" 0x0a
		"artist=Yuzo Koshiro" 0x0a
		"game=Sorcerian" 0x0a
		"year=1987" 0x0a
		"genre=game" 0x0a
		"comment=This is sample data." 0x0a
		"copyright=Nihon Falcom" 0x0a
		"s98by=foo" 0x0a
		"system=PC-8801" 0x0a
		*/	
		const char *pfx= "[S98]";
		int hasPrefix= !strncmp(raw_info_buffer, pfx, strlen(pfx));
		
		if (hasPrefix || g_soundinfo.dwIsV3) {
			std::string s= std::string(raw_info_buffer + (hasPrefix?strlen(pfx):0));

			std::string delimiter(1, (char)0xa);

			size_t pos = 0;
			std::string token;
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				extractFromInfoLine(token);
				s.erase(0, pos + delimiter.length());
			}
		} else {
			// some older format
			std::string in= raw_info_buffer;
			size_t p= in.find("Copyright");	// some contain this.. 
			
			if (p == std::string::npos) {
				// give up
				in = base64_encode((unsigned char*)in.c_str(), in.length());				
				snprintf(title_str, TEXT_MAX, "%s", in.c_str());	
			} else {
				// just split 2 sections
				const char *str= in.c_str();
				
				std::string encTitle = in.substr (0, p);
				encTitle= base64_encode((unsigned char*)encTitle.c_str(), encTitle.length());
				snprintf(title_str, TEXT_MAX, "%s", encTitle.c_str());

				std::string encCopRigt = std::string(str + p);
				encCopRigt= base64_encode((unsigned char*)encCopRigt.c_str(), encCopRigt.length());
				snprintf(copyright_str, TEXT_MAX, "%s", encCopRigt.c_str());	
			}			
		}		
	}
}

int computeSamples() {
	if (g_loop_detected) return 1;
	
	samples_available = g_s98->Write((Int16 *)sample_buffer, SAMPLE_BUF_SIZE / 4) ;	
	return 0;
}

extern "C"  int emu_load_file(char *filename, void * inBuffer, uint32_t inBufSize)  __attribute__((noinline));
extern "C"  int EMSCRIPTEN_KEEPALIVE emu_load_file(char *filename, void * inBuffer, uint32_t inBufSize) {
	emu_teardown();

	if (!loadBuffer(inBuffer, inBufSize)) {
		// error
		return 1;
	} else {
		// success 
		extractStructFileInfo(filename);		
		return 0;					
	}
}

extern "C" int emu_get_sample_rate() __attribute__((noinline));
extern "C" EMSCRIPTEN_KEEPALIVE int emu_get_sample_rate()
{
	return g_soundinfo.dwSamplesPerSec;
}
 
extern "C" int emu_set_subsong(int subsong, unsigned char boost) __attribute__((noinline));
extern "C" int EMSCRIPTEN_KEEPALIVE emu_set_subsong(int track, unsigned char boost) {
	// there are no subsongs...
	return 0;
}

extern "C" const char** emu_get_track_info() __attribute__((noinline));
extern "C" const char** EMSCRIPTEN_KEEPALIVE emu_get_track_info() {
	return (const char**)info_texts;
}

extern "C" char* EMSCRIPTEN_KEEPALIVE emu_get_audio_buffer(void) __attribute__((noinline));
extern "C" char* EMSCRIPTEN_KEEPALIVE emu_get_audio_buffer(void) {
	return (char*)sample_buffer;
}

extern "C" long EMSCRIPTEN_KEEPALIVE emu_get_audio_buffer_length(void) __attribute__((noinline));
extern "C" long EMSCRIPTEN_KEEPALIVE emu_get_audio_buffer_length(void) {
	return samples_available;
}


extern "C" int emu_compute_audio_samples() __attribute__((noinline));
extern "C" int EMSCRIPTEN_KEEPALIVE emu_compute_audio_samples() {
	return computeSamples();
}

extern "C" int emu_get_current_position() __attribute__((noinline));
extern "C" int EMSCRIPTEN_KEEPALIVE emu_get_current_position() {
	if (g_s98->GetPosition() > g_soundinfo.dwLength) {
		g_loop_detected = 1;
	}
	return g_s98->GetPosition() % g_soundinfo.dwLength;
}

extern "C" void emu_seek_position(int pos) __attribute__((noinline));
extern "C" void EMSCRIPTEN_KEEPALIVE emu_seek_position(int frames) {
	g_s98->SetPosition(frames);
}

extern "C" int emu_get_max_position() __attribute__((noinline));
extern "C" int EMSCRIPTEN_KEEPALIVE emu_get_max_position() {
	return g_soundinfo.dwSeekable ? g_soundinfo.dwLength : -1;
}

