//============================================================================
// Name        : Patterns.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : extended initializer lists only available with -std=c++11
//============================================================================

#include <iostream>
#include <vector>

using namespace std;

struct Observer {
	virtual void notify() = 0;//Has to be virtual if abstract
	void signal() {}
protected:
	~Observer() {}
};
/**
 * A view manages the appearance of one UI object, a textfield, button...
 */
class View : public Observer {
public:
	int identity;
	View(int identity) : identity{identity}{}
	View(const View &that) : identity{that.identity} {}//Copy constructor
	void notify() {}
	void signal() {}
	virtual ~View(){}//The virtual method requires a virtual destructor
};

/**
 * The model is the data, it holds the data and provide mechanisms to read and manipulate
 */
struct Model {
	vector<View> observers;
	int count = 0;
public:
	void subscribe(View v) {
		observers.push_back(v);
	}
	void unSubscribe(View v) {
		for(auto iterator = observers.begin(); iterator != observers.end(); iterator++) {
			if(iterator->identity == v.identity)
				observers.erase(iterator);
		}

	}
};

/**
 * A controller manages user input as related to a view. a controller is coupled to view
 */
struct Controller {
	View view;
public:
	Controller(View newView) : view{newView} {

	}
};

int main() {
	Model model;
	View view{42};
	View view2 = view;
	view.identity = 99;
	View view3{view};
	model.subscribe(view);
	cout << model.observers.at(0).identity<<endl;
	Controller cnt{View{42}};
	//model.unSubscribe(view);
	cout << model.observers.at(0).identity<<endl; // prints !!!Hello World!!!
	cout << view.identity<<endl;
	cout << view2.identity<<endl;
	cout << view3.identity<<endl;
	return 0;
}
