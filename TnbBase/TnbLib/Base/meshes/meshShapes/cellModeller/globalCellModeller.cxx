#include <cellModeller.hxx>

#include <OSspecific.hxx>
#include <IFstream.hxx>

// * * * * * * * * * * * * * * * Static data * * * * * * * * * * * * * * * * //


// PtrList of models
tnbLib::PtrList<tnbLib::cellModel> tnbLib::cellModeller::models_
(
	IFstream(findEtcFile("cellModels", true))()
);

// List of model pointers
tnbLib::List<tnbLib::cellModel*> tnbLib::cellModeller::modelPtrs_;

// HashTable of model pointers
tnbLib::HashTable<const tnbLib::cellModel*> tnbLib::cellModeller::modelDictionary_;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Construct a dummy cellModeller which reads the models and fills
	// the above tables
	cellModeller globalCellModeller_;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //