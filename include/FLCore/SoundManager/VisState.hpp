#pragma once

/* ---------- constants */

enum class vis_state
{
	VS_UNKNOWN,
	VS_NOT_VISIBLE,
	VS_SUB_PIXEL,			// smaller than one pixel
	VS_PARTIALLY_VISIBLE,
	VS_FULLY_VISIBLE,
	VS_END = 0x7FFFFFFF
}; // the order here is important (inceasing from invisible to fully visible) -ms