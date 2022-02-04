#include "ofApp.h"
#include <armadillo>
#include "TrainingModel.h"
#include "GameEngine.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(220,255,255);

    gui.setup();
    gui.add(home_team_shots.setup("Home Team Shots", 0, 0, 30));
    gui.add(away_team_shots.setup("Away Team Shots", 0, 0, 30));
    gui.add(home_team_shots_on_target.setup("Home Team Shots on target", 0, 0, 30));
    gui.add(away_team_shots_on_target.setup("Away Team Shots on target", 0, 0, 30));
    gui.add(home_team_red_cards.setup("Home Team Red cards", 0, 0, 3));
    gui.add(away_team_red_cards.setup("Away Team Red cards", 0, 0, 3));

    arsenal.load("C:\\Users\\djh99\\Documents\\Arsenal.png");
    liverpool.load("C:\\Users\\djh99\\Documents\\Liverpool.png");
    mancity.load("C:\\Users\\djh99\\Documents\\Man City.png");
    manunited.load("C:\\Users\\djh99\\Documents\\Man United.png");
    chelsea.load("C:\\Users\\djh99\\Documents\\Chelsea.png");
    tottenham.load("C:\\Users\\djh99\\Documents\\Tottenham.png");

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    int width = ofGetWidth(), height = ofGetHeight();

    ofEnableAlphaBlending();
    ofSetColor(255,255,255);

    arsenal.draw(20, 0, 100, 120);
    liverpool.draw(width / 6 + 20, 0, 100, 120);
    mancity.draw(width / 3, 0, 180, 120);
    manunited.draw(width / 2 + 20, 0, 100, 120);
    chelsea.draw(width * 2 / 3 + 20, 0, 100, 120);
    tottenham.draw(width * 5 / 6 + 20, 0, 100, 120);

    gui.draw();

    ofSetColor(0, 0, 0);
    ofDrawBitmapString("Left Click to choose Home team and Right Click to choose Away team",300, 300);

    if (keypressed)
    {
        ofDrawBitmapString("Home team's (" + home_team + ") winning Percentage is: " + std::to_string(100 * winning_percentage), width / 2, height/2);
        ofDrawBitmapString("Drawing Percentage is: " + std::to_string(100 * drawing_percentage), width / 2 , height / 2 + 15);
        ofDrawBitmapString("Away team's (" + away_team + ") winning Percentage is: " + std::to_string(100 * losing_percentage), width / 2 , height / 2 + 30);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key)
    {
    case 'r':
        GameEngine game_engine(home_team, away_team);

        game_engine.setResultMatrix();
        game_engine.setFeatureMatrix();

        mat win_result_matrix = game_engine.getWinResultMatrix();
        mat draw_result_matrix = game_engine.getDrawResultMatrix();
        mat lose_result_matrix = game_engine.getLoseResultMatrix();

        game_engine.gradientDescent(win_result_matrix);
        mat win_parameters = game_engine.getParameters();

        game_engine.resetParameters();
        game_engine.gradientDescent(draw_result_matrix);
        mat draw_parameters = game_engine.getParameters();

        game_engine.resetParameters();
        game_engine.gradientDescent(lose_result_matrix);
        mat lose_parameters = game_engine.getParameters();

        mat user_feature(1, 9);
        user_feature << 1 << 1 << 0 << home_team_shots << away_team_shots << home_team_shots_on_target << away_team_shots_on_target
            << home_team_red_cards << away_team_red_cards;

        winning_percentage = sigmoid(user_feature * win_parameters)(0, 0);
        losing_percentage = sigmoid(user_feature * lose_parameters)(0, 0);
        drawing_percentage = 1 - (winning_percentage + losing_percentage);

        keypressed = true;
    deafault:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    int width = ofGetWidth(), height = ofGetHeight();

    if (20 <= x && x < width / 6 + 20 && 0 <= y && y <= 120)
    {
        if (button == 0)
        {
            home_team = "Arsenal";
        }
        else if (button == 2)
        {
            away_team = "Arsenal";
        }
    }
    else if (width / 6 + 20 <= x && x < width / 3 && 0 <= y && y <= 120)
    {
        if (button == 0)
        {
            home_team = "Liverpool";
        }
        else if (button == 2)
        {
            away_team = "Liverpool";
        }
    }
    else if (width / 3 <= x && x < width / 2 + 20 && 0 <= y && y <= 120)
    {
        if (button == 0)
        {
            home_team = "Man City";
        }
        else if (button == 2)
        {
            away_team = "Man City";
        }
    }
    else if (width / 2 + 20 <= x && x < width * 2 / 3 + 20 && 0 <= y && y <= 120)
    {
        if (button == 0)
        {
            home_team = "Man United";
        }
        else if (button == 2)
        {
            away_team = "Man United";
        }
    }
    else if (width * 2 / 3 + 20 <= x && x < width * 5 / 6 + 20 && 0 <= y && y <= 120)
    {
        if (button == 0)
        {
            home_team = "Chelsea";
        }
        else if (button == 2)
        {
            away_team = "Chelsea";
        }
    }
    else if ( x >= width * 5 / 6 + 20 && 0 <= y && y <= 120)
    {
        if (button == 0)
        {
            home_team = "Tottenham";
        }
        else if (button == 2)
        {
            away_team = "Tottenham";
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
