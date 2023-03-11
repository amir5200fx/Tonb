#pragma once
#ifndef _Mesh_Surface_Header
#define _Mesh_Surface_Header

#include <Entity3d_TriangulationFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Global_Indexed.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>

namespace tnbLib
{

	template<class SurfType>
	class Mesh_Surface
		: public Global_Indexed
	{

		/*Private Data*/

		std::shared_ptr<SurfType> theSurface_;

		std::shared_ptr<Entity2d_Triangulation> theParaTriangulation_;
		std::shared_ptr<Entity3d_Triangulation> theTriangulation_;


		// Private functions and operators [3/9/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			Info << "This function is not supposed to be called." << endl;
			NotImplemented;
		}

	public:

		// default constructor [3/9/2023 Payvand]

		Mesh_Surface()
		{}

		// constructors [3/9/2023 Payvand]

		explicit Mesh_Surface(const std::shared_ptr<SurfType>& theSurface)
			: theSurface_(theSurface)
		{}

		Mesh_Surface(std::shared_ptr<SurfType>&& theSurface)
			: theSurface_(std::move(theSurface))
		{}

		Mesh_Surface
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<SurfType>& theSurface
		)
			: Global_Indexed(theIndex)
			, theSurface_(theSurface)
		{}

		Mesh_Surface
		(
			const Standard_Integer theIndex,
			std::shared_ptr<SurfType>&& theSurface
		)
			: Global_Indexed(theIndex)
			, theSurface_(std::move(theSurface))
		{}


		// Public functions and operators [3/9/2023 Payvand]

		const auto& Surface() const { return theSurface_; }
		const auto& ParaTriangulation() const { return theParaTriangulation_; }
		const auto& Triangulation() const { return theTriangulation_; }

		void SetSurface(const std::shared_ptr<SurfType>& theSurface);
		void SetSurface(std::shared_ptr<SurfType>&& theSurface);
		void SetParaTriangulation(const std::shared_ptr<Entity2d_Triangulation>&);
		void SetParaTriangulation(std::shared_ptr<Entity2d_Triangulation>&&);
		void SetTriangulation(const std::shared_ptr<Entity3d_Triangulation>&);
		void SetTriangulation(std::shared_ptr<Entity3d_Triangulation>&&);
	};
}

#include <Mesh_SurfaceI.hxx>

#endif // !_Mesh_Surface_Header
