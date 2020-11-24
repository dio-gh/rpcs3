#include "stdafx.h"
#include "overlay_quick_settings.h"
#include "Emu/system_config.h"
#include "Emu/RSX/RSXThread.h"

namespace rsx
{
	namespace overlays
	{
		quick_settings::quick_settings()
		{
			title.set_font("Arial", 16);
			title.set_text("Quick Settings");
			title.auto_resize();
			title.set_pos(1055 + 12, 435 + 12);
			title.back_color.a = 0.f;


			// frame size: 720/4 wide, 720/3 tall
			frame.back_color.r = .16f;
			frame.back_color.g = .16f;
			frame.back_color.b = .16f;
			frame.back_color.a = 0.8f;
			frame.set_pos(1055, 435);
			frame.set_size(180, 240);

			sliding_animation.duration = .25;
			sliding_animation.type     = animation_type::ease_in_out_cubic;
			sliding_animation.current  = {(f32)24, 0, 0};
			sliding_animation.end      = {0, 0, 0};
			sliding_animation.active   = true;

			fade_animation.current  = color4f(0.f);
			fade_animation.end      = color4f(1.f);
			fade_animation.duration = .25;
			fade_animation.type     = animation_type::ease_in_out_cubic;
			fade_animation.active   = true;

			visible = true;
		}

		void quick_settings::update()
		{
			if (sliding_animation.active)
			{
				sliding_animation.update(rsx::get_current_renderer()->vblank_count);
			}

			if (fade_animation.active)
			{
				fade_animation.update(rsx::get_current_renderer()->vblank_count);
			}
		}

		compiled_resource quick_settings::get_compiled()
		{
			if (!visible) return {};

			auto compiled = frame.get_compiled();
			compiled.add(title.get_compiled());

			fade_animation.apply(compiled);
			sliding_animation.apply(compiled);

			return compiled;
		}

		void show_quick_settings()
		{
			if (!g_cfg.misc.use_native_interface)
				return;

			if (auto manager = g_fxo->get<rsx::overlays::display_manager>())
			{
				auto widget = manager->get<rsx::overlays::quick_settings>();

				const bool existed = !!widget;

				if (!existed) widget = manager->create<rsx::overlays::quick_settings>();
			}
		}

		void hide_quick_settings()
		{
			if (!g_cfg.misc.use_native_interface)
				return;

			if (auto manager = g_fxo->get<rsx::overlays::display_manager>())
			{
				auto widget = manager->get<rsx::overlays::quick_settings>();

				const bool existed = !!widget;

				if (existed) manager->remove<rsx::overlays::quick_settings>();
			}
		}

		void toggle_quick_settings()
		{
			if (!g_cfg.misc.use_native_interface)
				return;

			if (auto manager = g_fxo->get<rsx::overlays::display_manager>())
			{
				auto widget = manager->get<rsx::overlays::quick_settings>();

				const bool existed = !!widget;

				if (!existed) show_quick_settings();
				else hide_quick_settings();
			}
		}
	}
}