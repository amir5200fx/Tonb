#pragma once
#ifndef _Cad_LineSingularZone_Dangle_Header
#define _Cad_LineSingularZone_Dangle_Header

#include <Cad_LineSingularZone.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		struct LineSingularZone_DangleBase
		{
			static TnbMesh_EXPORT const word typeName;
		};

		template<class SurfPln>
		class LineSingularZone_Dangle
			: public Cad_LineSingularZone<SurfPln>
			, public LineSingularZone_DangleBase
		{

		public:

			typedef typename cad_singular_zone_traits<SurfPln>::curveType curveType;
			typedef Cad_LineSingularZone<SurfPln> base;

		private:

			/*Private Data*/

			std::shared_ptr<curveType> theHorizon0_;
			std::shared_ptr<curveType> theHorizon1_;
			std::shared_ptr<curveType> theHorizon2_;

		public:

			// default constructor [12/31/2021 Amir]

			LineSingularZone_Dangle()
			{}


			// constructors [12/31/2021 Amir]

			explicit LineSingularZone_Dangle(const Standard_Integer theIndex)
				: base(theIndex)
			{}

			LineSingularZone_Dangle(const Standard_Integer theIndex, const std::shared_ptr<SurfPln>& thePlane)
				: base(theIndex, thePlane)
			{}

			LineSingularZone_Dangle(const Standard_Integer theIndex, std::shared_ptr<SurfPln>&& thePlane)
				: base(theIndex, std::move(thePlane))
			{}

			explicit LineSingularZone_Dangle(std::shared_ptr<SurfPln>&& thePlane)
				: base(std::move(thePlane))
			{}

			explicit LineSingularZone_Dangle(const std::shared_ptr<SurfPln>& thePlane)
				: base(thePlane)
			{}

			LineSingularZone_Dangle
			(
				const std::shared_ptr<curveType>& theHorizon0,
				const std::shared_ptr<curveType>& theHorizon1,
				const std::shared_ptr<curveType>& theHorizon2
			)
				: theHorizon0_(theHorizon0)
				, theHorizon1_(theHorizon1)
				, theHorizon2_(theHorizon2)
			{}

			LineSingularZone_Dangle
			(
				std::shared_ptr<curveType>&& theHorizon0,
				std::shared_ptr<curveType>&& theHorizon1,
				std::shared_ptr<curveType>&& theHorizon2
			)
				: theHorizon0_(std::move(theHorizon0))
				, theHorizon1_(std::move(theHorizon1))
				, theHorizon2_(std::move(theHorizon2))
			{}

			LineSingularZone_Dangle
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<SurfPln>& thePlane,
				const std::shared_ptr<curveType>& theHorizon0,
				const std::shared_ptr<curveType>& theHorizon1,
				const std::shared_ptr<curveType>& theHorizon2
			)
				: base(theIndex, thePlane)
				, theHorizon0_(theHorizon0)
				, theHorizon1_(theHorizon1)
				, theHorizon2_(theHorizon2)
			{}

			LineSingularZone_Dangle
			(
				const Standard_Integer theIndex,
				std::shared_ptr<SurfPln>&& thePlane,
				std::shared_ptr<curveType>&& theHorizon0,
				std::shared_ptr<curveType>&& theHorizon1,
				std::shared_ptr<curveType>&& theHorizon2
			)
				: base(theIndex, std::move(thePlane))
				, theHorizon0_(std::move(theHorizon0))
				, theHorizon1_(std::move(theHorizon1))
				, theHorizon2_(std::move(theHorizon2))
			{}

			// public functions and operators [12/31/2021 Amir]

			const auto& Horizon0() const
			{
				return theHorizon0_;
			}

			const auto& Horizon1() const
			{
				return theHorizon1_;
			}

			const auto& Horizon2() const
			{
				return theHorizon2_;
			}

			void SetHorizon0(const std::shared_ptr<curveType>& theCurve)
			{
				theHorizon0_ = theCurve;
			}

			void SetHorizon0(std::shared_ptr<curveType>&& theCurve)
			{
				theHorizon0_ = std::move(theCurve);
			}

			void SetHorizon1(const std::shared_ptr<curveType>& theCurve)
			{
				theHorizon1_ = theCurve;
			}

			void SetHorizon1(std::shared_ptr<curveType>&& theCurve)
			{
				theHorizon1_ = std::move(theCurve);
			}

			void SetHorizon2(const std::shared_ptr<curveType>& theCurve)
			{
				theHorizon2_ = theCurve;
			}

			void SetHorizon2(std::shared_ptr<curveType>&& theCurve)
			{
				theHorizon2_ = std::move(theCurve);
			}

			// override functions and operators [12/31/2021 Amir]

			Cad_SingularType ZoneType() const override;

			Standard_Integer NbHorizons() const override;
			std::shared_ptr<curveType> Horizon(const Standard_Integer theIndex) const override;
		};
	}
}

#include <Cad_LineSingularZone_DangleI.hxx>

#endif // !_Cad_LineSingularZone_Dangle_Header
