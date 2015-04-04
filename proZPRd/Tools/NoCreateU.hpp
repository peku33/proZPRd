#pragma once

/**
	Klasa NoCreatU to klasa po której dziedziczymy, aby nie pozwolić na stworzenie obiektu danej klasy.
	Można tego użyć na przykład do robienia klas z wyłącznie metodami statycznymi
*/

namespace proZPRd
{
	namespace Tools
	{
		class NoCreateU
		{
			public:
				NoCreateU() = delete;
				~NoCreateU() = delete;
		};
	}
}
