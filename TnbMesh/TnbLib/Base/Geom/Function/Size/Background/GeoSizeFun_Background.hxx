#pragma once
#ifndef _GeoSizeFun_Background_Header
#define _GeoSizeFun_Background_Header

#include <GeoSizeFun_nonUniform.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>

namespace tnbLib
{

	template<class BackMeshData>
	class GeoSizeFun_Background
		: public GeoSizeFun_nonUniform<typename BackMeshData::Point>
	{

		typedef typename BackMeshData::Point Point;

		/*Private Data*/

		std::shared_ptr<BackMeshData> theBackMesh_;


		//- private functions and operators

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			Info << "this function is not supposed to be called" << endl;
			NotImplemented;
		}

	protected:

		//- default constructor for serialization purposes only!

		GeoSizeFun_Background()
		{}

	public:

		typedef Point ptType;


		//- constructors

		GeoSizeFun_Background
		(
			const Entity_Box<Point>& theBox,
			const std::shared_ptr<BackMeshData>& theBackMesh
		)
			: GeoSizeFun_nonUniform<typename BackMeshData::Point>(theBox)
			, theBackMesh_(theBackMesh)
		{}

		GeoSizeFun_Background
		(
			Entity_Box<Point>&& theBox,
			std::shared_ptr<BackMeshData>&& theBackMesh
		)
			: GeoSizeFun_nonUniform<typename BackMeshData::Point>(std::move(theBox))
			, theBackMesh_(std::move(theBackMesh))
		{}

		GeoSizeFun_Background
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Entity_Box<Point>& theBox,
			const std::shared_ptr<BackMeshData>& theBackMesh
		)
			: GeoSizeFun_nonUniform<typename BackMeshData::Point>(theIndex, theName, theBox)
			, theBackMesh_(theBackMesh)
		{}

		GeoSizeFun_Background
		(
			const Standard_Integer theIndex,
			const word& theName,
			Entity_Box<Point>&& theBox,
			std::shared_ptr<BackMeshData>&& theBackMesh
		)
			: GeoSizeFun_nonUniform<typename BackMeshData::Point>(theIndex, theName, std::move(theBox))
			, theBackMesh_(std::move(theBackMesh))
		{}


		//- public functions and operators

		const std::shared_ptr<BackMeshData>& BackMesh() const
		{
			return theBackMesh_;
		}


		//- override functions and operators

		Standard_Real Value(const Point& theCoord) const override;
	};
}

#include <GeoSizeFun_BackgroundI.hxx>

#endif // !_GeoSizeFun_Background_Header
