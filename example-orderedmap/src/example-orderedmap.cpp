//                                      __
//     ____ ___  ___  ____ ___  ____   / /__   __
//    / __ `__ \/ _ \/ __ `__ \/ __ \ / __/ | / /
//   / / / / / /  __/ / / / / / /_/ // /_ | |/ /
//  /_/ /_/ /_/\___/_/ /_/ /_/\____(_)__/ |___/
//
//
//  Created by Memo Akten, www.memo.tv
//
//  acts like a std::map, but preserves order of insertion
//  I use this now with std::shared_ptr instead of ofxMSAOrderedPointerMap
//


#include "ofxMSAOrderedMap.h"
#include "ofMain.h"


// this will store our output
stringstream outputStream;


// an arbitrary class to hold some data
class Data {
public:
    float age;
    float height;

    Data(float age, float height) {
        this->age = age;
        this->height = height;
    }

    ~Data() {
        outputStream << "* deleting... " << toString() << endl;
    }

    string toString() {
        return "[ age: " + ofToString(age) + ", height: " + ofToString(height) + "cm ]";
    }
};




class ofApp : public ofBaseApp{
public:

    void tester() {
        outputStream << "STARTING..." << endl << endl;

        // create an ordered named map of PersonData pointers
        msa::OrderedMap<string, shared_ptr<Data> >myContainer;

        // add some data
        outputStream << "adding data..." << endl;
        myContainer.push_back("memo", make_shared<Data>(37, 175));   // push myContainer shared pointer of the object into the OrderedPointerMap
        myContainer.push_back("jane", make_shared<Data>(27, 165));
        myContainer.push_back("pearl", make_shared<Data>(2, 15));
        myContainer.push_back("bruce", make_shared<Data>(3, 12));

        outputStream << "memo - " << myContainer["memo"]->toString() << endl;
        outputStream << "jane - " << myContainer["jane"]->toString() << endl;
        outputStream << "pearl - " << myContainer["pearl"]->toString() << endl;
        outputStream << "bruce - " << myContainer["bruce"]->toString() << endl;

        // i know this one doesn't exist, so checking first to avoid an exception
        if(myContainer.exists("blufo")) outputStream << "blufo - " << myContainer["blufo"]->toString() << endl;
        else outputStream << "blufo doesn't exist!" << endl;


        // accessing via name
        outputStream << endl << endl << "accessing and modifying via names (make 1 year older)..." << endl;
        // various different ways of modifying:
        myContainer["memo"]->age = 38;
        myContainer["jane"]->age = myContainer["jane"]->age + 1;
        myContainer["pearl"]->age += 1;
        myContainer["bruce"]->age++;
        outputStream << "memo - " << myContainer["memo"]->toString() << endl;
        outputStream << "jane - " << myContainer["jane"]->toString() << endl;
        outputStream << "pearl - " << myContainer["pearl"]->toString() << endl;
        outputStream << "bruce - " << myContainer["bruce"]->toString() << endl;


        // accessing via index
        outputStream << endl << endl << "accessing and modifying via index (make 1 year older)..." << endl;
        for(int i=0; i<myContainer.size(); i++) {
            myContainer[i]->age ++;
            outputStream << myContainer.keyFor(i) << " - " << myContainer[i]->toString() << endl;
        }

        // getting index for name
        outputStream << endl << endl << "accessing and modifying via index (make 1 year older)..." << endl;
        outputStream << "memo - " << myContainer.indexFor("memo") << endl;
        outputStream << "jane - " << myContainer.indexFor("jane") << endl;
        outputStream << "pearl - " << myContainer.indexFor("pearl") << endl;
        outputStream << "bruce - " << myContainer.indexFor("bruce") << endl;

        // erase by index
        outputStream << endl << endl << "erase by index... erase(1)" << endl;
        myContainer.erase(1); // erasing jane
        for(int i=0; i<myContainer.size(); i++) {
            outputStream << myContainer.keyFor(i) << " - " << myContainer[i]->toString() << endl;
        }

        // erase by key
        outputStream << endl << endl << "erase by key... erase('bruce') " << endl;
        myContainer.erase("bruce"); // erasing bruce
        for(int i=0; i<myContainer.size(); i++) {
            outputStream << myContainer.keyFor(i) << " - " << myContainer[i]->toString() << endl;
        }


        // change key
        outputStream << endl << endl << "change key..." << endl;
        myContainer.changeKey(0, "mehmet");
        myContainer.changeKey("pearl", "pearlikens");
        for(int i=0; i<myContainer.size(); i++) {
            outputStream << myContainer.keyFor(i) << " - " << myContainer[i]->toString() << endl;
        }

        outputStream << endl << "ENDING..." << endl << endl;
    }

    //--------------------------------------------------------------
    void setup() {
        tester();
        cout << outputStream.str();
    }

    //--------------------------------------------------------------
    void draw() {
        ofBackground(0);
        ofDrawBitmapString(outputStream.str(), 20, 30);
    }

};

//========================================================================
int main( ){
    ofSetupOpenGL(800, 800, OF_WINDOW);			// <-------- setup the GL context
    ofRunApp( new ofApp());
}
