#pragma once
/* Log: console logging utilities for Anim2 */
namespace Anim {
	class Log
	{

	public:
		static void Info(const char* msg);
		static void Warn(const char* msg);
		static void Error(const char* msg);
		static void Crit(const char* msg);
	};
}