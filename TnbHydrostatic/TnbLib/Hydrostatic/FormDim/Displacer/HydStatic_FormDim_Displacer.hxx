#pragma once
#ifndef _HydStatic_FormDim_Displacer_Header
#define _HydStatic_FormDim_Displacer_Header

#include <Marine_VesselParams.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Global_Done.hxx>

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
			};


		private:

			/*Private Data*/

			std::shared_ptr<marineLib::Body_Displacer> theBody_;

			std::shared_ptr<Parameter> theParameters_;


			//- private functions

			auto& ChangeParameters()
			{
				return theParameters_;
			}

			void AllocateMemory();

			void CalcDims();

		public:

			Displacer()
			{}

			Displacer
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

			void Perform();

			void LoadBody
			(
				const std::shared_ptr<marineLib::Body_Displacer>& theBody
			);
		};
	}
}

#endif // !_HydStatic_FormDim_Displacer_Header
