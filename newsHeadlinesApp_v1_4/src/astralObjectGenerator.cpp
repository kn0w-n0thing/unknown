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
  "无明显倾向的" [6]
  */

  string objects, radiance, speed, orbitingPlanets, flickerRate, brightness,
      size, spin, paragraph, units;

  int primaryEmotionMax = 7;
  int secondEmotionMax = 3;
  int secondEmo2D = 5;

  float emoValMax = 1.0;

  // Primary Emotions
  string objectOpts[primaryEmotionMax] = {
      "紧簇成群的星体", "星群", "星体", "星体", "星体", "星域", "孤立星体"};
  string radianceOpts[primaryEmotionMax] = {
      "红光", "霓虹橙光", "白光", "金光", "蓝光", "五彩光芒", "朦胧暗昧的光"};
  string unitsOpts[primaryEmotionMax] = {"丛", "簇", "颗", "个",
                                         "个", "片", "颗"};

  // Secondary Emotions
  string speedOpts[secondEmotionMax][secondEmo2D] = {
      {"缓慢移动的", "漂浮的", "徐徐移动的", "漂浮的", "缓慢移动的"},
      {"快速移动的", "中速移动的", "快速移动的", "中速移动的", "快速移动的"},
      {"高速运动的", "疾速移动的", "如波浪般翻滚起伏的", "汹涌运动的",
       "高速运动的"}};
  string orbitingPlanetsOpts[secondEmotionMax][secondEmo2D] = {
      {"没有其他星体围绕它运行", "没有其他星体围绕它运行",
       "它孤立于其他星体，没有卫星环绕", "没有其他星体围绕它运行",
       "没有其他星体围绕它运行"},
      {"有数个星体被它的引力捕获，围绕着它运行",
       "有数个星体被它的引力捕获，围绕着它运行", "能看见它的周围有几颗卫星环绕",
       "它的周边环绕着其他引人注目的天体",
       "有数个星体被它的引力捕获，围绕着它运行"},
      {"有许多较小的星体围绕着它运行", "有一小簇更小的天体围绕着它运行",
       "它的大气层外点缀着许多体积更小的卫星", "有许多较小的星体围绕着它运行",
       "有许多较小的星体围绕着它运行"}};
  string flickerRateOpts[secondEmotionMax][secondEmo2D] = {
      {"稳定的", "均匀的", "稳定的", "稳定的", "稳定的"},
      {"忽明忽灭的", "闪烁的", "明暗不定的", "忽明忽灭的", "闪烁的"},
      {"忽隐忽现的", "闪烁的", "颤动的", "忽隐忽现的", "脉冲般的"}};
  string brightnessOpts[secondEmotionMax][secondEmo2D] = {
      {"暗淡的", "昏暗的", "暗哑的", "黯淡的", "暗淡的"},
      {"明亮的", "明亮的", "微弱的", "辉耀的", "极光般的"},
      {"眩目的", "鲜艳的", "灿烂的", "耀眼的", "眩目的"}};
  string sizeOpts[secondEmotionMax][secondEmo2D] = {
      {"矮星大小的", "中等大小的", "小型的", "小型的", "矮星大小的"},
      {"太阳大小的", "大型的", "大型的", "中型的", "大型的"},
      {"巨大的", "巨型的", "极大的", "庞大的", "巨大的"}};
  string spinOpts[secondEmotionMax][secondEmo2D] = {
      {"一座废弃的旋转木马", "旧的吱吱作响的马车车轮", "一座废弃的旋转木马",
       "一台无风时的风车", "旧得吱吱作响的马车车轮"},
      {"一台风力发电机", "一个悠悠球", "一只追着自己尾巴转圈的小狗",
       "一片正在飘落的树叶", "一只被风吹着跑的塑料袋"},
      {"一阵五级飓风", "你在日常生活中为了形成习惯而进行动作的频繁重复",
       "一台台式风扇", "一阵旋风", "喷气式飞机的引擎"}};

  if (emoObj["original-dominant-emotion"] == "Anger") {
    objects = objectOpts[0];
    radiance = radianceOpts[0];
    units = unitsOpts[0];
  } else if (emoObj["original-dominant-emotion"] == "Disgust") {
    objects = objectOpts[1];
    radiance = radianceOpts[1];
    units = unitsOpts[1];
  } else if (emoObj["original-dominant-emotion"] == "Fear") {
    objects = objectOpts[2];
    radiance = radianceOpts[2];
    units = unitsOpts[2];
  } else if (emoObj["original-dominant-emotion"] == "Happiness") {
    objects = objectOpts[3];
    radiance = radianceOpts[3];
    units = unitsOpts[3];
  } else if (emoObj["original-dominant-emotion"] == "Sadness") {
    objects = objectOpts[4];
    radiance = radianceOpts[4];
    units = unitsOpts[4];
  } else if (emoObj["original-dominant-emotion"] == "Surprise") {
    objects = objectOpts[5];
    radiance = radianceOpts[5];
    units = unitsOpts[5];
  } else if (emoObj["original-dominant-emotion"] == "Neutral") {
    objects = objectOpts[6];
    radiance = radianceOpts[6];
    units = unitsOpts[6];
  }

  if (emoObj["average-emotions"]["angry"] <= emoValMax / secondEmotionMax) {
    speed = speedOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["angry"] <=
             (emoValMax / secondEmotionMax) * 2) {
    speed = speedOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["angry"] <= emoValMax) {
    speed = speedOpts[2][(int)ofRandom(secondEmo2D)];
  }

  if (emoObj["average-emotions"]["disgusted"] <= emoValMax / secondEmotionMax) {
    orbitingPlanets = orbitingPlanetsOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["disgusted"] <=
             (emoValMax / secondEmotionMax) * 2) {
    orbitingPlanets = orbitingPlanetsOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["disgusted"] <= emoValMax) {
    orbitingPlanets = orbitingPlanetsOpts[2][(int)ofRandom(secondEmo2D)];
  }

  if (emoObj["average-emotions"]["afraid"] <= emoValMax / secondEmotionMax) {
    flickerRate = flickerRateOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["afraid"] <=
             (emoValMax / secondEmotionMax) * 2) {
    flickerRate = flickerRateOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["afraid"] <= emoValMax) {
    flickerRate = flickerRateOpts[2][(int)ofRandom(secondEmo2D)];
  }

  if (emoObj["average-emotions"]["happy"] <= emoValMax / secondEmotionMax) {
    brightness = brightnessOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["happy"] <=
             (emoValMax / secondEmotionMax) * 2) {
    brightness = brightnessOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["happy"] <= emoValMax) {
    brightness = brightnessOpts[2][(int)ofRandom(secondEmo2D)];
  }

  if (emoObj["average-emotions"]["sad"] <= emoValMax / secondEmotionMax) {
    size = sizeOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["sad"] <=
             (emoValMax / secondEmotionMax) * 2) {
    size = sizeOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["sad"] <= emoValMax) {
    size = sizeOpts[1][(int)ofRandom(secondEmo2D)];
  }

  if (emoObj["average-emotions"]["surprised"] <= emoValMax / secondEmotionMax) {
    spin = spinOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["surprised"] <=
             (emoValMax / secondEmotionMax) * 2) {
    spin = spinOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["surprised"] <= emoValMax) {
    spin = spinOpts[1][(int)ofRandom(secondEmo2D)];
  }

  paragraph = "您生成了一" + units + speed + "、" + size + objects +
              "，它散发出" + brightness + "、" + flickerRate + radiance + "。" +
              orbitingPlanets + "。它的旋转速度如同" + spin + "。";

  return paragraph;
}

//--------------------------------------------------------------
string astralObjectGenerator::generateEnglishText(ofJson emoObj) {
  /*
  angry 		[0]
  disgust 	[1]
  scared 		[2]
  happy 		[3]
  sad 		  [4]
  surprised [5]
  nuetral 	[6]
  */

  string objects, radiance, speed, orbitingPlanets, flickerRate, brightness,
      size, spin, paragraph;

  int primaryEmotionMax = 7;
  int secondEmotionMax = 3;
  int secondEmo2D = 5;

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
  string speedOpts[secondEmotionMax][secondEmo2D] = {
      {"slow moving", "floating", "slow moving", "floating", "slow moving"},
      {"fast moving", "medium-speed", "fast moving", "medium-speed",
       "fast moving"},
      {"high-speed", "velocious", "billowing", "surging", "high-speed"}};
  string orbitingPlanetsOpts[secondEmotionMax][secondEmo2D] = {
      {"Not a single object orbits around it", "Nothing orbits around it",
       "It is rather solitary with nothing else orbiting its surroundings",
       "Not a single object orbits around it",
       "Not a single object orbits around it"},
      {"A few objects have been caught in its orbit",
       "A few objects have been caught in its orbit",
       "Several moons can been observed in its orbit",
       "It is surrounded by several noticeable cellestial bodies",
       "A few objects have been caught in its orbit"},
      {"Many other smaller objects orbit around it",
       "A cluster of smaller celestial objects orbits around it",
       "Its atmosphere is dotted with smaller sattelite objects",
       "Many other smaller objects orbit around it",
       "Many other smaller objects orbit around it"}};
  string flickerRateOpts[secondEmotionMax][secondEmo2D] = {
      {"steady", "uniform", "stable", "steady", "steady"},
      {"wavering", "twinkling", "oscillating", "wavering", "twinkling"},
      {"flickering", "flashing", "quivering", "flickering", "pulsating"}};
  string brightnessOpts[secondEmotionMax][secondEmo2D] = {
      {"dim", "dark", "dull", "murky", "dim"},
      {"bright", "luminous", "glimmery", "sunny", "auroral"},
      {"blinding", "vivid", "brilliant", "dazzling", "blinding"}};
  string sizeOpts[secondEmotionMax][secondEmo2D] = {
      {"dwarfish", "modest", "small", "small", "dwarfish"},
      {"sun-sized", "large", "sizable", "moderately sized", "sizable"},
      {"massive", "colossal", "enormous", "unwieldy", "massive"}};
  string spinOpts[secondEmotionMax][secondEmo2D] = {
      {"an abandoned carousel", "an old creaky wagon wheel",
       "an abandoned carousel", "a windmill on a calm day",
       "an old creaky wagon wheel"},
      {"a wind turbine", " a yo-yo",
       "a dog trying to catch its tail in its mouth", "a falling leaf",
       "a plastic bag caught in the wind"},
      {"a category five hurricane", "the habitualization of your daily life",
       "a desktop fan", "a whilrwind", "a jet engine"}};

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
    speed = speedOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["angry"] <=
             (emoValMax / secondEmotionMax) * 2) {
    speed = speedOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["angry"] <= emoValMax) {
    speed = speedOpts[2][(int)ofRandom(secondEmo2D)];
  }

  if (emoObj["average-emotions"]["disgusted"] <= emoValMax / secondEmotionMax) {
    orbitingPlanets = orbitingPlanetsOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["disgusted"] <=
             (emoValMax / secondEmotionMax) * 2) {
    orbitingPlanets = orbitingPlanetsOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["disgusted"] <= emoValMax) {
    orbitingPlanets = orbitingPlanetsOpts[2][(int)ofRandom(secondEmo2D)];
  }

  if (emoObj["average-emotions"]["afraid"] <= emoValMax / secondEmotionMax) {
    flickerRate = flickerRateOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["afraid"] <=
             (emoValMax / secondEmotionMax) * 2) {
    flickerRate = flickerRateOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["afraid"] <= emoValMax) {
    flickerRate = flickerRateOpts[2][(int)ofRandom(secondEmo2D)];
  }

  if (emoObj["average-emotions"]["happy"] <= emoValMax / secondEmotionMax) {
    brightness = brightnessOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["happy"] <=
             (emoValMax / secondEmotionMax) * 2) {
    brightness = brightnessOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["happy"] <= emoValMax) {
    brightness = brightnessOpts[2][(int)ofRandom(secondEmo2D)];
  }

  if (emoObj["average-emotions"]["sad"] <= emoValMax / secondEmotionMax) {
    size = sizeOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["sad"] <=
             (emoValMax / secondEmotionMax) * 2) {
    size = sizeOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["sad"] <= emoValMax) {
    size = sizeOpts[1][(int)ofRandom(secondEmo2D)];
  }

  if (emoObj["average-emotions"]["surprised"] <= emoValMax / secondEmotionMax) {
    spin = spinOpts[0][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["surprised"] <=
             (emoValMax / secondEmotionMax) * 2) {
    spin = spinOpts[1][(int)ofRandom(secondEmo2D)];
  } else if (emoObj["average-emotions"]["surprised"] <= emoValMax) {
    spin = spinOpts[1][(int)ofRandom(secondEmo2D)];
  }

  paragraph = "You have generated a " + speed + ", " + size + " " + objects +
              " with a " + brightness + ", " + flickerRate + " " + radiance +
              ". " + orbitingPlanets + ". It is rotating about as fast as " +
              spin + ".";

  return paragraph;
}