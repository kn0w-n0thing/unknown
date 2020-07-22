#pragma once

#include "ofMain.h"

class emotionProcessor {

public:

	void init(ofJson data);
	ofJson processEmotions(string language);

private:
	ofJson emoJson;
	float frames;
	string domEmotion;
	float x1, x2, y1, y2;
	float resolutionX, resolutionY;
	vector<float> averageEmo;
};