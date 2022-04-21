#pragma once

#include "Context.h"

class GameObject {
public:
	virtual void onAttach(Context* context);
	virtual void onDetach();

	
	virtual void onUpdate() { };
	virtual void onRender() { };
	
protected:
	virtual void onCreate() { };
	virtual void onRelease() { };

	Context* const getContext();

private:
	Context* context = nullptr;
};