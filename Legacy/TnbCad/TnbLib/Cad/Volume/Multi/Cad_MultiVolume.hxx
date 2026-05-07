#pragma once
#ifndef _Cad_MultiVolume_Header
#define _Cad_MultiVolume_Header

#include <Cad_Volume.hxx>

#include <map>
#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [6/13/2023 Payvand]

	class Cad_Solid;

	class Cad_MultiVolume
		: public Cad_Volume
	{

	public:

		struct PairedEntity
		{
			Standard_Integer surf0;
			Standard_Integer surf1;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar& surf0;
				ar& surf1;
			}
		};

	private:

		/*Private Data*/

		std::vector<std::shared_ptr<Cad_Solid>> theSolids_;

		std::map<Standard_Integer, Standard_Integer> thePairs_;

		// Private functions and operators [6/13/2023 Payvand]

		TnbCad_EXPORT void Check();

		TNB_SERIALIZATION(TnbCad_EXPORT);


		// default constructor [6/13/2023 Payvand]

		Cad_MultiVolume()
		{}

	public:

		// default constructor [6/13/2023 Payvand]


		// constructors [6/13/2023 Payvand]

		TnbCad_EXPORT Cad_MultiVolume
		(
			const std::vector<std::shared_ptr<Cad_Solid>>& theSolids
		);

		TnbCad_EXPORT Cad_MultiVolume
		(
			std::vector<std::shared_ptr<Cad_Solid>>&& theSolids
		);

		TnbCad_EXPORT Cad_MultiVolume
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::vector<std::shared_ptr<Cad_Solid>>& theSolids
		);

		TnbCad_EXPORT Cad_MultiVolume
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<std::shared_ptr<Cad_Solid>>&& theSolids
		);

		// Public functions and operators

		const auto& Solids() const
		{
			return theSolids_;
		}

		TnbCad_EXPORT Standard_Integer IsPairedSurface(const Standard_Integer theIndex) const override;
		TnbCad_EXPORT Standard_Integer NbPairs() const;
		const auto& Pairs() const { return thePairs_; }

		// It registers the two surfaces as a paired entity; the order of surfaces doesn't matter
		TnbCad_EXPORT void SetPairs(const PairedEntity& theSurfaces);

		// Override virtual functions

		TnbCad_EXPORT Standard_Integer NbVolumes() const override;
		TnbCad_EXPORT std::shared_ptr<Cad_Solid>
			Volume(const Standard_Integer theIndex) const override;

		TnbCad_EXPORT std::vector<std::shared_ptr<Cad_Solid>> Volumes() const override;
		TnbCad_EXPORT std::vector<std::shared_ptr<TModel_Surface>> RetrieveSurfaces() const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Cad_MultiVolume);

#endif // !_Cad_MultiVolume_Header
