#pragma once
#ifndef _HydStatic_Model_Moment_Header
#define _HydStatic_Model_Moment_Header

#include <HydStatic_Model_Entity.hxx>
#include <Marine_VesselParam_MH.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class Model_Moment
		{

			/*Private Data*/

			marineLib::MH theMoment_;

		public:

			Model_Moment();

			Model_Moment(const Standard_Integer theIndex, const word& theName);


			const auto& Value() const
			{
				return theMoment_;
			}

			void SetValue(const Standard_Real theValue)
			{
				theMoment_() = theValue;
			}
		};
	}
}

#endif // !_HydStatic_Model_Moment_Header
