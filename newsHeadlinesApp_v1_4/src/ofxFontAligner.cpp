#include "ofApp.h"

//--------------------------------------------------------------
void ofxFontAligner::init(string fontPath, float fontSize) {
	path = fontPath;
	fSize = fontSize;

	font.loadFont(path, fSize, true, true);

	boundingBox = ofColor(255, 51, 201);
	lHeight = font.getLineHeight() / 4;

	mainColor = ofColor(255);
}

//--------------------------------------------------------------
void ofxFontAligner::setColor(ofColor c){
	mainColor = c;
}

//--------------------------------------------------------------
void ofxFontAligner::setFontSize(float fs) {
	font.loadFont(path, fs, true, true);
}

//--------------------------------------------------------------
ofVec2f ofxFontAligner::drawLeft(string t, float x, float y, bool debug) {
	ofSetColor(mainColor);

	float h = font.getLineHeight();

	y += h;

	ofRectangle r = font.getStringBoundingBox(t, 0, 0);
	font.drawString(t, x, y);

	if (debug) {
		ofSetColor(boundingBox);
		ofNoFill();
		ofDrawRectangle(x , y - h + lHeight, r.width, r.height);
		ofSetColor(255);
		ofFill();
		ofSetColor(underlineColor);
		ofLine(x, y, x + r.width, y);
		float lineCount = 0;
		for (int i = 0; i < t.size(); i++) {
			if (t[i] == '\n') {
				ofLine(x, y + (h * lineCount), x + r.width, y + (h * lineCount));
				lineCount++;
			}
		}
		ofLine(x, y + (h * lineCount), x + r.width, y + (h * lineCount));
	}

	ofVec2f boxSize;
	boxSize.set(r.width, r.height + lHeight);

	return boxSize;
}

//--------------------------------------------------------------
ofVec2f ofxFontAligner::drawCentered(string t, float x, float y, bool debug) {
	ofSetColor(mainColor);

	float h = font.getLineHeight();

	vector<string> lines;

	for (int i = 0; i < t.size(); i++) {
		if (t[i] == '\n') {
			lines = ofSplitString(t, "\n");
		}
	}

	if (lines.size() == 0) {
		lines.push_back(t);
	}

	ofRectangle r;
	ofVec2f offset;
	vector<ofVec2f> allOffsets;
	vector<float> linesWidth;

	for (int i = 0; i < lines.size(); i++) {
		r = font.getStringBoundingBox(lines[i], 0, 0);
		linesWidth.push_back(r.width);
		offset.set( floor(-r.x - r.width * 0.5f), floor(-r.y - r.height * 0.5f) );
		allOffsets.push_back(offset);
		font.drawString(lines[i], x + offset.x, y + offset.y + (h * i));
	}

	std::sort(linesWidth.begin(), linesWidth.end());
	int lastIndex = linesWidth.size() - 1;

	if (debug) {
		ofSetColor(boundingBox);
		ofNoFill();
		ofDrawRectangle(x + allOffsets[0].x, y - allOffsets[0].y - lHeight, linesWidth[lastIndex], r.height * lines.size() + lHeight / 2);
		ofSetColor(255);
		ofFill();
		ofSetColor(underlineColor);
		for (int i = 0; i < lines.size(); i++) {
			ofLine(x + allOffsets[i].x, y + allOffsets[i].y + (h * i), x + allOffsets[i].x + r.width, y + allOffsets[i].y + (h * i));
		}
	}

	ofVec2f boxSize;
	boxSize.set(r.width, r.height);

	return boxSize;
}

//--------------------------------------------------------------
ofVec2f ofxFontAligner::drawEnglishBlock(string t, float x, float y, float w, bool debug) {

	ofSetColor(mainColor);

	float h = font.getLineHeight();

	y = h + y;

	vector<string> lines;
	lines = englishLines(t, w, false);

	for (int i = 0; i < lines.size(); i++) {
		if (lines[i][0] == ' ') {
			lines[i].erase(lines[i].begin());
		}

		font.drawString(lines[i], x, y + (h * i));
	}

	if (debug) {
		ofSetColor(boundingBox);
		ofNoFill();
		ofDrawRectangle(x, y - h, w, lines.size() * font.getLineHeight());
		ofSetColor(255);
		ofFill();
		ofSetColor(underlineColor);
		for (int i = 0; i < lines.size(); i++) {
			float ny = y + (font.getLineHeight() * i );
			ofLine(x, ny, w, ny);
		}
	}

	boxSize.set(w, lines.size() * font.getLineHeight());
	lines.clear();

	return boxSize;
}

//--------------------------------------------------------------
ofVec2f ofxFontAligner::drawChineseBlock(string t, float x, float y, float w, float rightMarginError, bool debug) {

	ofSetColor(mainColor);

	float h = font.getLineHeight();

	y = h + y;

	vector<string> lines;
	lines = chineseLines(t, w, true, rightMarginError);

	for (int i = 0; i < lines.size(); i++) {
		if (lines[i][0] == ' ') {
			lines[i].erase(lines[i].begin());
		}

		font.drawString(lines[i], x, y + ((h + lHeight / 2)* i));
	}

	if (debug) {
		ofSetColor(boundingBox);
		ofNoFill();
		ofDrawRectangle(x, y - h, w, lines.size() * (font.getLineHeight() + lHeight / 2));
		ofSetColor(255);
		ofFill();
		ofSetColor(underlineColor);
		for (int i = 0; i < lines.size(); i++) {
			float ny = y + ((font.getLineHeight() + lHeight / 2) * i );
			ofLine(x, ny, w, ny);
		}
	}

	boxSize.set(w, lines.size() * (font.getLineHeight() + lHeight / 2));
	lines.clear();

	return boxSize;
}

//--------------------------------------------------------------
ofVec2f ofxFontAligner::englishGraphicBlock(string t, float x, float y, float w, bool debug) {

	ofSetColor(mainColor);

	float h = font.getLineHeight();

	y = h + y;

	vector<string> lines;
	lines = englishLines(t, w, false);

	for (int i = 0; i < lines.size(); i++) {
		if (lines[i][0] == ' ') {
			lines[i].erase(lines[i].begin());
		}

		font.drawStringAsShapes(lines[i], x, y + ((h + lHeight / 2)* i));
	}

	if (debug) {
		ofSetColor(boundingBox);
		ofNoFill();
		ofDrawRectangle(x, y - h, w, lines.size() * (font.getLineHeight() + lHeight / 2));
		ofFill();
		ofSetColor(underlineColor);
		for (int i = 0; i < lines.size(); i++) {
			float ny = y + ((font.getLineHeight() + lHeight / 2) * i );
			ofLine(x, ny, w, ny);
		}
	}

	boxSize.set(w, lines.size() * (font.getLineHeight() + lHeight / 2));
	lines.clear();

	return boxSize;
}

//--------------------------------------------------------------
ofVec2f ofxFontAligner::chineseGraphicBlock(string t, float x, float y, float w, float rightMarginError, bool debug) {

	ofSetColor(mainColor);

	float h = font.getLineHeight();

	y = h + y;

	vector<string> lines;
	lines = chineseLines(t, w, true, rightMarginError);

	for (int i = 0; i < lines.size(); i++) {
		// ofLog(OF_LOG_NOTICE, lines[i]);
		if (lines[i][0] == ' ') {
			lines[i].erase(lines[i].begin());
		}

		font.drawStringAsShapes(lines[i], x, y + ((h + lHeight)* i));
	}

	if (debug) {
		ofSetColor(boundingBox);
		ofNoFill();
		ofDrawRectangle(x, y - h, w, lines.size() * (font.getLineHeight() + lHeight));
		ofFill();
		ofSetColor(underlineColor);
		for (int i = 0; i < lines.size(); i++) {
			float ny = y + ((font.getLineHeight() + lHeight) * i );
			ofLine(x, ny, w, ny);
		}
	}

	// ofLog(OF_LOG_NOTICE, "Total Lines:" + ofToString(lines.size()));
	// ofLog(OF_LOG_NOTICE, "W:" + ofToString(w));
	// ofLog(OF_LOG_NOTICE, "line Height:" + ofToString((font.getLineHeight() + lHeight)));

	boxSize.set(w, lines.size() * (font.getLineHeight() + lHeight));
	lines.clear();

	return boxSize;
}

//--------------------------------------------------------------
ofVec2f ofxFontAligner::getChineseBlockSize(string t, float x, float y, float w, float rightMarginError) {

	float h = font.getLineHeight();

	y = h + y;

	vector<string> lines;
	lines = chineseLines(t, w, true, rightMarginError);

	for (int i = 0; i < lines.size(); i++) {
		// ofLog(OF_LOG_NOTICE, lines[i]);
		if (lines[i][0] == ' ') {
			lines[i].erase(lines[i].begin());
		}
	}

	boxSize.set(w, lines.size() * (font.getLineHeight() + lHeight));
	lines.clear();

	return boxSize;
}

//--------------------------------------------------------------
ofVec2f ofxFontAligner::getEnglishBlockSize(string t, float x, float y, float w) {

	float h = font.getLineHeight();

	y = h + y;

	vector<string> lines;
	lines = englishLines(t, w, false);

	for (int i = 0; i < lines.size(); i++) {
		//ofLog(OF_LOG_NOTICE, lines[i]);
		if (lines[i][0] == ' ') {
			lines[i].erase(lines[i].begin());
		}
	}

	boxSize.set(w, lines.size() * (font.getLineHeight() + lHeight));
	lines.clear();

	return boxSize;
}

//--------------------------------------------------------------
ofVec2f ofxFontAligner::getSimpleBlockSize(string t) {

	ofRectangle r = font.getStringBoundingBox(t, 0, 0);
	ofVec2f boxSize;
	boxSize.set(r.width, r.height);

	return boxSize;
}

//--------------------------------------------------------------
vector<string> ofxFontAligner::chineseLines(string t, float w, bool wordCut, float rightMarginError) {

	string singleLine = "";
	vector<string> lines;

	for (int i = 0; i < t.size(); i++) {
		vector<string> words;
		float tmpWidth = font.stringWidth(ofToString(t[i]));

		if (font.stringWidth(singleLine) > w - tmpWidth - fSize * rightMarginError) { //*1.5 for a small margin of error for the last char of the line

			if (singleLine[singleLine.size()] != ' ') {

				if (!wordCut) {
					words = ofSplitString(singleLine, " ");
					singleLine = "";
					for (int w = 0; w < words.size() - 1; w++) {
						singleLine += (words[w] + " ");
					}
				}
			}

			lines.push_back(singleLine);

			if (wordCut) {
				singleLine = t[i];
			} else {
				singleLine = words[words.size() - 1] + t[i];
			}

		} else {
			singleLine += t[i];
		}

		words.clear();
	}

	if (singleLine != "") {
		lines.push_back(singleLine);
	}

	return lines;
}

//--------------------------------------------------------------
vector<string> ofxFontAligner::englishLines(string t, float w, bool wordCut) {

	string singleLine = "";
	vector<string> lines;

	for (int i = 0; i < t.size(); i++) {
		vector<string> words;
		float tmpWidth = font.stringWidth(ofToString(t[i]));

		if (font.stringWidth(singleLine) > w - tmpWidth) {

			if (singleLine[singleLine.size()] != ' ') {

				if (!wordCut) {
					words = ofSplitString(singleLine, " ");
					singleLine = "";
					for (int w = 0; w < words.size() - 1; w++) {
						singleLine += (words[w] + " ");
					}
				}
			}

			lines.push_back(singleLine);

			if (wordCut) {
				singleLine = t[i];
			} else {
				singleLine = words[words.size() - 1] + t[i];
			}

		} else {
			singleLine += t[i];
		}

		words.clear();
	}

	if (singleLine != "") {
		lines.push_back(singleLine);
	}

	return lines;
}

//--------------------------------------------------------------
