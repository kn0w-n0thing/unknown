#include "ofApp.h"

//--------------------------------------------------------------
void emotionProcessor::init(ofJson data) {
  emoJson = data;
  frames = emoJson["frames"].size();
}

//--------------------------------------------------------------
ofJson emotionProcessor::processEmotions(string language) {
  float angry = 0;
  float disgusted = 0;
  float afraid = 0;
  float happy = 0;
  float sad = 0;
  float surprised = 0;
  float neutral = 0;

  float tmpFloat = 0;

  domEmotion = "";
  string originalDomEmotion = "";

  ofJson obj;

  if (!emoJson["frames"].empty() && frames > 0) {
    for (int i = 0; i < frames; i++) {
      tmpFloat = emoJson["frames"][i]["emotion-probs"]["angry"];
      angry += tmpFloat;
      tmpFloat = emoJson["frames"][i]["emotion-probs"]["disgusted"];
      disgusted += tmpFloat;
      tmpFloat = emoJson["frames"][i]["emotion-probs"]["afraid"];
      afraid += tmpFloat;
      tmpFloat = emoJson["frames"][i]["emotion-probs"]["happy"];
      happy += tmpFloat;
      tmpFloat = emoJson["frames"][i]["emotion-probs"]["sad"];
      sad += tmpFloat;
      tmpFloat = emoJson["frames"][i]["emotion-probs"]["surprised"];
      surprised += tmpFloat;
      tmpFloat = emoJson["frames"][i]["emotion-probs"]["neutral"];
      neutral += tmpFloat;
    }

    averageEmo.push_back(angry / frames);
    averageEmo.push_back(disgusted / frames);
    averageEmo.push_back(afraid / frames);
    averageEmo.push_back(happy / frames);
    averageEmo.push_back(sad / frames);
    averageEmo.push_back(surprised / frames);
    averageEmo.push_back(neutral / frames);

    // sort emotions average values within vector
    std::sort(averageEmo.begin(), averageEmo.end());

    float highestVal = averageEmo[averageEmo.size() - 1];

    if (language == "zh") {
      if (highestVal == angry / frames) {
        domEmotion = "愤怒";
        originalDomEmotion = "Anger";
      }
      if (highestVal == disgusted / frames) {
        domEmotion = "厌恶";
        originalDomEmotion = "Disgust";
      }
      if (highestVal == afraid / frames) {
        domEmotion = "害怕";
        originalDomEmotion = "Fear";
      }
      if (highestVal == happy / frames) {
        domEmotion = "快乐";
        originalDomEmotion = "Happiness";
      }
      if (highestVal == sad / frames) {
        domEmotion = "忧伤";
        originalDomEmotion = "Sadness";
      }
      if (highestVal == surprised / frames) {
        domEmotion = "惊讶";
        originalDomEmotion = "Surprise";
      }
      if (highestVal == neutral / frames) {
        domEmotion = "中性";
        originalDomEmotion = "Neutral";
      }
    } else {
      if (highestVal == angry / frames) {
        domEmotion = "Anger";
      }
      if (highestVal == disgusted / frames) {
        domEmotion = "Disgust";
      }
      if (highestVal == afraid / frames) {
        domEmotion = "Fear";
      }
      if (highestVal == happy / frames) {
        domEmotion = "Happiness";
      }
      if (highestVal == sad / frames) {
        domEmotion = "Sadness";
      }
      if (highestVal == surprised / frames) {
        domEmotion = "Surprise";
      }
      if (highestVal == neutral / frames) {
        domEmotion = "Neutral";
      }

      originalDomEmotion = domEmotion;
    }

    float divisor = 1000;

    obj["total-frames"] = frames;
    obj["dominant-emotion"] = ofToString(domEmotion);
    obj["original-dominant-emotion"] = ofToString(originalDomEmotion);
    obj["dominant-emotion-value"] = roundf(highestVal * divisor) / divisor;
    obj["average-emotions"]["angry"] =
        roundf((angry / frames) * divisor) / divisor;
    obj["average-emotions"]["disgusted"] =
        roundf((disgusted / frames) * divisor) / divisor;
    obj["average-emotions"]["afraid"] =
        roundf((afraid / frames) * divisor) / divisor;
    obj["average-emotions"]["happy"] =
        roundf((happy / frames) * divisor) / divisor;
    obj["average-emotions"]["sad"] = roundf((sad / frames) * divisor) / divisor;
    obj["average-emotions"]["surprised"] =
        roundf((surprised / frames) * divisor) / divisor;
    obj["average-emotions"]["neutral"] =
        roundf((neutral / frames) * divisor) / divisor;

  } else {
    obj["total-frames"] = 0;
    obj["dominant-emotion"] = "None";
    obj["dominant-emotion-value"] = 0;
    obj["average-emotions"]["angry"] = 0;
    obj["average-emotions"]["disgusted"] = 0;
    obj["average-emotions"]["afraid"] = 0;
    obj["average-emotions"]["happy"] = 0;
    obj["average-emotions"]["sad"] = 0;
    obj["average-emotions"]["surprised"] = 0;
    obj["average-emotions"]["neutral"] = 0;
  }

  averageEmo.clear();

  return obj;
}