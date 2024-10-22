#pragma once
#include "Global.h"

struct baseEntity {
	Vector2 position;
	float angle;

	virtual void Update();
	virtual void Draw();

	baseEntity(Vector2 pos, float angle);
};

struct player : public baseEntity {
	void Update() override;
	void Draw() override;

	player(Vector2 pos, float angle);
};

struct enemy : public baseEntity {
	void Update() override;
	void Draw() override;

	enemy(Vector2 pos, float angle);
};

struct item : public baseEntity {
	void Update() override;
	void Draw() override;

	item(Vector2 pos);
};