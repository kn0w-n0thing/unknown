#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::guiSaveListener() {
  messageStartTime = ofGetElapsedTimef();
  saveMessageState = true;
  cout << "saving settings.xml" << endl;
}

//--------------------------------------------------------------
void ofApp::guiLoadListener() {
  messageStartTime = ofGetElapsedTimef();
  loadMessageState = true;
  cout << "loading settings.xml" << endl;
}

//--------------------------------------------------------------
void ofApp::debugChanged(bool& debugUpdate) {
  debug = debugUpdate;
}

//--------------------------------------------------------------
void ofApp::idChanged(string& idUpdate) {
  id = idUpdate;
}

//--------------------------------------------------------------
void ofApp::chineseLangInitChanged(bool& chineseLangSelectedInitUpdate) {
  chineseLangSelectedInit = chineseLangSelectedInitUpdate;
}

//--------------------------------------------------------------
void ofApp::bgColorChanged(ofColor& bgColorUpdate) {
  bgColor = bgColorUpdate;
  ofBackground(bgColor);
}

//--------------------------------------------------------------
void ofApp::marginXchanged(int& marginXupdate) {
  marginX = marginXupdate;
  w = ofGetWidth() - (marginX * 2);
}

//--------------------------------------------------------------
void ofApp::marginYchanged(int& marginYupdate) {
  marginY = marginYupdate;
}

//--------------------------------------------------------------
void ofApp::fontSizeChanged(int& fontSizeUpdate) {
  fontSize = fontSizeUpdate;
  enFont.setFontSize(fontSize);
  zhFont.setFontSize(fontSize);
}

//--------------------------------------------------------------
void ofApp::rightMarginErrorChanged(float& rightMarginErrorUpdate) {
  rightMarginError = rightMarginErrorUpdate;
}

//--------------------------------------------------------------
void ofApp::headStrCorrectChanged(bool& headStrCorrectUpdate) {
  headStrCorrect = headStrCorrectUpdate;
}

//--------------------------------------------------------------
void ofApp::textColorChanged(ofColor& textColorUpdate) {
  textColor = textColorUpdate;
  enFont.setColor(textColor);
  zhFont.setColor(textColor);
}

//--------------------------------------------------------------
void ofApp::hTimeLimitChanged(int& hTimeLimitUpdate) {
  hTimeLimit = hTimeLimitUpdate;
}

//--------------------------------------------------------------
void ofApp::imagePassesMaxChanged(int& passesMaxUpdate) {
  passesMax = passesMaxUpdate;
}

//--------------------------------------------------------------
void ofApp::imageMaxRangeChanged(int& maxRangeUpdate) {
  maxRange = maxRangeUpdate;
}

//--------------------------------------------------------------
void ofApp::imagePixSizeMinChanged(int& pixSizeMinUpdate) {
  pixSizeMin = pixSizeMinUpdate;
}

//--------------------------------------------------------------
void ofApp::imagePixSizeMaxChanged(int& pixSizeMaxUpdate) {
  pixSizeMax = pixSizeMaxUpdate;
}

//--------------------------------------------------------------
void ofApp::imageRangeIncChanged(float& rangeIncUpdate) {
  rangeInc = rangeIncUpdate;
}

//--------------------------------------------------------------
void ofApp::emoFontSizeChanged(int& emoFontSizeUpdate) {
  emoFontSize = emoFontSizeUpdate;
  enEmoFont.setFontSize(emoFontSize);
  zhEmoFont.setFontSize(emoFontSize);
}

//--------------------------------------------------------------
void ofApp::emoTextColorChanged(ofColor& emoTextColorUpdate) {
  emoTextColor = emoTextColorUpdate;
  enEmoFont.setColor(emoTextColor);
  zhEmoFont.setColor(emoTextColor);
}

//--------------------------------------------------------------
void ofApp::emoParSpaceChanged(int& emoParSpaceUpdate) {
  emoParSpace = emoParSpaceUpdate;
}

//--------------------------------------------------------------
void ofApp::astralObjectSizeChanged(float& astralObjectSizeUpdate) {
  astralObjectSize = astralObjectSizeUpdate;
}

//--------------------------------------------------------------
void ofApp::cameraDistanceChanged(int& cameraDistanceUpdate) {
  cameraDistance = cameraDistanceUpdate;
}

//--------------------------------------------------------------
void ofApp::emoTimeLimitChanged(int& emoTimeLimitUpdate) {
  emoTimeLimit = emoTimeLimitUpdate;
}

//--------------------------------------------------------------
void ofApp::oscReceiverPortChanged(string& oscReceiverPortUpdate) {
  oscReceiverPort = oscReceiverPortUpdate;
  receiver.setup(ofToInt(oscReceiverPort.get()));
}

//--------------------------------------------------------------
void ofApp::headSendAddressChanged(string& headSendAddressUpdate) {
  headSendAddress = headSendAddressUpdate;
  oscHeadSender.clear();
  oscHeadSender.setup(ofToString(headSendAddress.get()),
                      ofToInt(headSendPort.get()));
}

//--------------------------------------------------------------
void ofApp::headSendPortChanged(string& headSendPortUpdate) {
  headSendPort = headSendPortUpdate;
  oscHeadSender.clear();
  oscHeadSender.setup(ofToString(headSendAddress.get()),
                      ofToInt(headSendPort.get()));
}

//--------------------------------------------------------------
void ofApp::headReconnectTimeoutChanged(string& headReconnectTimeoutUpdate) {
  headReconnectTimeout = headReconnectTimeoutUpdate;
}

//--------------------------------------------------------------
void ofApp::emoSendAddressChanged(string& emoSendAddressUpdate) {
  emoSendAddress = emoSendAddressUpdate;
  oscEmoSender.clear();
  oscEmoSender.setup(ofToString(emoSendAddress.get()),
                     ofToInt(emoSendPort.get()));
}

//--------------------------------------------------------------
void ofApp::emoSendPortChanged(string& emoSendPortUpdate) {
  emoSendPort = emoSendPortUpdate;
  oscEmoSender.clear();
  oscEmoSender.setup(ofToString(emoSendAddress.get()),
                     ofToInt(emoSendPort.get()));
}

//--------------------------------------------------------------
void ofApp::emoReconnectTimeoutChanged(string& emoReconnectTimeoutUpdate) {
  emoReconnectTimeout = emoReconnectTimeoutUpdate;
}

//--------------------------------------------------------------
void ofApp::galaxySendAddressChanged(string& galaxySendAddressUpdate) {
  galaxySendAddress = galaxySendAddressUpdate;
  galaxySender.clear();
  galaxySender.setup(ofToString(galaxySendAddress.get()),
                     ofToInt(galaxySendPort.get()));
}

//--------------------------------------------------------------
void ofApp::galaxySendPortChanged(string& galaxySendPortUpdate) {
  galaxySendPort = galaxySendPortUpdate;
  galaxySender.clear();
  galaxySender.setup(ofToString(galaxySendAddress.get()),
                     ofToInt(galaxySendPort.get()));
}

//--------------------------------------------------------------
void ofApp::oscDebugConsoleChanged(bool& oscDebugConsoleUpdate) {
  oscDebugConsole = oscDebugConsoleUpdate;
}

//--------------------------------------------------------------
float ofApp::getRotatedAspectRatio(float nh) {
  float nw = nh * ofGetWidth() / ofGetHeight();
  return nw;
}

//--------------------------------------------------------------
string ofApp::getHeadlineData(ofJson jsonData, int i) {
  string h = jsonData["articles"][i]["title"];
  return h;
}

//--------------------------------------------------------------
string ofApp::cleanHeadline(string headline) {
  vector<string> parts;
  string splitHeadline = "";
  string cleanHeadline = "";
  parts = ofSplitString(headline, "-");
  if (parts.size() > 2) {
    for (int i = 0; i < parts.size(); i++) {
      if (i <= parts.size() - 2) {
        if (i == parts.size() - 2) {
          splitHeadline += parts[i];
        } else {
          splitHeadline += parts[i] + "-";
        }
      }
    }
  } else {
    splitHeadline = parts[0];
  }

  // find extra white spaces
  int spaceCounter = 0;
  for (int c = 0; c < splitHeadline.size(); c++) {
    if (splitHeadline[c] == ' ') {
      spaceCounter++;
      if (spaceCounter < 2) {
        cleanHeadline += splitHeadline[c];
      }
    } else {
      spaceCounter = 0;
      cleanHeadline += splitHeadline[c];
    }
  }

  return cleanHeadline;
}

//--------------------------------------------------------------
void ofApp::setupRenderEngine() {
  range = 1;
  maxRange = maxRange.get();
  passesMax = passesMax.get();
  passes = passesMax;
  pixSizeMax = pixSizeMax.get();
  pixSizeMin = pixSizeMin.get();
  rangeInc = rangeInc.get();
}

//--------------------------------------------------------------
void ofApp::renderRandomPixels() {
  if (img.isAllocated()) {
    ofPixels pix = img.getPixels();
    int randIndexWidthPrev = 0;
    int randIndexHeightPrev = 0;

    for (int i = range; i > 0; i--) {
      int randIndexWidth = int(ofRandom(img.getWidth()));
      int randIndexHeight = int(ofRandom(img.getHeight()));

      if (randIndexWidth != randIndexWidthPrev &&
          randIndexHeight != randIndexHeightPrev) {
        int pixIndex = pix.getPixelIndex(randIndexWidth, randIndexHeight);
        float randSize = ofRandom(pixSizeMin, pixSizeMax);
        float rs = ofMap(passes, passesMax, 0, randSize, pixSizeMin);
        ofColor c = pix.getColor(pixIndex);
        ofSetColor(c.r, c.g, c.b, ofMap(passes, passesMax, 0, 70, 255));
        ofFill();
        ofDrawRectangle(randIndexWidth, randIndexHeight, rs, rs);
      }

      randIndexWidthPrev = randIndexWidth;
      randIndexHeightPrev = randIndexWidthPrev;
    }
  }
}

//--------------------------------------------------------------
void ofApp::renderEmotionsScene(ofJson jsonData) {
  if (dataSceneSetup) {
    emo.init(jsonData);

    if (chineseLangSelected) {
      emoObj = emo.processEmotions("zh");
      astralTextZhi = astralObject.generateChineseText(emoObj);
    } else {
      emoObj = emo.processEmotions("en");
      astralTextEn = astralObject.generateEnglishText(emoObj);
    }

    domEmotion = emoObj["dominant-emotion"];
    originalDomEmotion = emoObj["original-dominant-emotion"];
    totalFrames = emoObj["total-frames"];
    avgAngry = emoObj["average-emotions"]["angry"];
    avgDisgusted = emoObj["average-emotions"]["disgusted"];
    avgAfraid = emoObj["average-emotions"]["afraid"];
    avgHappy = emoObj["average-emotions"]["happy"];
    avgSad = emoObj["average-emotions"]["sad"];
    avgSurprised = emoObj["average-emotions"]["surprised"];
    avgNeutral = emoObj["average-emotions"]["neutral"];
    allAvgEmoEn = "angry: " + ofToString(avgAngry) +
                  " | disgusted: " + ofToString(avgDisgusted) +
                  " | afraid: " + ofToString(avgAfraid) +
                  " | happy: " + ofToString(avgHappy) +
                  " |\nsad: " + ofToString(avgSad) +
                  " | surprised: " + ofToString(avgSurprised) +
                  " | neutral: " + ofToString(avgNeutral);
    allAvgEmoTitlesZh = "愤怒:\n厌恶:\n害怕:\n快乐:\n忧伤:\n惊讶:\n中性:";
    allAvgEmoTitlesEn =
        "angry:\ndisgusted:\nafraid:\nhappy:\nsad:\nsurprised:\nneutral:";
    allAvgEmoZh = ofToString(avgAngry) + "\n" + ofToString(avgDisgusted) +
                  "\n" + ofToString(avgAfraid) + "\n" + ofToString(avgHappy) +
                  "\n" + ofToString(avgSad) + "\n" + ofToString(avgSurprised) +
                  "\n" + ofToString(avgNeutral);

    // set size of astral objet from dominant emotion value
    float domEmoVal = emoObj["dominant-emotion-value"];

    // arguments: float size, float rotationDegsX, float rotationDegsY
    astralObject.setupObject(astralObjectSize, avgAngry * ofRandom(-20, 20),
                             domEmoVal * ofRandom(-20, 20));

    dataSceneSetup = false;
  } else {
    astralObject.drawObject("faces");  // OPTS: wireframe, vertices, faces

    if (chineseLangSelected) {
      // if Chinese Language
      ofVec2f domEmoTxtZh, emoTxtZh1, emoTxtZh2, emoGenerativeZh;

      domEmoTxtZh = zhEmoFont.drawLeft("主导情绪:\n" + domEmotion, marginX,
                                       marginY, debug);

      float tmpY = marginY + domEmoTxtZh.y + emoParSpace;

      emoTxtZh1 = zhEmoFont.drawLeft(allAvgEmoTitlesZh, marginX, tmpY, debug);

      emoTxtZh2 = zhEmoFont.drawLeft(allAvgEmoZh, marginX + emoTxtZh1.x * 1.2,
                                     tmpY, debug);

      // the argument 2 (before debug) refers to a right margin correction error
      emoGenerativeZh = zhEmoFont.drawChineseBlock(
          astralTextZhi, marginX, tmpY + emoTxtZh1.y + emoParSpace, w,
          rightMarginError, debug);
    } else {
      // if English Language
      ofVec2f domEmoTxtEn, emoTxtEn1, emoTxtEn2, emoGenerativeEn;

      domEmoTxtEn = enEmoFont.drawLeft("Dominant Emotion:\n" + domEmotion,
                                       marginX, marginY, debug);

      float tmpY = marginY + domEmoTxtEn.y + emoParSpace;

      emoTxtEn1 = enEmoFont.drawLeft(allAvgEmoTitlesEn, marginX, tmpY, debug);

      emoTxtEn2 = enEmoFont.drawLeft(allAvgEmoZh, marginX + emoTxtEn1.x * 1.2,
                                     tmpY, debug);

      emoGenerativeEn = enEmoFont.drawEnglishBlock(
          astralTextEn, marginX, tmpY + emoTxtEn1.y + emoParSpace, w, debug);
    }
  }
}

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofSetWindowTitle("newsHeadlinesApp");
  ofHideCursor();
  ofSetBackgroundAuto(true);

  ///////////////////////
  // GUI EVENT LISTENERS//
  ///////////////////////
  ofAddListener(panel.savePressedE, this, &ofApp::guiSaveListener);
  ofAddListener(panel.loadPressedE, this, &ofApp::guiLoadListener);
  debug.addListener(this, &ofApp::debugChanged);
  id.addListener(this, &ofApp::idChanged);
  chineseLangSelectedInit.addListener(this, &ofApp::chineseLangInitChanged);
  bgColor.addListener(this, &ofApp::bgColorChanged);
  marginX.addListener(this, &ofApp::marginXchanged);
  marginY.addListener(this, &ofApp::marginYchanged);
  fontSize.addListener(this, &ofApp::fontSizeChanged);
  rightMarginError.addListener(this, &ofApp::rightMarginErrorChanged);
  headStrCorrect.addListener(this, &ofApp::headStrCorrectChanged);
  textColor.addListener(this, &ofApp::textColorChanged);
  hTimeLimit.addListener(this, &ofApp::hTimeLimitChanged);
  passesMax.addListener(this, &ofApp::imagePassesMaxChanged);
  maxRange.addListener(this, &ofApp::imageMaxRangeChanged);
  pixSizeMin.addListener(this, &ofApp::imagePixSizeMinChanged);
  pixSizeMax.addListener(this, &ofApp::imagePixSizeMaxChanged);
  rangeInc.addListener(this, &ofApp::imageRangeIncChanged);
  emoFontSize.addListener(this, &ofApp::emoFontSizeChanged);
  emoTextColor.addListener(this, &ofApp::emoTextColorChanged);
  emoParSpace.addListener(this, &ofApp::emoParSpaceChanged);
  astralObjectSize.addListener(this, &ofApp::astralObjectSizeChanged);
  cameraDistance.addListener(this, &ofApp::cameraDistanceChanged);
  emoTimeLimit.addListener(this, &ofApp::emoTimeLimitChanged);
  oscReceiverPort.addListener(this, &ofApp::oscReceiverPortChanged);
  headSendAddress.addListener(this, &ofApp::headSendAddressChanged);
  headSendPort.addListener(this, &ofApp::headSendPortChanged);
  headReconnectTimeout.addListener(this, &ofApp::headReconnectTimeoutChanged);
  emoSendAddress.addListener(this, &ofApp::emoSendAddressChanged);
  emoSendPort.addListener(this, &ofApp::emoSendPortChanged);
  emoReconnectTimeout.addListener(this, &ofApp::emoReconnectTimeoutChanged);
  galaxySendAddress.addListener(this, &ofApp::galaxySendAddressChanged);
  galaxySendPort.addListener(this, &ofApp::galaxySendPortChanged);
  oscDebugConsole.addListener(this, &ofApp::oscDebugConsoleChanged);

  ///////
  // GUI//
  ///////
  ofxGuiSetBorderColor(ofColor(255, 200));
  ofxGuiSetHeaderColor(ofColor(80, 200));
  ofxGuiSetFillColor(ofColor(91, 118, 133, 200));
  ofxGuiSetBackgroundColor(ofColor(0, 200));
  ofxGuiSetTextColor(ofColor(255));

  panel.setup("SETTINGS");

  // options: "headline", "image", "emotions"
  currentScene = "headline";

  // GUI GENERAL PARAMETERS
  generalParam.setName("GENERAL");
  generalParam.add(id.set("PC ID", "1"));
  generalParam.add(chineseLangSelectedInit.set("Init Language Chinese", true));
  generalParam.add(bgColor.set("Background Color", ofColor(0, 0, 0),
                               ofColor(0, 0, 0), ofColor(255, 255, 255)));
  generalParam.add(marginX.set("Margin X", 50, 0, 300));
  generalParam.add(marginY.set("Margin Y", 100, 0, 300));
  panel.add(generalParam);

  // GUI HEADLINES SCENE PARAMETERS
  headlinesParam.setName("HEADLINE");
  headlinesParam.add(fontSize.set("Font Size", 72, 0, 300));
  headlinesParam.add(rightMarginError.set("Margin Fix", 1.5, 0, 6));
  headlinesParam.add(headStrCorrect.set("Auto Correct -", true));
  headlinesParam.add(textColor.set("Headline Color", ofColor(255, 255, 255),
                                   ofColor(0, 0, 0), ofColor(255, 255, 255)));
  headlinesParam.add(hTimeLimit.set("Time Limit", 15, 0, 60));
  panel.add(headlinesParam);

  // GUI IMAGE SCENE PARAMETERS
  imageParam.setName("IMAGE RENDERING");
  imageParam.add(remainingPasses.set("Remaining Passes:", ofToString(passes)));
  imageParam.add(passesMax.set("Max Passes", 5000, 0, 5000));
  imageParam.add(maxRange.set("Max Range", 1000, 0, 5000));
  imageParam.add(pixSizeMin.set("Pixel Size Min", 1, 0, 50));
  imageParam.add(pixSizeMax.set("Pixel Size Max", 20, 0, 50));
  imageParam.add(rangeInc.set("Range Increment", 1.01, 1, 5));
  panel.add(imageParam);

  // GUI EMOTIONS SCENE PARAMETERS
  emoParam.setName("EMOTIONS");
  emoParam.add(emoFontSize.set("Font Size", 48, 0, 120));
  emoParam.add(emoTextColor.set("Text Color", ofColor(255, 255, 255),
                                ofColor(0, 0, 0), ofColor(255, 255, 255)));
  emoParam.add(emoParSpace.set("Paragraph Space", 200, 0, 400));
  emoParam.add(astralObjectSize.set("Object Size", 1.7, 0, 5));
  emoParam.add(cameraDistance.set("Camera Distance", 1500, 0, 3000));
  emoParam.add(emoTimeLimit.set("Time Limit", 25, 0, 120));
  emoParam.add(emoJsonPath.set("Data Path", "emotions/Python/emotions.json"));
  panel.add(emoParam);

  osc.setName("OSC");

  // OSC RECEIVER PARAMETERS
  oscReceiverParam.setName("OSC RECEIVER");
  oscReceiverParam.add(oscReceiverPort.set("PORT", "5001"));
  osc.add(oscReceiverParam);

  // OSC HEADLINES SENDER PARAMETERS
  oscHeadSendParam.setName("OSC HEADLINE SENDER");
  oscHeadSendParam.add(headSendAddress.set("IP", "127.0.0.1"));
  oscHeadSendParam.add(headSendPort.set("PORT", "4003"));
  oscHeadSendParam.add(headReconnectTimeout.set("Timeout", "3"));
  osc.add(oscHeadSendParam);

  // OSC EMOTIONS SENDER PARAMETERS
  oscEmoSendParam.setName("OSC EMOTIONS SENDER");
  oscEmoSendParam.add(emoSendAddress.set("IP", "127.0.0.1"));
  oscEmoSendParam.add(emoSendPort.set("PORT", "4002"));
  oscEmoSendParam.add(emoReconnectTimeout.set("Timeout", "3"));
  osc.add(oscEmoSendParam);

  // OSC GALAXY SENDER PARAMETERS
  oscGalaxySendParam.setName("OSC GALAXY SENDER");
  oscGalaxySendParam.add(galaxySendAddress.set("IP", "127.0.0.1"));
  oscGalaxySendParam.add(galaxySendPort.set("PORT", "4001"));
  osc.add(oscGalaxySendParam);

  panel.add(osc);
  panel.minimizeAll();

  // GUI DEBUG PARAMETERS
  debugParam.setName("DEBUG");
  debugParam.add(debug.set(" Debug Mode", true));
  debugParam.add(oscDebugConsole.set("OSC Debug Console", true));
  debugParam.add(fps.set("FPS:", ofToString(int(ofGetFrameRate()))));
  debugParam.add(currentSceneDebug.set("Scene:", currentScene));
  debugParam.add(remainingTime.set("Timer:", ""));
  panel.add(debugParam);

  panel.loadFromFile("settings.xml");
  panel.setPosition(ofGetWidth() - panel.getWidth() - panel.getWidth() / 15,
                    panel.getWidth() / 15);
  ////////////////

  ofBackground(bgColor);

  marginColor = ofColor(255);
  xAxisColor = ofColor(255, 0, 0);
  yAxisColor = ofColor(0, 255, 0);
  textBoxColor = ofColor(255, 64, 229);
  underlineColor = ofColor(248, 252, 3);

  imageLoading = true;
  dataSceneSetup = false;

  w = ofGetWidth() - (marginX * 2);

  chineseLangSelected = chineseLangSelectedInit;

  headlineToRender = "";
  headlineSetup = true;
  headlineDataReady = false;

  emoSetup = false;
  emoDataReady = false;

  headIndex = 0;
  prefix = "";

  messageTimeLimit = 1;

  astralObject.init("sculpture.3ds");  // 3D SETUP
  faceDetected = false;

  hide = true;

  if (!hide) {
    ofShowCursor();
  } else {
    ofHideCursor();
  }

  //////////////
  // FONT setup//
  //////////////
  zhFont.init("fonts/zh/SourceHanSansSC-Regular.ttf", fontSize);  // chinese
                                                                  // font
  enFont.init("fonts/en/SuisseIntl-Regular.ttf", fontSize);  // english font
  zhFont.setColor(textColor);
  enFont.setColor(textColor);
  zhFont.underlineColor = underlineColor;
  enFont.underlineColor = underlineColor;

  zhEmoFont.init("fonts/zh/SourceHanSansSC-Regular.ttf", emoFontSize);
  enEmoFont.init("fonts/en/SuisseIntl-Regular.ttf", emoFontSize);
  zhEmoFont.setColor(emoTextColor);
  enEmoFont.setColor(emoTextColor);
  zhEmoFont.underlineColor = underlineColor;
  enEmoFont.underlineColor = underlineColor;

  debugFontSize = 14;
  debugFont.init("fonts/en/SuisseIntl-Regular.ttf", debugFontSize);
  debugFont.setColor(255);

  // setup initial values for image rendering
  setupRenderEngine();

  /////////////////////////
  // EMOTIONS INITIAL JSON//
  /////////////////////////
  ofFile file(ofToString(emoJsonPath.get()));
  if (file.exists()) {
    emotionsJson = ofLoadJson(ofToString(emoJsonPath.get()));
    ofLog(OF_LOG_NOTICE, "BOOT: Loaded Json");
  }

  ///////
  // OSC//
  ///////
  // Receiver
  receiver.setup(ofToInt(oscReceiverPort.get()));

  // Headline Sender
  oscHeadSender.setup(ofToString(headSendAddress.get()),
                      ofToInt(headSendPort.get()));
  headReconnectCount = 0;

  // Emotions Sender
  oscEmoSender.setup(ofToString(emoSendAddress.get()),
                     ofToInt(emoSendPort.get()));
  emoReconnectCount = 0;

  // Galaxy Sender
  galaxySender.setup(ofToString(galaxySendAddress.get()),
                     ofToInt(galaxySendPort.get()));

  /////////
  // LOG //
  /////////
  ofLog(OF_LOG_NOTICE, "PC-ID: " + ofToString(id));
  ofLog(OF_LOG_NOTICE, "CurrentScene: " + currentScene);
  cout << "================================================================"
       << endl;
  ofLog(OF_LOG_NOTICE,
        "Listening for OSC messages on port: " + ofToString(oscReceiverPort));
  ofLog(OF_LOG_NOTICE, "OSC Sender to local server (headlines + ai) on: " +
                           ofToString(headSendAddress) + ":" +
                           ofToString(headSendPort));
  ofLog(OF_LOG_NOTICE,
        "OSC Sender to GALAXY on: " + ofToString(galaxySendAddress.get()) +
            ":" + ofToString(galaxySendPort));
  cout << "================================================================"
       << endl;
}

//--------------------------------------------------------------
void ofApp::update() {
  if (currentScene == "headline") {
    if (headlineSetup) {
      headReconnectCount = 0;

      if (chineseLangSelected) {
        // if Chinese Language
        prefix = "zh";
      } else {
        // if English Language
        prefix = "en";
      }

      // send first osc message to local headlines server
      ofxOscMessage headMessage;
      headMessage.setAddress("/screen" + ofToString(id));
      headMessage.addStringArg("ready");
      headMessage.addStringArg(prefix);
      oscHeadSender.sendMessage(headMessage, false);
      oscLocalSenderStartTime = ofGetElapsedTimef();
      oscEmoSenderStartTime = ofGetElapsedTimef();
      headlineSetup = false;
    }

    if (emoSetup) {
      emoReconnectCount = 0;
      // send message to emotions app (START!)
      ofxOscMessage emoMessage;
      emoMessage.setAddress("/emotions");
      emoMessage.addBoolArg(true);
      oscEmoSender.sendMessage(emoMessage, false);
      emoSenderLastMessage = "Sent to: /emotions\nMessage: true";
      emoSetup = false;
    }

    if (headlineDataReady && emoDataReady) {
      if (ofGetElapsedTimef() - hStartTime >= hTimeLimit) {
        currentScene = "image";
        imageLoading = true;
        ofSetBackgroundAuto(false);
        ofBackground(bgColor);
        setupRenderEngine();

        // send message to emotions app (DONE!)
        ofxOscMessage emoMessage;
        emoMessage.setAddress("/emotions");
        emoMessage.addBoolArg(false);
        oscEmoSender.sendMessage(emoMessage, false);
        emoSenderLastMessage = "Sent to: /emotions\nMessage: false";
      }
    }
    // RECONNECT TO LOCAL SERVER (HEADLINES + AI)
    if (!headlineDataReady) {
      if (ofGetElapsedTimef() - oscLocalSenderStartTime >=
          ofToInt(headReconnectTimeout.get())) {
        ofxOscMessage headMessage;
        headMessage.setAddress("/screen" + ofToString(id));
        headMessage.addStringArg("ready");
        headMessage.addStringArg(prefix);
        oscHeadSender.sendMessage(headMessage, false);
        oscLocalSenderStartTime = ofGetElapsedTimef();
        headReconnectCount++;
      }
    }
    // RECONNECT TO EMOTIONS APP
    if (headlineDataReady && !emoDataReady) {
      if (ofGetElapsedTimef() - oscEmoSenderStartTime >=
          ofToInt(emoReconnectTimeout.get())) {
        ofxOscMessage emoMessage;
        emoMessage.setAddress("/emotions");
        emoMessage.addBoolArg(true);
        oscEmoSender.sendMessage(emoMessage, false);
        emoSenderLastMessage = "Sent to: /emotions\nMessage: true";
        oscEmoSenderStartTime = ofGetElapsedTimef();
        emoReconnectCount++;
      }
    }
    // }
  }

  if (currentScene == "image") {
    if (imageLoading) {
      img.load(imgPath);
      astralObject.loadTexture(imgPath);
      int ih = ofGetHeight();
      int iw = int(getRotatedAspectRatio(ih));
      img.resize(iw, ih);  // resize to fit screen's aspect ratio
      imageLoading = false;
    }
  }

  if (currentScene == "emotions") {
    if (faceDetected) {
      astralObject.updateObject(astralObjectSize, cameraDistance);

      if (ofGetElapsedTimef() - emoStartTime >= emoTimeLimit) {
        hStartTime = ofGetElapsedTimef();
        ofBackground(bgColor);
        headlineSetup = true;
        headlineDataReady = false;
        chineseLangSelected =
            !chineseLangSelected;  // change language for next round
        currentScene = "headline";
        emoDataReady = false;

        //////////////////////////
        // Send Data to GALAXY PC//
        //////////////////////////
        /*The order of elements are: ['/galaxy', 30, 'Disgust',
                    0.111,0.481, 0.026, 0.002, 0.254, 0.008, 0.118,
                    'http://localhost:4000/english/14.jpeg']*/
        ofxOscMessage m;
        m.setAddress("/galaxy");
        m.addFloatArg(totalFrames);
        m.addStringArg(originalDomEmotion);
        m.addFloatArg(avgAngry);
        m.addFloatArg(avgDisgusted);
        m.addFloatArg(avgAfraid);
        m.addFloatArg(avgHappy);
        m.addFloatArg(avgSad);
        m.addFloatArg(avgSurprised);
        m.addFloatArg(avgNeutral);
        m.addStringArg(imgPath);
        galaxySender.sendMessage(m, false);
        galaxySenderLastMessage =
            "Data sent OK: [/galaxy, " + ofToString(totalFrames) + ", " +
            ofToString(originalDomEmotion) + ", " + ofToString(avgAngry) +
            ", " + ofToString(avgDisgusted) + ",\n" + ofToString(avgAfraid) +
            ", " + ofToString(avgHappy) + ", " + ofToString(avgSad) + ", " +
            ofToString(avgSurprised) + ", " + ofToString(avgNeutral) + ",\n" +
            ofToString(imgPath);
      }
    } else {
      hStartTime = ofGetElapsedTimef();
      ofBackground(bgColor);
      headlineSetup = true;
      headlineDataReady = false;
      chineseLangSelected =
          !chineseLangSelected;  // change language for next round
      currentScene = "headline";
      emoDataReady = false;

      //////////////////////////
      // Send Data to GALAXY PC//
      //////////////////////////
      /*The order of elements are: ['/galaxy', 0, "",
      0 ,0, 0, 0, 0, 0, 0, 'http://localhost:4000/english/14.jpeg']*/
      ofxOscMessage m;
      m.setAddress("/galaxy");
      m.addFloatArg(0);
      m.addStringArg("");
      m.addFloatArg(0);
      m.addFloatArg(0);
      m.addFloatArg(0);
      m.addFloatArg(0);
      m.addFloatArg(0);
      m.addFloatArg(0);
      m.addFloatArg(0);
      m.addStringArg(imgPath);
      galaxySender.sendMessage(m, false);
      galaxySenderLastMessage =
          "Data sent OK: [/galaxy, " + ofToString(0) + ", , " + ofToString(0) +
          ", " + ofToString(0) + ",\n" + ofToString(0) + ", " + ofToString(0) +
          ", " + ofToString(0) + ", " + ofToString(0) + ", " + ofToString(0) +
          ",\n" + ofToString(imgPath);
    }
  }

  // check for waiting OSC messages
  while (receiver.hasWaitingMessages()) {
    ofxOscMessage m;
    receiver.getNextMessage(m);

    if (m.getAddress() == "/shutdown" + ofToString(id)) {
      ofSystem("shutdown -h now");
    }

    // ping from headlines server
    if (m.getAddress() == "/ping" + ofToString(id)) {
      ofxOscMessage headMessage;
      headMessage.setAddress("/screen" + ofToString(id));
      headMessage.addStringArg("ping");
      oscHeadSender.sendMessage(headMessage, false);
    }

    // check for headlines data
    if (m.getAddress() == "/headline-" + ofToString(id)) {
      headlineDataReady = true;
      emoSetup = true;

      if (headStrCorrect) {
        headlineToRender = cleanHeadline(m.getArgAsString(0));
      } else {
        headlineToRender = m.getArgAsString(0);
      }

      imgPath =
          "http://" + ofToString(headSendAddress.get()) + m.getArgAsString(1);
      hStartTime = ofGetElapsedTimef();
      tmpHead = "Message from: /headline-" + ofToString(id) +
                "\nHeadline data received OK!\nImage-source: " + imgPath;
    }

    // check if emotions app is running
    if (m.getAddress() == "/emo-running") {
      string tmpEmoData = m.getArgAsString(0);
      tmpMsg = "Message from: /emo-running\ndata: " + tmpEmoData +
               "\nstatus: recording facial data...";
      emoDataReady = true;
      hStartTime = ofGetElapsedTimef();
    }

    if (m.getAddress() == "/emo-done") {
      string tmpEmoData = m.getArgAsString(0);

      emoDataReady = false;

      // Get new Json data
      ofFile file(ofToString(emoJsonPath.get()));
      string tmpFrames = "";
      if (file.exists()) {
        emotionsJson = ofLoadJson(ofToString(emoJsonPath.get()));
        if (emotionsJson["frames"].empty()) {
          tmpFrames = "0";
          faceDetected = false;
        } else {
          faceDetected = true;
          tmpFrames = ofToString(emotionsJson["frames"].size());
        }
        tmpMsg = "Message from: /emo-done\ndata: " + tmpEmoData +
                 "\nstatus: done recording! Captured " + tmpFrames + " frames";
      }
    }

    receiverLastMessage = tmpHead + "\n" + tmpMsg;
  }

  if (!hide) {
    int tmpHeadTimer;
    if (currentScene == "headline" && headlineDataReady) {
      tmpHeadTimer = int(hTimeLimit - (ofGetElapsedTimef() - hStartTime));
    } else if (currentScene == "emotions") {
      tmpHeadTimer = int(emoTimeLimit - (ofGetElapsedTimef() - emoStartTime));
      ;
    } else {
      tmpHeadTimer = 0;
    }

    remainingPasses.set("Remaining Passes:", ofToString(passes));
    fps.set("FPS:", ofToString(int(ofGetFrameRate())));
    currentSceneDebug.set("Scene:", currentScene);
    remainingTime.set("Timer:", ofToString(tmpHeadTimer));
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ///////////////////////////
  // Render headline Scene //
  ///////////////////////////
  if (currentScene == "headline") {
    ofSetColor(textColor);

    ofVec2f tmpTextBoxSize;

    if (headlineDataReady && emoDataReady) {
      if (chineseLangSelected) {
        // the argument 1.2 (before debug) refers to a right margin correction
        // error
        textBoxSize = zhFont.drawChineseBlock(
            headlineToRender, marginX, marginY, w, rightMarginError, debug);
      } else {
        textBoxSize = enFont.drawEnglishBlock(headlineToRender, marginX,
                                              marginY, w, debug);
      }
    } else {
      if (!headlineDataReady && !emoDataReady ||
          !headlineDataReady && emoDataReady) {
        if (headReconnectCount > 0) {
          debugFont.drawCentered(
              "OSC ERROR: headlines server is offline.\nretrying in " +
                  ofToString(
                      int(ofToInt(headReconnectTimeout.get())) -
                      int(ofGetElapsedTimef() - oscLocalSenderStartTime)),
              ofGetWidth() / 2, ofGetHeight() / 2, false);
        }
      } else if (!emoDataReady) {
        if (emoReconnectCount > 0) {
          debugFont.drawCentered(
              "OSC ERROR: emotions app is offline.\nretrying in " +
                  ofToString(int(ofToInt(emoReconnectTimeout.get())) -
                             int(ofGetElapsedTimef() - oscEmoSenderStartTime)),
              ofGetWidth() / 2, ofGetHeight() / 2, false);
        }
      }
    }
  }

  ////////////////////////
  // Render Image Scene //
  ////////////////////////
  if (currentScene == "image") {
    if (!imageLoading) {
      renderRandomPixels();
      passes--;

      if (range <= maxRange) {
        range *= rangeInc;
      }

      if (passes <= 0) {
        currentScene = "emotions";
        ofSetBackgroundAuto(true);
        ofBackground(bgColor);
        emoStartTime = ofGetElapsedTimef();
        dataSceneSetup = true;
      }
    }
  }

  ///////////////////////
  // Render Data Scene //
  ///////////////////////
  if (currentScene == "emotions" && faceDetected) {
    if (!imageLoading) {
      renderEmotionsScene(emotionsJson);
    }
  }

  //////////////////////
  // When DEBUG is ON //
  //////////////////////
  if (debug) {
    // draw X axis
    ofSetColor(xAxisColor);
    ofDrawLine(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() / 2);

    // draw Y axis
    ofSetColor(yAxisColor);
    ofDrawLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());

    // vertical quarters
    ofSetColor(255);
    ofDrawLine(w / 4 + marginX, 0, w / 4 + marginX, ofGetHeight());
    ofDrawLine(w - w / 4 + marginX, 0, w - w / 4 + marginX, ofGetHeight());

    // draw margins
    ofSetColor(marginColor);
    ofDrawLine(marginX, marginY, marginX,
               ofGetHeight() - marginY);  // left
    ofDrawLine(ofGetWidth() - marginX, marginY, ofGetWidth() - marginX,
               ofGetHeight() - marginY);                            // right
    ofDrawLine(marginX, marginY, ofGetWidth() - marginX, marginY);  // Top
    ofDrawLine(marginX, ofGetHeight() - marginY, ofGetWidth() - marginX,
               ofGetHeight() - marginY);  // Bottom

    // text renderable area draw
    if (currentScene == "headline") {
      ofSetColor(0, 0, 255, 30);
      ofDrawRectangle(marginX, marginY, w, ofGetHeight() - marginY * 2);
    }

    if (oscDebugConsole) {
      float consoleY = ofGetHeight() / 4;
      float padding = 20;
      ofSetColor(255);
      ofNoFill();
      ofDrawRectangle(marginX, ofGetHeight() - marginY - consoleY, w / 4,
                      consoleY);
      ofSetColor(0, 90);
      ofFill();
      ofDrawRectangle(marginX, ofGetHeight() - marginY - consoleY, w / 4,
                      consoleY);
      ofSetColor(255, 200);
      ofDrawBitmapString("OSC RECEIVER\n" + receiverLastMessage,
                         marginX + padding / 2,
                         ofGetHeight() - marginY - consoleY + padding, false);
      ofDrawBitmapString(
          "OSC EMOTION SENDER\n" + emoSenderLastMessage, marginX + padding / 2,
          ofGetHeight() - marginY - consoleY * 0.5 + padding, false);
      ofDrawBitmapString("OSC GALAXY SENDER\n" + galaxySenderLastMessage,
                         marginX + padding / 2,
                         ofGetHeight() - marginY - consoleY * 0.25 + padding,
                         false);
    }
  }

  if (!hide) {
    panel.draw();
  }

  if (saveMessageState || loadMessageState) {
    string slm = "";
    if (saveMessageState) {
      slm = "saving settings...";
    } else {
      slm = "loading settings...";
    }
    ofSetColor(0, 220);
    ofFill();
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    enFont.setFontSize(26);
    enFont.drawCentered(slm, ofGetWidth() / 2, ofGetHeight() / 2, false);
    enFont.setFontSize(fontSize);

    if (ofGetElapsedTimef() - messageStartTime >= messageTimeLimit) {
      saveMessageState = false;
      loadMessageState = false;
    }
  }
}

//--------------------------------------------------------------
void ofApp::exit() {
  // send message to emotions app (DONE!)
  ofxOscMessage emoMessage;
  emoMessage.setAddress("/emotions");
  emoMessage.addBoolArg(false);
  oscEmoSender.sendMessage(emoMessage, false);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's' || key == 'S') {
    hide = !hide;
    if (hide) {
      ofHideCursor();
    } else {
      ofShowCursor();
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
