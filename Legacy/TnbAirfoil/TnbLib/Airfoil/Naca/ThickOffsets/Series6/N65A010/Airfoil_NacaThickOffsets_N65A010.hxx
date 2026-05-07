#pragma once
#ifndef _Airfoil_NacaThickOffsets_N65A010_Header
#define _Airfoil_NacaThickOffsets_N65A010_Header

#include <Airfoil_NacaThickOffsets_Series6.hxx>

namespace tnbLib
{

	class Airfoil_NacaThickOffsets_N65A010
		: public Airfoil_NacaThickOffsets_Series6
	{

	public:

		static std::vector<Standard_Real> XOC;
		static std::vector<Standard_Real> TOC;

		class RuntimeSettings
		{

			/*Private Data*/

		public:

			// default constructor [11/5/2022 Amir]

			RuntimeSettings()
			{
				Init();
			}

			static TnbAirfoil_EXPORT void Init();
		};

	private:

		/*Private Data*/

		

	public:

		

		// default constructor [11/5/2022 Amir]

		Airfoil_NacaThickOffsets_N65A010()
		{}

		// constructors [11/5/2022 Amir]


		// public functions and operators [11/5/2022 Amir]

		TnbAirfoil_EXPORT std::vector<std::pair<Standard_Real, Standard_Real>> 
			Values(const Standard_Real theMaxThick) const override;

	};
}

#endif // !_Airfoil_NacaThickOffsets_N65A010_Header
