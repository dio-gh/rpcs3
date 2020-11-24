#pragma once

#include "overlays.h"

namespace rsx
{
	namespace overlays
	{
		struct quick_settings : user_interface
		{
			label title;
			overlay_element frame;
			animation_translate sliding_animation;
			animation_color_interpolate fade_animation;

			quick_settings();

			void update() override;

			compiled_resource get_compiled() override;
		};

		void toggle_quick_settings();

		void show_quick_settings();

		void hide_quick_settings();
	}
}