#pragma once
#ifndef _SectPx_DimensionFrame_Header
#define _SectPx_DimensionFrame_Header

#include <SectPx_ParsFwd.hxx>
#include <SectPx_PntsFwd.hxx>
#include <SectPx_MakersFwd.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Registry;


	namespace frame
	{

		class Dimension
		{

		public:

			struct EntityMaker
			{

				EntityMaker(const std::shared_ptr<SectPx_Registry>&);

				std::shared_ptr<maker::Point> Pnt;
				std::shared_ptr<maker::GeometricMap> GeoMap;
				std::shared_ptr<maker::CmptProfile> CmptProfile;
			};

		private:

			/*Private Data*/

			std::shared_ptr<EntityMaker> theMakers_;

		protected:

			Dimension(const std::shared_ptr<SectPx_Registry>& theReg);

		public:

			const auto& DimensionMakers() const
			{
				return theMakers_;
			}

			const auto& PointMaker() const
			{
				return DimensionMakers()->Pnt;
			}

			const auto& GeometricMapMaker() const
			{
				return DimensionMakers()->GeoMap;
			}

			const auto& CmptProfileMaker() const
			{
				return DimensionMakers()->CmptProfile;
			}
		};
	}
}

#endif // !_SectPx_DimensionFrame_Header
