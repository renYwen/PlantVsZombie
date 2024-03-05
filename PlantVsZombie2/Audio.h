#pragma once
#include"CoreMinimal.h"



//媒体源
class AudioSource
{
	string name = "";
public:
	AudioSource() { ; }
	AudioSource(string na) :name(na) {};
	void Load(string na) { name = na; }
	string GetPath() { return name; }
};


//媒体播放器
class AudioPlayer :public Component
{
	set<string>paths;
	float innerRadius = 0;
	float outerRadius = 0;
	bool bSpacial = false;//支持空间感的播放器时间开销较大，慎用
	int volume = 1000;//0~1000

	void AdjustVolume();

public:
	AudioPlayer(bool spacial = false):bSpacial(spacial) {}
	AudioPlayer(int vol, bool spacial = false):volume(vol),bSpacial(spacial) {}
	virtual ~AudioPlayer() {}

	virtual void Update() {AdjustVolume();}

	void SetRadius(float inner,float outer){
		inner = inner < 0 ? 0 : inner;
		outer = outer < 0 ? 0 : outer;
	}

	void SetSpacial(bool spacial) { bSpacial = spacial; }

	void SetVolume(int vol) { 
		if (vol) {
			volume = vol;

			for (auto it = paths.begin(); it != paths.end();++it) 
			{
				string file = string("setaudio ") + (*it) + string(" volume to ") + to_string(vol);
				mciSendString(file.c_str(), NULL, 0, NULL);
			}
		}
	}

	void Play(AudioSource source,bool repeat = false)
	{
		string buf = source.GetPath();
		paths.insert(buf);
	/*	mciSendString((string("seek ") + buf + string(" to start")).c_str(), 0, 0, 0);*/
		mciSendString((string("close ") + buf).c_str(), 0, 0, 0);
		mciSendString((string("play ") + buf +(repeat?string(" repeat"):"")).c_str(), 0, 0, 0);

		string file = string("setaudio ") + buf + string(" volume to ") + to_string(volume);
		mciSendString(file.c_str(), NULL, 0, NULL);
	}


	void Stop(AudioSource source) {mciSendString((string("stop ") + source.GetPath()).c_str(), 0, 0, 0);}

	void Close(AudioSource source) {
		paths.erase(source.GetPath());
		mciSendString((string("close ") + source.GetPath()).c_str(), 0, 0, 0);
	}

	void Pause(AudioSource source) { mciSendString((string("pause ") + source.GetPath()).c_str(), 0, 0, 0); }

	void Resume(AudioSource source){ mciSendString((string("resume ") + source.GetPath()).c_str(), 0, 0, 0); }
};