#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>

namespace Structure
{
	class Rand
	{
	public:
		static int cnt;
		static void checkSeed(void);
		static void newSeed(int s);
		static int randi(void);
		static int randi(int max);
	};
}


