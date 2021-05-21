#pragma once
#ifndef _Mesh2d_SizeMapTool_Header
#define _Mesh2d_SizeMapTool_Header

#include <Global_Done.hxx>
#include <Mesh_SizeMapToolBase.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;

	class Mesh2d_SizeMapTool
		: public Mesh_SizeMapToolBase<GeoMesh2d_Background>
		, public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_Plane> thePlane_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		//- default constructor
		Mesh2d_SizeMapTool()
		{}


		//- constructor

		Mesh2d_SizeMapTool
		(
			const std::shared_ptr<Mesh_ReferenceValues>& theRef, 
			const std::shared_ptr<Cad2d_Plane>& thePlane
		)
			: Mesh_SizeMapToolBase<GeoMesh2d_Background>(theRef)
			, thePlane_(thePlane)
		{}


		virtual ~Mesh2d_SizeMapTool()
		{}

	public:


		const auto& Plane() const
		{
			return thePlane_;
		}
	};
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Mesh2d_SizeMapTool);


namespace tnbLib
{

	template<>
	template<>
	void Mesh_SizeMapToolBase<GeoMesh2d_Background>::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int /*file_version*/
			);

	template<>
	template<>
	void Mesh_SizeMapToolBase<GeoMesh2d_Background>::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);
}

#endif // !_Mesh2d_SizeMapTool_Header
