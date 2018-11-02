#pragma once

struct pluginInfo
{
	wchar_t *processName;
	wchar_t *bindTitle;
	wchar_t *version;
	wchar_t *manufacturer;
	wchar_t *url;
	bool supportConfigWindow;
};

struct pluginData
{
	float surge;
	float sway;
	float pitch;
	float roll;
	float speed;
	bool isPaused;
};
