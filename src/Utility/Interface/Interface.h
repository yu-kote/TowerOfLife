#pragma once
#include "cinder/params/Params.h"



class Interface
{
public:
	Interface(ci::params::InterfaceGlRef _inter) {
		Param = _inter;
	}

	static Interface single() {
		static Interface interface(ci::params::InterfaceGl::create("Interface", ci::Vec2i(200, 300)));
		return interface;
	}
	ci::params::InterfaceGlRef Param;
private:

};

#define Params Interface::single().Param