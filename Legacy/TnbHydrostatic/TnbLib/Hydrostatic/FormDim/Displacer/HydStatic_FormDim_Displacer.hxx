#pragma once
#ifndef _HydStatic_FormDim_Displacer_Header
#define _HydStatic_FormDim_Displacer_Header

#include <Marine_VesselParams.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Global_Done.hxx>
#include <Global_Serialization.hxx>
#include <HydStatic_Module.hxx>

#include <memory>

namespace tnbLib
{

	namespace formDim
	{

		class Displacer
			: public Global_Done
		{

		public:

			struct Parameter
			{
				Parameter();

				//- Breadth
				marineLib::B B;

				//- Depth
				marineLib::D D;

				//- Length overall
				marineLib::LOA Loa;

				TNB_SERIALIZATION(TnbHydStatic_EXPORT);
			};


		private:

			/*Private Data*/

			std::shared_ptr<marineLib::Body_Displacer> theBody_;

			std::shared_ptr<Parameter> theParameters_;


			//- private functions


			TNB_SERIALIZATION(TnbHydStatic_EXPORT);

			auto& ChangeParameters()
			{
				return theParameters_;
			}

			TnbHydStatic_EXPORT void AllocateMemory();

			TnbHydStatic_EXPORT void CalcDims();

		public:

			Displacer()
			{}

			TnbHydStatic_EXPORT Displacer
			(
				const std::shared_ptr<marineLib::Body_Displacer>& theBody
			);


			const auto& Body() const
			{
				return theBody_;
			}

			const auto& Parameters() const
			{
				return theParameters_;
			}

			TnbHydStatic_EXPORT void Perform();

			TnbHydStatic_EXPORT void LoadBody
			(
				const std::shared_ptr<marineLib::Body_Displacer>& theBody
			);
		};
	}
}

#endif // !_HydStatic_FormDim_Displacer_Header
