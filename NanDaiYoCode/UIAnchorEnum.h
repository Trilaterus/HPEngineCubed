/*
Split into its own file its a list of anchor enums
needed to position a UI (or UIPosition)
*/

#pragma once

enum UIAnchor
{
	CENTRE = 0,
	LEFT = 1,
	RIGHT = 2,
	TOP = 4,
	BOT = 8
};

inline UIAnchor operator|(UIAnchor a, UIAnchor b)
{
	return static_cast<UIAnchor>(static_cast<int>(a) | static_cast<int>(b));
}