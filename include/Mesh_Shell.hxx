#pragma once
#ifndef _Mesh_Shell_Header
#define _Mesh_Shell_Header

#include <Entity3d_BoxFwd.hxx>
#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	template<class MeshSurf>
	class Mesh_Shell
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		std::vector<std::shared_ptr<MeshSurf>> theSurfaces_;

		/*Private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			Info << "This function is not supposed to be called." << endl;
			NotImplemented;
		}

	public:

		// default constructor [3/7/2023 Payvand]

		Mesh_Shell()
			: Global_Named("shell")
		{}


		// constructors [3/7/2023 Payvand]

		explicit Mesh_Shell(const std::vector<std::shared_ptr<MeshSurf>>& theSurfaces)
			: theSurfaces_(theSurfaces)
		{}

		Mesh_Shell(std::vector<std::shared_ptr<MeshSurf>>&& theSurfaces)
			: theSurfaces_(std::move(theSurfaces))
		{}

		Mesh_Shell
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::vector<std::shared_ptr<MeshSurf>>& theSurfaces
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theSurfaces_(theSurfaces)
		{}

		Mesh_Shell
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<std::shared_ptr<MeshSurf>>&& theSurfaces
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theSurfaces_(std::move(theSurfaces))
		{}


		// Public functions and operators [3/7/2023 Payvand]

		auto NbSurfaces() const
		{
			return (Standard_Integer)theSurfaces_.size();
		}

		Entity3d_Box CalcBoundingBox() const;

		const auto& Surfaces() const { return theSurfaces_; }

		void ExportToPlt(OFstream&) const;

		static std::vector<std::shared_ptr<MeshSurf>> 
			RetrieveSurfaces(const std::vector<std::shared_ptr<MeshSurf>>& theShell);

	};
}

#endif // !_Mesh_Shell_Header
