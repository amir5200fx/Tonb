#pragma once
#ifndef _HydStatic_DisContinuBonjean_Header
#define _HydStatic_DisContinuBonjean_Header

#include <Standard_Handle.hxx>
#include <Global_Done.hxx>
#include <Pnt2d.hxx>
#include <Geo_Interval.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <HydStatic_Module.hxx>

class Geom2d_Curve;

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Marine_Body;
	class Marine_Domain;
	class HydStatic_BnjCurve;
	class HydStatic_BonjeanGraph;

	class HydStatic_DisContinuBonjean
		: public Global_Done
	{

	public:

		typedef Geo_Interval<Standard_Real> span;

	public:

		class Clip
		{

			/*Private Data*/

			span theSpan_;

			std::shared_ptr<HydStatic_BnjCurve> theCurve_;

		public:

			//- default constructor

			Clip()
			{}

			//- constructors

			TnbHydStatic_EXPORT Clip
			(
				span&& theSpan,
				std::shared_ptr<HydStatic_BnjCurve>&& theCurve
			);

			//- public functions and operators

			const auto& Curve() const
			{
				return theCurve_;
			}

			const auto& Span() const
			{
				return theSpan_;
			}

			TnbHydStatic_EXPORT Pnt2d FirstValue() const;
			TnbHydStatic_EXPORT Pnt2d LastValue() const;

			inline Standard_Real Z0() const;
			inline Standard_Real Z1() const;
			inline Standard_Real Value0() const;
			inline Standard_Real Value1() const;

			TnbHydStatic_EXPORT std::shared_ptr<Clip> Copy() const;
			inline std::shared_ptr<Clip> Scaled(const Standard_Real) const;

			TnbHydStatic_EXPORT void Scale(const Standard_Real);
			inline void SetCurve(std::shared_ptr<HydStatic_BnjCurve> && theCurve);
			inline void SetSpan(const span&);
			inline void SetSpan(span&&);
		};


		class SectionClips
		{

			/*Private Data*/

			std::vector<std::shared_ptr<Clip>> theClips_;

			std::shared_ptr<Marine_CmpSection> theSection_;

		public:

			//- default constructor

			SectionClips()
			{}

			//- constructors

			TnbHydStatic_EXPORT SectionClips
			(
				const std::shared_ptr<Marine_CmpSection>& theSection,
				const std::vector<std::shared_ptr<Clip>>& theClips
			);


			//- public functions and operators

			inline Standard_Integer NbClips() const;

			const auto& Clips() const
			{
				return theClips_;
			}

			const auto& Section() const
			{
				return theSection_;
			}

			inline std::shared_ptr<Clip> First() const;
			inline std::shared_ptr<Clip> Last() const;

			inline Standard_Real MaxValue() const;
			inline Standard_Real Dz() const;

			inline Standard_Real CalcAngle() const;
				
			inline Standard_Real Z0() const;
			inline Standard_Real Z1() const;
			inline Standard_Real Value0() const;
			inline Standard_Real Value1() const;

			TnbHydStatic_EXPORT std::vector<std::shared_ptr<HydStatic_BnjCurve>> 
				RetrieveBonjeanCurves() const;

			TnbHydStatic_EXPORT std::shared_ptr<SectionClips> reCalculate(const Standard_Real) const;
			TnbHydStatic_EXPORT std::shared_ptr<SectionClips> FitToSpan(const span&) const;

			TnbHydStatic_EXPORT void SetSection(const std::shared_ptr<Marine_CmpSection>& theSection);
			TnbHydStatic_EXPORT void SetClips(std::vector<std::shared_ptr<Clip>>&& theClips);

			TnbHydStatic_EXPORT void Add(const std::shared_ptr<Clip>& theClip);

		};


		enum class interplScheme
		{
			Global = 0,
			Local
		};

		struct localInfo
		{

			localInfo()
				: Tolerance(1.0E-6)
				, NeighborType(neighborType::fivePoint)
				, ContinuityType(continuityType::G1)
				, KnotsType(knotsType::chordLen)
			{}

			enum class neighborType
			{
				threePoint = 0,
				fivePoint
			};

			enum class continuityType
			{
				G1 = 0,
				C1
			};

			enum class knotsType
			{
				chordLen = 0,
				centripetal,
				uniform
			};

			neighborType NeighborType;
			continuityType ContinuityType;
			knotsType KnotsType;

			Standard_Real Tolerance;
		};

	private:

		/*Private Data*/

		std::shared_ptr<Marine_Domain> theDomain_;
		std::shared_ptr<Marine_Body> theBody_;

		interplScheme theInterplScheme_;
		localInfo theLocalInterplInfo_;

		Standard_Integer theNbLevels_;

		std::vector<std::shared_ptr<SectionClips>> theSections_;

		//- private functions and operators

		static TnbHydStatic_EXPORT Handle(Geom2d_Curve) MakeSegment(const span&, const Standard_Real x);
		static TnbHydStatic_EXPORT Handle(Geom2d_Curve) MakeClip(const Handle(Geom2d_Curve)&, const span&);
		static TnbHydStatic_EXPORT Handle(Geom2d_Curve) Sum(const Handle(Geom2d_Curve)&, const Handle(Geom2d_Curve)&);
		static TnbHydStatic_EXPORT Handle(Geom2d_Curve) Sum(const Handle(Geom2d_Curve)&, const Standard_Real);
		static TnbHydStatic_EXPORT std::vector<std::shared_ptr<Clip>> Sum(const std::shared_ptr<Clip>&, const std::shared_ptr<Clip>&);

	public:


		static TnbHydStatic_EXPORT std::shared_ptr<Geo_ApprxCurve_Info> curveApproxInfo;
		static TnbHydStatic_EXPORT unsigned short verbose;

		static TnbHydStatic_EXPORT const unsigned int MIN_NB_OF_POINTS;

		//- default constructor

		TnbHydStatic_EXPORT HydStatic_DisContinuBonjean();

		//- constructors

		TnbHydStatic_EXPORT HydStatic_DisContinuBonjean
		(
			const std::shared_ptr<Marine_Domain>& theDomain,
			const std::shared_ptr<Marine_Body>& theBody, 
			const Standard_Integer nbLevs
		);


		//- public functions and operators

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Body() const
		{
			return theBody_;
		}

		auto NbLevels() const
		{
			return theNbLevels_;
		}

		const auto& Sections() const
		{
			return theSections_;
		}

		const auto& LocalInterplInfo() const
		{
			return theLocalInterplInfo_;
		}

		auto& LocalInterplInfoRef()
		{
			return theLocalInterplInfo_;
		}

		TnbHydStatic_EXPORT void Perform();

		inline void LoadDomain(const std::shared_ptr<Marine_Domain>& theDomain);
		inline void LoadBody(const std::shared_ptr<Marine_Body>& theBody);
		inline void SetNbLevels(const Standard_Integer n);
		inline void SetInterplScheme(const interplScheme);

		//- static functions and operators

		static Standard_Real EstimateMaxAngle(const std::shared_ptr<Marine_Body>&);

		static TnbHydStatic_EXPORT std::pair
			<
			std::vector<std::shared_ptr<SectionClips>>,
			Standard_Real
			> 
			reCalculate
			(
				const std::vector<std::shared_ptr<SectionClips>>& theClips, 
				const Standard_Real theMaxDegree
			);

		static TnbHydStatic_EXPORT std::vector<std::shared_ptr<SectionClips>>
			Sync
			(
				const std::vector<std::shared_ptr<SectionClips>>&, 
				const Standard_Real z0, 
				const Standard_Real z1
			);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_BonjeanGraph> 
			RetrieveGraph
			(
				const std::vector<std::shared_ptr<SectionClips>>&
			);
	};
}

#include <HydStatic_DisContinuBonjeanI.hxx>

#endif // !_HydStatic_DisContinuBonjean_Header
