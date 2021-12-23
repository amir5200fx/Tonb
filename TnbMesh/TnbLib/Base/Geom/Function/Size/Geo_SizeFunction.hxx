#pragma once
#ifndef _Geo_SizeFunction_Header
#define _Geo_SizeFunction_Header

#include <Global_Done.hxx>
#include <Global_Named.hxx>
#include <Global_Indexed.hxx>
#include <Entity_Box.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<class Point>
	class Geo_SizeFunction
		: public Global_Indexed
		, public Global_Named
		, public Global_Done
	{

		/*Private Data*/

		Entity_Box<Point> theBoundingBox_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
			ar & boost::serialization::base_object<Global_Done>(*this);
			ar & theBoundingBox_;
		}

	protected:


		// default constructor [7/21/2021 Amir]

		Geo_SizeFunction()
		{}


		// constructors [7/21/2021 Amir]

		Geo_SizeFunction(const Entity_Box<Point>& theBox)
			: theBoundingBox_(theBox)
		{}

		Geo_SizeFunction
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Entity_Box<Point>& theBox
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theBoundingBox_(theBox)
		{}

	public:

		typedef Point ptType;
		typedef Entity_Box<Point> boxType;

		static TnbMesh_EXPORT const std::string extension;

		const Entity_Box<Point>& BoundingBox() const
		{
			return theBoundingBox_;
		}

		//- virtual functions and operators

		virtual Standard_Real Value(const Point& theCoord) const = 0;

		virtual void Perform()
		{
			Change_IsDone() = Standard_True;
		}

		//static TnbGeoSizeFun_EXPORT void Save(TNB_oARCH_TYPE& ar, const std::shared_ptr<Geo_SizeFunction<Point>>&);
		//static TnbGeoSizeFun_EXPORT void Load(TNB_iARCH_TYPE& ar, std::shared_ptr<Geo_SizeFunction<Point>>&);

	};
}

#include <Geo2d_SizeFunction.hxx>
#include <Geo3d_SizeFunction.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo2d_SizeFunction);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo3d_SizeFunction);

#endif // !_Geo_SizeFunction_Header