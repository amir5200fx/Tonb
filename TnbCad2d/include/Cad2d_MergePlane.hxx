#pragma once
#ifndef _Cad2d_MergePlane_Header
#define _Cad2d_MergePlane_Header

#include <Global_Done.hxx>
#include <Cad2d_Module.hxx>
#include <Entity2d_ChainFwd.hxx>

#include <memory>

namespace tnbLib
{

	//- Forward Declarations
	class Cad2d_Plane;

	class Cad2d_MergePlane
		: public Global_Done
	{

	public:

		struct mergeInfo
		{
			Standard_Real resolution;
			Standard_Real radius;

			TnbCad2d_EXPORT mergeInfo();
		};

	private:

		/*Private Data*/

		mergeInfo theInfo_;

		std::shared_ptr<Cad2d_Plane> thePlane_;

		std::shared_ptr<Entity2d_Chain> theMerged_;

	public:

		//- default constructor

		Cad2d_MergePlane()
		{}


		//- public functions and operators

		const auto& Plane() const
		{
			return thePlane_;
		}

		const auto& Merged() const
		{
			return theMerged_;
		}

		const auto& Info() const
		{
			return theInfo_;
		}

		auto& Info()
		{
			return theInfo_;
		}

		TnbCad2d_EXPORT void Perform();

		void LoadPlane(const std::shared_ptr<Cad2d_Plane>& thePlane)
		{
			thePlane_ = thePlane;
		}

	};
}

#endif // !_Cad2d_MergePlane_Header
