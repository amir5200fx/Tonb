#pragma once
#ifndef _SectPx_KnotVector_Header
#define _SectPx_KnotVector_Header

#include <SectPx_Entity.hxx>

#include <Pnt2d.hxx>

#include <opencascade/TColStd_Array1OfReal.hxx>
#include <opencascade/TColStd_Array1OfInteger.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Coord;

	class SectPx_KnotVector
		: public SectPx_Entity
	{

		/*Private Data*/

		Standard_Real theU0_;
		Standard_Real theU1_;


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_Entity>(*this);
			ar & theU0_;
			ar & theU1_;
		}

		TnbSectPx_EXPORT void SetDefaults();

	protected:

		template<class... _Types>
		SectPx_KnotVector(_Types&&... _Args)
			: SectPx_Entity(_Args...)
		{
			SetDefaults();
		}

		void SetU0(const Standard_Real u)
		{
			theU0_ = u;
		}

		void SetU1(const Standard_Real u)
		{
			theU1_ = u;
		}

		static TnbSectPx_EXPORT std::vector<Standard_Real>
			toKnots
			(
				const std::vector<Standard_Real>& Ubar, 
				const Standard_Integer theDeg
			);

	public:

		typedef TColStd_Array1OfReal knotList;
		typedef TColStd_Array1OfInteger multList;

		auto U0() const
		{
			return theU0_;
		}

		auto U1() const
		{
			return theU1_;
		}

		/*virtual std::vector<Standard_Real>
			CreateKnots
			(
				const std::vector<std::shared_ptr<SectPx_Coord>>& theCoords,
				const Standard_Integer degree
			) const = 0;*/

		virtual std::vector<Standard_Real>
			CreateKnots
			(
				const std::vector<Pnt2d>& theCoords,
				const Standard_Integer degree
			) const = 0;

		static TnbSectPx_EXPORT std::tuple<knotList, multList>
			Convert
			(
				const std::vector<Standard_Real>& seqKnots
			);
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_KnotVector);

#endif // !_SectPx_KnotVector_Header
