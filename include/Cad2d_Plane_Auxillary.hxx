#pragma once
#ifndef _Cad2d_Plane_Auxillary_Header
#define _Cad2d_Plane_Auxillary_Header

#include <Entity2d_BoxFwd.hxx>
#include <Global_Serialization.hxx>
#include <Cad2d_Module.hxx>

#include <opencascade/gp_Ax2.hxx>

#include <memory>

namespace tnbLib
{

	namespace cad2dLib
	{

		class Plane_Auxillary
		{

			/*Private Data*/

			std::shared_ptr<Entity2d_Box> theBoundingBox_;

			gp_Ax2 theSystem_;


			/*private functions and operators*/

			auto& ChangeBoundingBox()
			{
				return theBoundingBox_;
			}

			auto& ChangeSystem()
			{
				return theSystem_;
			}

			TNB_SERIALIZATION(TnbCad2d_EXPORT);

		protected:

			TnbCad2d_EXPORT Plane_Auxillary(const gp_Ax2& theSystem);

			TnbCad2d_EXPORT Plane_Auxillary(const gp_Ax2&& theSystem);


			TnbCad2d_EXPORT void SetBoundingBox(const std::shared_ptr<Entity2d_Box>&& theB);

		public:

			const auto& BoundingBox() const
			{
				return theBoundingBox_;
			}

			const auto& System() const
			{
				return theSystem_;
			}


		};
	}
}

#endif // !_Cad2d_Plane_Auxillary_Header
