#include "FontData.h"

#include <allegro5/allegro_ttf.h>

FontData::FontData()
{
	fonts_ = {
		{ 8, al_load_ttf_font("font/chary___.ttf", 8, 0) },
		{ 16, al_load_ttf_font("font/chary___.ttf", 16, 0) },
		{ 32, al_load_ttf_font("font/chary___.ttf", 32, 0) },
		{ 64, al_load_ttf_font("font/chary___.ttf", 64, 0) },
		{ 128, al_load_ttf_font("font/chary___.ttf", 128, 0) }
	};
}

FontData::~FontData()
{
	for (auto it = fonts_.begin(); it != fonts_.end(); it++)
	{
		al_destroy_font(it->second);
		it->second = nullptr;
	}
}

FontData &FontData::instance()
{
	static FontData fontData;

	return fontData;
}

void FontData::renderText(
	float x, float y,
	const char *text,
	unsigned int size,
	const ALLEGRO_COLOR &color,
	int allegroFlags,
	uint8_t textFlags) const
{
	if (textFlags & TextFlags::CenterVertically)
		y -= al_get_font_line_height(fonts_.at(size)) * 0.5f;

	al_draw_text(fonts_.at(size), color, x, y, allegroFlags, text);
}

void FontData::renderText(
	float x, float y,
	const std::string &text,
	unsigned int size,
	const ALLEGRO_COLOR &color,
	int allegroFlags,
	uint8_t textFlags) const
{
	this->renderText(x, y, text.c_str(), size, color, allegroFlags, textFlags);
}

ALLEGRO_FONT *FontData::get(unsigned int size)
{
	return fonts_.at(size);
}