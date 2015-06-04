#pragma once

namespace proZPRd
{
	namespace Tools
	{
		/**
		*	@file
		*	@version 1.0
		*	@class NoCreateU
		*	Klasa NoCreatU to klasa po której dziedziczymy, aby nie pozwolić na stworzenie obiektu danej klasy.
		*	Można tego użyć na przykład do robienia klas z wyłącznie metodami statycznymi
		*/
		class NoCreateU
		{
			public:
				NoCreateU() = delete;
				~NoCreateU() = delete;
		};
	}
}
