#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int len_param = 280;
	int radius = 250;

	for (int z = 0; z > -1000; z -= 10) {

		ofSetColor(ofMap(z, 0, -1000, 0, 239));

		ofBeginShape();

		ofVertex(glm::vec3(len_param, len_param, z));
		ofVertex(glm::vec3(len_param, -len_param, z));
		ofVertex(glm::vec3(-len_param, -len_param, z));
		ofVertex(glm::vec3(-len_param, len_param, z));

		ofNextContour();

		for (int deg = 0; deg < 360; deg += 1) {

			auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z);
			auto tmp_radius = ofMap(ofNoise(location.x * 0.005, location.y * 0.005, location.z * 0.005, ofGetFrameNum() * 0.005), 0, 1, radius * 0.5, len_param);
			ofVertex(glm::vec3(tmp_radius * cos(deg * DEG_TO_RAD), tmp_radius * sin(deg * DEG_TO_RAD), z));
		}

		ofEndShape();
	}

	for (int i = 0; i < 10; i++) {

		auto x = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -radius * 0.5, radius * 0.5);
		auto y = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -radius * 0.5, radius * 0.5);
		auto z = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0, -1000);

		ofSetColor(ofMap(z, 0, -1000, 0, 239));
		ofDrawSphere(glm::vec3(x, y, z), 5);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}