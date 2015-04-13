#pragma once

namespace proZPRd
{
	namespace Tools
	{
		/**
			Klasa NoCopyU to klasa po której dziedziczymy, aby nie pozwolić na kopiowanie obiektów danej klasy.
			Może być przydatna wtedy, kiedy klasa zawiera wskaźniki, deskryptory plików itp, których skopiowanie
			mogłoby mieć negatywne skutki
		*/
		class NoCopyU
		{
			public:
				NoCopyU(const NoCopyU &) = delete;
				NoCopyU & operator = (const NoCopyU &) = delete;
		};
	}
}
