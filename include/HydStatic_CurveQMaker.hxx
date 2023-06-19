#pragma once
#ifndef _HydStatic_CurveQMaker_Header
#define _HydStatic_CurveQMaker_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <word.hxx>
#include <HydStatic_CurveMakerType.hxx>
#include <HydStatic_Module.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	namespace hydStcLib
	{

		template<class CurveType>
		class CurveQMaker_SymmHeel
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

			

		public:

			//- default constructor

			CurveQMaker_SymmHeel()
			{}

			//- constructors

			CurveQMaker_SymmHeel
			(
				const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
			)
				: CurveType(theQs)
			{}

			CurveQMaker_SymmHeel
			(
				std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
			)
				: CurveType(std::move(theQs))
			{}


			CurveQMaker_SymmHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
			)
				: CurveType(theIndex, theName, theQs)
			{}

			CurveQMaker_SymmHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
			)
				: CurveType(theIndex, theName, std::move(theQs))
			{}


			//- public functions and operators


		};

		template<class CurveType>
		bool IsSymmHeelQ(const std::shared_ptr<CurveType>& theCurve)
		{
			return (bool)std::dynamic_pointer_cast<CurveQMaker_SymmHeel<CurveType>>(theCurve);
		}

		template<class CurveType>
		class CurveQMaker_AsymmHeel
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


		public:

			CurveQMaker_AsymmHeel()
			{}

			//- constructors

			CurveQMaker_AsymmHeel
			(
				const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
			)
				: CurveType(theQs)
			{}

			CurveQMaker_AsymmHeel
			(
				std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
			)
				: CurveType(std::move(theQs))
			{}


			CurveQMaker_AsymmHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
			)
				: CurveType(theIndex, theName, theQs)
			{}

			CurveQMaker_AsymmHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
			)
				: CurveType(theIndex, theName, std::move(theQs))
			{}


			//- public functions and operators
		};


		template<class CurveType>
		bool IsAsymmHeelQ(const std::shared_ptr<CurveType>& theCurve)
		{
			return (bool)std::dynamic_pointer_cast<CurveQMaker_AsymmHeel<CurveType>>(theCurve);
		}


		template<class CurveType>
		class CurveQMaker_StbHeel
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

		public:

			//- default constructor

			CurveQMaker_StbHeel()
			{}

			//- constructors

			CurveQMaker_StbHeel
			(
				const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
			)
				: CurveType(theQs)
			{}

			CurveQMaker_StbHeel
			(
				std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
			)
				: CurveType(std::move(theQs))
			{}


			CurveQMaker_StbHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
			)
				: CurveType(theIndex, theName, theQs)
			{}

			CurveQMaker_StbHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
			)
				: CurveType(theIndex, theName, std::move(theQs))
			{}


			//- public functions and operators
		};


		template<class CurveType>
		bool IsStbHeelQ(const std::shared_ptr<CurveType>& theCurve)
		{
			return (bool)std::dynamic_pointer_cast<CurveQMaker_StbHeel<CurveType>>(theCurve);
		}

		template<class CurveType>
		class CurveQMaker_ArbtHeel
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

		public:

			//- default constructor

			CurveQMaker_ArbtHeel()
			{}

			//- constructors

			CurveQMaker_ArbtHeel
			(
				const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
			)
				: CurveType(theQs)
			{}

			CurveQMaker_ArbtHeel
			(
				std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
			)
				: CurveType(std::move(theQs))
			{}


			CurveQMaker_ArbtHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
			)
				: CurveType(theIndex, theName, theQs)
			{}

			CurveQMaker_ArbtHeel
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
			)
				: CurveType(theIndex, theName, std::move(theQs))
			{}

			//- public functions and operators

		};

		template<class CurveType>
		bool IsArbtHeelQ(const std::shared_ptr<CurveType>& theCurve)
		{
			return (bool)std::dynamic_pointer_cast<CurveQMaker_ArbtHeel<CurveType>>(theCurve);
		}

		template<class CurveType>
		CurveMakerType RetrieveTypeQ(const std::shared_ptr<CurveType>& theCurve)
		{
			if (IsArbtHeelQ(theCurve))
			{
				return CurveMakerType::arbitrary;
			}
			else if (IsAsymmHeelQ(theCurve))
			{
				return CurveMakerType::asymmetric;
			}
			else if (IsStbHeelQ(theCurve))
			{
				return CurveMakerType::starboard;
			}
			else if (IsSymmHeelQ(theCurve))
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
		std::shared_ptr<CurveType> MakeCurveQ(std::vector<std::pair<Standard_Real, Standard_Real>>&& theGeom, const CurveMakerType t)
		{
			switch (t)
			{
			case hydStcLib::CurveMakerType::arbitrary:
			{
				auto curve = std::make_shared<hydStcLib::CurveQMaker_ArbtHeel<CurveType>>(0, "curve", std::move(theGeom));
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::asymmetric:
			{
				auto curve = std::make_shared<hydStcLib::CurveQMaker_AsymmHeel<CurveType>>(0, "curve", std::move(theGeom));
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::starboard:
			{
				auto curve = std::make_shared<hydStcLib::CurveQMaker_StbHeel<CurveType>>(0, "curve", std::move(theGeom));
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::symmetric:
			{
				auto curve = std::make_shared<hydStcLib::CurveQMaker_SymmHeel<CurveType>>(0, "curve", std::move(theGeom));
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
		std::shared_ptr<CurveType> MakeCurveQ(const std::vector<std::pair<Standard_Real, Standard_Real>>& theGeom, const CurveMakerType t)
		{
			switch (t)
			{
			case hydStcLib::CurveMakerType::arbitrary:
			{
				auto curve = std::make_shared<hydStcLib::CurveQMaker_ArbtHeel<CurveType>>(0, "curve", theGeom);
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::asymmetric:
			{
				auto curve = std::make_shared<hydStcLib::CurveQMaker_AsymmHeel<CurveType>>(0, "curve", theGeom);
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::starboard:
			{
				auto curve = std::make_shared<hydStcLib::CurveQMaker_StbHeel<CurveType>>(0, "curve", theGeom);
				return std::move(curve);
			}
			case hydStcLib::CurveMakerType::symmetric:
			{
				auto curve = std::make_shared<hydStcLib::CurveQMaker_SymmHeel<CurveType>>(0, "curve", theGeom);
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
		CurveMakerType RetrieveTypeQ
		(
			const std::vector<std::shared_ptr<CurveType>>& theCurves
		)
		{
			if (theCurves.size() < 2)
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid cross-curves has been detected" << endl
					<< abort(FatalError);
			}
			const auto t = hydStcLib::RetrieveTypeQ(theCurves[0]);
			for (const auto& x : theCurves)
			{
				if (hydStcLib::RetrieveTypeQ(x) NOT_EQUAL t)
				{
					FatalErrorIn(FunctionSIG)
						<< "all of the cross-curves must be the same type" << endl
						<< abort(FatalError);
				}
			}
			return t;
		}
	}
}

#endif // !_HydStatic_CurveQMaker_Header
