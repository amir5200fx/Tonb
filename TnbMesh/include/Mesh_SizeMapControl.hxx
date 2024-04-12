#pragma once
#ifndef _Mesh_SizeMapControl_Header
#define _Mesh_SizeMapControl_Header

#include <word.hxx>
#include <Global_Serialization.hxx>
#include <Global_Done.hxx>
#include <Mesh_SizeMapControl_Traits.hxx>
#include <Mesh_Module.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	template<class Box>
	class Mesh_ReferenceValues;

	class Mesh_SizeMapControl_Info;

	class Mesh_SizeMapControl_Base
	{

		/*Private Data*/

		std::shared_ptr<Mesh_SizeMapControl_Info> theInfo_;

		// Private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor [7/18/2022 Amir]

		TnbMesh_EXPORT Mesh_SizeMapControl_Base();

		// constructors [7/18/2022 Amir]

	public:

		static TnbMesh_EXPORT const std::shared_ptr<Mesh_SizeMapControl_Info> DEFAULT_INFO;
		static TnbMesh_EXPORT unsigned short verbose;

		// public functions and operators [7/18/2022 Amir]

		const auto& SizeMapInfo() const
		{
			return theInfo_;
		}

		void SetInfo(const std::shared_ptr<Mesh_SizeMapControl_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetInfo(std::shared_ptr<Mesh_SizeMapControl_Info>&& theInfo)
		{
			theInfo_ = std::move(theInfo);
		}
	};

	template<class GeomType>
	class Mesh_SizeMapControl
		: public Mesh_SizeMapControl_Base
		, public Global_Done
	{

	public:

		typedef typename size_map_type<GeomType>::type sizeMapTool;
		typedef typename size_map_type<GeomType>::boxType boxType;
		typedef typename size_map_type<GeomType>::backMeshType backMeshType;
		typedef typename size_map_type<GeomType>::cloudType cloudType;

		typedef Mesh_ReferenceValues<boxType> meshRefValuesType;

	private:

		/*Private Data*/

		std::shared_ptr<meshRefValuesType> theReference_;
		std::shared_ptr<boxType> theDomain_;
		std::shared_ptr<cloudType> theCloud_;

		std::map<word, std::shared_ptr<sizeMapTool>> theBoundaries_;


		// results [7/17/2022 Amir]

		std::shared_ptr<backMeshType> theBackground_;

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			// it's not supposed to be called. [5/30/2021 Amir]
			NotImplemented;
		}

	protected:

		//- default constructor
		Mesh_SizeMapControl()
		{}

		//- constructors

		Mesh_SizeMapControl
		(
			const std::shared_ptr<meshRefValuesType>& theRef,
			const std::shared_ptr<boxType>& theDomain,
			const std::shared_ptr<cloudType>& theCloud
		)
			: theReference_(theRef)
			, theDomain_(theDomain)
			, theCloud_(theCloud)
		{}


		//- protected functions and operators

		

	public:


		virtual ~Mesh_SizeMapControl()
		{}

		//- public functions and operators

		Standard_Integer NbMaps() const
		{
			return (Standard_Integer)theBoundaries_.size();
		}

		Standard_Boolean HasSizeMap(const word& theName);

		const auto& References() const
		{
			return theReference_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Cloud() const
		{
			return theCloud_;
		}

		const auto& Maps() const
		{
			return theBoundaries_;
		}

		const std::shared_ptr<backMeshType>& BackgroundMesh() const;

		void Perform();

		void Import(const word& theName, const std::shared_ptr<sizeMapTool>& theSizeMap);
		void Remove(const word& theName);

		void LoadReference(const std::shared_ptr<meshRefValuesType>& theRef)
		{
			theReference_ = theRef;
		}

		void LoadReference(std::shared_ptr<meshRefValuesType>&& theRef)
		{
			theReference_ = std::move(theRef);
		}

		void SetDomain(const std::shared_ptr<boxType>& theDomain)
		{
			theDomain_ = theDomain;
		}

		void SetDomain(std::shared_ptr<boxType>&& theDomain)
		{
			theDomain_ = std::move(theDomain);
		}

		void SetCloud(const std::shared_ptr<cloudType>& theCloud)
		{
			theCloud_ = theCloud;
		}

		void SetCloud(std::shared_ptr<cloudType>&& theCloud)
		{
			theCloud_ = std::move(theCloud);
		}
	};
}

#include <Mesh_SizeMapControlI.hxx>

#endif // !_Mesh_SizeMapControl_Header
