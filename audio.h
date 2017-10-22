#ifndef  AUDIO_H // <- Prevents multiple inclusions
#define AUDIO_H // <- ...

/**************************/
// your stuff goes here
// function prototypes, etc.
ALboolean loadALData(ALuint &Buffer,char *audio_adress);
ALboolean bindALData(ALuint &Buffer, ALuint &Source, ALfloat *SourcePos, ALfloat *SourceVel, ALboolean loop);
void setListenerValues(ALfloat *ListenerPos, ALfloat *ListenerVel, ALfloat *ListenerOri);
void killALData(ALuint *Buffer,int bsize, ALuint *Source,int ssize);
// classes
// reservate names

#endif // AUDIO_H