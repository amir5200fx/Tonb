#pragma once
#ifndef _HydStatic_FillCurve_Header
#define _HydStatic_FillCurve_Header

#include <HydStatic_HydCurve.hxx>

#include <vector>

namespace tnbLib
{

	class HydStatic_FillCurve
		: public HydStatic_HydCurve
	{

	public:

		struct offSet
		{
			Standard_Real Level;
			Standard_Real Volume;

		private:

			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar & Level;
				ar & Volume;
			}
		};

	private:

		/*Private Data*/


		std::vector<offSet> theQs_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<HydStatic_HydCurve>(*this);
			ar & theQs_;
		}

	public:


		//- default constructor

		HydStatic_FillCurve()
		{}


		//- constructors

		TnbHydStatic_EXPORT HydStatic_FillCurve
		(
			Handle(Geom2d_Curve) && theCurve
		);

		TnbHydStatic_EXPORT HydStatic_FillCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_FillCurve
		(
			const Standard_Integer theIndex, 
			const word& theName,
			Handle(Geom2d_Curve) && theCurve
		);

		TnbHydStatic_EXPORT HydStatic_FillCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);


		//- public functions and operators

		const auto& Qs() const
		{
			return theQs_;
		}

		TnbHydStatic_EXPORT Standard_Boolean 
			IsLevelIntersect
			(
				const Standard_Real theLevel
			) const;

		TnbHydStatic_EXPORT Standard_Boolean 
			IsVolumeIntersect
			(
				const Standard_Real theVolume
			) const;

		TnbHydStatic_EXPORT Standard_Real MinLevel() const;

		TnbHydStatic_EXPORT Standard_Real MaxLevel() const;

		TnbHydStatic_EXPORT Standard_Real MinVolume() const;

		TnbHydStatic_EXPORT Standard_Real MaxVolume() const;

		TnbHydStatic_EXPORT Standard_Real 
			Volume
			(
				const Standard_Real theLevel
			) const;

		TnbHydStatic_EXPORT Standard_Real 
			Level
			(
				const Standard_Real theVolume
			) const;

		void SetQs(const std::vector<offSet>& theQs)
		{
			theQs_ = theQs;
		}

		void SetQs(std::vector<offSet>&& theQs)
		{
			theQs_ = std::move(theQs);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_FillCurve);

#endif // !_HydStatic_FillCurve_Header
