#pragma once

#include "Body.h"
#include "Vectors.h"


class Planet : public Body
{
public:

	Planet() {}
	~Planet() {}

public:
	
	Vec2 selfGravity;
};