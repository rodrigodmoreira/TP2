/*
*     Importante: caso de erro, reformatar .wav exportando pelo audacity (wav 16bits - formato suportado pelo código)
*				  caso atenuação não ocorra, checar se o arquivo de audio é "mono" e não stereo - openAL só atenua quando se tem um unico canal
*/

#include <bits/stdc++.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
 
using namespace std;

/*
 * ALboolean LoadALData()
 *
 *         This function will load our sample data from the disk using the Alut
 *         utility and send the data into OpenAL as a buffer.
 */
ALboolean loadALData(ALuint &Buffer,char *audio_adress)
{
    // Variables to load into.
    ALenum format;
    ALsizei size;
    ALvoid* data;
    ALsizei freq;
    ALboolean loop;

    // Load wav data into a buffer.
    alGenBuffers(1, &Buffer);

		// Check error generating a buffer
    if(alGetError() != AL_NO_ERROR)
                return AL_FALSE;

	// Load your wav song here
    alutLoadWAVFile((ALbyte *)audio_adress, &format, &data, &size, &freq, &loop);
    alBufferData(Buffer, format, data, size, freq);
    alutUnloadWAV(format, data, size, freq);

    return AL_TRUE;
}

/*
 * ALboolean BindALData()
 *
 *         This function will bind our sample data from the buffer previously loaded
 *         to a source previously defined.
 */
ALboolean bindALData(ALuint &Buffer, ALuint &Source, ALfloat *SourcePos, ALfloat *SourceVel, ALboolean loop)
{
	// Bind the buffer with the source.
        alGenSources(1, &Source);

        if(alGetError() != AL_NO_ERROR)
                    return AL_FALSE;

        alSourcei (Source, AL_BUFFER,   Buffer   );	// Indicar qual o buffer a ser "bindado"
        alSourcef (Source, AL_PITCH,    1.0      );	// Tom do som
        alSourcef (Source, AL_GAIN,     1.0      ); // Ganho/volume
		alSourcef (Source, AL_ROLLOFF_FACTOR, 1 );
		alSourcef (Source, AL_REFERENCE_DISTANCE, 50.0 );
		alSourcef (Source, AL_MAX_DISTANCE, 400.0 );
        alSourcefv(Source, AL_POSITION, SourcePos);	// Posição da fonte no mundo
        alSourcefv(Source, AL_VELOCITY, SourceVel);	// Velocidade da fonte - Doppler manda abraços
        alSourcei (Source, AL_LOOPING,  loop 	 );	// Definir se realiza loop ou não

    // Do another error check and return.
        if(alGetError() == AL_NO_ERROR)
            return AL_TRUE;
}

/*
 * void SetListenerValues()
 *
 *         We already defined certain values for the Listener, but we need
 *         to tell OpenAL to use that data. This function does just that.
 */
void setListenerValues(ALfloat *ListenerPos, ALfloat *ListenerVel, ALfloat *ListenerOri)
{
    alListenerfv(AL_POSITION,    ListenerPos);
    alListenerfv(AL_VELOCITY,    ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
}

/*
 * void KillALData()
 *
 *         We have allocated memory for our buffers and sources which needs
 *         to be returned to the system. This function frees that memory.
 */
void killALData(ALuint *Buffer,int bsize, ALuint *Source,int ssize)
{
	for(int x=0;x<bsize;x++)
		alDeleteBuffers(1, &Buffer[x]);
            
	for(int x=0;x<ssize;x++)
		alDeleteSources(1, &Source[x]);

	alutExit();
}