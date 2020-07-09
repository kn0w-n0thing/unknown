#include "ofApp.h"

//--------------------------------------------------------------
void astralObjectGenerator::init(string path) {
  ofDisableArbTex();
  model.loadModel(path);

  ofSetSmoothLighting(true);

  // MATERIAL
  // shininess is a value between 0 - 128, 128 being the most shiny //
  material.setShininess(120);
  // the light highlight of the material //
  material.setSpecularColor(ofColor(255, 255, 255, 255));

  // LIGHTS
  // Directional Lights emit light based on their orientation, regardless of
  // their position //
  directionalLight1.setDiffuseColor(ofColor(255.f, 255.f, 255.f));
  directionalLight1.setSpecularColor(ofColor(255.f, 255.f, 255.f));
  directionalLight1.setDirectional();
  directionalLight2.setDiffuseColor(ofColor(80.f, 80.f, 80.f));
  directionalLight2.setSpecularColor(ofColor(80.f, 80.f, 80.f));
  directionalLight2.setDirectional();
  // set light 1 pointing from left to right ->
  directionalLight1.setOrientation({0, 90, 0});
  // set light 2 pointing from right to left <-
  directionalLight2.setOrientation({0, -90, 0});

  // CAMERA
  camOrbitX = 0;
  camOrbitY = 0;
  camOrbitZ = 0;
  cam.setNearClip(0.1);
  cam.setFarClip(3000);
  cam.setPosition(ofVec3f(0, 0, 800));
  rotDegsX = 0;
  rotDegsY = 0;
}

//--------------------------------------------------------------
void astralObjectGenerator::setupObject(float size, float rx, float ry) {
  rotDegsX = rx;
  rotDegsY = ry;

  model.setScale(size, size, size);

  camOrbitX = ofRandom(0, 90);  // begin with a random angle for camera
  camOrbitY = ofRandom(0, 90);  // begin with a random angle for camera
}

//--------------------------------------------------------------
void astralObjectGenerator::updateObject(float size, int camDist) {
  model.setScale(size, size, size);
  cam.setPosition(ofVec3f(0, 0, camDist));

  camOrbitX += ofGetLastFrameTime() * rotDegsX;  // degrees per second on X;
  camOrbitY += ofGetLastFrameTime() * rotDegsY;  // degrees per second on Y;
  camOrbitZ = cam.getDistance();
  cam.orbitDeg(camOrbitX, camOrbitY, camOrbitZ, {0., 0., 0.});
}

//--------------------------------------------------------------
void astralObjectGenerator::loadTexture(string path) {
  tex.load(path);
}

//--------------------------------------------------------------
void astralObjectGenerator::drawObject(string mode) {
  ofEnableDepthTest();
  ofEnableLighting();

  material.begin();

  directionalLight1.enable();
  directionalLight2.enable();

  cam.begin();
  ofColor(255, 255);
  tex.bind();

  if (mode == "vertices") {
    model.drawVertices();
  } else if (mode == "wireframe") {
    model.drawWireframe();
  } else {
    model.drawFaces();
  }

  tex.unbind();
  cam.end();

  directionalLight1.disable();
  directionalLight2.disable();

  material.end();

  ofDisableLighting();
  ofDisableDepthTest();
}

//--------------------------------------------------------------
string astralObjectGenerator::generateChineseText(ofJson emoObj) {
  /*
  "愤怒的"  		[0]
  "厌恶的"  		[1]
  "害怕的"  		[2]
  "快乐的"  		[3]
  "忧伤的"   		[4]
  "惊喜的"  		[5]
  "无明显倾向的" 	[6]
  */

  string objects, radiance, speed, orbitingPlanets, flickerRate, brightness,
      size, spin, paragraph;

  int primaryEmotionMax = 7;
  int secondEmotionMax = 3;

  float emoValMax = 1.0;

  // Primary Emotions
  string objectOpts[primaryEmotionMax] = {
      "紧簇成群的星体", "聚集的星体", "星体",      "星体",
      "星体",           "星域",       "孤立的星体"};
  string radianceOpts[primaryEmotionMax] = {
      "红光", "霓虹橙光", "白光", "金光", "蓝光", "五彩光", "不存在的光"};

  // Secondary Emotions
  string speedOpts[secondEmotionMax] = {"缓慢移动的", "快速移动的",
                                        "高速移动的"};
  string orbitingPlanetsOpts[secondEmotionMax] = {
      "没有其他物体围绕它运行", "能看见有数个物体在它的轨道上运行",
      "有许多较小的物体围绕着它运行"};
  string flickerRateOpts[secondEmotionMax] = {"持续的", "摇曳的", "闪烁的"};
  string brightnessOpts[secondEmotionMax] = {"暗淡的", "明亮的", "眩目的"};
  string sizeOpts[secondEmotionMax] = {"矮星大小的", "太阳大小的", "巨大的"};
  string spinOpts[secondEmotionMax] = {"一座废弃的旋转木马", "一个风力涡轮机",
                                       "一阵五级飓风"};

  if (emoObj["dominant-emotion"] == "Anger") {
    objects = objectOpts[0];
    radiance = radianceOpts[0];
  } else if (emoObj["dominant-emotion"] == "Disgust") {
    objects = objectOpts[1];
    radiance = radianceOpts[1];
  } else if (emoObj["dominant-emotion"] == "Fear") {
    objects = objectOpts[2];
    radiance = radianceOpts[2];
  } else if (emoObj["dominant-emotion"] == "Happiness") {
    objects = objectOpts[3];
    radiance = radianceOpts[3];
  } else if (emoObj["dominant-emotion"] == "Sadness") {
    objects = objectOpts[4];
    radiance = radianceOpts[4];
  } else if (emoObj["dominant-emotion"] == "Surprise") {
    objects = objectOpts[5];
    radiance = radianceOpts[5];
  } else if (emoObj["dominant-emotion"] == "Neutral") {
    objects = objectOpts[6];
    radiance = radianceOpts[6];
  }

  if (emoObj["average-emotions"]["angry"] <= emoValMax / secondEmotionMax) {
    speed = speedOpts[0];
  } else if (emoObj["average-emotions"]["angry"] <=
             (emoValMax / secondEmotionMax) * 2) {
    speed = speedOpts[1];
  } else if (emoObj["average-emotions"]["angry"] <= emoValMax) {
    speed = speedOpts[2];
  }

  if (emoObj["average-emotions"]["disgusted"] <= emoValMax / secondEmotionMax) {
    orbitingPlanets = orbitingPlanetsOpts[0];
  } else if (emoObj["average-emotions"]["disgusted"] <=
             (emoValMax / secondEmotionMax) * 2) {
    orbitingPlanets = orbitingPlanetsOpts[1];
  } else if (emoObj["average-emotions"]["disgusted"] <= emoValMax) {
    orbitingPlanets = orbitingPlanetsOpts[2];
  }

  if (emoObj["average-emotions"]["afraid"] <= emoValMax / secondEmotionMax) {
    flickerRate = flickerRateOpts[0];
  } else if (emoObj["average-emotions"]["afraid"] <=
             (emoValMax / secondEmotionMax) * 2) {
    flickerRate = flickerRateOpts[1];
  } else if (emoObj["average-emotions"]["afraid"] <= emoValMax) {
    flickerRate = flickerRateOpts[2];
  }

  if (emoObj["average-emotions"]["happy"] <= emoValMax / secondEmotionMax) {
    brightness = brightnessOpts[0];
  } else if (emoObj["average-emotions"]["happy"] <=
             (emoValMax / secondEmotionMax) * 2) {
    brightness = brightnessOpts[1];
  } else if (emoObj["average-emotions"]["happy"] <= emoValMax) {
    brightness = brightnessOpts[2];
  }

  if (emoObj["average-emotions"]["sad"] <= emoValMax / secondEmotionMax) {
    size = sizeOpts[0];
  } else if (emoObj["average-emotions"]["sad"] <=
             (emoValMax / secondEmotionMax) * 2) {
    size = sizeOpts[1];
  } else if (emoObj["average-emotions"]["sad"] <= emoValMax) {
    size = sizeOpts[1];
  }

  if (emoObj["average-emotions"]["surprised"] <= emoValMax / secondEmotionMax) {
    spin = spinOpts[0];
  } else if (emoObj["average-emotions"]["surprised"] <=
             (emoValMax / secondEmotionMax) * 2) {
    spin = spinOpts[1];
  } else if (emoObj["average-emotions"]["surprised"] <= emoValMax) {
    spin = spinOpts[1];
  }

  paragraph = "您生成了一个 " + speed + ", " + size + " " + objects +
              " ，它散发着 " + brightness + ", " + flickerRate + " " +
              radiance + "。 " + orbitingPlanets + "。它的旋转速度如同 " +
              spin + "。";

  return paragraph;
}

//--------------------------------------------------------------
string astralObjectGenerator::generateEnglishText(ofJson emoObj) {
  /*
  angry 		[0]
  disgust 	[1]
  scared 		[2]
  happy 		[3]
  sad 		[4]
  surprised 	[5]
  nuetral 	[6]
  */

  string objects, radiance, speed, orbitingPlanets, flickerRate, brightness,
      size, spin, paragraph;

  int primaryEmotionMax = 7;
  int secondEmotionMax = 3;

  float emoValMax = 1.0;

  // Primary Emotions
  string objectOpts[primaryEmotionMax] = {"tight cluster of objects",
                                          "clump of objects",
                                          "object",
                                          "object",
                                          "object",
                                          "field of objects",
                                          "solitary object"};

  string radianceOpts[primaryEmotionMax] = {
      "red radiance",         "neon orange radiance", "white radiance",
      "golden radiance",      "blue radiance",        "multicolored radiance",
      "non-existent radiance"};

  // Secondary Emotions
  string speedOpts[secondEmotionMax] = {"slow moving", "fast moving",
                                        "high speed"};
  string orbitingPlanetsOpts[secondEmotionMax] = {
      "Not a single object orbits around it",
      "A few objects have been caught in its orbit",
      "Many other smaller objects orbit around it"};
  string flickerRateOpts[secondEmotionMax] = {"steady", "wavering",
                                              "flickering"};
  string brightnessOpts[secondEmotionMax] = {"dim", "bright", "blinding"};
  string sizeOpts[secondEmotionMax] = {"dwarfish", "sun-sized", "massive"};
  string spinOpts[secondEmotionMax] = {
      "an abandoned carousel", "a wind turbine", "a category 5 hurricane"};

  if (emoObj["dominant-emotion"] == "Anger") {
    objects = objectOpts[0];
    radiance = radianceOpts[0];
  } else if (emoObj["dominant-emotion"] == "Disgust") {
    objects = objectOpts[1];
    radiance = radianceOpts[1];
  } else if (emoObj["dominant-emotion"] == "Fear") {
    objects = objectOpts[2];
    radiance = radianceOpts[2];
  } else if (emoObj["dominant-emotion"] == "Happiness") {
    objects = objectOpts[3];
    radiance = radianceOpts[3];
  } else if (emoObj["dominant-emotion"] == "Sadness") {
    objects = objectOpts[4];
    radiance = radianceOpts[4];
  } else if (emoObj["dominant-emotion"] == "Surprise") {
    objects = objectOpts[5];
    radiance = radianceOpts[5];
  } else if (emoObj["dominant-emotion"] == "Neutral") {
    objects = objectOpts[6];
    radiance = radianceOpts[6];
  }

  if (emoObj["average-emotions"]["angry"] <= emoValMax / secondEmotionMax) {
    speed = speedOpts[0];
  } else if (emoObj["average-emotions"]["angry"] <=
             (emoValMax / secondEmotionMax) * 2) {
    speed = speedOpts[1];
  } else if (emoObj["average-emotions"]["angry"] <= emoValMax) {
    speed = speedOpts[2];
  }

  if (emoObj["average-emotions"]["disgusted"] <= emoValMax / secondEmotionMax) {
    orbitingPlanets = orbitingPlanetsOpts[0];
  } else if (emoObj["average-emotions"]["disgusted"] <=
             (emoValMax / secondEmotionMax) * 2) {
    orbitingPlanets = orbitingPlanetsOpts[1];
  } else if (emoObj["average-emotions"]["disgusted"] <= emoValMax) {
    orbitingPlanets = orbitingPlanetsOpts[2];
  }

  if (emoObj["average-emotions"]["afraid"] <= emoValMax / secondEmotionMax) {
    flickerRate = flickerRateOpts[0];
  } else if (emoObj["average-emotions"]["afraid"] <=
             (emoValMax / secondEmotionMax) * 2) {
    flickerRate = flickerRateOpts[1];
  } else if (emoObj["average-emotions"]["afraid"] <= emoValMax) {
    flickerRate = flickerRateOpts[2];
  }

  if (emoObj["average-emotions"]["happy"] <= emoValMax / secondEmotionMax) {
    brightness = brightnessOpts[0];
  } else if (emoObj["average-emotions"]["happy"] <=
             (emoValMax / secondEmotionMax) * 2) {
    brightness = brightnessOpts[1];
  } else if (emoObj["average-emotions"]["happy"] <= emoValMax) {
    brightness = brightnessOpts[2];
  }

  if (emoObj["average-emotions"]["sad"] <= emoValMax / secondEmotionMax) {
    size = sizeOpts[0];
  } else if (emoObj["average-emotions"]["sad"] <=
             (emoValMax / secondEmotionMax) * 2) {
    size = sizeOpts[1];
  } else if (emoObj["average-emotions"]["sad"] <= emoValMax) {
    size = sizeOpts[1];
  }

  if (emoObj["average-emotions"]["surprised"] <= emoValMax / secondEmotionMax) {
    spin = spinOpts[0];
  } else if (emoObj["average-emotions"]["surprised"] <=
             (emoValMax / secondEmotionMax) * 2) {
    spin = spinOpts[1];
  } else if (emoObj["average-emotions"]["surprised"] <= emoValMax) {
    spin = spinOpts[1];
  }

  paragraph = "You have generated a " + speed + ", " + size + " " + objects +
              " with a " + brightness + ", " + flickerRate + " " + radiance +
              ". " + orbitingPlanets + ". It is rotating about as fast as " +
              spin + ".";

  return paragraph;
}