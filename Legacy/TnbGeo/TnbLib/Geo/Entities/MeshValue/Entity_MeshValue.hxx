#pragma once
#ifndef _Entity_MeshValue_Header
#define _Entity_MeshValue_Header

#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>
#include <vector>
#include <string>

namespace tnbLib
{

	template<class MeshType, class ValueType>
	class Entity_MeshValue
	{

		/*Private Data*/

		std::shared_ptr<MeshType> theMesh_;

		std::vector<ValueType> theValues_;


		// Private functions and operators [12/30/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			Info << "This function is not supposed to be called!" << endl;
			NotImplemented;
		}

	public:

		static const TnbGeo_EXPORT std::string extension;

		// default constructor [12/29/2021 Amir]

		Entity_MeshValue()
		{}

		// constructors [12/29/2021 Amir]

		Entity_MeshValue
		(
			const std::shared_ptr<MeshType>& theMesh
		)
			: theMesh_(theMesh)
		{}

		Entity_MeshValue
		(
			std::shared_ptr<MeshType>&& theMesh
		)
			: theMesh_(std::move(theMesh))
		{}

		Entity_MeshValue
		(
			const std::shared_ptr<MeshType>& theMesh, 
			const std::vector<ValueType>& theValues
		)
			: theMesh_(theMesh)
			, theValues_(theValues)
		{}

		Entity_MeshValue
		(
			std::shared_ptr<MeshType>&& theMesh,
			std::vector<ValueType>&& theValues
		)
			: theMesh_(std::move(theMesh))
			, theValues_(std::move(theValues))
		{}

		// public functions and operators [12/29/2021 Amir]

		const auto& Mesh() const
		{
			return theMesh_;
		}

		const auto& Values() const
		{
			return theValues_;
		}

		auto& MeshRef()
		{
			return theMesh_;
		}

		auto& ValuesRef()
		{
			return theValues_;
		}

		void SetMesh(const std::shared_ptr<MeshType>& theMesh)
		{
			theMesh_ = theMesh;
		}

		void SetMesh(std::shared_ptr<MeshType>&& theMesh)
		{
			theMesh_ = std::move(theMesh);
		}

		void SetValues(const std::vector<ValueType>& theValues)
		{
			theValues_ = theValues;
		}

		void SetValues(std::vector<ValueType>&& theValues)
		{
			theValues_ = std::move(theValues);
		}
	};
}

#endif // !_Entity_MeshValue_Header
