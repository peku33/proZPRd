#pragma once

/**
	Klasa NoCopyU to klasa po której dziedziczymy, aby nie pozwolić na kopiowanie obiektów danej klasy.
	Może być przydatna wtedy, kiedy klasa zawiera wskaźniki, deskryptory plików itp, których skopiowanie
	mogłoby mieć negatywne skutki
*/

namespace proZPRd
{
	namespace Tools
	{
		class NoCopyU
		{
			public:
				//NoCopyU() {};
				NoCopyU(const NoCopyU & CopyFrom) = delete;
				NoCopyU & operator = (const NoCopyU &) = delete;
		};
	}
}
