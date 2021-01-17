#pragma once
#ifndef _HydStatic_CurveMaker_Header
#define _HydStatic_CurveMaker_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <word.hxx>
#include <HydStatic_CurveMakerType.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>

class Geom2d_Curve;

namespace tnbLib
{

	namespace hydStcLib
	{

		template<class CurveType>
		class CurveMaker_SymmHeel
			: public CurveType
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<CurveType>(*this);
			}

			CurveMaker_SymmHeel()
			{}

		public:

			CurveMaker_SymmHeel
			(
				const Handle(Geom2d_Curve)& theGeom
			)
				: CurveType(theGeom)
			{}

			CurveMaker_SymmHeel
			(
				Handle(Geom2d_Curve)&& theGeom
			)
				: CurveType(std::move(theGeom))
			{}

			CurveMaker_SymmHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Handle(Geom2d_Curve)& theGeom
			)
				: CurveType(theGeom)
			{}

			CurveMaker_SymmHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				Handle(Geom2d_Curve) && theGeom
			)
				: CurveType(std::move(theGeom))
			{}
		};


		template<class CurveType>
		bool IsSymmHeel(const std::shared_ptr<CurveType>& theCurve)
		{
			return (bool)std::dynamic_pointer_cast<CurveMaker_SymmHeel<CurveType>>(theCurve);
		}


		template<class CurveType>
		class CurveMaker_AsymmHeel
			: public CurveType
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<CurveType>(*this);
			}


			CurveMaker_AsymmHeel()
			{}

		public:

			CurveMaker_AsymmHeel
			(
				const Handle(Geom2d_Curve)& theGeom
			)
				: CurveType(theGeom)
			{}

			CurveMaker_AsymmHeel
			(
				Handle(Geom2d_Curve) && theGeom
			)
				: CurveType(std::move(theGeom))
			{}

			CurveMaker_AsymmHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Handle(Geom2d_Curve)& theGeom
			)
				: CurveType(theGeom)
			{}

			CurveMaker_AsymmHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				Handle(Geom2d_Curve) && theGeom
			)
				: CurveType(std::move(theGeom))
			{}
		};


		template<class CurveType>
		bool IsAsymmHeel(const std::shared_ptr<CurveType>& theCurve)
		{
			return (bool)std::dynamic_pointer_cast<CurveMaker_AsymmHeel<CurveType>>(theCurve);
		}

		template<class CurveType>
		class CurveMaker_StbHeel
			: public CurveType
		{

			/*Private Data*/



			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<CurveType>(*this);
			}


			CurveMaker_StbHeel()
			{}

		public:

			CurveMaker_StbHeel
			(
				const Handle(Geom2d_Curve)& theGeom
			)
				: CurveType(theGeom)
			{}

			CurveMaker_StbHeel
			(
				Handle(Geom2d_Curve) && theGeom
			)
				: CurveType(std::move(theGeom))
			{}

			CurveMaker_StbHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Handle(Geom2d_Curve)& theGeom
			)
				: CurveType(theGeom)
			{}

			CurveMaker_StbHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				Handle(Geom2d_Curve) && theGeom
			)
				: CurveType(std::move(theGeom))
			{}
		};


		template<class CurveType>
		bool IsStbHeel(const std::shared_ptr<CurveType>& theCurve)
		{
			return (bool)std::dynamic_pointer_cast<CurveMaker_StbHeel<CurveType>>(theCurve);
		}


		template<class CurveType>
		class CurveMaker_ArbtHeel
			: public CurveType
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<CurveType>(*this);
			}


			CurveMaker_ArbtHeel()
			{}

		public:

			CurveMaker_ArbtHeel
			(
				const Handle(Geom2d_Curve)& theGeom
			)
				: CurveType(theGeom)
			{}

			CurveMaker_ArbtHeel
			(
				Handle(Geom2d_Curve) && theGeom
			)
				: CurveType(std::move(theGeom))
			{}

			CurveMaker_ArbtHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Handle(Geom2d_Curve)& theGeom
			)
				: CurveType(theGeom)
			{}

			CurveMaker_ArbtHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				Handle(Geom2d_Curve) && theGeom
			)
				: CurveType(std::move(theGeom))
			{}
		};


		template<class CurveType>
		bool IsArbtHeel(const std::shared_ptr<CurveType>& theCurve)
		{
			return (bool)std::dynamic_pointer_cast<CurveMaker_ArbtHeel<CurveType>>(theCurve);
		}

		template<class CurveType>
		CurveMakerType RetrieveType(const std::shared_ptr<CurveType>& theCurve)
		{
			if (IsArbtHeel(theCurve))
			{
				return CurveMakerType::arbitrary;
			}
			else if (IsAsymmHeel(theCurve))
			{
				return CurveMakerType::asymmetric;
			}
			else if (IsStbHeel(theCurve))
			{
				return CurveMakerType::starboard;
			}
			else if (IsSymmHeel(theCurve))
			{
				return CurveMakerType::symmetric;
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "undefined curve type" << endl
					<< abort(FatalError);
				return CurveMakerType::symmetric;
			}
		}


		template<class CurveType>
		std::shared_ptr<CurveType> MakeCurve(Handle(Geom2d_Curve)&& theGeom, const CurveMakerType t)
		{
			switch (t)
			{
			case hydStcLib::CurveMakerType::arbitrary:
			{
				auto curve = std::make_shared<hydStcLib::CurveMaker_ArbtHeel<CurveType>>(0, "curve", std::move(theGeom));
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::asymmetric:
			{
				auto curve = std::make_shared<hydStcLib::CurveMaker_AsymmHeel<CurveType>>(0, "curve", std::move(theGeom));
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::starboard:
			{
				auto curve = std::make_shared<hydStcLib::CurveMaker_StbHeel<CurveType>>(0, "curve", std::move(theGeom));
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::symmetric:
			{
				auto curve = std::make_shared<hydStcLib::CurveMaker_SymmHeel<CurveType>>(0, "curve", std::move(theGeom));
				return std::move(curve);
			}
			default:
				FatalErrorIn(FunctionSIG)
					<< "undefined curve type has been encountered!" << endl
					<< abort(FatalError);
				break;
			}
			return nullptr;
		}

		template<class CurveType>
		std::shared_ptr<CurveType> MakeCurve(const Handle(Geom2d_Curve) & theGeom, const CurveMakerType t)
		{
			switch (t)
			{
			case hydStcLib::CurveMakerType::arbitrary:
			{
				auto curve = std::make_shared<hydStcLib::CurveMaker_ArbtHeel<CurveType>>(0, "curve", theGeom);
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::asymmetric:
			{
				auto curve = std::make_shared<hydStcLib::CurveMaker_AsymmHeel<CurveType>>(0, "curve", theGeom);
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::starboard:
			{
				auto curve = std::make_shared<hydStcLib::CurveMaker_StbHeel<CurveType>>(0, "curve", theGeom);
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::symmetric:
			{
				auto curve = std::make_shared<hydStcLib::CurveMaker_SymmHeel<CurveType>>(0, "curve", theGeom);
				return std::move(curve);
			}
			default:
				FatalErrorIn(FunctionSIG)
					<< "undefined curve type has been encountered!" << endl
					<< abort(FatalError);
				break;
			}
			return nullptr;
		}
	}
}

#endif // !_HydStatic_CurveMaker_Header
