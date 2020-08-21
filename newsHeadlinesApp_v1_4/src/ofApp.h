#pragma once

#include "astralObjectGenerator.h"
#include "emotionProcessor.h"
#include "ofMain.h"
#include "ofURLFileLoader.h"
#include "ofxFontAligner.h"
#include "ofxGui.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

  void exit();
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  // get aspect ratio of screen
  float getRotatedAspectRatio(float nh);

  // clean headine string
  string cleanHeadline(string headline);

  // setup initial values for rendering image
  void setupRenderEngine();
  // render random pixels for image transition
  void renderRandomPixels();
  // render data scene
  void renderEmotionsScene(ofJson jsonData);
  // prepare headline data
  string getHeadlineData(ofJson jsonData, int i);

  // gui events
  void guiSaveListener();
  void guiLoadListener();
  void debugChanged(bool& debugUpdate);
  void idChanged(string& idUpdate);
  void chineseLangInitChanged(bool& chineseLangSelectedInitUpdate);
  void bgColorChanged(ofColor& bgColorUpdate);
  void marginXchanged(int& marginXupdate);
  void marginYchanged(int& marginYupdate);
  void fontSizeChanged(int& fontSizeUpdate);
  void rightMarginErrorChanged(float& rightMarginErrorUpdate);
  void headStrCorrectChanged(bool& headStrCorrectUpdate);
  void textColorChanged(ofColor& textColorUpdate);
  void hTimeLimitChanged(int& hTimeLimitUpdate);
  void imagePassesMaxChanged(int& passesMaxUpdate);
  void imageMaxRangeChanged(int& maxRangeUpdate);
  void imagePixSizeMinChanged(int& pixSizeMinUpdate);
  void imagePixSizeMaxChanged(int& pixSizeMaxUpdate);
  void imageRangeIncChanged(float& rangeIncUpdate);
  void emoFontSizeChanged(int& emoFontSizeUpdate);
  void emoTextColorChanged(ofColor& emoTextColorUpdate);
  void emoParSpaceChanged(int& emoParSpaceUpdate);
  void astralObjectSizeChanged(float& astralObjectSizeUpdate);
  void cameraDistanceChanged(int& cameraDistanceUpdate);
  void emoTimeLimitChanged(int& emoTimeLimitUpdate);
  void oscReceiverPortChanged(string& oscReceiverPortUpdate);
  void headSendAddressChanged(string& headSendAddressUpdate);
  void headSendPortChanged(string& headSendPortUpdate);
  void headReconnectTimeoutChanged(string& headReconnectTimeoutUpdate);
  void emoSendAddressChanged(string& emoSendAddressUpdate);
  void emoSendPortChanged(string& emoSendPortUpdate);
  void emoReconnectTimeoutChanged(string& emoReconnectTimeoutUpdate);
  void galaxySendAddressChanged(string& galaxySendAddressUpdate);
  void galaxySendPortChanged(string& galaxySendPortUpdate);
  void oscDebugConsoleChanged(bool& oscDebugConsoleUpdate);

  // font variables
  ofColor textBoxColor, underlineColor;
  ofxFontAligner enFont, zhFont, enEmoFont, zhEmoFont, debugFont;
  ofVec2f textBoxSize;

  // render variables
  ofColor marginColor, xAxisColor, yAxisColor;
  float debugFontSize;
  ofImage img;
  string imgPath;
  bool imageLoading;
  float w;
  float range;
  int passes;
  string headlineToRender;
  bool headlineSetup, headlineDataReady, emoSetup, emoDataReady;
  int headIndex;
  string prefix;
  bool chineseLangSelected;
  string currentScene;
  float hStartTime;  // headline scene timer vars
  float emoStartTime;
  bool dataSceneSetup;

  // JSON
  ofJson emotionsJson;

  // 3D
  astralObjectGenerator astralObject;
  string astralTextEn, astralTextZhi;

  // Emotions
  bool faceDetected;
  emotionProcessor emo;
  ofJson emoObj;
  string domEmotion, originalDomEmotion;
  float totalFrames;
  float avgAngry;
  float avgDisgusted;
  float avgAfraid;
  float avgHappy;
  float avgSad;
  float avgSurprised;
  float avgNeutral;
  string allAvgEmoTitlesZh, allAvgEmoTitlesEn;
  string allAvgEmoEn, allAvgEmoZh;

  ///////
  // OSC//
  ///////

  // OSC Receiver
  ofxOscReceiver receiver;

  // OSC Communication with local server (headlines and ai)
  ofxOscSender oscHeadSender;  // client sender object
  float oscLocalSenderStartTime;
  int headReconnectCount;

  // OSC Communication with emotions APP
  ofxOscSender oscEmoSender;
  float oscEmoSenderStartTime;
  int emoReconnectCount;

  // OSC Communication with Galaxy Unity APP
  ofxOscSender galaxySender;  // client sender object

  // OSC debug console
  string tmpMsg, tmpHead;
  string receiverLastMessage, galaxySenderLastMessage, emoSenderLastMessage;

  ///////
  // GUI//
  ///////

  bool hide;

  ofxPanel panel;

  ofParameterGroup generalParam;
  ofParameter<string> id;
  ofParameter<bool> chineseLangSelectedInit;
  ofParameter<ofColor> bgColor;
  ofParameter<int> marginX, marginY;
  ofParameter<string> emoJsonPath;

  ofParameterGroup headlinesParam;
  ofParameter<int> fontSize;
  ofParameter<float> rightMarginError;
  ofParameter<bool> headStrCorrect;
  ofParameter<ofColor> textColor;
  ofParameter<int> hTimeLimit;

  ofParameterGroup imageParam;
  ofParameter<string> remainingPasses;
  ofParameter<int> passesMax;
  ofParameter<int> maxRange;
  ofParameter<int> pixSizeMin;
  ofParameter<int> pixSizeMax;
  ofParameter<float> rangeInc;

  ofParameterGroup emoParam;
  ofParameter<int> emoFontSize;
  ofParameter<ofColor> emoTextColor;
  ofParameter<int> emoParSpace;
  ofParameter<float> astralObjectSize;
  ofParameter<int> cameraDistance;
  ofParameter<int> emoTimeLimit;

  ofParameterGroup osc;

  ofParameterGroup oscReceiverParam;
  ofParameter<string> oscReceiverPort;
  ofParameter<string> ioReceiver;

  ofParameterGroup oscHeadSendParam;
  ofParameter<string> headSendAddress;
  ofParameter<string> headSendPort;
  ofParameter<string> headReconnectTimeout;

  ofParameterGroup oscEmoSendParam;
  ofParameter<string> emoSendAddress;
  ofParameter<string> emoSendPort;
  ofParameter<string> emoReconnectTimeout;

  ofParameterGroup oscGalaxySendParam;
  ofParameter<string> galaxySendAddress;
  ofParameter<string> galaxySendPort;

  ofParameterGroup debugParam;
  ofParameter<string> fps;
  ofParameter<string> currentSceneDebug;
  ofParameter<string> remainingTime;
  ofParameter<string> myIpAddress;
  ofParameter<bool> debug;
  ofParameter<bool> oscDebugConsole;

  // SAVE / LOAD Timer
  float messageStartTime, messageTimeLimit;
  bool saveMessageState, loadMessageState;
};
