#pragma once

#include <string>
#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:

        bool keypressed = false;

        double winning_percentage;
        double drawing_percentage;
        double losing_percentage;

        std::string home_team;
        std::string away_team;
        
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofImage arsenal;
        ofImage chelsea;
        ofImage mancity;
        ofImage liverpool;
        ofImage manunited;
        ofImage tottenham;

        ofxPanel gui;

        ofxIntSlider home_team_shots;
        ofxIntSlider away_team_shots;
        ofxIntSlider home_team_shots_on_target;
        ofxIntSlider away_team_shots_on_target;
        ofxIntSlider home_team_red_cards;
        ofxIntSlider away_team_red_cards;
		
};
