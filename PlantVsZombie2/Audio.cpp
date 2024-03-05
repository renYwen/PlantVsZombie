#include "Audio.h"
#include"Camera.h"


void AudioPlayer::AdjustVolume()
{
	if (bSpacial) {
		int vol = volume;
		float dis = Vector::Dis(MainCamera->GetWorldPosition(), GetWorldPosition());
		if (dis <= innerRadius);
		else if (dis > outerRadius)vol = 0;
		else vol = (outerRadius - dis) * volume / (outerRadius - innerRadius);

		for (auto it = paths.begin(); it != paths.end(); ++it)
		{
			string file = string("setaudio ") + (*it) + string(" volume to ") + to_string(vol);
			mciSendString(file.c_str(), NULL, 0, NULL);
		}
	}
}
