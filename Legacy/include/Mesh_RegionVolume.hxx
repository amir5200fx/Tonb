#pragma once
#ifndef _Mesh_RegionVolume_Header
#define _Mesh_RegionVolume_Header

#include <Mesh_RegionVolumeTraits.hxx>
#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <OFstream.hxx>

#include <memory>
#include <vector>
#include <map>

namespace tnbLib
{

	// Forward Declarations [3/7/2023 Payvand]

	template<class SurfType>
	class Mesh_Surface;

	template<class MeshSurf>
	class Mesh_Shell;

	template<class SurfType>
	class Mesh_RegionVolume
		: public Global_Indexed
		, public Global_Named
	{

	public:

		typedef Mesh_Surface<SurfType> surfMeshType;
		typedef typename Mesh_RegionVolumeTraits<SurfType>::volType
			volType;

		typedef Mesh_Shell<surfMeshType> shellType;

	private:

		/*Private Data*/

		std::shared_ptr<volType> theSolid_;

		std::shared_ptr<shellType> theOuter_;
		std::shared_ptr<std::vector<std::shared_ptr<shellType>>> theInners_;


		// default constructor [3/8/2023 Payvand]

		Mesh_RegionVolume()
		{}


		// Private functions and operators [3/8/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive&, const unsigned int /*file_version*/)
		{
			Info << "WARNING! This function is not supposed to be called." << endl;
			NotImplemented;
		}

	public:

		// default constructor [3/7/2023 Payvand]

		// constructors [3/7/2023 Payvand]

		Mesh_RegionVolume
		(
			const std::shared_ptr<volType>& theSolid,
			const std::shared_ptr<shellType>& theOuter, 
			const std::shared_ptr<std::vector<std::shared_ptr<shellType>>>& theInners = nullptr
		)
			: theSolid_(theSolid)
			, theOuter_(theOuter)
			, theInners_(theInners)
		{}

		Mesh_RegionVolume
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<volType>& theSolid,
			const std::shared_ptr<shellType>& theOuter,
			const std::shared_ptr<std::vector<std::shared_ptr<shellType>>>& theInners = nullptr
		)
			: theSolid_(theSolid)
			, theOuter_(theOuter)
			, theInners_(theInners)
		{}


		// Public functions and operators [3/8/2023 Payvand]

		const auto& Solid() const
		{
			return theSolid_;
		}

		Standard_Boolean HasHole() const;
		Standard_Integer NbHoles() const;

		const auto& Inners() const { return theInners_; }
		const auto& Outer() const { return theOuter_; }

		void SetSolid(const std::shared_ptr<volType>& theSolid)
		{
			theSolid_ = theSolid;
		}

		void RetrieveShellsTo(std::vector<std::shared_ptr<shellType>>&) const;
		void ExportToPlt(OFstream&) const;


		// Static functions [3/8/2023 Payvand]

		/*template<class ShellType>
		static std::shared_ptr<shellType> MakeMeshShell(const ShellType& theShell);

		static std::shared_ptr<Mesh_RegionVolume> MakeVolume(const std::shared_ptr<volType>&);*/
	};
}

#include <Mesh_RegionVolumeI.hxx>

#endif // !_Mesh_RegionVolume_Header
